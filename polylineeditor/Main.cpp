#include <simge/glut/Application.hpp>
#include <simge/util/PolylineFile.hpp>

#include "Editor.hpp"

#include <cstdlib>
#include <iostream>

Editor* editor;

void saveFile()
{
    editor->~Editor();
}

int main(int argc, char* argv[])
{
    simge::glut::Application app(argc, argv);
    Polyline2DVec lines;

    char const* filename;

    if(argc == 1)
    {
        filename = "untitled.txt";
    }
    else if(argc == 2)
    {
        filename = argv[1];
    }
    else
    {
        std::cerr << "Please specify at most 1 file.\n";
        return -1;
    }
    
    Editor mw("Polyline File Viewer", filename);
    editor = &mw;
    atexit(&saveFile);
    
    app.run();

    return 0;
}
