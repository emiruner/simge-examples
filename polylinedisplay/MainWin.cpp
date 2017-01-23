#include "MainWin.hpp"
#include <algorithm>

using namespace simge::glut;

MainWin::MainWin(char const* name, Polyline2DVec const& lines)
: Planar(name), lines_(lines)
{
    glClearColor(0.8, 0.9, 1.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(2);

    setSize(640, 480);
}

void MainWin::paintGL()
{
    void (*drawer)(Polyline2D const& line) = &simge::util::draw;    

    glClear(GL_COLOR_BUFFER_BIT);    
    std::for_each(lines_.begin(), lines_.end(), drawer);
    glFlush();
}
