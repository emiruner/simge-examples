#include "MainWin.hpp"

#include <simge/glut/Application.hpp>
#include <simge/algo/LineTriangleInx.hpp>

#include <iostream>

using namespace simge;

int main(int argc, char* argv[])
{
    glut::Application app(argc, argv);
    geom::Point<3> triangle[3];
    geom::Point<3> line[2];
    
    triangle[0] = geom::point(0, 1, 0);
    triangle[1] = geom::point(0, 0, 1);
    triangle[2] = geom::point(1, 0, 0);

    line[0] = geom::point(0, 0, 0);
    line[1] = geom::point(0.8, 0.8, 0.8);
    
    geom::Point<3> inx;
    
    bool inside = algo::findLineTriangleIntersection(triangle, line, inx);
    if(inside)
    {
        std::cout << "Line intersects with the triangle at the point: " << inx << '\n';
    }
    else 
    {
        std::cout << "Line does not intersect with the triangle.\n";
    }
    
    MainWin sw(triangle, line, inx);

    app.run();

	return 0;
}
