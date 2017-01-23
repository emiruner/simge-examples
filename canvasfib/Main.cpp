#include "MainWin.hpp"
#include "Golden.hpp"

#include <simge/glut/Application.hpp>

#include <cstdlib>
#include <vector>
#include <iostream>

int main(int argc, char* argv[])
{
    simge::glut::Application app(argc, argv);
    MainWin sw(32);
    Golden ratio(32);
    
    app.run();

	return 0;
}
