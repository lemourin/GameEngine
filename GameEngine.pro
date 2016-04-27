QT = core gui quick
CONFIG += c++14
CONFIG -= debug_and_release
TARGET = GameEngine
TEMPLATE = lib
OBJECTS_DIR = .obj
MOC_DIR = .moc
INCLUDEPATH += Box2D/

SOURCES += \
    Actions/Action.cpp \
    Actions/AddBody.cpp \
    Actions/AddChain.cpp \
    Actions/AddCircle.cpp \
    Actions/AddFixture.cpp \
    Actions/AddPolygon.cpp \
    Actions/AddRectangle.cpp \
    Actions/BodyEdit.cpp \
    Actions/DeleteItem.cpp \
    Actions/FileAction.cpp \
    Actions/GrabItem.cpp \
    Actions/MainAction.cpp \
    Actions/MapEditor.cpp \
    Actions/SubAction.cpp \
    Geometry/Circle.cpp \
    Geometry/Edge.cpp \
    Geometry/Functions.cpp \
    Geometry/Triangle.cpp \
    Geometry/Triangulate.cpp \
    Geometry/Vector2d.cpp \
    Lighting/DynamicLight.cpp \
    Lighting/EnlightedItems.cpp \
    Lighting/Light.cpp \
    Lighting/LightBlender.cpp \
    Lighting/LightMaterial.cpp \
    Lighting/LightSystem.cpp \
    Lighting/StaticLight.cpp \
    QBox2D/Fixture/Box2DBox.cpp \
    QBox2D/Fixture/Box2DChain.cpp \
    QBox2D/Fixture/Box2DCircle.cpp \
    QBox2D/Fixture/Box2DEdge.cpp \
    QBox2D/Fixture/Box2DPolygon.cpp \
    QBox2D/Fixture/Fixture.cpp \
    QBox2D/QBody.cpp \
    QBox2D/QChain.cpp \
    QBox2D/QFixture.cpp \
    QBox2D/QJoint.cpp \
    QBox2D/QWorld.cpp \
    Graphics/ParticleSystem.cpp \
    Graphics/Primitives.cpp \
    Graphics/SpriteSequence.cpp \
    Graphics/TexturedConvexPolygon.cpp \
    Graphics/TexturedItem.cpp \
    Graphics/TexturedPolygon.cpp \
    Graphics/TexturedRectangle.cpp \
    Utility/BaseItem.cpp \
    Utility/DisplayItem.cpp \
    Utility/Utility.cpp \
    Actions/FixtureEdit.cpp

HEADERS += \
    Actions/Action.hpp \
    Actions/AddBody.hpp \
    Actions/AddChain.hpp \
    Actions/AddCircle.hpp \
    Actions/AddFixture.hpp \
    Actions/AddPolygon.hpp \
    Actions/AddRectangle.hpp \
    Actions/BodyEdit.hpp \
    Actions/DeleteItem.hpp \
    Actions/FileAction.hpp \
    Actions/GrabItem.hpp \
    Actions/MainAction.hpp \
    Actions/MapEditor.hpp \
    Actions/SubAction.hpp \
    Geometry/Circle.hpp \
    Geometry/Edge.hpp \
    Geometry/Functions.hpp \
    Geometry/Triangle.hpp \
    Geometry/Triangulate.hpp \
    Geometry/Vector2d.hpp \
    Lighting/DynamicLight.hpp \
    Lighting/EnlightedItems.hpp \
    Lighting/Light.hpp \
    Lighting/LightBlender.hpp \
    Lighting/LightMaterial.hpp \
    Lighting/LightSystem.hpp \
    Lighting/StaticLight.hpp \
    QBox2D/Fixture/Box2DBox.hpp \
    QBox2D/Fixture/Box2DChain.hpp \
    QBox2D/Fixture/Box2DCircle.hpp \
    QBox2D/Fixture/Box2DEdge.hpp \
    QBox2D/Fixture/Box2DPolygon.hpp \
    QBox2D/Fixture/Fixture.hpp \
    QBox2D/QBody.hpp \
    QBox2D/QChain.hpp \
    QBox2D/QFixture.hpp \
    QBox2D/QJoint.hpp \
    QBox2D/QWorld.hpp \
    Graphics/ParticleSystem.hpp \
    Graphics/Primitives.hpp \
    Graphics/SpriteSequence.hpp \
    Graphics/TexturedConvexPolygon.hpp \
    Graphics/TexturedItem.hpp \
    Graphics/TexturedPolygon.hpp \
    Graphics/TexturedRectangle.hpp \
    Utility/BaseItem.hpp \
    Utility/DisplayItem.hpp \
    Utility/Factory.hpp \
    Utility/List.hpp \
    Utility/Pool.hpp \
    Utility/Utility.hpp \
    Actions/FixtureEdit.hpp

unix|win32: LIBS += -L$$OUT_PWD/SceneGraph/ -lSceneGraph
INCLUDEPATH += $$PWD/SceneGraph
DEPENDPATH += $$PWD/SceneGraph

unix|win32: LIBS += -L$$OUT_PWD/Box2D/ -lBox2D
INCLUDEPATH += $$PWD/Box2D
DEPENDPATH += $$PWD/Box2D

