#include "basicopenglview.h"
#include <cmath>
#include <QMouseEvent>
#define pi 3.1415926535897932384626433832795

BasicOpenGLView::BasicOpenGLView(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
    projectionMatrix(),
    viewMatrix(),
    curMouseIntersection(),
    herd(10)
{

}

void BasicOpenGLView::setNumberFlocks(int m_NumFlocks)
{
    herd.resize(m_NumFlocks);
}

void BasicOpenGLView::initializeGL()
{
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    setMouseTracking(true);


    glPointSize(5.0);
}

void BasicOpenGLView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    viewMatrix.setToIdentity();
    viewMatrix.lookAt(QVector3D(0.0f, 0.0f, 100.0f),
                      QVector3D(0.0f, 0.1f, 0.0f),
                      QVector3D(0.0f, 1.0f, 0.0f));
    glLoadMatrixd(viewMatrix.data());
    glColor3f(0.1, 0.1, 0.1);
    glBegin(GL_POLYGON);
    glVertex3f(-70,-60,70);
    glVertex3f(-70,-60,-70);
    glVertex3f(70,-60,-70);
    glVertex3f(70,-60,70);
    glEnd();
    glColor3f(0.11, 0.1, 0.1);
    glBegin(GL_POLYGON);
    glVertex3f(-70,-60,70);
    glVertex3f(-70,-60,-70);
    glVertex3f(-70,60,-70);
    glVertex3f(-70,60,70);
    glEnd();
    glColor3f(0.11, 0.1, 0.1);
    glBegin(GL_POLYGON);
    glVertex3f(70,-60,70);
    glVertex3f(70,-60,-70);
    glVertex3f(70,60,-70);
    glVertex3f(70,60,70);
    glEnd();
    //left side
    herd.rules(0.02f);
    herd.animate(0.02f);
    herd.draw();

}

void BasicOpenGLView::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(60.0f, (float)width/(float)height, 0.01f, 500.0f);
    glLoadMatrixd(projectionMatrix.data());

    glMatrixMode(GL_MODELVIEW);
    double viewport[4];
    glGetDoublev(GL_VIEWPORT, viewport);
}

void BasicOpenGLView::mousePressEvent(QMouseEvent *event)
{
    herd.setLeader();
}

void BasicOpenGLView::mouseMoveEvent(QMouseEvent *event)
{
    float eventX = (float)event->x() / width();
    float eventY = 1.0f - (float) event->y() / height();

    eventX -= 0.5f;
    eventY -= 0.5f;
    eventX *= 2.0f;
    eventY *= 2.0f;

    QVector3D rayStart(eventX, eventY, 0.0f);
    QVector3D rayEnd(eventX, eventY, 1.0f);

    QMatrix4x4 viewProjection = projectionMatrix * viewMatrix;
    QMatrix4x4 inverseViewProjection = viewProjection.inverted();
    QVector3D worldStart = inverseViewProjection * rayStart;
    QVector3D worldEnd = inverseViewProjection * rayEnd;

    QVector3D rayDir = worldEnd - worldStart;
    rayDir.normalize();

    // the plane in XY, at 0,0,0
    QVector3D normal(0.0f, 0.0f, 1.0f);
    float d = 0;

    // intersection routine of plane with ray
    float denom = QVector3D::dotProduct(normal, rayDir);
    float s = QVector3D::dotProduct(normal, worldStart) + d;


    if (fabs(denom) < std::numeric_limits<float>::epsilon())
    {
        if (fabs(s) < std::numeric_limits<float>::epsilon())
        {
            curMouseIntersection = worldStart;
            return;
        }
        else
        {
            return;
        }
    }

    float t = s / (-denom);
    curMouseIntersection = worldStart + rayDir * t;
}
