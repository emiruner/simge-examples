#ifndef JOINPOLYGON_HPP_INCLUDED
#define JOINPOLYGON_HPP_INCLUDED

#include <simge/geom/Polygon.hpp>

using namespace simge;

template <int Dim>
geom::Polygon<Dim> join(geom::Polygon<Dim> const& p1, geom::Polygon<Dim> const& p2)
{
    geom::Polygon<Dim> joined(geom::PolygonType::LeftIsInterior());
    typename geom::Polygon<Dim>::const_iterator it, end;
    
    it = p1.begin();
    end = p1.end();
    
    while(it != end)
    {
        joined.addVertex(*it);
        ++it;
    }
    
    it = p2.begin();
    end = p2.end();
    
    while(it != end)
    {
        joined.addVertex(*it);
        ++it;
    }

    return joined;
}

#endif
