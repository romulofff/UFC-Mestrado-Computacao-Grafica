/*	UNIVERSIDADE FEDERAL DO CEARA - COMPUTACAO
 *	COMPUTACAO GRAFICA 1
 *	PROFESSOR: CRETO AUGUSTO VIDAL
 *
 *	JONAS LIMA DA SILVA				344090
 *	PAULO BRUNO DE SOUSA SERAFIM	354086
*/

#include "GLWidget.h"
#include <iostream>

#ifdef __APPLE__
    #include "glu.h"
#else
    #include "GL/glu.h"
#endif

GLWidget :: GLWidget(QWidget *parent) : QGLWidget(parent)
{
    viewCamera = false;
    perspective = true;

    background = NULL;
    selectedObject = NULL;

    editor = new Camera(0.0, 2.0, 5.0,
                        0.0, 0.0, 0.0,
                        0.0, 1.0, 0.0);

    camera = new Camera(0.0, 0.0, 7.0,
                        0.0, 0.0, 0.0,
                        0.0, 1.0, 0.0);

    ambientLight = new LightSource();
}

GLWidget :: ~GLWidget()
{
}

void GLWidget :: initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glFrontFace(GL_CCW);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);

    ambientLight->setAmbient(0.8f, 0.8f, 0.8f);
    ambientLight->setDiffuse(0.8f, 0.8f, 0.8f);
    ambientLight->setSpecular(1.0f, 1.0f, 1.0f);
    ambientLight->setPosition(0.0f, 0.0f, 0.0f, 200.0f);
    ambientLight->enableLight();

    float ambient[4] = {0.8f, 0.8f, 0.8f, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
}

void GLWidget :: resizeGL(GLsizei w, GLsizei h)
{
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    width = w;
    height = h;
}

void GLWidget :: paintGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (perspective)
    {
        if (width > height) {
            glFrustum(-0.0008f*width/height, 0.0008f*width/height,
                      -0.0008f, 0.001f,
                      0.001f, 1000.0f);
        }
        else {
            glFrustum(-0.0008f, 0.0008f,
                      -0.0008f*height/width, 0.0008f*height/width,
                      0.001f, 10000.0f);
        }
    }
    else
    {
        if (width > height) {
            glOrtho(-10.0f*width/height, 10.0f*width/height,
                    -10.0f, 10.0f,
                     0.001f, 1000.0f);
        }
        else {
            glOrtho(-10.0f, 10.0f,
                    -10.0f*height/width, 10.0f*height/width,
                     0.001f, 1000.0f);
        }
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (viewCamera)
        glLoadMatrixd(camera->getMatrix());
    else
        glLoadMatrixd(editor->getMatrix());

    glRotatef(angle_x, 0.0f, 1.0f, 0.0f);
    glRotatef(angle_y, 1.0f, 0.0f, 0.0f);

    if (renderMode == GL_SELECT) 
	{
        startPick();
        drawObjects();
        finishPick();

        renderMode = GL_RENDER;
        updateGL();
    } 
	else 
        drawObjects();
}

void GLWidget :: drawObjects()
{
    // draw background
    if (background != NULL)
    {
        glPushName(background->getId());
            background->draw();
        glPopName();
    }

    // draw objects
    if ( !objectsList.empty() )
    {
        std::list<Object*> :: iterator objIt;

        for (objIt = objectsList.begin(); objIt != objectsList.end(); ++objIt)
        {
            glPushName((*objIt)->getId());
                glPushMatrix();
                    // translate objects
                    glTranslatef((*objIt)->getTranslate_x(),
                                 (*objIt)->getTranslate_y(),
                                 (*objIt)->getTranslate_z());

                    // rotate objects
                    glRotatef((*objIt)->getRotateAngleAxis_x(), 1.0, 0.0, 0.0);
                    glRotatef((*objIt)->getRotateAngleAxis_y(), 0.0, 1.0, 0.0);
                    glRotatef((*objIt)->getRotateAngleAxis_z(), 0.0, 0.0, 1.0);

                    // scale objects
                    glScalef((*objIt)->getScale_x(),
                             (*objIt)->getScale_y(),
                             (*objIt)->getScale_z());

                    (*objIt)->draw();

                glPopMatrix();
            glPopName();
        }
    }

}

void GLWidget :: mousePressEvent(QMouseEvent *event)
{
    if( event != NULL ) {
        position = event->pos();

        renderMode = GL_SELECT;
        updateGL();
    }
}

