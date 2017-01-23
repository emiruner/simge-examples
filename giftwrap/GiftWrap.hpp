#ifndef GIFTWRAP_HPP_INCLUDED
#define GIFTWRAP_HPP_INCLUDED

#include <simge/geom/Polygon.hpp>

/**
 * Finds the convex hull of the given point set using gift wrapping algorithm.
 */
simge::geom::Polygon<2> giftWrapConvexHull(simge::geom::Point<2>* points, int count);

#endif
