#include "EnlightedItems.hpp"
#include <cassert>
#include "Light.hpp"
#include "LightSystem.hpp"
#include "QBox2D/QFixture.hpp"
#include "QBox2D/QWorld.hpp"
#include "StaticLight.hpp"

EnlightedItems::EnlightedItems(LightSystem* system, SceneGraph::Item* parent)
    : SceneGraph::Item(parent), m_lightSystem(system), m_state() {}

void EnlightedItems::clear() { m_state |= Reset; }

QWorld* EnlightedItems::world() const { return lightSystem()->world(); }

std::unique_ptr<SceneGraph::Node> EnlightedItems::synchronize(
    std::unique_ptr<SceneGraph::Node> root) {
  if (!root) root = std::make_unique<Node>();

  Node* node = static_cast<Node*>(root.get());
  while (node->firstChild()) node->removeChild(node->firstChild());

  if (m_state & Reset) {
    m_state &= ~Reset;
    node->clear();
  }

  while (!m_destroyedFixture.empty()) {
    node->destroyedFixture(m_destroyedFixture.back());
    m_destroyedFixture.pop_back();
  }

  uint it = 0;
  QRectF visibleArea = world()->visibleRect();
  for (StaticLight* light : lightSystem()->visibleLights()) {
    if (!light->dynamicLight()) continue;

    QRectF lightRect = light->matrix().mapRect(light->boundingRect());
    QRectF rect = visibleArea.intersected(lightRect);
    for (QFixture* f : world()->fixtures(rect)) {
      if (f->shadowCaster()) {
        EnlightedNode* enlightedNode = node->getNode(f, light, it++);
        node->appendChild(enlightedNode);
      }
    }
  }

  update();

  return root;
}

void EnlightedItems::onFixtureDestroyed(QFixture* f) {
  if (f->shadowCaster()) m_destroyedFixture.push_back(f);
}

EnlightedNode::EnlightedNode() {
  m_geometryNode.setMaterial(&m_material);
  appendChild(&m_geometryNode);
}

void EnlightedNode::update(QFixture* fixture, Light* light) {
  updateMatrix(fixture);
  updateMaterial(light);
}

void EnlightedNode::setGeometry(SceneGraph::Geometry* g) {
  m_geometryNode.setGeometry(g);
}

void EnlightedNode::updateMaterial(Light* light) {
  m_material.setNormalMap(light->lightSystem()->normalMap()->shaderNode());
  QVector3D p(light->position().x(), light->position().y(), light->z());
  m_material.setLightPosition(matrix().inverted() * p);
  m_material.setColor(light->color());
  m_material.setAttenuation(light->attenuation());
}

void EnlightedNode::updateMatrix(QFixture* fixture) {
  setMatrix(fixture->body()->matrix() * fixture->matrix());
}

EnlightedItems::Node::Node() : m_node(1) {}

EnlightedItems::Node::~Node() { clear(); }

void EnlightedItems::Node::clear() {
  m_data.clear();
  m_node.clear();
  m_node.resize(1);
}

SceneGraph::Geometry* EnlightedItems::Node::geometry(QFixture* fixture) {
  if (m_data.find(fixture) != m_data.end()) return m_data[fixture].get();

  std::vector<QPointF> vert = fixture->vertices();
  std::unique_ptr<SceneGraph::Geometry> g =
      std::make_unique<SceneGraph::Geometry>(
          std::vector<SceneGraph::Attribute>({{2, GL_FLOAT}}), vert.size() - 1,
          sizeof(Vertex));
  Vertex* array = g->vertexData<Vertex>();
  g->setDrawingMode(GL_TRIANGLE_FAN);
  for (uint i = 0; i + 1 < vert.size(); i++)
    array[i] = {float(vert[i].x()), float(vert[i].y())};
  g->updateVertexData();

  return (m_data[fixture] = std::move(g)).get();
}

EnlightedNode* EnlightedItems::Node::getNode(QFixture* f, Light* light,
                                             uint it) {
  if (it >= m_node.size()) m_node.resize(2 * m_node.size());

  if (m_node[it] == nullptr) m_node[it] = std::make_unique<EnlightedNode>();

  EnlightedNode* node = m_node[it].get();
  node->setGeometry(geometry(f));
  node->update(f, light);

  return node;
}

void EnlightedItems::Node::destroyedFixture(void* f) {
  auto it = m_data.find(f);
  if (it != m_data.end()) {
    m_data.erase(it);
  }
}
