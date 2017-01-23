#include "Sickle.hpp"
#include <simge/geom/Edge.hpp>
#include <simge/util/Enum.hpp>
#include <vector>

using namespace simge::geom;
using namespace simge;

namespace
{
    typedef std::vector<Point<2> > PointVec;
    
    bool isInsidePolygon(Polygon<2> const& poly, Point<2> const& q)
    {
        const double x = q[0], y = q[1];
        const int polySides = poly.size();
        bool oddNodes = false;
        PointVec v;
        
        for(Polygon<2>::const_iterator it = poly.begin(); it != poly.end(); ++it)    
        {
            v.push_back(*it);
        }
        
        int j = 0;
        for(int i = 0; i < polySides; ++i)
        {
            ++j;
            
            if(j == polySides)
            {
                j = 0;
            }
            
            if(v[i][1] < y && v[j][1] >= y || v[j][1] < y && v[i][1] >= y)
            {
                if(v[i][0] + (y - v[i][1]) / (v[j][1] - v[i][1]) * (v[j][0] - v[i][0]) < x)
                {
                    oddNodes = !oddNodes;
                }
            }
        }
        
        return oddNodes;
    }
    
    /**
     * Checks whehter polygon q is completely inside polygon p.
     */
    bool isCompletelyInside(Polygon<2> const& p, Polygon<2> const& q)
    {
        const Polygon<2>::const_iterator end = q.end();
        
        for(Polygon<2>::const_iterator it = q.begin(); it != end; ++it)
        {
            if(!isInsidePolygon(p, *it))
            {
                return false;
            }
        }

        return true;
    }
    
    bool aimsAt(Edge<2> const& a, Edge<2> const& b, Orientation aclass, IntersectionType crossType)
    {
        const Vector<2> va = a.direction0_1();
        const Vector<2> vb = b.direction0_1();
        
        if(crossType != IntersectionType::Collinear())
        {
            if(va[0] * vb[1] >= vb[0] * va[1])
            {
                return aclass != Orientation::Right();
            }
            else
            {
                return aclass != Orientation::Left();
            }
        }
        else
        {
            return aclass != Orientation::Beyond();
        }
    }
}

class InType : public util::Enum<int>
{
private:
    InType(int value)
    : util::Enum<int>(value)
    {
    }

public:
    static inline InType Unknown()
    {
        return InType(0);
    }
    
    static inline InType PIsInside()
    {
        return InType(1);
    }
    
    static inline InType QIsInside()
    {
        return InType(2);
    }
};

namespace
{
    const double kEpsilon = 0.0000000001;
}

struct Iterator
{
    Polygon<2>& src;
    Polygon<2>::iterator it;
    
    Iterator(Polygon<2>& s, Polygon<2>::iterator i)
    : src(s), it(i)
    {
    }

    inline void advance()
    {
        ++it;
        
        if(it == src.end())
        {
            it = src.begin();
        }
    }
};
        
void advance(Iterator& aIt, Iterator& rIt, int inside)
{
    aIt.advance();
    
    if(inside && *rIt.it != *aIt.it)
    {
        rIt.src.insert(rIt.it, *aIt.it);
    }
}

Edge<2> edgeOf(Iterator it)
{
    const Point<2> p0 = *it.it;

    it.advance();
    
    const Point<2> p1 = *it.it;
    
    return Edge<2>(p0, p1);
}

IntersectionType crossingPoint(Edge<2> const& e, Edge<2> const& f, Point<2>& p)
{
    double s, t;
    const IntersectionType eclass = intersect(e, f, s);
    
    if(eclass == IntersectionType::Collinear() || eclass == IntersectionType::Parallel())
    {
        return eclass;
    }
    
    const double lene = e.length();
    
    if(s < -kEpsilon * lene || s > 1.0 + kEpsilon * lene)
    {
        return IntersectionType::SkewNoCross();
    }
    
    intersect(f, e, t);

    const double lenf = f.length();

    if(kEpsilon * lenf <= t && t <= 1.0 + kEpsilon * lenf)
    {
        if(t <= kEpsilon * lenf)
        {
            p = f[0];
        }
        else if(t >= 1.0 - kEpsilon * lenf)
        {
            p = f[1];
        }
        else if(s <= kEpsilon * lene)
        {
            p = e[0];
        }
        else if(s >= 1.0 - kEpsilon * lene)
        {
            p = e[1];
        }
        else 
        {
            intersection(e, f, p);
        }
        
        return IntersectionType::SkewCross();
    }
    else
    {
        return IntersectionType::SkewNoCross();
    }
}

Polygon<2> clipPolygon(Polygon<2>& pPoly, Polygon<2>& qPoly)
{
    if(isCompletelyInside(pPoly, qPoly))
    {
        return qPoly;
    }

    if(isCompletelyInside(qPoly, pPoly))
    {
        return pPoly;
    }
    
    Polygon<2> rPoly;
    Iterator p(pPoly, pPoly.begin());
    Iterator q(qPoly, qPoly.begin());
    Iterator r(rPoly, rPoly.begin());
    
    Point<2> iPt, startPt;
    InType inFlag = InType::Unknown();
    int phase = 1;
    int maxIters = 2 * (pPoly.size() + qPoly.size());

    for(int i = 1; i <= maxIters || phase == 1; ++i)
    {
        Edge<2> pe = edgeOf(p);
        Edge<2> qe = edgeOf(q);
        
        Orientation pclass = classify(qe, pe[1]);
        Orientation qclass = classify(pe, qe[1]);
        IntersectionType crossType = crossingPoint(pe, qe, iPt);

        if(crossType == IntersectionType::SkewCross())
        {
            if(phase == 1)
            {
                phase = 2;

                r.src.insert(r.it, iPt);
                startPt = iPt;
            }
            else if(iPt != *r.it)
            {
                if(iPt != startPt)
                {
                    r.src.insert(r.it, iPt);
                }
                else
                {
                    return r.src;
                }
            }

            if(pclass == Orientation::Right())
            {
                inFlag = InType::PIsInside();
            }
            else if(qclass == Orientation::Right())
            {
                inFlag = InType::QIsInside();
            }
            else
            {
                inFlag = InType::Unknown();
            }
        }
        else if(crossType == IntersectionType::Collinear() && pclass != Orientation::Behind() &&
                qclass != Orientation::Behind())
        {
            inFlag = InType::Unknown();
        }
        
        const bool pAimsQ = aimsAt(pe, qe, pclass, crossType);
        const bool qAimsP = aimsAt(qe, pe, qclass, crossType);
        
        if(pAimsQ && qAimsP)
        {
            if(inFlag == InType::QIsInside() || (inFlag == InType::Unknown() && pclass == Orientation::Left()))
            {
                advance(p, r, false);
            }
            else
            {
                advance(q, r, false);
            }
        }
        else if(pAimsQ)
        {
            advance(p, r, inFlag == InType::PIsInside());
        }
        else if(qAimsP)
        {
            advance(q, r, inFlag == InType::QIsInside());
        }
        else
        {
            if(inFlag == InType::QIsInside() || (inFlag == InType::Unknown() && pclass == Orientation::Left()))
            {
                advance(p, r, false);
            }
            else
            {
                advance(q, r, false);
            }
        }
    }

    return r.src;
}

