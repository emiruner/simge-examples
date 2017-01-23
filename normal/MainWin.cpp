#include "MainWin.hpp"
#include <algorithm>
#include <simge/geom/Operations.hpp>
#include <simge/util/Utility.hpp>
#include <iostream>

using namespace simge::geom;
using namespace simge::glut;
using namespace simge::util;

MainWin::MainWin()
: Planar("Normal Test", GLUT_RGBA | GLUT_DOUBLE), clickCount_(0)
{
    glClearColor(0.8, 0.9, 1, 0);
    glColor3f(1, 0, 0);
    setSize(620, 460);
}

void MainWin::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if(isSecondPointSelected())
    {
        glColor3f(1, 0, 0);
        drawArrow(line_[0], line_.direction0_1(), line_.length());
        glColor3f(0, 0, 0);
        drawArrow(normal_[0], normal_.direction0_1(), normal_.length());
    }
    
    glFlush();
    glutSwapBuffers();
}

void MainWin::mouseGL(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN)
    {
        if(button == GLUT_LEFT_BUTTON)
        {
            if(isFirstPointSelected())
            {
                line_[1] = windowToGl(x, y);

                Vector<2> norm = line_.ccwNormal0_1() * line_.length() / 2;
                
                normal_[0] = findMidPoint(line_[0], line_[1]);
                normal_[1] = normal_[0] + norm;

                invalidate();
            }
            else
            {
                line_[0] = windowToGl(x, y);
            }

            selectNewPoint();
        }
    }
}

