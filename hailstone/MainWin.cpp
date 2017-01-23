#include "MainWin.hpp"

using namespace simge::glut;

namespace
{
    inline void calculateFloatRanges(long start_, float& maxValue,
                                     float& maxSteps)
    {
        long maxlongValue, maxlongSteps;
        calculateRanges(start_, maxlongValue, maxlongSteps);
        maxValue = maxlongValue;
        maxSteps = maxlongSteps;
    }
}

MainWin::MainWin(char const* name, long start)
: Planar(name), start_(start)
{
    glClearColor(0.8, 0.9, 1.0, 0.0);
}

void MainWin::paintGL()
{
    const float width = getWidth();
    const float height = getHeight();

    glClear(GL_COLOR_BUFFER_BIT);

    // Axes
    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
    {
        glVertex2f(20, 0);
        glVertex2f(20, height - 20);
        glVertex2f(0, 20);
        glVertex2f(width - 20, 20);
    }
    glEnd();
    
    glColor3f(1.0, 0, 0);
    glBegin(GL_LINE_STRIP);
    {
        float maxValue, maxSteps;
        
        calculateFloatRanges(start_, maxValue, maxSteps);
        
        const float xcoeff = (width - 40) / maxSteps;
        const float ycoeff = (height - 40) / maxValue;
        
        for(int i = 0; i < static_cast<int>(maxSteps); ++i)
        {
            glVertex2f(i * xcoeff + 20,
                       static_cast<float>(hailstoneN(start_, i)) * ycoeff +20);
        }
    }
    glEnd();
    glFlush();    
}
