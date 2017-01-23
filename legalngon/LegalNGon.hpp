#ifndef LEGALNGON_HPP_INCLUDED
#define LEGALNGON_HPP_INCLUDED

#include <simge/geom/Polygon.hpp>

/**
 * Checks whether the given polygon is a legal n-gon. Assumes that the polygon's vertexes
 * given in clockwise order.
 */
bool isLegalNgon(simge::geom::Polygon<2> const& poly);

#endif
