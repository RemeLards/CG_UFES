#ifndef BULLET_H
#define	BULLET_H

#include <GL/gl.h>
#include <GL/glu.h>

#include "utils.h"

#define radiusTiro 5

class Bullet
{
    VelocityDefinition _vel;
    PositionDefinition _pos;
    CircleDefinition _bullet;

private:
    void DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void DesenhaTiro(PositionDefinition pos);
public:
    Bullet(VelocityDefinition vel, PositionDefinition pos, CircleDefinition bullet)
    : _vel(vel),
      _pos(pos),
      _bullet(bullet)
      {};
    void Desenha(){ 
        DesenhaTiro(_pos);
    };
    void Move(GLdouble timeDiference);
    bool Valido();
    //void GetPos(GLfloat &xOut, GLfloat &yOut){
    //    xOut = gX;
    //    yOut = gY;
    //};
};

#endif	/* TIRO_H */

