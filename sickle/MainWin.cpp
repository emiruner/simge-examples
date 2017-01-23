#include "MainWin.hpp"
#include "Sickle.hpp"

#include <algorithm>
#include <simge/util/Utility.hpp>

using namespace simge::geom;
using namespace simge::glut;
using namespace simge::util;

namespace
{

bool isConvex(Polygon<2> const& poly)
{
    Polygon<2>::const_iterator it, end = poly.end(), next;
    
    for(it = poly.begin(); it != end; ++it)
    {
        next = it;
        
        ++next;
        if(next == end)
        {
            next = poly.begin();
        }
        
        const Edge<2> edge(*it, *cycle(poly, it));
        const Point<2> classifier(*cycle(poly, cycle(poly, it)));
        
        if(classify(edge, classifier) == Orientation::Left())
        {
            return false;
        }
    }
    
    return true;
}


inline void writeMsg(char const* msg)
{
    glColor3f(1, 0, 0);
    drawText(GLUT_BITMAP_8_BY_13, point(10, 10), msg);
}

} // namespace <unnamed>

MainWin::MainWin()
: Planar("Polygon Clipping", GLUT_RGBA | GLUT_DOUBLE),
  p_(PolygonType::RightIsInterior()), q_(PolygonType::LeftIsInterior()),
  state_(EnteringSubject)
{
    glClearColor(0, 0, 0, 0);
    glColor3f(1, 0, 0);
    setSize(620, 460);
}

void MainWin::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(2);

    glColor3f(1, 0, 0);
    drawLineLoop(p_);

    glColor3f(0.3, 1, 0.3);
    drawLineLoop(q_);    

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
        drawLineLoop(intersection_);

        if(!isConvex(p_) || !isConvex(q_))
        {
            writeMsg("Warning: One of the polygons is not convex. Press `n' to start from beginning.");
        }
        else
        {
            writeMsg("Press `n' to start from beginning.");
        }
        
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
                p_.addVertex(windowToGl(x, y));
                invalidate();
            }
            else if(state_ == EnteringClip)
            {
                q_.addVertex(windowToGl(x, y));
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
                intersection_ = clipPolygon(p_, q_);
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
            p_.clear();
            q_.clear();
            invalidate();
        }
    }

    Planar::keyboardGL(key, x, y);
}
