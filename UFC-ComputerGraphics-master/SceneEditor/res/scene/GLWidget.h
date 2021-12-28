/*	UNIVERSIDADE FEDERAL DO CEARA - COMPUTACAO
 *	COMPUTACAO GRAFICA 1
 *	PROFESSOR: CRETO AUGUSTO VIDAL
 *
 *	JONAS LIMA DA SILVA				344090
 *	PAULO BRUNO DE SOUSA SERAFIM	354086
*/

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>

#include <list>
#include "Object.h"
#include "LightSource.h"
#include "Camera.h"

#define SELECT_BUFFER_SIZE 4*16

class GLWidget : public QGLWidget{
	Q_OBJECT

	public:
        explicit GLWidget(QWidget *parent = 0);

        ~GLWidget();

        Object *background, *selectedObject;
        std::list<Object*> objectsList;
        LightSource *ambientLight;
        Camera *camera, *editor;

        // handle objects and background
        void newObject(Object* obj);
        void setBackground(Object* back) {if (! background != NULL) background = back; updateGL();}

        // handle widget's view rotation
        void resetDefault();
        void setAngle_x(float alfa) {angle_x = alfa; updateGL();}
        void setAngle_y(float alfa) {angle_y = alfa; updateGL();}

        // handle type of modelview and projection
        void setViewCamera(bool b) {viewCamera = b; updateGL();}
        void setPerspectiveProjection(bool b) {perspective = b; updateGL();}

        // objects tarnsformations
        void translateSelectedObject(float x, float y, float z);
        void scaleSelectedObject(float x, float y, float z);
        void rotateSelectedObject(float angle_x, float angle_y, float angle_z);
        void deleteSelectedObject();

    signals:
        // if an object was picked tells mainwindow
        void pickedObject(Object* objectpicked);

    protected:
		virtual void initializeGL();
		virtual void resizeGL(int w, int h);
        virtual void paintGL();

        virtual void mousePressEvent(QMouseEvent *event);

    private:
		GLenum renderMode;
        GLuint selectBuffer[SELECT_BUFFER_SIZE];
        QPoint position;
        float width, height;

        // widget's rotation angle
        float angle_x, angle_y;

        // if the view is the editor or camera and if
        // the projection is perspective or orthogonal
        bool viewCamera, perspective;

        void drawObjects();
		
		void startPick();
		void finishPick();
        void handlePick(GLint hits, GLuint *selectBuffer);
};

#endif // GLWIDGET_H
