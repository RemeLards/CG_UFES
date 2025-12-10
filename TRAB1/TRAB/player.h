#ifndef PLAYER_H
#define PLAYER_H

#include "utils.h"
#include "arena.h"
#include "arena_obstacles.h"

#include <vector>
#include <string>

#include <stdio.h>
#include <math.h>


class ArenaPlayer
{
    private:
        CircleDefinition player_head;
        PositionDefinition current_pos;
        PositionDefinition last_pos;
        
    public:
        ArenaPlayer(CircleDefinition c) : player_head(c) {};

        void DrawPlayer();

        double SquareDistanceTo(double x, double y);

        bool InArena(CircularArena arena);
        bool ArenaCollision(CircularArena arena);
        bool ObstacleCollsion(CircularArena arena, std::vector<CircularObstacles> circular_obstacles_vec);

};


#endif