#ifndef BULLET_H
#define	BULLET_H

#include <GL/gl.h>
#include <GL/glu.h>

#include "utils.h"
#include "player.h"

#define radiusTiro 5

class ArenaPlayer;

class Bullet
{
    VelocityDefinition _vel;
    PositionDefinition _pos;
    CircleDefinition _bullet;
    int _owner;

private:
    void DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void DesenhaTiro(PositionDefinition pos);
public:
    Bullet(VelocityDefinition vel, PositionDefinition pos, CircleDefinition bullet, int owner)
    : _vel(vel),
      _pos(pos),
      _bullet(bullet),
      _owner(owner) 
      {};
    void Desenha(){ 
        DesenhaTiro(_pos);
    };
    void Move(GLdouble timeDiference);
    bool Valido();

    int GetOwner(){ return _owner;};
    void Delete(ArenaPlayer& player);

    bool PlayerCollision(ArenaPlayer& player);
    //void GetPos(GLfloat &xOut, GLfloat &yOut){
    //    xOut = gX;
    //    yOut = gY;
    //};
    double GetX() { return this->_pos.GetX(); };
    double GetY() { return this->_pos.GetY(); };
    double GetRadius() { return this->_bullet.GetRadius(); };
};

#endif	/* TIRO_H */

