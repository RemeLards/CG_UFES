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
        ArenaPlayer(CircleDefinition c) : player_head(c)
        {
            last_pos = PositionDefinition(
                player_head.GetX(), // Precisa ver as coordenadas ... mas apriori é isso
                player_head.GetY(),
                0
            );
            current_pos = last_pos;
        };

        void DrawPlayer();
        void AnimatePlayer();
        void MoveInX(
            CircularArena& arena,
            std::vector<CircularObstacle>& obstacles_vec,
            std::vector<ArenaPlayer>& arena_vec,
            double dx
        );
        void MoveInY(
            CircularArena& arena,
            std::vector<CircularObstacle>& obstacles_vec,
            std::vector<ArenaPlayer>& arena_vec, 
            double dy
        );

        double SquareDistanceTo(double x, double y);


        bool InArena(CircularArena& arena);
        bool ArenaCollision(CircularArena& arena);
        bool ObstacleCollision(CircularArena& arena, std::vector<CircularObstacle>& obstacles_vec);
        bool PlayerCollision(CircularArena& arena, std::vector<ArenaPlayer>& players_vec);

        PositionDefinition GetPos(){ return current_pos; };
        double Hitbox(){ return player_head.GetRadius(); };
        double GetX() {return current_pos.GetX(); };
        double GetY() {return current_pos.GetY(); };

};


#endif