#ifndef MY_DOTS_HPP_INCLUDED
#define MY_DOTS_HPP_INCLUDED

#include <simge/glut/Planar.hpp>
#include "BasicRng.hpp"

class Dots : public simge::glut::Planar
{
public:
    Dots(BasicRng const& gen, int dotCount);

protected:
    void paintGL();
    
private:
    BasicRng gen_;
    int dotCount_;
};

#endif
