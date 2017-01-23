#include "MainWin.hpp"
#include <cstdio>

using namespace simge::glut;
using namespace simge::util;

namespace 
{
    const int kStepLength = 32;    
}

MainWin::MainWin(char const* cmd)
: Planar("Turtle Walker"), cmd_(cmd)
{
    glClearColor(0.8, 0.9, 1, 0);
    glColor3f(1, 0, 0);
    setSize(640, 480);
}

void MainWin::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 1);
    
    Turtle t;
  
    t.moveTo(simge::geom::point(320, 240));
   
    std::string::const_iterator ch, end = cmd_.end();
    
    for(ch = cmd_.begin(); ch != end; ++ch)
    {
        switch(*ch)
        {
        case 'f':
        case 'F':
            t.forward(kStepLength);
            break;
        case 'l':
        case 'L':
            t.turn(60);
            break;
        case 'r':
        case 'R':
            t.turn(-60);
            break;
        default:
            printf("Invalid command: %c\n", *ch);
        }
    }
    
    glFlush();
}
