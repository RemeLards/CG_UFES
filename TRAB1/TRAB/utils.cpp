#include "utils.h"

void CircleDefinition::PrintAttributes()
{
    printf(" Circle:");
    printf(" cx: %.2f|", cx);
    printf(" cy: %.2f|", cy);
    printf(" radius: %.2f|", radius);
    printf(" color: %s", color.c_str());
    printf("\n\n");
}