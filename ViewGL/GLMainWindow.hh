#pragma once

#include <QMainWindow>

#include "Controller.hh"
#include "ViewGL/GLWidget.hh"
#include "GPUConnections/GPUCamera.hh"
#include "ViewGL/GLBuilder.hh"

#include "ui_mainwindow.h"
#include "ui_about.h"


#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
    class QSlider;
    class GLWidget;
QT_END_NAMESPACE

namespace Ui {
   class MainWindow;
}

class GLMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit GLMainWindow(QWidget *parent = 0);
    ~GLMainWindow();

    bool changes; // Variable de control de canvis

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
    GLBuilder *builder;
    GLWidget  *glWidget;


private slots:

    void on_persNearSpin_valueChanged(double arg1);

    void on_persFarSpin_valueChanged(double arg1);

    void on_lookEyeXSpin_valueChanged(double arg1);

    void on_lookEyeYSpin_valueChanged(double arg1);

    void on_lookEyeZSpin_valueChanged(double arg1);

    void on_lookCenterXSpin_valueChanged(double arg1);

    void on_lookCenterYSpin_valueChanged(double arg1);

    void on_lookCenterZSpin_valueChanged(double arg1);

    void on_lookUpXSpin_valueChanged(double arg1);

    void on_lookUpYSpin_valueChanged(double arg1);

    void on_lookUpZSpin_valueChanged(double arg1);

    void on_action_exit_triggered();

    void on_persNearSlider_valueChanged(int value);

    void on_persFarSlider_valueChanged(int value);




    // POINT LIGHT UI
    void on_pointLightPosXSpin_valueChanged(double arg1);

    void on_pointLightPosYSpin_valueChanged(double arg1);

    void on_pointLightPosZSpin_valueChanged(double arg1);

    void on_pointLightId1Spin_valueChanged(double arg1);

    void on_pointLightId2Spin_valueChanged(double arg1);

    void on_pointLightId3Spin_valueChanged(double arg1);

    void on_pointLightIa1Spin_valueChanged(double arg1);

    void on_pointLightIa2Spin_valueChanged(double arg1);

    void on_pointLightIa3Spin_valueChanged(double arg1);

    void on_pointLightIs1Spin_valueChanged(double arg1);

    void on_pointLightIs2Spin_valueChanged(double arg1);

    void on_pointLightIs3Spin_valueChanged(double arg1);

    void on_pointLightCoefA_valueChanged(double arg1);

    void on_pointLightCoefB_valueChanged(double arg1);

    void on_pointLightCoefC_valueChanged(double arg1);

    void setPointLight();


    // SPOT LIGHT UI
    void on_spotLightPosXSpin_valueChanged(double arg1);

    void on_spotLightPosYSpin_valueChanged(double arg1);

    void on_spotLightPosZSpin_valueChanged(double arg1);

    void on_spotLightId1Spin_valueChanged(double arg1);

    void on_spotLightId2Spin_valueChanged(double arg1);

    void on_spotLightId3Spin_valueChanged(double arg1);

    void on_spotLightIa1Spin_valueChanged(double arg1);

    void on_spotLightIa2Spin_valueChanged(double arg1);

    void on_spotLightIa3Spin_valueChanged(double arg1);

    void on_spotLightIs1Spin_valueChanged(double arg1);

    void on_spotLightIs2Spin_valueChanged(double arg1);

    void on_spotLightIs3Spin_valueChanged(double arg1);

    void on_spotLightSpotDir1_valueChanged(double arg1);

    void on_spotLightSpotDir2_valueChanged(double arg1);

    void on_spotLightSpotDir3_valueChanged(double arg1);

    void on_spotLightCosCutoff_valueChanged(double arg1);

    void on_spotLightExponent_valueChanged(double arg1);

    void setSpotLight();

    // DIRECTIONAL LIGHT UI

    void on_dirLightDirXSpin_valueChanged(double arg1);

    void on_dirLightDirYSpin_valueChanged(double arg1);

    void on_dirLightDirZSpin_valueChanged(double arg1);

    void on_dirLightId1Spin_valueChanged(double arg1);

    void on_dirLightId2Spin_valueChanged(double arg1);

    void on_dirLightId3Spin_valueChanged(double arg1);

    void on_dirLightIa1Spin_valueChanged(double arg1);

    void on_dirLightIa2Spin_valueChanged(double arg1);

    void on_dirLightIa3Spin_valueChanged(double arg1);

    void on_dirLightIs1Spin_valueChanged(double arg1);

    void on_dirLightIs2Spin_valueChanged(double arg1);

    void on_dirLightIs3Spin_valueChanged(double arg1);

    void on_dirLightIntensity_valueChanged(double arg1);

    void setDirLight();


    void setObsCamera(shared_ptr<GPUCamera> cam);
    void setFrustumCamera(shared_ptr<GPUCamera> cam);

    void refreshWindow();
    void aboutMenu();


private:
    void connectShaders();

};

