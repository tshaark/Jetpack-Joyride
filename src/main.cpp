#include "main.h"
#include "timer.h"
#include "ball.h"
#include "platform.h"
#include "coins.h"
#include "bonuscoin.h"
#include "firelines.h"
#include "firebeam.h"
#include "boomerang.h"
#include "magnet.h"
#include "splflying.h"
#include "waterballoon.h"
#include "score.h"
#include "tunnel.h"
#include "viserion.h"
#include "ninjastars.h"
#include "livesdisplay.h"
#include "lives.h"
#include <ctime>

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;


/**************************
* Customizable functions *
**************************/

Ball ball1;
Platform p;
Tunnel t[10];
int tFlag;
int lives=3;
double angle=180.0;
Score s[4]; 
Livesdisplay l;
Coins c[200];
Bonuscoin b[100];
Firelines f[100];
Firebeam fb[50];
Boomerang br[20];
Magnet mag[50];
Splflying spl[20];
Lives lv[6];
Viserion v;
std::vector<Waterballoon> wb;
std::vector<Ninjastars> ns;
std::vector<int> wflag;
std::vector<int> nflag;

int timer;
float timer1=0;
int flag=0;
int spFlag[20];
int lvFlag[6];
int fFlag[105];
int fbFlag[55];
int flag1=0;
int flag2=0;
int tOn[10];
int cFlag[2000];
int bFlag[1000];
int score;
float screen_zoom = 1.0, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float xEye = 0;
float x=0;
Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( xEye,0,10);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (xEye, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model
    int tens=1;
    // Scene rendera
    ball1.draw(VP);
    p.draw(VP);
    v.draw(VP);
    for (int i = 0; i < 10; ++i)
    {
        t[i].draw(VP);      /* code */
    }
    for (int i = 0; i < 4; ++i)
    {
        s[i].draw(VP,(score/tens)%10);
        tens*=10;
    } 
    l.draw(VP,lives);
    for(int i=0;i<200;i++)
    {
        if(cFlag[i]!=1)
        c[i].draw(VP);
    }
    for(int i=0;i<100;i++)
    {
        if(bFlag[i]!=1)
        b[i].draw(VP);
    }
    for(int i=0;i<100;i++)
    {
        if(fFlag[i])
            f[i].draw(VP);
    }
    for(int i=0;i<50;i++)
    {
        if(fbFlag[i])
            fb[i].draw(VP);
    }
    for(int i=0;i<20;i++)
    {
        br[i].draw(VP);    
    }
    for(int i=0;i<50;i++)
    {
        mag[i].draw(VP);    
    }
    for(int i=0;i<20;i++)
    {
        if(!spFlag[i])
            spl[i].draw(VP);    
    }
    for(int i=0;i<6;i++)
    {
        if(!lvFlag[i])
            lv[i].draw(VP);    
    }
    for(int i=0;i<wb.size();i++)
    {
        if(wflag[i])
            wb[i].draw(VP);
    }
    for(int i=0;i<ns.size();i++)
    {
        if(nflag[i])
            ns[i].draw(VP);
    }
}

void tick_input(GLFWwindow *window) {
    int up      = glfwGetKey(window, GLFW_KEY_SPACE);
    int down    = glfwGetKey(window, GLFW_KEY_DOWN);
    int left    = glfwGetKey(window, GLFW_KEY_LEFT);
    int right   = glfwGetKey(window, GLFW_KEY_RIGHT);
    int zoomIn  = glfwGetKey(window, GLFW_KEY_W);
    int zoomOut = glfwGetKey(window, GLFW_KEY_S);
    int shoot   = glfwGetKey(window, GLFW_KEY_Z);

    if (zoomIn){
        screen_zoom+=0.01;
    }
    if (zoomOut){
        if(screen_zoom>=0.5)       
        screen_zoom-=0.01;
    }
    if (left) {
        ball1.position.x-=0.25;
        xEye-=0.25;
        ball1.speedX=-0.1;
    }
    if (right){
        ball1.position.x+=0.25;
        xEye+=0.25;
        ball1.speedX=0.1;
    }
    int currYPosition = ball1.position.y;
    if (up){
        if (currYPosition < 3)
        {
            ball1.speedY+=0.150;
            ball1.position.y+=0.25;
        }
    }
    if (shoot && timer==0){
        timer=1;
        wb.push_back(Waterballoon(ball1.position.x,ball1.position.y,COLOR_DEEPSKYBLUE));
        wflag.push_back(1);
    }
}

