#include "GiftWrap.hpp"

using namespace simge::geom;

namespace
{
    inline bool operator<(Point<2> const& lhs, Point<2> const& rhs)
    {
        if(lhs[0] < rhs[0])
        {
            return true;
        }
        else if(lhs[0] == rhs[0])
        {
            if(lhs[1] < rhs[1])
            {
                return true;
            }
        }
        
        return false;
    }

    inline void swap(Point<2>& p1, Point<2>& p2)
    {
        Point<2> tmp(p1);
        
        p1 = p2;
        p2 = tmp;
    }

    /**
     * @pre n > 0
     */
    inline int findLeftMost(Point<2> const* s, int n)
    {
        int leftMost = 0;
        
        for(int i = 1; i < n; ++i)
        {
            if(s[i] < s[leftMost])
            {
                leftMost = i;
            }
        }
        
        return leftMost;
    }
}

Polygon<2> giftWrapConvexHull(Point<2>* s, int n)
{
    Polygon<2> p(PolygonType::LeftIsInterior());
    int a = findLeftMost(s, n);
    Point<2> np = s[a];
    
    for(int m = 0; m < n; ++m)
    {
        swap(s[a], s[m]);
        p.addVertex(s[m]);
        
        a = m + 1;
        
        for(int i = m + 2; i <= n; ++i)
        {
            const Edge<2> edge(s[m], a == n ? np : s[a]);
            const Orientation c = classify(edge, i == n ? np : s[i]);
            
            if(c == Orientation::Left() || c == Orientation::Beyond())
            {
                a = i;
            }
            
            if(a == n)
            {
                return p;
            }
        }
    }
    
    return p;
}

