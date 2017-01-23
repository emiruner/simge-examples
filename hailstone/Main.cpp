#include <simge/glut/Application.hpp>
#include "MainWin.hpp"

#include <cstdlib>
#include <cstdio>

int main(int argc, char* argv[])
{
    simge::glut::Application app(argc, argv);

    if(argc != 2)
    {
        fprintf(stderr, "\nPlease specify starting number [1, maxint)"
                        " in command line.\n\n");
        exit(-1);
    }
    
    const int count = atoi(argv[1]);
    
    if(count <= 0)
    {
        fprintf(stderr, "\nSpecified number is not in accepted range.\n\n");
        exit(-2);
    }
    
    MainWin mw("Hailstone", count);
    app.run();

    return 0;
}
