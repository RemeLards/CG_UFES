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

        void PrintAttributes();
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

        void PrintAttributes();
};

class RGBColor
{
    private:
        double _r;
        double _g;
        double _b;
    public:
        RGBColor() : _r(0), _g(0), _b(0) {};
        RGBColor(double r,double g, double b) : _r(r), _g(g), _b(b) {};

        double GetR() const {return _r;};
        double GetG() const {return _g;};
        double GetB() const {return _b;};

        void SetR(double r) {_r = r;};
        void SetG(double g) {_g = g;};
        void SetB(double b) {_b = b;};

        void PrintAttributes();
};

class StateDefinition : public PositionDefinition
{
    private:
        double _time;
    
    public:
        StateDefinition() : PositionDefinition(0,0,0),_time(0){};
        StateDefinition(double x, double y, double z, double time) 
            : PositionDefinition(x,y,y),_time(time){};
        
        double GetTime(){return _time;};

};

// --------------------------------------------- //

class ObjectDefinition
{
    private:
        PositionDefinition _position;
        std::string color;
        RGBColor rgb;
    public:
        ObjectDefinition(double x, double y, double z,const std::string& color)
            : _position{x, y, z}, color(color), rgb{}
            {
                this->SetRBGByColorName();
            }
        
        const std::string& GetColorName() const { return color; };
        void SetColorName(const std::string& c) { color = c; };
        void SetRBGByColorName();
        RGBColor& GetRGB() {return rgb;};

        PositionDefinition& GetPosition() { return _position; };

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