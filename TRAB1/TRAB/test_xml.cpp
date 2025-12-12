// https://github.com/leethomason/tinyxml2

#include "utils.h"
#include "arena.h"
#include "arena_parser.h"

using namespace tinyxml2;

int main(int argc,char** argv)
{
    if (argc < 2)
    {
        printf("Insira o caminho para o SVG!\n");
        return 1;
    }
    if (argc > 2)
    {
        printf("Apenas insira o caminho para o SVG!\n");
        return 2;   
    }

    std::vector<CircleDefinition> circle_vec = svg_parser(argv[1]);

    // if (circle_vec.size() != 0)
    // {
    //     for (CircleDefinition& obj : circle_vec)
    //     {
    //         obj.PrintAttributes();
    //     }
    // }

    std::optional<CircularArena>  arena = arena_getter(circle_vec);
    if (arena)
    {
        printf("Arena: \n");
        arena->PrintAttributes();
        printf("\n\n");
    }

    std::optional<std::vector<ArenaPlayer>> players = players_getter(circle_vec);
    if (players)
    {
        int i = 0;
        for ( ArenaPlayer& p : *players)
        {
            printf("Player %d: \n",(i++)+1);
            p.PrintAttributes();
            printf("\n\n");
        }
    }

    std::optional<std::vector<CircularObstacle>> obstacles = obstacles_getter(circle_vec);
    if (obstacles)
    {
        int i = 0;
        for ( CircularObstacle& obs : *obstacles)
        {
            printf("Obstacle %d: \n",(i++)+1);
            obs.PrintAttributes();
            printf("\n\n");
        }
    }


    return 0;
}