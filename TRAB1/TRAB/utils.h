#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <iostream>
#include <vector>

#include "tinyxml2.h"

// --------------------------------------------- //

class PositionDefinition
{
    private:
        double _x;
        double _y;
        double _z;

    public:
        PositionDefinition(double x,double y, double z) 
            : _x(x),_y(y),_z(z) {};
        
        double GetX() const { return _x; };
        double GetY() const { return _y; };
        double GetZ() const { return _z; };

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
        
        double GetVx() const { return _vx; };
        double GetVy() const { return _vy; };
        double GetVz() const { return _vz; };

        void SetVx(double vx) { _vx = vx; };
        void SetVy(double vy) { _vy = vy; };
        void SetVz(double vz) { _vz = vz; };
};

// --------------------------------------------- //

class ObjectDefinition
{
    private:
        PositionDefinition position;
        std::string color;
        double r,g,b;
    public:
        ObjectDefinition(double x, double y, double z,const std::string& color)
            : position{x, y, z}, color(color) {}
        
        const std::string& GetColor() const { return color; };
        void SetColor(const std::string& c) { color = c; };
        PositionDefinition& GetPosition() { return position; }
        
        void PrintAttributes();
};


class CircleDefinition : public ObjectDefinition
{
    private:
        double _radius;  
    public:
        CircleDefinition(double cx, double cy, double radius, const std::string& color)
            : ObjectDefinition(cx,cy,0,color), _radius(radius) {};
        
        double GetRadius() const { return _radius; };
        void SetRadius(double r) { _radius = r; };
        
};

// --------------------------------------------- //

class EntityDefinition : public ObjectDefinition
{
    private:
        VelocityDefinition velocity;

    public:
        EntityDefinition(
            double x, double y, double z,
            const std::string& color,
            double vx, double vy, double vz
        ) : ObjectDefinition(x, y, z, color), velocity{vx, vy, vz}
        {};

        VelocityDefinition& GetVelocity() { return velocity; }
};

class CircularEntityDefinition : public EntityDefinition
{
    private:
        double _radius;

    public:
        CircularEntityDefinition(
            double x, double y, double z,
            const std::string& color,
            double vx, double vy, double vz,
            double radius
        ) : EntityDefinition(x, y, z, color,vx,vy,vz), _radius(radius)
        {};

        double GetRadius() const { return _radius; };
        void SetRadius(double r) { _radius = r; };
};

// --------------------------------------------- //

std::vector<CircleDefinition> svg_parser(const char* path);

#endif