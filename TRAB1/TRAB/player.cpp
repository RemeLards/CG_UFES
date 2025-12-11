#include "player.h"

#define BULLET_VEL 2
#define BULLET_RADIUS 2

//  Player interaction -> Moving, Rotating and Shooting

void ArenaPlayer::MoveInX(
    CircularArena& arena,
    std::vector<CircularObstacle>& obstacles_vec, 
    std::vector<ArenaPlayer>& arena_vec,
    double dx)
{
    last_pos = current_pos;
    current_pos.SetX(current_pos.GetX() + dx);
    if ( this->ArenaCollision(arena) || this->ObstacleCollision(arena,obstacles_vec) )
    {
        current_pos = last_pos;
        return;
    }
}

void ArenaPlayer::MoveInY(
    CircularArena& arena,
    std::vector<CircularObstacle>& obstacles_vec,
    std::vector<ArenaPlayer>& arena_vec, 
    double dy)
{
    last_pos = current_pos;
    current_pos.SetY(current_pos.GetY() + dy);
    if ( this->ArenaCollision(arena) || this->ObstacleCollision(arena,obstacles_vec) )
    {
        current_pos = last_pos;
        return;
    }
}

Bullet* ArenaPlayer::Shoot()
{
    // Fazer transformações
    Bullet* bullet = new Bullet(
        VelocityDefinition(BULLET_VEL*cos(gun_yaw),BULLET_VEL*sin(gun_yaw),0),
        PositionDefinition(0,0,0),
        CircleDefinition(0,0,BULLET_RADIUS,"yellow")  
    )
}


// Collision


double ArenaPlayer::SquareDistanceTo(double x, double y)
{
    double dx = fabs(x - this->GetX());
    double dy = fabs(y - this->GetY());

    return (dx*dx + dy*dy);
}

bool ArenaPlayer::InArena(CircularArena& arena)
{
    return (this->SquareDistanceTo(arena.GetX(),arena.GetY()) <= arena.GetRadius()*arena.GetRadius());
}

bool ArenaPlayer::ArenaCollision(CircularArena& arena)
{
    if (this->InArena(arena))
    {
        double player_distance_from_arena_center = this->SquareDistanceTo(
            arena.GetX(),
            arena.GetY()
        );
        double equivalent_radius = arena.GetRadius() - this->Hitbox();
        return !(player_distance_from_arena_center <= (equivalent_radius*equivalent_radius));
    }
    else
    {
        return true; //Player somehow escaped the arena ??? useful for debug I imagine
    }
    return false;
}

// Obstacles should only exist inside the Arena
bool ArenaPlayer::ObstacleCollision(CircularArena& arena, std::vector<CircularObstacle>& obstacles_vec)
{
    if (this->InArena(arena))
    {
        for (CircularObstacle& obstacle : obstacles_vec)
        {
            double player_distance_from_obstacle_center = this->SquareDistanceTo(
                obstacle.GetX(),
                obstacle.GetY()
            );
            double limit = obstacle.GetRadius() + this->Hitbox();
            if ( player_distance_from_obstacle_center <= limit*limit )
            {
                return true;
            }
        }
    }
    else
    {
        return true; //Player somehow escaped the arena ??? useful for debug I imagine
    }

    return false;
}

bool ArenaPlayer::PlayerCollision(CircularArena& arena, std::vector<ArenaPlayer>& players_vec)
{
    if (this->InArena(arena))
    {
        for (ArenaPlayer& current_player : players_vec)
        {
            if (&current_player == this) continue;

            PositionDefinition current_player_pos = current_player.GetPos();
            double player_distance_from_current_player = this->SquareDistanceTo(
                current_player_pos.GetX(),
                current_player_pos.GetY()
            );
            double limit = current_player.Hitbox() + this->Hitbox();
            if (player_distance_from_current_player <= limit * limit)
            {
                return true;
            }
        }
    }
    else
    {
        return true; //Player somehow escaped the arena ??? useful for debug I imagine
    }

    return false;  
}