#include "MainWin.hpp"

using namespace simge::glut;
using namespace simge::util;

namespace 
{
    const int kStepLength = 12;    

    void zigzag(Turtle& t, int maxSteps) 
    {
        int stepCount = maxSteps;
        
        while(stepCount > 0)
        {
            t.forward(stepCount * kStepLength);
            t.turn(90);
            --stepCount;
        }

        t.forward(kStepLength);
        
        t.turn(-90);

        stepCount = 1;
        
        while(stepCount <= maxSteps)
        {
            t.forward(stepCount * kStepLength);
            t.turn(-90);
            ++stepCount;
        }

        t.forward((stepCount - 1) * kStepLength);
    }
}

MainWin::MainWin()
: Planar("Zig Zag")
{
    glClearColor(0.8, 0.9, 1, 0);
    glColor3f(1, 0, 0);
    setSize(512, 148);
}

void MainWin::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 1);

    Turtle t;

    t.moveTo(simge::geom::point(10, 10));
    t.turnTo(0);

    for(int i = 3; i < 9; ++i)
    {
        zigzag(t, i);
        t.turn(90);
    }
   
    glFlush();
}
