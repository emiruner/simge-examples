#include "MainWin.hpp"

#include <simge/glut/Application.hpp>
#include <cstdio>

int main(int argc, char* argv[])
{
    simge::glut::Application app(argc, argv);

    if(argc != 2)
    {
        printf("\nPlease give turtle commands at command line.\n\n");
    }
    else
    {
        MainWin sw(argv[1]);
        app.run();
    }
    
    return 0;
}
