#include <simge/glut/Application.hpp>
#include <simge/util/PolylineFile.hpp>

#include "MainWin.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
    simge::glut::Application app(argc, argv);
    Polyline2DVec lines;

    if(argc != 2)
    {
        std::cerr << "\nMissing argument!\n"
                  << "Usage: exename inputfile\n\n";
        return -1;
    }

    std::ifstream in(argv[1]);
    
    if(!in.is_open())
    {
        std::cerr << "Cannot open input file.\n";
        return -1;
    }
    
    try
    {
        simge::util::PolylineFile<simge::geom::Point<2> > input(in);

        const int lineCount = input.getPolylineCount();
        
        for(int i = 0; i < lineCount; ++i)
        {
            lines.push_back(input.getNext());
        }

        MainWin mw("Polyline File Viewer", lines);
        app.run();
    }
    catch(std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}
