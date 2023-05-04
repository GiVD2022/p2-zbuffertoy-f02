QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter -Wpedantic -Wno-warn
# You can make yousr code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller.cpp \
    DataInOut/AttributeMapping.cpp \
    DataInOut/VisualMapping.cpp \
    GPUConnections/GPUCamera.cpp \
    GPUConnections/GPULight.cpp \
    GPUConnections/GPULightFactory.cpp \
    GPUConnections/GPUMesh.cpp \
    GPUConnections/GPUObjectFactory.cpp \
    GPUConnections/GPUPointLight.cpp \
    GPUConnections/GPUSpotLight.cpp \
    GPUConnections/GPUDirectionalLight.cpp \
    GPUConnections/GPUScene.cpp \
    GPUConnections/GPUSceneFactory.cpp \
    GPUConnections/GPUSceneFactoryData.cpp \
    GPUConnections/GPUSceneFactoryVirtual.cpp \
    GPUConnections/GPUSetUp.cpp \
    Main.cpp \
    Model/Modelling/Animation.cpp \
    Model/Modelling/Lights/Light.cpp \
    Model/Modelling/Lights/LightFactory.cpp \
    Model/Modelling/Lights/PointLight.cpp \
    Model/Modelling/Lights/DirectionalLight.cpp \
    Model/Modelling/Lights/SpotLight.cpp \
    Model/Modelling/Materials/ColorMapStatic.cpp \
    Model/Modelling/Materials/Lambertian.cpp \
    Model/Modelling/Materials/Material.cpp \
    Model/Modelling/Materials/MaterialFactory.cpp \
    Model/Modelling/Materials/Texture.cpp \
    Model/Modelling/Objects/Face.cpp \
    Model/Modelling/Objects/Mesh.cpp \
    Model/Modelling/Objects/Object.cpp \
    Model/Modelling/Objects/ObjectFactory.cpp \
    Model/Modelling/Scene.cpp \
    Model/Modelling/TG/TG.cpp \
    Model/Modelling/TG/TranslateTG.cpp \
    Model/Rendering/ColorShading.cpp \
    Model/Rendering/ColorShadow.cpp \
    Model/Rendering/SetUp.cpp \
    Model/Rendering/ShadingFactory.cpp \
    ViewGL/GLBuilder.cpp \
    ViewGL/GLMainWindow.cpp \
    ViewGL/GLShader.cpp \
    ViewGL/GLWidget.cpp \
    library/Common.cpp

HEADERS += \
    Controller.hh \
    DataInOut/AttributeMapping.hh \
    DataInOut/Serializable.hh \
    DataInOut/VisualMapping.hh \
    GPUConnections/GPUCamera.hh \
    GPUConnections/GPUConnectable.hh \
    GPUConnections/GPULight.hh \
    GPUConnections/GPULightFactory.hh \
    GPUConnections/GPUMesh.hh \
    GPUConnections/GPUObjectFactory.hh \
    GPUConnections/GPUPointLight.hh \
    GPUConnections/GPUSpotLight.hh \
    GPUConnections/GPUDirectionalLight.hh \
    GPUConnections/GPUScene.hh \
    GPUConnections/GPUSceneFactory.hh \
    GPUConnections/GPUSceneFactoryData.hh \
    GPUConnections/GPUSceneFactoryVirtual.hh \
    GPUConnections/GPUSetUp.hh \
    Model/Modelling/Animation.hh \
    Model/Modelling/Hitable.hh \
    Model/Modelling/Lights/Light.hh \
    Model/Modelling/Lights/LightFactory.hh \
    Model/Modelling/Lights/PointLight.hh \
    Model/Modelling/Lights/DirectionalLight.hh \
    Model/Modelling/Lights/SpotLight.hh \
    Model/Modelling/Materials/ColorMap.hh \
    Model/Modelling/Materials/ColorMapStatic.hh \
    Model/Modelling/Materials/Lambertian.hh \
    Model/Modelling/Materials/Material.hh \
    Model/Modelling/Materials/MaterialFactory.hh \
    Model/Modelling/Materials/Texture.hh \
    Model/Modelling/Objects/Face.hh \
    Model/Modelling/Objects/Mesh.hh \
    Model/Modelling/Objects/Object.hh \
    Model/Modelling/Objects/ObjectFactory.hh \
    Model/Modelling/Ray.hh \
    Model/Modelling/Scene.hh \
    Model/Modelling/TG/TG.hh \
    Model/Modelling/TG/TranslateTG.hh \
    Model/Rendering/ColorShading.hh \
    Model/Rendering/ColorShadow.hh \
    Model/Rendering/SetUp.hh \
    Model/Rendering/ShadingFactory.hh \
    Model/Rendering/ShadingStrategy.hh \
    ViewGL/GLBuilder.hh \
    ViewGL/GLMainWindow.hh \
    ViewGL/GLShader.hh \
    ViewGL/GLWidget.hh \
    library/Common.h \
    library/Singleton.hh \
    library/mat.h \
    library/vec.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    libWin32/glut.dll \
    libWin32/glut.lib \
    libWin32/glut32.dll \
    libWin32/glut32.lib

FORMS += \
    about.ui \
    mainwindow.ui

RESOURCES += \
    resources.qrc
