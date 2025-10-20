#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#define TAMANHO_JANELA 500

float gCurrentMouseX = 0;
float gCurrentMouseY = 0;
float gPastMouseX = 0;
float gPastMouseY = 0;

float gX = 0;
float gY = 0;

int keyStatus[256];
int mouseStatus=0;


// void mouse(int button, int state, int x, int y)
// {
//    gX = (x / ( (float) TAMANHO_JANELA )) - 0.25;
//    gY = ((TAMANHO_JANELA-y) / ((float) TAMANHO_JANELA)) - 0.25;

// }

void mouseMotion(int x,int y)
{
   gPastMouseX = gCurrentMouseX;
   gPastMouseY = gCurrentMouseY;
   gCurrentMouseX = (x / ( (float) TAMANHO_JANELA ));
   gCurrentMouseY = ((TAMANHO_JANELA-y) / ((float) TAMANHO_JANELA));

   if (gCurrentMouseX >= gX+0.25 && gCurrentMouseX <= gX+0.75)
   {
      if (gCurrentMouseY >= gY+0.25 && gCurrentMouseY <= gY+0.75)
      {
         gX += gCurrentMouseX - gPastMouseX;
         gY += gCurrentMouseY - gPastMouseY;
      }

      glutPostRedisplay();
   }

}

void globalmouseMotion(int x, int y)
{
   gPastMouseX = gCurrentMouseX;
   gPastMouseY = gCurrentMouseY;
   gCurrentMouseX = (x / ( (float) TAMANHO_JANELA ));
   gCurrentMouseY = ((TAMANHO_JANELA-y) / ((float) TAMANHO_JANELA));
}

void idle(void)
{
   if (keyStatus[(int)('w')] == 1) gY += 0.002;
   if (keyStatus[(int)('s')] == 1) gY -= 0.002;
   if (keyStatus[(int)('a')] == 1) gX -= 0.002;
   if (keyStatus[(int)('d')] == 1) gX += 0.002;


   
   glutPostRedisplay();
}

void keyPress(unsigned char key,int x,int y)
{
   if (key == 'w') keyStatus[(int)('w')] = 1; //gY += 0.02;
   if (key == 's') keyStatus[(int)('s')] = 1; //gY -= 0.02;
   if (key == 'a') keyStatus[(int)('a')] = 1; //gX -= 0.02;
   if (key == 'd') keyStatus[(int)('d')] = 1; //gX += 0.02;

   printf("key : %d",key);

   //glutPostRedisplay();
}

void keyUp(unsigned char key, int x, int y)
{
   if (key == 'w') keyStatus[(int)('w')] = 0;
   if (key == 's') keyStatus[(int)('s')] = 0;
   if (key == 'a') keyStatus[(int)('a')] = 0;
   if (key == 'd') keyStatus[(int)('d')] = 0;

   glutPostRedisplay();
}

void display(void)
{
   /* Limpar todos os pixels  */
   glClear (GL_COLOR_BUFFER_BIT);

   /* Define cor dos vértices com os valores R, G e B variando de 0.0 a 1.0 */
   glColor3f (1.0, 1.0, 1.0);
   /* Desenhar um polígono branco (retângulo) */
   glBegin(GL_POLYGON);
      glVertex3f (0.25+gX, 0.25+gY, 0.0);
      glVertex3f (0.75+gX, 0.25+gY, 0.0);
      glVertex3f (0.75+gX, 0.75+gY, 0.0);
      glVertex3f (0.25+gX, 0.75+gY, 0.0);
   glEnd();

   /* Desenhar no frame buffer! */
   glutSwapBuffers(); //Funcao apropriada para janela double buffer
}

void init (void) 
{
  /* selecionar cor de fundo (preto) */
  glClearColor (0.0, 0.0, 0.0, 0.0);

  /* inicializar sistema de visualizacao */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (TAMANHO_JANELA, TAMANHO_JANELA); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("hello world");
   init();

   // Callback Registration
   
   glutDisplayFunc(display); 
   glutKeyboardFunc(keyPress);
   glutKeyboardUpFunc(keyUp);
   glutIdleFunc(idle);
   // glutMouseFunc(mouse);
   glutMotionFunc(mouseMotion);
   glutPassiveMotionFunc(globalmouseMotion);
   

   // Main Loop

   glutMainLoop();

   return 0;
}
