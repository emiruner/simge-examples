#ifndef GOLDEN_HPP_INCLUDED
#define GOLDEN_HPP_INCLUDED

#include <simge/glut/Planar.hpp>
#include <simge/util/Turtle.hpp>

class Golden : public simge::glut::Planar
{
public:
    Golden(int n);

protected:
    void paintGL();

private:
    const int n_;
};

#endif
