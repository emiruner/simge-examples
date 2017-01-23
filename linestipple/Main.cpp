#include <simge/glut/Application.hpp>
#include "StippleWin.hpp"

#include <cstdio>
#include <cstdlib>

int main(int argc, char* argv[])
{
    simge::glut::Application app(argc, argv);

    if(argc != 3)
    {
        printf("\nMissing argument!\n");
        printf("Please supply factor and pattern(as hex)\n\n");
        exit(-1);
    }
    
    printf("\nSelect start and end points of lines "
           "by clicking left mouse button.\n\n");
    
    StippleWin sw(atoi(argv[1]), strtol(argv[2], 0, 16));
    sw.setSize(640, 480);
    
    app.run();

    return 0;
}
