//
//  Math.cpp
//  Breakout
//
//  Created by Rob Dawson on 28/02/2016.
//
//

#include "Math.hpp"

namespace math {
    float distance( vec2 a, vec2 b){
        return sqrt( pow(a.x-b.x, 2) + pow(a.y-b.y, 2));
    }
    
    float getAngle( vec2 a, vec2 b){
        return atan2( a.y - b.y, a.x - b.x );
    }
}