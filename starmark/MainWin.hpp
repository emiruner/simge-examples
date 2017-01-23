#ifndef MAINWIN_HPP_INCLUDED
#define MAINWIN_HPP_INCLUDED

#include <simge/glut/Planar.hpp>
#include <simge/util/Turtle.hpp>

#include <vector>

typedef std::vector<int> IntVec;

class MainWin : public simge::glut::Planar
{
public:
    /**
     * Swaps the passed vectors' data with internal ones effectively
     * destroying them.
     */
    MainWin(IntVec& xs, IntVec& ys);

protected:
    void paintGL();
    
private:
    IntVec xs_;
    IntVec ys_;
};

#endif
