#include "MainWin.hpp"

#include <cmath>
#include <cassert>

using namespace simge::glut;
using namespace simge::util;

namespace
{
    /**
     * Draws an n-gon using turtle.
     */
    void turtleNGon(Turtle& t, int numSides, float sideLength)
    {
        const float turnAngle = 360.0 / numSides;
        
        for(int i = 0; i < numSides; ++i)
        {
            t.forward(sideLength);
            t.turn(turnAngle);
        }
    }
    
} // namespace <unnamed>

MainWin::MainWin()
: Planar("Turtle NGon")
{
    glClearColor(0.8, 0.9, 1, 0);
    glColor3f(1, 0, 0);
    setSize(400, 400);
}

void MainWin::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0, 0, 1);

    Turtle t;

    for(int i = 3; i < 13; ++i)
    {
        t.turnTo(270);
        t.moveTo(simge::geom::point(10, 200));
        turtleNGon(t, i, 64);
    }
    
    glFlush();
}
