#include "Dots.hpp"

Dots::Dots(BasicRng const& gen, int dotCount)
: simge::glut::Planar("Random Number Visualization"), gen_(gen), dotCount_(dotCount)
{
    glClearColor(0.8, 0.9, 1, 0);
    glColor3f(1.0, 0.0, 0.0);
}

void Dots::paintGL()
{
    const int width = getWidth();
    const int height = getHeight();

    glClear(GL_COLOR_BUFFER_BIT);    
    glBegin(GL_POINTS);
    {        
        gen_.reset();
        for(int i = 0; i < dotCount_; ++i)
        {
            int num = gen_.next();
            num = num % (width * height);
            
            glVertex2i(num % width, num / width);
        }
    }
    glEnd();
    glFlush();
}
