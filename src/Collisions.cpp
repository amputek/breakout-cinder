//
//  Collisions.cpp
//  Breakout
//
//  Created by Rob Dawson on 25/02/2016.
//
//

#include "Collisions.hpp"


CollisionManager::CollisionManager( int w, int h ){
    topWall = *new Block( vec2(300,-10), 1000, 20 );
    leftWall = *new Block( vec2(0,200), 10, 1000 );
    rightWall = *new Block( vec2(w,200), 10, 1000 );
}

bool CollisionManager::checkCollision( Ball * ball, vec2 c, vec2 d, string dir ){
    vec2 currentpos = ball->pos;
    vec2 nextpos = ball->pos + ball->vel;
    float denom = ((d.y-c.y) * (nextpos.x-currentpos.x)) - ((d.x-c.x) * (nextpos.y-currentpos.y));
    if (denom != 0){
        float ua = (((d.x-c.x) * (currentpos.y-c.y)) - ((d.y-c.y) * (currentpos.x-c.x))) / denom;
        if ((ua >= 0) && (ua <= 1)){
            float ub = (((nextpos.x-currentpos.x) * (nextpos.y-c.y)) - ((nextpos.y-currentpos.y) * (currentpos.x-c.x))) / denom;
            if ((ub >= 0) && (ub <= 1)){
                float x = currentpos.x + (ua * (nextpos.x - currentpos.x));
                float y = currentpos.y + (ua * (nextpos.y - currentpos.y));
                vec2 pos = vec2(x,y);
                affectBall( ball, pos, dir );
                return true;
            }
        }
    }
    return false;
}

bool CollisionManager::ballCollision( Ball * ball, Block * rec ){
    

    vec2 topleft     = vec2( rec->left - ball->radius  , rec->top - ball->radius );
    vec2 bottomleft  = vec2( rec->left - ball->radius  , rec->bottom + ball->radius);
    vec2 bottomright = vec2( rec->right - ball->radius , rec->bottom + ball->radius);
    vec2 topright    = vec2( rec->right - ball->radius , rec->top - ball->radius );
    
    
    if( checkCollision( ball , topright   , bottomright , "right" ) ) return true;
    if( checkCollision( ball , topleft    , bottomleft  , "left" ) ) return true;
    if( checkCollision( ball , bottomleft , bottomright , "bottom" ) ) return true;
    if( checkCollision( ball , topleft    , topright    , "top" ) ) return true;


//    if( ball->vel.x < 0){
//        if( checkCollision( ball ,topright, bottomright, "right" ) ) return true;
//    } else {
//        if( checkCollision( ball, topleft, bottomleft, "left" ) ) return true;
//    }
//    if( ball->vel.y < 0){
//        if( checkCollision( ball, bottomleft, bottomright, "bottom" ) ) return true;
//    } else {
//        if( checkCollision( ball, topleft, topright, "top" ) ) return true;
//    }
    
    return false;
}