void tick_elements() {
    ball1.tick(flag);
    v.tick(flag2);
    for (int i = 0; i < 200; ++i)
    {
       if(cFlag[i]!=1)
        c[i].tick();    
    }
    for (int i = 0; i < 100; ++i)
    {
        if(bFlag[i]!=1)
        b[i].tick();    
    }
    for (int i = 0; i < 50; ++i)
    {
        if(fbFlag[i])
        fb[i].tick(flag1);    
    }
    for (int i = 0; i < 20; ++i)
    {
        br[i].tick();    
    }
    for (int i = 0; i < 20; ++i)
    {
        if(!spFlag[i])
            spl[i].tick();    
    }
    for (int i = 0; i < 6; ++i)
    {
        if(!lvFlag[i])
            lv[i].tick();    
    }
    if(timer)
        timer++;
    if(timer>=60)
        timer=0;
    
    for (int i = 0; i < wb.size(); ++i)
    {
        if(wflag[i])
        {
            wb[i].tick();
        }    
        if(wb[i].position.y<=-5)
            wflag[i]=0;
    }
    for (int i = 0; i < ns.size(); ++i)
    {
        if(nflag[i])
        {
            ns[i].tick();
        }    
        if(ns[i].position.y<=-5)
            nflag[i]=0;
    }
    camera_rotation_angle += 0;
}


