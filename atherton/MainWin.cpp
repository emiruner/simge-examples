#include "MainWin.hpp"

#include <algorithm>
#include <simge/util/Utility.hpp>
#include <simge/algo/Atherton.hpp>

using namespace simge::geom;
using namespace simge::glut;
using namespace simge::util;
using namespace simge::algo;

namespace
{

inline void writeMsg(char const* msg)
{
    glColor3f(1, 0, 0);
    drawText(GLUT_BITMAP_8_BY_13, point(10, 10), msg);
}

} // namespace <unnamed>

MainWin::MainWin()
: Planar("Weiler-Atherton Clipping", GLUT_RGBA | GLUT_DOUBLE),
  subject_(PolygonType::RightIsInterior()), clip_(PolygonType::LeftIsInterior()),
  state_(EnteringSubject)
{
    glClearColor(0, 0, 0, 0);
    glColor3f(1, 0, 0);
    setSize(620, 460);
}

void MainWin::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    void (*looper)(Polygon<2> const&) = &drawLineLoop;
    
    glLineWidth(2);

    glColor3f(1, 0, 0);
    drawLineLoop(subject_);

    glColor3f(0.3, 1, 0.3);
    drawLineLoop(clip_);    

    switch(state_)
    {
    case EnteringSubject:
        writeMsg("Enter subject polygon clockwise. "
                 "Finish by clicking right mouse button.");
        break;

    case EnteringClip:
        writeMsg("Enter clip polgon clockwise. "
                 "Finish by clicking right mouse button.");
        break;

    case Display:
        glLineWidth(4);
        glColor3f(0.9, 1, 1);
        std::for_each(intersections_.begin(), intersections_.end(), looper);
        writeMsg("Press `n' to start from beginning.");
        break;
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
            if(state_ == EnteringSubject)
            {
                subject_.addVertex(windowToGl(x, y));
                invalidate();
            }
            else if(state_ == EnteringClip)
            {
                clip_.addVertex(windowToGl(x, y));
                invalidate();
            }
        }
        else if(button == GLUT_RIGHT_BUTTON)
        {
            if(state_ == EnteringSubject)
            {
                state_ = EnteringClip;
                invalidate();
            }
            else if(state_ == EnteringClip)
            {
                state_ = Display;
                intersections_ = atherton(subject_, clip_);
                invalidate();
            }
        }
    }
}

void MainWin::keyboardGL(unsigned char key, int x, int y)
{
    if(key == 'n' || key == 'N')
    {
        if(state_ == Display)
        {
            state_ = EnteringSubject;
            subject_.clear();
            clip_.clear();
            invalidate();
        }
    }

    Planar::keyboardGL(key, x, y);
}
