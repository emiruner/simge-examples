#include "MainWin.hpp"

#include <simge/glut/Application.hpp>
#include <simge/algo/TriangleTriangleInx.hpp>
#include <iostream>

using namespace simge;

int main(int argc, char* argv[])
{
    glut::Application app(argc, argv);
    geom::Point<3> t1[3];
    geom::Point<3> t2[3];

    t1[0] = geom::point(0, 1, 0);
    t1[1] = geom::point(0, 0, 1);
    t1[2] = geom::point(1, 0, 0);

    t2[0] = geom::point(0.1, 0.1, 0.1);
    t2[1] = geom::point(1, 0.1, 0.1);
    t2[2] = geom::point(0.1, 1, 0.4);

    PointVec inx = algo::findTriangleTriangleIntersection(t1, t2);
    if(inx.size() > 0)
    {
        std::cout << "Triangles intersect.\n";
    }
    else 
    {
        std::cout << "Triangles does not intersect.\n";
    }
    
    MainWin sw(t1, t2, inx);

    app.run();

	return 0;
}