/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1       = Ball(0,-3,0,0, COLOR_RED);
    p           =Platform(0.0,0.0,COLOR_GREEN);
    v           =Viserion(100.0,0.0,COLOR_BLUE,COLOR_BLACK,COLOR_GRAY);
    l           =Livesdisplay(3.5,3.0,COLOR_BLACK);
    int xT = 10.0;
    for (int i = 0; i < 10; ++i)
    {
        t[i]=Tunnel(xT,0.0,COLOR_BLACK);
        xT+=50.0;
    }
    for (int i = 0; i < 4; ++i)
    {
        s[i]=Score(-4.0+0.5*(4-i),3.0,COLOR_BLACK);
    }
    for (int i = 0; i < 200; ++i)
    {
        c[i]= Coins(rand()%5000,rand()%4,COLOR_GOLD);    
    }
    for (int i = 0; i < 100; ++i)
    {
        b[i]= Bonuscoin(rand()%5000,rand()%4,COLOR_PINK);    
    }
    for (int i = 0; i < 100; ++i)
    {
        f[i]= Firelines(rand()%360,rand()%5000,rand()%4,COLOR_GRAY);  
        fFlag[i]=1;  
    }
    for (int i = 0; i < 50; ++i)
    {
        fb[i]= Firebeam(rand()%5000,rand()%4,COLOR_NEONGREEN);   
        fbFlag[i]=1; 
    }
    for (int i = 0; i < 20; ++i)
    {
        br[i]= Boomerang(rand()%5000,2.0,COLOR_BLACK);    
    }
    for (int i = 0; i < 50; ++i)
    {
        mag[i]= Magnet(rand()%5000,rand()%4,COLOR_GRAY,COLOR_RED);    
    }
    for (int i = 0; i < 20; ++i)
    {
        spl[i]= Splflying(rand()%5000,2,COLOR_AQUA);    
    }
    for (int i = 0; i < 6; ++i)
    {
        lv[i]= Lives(10+i*100,2,COLOR_PINKRED);    
    }
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    // if(xEye<=100.0)
        glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
        // if(xEye>100.0 && ball1.position.x<200.0)
        //     glClearColor (COLOR_WOOD.r / 256.0, COLOR_WOOD.g / 256.0, COLOR_WOOD.b / 256.0, 0.0f); // R, G, B, A

    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 900;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);
        clock_t bt  = std::clock();

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        bounding_box_t b1,b2[2005],b3[1005],fbBox[55],brBox[21],tBox[10],spBox[20],lvBox[6];
        std::vector<bounding_box_t> wbBox;
        std::vector<bounding_box_t> nsBox;
        b1.x= ball1.position.x; 
        b1.y= ball1.position.y;
        float tim = (std::clock()- bt)/(float)CLOCKS_PER_SEC;

        if(v.position.x-ball1.position.x<=6 && v.position.x-ball1.position.x>=1 && tim>1.0)
        {
            bt = std::clock();
            ns.push_back(Ninjastars(v.position.x-1.5,v.position.y-1.0,COLOR_BLACK,COLOR_GRAY));
            nflag.push_back(1);
        }
        for(int i=0;i<10;i++)
        {
            tBox[i].x=t[i].position.x-1.5;
            tBox[i].y=t[i].position.y;
            tBox[i].width = tBox[i].height = 3.0f;
            if(detect_collision(b1,tBox[i]))
            {
                tFlag=1;
                tOn[i]=1;
            }
        }
        for(int i=0;i<20;i++)
        {
            spBox[i].x=spl[i].position.x;
            spBox[i].y=spl[i].position.y;
            spBox[i].height=0.5f;
            spBox[i].width=0.5f;
        }
        for (int i = 0; i < 20; ++i)
        {
            if(detect_collision(b1,spBox[i]) && !spFlag[i])
            {
                spFlag[i]=1;
                score+=20;
            }
        }
        for(int i=0;i<6;i++)
        {
            lvBox[i].x=lv[i].position.x;
            lvBox[i].y=lv[i].position.y;
            lvBox[i].height=0.5f;
            lvBox[i].width=0.5f;
        }
        for (int i = 0; i < 6; ++i)
        {
            if(detect_collision(b1,lvBox[i]) && !lvFlag[i])
            {
                lvFlag[i]=1;
                lives+=1;
            }
        }
        for(int i=0; i<200; i++) 
        {

            b2[i].x = c[i].position.x;
            b2[i].y = c[i].position.y;
            b2[i].width = b2[i].height = 1.0f;
        }
        for(int i=0; i<100; i++) 
        {

            b3[i].x = b[i].position.x;
            b3[i].y = b[i].position.y;
            b3[i].width = b3[i].height = 1.5f;
        }
        b1.width = b1.height = 0.5f;
        for(int i=0; i<50; i++) 
        {

            fbBox[i].x = fb[i].position.x+3.25;
            fbBox[i].y = fb[i].position.y;
            fbBox[i].width = 6.0f;
            fbBox[i].height = 0.25f;
            if(detect_collision(b1,fbBox[i]) && fbFlag[i]==1 && !tFlag)
            {
                if(lives==0)
                    quit(window);
                else
                {
                 
                    lives--;
                    ball1.position.y+=2.0;  

                }
            }
        }
        for(int i=0; i<20; i++) 
        {

            brBox[i].x = br[i].position.x;
            brBox[i].y = br[i].position.y-0.125;
            brBox[i].width = 1.0f;
            brBox[i].height = 0.75f;
            if(detect_collision(b1,brBox[i]) && !tFlag)
            {
                if(lives==0)
                    quit(window);
                else
                {
                    lives--;
                    ball1.position.x+=0.5;  
                }    
            }
        }
        for(int i=0;i<100;i++)
        {
            float dist1=ball1.position.x-f[i].position.x-ball1.position.y+f[i].position.y;
            if(dist1<0)
                dist1=-dist1;
            float dist=dist1/sqrt(2);
            if(dist<0.4 && ball1.position.x>=f[i].position.x+0.25 && ball1.position.x<=f[i].position.x+2 && fFlag[i]==1 && !tFlag)
            {
                if(lives==0)
                    quit(window);
                else
                {    
                    lives--;
                    ball1.position.x+=1.0;  
                }
                  
            }
        }
        for (int i = 0; i < wb.size(); ++i)
        {
            if(wflag[i]==1)
            {
                bounding_box_t temp;
                temp.x = wb[i].position.x;
                temp.y = wb[i].position.y;
                temp.height = 0.5f;
                temp.width = 0.5f;
                wbBox.push_back(temp);
            }
        }
        for(int j=0;j<wb.size();j++)
        {
          if(wflag[j]==1)
            for(int i=0;i<100;i++)
            {
                float dist1=wb[j].position.x-f[i].position.x-wb[j].position.y+f[i].position.y;
                if(dist1<0)
                    dist1=-dist1;
                float dist=dist1/sqrt(2);
                if(dist<0.4)
                {
                    fFlag[i]=0;
                }
            }
        }
        for (int i = 0; i < ns.size(); ++i)
        {
            if(nflag[i]==1)
            {
                bounding_box_t temp;
                temp.x = ns[i].position.x;
                temp.y = ns[i].position.y;
                temp.height = 0.5f;
                temp.width = 0.5f;
                nsBox.push_back(temp);
            }
        }
        for(int i=0;i<nsBox.size();i++)
        {
            if(detect_collision(b1,nsBox[i]))
            {   
                if(lives==0)
                    quit(window);
                else
                {
                    lives--;
                    ball1.position.x+=0.5;  
                    
                }
            }
        }
        // for(int j=0;j<wb.size();j++)
        // {
        //   if(wflag[j]==1)
        //     for(int i=0;i<50;i++)
        //     {
        //         float dist1=wb[j].position.x-fb[i].position.x-wb[j].position.y+fb[i].position.y;
        //         if(dist1<0)
        //             dist1=-dist1;
        //         float dist=dist1/sqrt(2);
        //         if(dist<0.1)
        //         {
        //             fbFlag[i]=0;
        //         }
        //     }
        // }
        for(int i=0; i<200; i++) { 
            if(detect_collision(b1,b2[i]) && !cFlag[i]) {
                score++;
                cFlag[i]=1;
                break;
            }
        }
        for(int i=0; i<100; i++) { 
            if(detect_collision(b1,b3[i]) && !bFlag[i]) {
                score+=2;
                bFlag[i]=1;
                break;
            }
        }
        for(int i=0;i<50;i++)
        {
            if(fb[i].position.y>=4)
                flag1=1;
            if(fb[i].position.y<=-3)
                flag1=0;
        }
        if(v.position.y>=3)
                flag2=1;
        if(v.position.y<=-2)
                flag2=0;
        for(int i=0;i<50;i++)
        {    
            float r=sqrt(((mag[i].position.x-ball1.position.x)*(mag[i].position.x-ball1.position.x))+((mag[i].position.y-ball1.position.y)*(mag[i].position.y-ball1.position.y)));
            float force;
            float forceX;
            float forceY;
            if(r!=0)
            {    force=0.00012/r*r;
                 forceX=(force*(mag[i].position.x-ball1.position.x)/r);
                 forceY=(force*(mag[i].position.y-ball1.position.y)/r);
            }
            if(r<6 && r!=0 && !tFlag)
            {
                ball1.position.x+=forceX;
                ball1.position.y+=forceY;
            }
        }
        // Process timers
        if(ball1.position.y <= -3)
            flag=1;
        else
            flag=0;
            if (t60.processTick()) {
                if(timer1)
                    timer1+=1.0/60.0;
                if(timer1>=3.0)
                    timer1=0.0;
                for (int i = 0; i < 4; ++i)
                {
                    s[i].position.x=xEye-4.0+(0.5*(4-i));    
                }
                l.position.x=xEye+3.5;
                for(int i=0;i<10;i++)
                    if (tFlag && angle>0.0 && tOn[i])
                    {
                        ball1.position.x=t[i].position.x+1.4*cos(angle*M_PI/180.0);
                        ball1.position.y=t[i].position.y+1.4*sin(angle*M_PI/180.0);
                        angle-=2.0;
                        if(angle==0.0) {
                            angle=180.0;
                            tFlag=0;
                            tOn[i]=0;
                        }
                    }
            // 60 fps
            // OpenGL Draw commands
                draw();
            // Swap Frame Buffer in double buffering
                glfwSwapBuffers(window);
                reset_screen();
                tick_elements();
                tick_input(window);
                
            }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    double temp=0.0;
    if(screen_zoom>1.0)
        temp=ball1.position.y;
    float top    = temp + 4 / screen_zoom;
    float bottom = temp - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
