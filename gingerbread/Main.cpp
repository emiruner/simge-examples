#include <simge/glut/Application.hpp>
#include "MainWin.hpp"

#include <cstdlib>
#include <cstdio>

namespace
{
    struct ProgramConfig
    {
        int m;
        int l;
        int dotCount;
    };
    
    bool processCommandLine(int argc, char* argv[], ProgramConfig& cfg)
    {
        if(argc != 4)
        {
            fprintf(stderr, "Missing arguments.\n");
            fprintf(stderr, "Usage: exename m l dotCount\n");
            return false;
        }
     
        fprintf(stderr, "\nUse left button to select new starting point!\n\n");
        
        if((cfg.m = atoi(argv[1])) > 0)
        {
            if((cfg.l = atoi(argv[2])) > 0)
            {
                if((cfg.dotCount = atoi(argv[3])) > 0)
                {
                    return true;
                }
            }
        }
        
        fprintf(stderr, "Invalid argument: all arguments must be"
                        " numbers in range [1, intmax)\n");
        return false;
    }
} // namespace <unnamed>

int main(int argc, char* argv[])
{
    simge::glut::Application app(argc, argv);
    ProgramConfig cfg;
    
    if(processCommandLine(argc, argv, cfg))
    {
        MainWin mw("Gingerbread Man", cfg.m, cfg.l, cfg.dotCount);
        app.run();
    }
    
    return 0;
}
