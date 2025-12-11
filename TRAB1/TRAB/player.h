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


#define PLAYER_HEALTH 3

class ArenaPlayer
{
    private:
        CircleDefinition player_head;
        PositionDefinition last_pos;
        PositionDefinition current_pos;
        std::vector<Bullet*> bullet_vec;
        double gun_yaw;
        const int health = PLAYER_HEALTH;
        const int _id;
        
    public:
        ArenaPlayer(CircleDefinition c,int id) : 
            player_head(c),
            last_pos(c.GetX(), c.GetY(), 0),
            current_pos(c.GetX(), c.GetY(), 0),
            gun_yaw(0),
            _id(id)
            {};

        // Drawing
        void DrawPlayer();
        void AnimatePlayer();

        // Player interaction -> Moving,Rotating and Shooting
        void MoveInX(
            CircularArena& arena,
            std::vector<CircularObstacle>& obstacles_vec,
            std::vector<ArenaPlayer>& player_vec,
            double dx
        );
        void MoveInY(
            CircularArena& arena,
            std::vector<CircularObstacle>& obstacles_vec,
            std::vector<ArenaPlayer>& player_vec, 
            double dy
        );
        void Shoot(double x,double y);
        void DeleteBullet(std::size_t index);
        int GetBulletIndex(Bullet* bullet);

        // Collions Check
        double SquareDistanceTo(double x, double y);
        bool InArena(CircularArena& arena);
        bool ArenaCollision(CircularArena& arena);
        bool ObstacleCollision(CircularArena& arena, std::vector<CircularObstacle>& obstacles_vec);
        bool PlayerCollision(CircularArena& arena, std::vector<ArenaPlayer>& players_vec);
        Bullet* BulletCollision(std::vector<Bullet*> bullet_vec); 

        // Pos and Hitbox
        PositionDefinition GetPos(){ return current_pos; };
        double Hitbox(){ return this->player_head.GetRadius(); };
        double GetX() { return this->current_pos.GetX(); };
        double GetY() { return this->current_pos.GetY(); };
        int GetId() { return this->_id; };
        std::vector<Bullet*> GetBulletVec() { return this->bullet_vec; };

};


#endif