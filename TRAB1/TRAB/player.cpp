#include "player.h"

double ArenaPlayer::SquareDistanceTo(double x, double y)
{
    double dx = fabs(x - player_head.GetX());
    double dy = fabs(y - player_head.GetY());

    return (dx*dx + dy*dy);
}

bool ArenaPlayer::InArena(CircularArena arena)
{
    return (SquareDistanceTo(arena.GetX(),arena.GetY()) <= arena.GetRadius()*arena.GetRadius())
}

bool ArenaPlayer::ArenaCollision(CircularArena arena)
{
    if (InArena(arena))
    {
        double player_distance_from_arena_center = SquareDistanceTo(arena.GetX(),arena.GetY());
        double equivalent_radius = arena.getRadius() - player_head.GetRadius();
        return ( player_distance_from_arena_center <= (equivalent_radius*equivalent_radius))
    }
    return false;
}

// Obstacles should only exist inside the Arena
bool ArenaPlayer::ObstacleCollsion(CircularArena arena, CircularObstacle obstacle)
{
    if (InArena(arena))
    {
        double player_distance_from_obstacle_center = SquareDistanceTo(obstacle.GetX(),obstacle.GetY());
        return ( player_distance_from_obstacle_center <= (obstacle.GetRadius()))
    }

    return false;
}