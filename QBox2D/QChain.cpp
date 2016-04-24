#include "QChain.hpp"
#include <QJsonArray>
#include <QJsonObject>
#include <QPainterPath>
#include <QPolygonF>
#include "Geometry/Circle.hpp"
#include "Geometry/Functions.hpp"
#include "Geometry/Vector2d.hpp"
#include "Graphics/Primitives.hpp"
#include "QBox2D/Fixture/Box2DBox.hpp"
#include "QBox2D/Fixture/Box2DChain.hpp"
#include "QBox2D/Fixture/Box2DChain.hpp"
#include "QBox2D/Fixture/Box2DEdge.hpp"
#include "QBox2D/QBody.hpp"
#include "QBox2D/QFixture.hpp"
#include "QBox2D/QWorld.hpp"
#include "Utility/Utility.hpp"

static b2Vec2 tob2Vec2(QPointF p) { return b2Vec2(p.x(), p.y()); }

QChain::QChain(Item *parent) : QBody(parent), m_texture(this) {}

QChain::~QChain() {}

void QChain::setVertices(const std::vector<QPointF> &v) {
  m_vertices = v;
  createChain();
}

void QChain::cutCircle(Circle circle) {
  if (m_vertices.size() == 0) return;
  circle.setCenter(circle.pos());

  QPainterPath cr;
  cr.addEllipse(circle.x - circle.r, circle.y - circle.r, 2 * circle.r,
                2 * circle.r);

  QPolygonF polygon;
  for (QPointF p : m_vertices) polygon.append(p);
  QPainterPath chain;
  chain.addPolygon(polygon);

  if (!chain.intersects(cr)) return;

  chain = chain.subtracted(cr);

  for (const QPolygonF &poly : chain.toSubpathPolygons()) {
    std::vector<Vector2d> pts(poly.begin(), poly.end() - 1);

    if (std::fabs(Geometry::area(pts.begin(), pts.end())) > 5.f) {
      auto chain = std::make_unique<QChain>(world());
      chain->setVertices(std::vector<QPointF>(pts.begin(), pts.end()));
      chain->initializeLater(world());

      world()->itemSet()->addBody(std::move(chain));
    }
  }

  m_vertices.clear();
  destroyLater();
}

bool QChain::testPoint(const QPointF &point) const {
  std::vector<Vector2d> vert(m_vertices.begin(), m_vertices.end() - 1);
  return Geometry::pointInPolygon(vert.begin(), vert.end(), Vector2d(point));
}

bool QChain::read(const QJsonObject &obj) {
  std::vector<QPointF> pts;
  QJsonArray array = obj["vertices"].toArray();
  for (int i = 0; i < array.size(); i++)
    pts.push_back(Utility::Json::toPoint(array[i].toObject()));
  setVertices(pts);
  texture().setSource(obj["textureSource"].toString());
  texture().setTextureScale(
      QVector2D(Utility::Json::toPoint(obj["textureScale"].toObject())));

  return true;
}

bool QChain::write(QJsonObject &obj) const {
  obj["class"] = QString("QChain");
  obj["textureSource"] = texture().source();
  obj["textureScale"] = Utility::Json::toObject(QPointF(0.02, 0.02));

  QJsonArray array;
  std::vector<QPointF> pts = vertices();
  for (uint i = 0; i < pts.size(); i++)
    array.append(Utility::Json::toObject(pts[i]));
  obj["vertices"] = array;

  return true;
}

void QChain::createChain() {
  std::vector<Vector2d> tmp(m_vertices.begin(), m_vertices.end());
  tmp = Geometry::simplifyPolygon(tmp, 0.2);

  m_vertices = std::vector<QPointF>(tmp.begin(), tmp.end());
  std::vector<QPointF> pts = vertices();

  size_t it = pts.size() - 1, prev = it - 1, next = 1;
  for (size_t i = 0; i < pts.size(); i++) {
    QPointF vec = pts[i] - pts[it];
    QPointF vecp = pts[it] - pts[prev], vecn = pts[next] - pts[i];

    auto fixture = std::make_unique<Box2DEdge>(this);
    fixture->setVisible(false);
    fixture->setShadowCaster(false);

    b2EdgeShape &edge = fixture->edgeShape();
    edge.Set(tob2Vec2(pts[it]), tob2Vec2(pts[i]));

    if (QPointF::dotProduct(vec, vecp) > 0) {
      edge.m_hasVertex0 = true;
      edge.m_vertex0 = tob2Vec2(pts[prev]);
    }
    if (QPointF::dotProduct(vec, vecn) > 0) {
      edge.m_hasVertex3 = true;
      edge.m_vertex3 = tob2Vec2(pts[next]);
    }
    addFixture(std::move(fixture));

    prev = it, it = i;
    next = next + 1 < pts.size() ? next + 1 : 0;
  }

  qreal minx = INF, miny = INF, maxx = -INF, maxy = -INF;
  for (QPointF p : vertices()) {
    minx = std::min(minx, p.x());
    miny = std::min(miny, p.y());
    maxx = std::max(maxx, p.x());
    maxy = std::max(maxy, p.y());
  }

  auto box = std::make_unique<Box2DBox>();
  box->setSize(QSizeF(maxx - minx, maxy - miny));
  box->setPosition(QPointF(minx, miny));
  box->setVisible(false);
  box->setSensor(true);
  addFixture(std::move(box));

  m_texture.setVertices(vertices());
}