void GLWidget :: startPick()
{
    for (int i = 0; i < SELECT_BUFFER_SIZE; ++i)
        selectBuffer[i] = 0;

    GLint view[4];
    GLfloat projection[16];

    // This choose the buffer where store the values for the selection data
    glSelectBuffer(SELECT_BUFFER_SIZE, selectBuffer);

    // Switching in selecton mode
    glRenderMode(GL_SELECT);

    // Now modify the viewing volume, restricting selection area around the cursor
    glMatrixMode(GL_PROJECTION);

    // Save the current Frustum
    glGetFloatv(GL_PROJECTION_MATRIX, projection);
    glPushMatrix();

    // Load identity
    glLoadIdentity();

    // Retrieve info about the viewport
    glGetIntegerv(GL_VIEWPORT, view);

    // Get the cursor position (invert y)
    GLdouble x = position.x();
    GLdouble y = view[3] - position.y();

    gluPickMatrix(x, y, 1.0, 1.0, view);

    // Apply our projection matrix
    glMultMatrixf(projection);

    // Draw the objects onto the screen
    glMatrixMode(GL_MODELVIEW);

    // Clear the name stack
    glInitNames();
}

void GLWidget :: finishPick() {
    GLint hits;

    // Reset projection
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    // Return to GL_MODELVIEW
    glMatrixMode(GL_MODELVIEW);

    // Get number of objects drawed in that area
    // and return to render mode
    hits = glRenderMode(GL_RENDER);

    // Handle the hits
    handlePick(hits, selectBuffer);
}

void GLWidget :: handlePick(GLint hits, GLuint *_selectBuffer)
{
    // Print a list of the objects
    printf("Number of hits: %d\n", hits);

    GLuint hitId = 0;
    GLuint smallestHit = 0;

    for (int i = 0; i < hits; i++) {
        printf("====== Hit ======\n");
        printf(	/**
                 * "Number: %u\n"
                 */
                "Min Z: %u\n"
                "Max Z: %u\n"
                "Name on stack: %u\n",
                 /**
                  *_selectBuffer[(i * 4)],
                  */
                 _selectBuffer[(i * 4) + 1], // zMin
                 _selectBuffer[(i * 4) + 2],
                 _selectBuffer[(i * 4) + 3]); // name

        if (hitId == 0 || _selectBuffer[(i * 4) + 1] < smallestHit) {
            smallestHit = _selectBuffer[(i * 4) + 1];
            hitId = _selectBuffer[(i * 4) + 3];
        }
    }

    if ( hits == 0 )
    {
        emit pickedObject(NULL);
    }
    else if ( background != NULL && background->getId() == hitId)
    {
        emit pickedObject(NULL);
        printf("Background selected!\n");
    }
    else
    {
        printf("Object selected!\n");

        std::list<Object*> :: iterator objIt;

        for (objIt = objectsList.begin(); objIt != objectsList.end(); ++objIt)
        {
            if ((*objIt)->getId() == hitId)
            {

                emit pickedObject((*objIt));
                selectedObject = (*objIt);
                break;
            }
        }
    }

    printf("\n");
    fflush(stdout);
}

void GLWidget :: newObject(Object *obj)
{
    if ( obj != NULL)
    {
        objectsList.push_back(obj);
        updateGL();
    }
}

void GLWidget :: resetDefault()
{
    angle_x = 0.0f;
    angle_y = 0.0f;
}

void GLWidget :: translateSelectedObject(float x, float y, float z)
{
    selectedObject->setTranslate_x(x);
    selectedObject->setTranslate_y(y);
    selectedObject->setTranslate_z(z);

    updateGL();
}

void GLWidget :: scaleSelectedObject(float x, float y, float z)
{
    selectedObject->setScale_x(x);
    selectedObject->setScale_y(y);
    selectedObject->setScale_z(z);

    updateGL();
}

void GLWidget :: rotateSelectedObject(float angle_x, float angle_y, float angle_z)
{
    selectedObject->setRotateAngleAxis_x(angle_x);
    selectedObject->setRotateAngleAxis_y(angle_y);
    selectedObject->setRotateAngleAxis_z(angle_z);

    updateGL();
}

void GLWidget :: deleteSelectedObject()
{
    std::list<Object*> :: iterator objIt;

    for (objIt = objectsList.begin(); objIt != objectsList.end(); ++objIt)
    {
        if ((*objIt) == selectedObject)
        {
            selectedObject = NULL;
            delete (*objIt);
            objectsList.erase(objIt);

            emit pickedObject(NULL);
            break;
        }
    }
}
