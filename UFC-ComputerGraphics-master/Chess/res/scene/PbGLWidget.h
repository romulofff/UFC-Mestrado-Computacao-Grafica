// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil

#ifndef PB_GLWIDGET_H
#define PB_GLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>

#include "PbObject.h"
#include "PbLightSource.h"
#include "PbCamera.h"

class PbGLWidget : public QGLWidget{
	Q_OBJECT

	public:
        explicit PbGLWidget(QWidget *parent = 0);

        ~PbGLWidget();

        float vectorsSize;

        PbObject *chessboardBase, *chessFace1, *chessFace2, *pawn;
        PbLightSource *light0;

        PbCamera *player1camera, *player2camera, *crowdCamera, *pawnCamera;
        bool setPlayer1camera, setPlayer2camera, setCrowdCamera, setPawnCamera;
        bool setNormals, setVectorsL, setVectorsR, setVectorsV;

	protected:
		virtual void initializeGL();
		virtual void resizeGL(int w, int h);
        virtual void paintGL();

    private:
        void drawObjects();
        void drawLightVectors();
};

#endif // PB_GLWIDGET_H
