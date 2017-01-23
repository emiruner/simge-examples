#include "IsChord.hpp"
#include <simge/algo/Containment.hpp>

using namespace simge::geom;
using namespace simge::algo;

/**
 * Checks whether given diagonal is an arch at the same time.
 */
bool isChord(Polygon<2> const& poly, Edge<2> const& diagonal)
{
    Polygon<2>::const_iterator current = poly.begin(), end = poly.end();
    
    while(current != end)
    {  		
        const Edge<2> edge(*current, *cycle(poly, current));
        Point<2> intersectionPoint;
        
        if(intersection(diagonal, edge, intersectionPoint))
        {
            if(intersectionPoint != diagonal[0] && intersectionPoint != diagonal[1])
            {
                return false;
            }
        }
        
        ++current;
    }
    
    return isInsidePolygon(poly, findMidPoint(diagonal[0], diagonal[1]));
}
