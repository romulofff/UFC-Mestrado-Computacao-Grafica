/*	UNIVERSIDADE FEDERAL DO CEARA - COMPUTACAO
 *	COMPUTACAO GRAFICA 1
 *	PROFESSOR: CRETO AUGUSTO VIDAL
 *
 *	JONAS LIMA DA SILVA				344090
 *	PAULO BRUNO DE SOUSA SERAFIM	354086
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QSpinBox>
#include <sstream>

unsigned int MainWindow :: currentImage = 1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // implements zoom
    ui->verticalScrollBarZoom->setValue(ui->widgetScene->editor->getEye_z()*100);

    setupInitPosition();
    setupInitTransformations();

    // menu file
    connect(ui->actionScreenshot, SIGNAL(triggered()), this, SLOT(screenshot()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));

    // menu edit
    connect(ui->actionLoadObject, SIGNAL(triggered()), this, SLOT(loadObject()));
    connect(ui->actionLoadBackground, SIGNAL(triggered()), this, SLOT(loadBackground()));
    connect(ui->actionTranslatePickedObject, SIGNAL(triggered()), this, SLOT(translatePickedObject()));
    connect(ui->actionScalePickedObject, SIGNAL(triggered()), this, SLOT(scalePickedObject()));
    connect(ui->actionRotatePickedObject, SIGNAL(triggered()), this, SLOT(rotatePickedObject()));
    connect(ui->actionEditPositionCamera, SIGNAL(triggered()), this, SLOT(editCameraPosition()));
    connect(ui->actionDeletePickedObject, SIGNAL(triggered()), this, SLOT(deletePickedObject()));

    // menu help
    connect(ui->actionAboutHelp, SIGNAL(triggered()), this, SLOT(showAbout()));
    connect(ui->actionContentsHelp, SIGNAL(triggered()), this, SLOT(showContents()));

    // central widget
    connect(ui->pushButtonDefault, SIGNAL(clicked()), this, SLOT(resetDefaults()));
    connect(ui->horizontalSliderRotate, SIGNAL(valueChanged(int)), this, SLOT(rotateAngle_x(int)));
    connect(ui->verticalSliderRotate, SIGNAL(valueChanged(int)), this, SLOT(rotateAngle_y(int)));
    connect(ui->verticalScrollBarZoom, SIGNAL(valueChanged(int)), this, SLOT(updateZoom(int)));

    connect(ui->radioButtonCamera, SIGNAL(clicked()), this, SLOT(updateView()));
    connect(ui->radioButtonEditor, SIGNAL(clicked()), this, SLOT(updateView()));

    connect(ui->radioButtonOrthographic, SIGNAL(clicked()), this, SLOT(updateProjection()));
    connect(ui->radioButtonPerspective, SIGNAL(clicked()), this, SLOT(updateProjection()));

    // opengl widget
    connect(ui->widgetScene, SIGNAL(pickedObject(Object*)), this, SLOT(updatePickedObject(Object*)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rotateAngle_x(int theta)
{
    ui->widgetScene->setAngle_x(theta*10);
}

void MainWindow::rotateAngle_y(int theta)
{
    ui->widgetScene->setAngle_y(theta*10);
}

void MainWindow :: updateView()
{
    if (ui->radioButtonCamera->isChecked())
    {
        ui->widgetScene->setViewCamera(true);

        rotateAngle_x(0);
        rotateAngle_y(0);

        ui->horizontalSliderRotate->setEnabled(false);
        ui->verticalSliderRotate->setEnabled(false);
        ui->pushButtonDefault->setEnabled(false);
        ui->actionEditPositionCamera->setEnabled(true);
        ui->menuCamera->setEnabled(true);
    }
    else
    {
        ui->widgetScene->setViewCamera(false);

        rotateAngle_x(ui->horizontalSliderRotate->value());
        rotateAngle_y(ui->verticalSliderRotate->value());

        ui->horizontalSliderRotate->setEnabled(true);
        ui->verticalSliderRotate->setEnabled(true);
        ui->pushButtonDefault->setEnabled(true);
        ui->actionEditPositionCamera->setEnabled(false);
        ui->menuCamera->setEnabled(true);
    }
}

void MainWindow :: updateProjection()
{
    if (ui->radioButtonPerspective->isChecked())
        ui->widgetScene->setPerspectiveProjection(true);
    else
        ui->widgetScene->setPerspectiveProjection(false);
}

void MainWindow :: updateZoom(int dz)
{
    ui->widgetScene->editor->updateEye(ui->widgetScene->editor->getEye_x(),
                                       ui->widgetScene->editor->getEye_y(),
                                       (float)dz/100.0f);
    ui->widgetScene->updateGL();
}
void MainWindow :: resetDefaults()
{
    ui->widgetScene->resetDefault();
    ui->horizontalSliderRotate->setValue(0);
    ui->verticalSliderRotate->setValue(0);
}

void MainWindow :: screenshot()
{
    std::stringstream filename;
    filename << "sceneEditor00" << currentImage << ".png";

    QString name = QString::fromStdString(filename.str());

    ui->widgetScene->setViewCamera(true);
    ui->radioButtonCamera->setChecked(true);
    ui->radioButtonEditor->setChecked(false);

    QImage screenImage = ui->widgetScene->grabFrameBuffer();
    screenImage.save(name, "png");

    ++currentImage;
}

void MainWindow :: loadObject()
{
    QString qpath = QFileDialog::getOpenFileName(this, "Select an object", "../../assets/", "Wavefront .obj (*.obj)", 0, QFileDialog::DontUseNativeDialog);

    if( !qpath.isEmpty() ) {

        std::string path = qpath.toUtf8().constData();

        ui->widgetScene->newObject(new Object(path.c_str()));
    }
    else
        ui->widgetScene->newObject(NULL);
}

void MainWindow::loadBackground()
{
    QString qpath = QFileDialog::getOpenFileName(this, "Select an background", "../../assets/", "Wavefront .obj (*.obj)", 0, QFileDialog::DontUseNativeDialog);

    if( !qpath.isEmpty() ) {

        std::string path = qpath.toUtf8().constData();

        ui->widgetScene->setBackground(new Object(path.c_str()));
    }
    else
        ui->widgetScene->setBackground(NULL);
}

void MainWindow::updatePickedObject(Object* obj)
{
    if (obj != NULL)
    {
        ui->labelPickedObject->setText(obj->getName().c_str());
        ui->labelPickedObject->setEnabled(true);

        ui->menuPickedObject->setEnabled(true);
        ui->actionTranslatePickedObject->setEnabled(true);
        ui->actionScalePickedObject->setEnabled(true);
        ui->actionRotatePickedObject->setEnabled(true);
        ui->actionDeletePickedObject->setEnabled(true);
    }
    else
    {
        ui->labelPickedObject->setText("No object selected");
        ui->labelPickedObject->setEnabled(false);

        ui->menuPickedObject->setEnabled(false);
        ui->actionTranslatePickedObject->setEnabled(false);
        ui->actionScalePickedObject->setEnabled(false);
        ui->actionRotatePickedObject->setEnabled(false);
        ui->actionDeletePickedObject->setEnabled(false);
    }
}

void MainWindow :: translatePickedObject()
{
    QWidget *widgetTranslateObject = new QWidget;
    QGroupBox *groupBoxTranslate = new QGroupBox(tr("Translate"));
    QPushButton *okButton = new QPushButton("Ok");
    okButton->setMaximumWidth(80);

    doubleSpinBoxTranslateX->setValue(ui->widgetScene->selectedObject->getTranslate_x());
    doubleSpinBoxTranslateY->setValue(ui->widgetScene->selectedObject->getTranslate_y());
    doubleSpinBoxTranslateZ->setValue(ui->widgetScene->selectedObject->getTranslate_z());

    QGridLayout *gridTranslate = new QGridLayout;
    gridTranslate->addWidget(new QLabel("Translate X"), 0, 0);
    gridTranslate->addWidget(doubleSpinBoxTranslateX, 1, 0);
    gridTranslate->addWidget(new QLabel("Translate Y"), 0, 1);
    gridTranslate->addWidget(doubleSpinBoxTranslateY, 1, 1);
    gridTranslate->addWidget(new QLabel("Translate Z"), 0, 2);
    gridTranslate->addWidget(doubleSpinBoxTranslateZ, 1, 2);
    groupBoxTranslate->setLayout(gridTranslate);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(groupBoxTranslate);
    vbox->addWidget(okButton);
    widgetTranslateObject->setLayout(vbox);

    widgetTranslateObject->setWindowTitle(tr("Translate Selected Object"));
    widgetTranslateObject->show();

    connect(doubleSpinBoxTranslateX, SIGNAL(valueChanged(double)), this, SLOT(translateObject()));
    connect(doubleSpinBoxTranslateY, SIGNAL(valueChanged(double)), this, SLOT(translateObject()));
    connect(doubleSpinBoxTranslateZ, SIGNAL(valueChanged(double)), this, SLOT(translateObject()));
    connect(okButton, SIGNAL(clicked()), widgetTranslateObject, SLOT(close()));
}

void MainWindow :: translateObject()
{
    ui->widgetScene->translateSelectedObject(doubleSpinBoxTranslateX->value(),
                                             doubleSpinBoxTranslateY->value(),
                                             doubleSpinBoxTranslateZ->value());
}

void MainWindow :: scalePickedObject()
{
    QWidget *widgetScaleObject = new QWidget;
    QGroupBox *groupBoxScale = new QGroupBox(tr("Scale"));
    QPushButton *okButton = new QPushButton("Ok");
    okButton->setMaximumWidth(80);

    doubleSpinBoxScaleX->setValue(ui->widgetScene->selectedObject->getScale_x());
    doubleSpinBoxScaleY->setValue(ui->widgetScene->selectedObject->getScale_y());
    doubleSpinBoxScaleZ->setValue(ui->widgetScene->selectedObject->getScale_z());

    QGridLayout *gridScale = new QGridLayout;
    gridScale->addWidget(new QLabel("Scale X"), 0, 0);
    gridScale->addWidget(doubleSpinBoxScaleX, 1, 0);
    gridScale->addWidget(new QLabel("Scale Y"), 0, 1);
    gridScale->addWidget(doubleSpinBoxScaleY, 1, 1);
    gridScale->addWidget(new QLabel("Scale Z"), 0, 2);
    gridScale->addWidget(doubleSpinBoxScaleZ, 1, 2);
    groupBoxScale->setLayout(gridScale);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(groupBoxScale);
    vbox->addWidget(okButton);
    widgetScaleObject->setLayout(vbox);

    widgetScaleObject->setWindowTitle(tr("Scale Selected Object"));
    widgetScaleObject->show();

    connect(doubleSpinBoxScaleX, SIGNAL(valueChanged(double)), this, SLOT(scaleObject()));
    connect(doubleSpinBoxScaleY, SIGNAL(valueChanged(double)), this, SLOT(scaleObject()));
    connect(doubleSpinBoxScaleZ, SIGNAL(valueChanged(double)), this, SLOT(scaleObject()));
    connect(okButton, SIGNAL(clicked()), widgetScaleObject, SLOT(close()));
}

void MainWindow :: scaleObject()
{
    ui->widgetScene->scaleSelectedObject(doubleSpinBoxScaleX->value(),
                                         doubleSpinBoxScaleY->value(),
                                         doubleSpinBoxScaleZ->value());
}

void MainWindow :: rotatePickedObject()
{
    QWidget *widgetRotateObject = new QWidget;
    QGroupBox *groupBoxRotate = new QGroupBox(tr("Rotate"));
    QPushButton *okButton = new QPushButton("Ok");
    okButton->setMaximumWidth(80);

    doubleSpinBoxRotateX->setValue(ui->widgetScene->selectedObject->getRotateAngleAxis_x());
    doubleSpinBoxRotateY->setValue(ui->widgetScene->selectedObject->getRotateAngleAxis_y());
    doubleSpinBoxRotateZ->setValue(ui->widgetScene->selectedObject->getRotateAngleAxis_z());

    QGridLayout *gridRotate = new QGridLayout;
    gridRotate->addWidget(new QLabel("Rotate X"), 0, 0);
    gridRotate->addWidget(doubleSpinBoxRotateX, 1, 0);
    gridRotate->addWidget(new QLabel("Rotate Y"), 0, 1);
    gridRotate->addWidget(doubleSpinBoxRotateY, 1, 1);
    gridRotate->addWidget(new QLabel("Rotate Z"), 0, 2);
    gridRotate->addWidget(doubleSpinBoxRotateZ, 1, 2);
    groupBoxRotate->setLayout(gridRotate);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(groupBoxRotate);
    vbox->addWidget(okButton);
    widgetRotateObject->setLayout(vbox);

    widgetRotateObject->setWindowTitle(tr("Rotate Selected Object"));
    widgetRotateObject->show();

    connect(doubleSpinBoxRotateX, SIGNAL(valueChanged(double)), this, SLOT(rotateObject()));
    connect(doubleSpinBoxRotateY, SIGNAL(valueChanged(double)), this, SLOT(rotateObject()));
    connect(doubleSpinBoxRotateZ, SIGNAL(valueChanged(double)), this, SLOT(rotateObject()));
    connect(okButton, SIGNAL(clicked()), widgetRotateObject, SLOT(close()));
}

void MainWindow :: rotateObject()
{
    ui->widgetScene->rotateSelectedObject(doubleSpinBoxRotateX->value(),
                                          doubleSpinBoxRotateY->value(),
                                          doubleSpinBoxRotateZ->value());
}

void MainWindow :: deletePickedObject()
{
    ui->widgetScene->deleteSelectedObject();
}

void MainWindow :: editCameraPosition()
{
    QWidget *widgetCamera = new QWidget;

    QPushButton *okButton = new QPushButton("Ok");
    okButton->setMaximumWidth(80);

    QGroupBox *groupBoxEye = new QGroupBox(tr("Eye"));
    QGroupBox *groupBoxLookAt = new QGroupBox(tr("Look At"));
    QGroupBox *groupBoxViewUp = new QGroupBox(tr("View Up"));

    QGridLayout *gridEye = new QGridLayout;
    gridEye->addWidget(new QLabel("Eye X"), 0, 0);
    gridEye->addWidget(eyeX, 1, 0);
    gridEye->addWidget(new QLabel("Eye Y"), 0, 1);
    gridEye->addWidget(eyeY, 1, 1);
    gridEye->addWidget(new QLabel("Eye Z"), 0, 2);
    gridEye->addWidget(eyeZ, 1, 2);
    groupBoxEye->setLayout(gridEye);

    QGridLayout *gridLookAt = new QGridLayout;
    gridLookAt->addWidget(new QLabel("Look At X"), 0, 0);
    gridLookAt->addWidget(lookAtX, 1, 0);
    gridLookAt->addWidget(new QLabel("Look At Y"), 0, 1);
    gridLookAt->addWidget(lookAtY, 1, 1);
    gridLookAt->addWidget(new QLabel("Look At Z"), 0, 2);
    gridLookAt->addWidget(lookAtZ, 1, 2);
    groupBoxLookAt->setLayout(gridLookAt);

    QGridLayout *gridViewUp = new QGridLayout;
    gridViewUp->addWidget(new QLabel("View Up X"), 0, 0);
    gridViewUp->addWidget(viewUpX, 1, 0);
    gridViewUp->addWidget(new QLabel("View Up Y"), 0, 1);
    gridViewUp->addWidget(viewUpY, 1, 1);
    gridViewUp->addWidget(new QLabel("View Up Z"), 0, 2);
    gridViewUp->addWidget(viewUpZ, 1, 2);
    groupBoxViewUp->setLayout(gridViewUp);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(groupBoxEye);
    vbox->addWidget(groupBoxLookAt);
    vbox->addWidget(groupBoxViewUp);
    vbox->addWidget(okButton);
    widgetCamera->setLayout(vbox);

    widgetCamera->setWindowTitle(tr("Camera"));
    widgetCamera->show();

    connect(eyeX, SIGNAL(valueChanged(double)), this, SLOT(updateCamera()));
    connect(eyeY, SIGNAL(valueChanged(double)), this, SLOT(updateCamera()));
    connect(eyeZ, SIGNAL(valueChanged(double)), this, SLOT(updateCamera()));
    connect(lookAtX, SIGNAL(valueChanged(double)), this, SLOT(updateCamera()));
    connect(lookAtY, SIGNAL(valueChanged(double)), this, SLOT(updateCamera()));
    connect(lookAtZ, SIGNAL(valueChanged(double)), this, SLOT(updateCamera()));
    connect(viewUpX, SIGNAL(valueChanged(double)), this, SLOT(updateCamera()));
    connect(viewUpY, SIGNAL(valueChanged(double)), this, SLOT(updateCamera()));
    connect(viewUpZ, SIGNAL(valueChanged(double)), this, SLOT(updateCamera()));
    connect(okButton, SIGNAL(clicked()), widgetCamera, SLOT(close()));
}

void MainWindow :: updateCamera()
{
    ui->widgetScene->camera->updateEye(eyeX->value(), eyeY->value(), eyeZ->value());
    ui->widgetScene->camera->updateLookAt(lookAtX->value(), lookAtY->value(), lookAtZ->value());
    ui->widgetScene->camera->updateViewUp(viewUpX->value(), viewUpY->value(), viewUpZ->value());
    ui->widgetScene->updateGL();
}

void MainWindow :: showAbout()
{
    std::stringstream text;
    text << "Desenvolvido por Jonas Lima da Silva e Paulo Bruno de Sousa Serafim\n\n"
         << "Esse software compreende um trabalho escolar e todos os recursos aqui presentes "
         << "foram utilizados com proposito exclusivamente educacional.\n\n"
         << "Nao copiar, distribuir ou expor sem os devidos creditos.\n"
         << "Este software nao pode ser comercializado sob nenhuma hipotese.\n\n"
         << "Fortaleza, Universidade Federal do Ceara, 2013.";

    QString about = QString::fromStdString(text.str());

    QMessageBox help;
    help.about(this, "About", about);
}

void MainWindow::showContents()
{
    std::stringstream text;
    text << "Screenshot: takes a screenshot by the camera view\n\n"
         << "Load Object: load an editable WavefrontTM .obj\n\n"
         << "Load Background: load an non-editable WavefrontTM .obj\n\n"
         << "Picked Object: apply transformations\n\n"
         << "Camera: edit position of the camera";

    QString contents = QString::fromStdString(text.str());

    QMessageBox help;

    help.setText(contents);
    help.setWindowTitle("Contents");
    help.exec();
}

void MainWindow :: setupInitPosition()
{
    const double singleStep = 0.2;
    const double range = 200;

    eyeX = new QDoubleSpinBox;
    eyeY = new QDoubleSpinBox;
    eyeZ = new QDoubleSpinBox;

    lookAtX = new QDoubleSpinBox;
    lookAtY = new QDoubleSpinBox;
    lookAtZ = new QDoubleSpinBox;

    viewUpX = new QDoubleSpinBox;
    viewUpY = new QDoubleSpinBox;
    viewUpZ = new QDoubleSpinBox;

    eyeX->setRange(-range, range);
    eyeX->setSingleStep(singleStep);
    eyeX->setValue(ui->widgetScene->camera->getEye_x());

    eyeY->setRange(-range, range);
    eyeY->setSingleStep(singleStep);
    eyeY->setValue(ui->widgetScene->camera->getEye_y());

    eyeZ->setRange(-range, range);
    eyeZ->setSingleStep(singleStep);
    eyeZ->setValue(ui->widgetScene->camera->getEye_z());

    lookAtX->setRange(-range, range);
    lookAtX->setSingleStep(singleStep);
    lookAtX->setValue(ui->widgetScene->camera->getLookAt_x());

    lookAtY->setRange(-range, range);
    lookAtY->setSingleStep(singleStep);
    lookAtY->setValue(ui->widgetScene->camera->getLookAt_y());

    lookAtZ->setRange(-range, range);
    lookAtZ->setSingleStep(singleStep);
    lookAtZ->setValue(ui->widgetScene->camera->getLookAt_z());

    viewUpX->setRange(-range, range);
    viewUpX->setSingleStep(singleStep);
    viewUpX->setValue(ui->widgetScene->camera->getViewUp_x());

    viewUpY->setRange(-range, range);
    viewUpY->setSingleStep(singleStep);
    viewUpY->setValue(ui->widgetScene->camera->getViewUp_y());

    viewUpZ->setRange(-range, range);
    viewUpZ->setSingleStep(singleStep);
    viewUpZ->setValue(ui->widgetScene->camera->getViewUp_z());
}

void MainWindow :: setupInitTransformations()
{
    const double singleStep = 0.05;
    const double range = 200;
    const double rotateRange = 360;

    doubleSpinBoxTranslateX = new QDoubleSpinBox;
    doubleSpinBoxTranslateY = new QDoubleSpinBox;
    doubleSpinBoxTranslateZ = new QDoubleSpinBox;

    doubleSpinBoxScaleX = new QDoubleSpinBox;
    doubleSpinBoxScaleY = new QDoubleSpinBox;
    doubleSpinBoxScaleZ = new QDoubleSpinBox;

    doubleSpinBoxRotateX = new QDoubleSpinBox;
    doubleSpinBoxRotateY = new QDoubleSpinBox;
    doubleSpinBoxRotateZ = new QDoubleSpinBox;

    doubleSpinBoxTranslateX->setRange(-range, range);
    doubleSpinBoxTranslateX->setSingleStep(singleStep);
    doubleSpinBoxTranslateY->setRange(-range, range);
    doubleSpinBoxTranslateY->setSingleStep(singleStep);
    doubleSpinBoxTranslateZ->setRange(-range, range);
    doubleSpinBoxTranslateZ->setSingleStep(singleStep);

    doubleSpinBoxScaleX->setRange(0.0, range);
    doubleSpinBoxScaleX->setSingleStep(singleStep);
    doubleSpinBoxScaleY->setRange(0.0, range);
    doubleSpinBoxScaleY->setSingleStep(singleStep);
    doubleSpinBoxScaleZ->setRange(0.0, range);
    doubleSpinBoxScaleZ->setSingleStep(singleStep);

    doubleSpinBoxRotateX->setRange(-rotateRange, rotateRange);
    doubleSpinBoxRotateX->setSingleStep(1.0);
    doubleSpinBoxRotateY->setRange(-rotateRange, rotateRange);
    doubleSpinBoxRotateY->setSingleStep(1.0);
    doubleSpinBoxRotateZ->setRange(-rotateRange, rotateRange);
    doubleSpinBoxRotateZ->setSingleStep(1.0);
}
