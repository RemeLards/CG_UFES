#include "tiro.h"
#include <math.h>
#define DISTANCIA_MAX 500
#define RADIANS (M_PI / 180.0)

void Tiro::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{

    glBegin(GL_POLYGON);
        for (double i = 0.0; i <= 360.0; i+= 20.0 )
        {
            glColor3f (R, G, B);
            glVertex3f (radius * cos(i*RADIANS), radius * sin(i*RADIANS), 0.0);
        }
   glEnd();

}

void Tiro::DesenhaTiro(GLfloat x, GLfloat y)
{
    glPushMatrix();
        glTranslatef(x,y+radiusTiro/2,0);
        DesenhaCirc(radiusTiro,1.0,0,0);
    glPopMatrix();
}

void Tiro::Move()
{
    gX += gVel * cos(gDirectionAng * RADIANS);
    gY += gVel * sin(gDirectionAng * RADIANS);
}

bool Tiro::Valido()
{
    float deltaX = gX - gXInit;
    float deltaY = gY - gYInit;

    return ((deltaX * deltaX + deltaY * deltaY) < DISTANCIA_MAX * DISTANCIA_MAX);
}
