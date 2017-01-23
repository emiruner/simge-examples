#include "MainWin.hpp"

#include <algorithm>

#include <simge/util/Utility.hpp>
#include <simge/algo/Monotone.hpp>

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

void drawPolygon(Polygon<2> const& poly)
{

    drawLineLoop(poly);
}
    
} // namespace <unnamed>

MainWin::MainWin()
: Planar("Monotone Polygon Triangulation", GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE),
  p_(PolygonType::RightIsInterior()), finishedEntering_(false)
{
    glClearColor(0, 0, 0, 0);
    glColor3f(1, 0, 0);
    setSize(620, 460);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
}

void MainWin::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLineWidth(6);
    glColor4f(1, 0, 0, 0.8);
    drawLineLoop(p_);
    
    glColor4f(0, 1, 0, 0.9);
    glLineWidth(2);
    drawLineLoop(p_);
    for_each(triangles_.begin(), triangles_.end(), &drawPolygon);
    
    if(finishedEntering_)
    {
        writeMsg("Press `n' to start from beginning.");
    }
    else 
    {
        writeMsg("Enter polygon clockwise. Finish by clicking right mouse button.");
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
            if(!finishedEntering_)
            {
                p_.addVertex(windowToGl(x, y));
                invalidate();
            }
        }
    }
    else if(button == GLUT_RIGHT_BUTTON)
    {
        if(!finishedEntering_)
        {
            finishedEntering_ = true;
            triangles_ = triangulateMonotone(p_);
            invalidate();
        }
    }
}

void MainWin::keyboardGL(unsigned char key, int x, int y)
{
    if(key == 'n' || key == 'N')
    {
        if(finishedEntering_)
        {
            finishedEntering_ = false;
            triangles_.clear();
            p_.clear();
            invalidate();
        }
    }

    Planar::keyboardGL(key, x, y);
}
