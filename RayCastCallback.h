//
// Created by Nico on 13.02.2021.
//

#ifndef INC_2DENGINE_RAYCASTCALLBACK_H
#define INC_2DENGINE_RAYCASTCALLBACK_H

#include <Box2D.h>

class RayCastCallback :  public b2RayCastCallback {

public:
    RayCastCallback(){
        m_fixture  = nullptr;
    }
    float ReportFixture(b2Fixture *fixture, const  b2Vec2&  point, const  b2Vec2&  normal, float fraction)
    {
        m_fixture = fixture;
        m_point  = point;
        m_normal  =  normal;
        m_fraction  =  fraction;
        return fraction;

    }

    b2Fixture* m_fixture;
    b2Vec2  m_point;
    b2Vec2  m_normal;
    float  m_fraction;
};


#endif //INC_2DENGINE_RAYCASTCALLBACK_H
