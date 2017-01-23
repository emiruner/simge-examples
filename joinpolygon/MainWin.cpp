#include "MainWin.hpp"

#include <algorithm>
#include <simge/util/Utility.hpp>

#include "JoinPolygon.hpp"

using namespace simge::geom;
using namespace simge::glut;
using namespace simge::util;

namespace
{

inline void writeMsg(char const* msg)
{
    glColor3f(1, 0, 0);
    drawText(GLUT_BITMAP_8_BY_13, point(10, 10), msg);
}

} // namespace <unnamed>

MainWin::MainWin()
: Planar("Join Polygons", GLUT_RGBA | GLUT_DOUBLE),
  subject_(PolygonType::RightIsInterior()), clip_(PolygonType::LeftIsInterior()),
  joined_(PolygonType::LeftIsInterior()), state_(InputState::EnteringSubject())
{
    glClearColor(0, 0, 0, 0);
    glColor3f(1, 0, 0);
    setSize(620, 460);
}

void MainWin::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(2);

    if(state_ == InputState::EnteringSubject()) 
    {
        glColor3f(1, 0, 0);
        drawLineLoop(subject_);
        writeMsg("Enter first polygon clockwise. Finish by clicking right mouse button.");
    }

    if(state_ == InputState::EnteringClip())
    {
        glColor3f(1, 0, 0);
        drawLineLoop(subject_);
        glColor3f(0.3, 1, 0.3);
        drawLineLoop(clip_);    
        writeMsg("Enter second polgon clockwise. Finish by clicking right mouse button.");
    }
    
    if(state_ == InputState::Display())
    {
        glColor3f(1, 0, 0);
        drawLineLoop(subject_);
        glColor3f(0.3, 1, 0.3);
        drawLineLoop(clip_);    
        glLineWidth(4);
        glColor3f(0.9, 1, 1);
        drawLineLoop(joined_);
        writeMsg("Press `n' to start from beginning.");
    }

    
    // Status line
    glLineWidth(3);
    glColor3f(0.4, 0.7, 0.2);
    glBegin(GL_LINES);
    glVertex2i(0, 30);
    glVertex2i(getWidth(), 30);
    glEnd();
    glLineWidth(1);

    glFlush();
    glutSwapBuffers();
}

void MainWin::mouseGL(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN)
    {        
        if(button == GLUT_LEFT_BUTTON)
        {
            if(state_ == InputState::EnteringSubject())
            {
                subject_.addVertex(windowToGl(x, y));
                invalidate();
            }
            else if(state_ == InputState::EnteringClip())
            {
                clip_.addVertex(windowToGl(x, y));
                invalidate();
            }
        }
        else if(button == GLUT_RIGHT_BUTTON)
        {
            if(state_ == InputState::EnteringSubject())
            {
                state_ = InputState::EnteringClip();
                invalidate();
            }
            else if(state_ == InputState::EnteringClip())
            {
                state_ = InputState::Display();
                joined_ = join(subject_, clip_);
                invalidate();
            }
        }
    }
}

void MainWin::keyboardGL(unsigned char key, int x, int y)
{
    if(key == 'n' || key == 'N')
    {
        if(state_ == InputState::Display())
        {
            state_ = InputState::EnteringSubject();
            subject_.clear();
            clip_.clear();
            invalidate();
        }
    }

    Planar::keyboardGL(key, x, y);
}
