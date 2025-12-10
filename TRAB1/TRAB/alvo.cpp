#include "alvo.h"
#include <stdio.h>
#include <math.h>
#define RADIANS (M_PI / 180.0)

void Alvo::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
    glBegin(GL_POLYGON);
        for (double i = 0.0; i <= 360.0; i+= 20.0 )
        {
            glColor3f (R, G, B);
            glVertex3f (radius * cos(i*RADIANS), radius * sin(i*RADIANS), 0.0);
        }
   glEnd();
}

void Alvo::DesenhaAlvo(GLfloat x, GLfloat y)
{
    GLfloat R = 0.0;
    GLfloat G = 0.0;
    GLfloat B = 0.0;

    if (gColor == 0) R = 1.0;
    else if (gColor == 1) G = 1.0;
    else if (gColor == 2) B = 1.0;
    if (gColor == 3) gColor = 0;

    // printf("R : %.2f | G : %.2f | B : %.2f \n",R,G,B);

    glPushMatrix();
        glTranslatef(x,y,0);
        DesenhaCirc(radiusAlvo,R,G,B);
    glPopMatrix();
}

void Alvo::Recria(GLfloat x, GLfloat y)
{
    gColor++;
    glPushMatrix();
        glTranslatef(gX,gY,0);
        DesenhaCirc(radiusAlvo,0.0,0.0,0.0);
    glPopMatrix();

    DesenhaAlvo(x,y);
    
    gX = x;
    gY = y;

}

bool Alvo::Atingido(Tiro *tiro)
{
    GLfloat tiro_x;
    GLfloat tiro_y;

    tiro->GetPos(tiro_x,tiro_y);

    if ( ( tiro_x >= (gX - radiusAlvo)) && ( tiro_x < (gX + radiusAlvo)) )
    {
        if ( (tiro_y >= (gY - radiusAlvo)) && ( tiro_y < (gY + radiusAlvo)) )
        {
            return true;
        }
    }

    return false;
}
