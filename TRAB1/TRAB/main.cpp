#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


#include "robo.h"
#include "alvo.h"

#include "utils.h"
#include "arena_parser.h"
#include "arena.h"
#include "arena_obstacles.h"
#include "player.h"
#include "bullet.h"

#include <vector>
#include <string>
#include <stdio.h>
#include <math.h>

#include <stdlib.h>

#define INC_KEY 10 
#define INC_MOVEKEYIDLE -0.08 // Para mover para cima e para baixo se mantenha consistente

// debug
int debug = 0;

//Key status
int keyStatus[256];

// Window dimensions
const GLint Width = 500;
const GLint Height = 500;

// View
GLint VWidth;
GLint VHeight;

// Arena,Obstacles and Players
CircularArena g_arena;
std::vector<CircularObstacle> g_obstacles;
std::vector<ArenaPlayer> g_players;
GLdouble last_time_record_state = 0;
std::vector<PositionDefinition> last_players_recorded_pos;

#define LEG_ANIMATION_DELAY_MS 350.0

//Controla a animacao do robo
int animate = 0;

// Counts how many times the ball was hit
int atingido = 0;
static char str[1000];
void * font = GLUT_BITMAP_9_BY_15;

//Componentes do mundo virtual sendo modelado
Robo robo; //Um rodo
Tiro * tiro = NULL; //Um tiro por vez
Alvo alvo(0, 200); //Um alvo por vez

bool IsPlayerMoving(PositionDefinition p_pos, PositionDefinition saved_pos)
{
    return(
        p_pos.GetX()-saved_pos.GetX() +
        p_pos.GetY()-saved_pos.GetY() +
        p_pos.GetZ()-saved_pos.GetZ() != 0
    );
}

void ImprimePlacar(GLfloat x, GLfloat y)
{
    glColor3f(1.0, 1.0, 1.0);
    //Cria a string a ser impressa
    char *tmpStr;
    sprintf(str, "Atingido: %d", atingido );
    //Define a posicao onde vai comecar a imprimir
    glRasterPos2f(x, y);
    //Imprime um caractere por vez
    tmpStr = str;
    while( *tmpStr ){
        glutBitmapCharacter(font, *tmpStr);
        tmpStr++;
    }
}

void renderScene(void)
{
    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT);

        g_arena.DrawArena();

        for ( CircularObstacle& obstacle : g_obstacles)
        {
            obstacle.DrawObstacle();
        }

        for ( ArenaPlayer& obstacle : g_players)
        {
            obstacle.DrawPlayer();
        }
        // robo.Desenha();        
        // if (tiro) tiro->Desenha();
        
        // alvo.Desenha();

        // ImprimePlacar(-230.0,230.0);

    glutSwapBuffers(); // Desenha the new frame of the game.
}

void keyPress(unsigned char key, int x, int y)
{
    switch (key)
    {
        case '1':
             animate = !animate;
             break;
        case 'w':
        case 'W':
             keyStatus[(int)('w')] = 1; //Using keyStatus trick
             break;
        case 's':
        case 'S':
             keyStatus[(int)('s')] = 1; //Using keyStatus trick
             break;
        case 'a':
        case 'A':
             keyStatus[(int)('a')] = 1; //Using keyStatus trick
             break;
        case 'd':
        case 'D':
             keyStatus[(int)('d')] = 1; //Using keyStatus trick
             break;
            
        case 'f':
        case 'F':
             robo.RodaBraco1(-INC_KEY);   //Without keyStatus trick
             break;
        case 'r':
        case 'R':
             robo.RodaBraco1(+INC_KEY);   //Without keyStatus trick
             break;
        case 'g':
        case 'G':
             robo.RodaBraco2(-INC_KEY);   //Without keyStatus trick
             break;
        case 't':
        case 'T':
             robo.RodaBraco2(+INC_KEY);   //Without keyStatus trick
             break;
        case 'h':
        case 'H':
             robo.RodaBraco3(-INC_KEY);   //Without keyStatus trick
             break;
        case 'y':
        case 'Y':
             robo.RodaBraco3(+INC_KEY);   //Without keyStatus trick
             break;
        case ' ':
             if (!tiro)
                tiro = robo.Atira();
             break;
        case 27 :
             exit(0);
    }
    glutPostRedisplay();
}

void keyup(unsigned char key, int x, int y)
{
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}

void ResetKeyStatus()
{
    int i;
    //Initialize keyStatus
    for(i = 0; i < 256; i++)
       keyStatus[i] = 0; 
}

