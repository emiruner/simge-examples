#include "SpinWindow.hpp"

#include <simge/glut/Application.hpp>

int main(int argc, char* argv[])
{
    simge::glut::Application app(argc, argv);
    SpinWindow sw;

    app.run();

	return 0;
}
