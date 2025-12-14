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


#define PLAYER_SPEED -0.08 // Para mover para cima e para baixo se mantenha consistente
#define PLAYER_ROTATIONAL_SPEED 0.08 // Para mover para cima e para baixo se mantenha consistente
#define PLAYER_HEALTH 3

#define BULLET_VEL ((3.54*PLAYER_SPEED)*2.0) // (3.54*PLAYER_SPEED) = PLAYER_SPEED pra bala WTF ????
#define BULLET_RADIUS 8
#define BODY_X_RADIUS_MULTIPLER 2

#define ARM_DISTANCE_MULTIPLER 0.7
#define ARM_WIDTH_MULTIPLER 0.4
#define ARM_HEIGHT_MULTIPLER 2.0

#define LEG_DISTANCE_MULTIPLER 0.2
#define LEG_WIDTH_MULTIPLER (ARM_WIDTH_MULTIPLER * 1.2)
#define LEG_HEIGHT_MULTIPLER ARM_HEIGHT_MULTIPLER

#define LEFT_LEG_ID 1
#define RIGHT_LEG_ID 2

class Bullet; // forward declaration

class ArenaPlayer : public CircularEntityDefinition
{
    private:
        PositionDefinition direction = {0,1,0};
        PositionDefinition last_pos;
        std::vector<Bullet*> bullet_vec;
        double yaw = 0.0;
        double gun_yaw = 0.0;
        short health = PLAYER_HEALTH;
        const int _id;
        bool _is_moving = false;
        short _last_leg_id = LEFT_LEG_ID;
        bool is_leg_rotated = false;
        
    public:
        ArenaPlayer(
            double x, double y, double z,
            const std::string& color,
            double vx, double vy, double vz,
            double head_radius, int id

        ):  CircularEntityDefinition(x,y,z,color,vx,vy,vz,head_radius),
            last_pos(x, y, z),
            gun_yaw(0),
            _id(id) {};

        // Drawing
        void DrawBody();
        void DrawArm();
        void DrawLegs();
        void DrawPlayer();
        void AnimatePlayer();

        // Player interaction -> Moving,Rotating and Shooting
        void Rotate(GLdouble timeDiference);
        void Move(
            CircularArena& arena,
            std::vector<CircularObstacle>& obstacles_vec,
            std::vector<ArenaPlayer>& player_vec, 
            GLdouble timeDiference
        );
        void Shoot();
        void GotHit() { this->health--;};
        // void DeleteBullet(std::size_t index);
        // int GetBulletIndex(Bullet* bullet);

        // Collions Check
        double SquareDistanceTo(double x, double y);
        bool InArena(CircularArena& arena);
        bool ArenaCollision(CircularArena& arena);
        bool ObstacleCollision(CircularArena& arena, std::vector<CircularObstacle>& obstacles_vec);
        bool PlayerCollision(CircularArena& arena, std::vector<ArenaPlayer>& players_vec);
        // Bullet* BulletCollision(std::vector<Bullet*> bullet_vec); 

        // Pos and Hitbox
        double Hitbox(){ return this->GetRadius(); };
        int GetId() { return this->_id; };
        std::vector<Bullet*>& GetBulletVec() { return this->bullet_vec; };
        void SetMovingStatus(bool is_moving) {this->_is_moving = is_moving ;};
        bool IsMoving(){return this->_is_moving; };
        short GetLastLeg() {return this->_last_leg_id;};
        void SetCurrentLeg(short leg_id) {this->_last_leg_id = leg_id;};

};

#endif
