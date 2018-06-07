#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Miroljub;
typedef Miroljub::Point_2 Point;
typedef CGAL::Polygon_2<Miroljub> Polygon;
