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

void CollisionManager::checkCollision( Collision *pt, vec2 a, vec2 b, vec2 c, vec2 d, string dir ){
    float denom = ((d.y-c.y) * (b.x-a.x)) - ((d.x-c.x) * (b.y-a.y));
    if (denom != 0){
        float ua = (((d.x-c.x) * (a.y-c.y)) - ((d.y-c.y) * (a.x-c.x))) / denom;
        if ((ua >= 0) && (ua <= 1)){
            float ub = (((b.x-a.x) * (b.y-c.y)) - ((b.y-a.y) * (a.x-c.x))) / denom;
            if ((ub >= 0) && (ub <= 1)){
                float x = a.x + (ua * (b.x-a.x));
                float y = a.y + (ua * (b.y-a.y));
                vec2 pos = vec2(x,y);
                pt->exists = true;
                pt->pos = pos;
                pt->dir = dir;
            }
        }
    }
}

Collision CollisionManager::paddleCollision( vec2 pos, vec2 vel, float r, Block *rec ){
    return ballIntercept( pos, vel, r, rec );
}

Collision CollisionManager::brickCollision( vec2 pos, vec2 vel, float r, Block *brick ){
    return ballIntercept( pos, vel, r, brick );
}

Collision CollisionManager::wallCollision( vec2 pos, vec2 vel, float r ){
    Collision pt = ballIntercept( pos, vel, r, &topWall );
    if( !pt.exists ) pt = ballIntercept( pos, vel, r, &leftWall );
    if( !pt.exists ) pt = ballIntercept( pos, vel, r, &rightWall );
    return pt;
}

Collision CollisionManager::ballIntercept( vec2 pos, vec2 vel, float r, Block *rec ){

    Collision pt;
    
    float radius = r;
    vec2 bal = pos;

    vec2 topleft = vec2( rec->left-radius  , rec->top-radius );
    vec2 bottomleft = vec2( rec->left-radius, rec->bottom+radius);
    vec2 bottomright = vec2( rec->right+radius, rec->bottom+radius);
    vec2 topright = vec2( rec->right+radius , rec->top-radius );
    
    if( vel.x < 0){
        checkCollision( &pt, bal, bal+vel, topright, bottomright, "right" );
    } else {
        checkCollision( &pt, bal, bal+vel, topleft, bottomleft, "left" );
    }
    if( pt.exists == false ){
        if( vel.y < 0){
            checkCollision( &pt, bal, bal+vel, bottomleft, bottomright, "bottom" );
        } else {
            checkCollision( &pt, bal, bal+vel, topleft, topright, "top" );
        }
    }
    return pt;

//    if( pt->exists ){
//        if( pt->dir == "top" || pt->dir == "bottom" ){
//            ball->bounce( "vert" , pt->pos.y );
//        }
//        if( pt->dir == "left" || pt->dir == "right" ){
//            ball->bounce( "hor" , pt->pos.x );
//        }
//        delete pt;
//        return true;
//    }
//    
//    delete pt;
//    return false;
    
    
}
