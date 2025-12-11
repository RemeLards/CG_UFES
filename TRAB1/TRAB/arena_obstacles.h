#ifndef ARENA_OBSTACLES_H
#define ARENA_OBSTACLES_H

#include "utils.h"

class CircularObstacle
{
    private:
        CircleDefinition obstacle;

    public:
        Obstaculo(CircleDefinition c) : obstacle(c) {};
        
        void DrawObstacle();

        double GetX(){ return obstacle.GetX();};
        double GetY(){ return obstacle.GetY();};
        double GetRadius(){ return obstacle.GetRadius();};
};

#endif