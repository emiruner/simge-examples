#include <simge/glut/Application.hpp>

#include "Maze.hpp"
#include "MazeWin.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        std::cerr << "\nPlease specify row and "
            "column count at command line.\n";
    }
    else
    {
        const int r = atoi(argv[1]);
        const int c = atoi(argv[2]);
        
        if(r <= 0 || c <= 0)
        {
            std::cerr << "\nRow and column counts must be bigger than zero.\n";
        }
        else
        {
            simge::glut::Application app(argc, argv);
            Maze small(r, c);
            MazeWin mw("Maze Solver", small, 12);
    
            app.run();
            
            return 0;
        }
    }
}
