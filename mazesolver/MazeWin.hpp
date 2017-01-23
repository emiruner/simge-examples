#ifndef MY_MAZEWIN_HPP_INCLUDED
#define MY_MAZEWIN_HPP_INCLUDED

#include <simge/glut/Planar.hpp>
#include "Maze.hpp"

class MazeWin : public simge::glut::Planar
{
public:
    MazeWin(char const* name, Maze const& maze, int wallLength);
    
protected:
    void paintGL();
    void reshapeGL(int width, int height);
    void mouseGL(int button, int state, int x, int y);
    
private:
    /**
     * Calls gl vertex while converting the coordinates
     * considering Margin.
     */
    void vertex(int x, int y);
    
private:
    Maze maze_;
    int wallLength_;

    enum
    {
        Margin = 16
    };
};

#endif
