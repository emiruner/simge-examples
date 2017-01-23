#include "MainWin.hpp"

using namespace simge::glut;
using namespace simge::util;

namespace 
{
    const int kStepLength = 16;    

    void square(Turtle& t, int stepCount)
    {
        for(int i = 0; i < 4; ++i)
        {
            t.forward(kStepLength * stepCount);
            t.turn(90);
        }
    }
    
    void secondFig(Turtle& t, int stepCount)
    {
        while(stepCount > 1)
        {
            t.forward(kStepLength / 2 * stepCount - 1);
            t.turn(90);
            --stepCount;
        }
    }

    void baklavaDilimi(Turtle& t, int edgeLen)
    {
        t.forward(edgeLen);
        t.turn(60);
        t.forward(edgeLen);
        t.turn(120);
        t.forward(edgeLen);
        t.turn(60);
        t.forward(edgeLen);
    }
}

MainWin::MainWin()
: Planar("Misc Logos")
{
    glClearColor(0.8, 0.9, 1, 0);
    glColor3f(1, 0, 0);
    setSize(500, 160);
}

void MainWin::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 1);

    Turtle t;
  
    t.moveTo(simge::geom::point(10, 10));

    for(int i = 1; i < 5; ++i)
    {
        square(t, i);
    }
    
    t.moveTo(simge::geom::point(100, 10));
    secondFig(t, 16);
    
    t.moveTo(simge::geom::point(300, 10));
    
    t.turnTo(60);
    t.forward(40);
    t.turn(120);
    t.forward(40);
    t.turn(120);
    t.forward(40);
    t.turn(60);
    t.forward(40);
    t.turn(120);
    t.forward(80);
    t.turn(120);
    t.forward(80);
    t.turn(120);
    t.forward(40);
    
    t.moveTo(simge::geom::point(420, 45));
    
    t.turnTo(60);
    baklavaDilimi(t, 40);
    t.turnTo(180);
    baklavaDilimi(t, 40);
    t.turnTo(300);
    baklavaDilimi(t, 40);
    
    glFlush();
}
