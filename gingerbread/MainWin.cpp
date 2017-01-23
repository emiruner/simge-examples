#include "MainWin.hpp"

using namespace simge::geom;
using namespace simge::glut;

namespace
{
    inline double abs(double x)
    {
        return x > 0.0 ? x : 0.0 - x;
    }
    
    inline Point<2> iterate(Point<2> const& old, int m, int l)
    {
        return point(m * (1 + 2 * l) - old[1] + abs(old[0] - l * m), old[0]);
    }

} // namespace <unnamed>

MainWin::MainWin(char const* name, int m, int l, int dotCount)
: Planar(name, GLUT_RGBA | GLUT_DOUBLE), m_(m), l_(l), dotCount_(dotCount), start_(point(12, 23))
{
    glClearColor(0.8, 0.9, 1.0, 0.0);
    glColor3f(1.0, 0.0, 1.0);
    glPointSize(2.0);
    
    setSize(640, 480);
}

void MainWin::mouseGL(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        start_ = point(x, y);
        invalidate();
    }
}

void MainWin::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBegin(GL_POINTS);
    {
        Point<2> next(start_);
        
        for(int i = 0; i < dotCount_; ++i)
        {
            next = iterate(next, m_, l_);
            vertex(next);
        }
    }
    glEnd();

    swapBuffers();
    glFlush();
}
