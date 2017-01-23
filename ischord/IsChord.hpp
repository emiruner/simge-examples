#ifndef ISCHORD_HPP_INCLUDED
#define ISCHORD_HPP_INCLUDED

#include <simge/geom/Polygon.hpp>
#include <simge/geom/Edge.hpp>

/**
 * Checks whether given diagonal is an arch at the same time.
 */
bool isChord(simge::geom::Polygon<2> const& poly, simge::geom::Edge<2> const& diagonal);

#endif
