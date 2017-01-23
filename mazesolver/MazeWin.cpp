#include "MazeWin.hpp"
#include <simge/glut/Point.hpp>

using namespace simge::geom;
using namespace simge::glut;

MazeWin::MazeWin(char const* name, Maze const& maze, int wallLength)
: Planar(name, GLUT_RGBA | GLUT_DOUBLE), maze_(maze), wallLength_(wallLength)
{
    glClearColor(0.8, 0.9, 1.0, 0.0);
    setSize(maze_.getWidth() * wallLength_ + Margin * 2, maze_.getHeight() * wallLength_ + Margin * 2);
    maze_.solve(Location(0, 0), Location(maze_.getWidth() - 1,maze_.getHeight() -1));
}

void MazeWin::reshapeGL (int width, int height)
{
    Planar::reshapeGL(width, height);

    const int cellWidth = (width - Margin * 2) / maze_.getWidth();
    const int cellHeight = (height - Margin * 2) / maze_.getHeight();
    
    wallLength_ = cellWidth > cellHeight ? cellHeight : cellWidth;
}   

void MazeWin::mouseGL(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN)
    {        
        if(button == GLUT_LEFT_BUTTON)
        {
            maze_ = Maze(maze_.getWidth(), maze_.getHeight());
            maze_.solve(Location(0, 0), Location(maze_.getWidth() - 1,maze_.getHeight() -1));
            invalidate();
        }
    }
}    

void MazeWin::vertex(int x, int y)
{
    glVertex2i(Margin + x, Margin + y);
}

void MazeWin::paintGL()
{
    const int crossLen = wallLength_ / 3;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    {
        for(int y = 0; y < maze_.getHeight(); ++y)
        {
            for(int x = 0; x < maze_.getWidth(); ++x)
            {
                if(maze_.isWallPresent(x, y, Direction::North))
                {
                    vertex(x * wallLength_, y * wallLength_);
                    vertex((x + 1) * wallLength_, y * wallLength_);
                }

                if(maze_.isWallPresent(x, y, Direction::East))
                {
                    vertex((x + 1) * wallLength_, y * wallLength_);
                    vertex((x + 1) * wallLength_, (y + 1) * wallLength_);
                }

                if(maze_.isWallPresent(x, y, Direction::South))
                {
                    vertex(x * wallLength_, (y + 1) * wallLength_);
                    vertex((x + 1) * wallLength_, (y + 1) * wallLength_);
                }

                if(maze_.isWallPresent(x, y, Direction::West))
                {
                    vertex(x * wallLength_, y * wallLength_);
                    vertex(x * wallLength_, (y + 1) * wallLength_);
                }
            }
        }
    }
    glEnd();

    for(int y = 0; y < maze_.getHeight(); ++y)
    {
        for(int x = 0; x < maze_.getWidth(); ++x)
        {
            if(maze_.isOnPath(x, y))
            {
                glColor3f(0, 0, 1);
            }
            else
            {
                glColor3f(1, 0, 0);
            }
            
            if(maze_.isVisited(x, y))
            {
                glBegin(GL_POLYGON);
                vertex(x * wallLength_ + crossLen, (y + 1) * wallLength_ - crossLen);
                vertex((x + 1) * wallLength_ -crossLen, (y + 1) * wallLength_ -crossLen);
                vertex((x + 1) * wallLength_ - crossLen, y * wallLength_ + crossLen);
                vertex(x * wallLength_ + crossLen, y * wallLength_ + crossLen);
                glEnd();                
            }
        }
    }

    swapBuffers();
}