void idle(void)
{
    static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble currentTime, timeDiference;

    //Pega o tempo que passou do inicio da aplicacao
    currentTime = glutGet(GLUT_ELAPSED_TIME);

    // Calcula o tempo decorrido desde de a ultima frame.
    timeDiference = currentTime - previousTime;

    //Atualiza o tempo do ultimo frame ocorrido
    previousTime = currentTime;

    if ((currentTime-last_time_record_state) >= LEG_ANIMATION_DELAY_MS)
    {
        // printf("current time: %.2f\n",currentTime);
        // printf("last time diff : %.2f\n",last_time_record_state);
        // printf("time diff : %.2f\n",currentTime-last_time_record_state);
        for (unsigned int i = 0; i < g_players.size(); i++)
        {
            if(IsPlayerMoving(g_players[i].GetPosition(),last_players_recorded_pos[i]))
            {
                g_players[i].IsMoving(true);
                last_players_recorded_pos[i] =  g_players[i].GetPosition();
                if (g_players[i].GetLastLeg() == RIGHT_LEG_ID)
                {
                    g_players[i].SetCurrentLeg(LEFT_LEG_ID);
                }
                else g_players[i].SetCurrentLeg(RIGHT_LEG_ID);
            }
            else g_players[i].IsMoving(false);
        }
        last_time_record_state = currentTime;
    }

    double inc = INC_MOVEKEYIDLE;
    //Treat keyPress
    if(keyStatus[(int)('w')])
    {
        ArenaPlayer& p1 = g_players[0];
        p1.MoveInY(g_arena,g_obstacles,g_players,inc*timeDiference);
    }
    if(keyStatus[(int)('s')])
    {
        ArenaPlayer& p1 = g_players[0];
        p1.MoveInY(g_arena,g_obstacles,g_players,-inc*timeDiference);
    }
    if(keyStatus[(int)('a')])
    {
        ArenaPlayer& p1 = g_players[0];
        p1.MoveInX(g_arena,g_obstacles,g_players,inc*timeDiference);
    }
    if(keyStatus[(int)('d')])
    {
        ArenaPlayer& p1 = g_players[0];
        p1.MoveInX(g_arena,g_obstacles,g_players,-inc*timeDiference);
    }
    
    //Trata o tiro (soh permite um tiro por vez)
    //Poderia usar uma lista para tratar varios tiros
    if(tiro)
    {
        tiro->Move(timeDiference);

        //Trata colisao
        if (alvo.Atingido(tiro))
        {
            alvo.Recria(rand()%500 - 250, 200);
            delete tiro;
            tiro = NULL;
            atingido++; // increments the ammount of ball hits
        }
    }

    if (tiro)
    {
        if (!tiro->Valido())
        { 
            delete tiro;
            tiro = NULL;
        }
    }

    
    
    //Control animation
    if (animate){
        static int dir = 1;
        if (robo.ObtemX() > (VWidth/2)){
            dir *= -1;
        }
        else if (robo.ObtemX() < -(VWidth/2)){
            dir *= -1;
        }
        robo.MoveEmX(dir*INC_MOVEKEYIDLE);
    }
    
    glutPostRedisplay();
}


void gl_init()
{
    ResetKeyStatus();
    // The color the windows will redraw. Its done to erase the previous frame.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black, no opacity(alpha).
 
    glMatrixMode(GL_PROJECTION); // Select the projection matrix    
    glOrtho(-(VWidth/2),     // X coordinate of left edge             
            (VWidth/2),     // X coordinate of right edge            
            -(VHeight/2), //-(VHeight/2)     // Y coordinate of bottom edge            
            (VHeight/2),// (VHeight/2)     // Y coordinate of top edge
            -100,     // Z coordinate of the “near” plane            
            100);    // Z coordinate of the “far” plane
    glMatrixMode(GL_MODELVIEW); // Select the projection matrix    
    glLoadIdentity();
      
}

int load_svg(const char* path)
{
    // Get Circles
    std::vector<CircleDefinition> circle_vec = svg_parser(path);

    if (circle_vec.size() == 0)
    {
        return 3;
    }

    // Get Arena, Obstacles and Players
    std::optional<CircularArena>  arena = arena_getter(circle_vec);
    if (!(arena))
    {
        printf("Arena nao carregada corretamente!\n");
        return 4;   
    }

    std::optional<std::vector<CircularObstacle>> obstacles = obstacles_getter(circle_vec,*arena);
    std::optional<std::vector<ArenaPlayer>> players = players_getter(circle_vec,*arena);
    if (!(players))
    {
        printf("Jogadores nao carregados corretamente!\n");
        return 5;   
    }
    if (!(obstacles))
    {
        printf("Obstaculos nao carregados corretamente!\n");
        return 6;
    }

    g_arena = std::move(*arena);
    g_arena.GetPosition().SetX(0.0); // Arena beeing draw in the center of the axis
    g_arena.GetPosition().SetY(0.0); // Arena beeing draw in the center of the axis

    g_players = std::move(*players);
    g_obstacles = std::move(*obstacles);

    if (debug)
    {
        printf("Arena: \n");
        g_arena.PrintAttributes();
        printf("\n\n");

        int i = 0;
        for ( ArenaPlayer& p : g_players)
        {
            printf("Player %d: \n",(i++)+1);
            p.PrintAttributes();
            printf("\n\n");
        }

        i = 0;
        for ( CircularObstacle& obs : g_obstacles)
        {
            printf("Obstacle %d: \n",(i++)+1);
            obs.PrintAttributes();
            printf("\n\n");
        }

        g_arena.GetRGB().PrintAttributes();
    }
    return 0;
}
 
int main(int argc, char *argv[])
{
    // Parsing SVG

    if (argc < 2)
    {
        printf("Insira o caminho para o SVG!\n");
        return 1;
    }
    if (argc > 2)
    {
        printf("Apenas insira o caminho para o SVG!\n");
        return 2;   
    }

    int result = load_svg(argv[1]);
    if (result) return result;

    // Initialize openGL with Double buffer and RGB color without transparency.
    // Its interesting to try GLUT_SINGLE instead of GLUT_DOUBLE.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 
    // Create the window.
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(150,50);
    glutCreateWindow("Joguin 2D");
 
    // Define callbacks.
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyPress);
    glutIdleFunc(idle);
    glutKeyboardUpFunc(keyup);

    // Viewing Height=Width = Arena Diamater
    VHeight=VWidth=2*g_arena.GetRadius();
    gl_init();

    // Record Last Positions before start
    last_time_record_state=glutGet(GLUT_ELAPSED_TIME);
    for ( ArenaPlayer& player : g_players)
    {
        last_players_recorded_pos.push_back(player.GetPosition());
    }

    glutMainLoop();
 
    return 0;
}
