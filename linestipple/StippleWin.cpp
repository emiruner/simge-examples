#include "StippleWin.hpp"
#include <algorithm>

StippleWin::StippleWin(int factor, int pattern)
: simge::glut::Planar("Line Stipple Test")
{
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(factor, pattern);
    glClearColor(0.8, 0.9, 1, 0);
    glColor3f(1, 0, 0);
}

void StippleWin::mouseGL(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        points_.push_back(simge::geom::point(x, getHeight() - y));
        
        if(points_.size() % 2 == 0)
        {
            glBegin(GL_LINES);
            simge::glut::vertex(points_[points_.size() - 1]);
            simge::glut::vertex(points_[points_.size() - 2]);
            glEnd();
            glFlush();
        }
    }
}

void StippleWin::paintGL()
{
    void (*vertexer)(simge::geom::Point<2> const&) = &simge::glut::vertex;
    
    glClear(GL_COLOR_BUFFER_BIT);    
    glBegin(GL_LINES);
    std::for_each(points_.begin(), points_.end(), vertexer);
    glEnd();

    glFlush();
}
