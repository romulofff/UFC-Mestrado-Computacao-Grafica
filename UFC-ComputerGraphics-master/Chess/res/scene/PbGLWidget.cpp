// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil

#include "PbGLWidget.h"

#ifdef __APPLE__
    #include "glu.h"
#else
    #include "GL/glu.h"
#endif

PbGLWidget :: PbGLWidget(QWidget *parent) : QGLWidget(parent)
{
    vectorsSize = 1.0f;

    setNormals = false;
    setVectorsL = false;
    setVectorsR = false;
    setVectorsV = false;

    pawn = new PbObject("../../assets/pawn.obj");
    chessboardBase = new PbObject("../../assets/chessboardBase.obj");
    chessFace1 = new PbObject("../../assets/chessboardFace1.obj");
    chessFace2 = new PbObject("../../assets/chessboardFace2.obj");

    light0 = new PbLightSource();

    player1camera = new PbCamera(0.0, -8.0, 8.0, 0.0, 0.0, 0.0);
    player2camera = new PbCamera(0.0, 8.0, 8.0, 0.0, 0.0, 0.0);
    crowdCamera = new PbCamera(-8.0, 0.0, 8.0, 0.0, 0.0, 0.0);
    pawnCamera = new PbCamera(-1.5, -2.25, 1.75, -1.5, -1.25, 1.75);
}

PbGLWidget :: ~PbGLWidget()
{
    delete pawn;
    delete chessboardBase;
    delete chessFace1;
    delete chessFace2;

    delete light0;

    delete player1camera;
    delete player2camera;
    delete crowdCamera;
    delete pawnCamera;
}

void PbGLWidget :: initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glFrontFace(GL_CCW);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHTING);

    light0->setAmbient(0.1f, 0.1f, 0.1f);
    light0->setDiffuse(0.1f, 0.1f, 0.1f);
    light0->setSpecular(1.0f, 1.0f, 1.0f);
    light0->setPosition(-2.0f, 0.0f, 2.0f, 0.0f);
    light0->enableLight();
}

void PbGLWidget :: resizeGL(GLsizei w, GLsizei h)
{
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w > h) {
        glFrustum(-0.0008f*(float)w/(float)h, 0.0008f*(float)w/(float)h,
                  -0.0008f, 0.001f,
                  0.001f, 30.0f);
    }
    else {
        glFrustum(-0.0008f, 0.0008f,
                  -0.0008f*(float)h/(float)w, 0.0008f*(float)h/(float)w,
                  0.001f, 30.0f);
    }
}


void PbGLWidget :: paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    if (setPlayer1camera) {
        glLoadMatrixd(player1camera->getMatrix());
    }
    else if (setPlayer2camera) {
        glLoadMatrixd(player2camera->getMatrix());
    }
    else if (setPawnCamera) {
        glLoadMatrixd(pawnCamera->getMatrix());
    }
    else if (setCrowdCamera) {
        glLoadMatrixd(crowdCamera->getMatrix());
    }
    else
        glLoadIdentity();

    drawObjects();
    drawLightVectors();
}

void PbGLWidget :: drawObjects()
{
    if (pawn->getDrawable())
    {
        glPushMatrix();
            glTranslatef(-1.5f, -2.5f, 0.0f);
            pawn->draw();
        glPopMatrix();
    }
    if (chessboardBase->getDrawable()) chessboardBase->draw();
    if (chessFace1->getDrawable()) chessFace1->draw();
    if (chessFace2->getDrawable()) chessFace2->draw();
}

void PbGLWidget :: drawLightVectors()
{
    // draw normals
    if (setNormals)
    {
        if (pawn->getDrawable())
        {
            glPushMatrix();
                glTranslatef(-1.5f, -2.5f, 0.0f);
                pawn->drawVerticesNormals(vectorsSize);
            glPopMatrix();
        }

        if (chessboardBase->getDrawable())
            chessboardBase->drawVerticesNormals(vectorsSize);

        if (chessFace1->getDrawable())
            chessFace1->drawVerticesNormals(vectorsSize);

        if (chessFace2->getDrawable())
            chessFace2->drawVerticesNormals(vectorsSize);
    }
}
