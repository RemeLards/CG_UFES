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
            : cx(cx), cy(cy), radius(radius), color(color) {};
        
        double GetX() const { return cx; };
        double GetY() const { return cy; };
        double GetRadius() const { return radius; };
        const std::string& GetColor() const { return color; };

        void SetX(double x) { cx = x; };
        void SetY(double y) { cy = y; };
        void SetRadius(double r) { radius = r; };
        void SetColor(const std::string& c) { color = c; };
        
        void PrintAttributes();
};

class PositionDefinition
{
    private:
        double _x;
        double _y;
        double _z;

    public:
        PositionDefinition(double x,double y, double z) 
            : _x(x),_y(y),_z(z) {};
        
        double GetX() { return _x; };
        double GetY() { return _y; };
        double GetZ() { return _z; };

        void SetX(double x) { _x = x; };
        void SetY(double y) { _y = y; };
        void SetZ(double z) { _z = z; };
};

class VelocityDefinition
{
    private:
        double _vx;
        double _vy;
        double _vz;

    public:
        VelocityDefinition(double vx,double vy, double vz) 
            : _vx(vx),_vy(vy),_vz(vz) {};
        
        double GetVx() { return _vx; };
        double GetVy() { return _vy; };
        double GetVz() { return _vz; };

        void SetVx(double vx) { _vx = vx; };
        void SetVy(double vy) { _vy = vy; };
        void SetVz(double vz) { _vz = vz; };
};

#endif