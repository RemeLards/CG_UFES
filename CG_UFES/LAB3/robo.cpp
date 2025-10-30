#include "robo.h"
#include <math.h>

#define RADIANS (M_PI / 180.0)

void Robo::DesenhaRect(GLint height, GLint width, GLfloat R, GLfloat G, GLfloat B)
{
   /* Define cor dos vértices com os valores R, G e B variando de 0.0 a 1.0 */
   /* Desenhar um polígono vermelho (retângulo) */
   glBegin(GL_POLYGON);  
        glColor3f (R, G, B);
        glVertex3f (-width/2, 0.0, 0.0);
        glColor3f (R, G, B);
        glVertex3f (width/2, 0.0 , 0.0);
        glColor3f (R, G, B);
        glVertex3f (width/2, height, 0.0);
        glColor3f (R, G, B);
        glVertex3f (-width/2, height, 0.0);
   glEnd();

}

void Robo::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
    glBegin(GL_POINTS);
        for (double i = 0.0; i <= 360.0; i+= 20.0 )
        {
            glPointSize(4.0);
            glColor3f (R, G, B);
            glVertex3f (radius * cos(i*RADIANS), radius * sin(i*RADIANS), 0.0);
        }
   glEnd();
}

void Robo::DesenhaRoda(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat R, GLfloat G, GLfloat B)
{
    glPushMatrix();
        glTranslatef(x,y,0);
        glRotatef(thetaWheel,0,0,1.0);
        DesenhaCirc(radiusWheel,R,G,B);

        glRotatef(-thetaWheel,0,0,1.0);
        glTranslatef(baseWidth,y,0);
        glRotatef(thetaWheel,0,0,1.0);
        DesenhaCirc(radiusWheel,R,G,B);
    glPopMatrix();

}

void Robo::DesenhaBraco(GLfloat x, GLfloat y, GLfloat theta1, GLfloat theta2, GLfloat theta3)
{
    glPushMatrix();
        // Primeira Haste
        glTranslatef(x,y,0);
        glRotatef(theta1,0,0,1);
        DesenhaRect(paddleHeight,paddleWidth,0.0,0.0,1.0);

        // Segunda Haste
        glTranslatef(0,paddleHeight,0);
        glRotatef(theta2,0,0,1);
        DesenhaRect(paddleHeight,paddleWidth,0.0,1.0,0.0);

        // Terceira Haste
        glTranslatef(0,paddleHeight,0);
        glRotatef(theta3,0,0,1);
        DesenhaRect(paddleHeight,paddleWidth,1.0,1.0,0.0);


    glPopMatrix();
    
}

void Robo::DesenhaRobo(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat theta1, GLfloat theta2, GLfloat theta3)
{
    glPushMatrix();
        glTranslatef(x,y,0);
        DesenhaRect(baseHeight,baseWidth,1.0,0.0,0.0);
        DesenhaBraco(0,baseHeight,theta1,theta2,theta3);
        DesenhaRoda(-baseWidth/2,0,thetaWheel,1.0,1.0,1.0);
    glPopMatrix();
}

void Robo::RodaBraco1(GLfloat inc)
{
    gTheta1 += inc; 
}

void Robo::RodaBraco2(GLfloat inc)
{
    gTheta2 += inc;
}

void Robo::RodaBraco3(GLfloat inc)
{
    gTheta3 += inc;
}

void Robo::MoveEmX(GLfloat dx)
{
    gX += dx;
    gThetaWheel+= 10 * dx/radiusWheel;
}

//Funcao auxiliar de rotacao
void RotatePoint(GLfloat x, GLfloat y, GLfloat angle, GLfloat &xOut, GLfloat &yOut){

}

Tiro* Robo::Atira()
{
    GLfloat SpawnX  = gX // Robot Transform
                    + paddleHeight * sin(gTheta1 * RADIANS)  // First Haste Transform
                    + paddleHeight * sin((gTheta1+gTheta2) * RADIANS)  // Second Haste Transform
                    + paddleHeight * sin((gTheta1+gTheta2+gTheta3) * RADIANS);  // Third Haste Transform

    GLfloat SpawnY  = gY // Robot Transform
                    + baseHeight // Robot Height
                    + paddleHeight * cos(gTheta1 * RADIANS)  // First Haste Transform
                    + paddleHeight * cos((gTheta1+gTheta2) * RADIANS)  // Second Haste Transform
                    + paddleHeight * cos((gTheta1+gTheta2+gTheta3) * RADIANS);  // Third Haste Transform
    
    return  (Tiro*) (new Tiro(SpawnX,SpawnY,gTheta1+gTheta2+gTheta3+90)); // Hastes start with 90 degree rotation
}
