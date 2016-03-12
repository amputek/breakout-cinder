//
//  EntityManager.hpp
//  Breakout
//
//  Created by Rob Dawson on 12/03/2016.
//
//

#ifndef EntityManager_hpp
#define EntityManager_hpp

#include <stdio.h>
#include "GameObject.hpp"
#include "Explosion.hpp"
#include "Debris.hpp"
#include "Brick.hpp"
#include "Math.hpp"

using namespace math;

class EntityManager{
public:
    EntityManager(){}
    std::vector<GameObject*> collection;
    virtual void add(){}
    void update(float dt){
        for( std::vector<GameObject*>::iterator d = collection.begin(); d < collection.end(); ){
            if( (*d)->isDead() ){
                d = collection.erase(d);
            } else {
                (*d)->update( dt );
                ++d;
            }
        }
    }
    void draw( GameRenderer* renderer ){
        for(int i = 0; i < collection.size();  i++){
            collection.at(i)->draw( renderer );
        }
    }
    void kill( int i ){
        
    }
    int size(){ return collection.size(); }
    GameObject* get( int i ){ return collection.at(i); }
    virtual bool isDead( GameObject* obj ){
        return false;
    }
};

class DebrisManager : public EntityManager{
public:
    DebrisManager() : EntityManager(){}
    void add( vec2 p, vec2 v ){
        for( int i = 0; i < 5; i ++){
            vec2 vel = vec2( v * Rand::randFloat(4.0f, 20.0f) );
            vel += Rand::randVec2() * Rand::randFloat(30.0f, 100.0f);
            vec2 pos = p + (Rand::randVec2() *= Rand::randFloat(0.0f, 10.0f));
            Debris* d = new Debris( pos, vel, Rand::randFloat(2.0f, 6.0f), Rand::randFloat(-10.0f, 10.0f) );
            collection.push_back( d );
        }
    }
};

class ExplosionManager : public EntityManager {
public:
    ExplosionManager() : EntityManager(){}
    void add( vec2 pos ){
        collection.push_back( new Explosion( pos ));
    }
};

class BricksManager : public EntityManager{
public:
    BricksManager() : EntityManager(){}
    void add( int x, int y, std::string type ){
        if( type == "brick" ){
            collection.push_back( new StandardBrick( vec2( 40 + x * 18, 40 + y * 18), 14 ) );
        } else {
            collection.push_back( new ExplosiveBrick( vec2( 40 + x * 18, 40 + y * 18), 14 ) );
        }
    }
    void kill( int i ){
        Brick* b = dynamic_cast<Brick*>(collection.at(i));
        b->kill();
    }
    Block * getAsBlock( int i ){
        return dynamic_cast<Block*>( get(i) );
    }
    void checkCast( vec2 ballpos ){
        for(int i = 0; i < collection.size();  i++){
            Brick * b = dynamic_cast<Brick*>(collection.at(i));
            b->casting = true;
            for(int n = 0; n < collection.size(); n++){
                Brick * b2 = dynamic_cast<Brick*>(collection.at(n));
                if( distance( b2->pos, ballpos ) < distance( b->pos, ballpos ) ){
                    if( abs( getAngle( ballpos, b->pos ) - getAngle( ballpos, b2->pos ) ) < 0.03 ){
                        b->casting = false;
                    }
                }
            }
        }
    }
};


#endif /* EntityManager_hpp */
