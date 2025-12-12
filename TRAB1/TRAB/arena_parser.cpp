#include "arena_parser.h"

std::optional<CircularArena> arena_getter(std::vector<CircleDefinition>& svg_circles)
{
    for (CircleDefinition& circle : svg_circles)
    {
        if (circle.GetColor() == "blue")
        {
            return CircularArena(
                circle.GetPosition().GetX(),
                circle.GetPosition().GetY(),
                circle.GetRadius(),
                circle.GetColor()
            );
        }
    }

    return std::nullopt;
}

std::optional<std::vector<ArenaPlayer>> players_getter(std::vector<CircleDefinition>& svg_circles)
{
    std::vector<ArenaPlayer> players_vec;
    int id = 0;
    for (CircleDefinition& circle : svg_circles)
    {
        if (circle.GetColor() == "red" || circle.GetColor() == "green")
        {
            players_vec.push_back(
                ArenaPlayer(
                    circle.GetPosition().GetX(),circle.GetPosition().GetY(),0,
                    circle.GetColor(),
                    0,0,0,
                    circle.GetRadius(),
                    id++
                )
            );

        }
    }

    if (players_vec.size() > 0)
    {
        return players_vec;
    }

    return std::nullopt;
}

std::optional<std::vector<CircularObstacle>> obstacles_getter(std::vector<CircleDefinition>& svg_circles)
{
    std::vector<CircularObstacle> obstacles_vec;
    for (CircleDefinition& circle : svg_circles)
    {
        if (circle.GetColor() == "black")
        {
            obstacles_vec.push_back(
                CircularObstacle(
                    circle.GetPosition().GetX(),
                    circle.GetPosition().GetY(),
                    circle.GetRadius(),
                    circle.GetColor()
                )
            );
        }
    }

    if (obstacles_vec.size() > 0)
    {
        return obstacles_vec;
    }

    return std::nullopt;
}