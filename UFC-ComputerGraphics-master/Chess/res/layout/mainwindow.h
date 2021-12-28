#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "PbGLWidget.h"

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
        void updateView();
        void updateCamera();
        void updateVisible();
        void updateLightVectors();
        void normalSize(int size);

    private:
        Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
