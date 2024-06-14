#include "Structure.hpp"

Physics::Structure::Structure(Vec2d v1, Vec2d v2, Vec2d v3, Vec2d v4)
: v1(v1), v2(v2), v3(v3), v4(v4), 
  e1(Line2d(v1, v2)), e2(Line2d(v2, v3)), e3(Line2d(v3, v4)), e4(Line2d(v4, v1))
{}
