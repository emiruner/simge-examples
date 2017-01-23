#include "SpinWindow.hpp"

SpinWindow::SpinWindow()
: simge::glut::Window("Spin", GLUT_DOUBLE | GLUT_RGB), spin_(true), spinAngle_(0), idleCount_(0)
{
    setSize(250, 250);
    glClearColor(0, 0, 0, 0);
    glShadeModel(GL_SMOOTH);

    simge::glut::addIdleWorker(this);
}

SpinWindow::~SpinWindow()
{
    simge::glut::removeIdleWorker(this);
}

void SpinWindow::reshapeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50, 50, -50, 50, -1, 1);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
    
void SpinWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPushMatrix();
    glRotatef(spinAngle_, 0, 0, 1);

    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0);
    glVertex2f(-25, -25);
    glColor3f(0, 1, 0);
    glVertex2f(+25, -25);
    glColor3f(1, 1, 0);
    glVertex2f(0, +25);
    glEnd();
    
    glPopMatrix();
    
    glutSwapBuffers();
}
    
void SpinWindow::spinDisplay()
{
    spinAngle_ += 1;
    
    if(spinAngle_ > 360)
    {
        spinAngle_ -= 360;
    }
    
    invalidate();
}

void SpinWindow::idle()
{
    ++idleCount_;

    if((idleCount_ % 4096) == 0)
    {
        if(spin_)
        {
            spinDisplay();
        }
    }
}

void SpinWindow::mouseGL(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        spin_ = !spin_;
    }
}

void SpinWindow::keyboardGL(unsigned char key, int x, int y)
{
    if(key == 27)
    {
        exit(0);
    }
}
