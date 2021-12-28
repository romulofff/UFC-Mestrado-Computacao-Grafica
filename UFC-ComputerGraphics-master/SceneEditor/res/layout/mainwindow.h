/*	UNIVERSIDADE FEDERAL DO CEARA - COMPUTACAO
 *	COMPUTACAO GRAFICA 1
 *	PROFESSOR: CRETO AUGUSTO VIDAL
 *
 *	JONAS LIMA DA SILVA				344090
 *	PAULO BRUNO DE SOUSA SERAFIM	354086
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>

#include "Object.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
public slots:

    // central widget
    void rotateAngle_x(int theta);
    void rotateAngle_y(int theta);

    void updateView();
    void updateProjection();
    void updateZoom(int dz);

    void resetDefaults();

    // menu file
    void screenshot();

    // menu edit
    void loadObject();
    void loadBackground();

    void updatePickedObject(Object* obj);

    void translatePickedObject();
    void translateObject();

    void scalePickedObject();
    void scaleObject();

    void rotatePickedObject();
    void rotateObject();

    void deletePickedObject();

    void editCameraPosition();
    void updateCamera();

    // menu help
    void showAbout();
    void showContents();


private:
    Ui::MainWindow *ui;

    QDoubleSpinBox *eyeX;
    QDoubleSpinBox *eyeY;
    QDoubleSpinBox *eyeZ;

    QDoubleSpinBox *lookAtX;
    QDoubleSpinBox *lookAtY;
    QDoubleSpinBox *lookAtZ;

    QDoubleSpinBox *viewUpX;
    QDoubleSpinBox *viewUpY;
    QDoubleSpinBox *viewUpZ;

    QDoubleSpinBox *doubleSpinBoxTranslateX;
    QDoubleSpinBox *doubleSpinBoxTranslateY;
    QDoubleSpinBox *doubleSpinBoxTranslateZ;

    QDoubleSpinBox *doubleSpinBoxScaleX;
    QDoubleSpinBox *doubleSpinBoxScaleY;
    QDoubleSpinBox *doubleSpinBoxScaleZ;

    QDoubleSpinBox *doubleSpinBoxRotateX;
    QDoubleSpinBox *doubleSpinBoxRotateY;
    QDoubleSpinBox *doubleSpinBoxRotateZ;

    // initializes the QDoubleSpinBox'es created
    void setupInitPosition();
    void setupInitTransformations();

    // current quantity of screenshots
    static unsigned int currentImage;

};

#endif // MAINWINDOW_H
