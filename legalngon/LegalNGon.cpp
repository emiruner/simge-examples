#include "LegalNGon.hpp"
#include <vector>

using namespace simge::geom;

namespace 
{    
    typedef std::vector<Edge<2> > Edge2Vec;
    
    inline Edge2Vec getEdges(Polygon<2> const& poly) 
    {
        Edge2Vec result;
        Polygon<2>::const_iterator current = poly.begin(), end = poly.end();
        
        while(current != end)
        {  		
            result.push_back(Edge<2>(*current, *cycle(poly, current)));
            ++current;
        }
        
        return result;
    }
    
} // namespace <unnamed>

bool isLegalNgon(Polygon<2> const& poly)
{
    const Edge2Vec edges(getEdges(poly));
    const Edge2Vec::const_iterator end = edges.end();
    
    for(Edge2Vec::const_iterator it1 = edges.begin(); it1 != end; ++it1)
    {
        for(Edge2Vec::const_iterator it2 = edges.begin(); it2 != end; ++it2)
        {
            if(it1 != it2)
            {
                Point<2> inx;
                
                if(intersection(*it1, *it2, inx))
                {
                    if(inx != (*it1)[0] && inx != (*it1)[1])
                    {
                        return false;
                    }
                }
            }
        }
    }
    
    return true;
}
