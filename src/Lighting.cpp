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
//    lights.push_back( new Light( vec2(200,30), 100.0f ) );
//    lights.push_back( new Light( vec2(200,780), 200.0f ) );
}


vector<vec2> Lighting::getShadowShape( int index, Block &object ){

    vec2 source = lights.at(index)->pos;
    
    float angle = atan2( object.pos.y - source.y, object.pos.x - source.x);
    
    vec2 cornerA = vec2(0,0);
    vec2 cornerB = vec2(0,0);
    vec2 cornerC = vec2(0,0);
    
    bool hasCornerC = false;
    
    if( source.y < object.pos.y and abs(object.pos.x - source.x) < object.width/2){
        
        cornerA = vec2( object.left , object.top );
        cornerB = vec2( object.right, object.top );
        
    } else if( source.y > object.pos.y and abs(object.pos.x - source.x) < object.width/2){
        
        cornerA = vec2( object.left , object.bottom );
        cornerB = vec2( object.right , object.bottom );
        
    } else if( source.x < object.pos.x and abs(object.pos.y - source.y) < object.height/2){
        
        cornerA = vec2( object.left ,  object.bottom );
        cornerB = vec2( object.left ,  object.top );
        
    } else if( source.x > object.pos.x and abs(object.pos.y - source.y) < object.height/2){
        
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