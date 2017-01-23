#ifndef SICKLE_HPP_INCLUDED
#define SICKLE_HPP_INCLUDED

#include <simge/geom/Polygon.hpp>
#include <vector>

/**
 * Find intersection of two polygons. Polygons must be non degenerate convex polygons.
 * The polygons must be right is interior type polygons.
 */
simge::geom::Polygon<2> clipPolygon(simge::geom::Polygon<2>& p, simge::geom::Polygon<2>& q);

#endif
