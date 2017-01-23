#include <cstdio>
#include <cstdlib>

#include <simge/glut/Application.hpp>

#include "Dots.hpp"

namespace
{
    inline void errorExit(char const* msg, int code)
    {
        fprintf(stderr, "%s\n", msg);
        exit(code);
    }
    
    void processCommandLine(int argc, char* argv[], BasicRng& gen, int& dots)
    {
        if(argc != 5)
        {
            errorExit("\nInvalid arguments!\nUsage: exename "
                      "a b start dotCount\n", -1);
        }
        
        int a, b, start;
        
        a = atoi(argv[1]);
        b = atoi(argv[2]);
        start = atoi(argv[3]);

        gen = BasicRng(a, b, start);
        dots = atoi(argv[4]);
    }
} // namespace <unnamed>

int main(int argc, char* argv[])
{
    simge::glut::Application app(argc, argv);

    BasicRng gen;
    int dotCount;

    processCommandLine(argc, argv, gen, dotCount);

    Dots win(gen, dotCount);
    app.run();

    return 0;
}
