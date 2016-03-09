//
//  Lighting.cpp
//  Breakout
//
//  Created by Rob Dawson on 28/02/2016.
//
//

#include "Lighting.hpp"


Lighting::Lighting(){
    lights.push_back( new Light( vec2(10,10), 150.0f ) );
}

float Lighting::generateHighlight( Light &source, Block &object, float lum ){
    float l = lum *  (1.0 - ( distance(source.pos, object.pos) / source.radius ) );
    if(l < 0){
        l = 0;
    }
    return l;
}



vector<vec2> Lighting::getShadowShape( int index, Block &object ){
//    float dist = distance(source,object.pos);
    vec2 source = lights.at(index)->pos;
    
    float angle = atan2( object.pos.y - source.y, object.pos.x - source.x);
    
    vec2 cornerA = vec2(0,0);
    vec2 cornerB = vec2(0,0);
    vec2 cornerC = vec2(0,0);
    
    bool hasCornerC = false;
    
    if( source.y < object.pos.y and abs(object.pos.x - source.x) < object.width){
        
        cornerA = vec2( object.left , object.top );
        cornerB = vec2( object.right, object.top );
        
    } else if( source.y > object.pos.y and abs(object.pos.x - source.x) < object.width){
        
        cornerA = vec2( object.left , object.bottom );
        cornerB = vec2( object.right , object.bottom );
        
    } else if( source.x < object.pos.x and abs(object.pos.y - source.y) < object.height){
        
        cornerA = vec2( object.left ,  object.bottom );
        cornerB = vec2( object.left ,  object.top );
        
    } else if( source.x > object.pos.x and abs(object.pos.y - source.y) < object.height){
        
        cornerA = vec2( object.right, object.bottom );
        cornerB = vec2( object.right, object.top );
        
    } else if(angle > 0 and angle < M_PI/2){
        
        cornerA = vec2( object.left, object.bottom );
        cornerB = vec2( object.right, object.top );
        cornerC = vec2( object.left, object.top );
        hasCornerC = true;
        
    } else if(angle > M_PI/2 and angle < M_PI){
        
        cornerA = vec2( object.left, object.top );
        cornerB = vec2( object.right, object.bottom );
        cornerC = vec2( object.right, object.top );
        hasCornerC = true;
        
    } else if(angle > -M_PI and angle < -M_PI/2 ){
        
        cornerA = vec2( object.right, object.top );
        cornerB = vec2( object.left, object.bottom );
        cornerC = vec2( object.right, object.bottom );
        hasCornerC = true;
        
    } else if(angle > -M_PI/2 and angle < 0){
        
        cornerA = vec2( object.right, object.bottom );
        cornerB = vec2( object.left, object.top );
        cornerC = vec2( object.left, object.bottom );
        hasCornerC = true;
        
    }
    
    
    float limit = 1500;
    
    
    float newangle = getAngle( cornerA, source );
    vec2 cornerFarA = vec2( source.x + cos( newangle ) * limit, source.y + sin( newangle ) * limit );
    
    float newangle1 = getAngle( cornerB, source );
    vec2 cornerFarB = vec2( source.x + cos( newangle1 ) * limit, source.y + sin( newangle1 ) * limit );
    
    
    vector<vec2> result( hasCornerC ? 5 : 4 );
    result[0] = cornerA;
    result[1] = cornerFarA;
    result[2] = cornerFarB;
    result[3] = cornerB;
    if( hasCornerC ) result[4] = cornerC;
        
    return result;
}

//vector< vector<vec2> > Lighting::getShadows( vec2 source, vector<Block*> objects ){
//    vector<vector<vec2>> v(100, vector<vec2>(5) );
//    for (int i = 0; i < objects.size(); i++) {
//        Block b = *objects.at(i);
//        vector<vec2> corners = getShadowShape( source, b );
//        v.push_back( corners );
//     }
//    return v;
//}