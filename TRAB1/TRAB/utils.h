#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string>

class CircleDefinition
{
    private:
        double cx;
        double cy; 
        double radius;  
        std::string color;
    public:
        CircleDefinition(double cx, double cy, double radius, const std::string& color)
            : cx(cx), cy(cy), radius(radius), color(color) {}
        
        double GetX() const { return cx; }
        double GetY() const { return cy; }
        double GetRadius() const { return radius; }
        const std::string& GetColor() const { return color; }

        void SetX(double x) { cx = x; }
        void SetY(double y) { cy = y; }
        void SetRadius(double r) { radius = r; }
        void SetColor(const std::string& c) { color = c; }

        void PrintAttributes();
};

class PositionDefinition
{
    private:
        double x;
        double y;
        double z;

    public:
        PositionDefinition(double x,double y, double z) 
            : x(x),y(y),z(z) {}
        
        GetX() { return x; }
        GetY() { return y; }
        GetZ() { return z; }
}

#endif