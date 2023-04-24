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

    void on_lightPosXSpin_valueChanged(double arg1);

    void on_lightPosYSpin_valueChanged(double arg1);

    void on_lightPosZSpin_valueChanged(double arg1);

    void on_action_exit_triggered();

    void on_persNearSlider_valueChanged(int value);

    void on_persFarSlider_valueChanged(int value);

    void on_lightId1Spin_valueChanged(double arg1);

    void on_lightId2Spin_valueChanged(double arg1);

    void on_lightId3Spin_valueChanged(double arg1);

    void on_lightIa1Spin_valueChanged(double arg1);

    void on_lightIa2Spin_valueChanged(double arg1);

    void on_lightIa3Spin_valueChanged(double arg1);

    void on_lightIs1Spin_valueChanged(double arg1);

    void on_lightIs2Spin_valueChanged(double arg1);

    void on_lightIs3Spin_valueChanged(double arg1);

    void setObsCamera(shared_ptr<GPUCamera> cam);
    void setFrustumCamera(shared_ptr<GPUCamera> cam);

    void refreshWindow();
    void aboutMenu();


private:
    void connectShaders();

};

