#include "player.h"

#define BULLET_VEL 2
#define BULLET_RADIUS 2

// void ArenaPlayer::DeleteBullet(std::size_t index)
// {
//     Bullet* ptr = this->bullet_vec[index];
//     this->bullet_vec.erase(this->bullet_vec.begin() + index);
//     delete ptr;
// }
//  Player interaction -> Moving, Rotating and Shooting

void ArenaPlayer::DrawBody()
{
    glPushMatrix();
        DrawEllipseWithBorder(
            2*this->GetRadius(),0.5*this->GetRadius(),
            this->GetRGB().GetR(),this->GetRGB().GetG(),this->GetRGB().GetB()
        );
        DrawCircWithBorder(
            this->GetRadius(),
            this->GetRGB().GetR(),this->GetRGB().GetG(),this->GetRGB().GetB()
        );
    glPopMatrix();
}


void ArenaPlayer::DrawPlayer()
{
    glPushMatrix();
        glTranslatef(
            this->GetPosition().GetX(),
            -this->GetPosition().GetY(),
            0
        );
        this->DrawBody();
    // this->GetPosition().PrintAttributes();
    glPopMatrix();
}

void ArenaPlayer::MoveInX(
    CircularArena& arena,
    std::vector<CircularObstacle>& obstacles_vec, 
    std::vector<ArenaPlayer>& player_vec,
    double dx)
{
    this->last_pos = this->GetPosition();
    this->GetPosition().SetX(this->GetPosition().GetX() + dx);

    if ( this->ArenaCollision(arena) || 
         this->ObstacleCollision(arena,obstacles_vec) || 
         this->PlayerCollision(arena,player_vec)
    )
    {
        this->GetPosition() = last_pos;
        return;
    }
}

void ArenaPlayer::MoveInY(
    CircularArena& arena,
    std::vector<CircularObstacle>& obstacles_vec,
    std::vector<ArenaPlayer>& player_vec, 
    double dy)
{
    this->last_pos = this->GetPosition();
    this->GetPosition().SetY(this->GetPosition().GetY() + dy);
    
    if ( this->ArenaCollision(arena) || 
         this->ObstacleCollision(arena,obstacles_vec) || 
         this->PlayerCollision(arena,player_vec)
    )
    {
        this->GetPosition() = this->last_pos;
        return;
    }
}

void ArenaPlayer::Shoot(double pos_x, double pos_y)
{
    // Fazer transformações
    Bullet* bullet = new Bullet(
        0,0,0,"yellow",
        BULLET_VEL*cos(gun_yaw),BULLET_VEL*sin(gun_yaw),0,
        BULLET_RADIUS,this->GetId()
    );

    this->bullet_vec.push_back(bullet);
}


// Collision


double ArenaPlayer::SquareDistanceTo(double x, double y)
{
    double dx = fabs(x - this->GetPosition().GetX());
    double dy = fabs(y - this->GetPosition().GetY());

    return (dx*dx + dy*dy);
}

bool ArenaPlayer::InArena(CircularArena& arena)
{
    return (
        this->SquareDistanceTo(arena.GetPosition().GetX(),arena.GetPosition().GetY()) 
        <= arena.GetRadius()*arena.GetRadius()
    );
}

bool ArenaPlayer::ArenaCollision(CircularArena& arena)
{
    if (this->InArena(arena))
    {
        double player_distance_from_arena_center = this->SquareDistanceTo(
            arena.GetPosition().GetX(),
            arena.GetPosition().GetY()
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
                obstacle.GetPosition().GetX(),
                obstacle.GetPosition().GetY()
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

            double player_distance_from_current_player = this->SquareDistanceTo(
                current_player.GetPosition().GetX(),
                current_player.GetPosition().GetY()
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

// Bullet* ArenaPlayer::BulletCollision(std::vector<Bullet*> bullet_vec)
// {
//     for (Bullet*& bullet : bullet_vec)
//     {
//         double player_distance_from_current_player = this->SquareDistanceTo(
//             bullet->GetX(),
//             bullet->GetY()
//         );
//         double limit = bullet->GetRadius() * bullet->GetRadius();
//         if ( player_distance_from_current_player <=  limit )
//         {
//             return bullet;
//         }
//     }

//     return NULL;
// }