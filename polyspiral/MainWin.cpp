#include "MainWin.hpp"

using namespace simge::glut;
using namespace simge::util;

namespace 
{
    const int kStepLength = 12;    

    void polySpiral(Turtle& t, float length, float angle, float incr,int count)
    {
        while(--count >= 0)
        {
            t.forward(length);
            length += incr;
            t.turn(angle);
        }
    }
}

MainWin::MainWin()
: Planar("Polyspiral")
{
    glClearColor(0.8, 0.9, 1, 0);
    glColor3f(1, 0, 0);
    setSize(320, 240);
}

void MainWin::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 1);

    Turtle t;

    t.moveTo(simge::geom::point(160, 120));
    t.turnTo(0);

    polySpiral(t, 3, 10, 0.7, 100);
    
    glFlush();
}
