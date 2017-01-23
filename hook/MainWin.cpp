#include "MainWin.hpp"

using namespace simge::glut;
using namespace simge::util;

namespace 
{
    const int kStepLength = 32;

    void hook(Turtle& t)
    {
        t.forward(3 * kStepLength);
        t.turn(90);
        t.forward(kStepLength);
        t.turn(90);
        t.forward(kStepLength);
        t.turn(90);
    }
}

MainWin::MainWin()
: Planar("Hook")
{
    glClearColor(0.8, 0.9, 1, 0);
    glColor3f(1, 0, 0);
    setSize(200, 200);
}

void MainWin::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0, 0, 1);

    Turtle t;

    t.moveTo(simge::geom::point(getWidth() / 2.0 - kStepLength * 1.5,
                   getHeight() / 2.0));
    
    t.turnTo(0);
    for(int i = 0; i < 4; ++i)
    {
        hook(t);
    }
    
    glFlush();
}
