#ifndef CIRCULAR_ARENA_H
#define CIRCULAR_ARENA_H

#include <cmath>
#include <string>

// Por enquanto a Denifição de Círculo está aqui, depois trocar
#include "utils.h"

class CircularArena {
private:
    CircleDefinition arena;

public:
    CircularArena(CircleDefinition c)
        : arena(c) {}

    void DrawArena();

    double GetX(){ return arena.GetX()}
    double GetY(){ return arena.GetY()}
    double GetRadius(){ return arena.GetRadius()}
    
};

#endif