#ifndef PLAYER_H
#define PLAYER_H

#include "utils.h"
#include "arena.h"
#include "arena_obstacles.h"
#include "bullet.h"

#include <vector>
#include <string>

#include <stdio.h>
#include <math.h>


class ArenaPlayer
{
    private:
        CircleDefinition player_head;
        PositionDefinition last_pos;
        PositionDefinition current_pos;
        std::vector<Bullet> bullet_vec;
        double gun_yaw;
        
    public:
        ArenaPlayer(CircleDefinition c) : 
            player_head(c),
            last_pos(c.GetX(), c.GetY(), 0),
            current_pos(c.GetX(), c.GetY(), 0),
            gun_yaw(0)
            {};

        // Drawing
        void DrawPlayer();
        void AnimatePlayer();

        // Player interaction -> Moving,Rotating and Shooting
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
        Bullet* Shoot();

        // Collions Check
        double SquareDistanceTo(double x, double y);
        bool InArena(CircularArena& arena);
        bool ArenaCollision(CircularArena& arena);
        bool ObstacleCollision(CircularArena& arena, std::vector<CircularObstacle>& obstacles_vec);
        bool PlayerCollision(CircularArena& arena, std::vector<ArenaPlayer>& players_vec);

        // Pos and Hitbox
        PositionDefinition GetPos(){ return current_pos; };
        double Hitbox(){ return player_head.GetRadius(); };
        double GetX() {return current_pos.GetX(); };
        double GetY() {return current_pos.GetY(); };

};


#endif