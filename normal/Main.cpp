#include "MainWin.hpp"

#include <simge/glut/Application.hpp>

int main(int argc, char* argv[])
{
    simge::glut::Application app(argc, argv);
    MainWin sw;

    app.run();

	return 0;
}
