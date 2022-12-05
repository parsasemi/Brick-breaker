#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h> // window and renderer and basic configure
#include <SDL2/SDL_image.h> // loading BitMap images on window
#include <SDL2/SDL2_gfx.h> // extra useful function
#include <string>
#include <math.h>
#include <SDL2/SDL_ttf.h>
#include <cstring>
#include <string>
#include <fstream>
#include <SDL2/SDL_mixer.h>
using namespace std;
void chap(SDL_Renderer *Renderer,int x, int y, int digit);
void print_number(SDL_Renderer *Renderer,int x, int y, int number);
char * Printer (int score);

    SDL_Texture *digit0;
    SDL_Texture *digit1;
    SDL_Texture *digit2;
    SDL_Texture *digit3;
    SDL_Texture *digit4;
    SDL_Texture *digit5;
    SDL_Texture *digit6;
    SDL_Texture *digit7;
    SDL_Texture *digit8;
    SDL_Texture *digit9;

struct player
{
    string name;
    int level;
    int score;
    int lives;
    int history_score;

};


struct ball
{   int radius;
    double x;
    double y;
    double direction_x;
    double direction_y;
    int damage;
};
struct bar
{
    int x;
    int y;
    int w;
    int h;

};
struct brick
{   int x;
    int y;
    int w=130;
    int h=30;
    int level;
    int strength;

};
struct  game
{
    ball ball;
    player player;
    bar bar;
};

void window_color(SDL_Renderer *Renderer, int R, int G, int B);
void rect(SDL_Renderer *Renderer, int x,int y,int w,int h,int R, int G, int B, int fill_boolian );
void ellipse(SDL_Renderer *Renderer, int x, int y, int Radius1, int Radius2, int R, int G, int B, int fill_boolian);

int main( int argc, char * argv[] )
{
     SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
    Mix_Music *backgroundsound= Mix_LoadMUS("Alan Walker ft. Noah Cyrus & Digital Farm Animals - All Falls Down - MP3 128.mp3");
    Mix_Chunk *barkhord=Mix_LoadWAV("barkhord.wav");


    int command,flag_loadornew, flag_end=1, history_counter=0;

    game game;
    int ball_select=1;
    game.player.level=1;
    game.player.lives=3;
    game.player.score=0;
    brick brick[100][8];
//for loading the game
    ifstream in;
    ofstream out;
    int difficulty;
    string txt=".txt";
    cout<<"Please enter your name: "<<endl;
    cin>>game.player.name;
    game.player.name+=txt;
    int history_score[5]={0};
    in.open(game.player.name.c_str());
    if(!in.good())
    {
        cout<<"new game"<<endl;
        out.open(game.player.name.c_str());
        out.close();
        cout<<"choose a difficulty :"<<endl<<"1.easy"<<endl<<"2.medium"<<endl<<"3.hard"<<endl;
        cin>>difficulty;

        flag_loadornew=1;
    }
    else
    {


    for(int i=0; i<5; i++)
    {
        in>>history_score[i];
        if(history_score[i]!=0)
        {
            cout<<"history "<<i+1<<" : "<<history_score[i]<<endl;
            history_counter++;


        }
    }

        cout<<"Enter 1 for a new game, enter 2 for loading your last game... "<<endl;
        cin>>command;

        if(command==1)
        {
            flag_loadornew=1;

            cout<<"choose a difficulty :"<<endl<<"1.easy"<<endl<<"2.medium"<<endl<<"3.hard"<<endl;
            cin>>difficulty;
        }
        if(command==2)
        {
            flag_loadornew=2;
        }


    if(flag_loadornew==2)
    {
        in>>game.player.score>>game.player.level>>game.player.lives;


        for(int i=0;i<30;i++)
        {
            for(int j=0; j<8; j++)
            {
                in>>brick[i][j].strength;

            }
        }

        for(int i=0;i<30;i++)
        {
            for(int j=0; j<8; j++)
            {
                in>>brick[i][j].x;

            }
        }

        for(int i=0;i<30;i++)
        {
            for(int j=0; j<8; j++)
            {
                in>>brick[i][j].y;

            }
        }
    }

    }


 // MAIN WINDOW RISE
    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER ;
    Uint32 WND_flags = SDL_WINDOW_SHOWN;
    SDL_Window *m_window;


    SDL_Renderer *m_renderer;
    Mix_PlayMusic(backgroundsound,-1);
    Mix_VolumeMusic(70);
    SDL_Init( SDL_flags );
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    int W = DM.w;
    int H = DM.h;
    SDL_Event *event = new SDL_Event();

    int flag_ballmenu=1, flag_ball_1, flag_ball_2;

    //WINDOW 2
    SDL_Window *m_window2;
    SDL_Renderer *m_renderer2;

    //window 3
    SDL_Window *m_window3;
    SDL_Renderer *m_renderer3;
    SDL_CreateWindowAndRenderer( 1200, 700, WND_flags, &m_window3, &m_renderer3 );
    SDL_RaiseWindow(m_window3);


    //LOADING IMAGE
    SDL_Surface* gScreenSurface3 = NULL;
    SDL_Surface* gHelloWorld3 = NULL;

    SDL_Surface* gScreenSurface = NULL;
    SDL_Surface* gHelloWorld = NULL;

    gScreenSurface3 = SDL_GetWindowSurface( m_window3 );
    gHelloWorld3 = SDL_LoadBMP( "ball_menu_.bmp" );
    SDL_BlitSurface(gHelloWorld3,NULL,gScreenSurface3,NULL);



    while(flag_ballmenu==1)
        {

        SDL_UpdateWindowSurface( m_window3 );



    if( SDL_PollEvent( event ) )
        {
            //If a key was pressed
            if( event->type == SDL_KEYDOWN )
            {
                //Set the proper message surface
                switch( event->key.keysym.sym )
                {

                    case SDLK_1:
                        flag_ballmenu=0;
                        SDL_FreeSurface( gHelloWorld3 );
                        ball_select=1;
                        break;

                    case SDLK_2:
                        flag_ballmenu=0;
                        SDL_FreeSurface( gHelloWorld3 );
                        ball_select=2;
                        break;

                    case SDLK_3:
                        flag_ballmenu=0;
                        SDL_FreeSurface( gHelloWorld3 );
                        ball_select=3;
                        break;

                    case SDLK_4:
                        flag_ballmenu=0;
                        SDL_FreeSurface( gHelloWorld3 );
                        ball_select=4;
                        break;
                }

            }


            else if( event->type == SDL_QUIT )
            {

                SDL_DestroyWindow( m_window3 );
                SDL_DestroyRenderer( m_renderer3 );
                IMG_Quit();
                SDL_Quit();
                return 0;
            }
        }
        }


        SDL_DestroyWindow( m_window3 );



        //second window
    SDL_CreateWindowAndRenderer( 1000, 700, WND_flags, &m_window2, &m_renderer2 );
    SDL_RaiseWindow(m_window2);

    SDL_Surface* gScreenSurface2 = NULL;
    SDL_Surface* gHelloWorld2 = NULL;
    gScreenSurface2 = SDL_GetWindowSurface( m_window2 );
    gHelloWorld2 = SDL_LoadBMP( "loading.bmp" );
    SDL_BlitSurface(gHelloWorld2,NULL,gScreenSurface2,NULL);
    SDL_UpdateWindowSurface( m_window2 );
    SDL_Delay(5000);
    SDL_DestroyWindow( m_window2 );



    //main window rise
    SDL_CreateWindowAndRenderer( 1200, 800, WND_flags, &m_window, &m_renderer );
    SDL_RaiseWindow(m_window);




    /*int w5, h5;
    SDL_Texture* loading_img =NULL;
    loading_img=IMG_LoadTexture(m_renderer, "bar.gif");
    SDL_Rect loading_image;
    SDL_QueryTexture(loading_img, NULL, NULL, &w5, &h5);
    loading_image.x = 0;
    loading_image.y = 0;
    loading_image.w = w5*1;
    loading_image.h = h5*1;
    SDL_RenderCopy( m_renderer, loading_img, NULL, &loading_image);*/

    /*gHelloWorld = SDL_LoadBMP( "loading.bmp" );
    SDL_BlitSurface(gHelloWorld,NULL,gScreenSurface,NULL);
    SDL_UpdateWindowSurface( m_window );
    SDL_Delay(5000);*/

    gScreenSurface = SDL_GetWindowSurface( m_window );


    // BACKGROUND TEXTURE
    SDL_Texture *mTexture;
    mTexture = SDL_CreateTexture( m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET , W, H );
    SDL_SetRenderDrawColor( m_renderer, 255, 255, 255, 255 );
    SDL_RenderClear( m_renderer );
    SDL_RenderPresent( m_renderer );

    SDL_SetRenderTarget( m_renderer, mTexture );
    SDL_Texture* m_img = NULL;

    int img_w, img_h;
    SDL_Rect img_rect;
    m_img = IMG_LoadTexture(m_renderer, "nature.png");
    SDL_QueryTexture(m_img, NULL, NULL, &img_w, &img_h);
    img_rect.x = 0;
    img_rect.y = 0;
    img_rect.w = img_w * 1.15;
    img_rect.h = img_h * 1;

    SDL_RenderCopy(m_renderer, m_img, NULL, &img_rect);



        int font =2;
        int x_position=500;
        int y_position=200;
        int R=255;
        int G =2;
        int B=3;
        int A=0.5;
// text for score, level and lives


    textRGBA(m_renderer,x_position-490,y_position-100,"Score: ",font ,30,R,G,B,A);
    textRGBA(m_renderer,x_position-490,y_position,"Level: ",font ,30,R,G,B,A);
    textRGBA(m_renderer,x_position-490,y_position+100,"Lives: ",font ,30,R,G,B,A);
    SDL_SetRenderTarget( m_renderer, NULL );



    SDL_RenderCopy(m_renderer, mTexture, NULL, NULL);
    SDL_RenderPresent( m_renderer );
    SDL_DestroyTexture(m_img);


    //TEXTURE FOR PRINTING NUMBERS


    digit0 = IMG_LoadTexture( m_renderer, "digit0.png");
    digit1 = IMG_LoadTexture( m_renderer, "digit1.png");
    digit2 = IMG_LoadTexture( m_renderer, "digit2.png");
    digit3 = IMG_LoadTexture( m_renderer, "digit3.png");
    digit4 = IMG_LoadTexture( m_renderer, "digit4.png");
    digit5 = IMG_LoadTexture( m_renderer, "digit5.png");
    digit6 = IMG_LoadTexture( m_renderer, "digit6.png");
    digit7 = IMG_LoadTexture( m_renderer, "digit7.png");
    digit8 = IMG_LoadTexture( m_renderer, "digit8.png");
    digit9 = IMG_LoadTexture( m_renderer, "digit9.png");



     // IMAGE FOR BALL

    int w3, h3;
    SDL_Texture* ball_img = NULL;
    if(ball_select==1)
    ball_img=IMG_LoadTexture( m_renderer, "BALL.gif");
    if(ball_select==2)
    ball_img=IMG_LoadTexture( m_renderer, "ball_2.gif");
    if(ball_select==3)
    ball_img=IMG_LoadTexture( m_renderer, "ball_3.gif");
    if(ball_select==4)
    ball_img=IMG_LoadTexture( m_renderer, "ball_4.gif");
    // IMAGE FOR BAR
    int w4, h4;
    SDL_Texture* bar_img =NULL;
    bar_img=IMG_LoadTexture(m_renderer, "bar.gif");



    game.bar.x=0;
    game.bar.y=740;
    game.ball.direction_x=1;
    game.ball.direction_y=-1;
    game.ball.radius=25;
    game.ball.x=game.bar.x+game.bar.w/2;;
    game.ball.y=game.bar.y-game.ball.radius-1;
    game.bar.h=50;
    game.bar.w=200;

    double x,y;
    int flag_gameover=0, flag_pause=0;






if(flag_loadornew==1)
{
    srand(time(NULL));
    for(int i=0;i<30;i++)
    {   int f=0;

        for(int j=0;j<=7;j++)
        {
            brick[i][j].strength=rand()%(i+1)+difficulty-1;
            if(brick[i][j].strength==0)
            {
                f++;
                if(f>2)
                brick[i][j].strength++;

            }
        }
    }

}



int damage=1, level =1, firstshot=0, min_radif=0 , flag_cheat=0;
game.ball.damage=1;
    while(flag_end==1)
    {

    if(game.player.score<100)
    {
    print_number(m_renderer,x_position-400,y_position-100,game.player.score);
    }
    else
    {
    print_number(m_renderer,x_position-370,y_position-100,game.player.score);
    }
    print_number(m_renderer,x_position-400,y_position,game.player.level);
    print_number(m_renderer,x_position-400,y_position+100,game.player.lives);

           //barkhord be divar chap
        if(game.ball.x<=game.ball.radius)
        {
            game.ball.direction_x*=(-1);
        }
        //barkhord be divar rast
        if(game.ball.x>=1200-(game.ball.radius))
        {
            game.ball.direction_x*=(-1);
        }
        //barkhord be saghf
        if(game.ball.y<=game.ball.radius)
        {
            game.ball.direction_y*=(-1);

        }
        //barkhord ba bar
        if((game.ball.y+game.ball.radius>=800-(game.bar.h)) && ((game.ball.x<=game.bar.x+game.bar.w) && (game.ball.x>=game.bar.x)))
        {
            game.ball.direction_y*=(-1);
           Mix_PlayChannel(-1,barkhord,0);
        }
        //barkhord ba gooshe bar
        if(((game.ball.x-game.bar.x)*(game.ball.x-game.bar.x)+(game.ball.y-game.bar.y)*(game.ball.y-game.bar.y)<=game.ball.radius*game.ball.radius) || ((game.ball.x-(game.bar.x+game.bar.w))*(game.ball.x-(game.bar.x+game.bar.w)))+(game.ball.y-game.bar.y)*(game.ball.y-game.bar.y)<=game.ball.radius*game.ball.radius)
        {

            //x=((double)(rand()%9)/10)+0.1;
            //y=-sqrt(2-x*x);
            game.ball.direction_y*=(-1);
            game.ball.direction_x*=(-1);
            Mix_PlayChannel(-1,barkhord,0);
        }
        //barkhord ba zamin
        if((game.ball.y+game.ball.radius>=800))
        {

            game.ball.direction_y*=(-1);

            game.player.lives--;
            firstshot=0;
            if(game.player.lives<=0)
            {
                flag_gameover=1;

            }

        }


         //barkhord be brick
        for(int i=0;i<game.player.level;i++)
        {
            int c=0;
            for(int j=0;j<8;j++)
            {
                if(brick[i][j].strength!=0)
                {   //barkhord be rast brick
                    if(brick[i][j].y<=game.ball.y && brick[i][j].y+brick[i][j].h>=game.ball.y && fabs((brick[i][j].x+brick[i][j].w/2)-game.ball.x)-brick[i][j].w/2<=game.ball.radius)
                    {
                        game.ball.direction_x*=(-1);
                        damage=game.ball.damage;
                        game.ball.damage-=brick[i][j].strength;
                        if(brick[i][j].strength<=damage)
                               {

                                game.player.score+=game.player.level;
                                brick[i][j].strength=0;
                               }
                        else
                            brick[i][j].strength-=damage;

                    }

                    //barkhord be paein brick //might have a bug
                    else if(brick[i][j].x<=game.ball.x && brick[i][j].x+brick[i][j].w>=game.ball.x && fabs(brick[i][j].y+brick[i][j].h/2-game.ball.y)-brick[i][j].h/2<=game.ball.radius)
                    {
                       game.ball.direction_y*=(-1);
                       damage=game.ball.damage;
                        game.ball.damage-=brick[i][j].strength;
                        if(brick[i][j].strength<=damage){
                                game.player.score+=game.player.level;
                               brick[i][j].strength=0;
                        }
                        else
                            brick[i][j].strength-=damage;


                    }


                    //barkhod be gooshe haye balaeye brick

                    else if(((game.ball.x-brick[i][j].x)*(game.ball.x-brick[i][j].x)+(game.ball.y-brick[i][j].y)*(game.ball.y-brick[i][j].y)<=game.ball.radius*game.ball.radius) || ((game.ball.x-(brick[i][j].x+brick[i][j].w))*(game.ball.x-(brick[i][j].x+brick[i][j].w)))+(game.ball.y-brick[i][j].y)*(game.ball.y-brick[i][j].y)<=game.ball.radius*game.ball.radius)
                    {   continue;
                        game.ball.direction_y*=(-1);
                        game.ball.direction_x*=(-1);
                        damage=game.ball.damage;
                        game.ball.damage-=brick[i][j].strength;
                        if(brick[i][j].strength<=damage){
                                game.player.score+=game.player.level;
                               brick[i][j].strength=0;
                        }
                        else
                            brick[i][j].strength-=damage;
                    }
                    //barkhord be gooshe haye paeinie brick
                    else if(((game.ball.x-brick[i][j].x)*(game.ball.x-brick[i][j].x)+(game.ball.y-brick[i][j].y+brick[i][j].h)*(game.ball.y-brick[i][j].y+brick[i][j].h)<=game.ball.radius*game.ball.radius) || ((game.ball.x-(brick[i][j].x+brick[i][j].w))*(game.ball.x-(brick[i][j].x+brick[i][j].w)))+(game.ball.y-brick[i][j].y+brick[i][j].h)*(game.ball.y-brick[i][j].y+brick[i][j].h)<=game.ball.radius*game.ball.radius)
                    {   continue;
                        game.ball.direction_y*=(-1);
                        game.ball.direction_x*=(-1);
                        damage=game.ball.damage;
                        game.ball.damage-=brick[i][j].strength;
                        if(brick[i][j].strength<=damage){
                            game.player.score+=game.player.level;
                            brick[i][j].strength=0;
                        }
                        else
                            brick[i][j].strength-=damage;


                    }
                }
                else c++;
            }

            if(c==8 && i>=min_radif)
            {
                min_radif=i;
            }
        }


        // spawn brick
        for(int i=0;i<game.player.level;i++)
        {
            for(int j=0;j<8;j++)
            {
                if(brick[i][j].strength!=0)
                {
                    brick[i][j].x=20+(brick[i][j].w+10)*j;
                    brick[i][j].y=100+(game.player.level-i)*50;
                    rect(m_renderer , brick[i][j].x , brick[i][j].y , brick[i][j].w , brick[i][j].h , 0 ,min(brick[i][j].strength*50,255) , 0 , 1);

                }


            }
            if(brick[min_radif][0].y>=600)
            {
                flag_end=0;
            }
        }
        // damage and level initialization
        if(game.ball.damage<=0)
            {
            game.player.level++;
            game.ball.damage=game.player.level;
            firstshot=0;
            game.ball.y=game.bar.y-game.ball.radius;
            ellipse(m_renderer,game.ball.x,game.ball.y,game.ball.radius,game.ball.radius,0,0,0,1);
            }

        game.ball.x+=game.ball.direction_x*5;
        game.ball.y+=game.ball.direction_y*5;


        double d=1.55;
        int l=150;
while(firstshot==0)
{   game.ball.y=game.bar.y-game.ball.radius;
    game.ball.x=game.bar.x+game.bar.w/2;
            for(int i=0;i<game.player.level;i++)
        {
            for(int j=0;j<8;j++)
            {
                if(brick[i][j].strength!=0)
                {
                    brick[i][j].x=20+(brick[i][j].w+10)*j;
                    brick[i][j].y=100+(game.player.level-i)*50;
                    rect(m_renderer , brick[i][j].x , brick[i][j].y , brick[i][j].w , brick[i][j].h , 0 , min(brick[i][j].strength*50,255) , 0 , 1);

                }

            }
        }

        thickLineRGBA(m_renderer , game.bar.x+game.bar.w/2 , game.ball.y , game.bar.x+game.bar.w/2+l*cos(d) , game.ball.y-sin(d)*l , 2 , 200 , 190 , 120 , 255 );

        //IMAGE FOR BAR
        SDL_Rect bar_image;
        SDL_QueryTexture(bar_img, NULL, NULL, &w4, &h4);
        bar_image.x = game.bar.x;
        bar_image.y = game.bar.y;
        bar_image.w = w4*1.46;
        bar_image.h = h4*1;
        SDL_RenderCopy( m_renderer, bar_img, NULL, &bar_image);



        if(ball_select==1){
     //IMAGE FOR BALL
    SDL_Rect ball_image;
    SDL_QueryTexture(ball_img, NULL, NULL, &w3, &h3);
    ball_image.x = game.ball.x-game.ball.radius;
    ball_image.y = game.ball.y- game.ball.radius;
    ball_image.w = 2*game.ball.radius;
    ball_image.h = 2*game.ball.radius;
    SDL_RenderCopy( m_renderer, ball_img, NULL, &ball_image);
    }

     if(ball_select==2){
     //IMAGE FOR BALL
    SDL_Rect ball_image;
    SDL_QueryTexture(ball_img, NULL, NULL, &w3, &h3);
    ball_image.x = game.ball.x-game.ball.radius;
    ball_image.y = game.ball.y- game.ball.radius;
    ball_image.w = 2*game.ball.radius;
    ball_image.h = 2*game.ball.radius;
    SDL_RenderCopy( m_renderer, ball_img, NULL, &ball_image);
    }


     if(ball_select==3){
     //IMAGE FOR BALL
    SDL_Rect ball_image;
    SDL_QueryTexture(ball_img, NULL, NULL, &w3, &h3);
    ball_image.x = game.ball.x-game.ball.radius;
    ball_image.y = game.ball.y- game.ball.radius;
    ball_image.w = 2*game.ball.radius;
    ball_image.h = 2*game.ball.radius;
    SDL_RenderCopy( m_renderer, ball_img, NULL, &ball_image);
    }

    if(ball_select==4){
     //IMAGE FOR BALL
    SDL_Rect ball_image;
    SDL_QueryTexture(ball_img, NULL, NULL, &w3, &h3);
    ball_image.x = game.ball.x-game.ball.radius;
    ball_image.y = game.ball.y- game.ball.radius;
    ball_image.w = 2*game.ball.radius;
    ball_image.h = 2*game.ball.radius;
    SDL_RenderCopy( m_renderer, ball_img, NULL, &ball_image);
    }

        if(game.player.score<=100){
        print_number(m_renderer,x_position-400,y_position-100,game.player.score);
        }
        else
        {
        print_number(m_renderer,x_position-370,y_position-100,game.player.score);
        }

        print_number(m_renderer,x_position-400,y_position,game.player.level);
        print_number(m_renderer,x_position-400,y_position+100,game.player.lives);
        SDL_RenderPresent(m_renderer);

        SDL_RenderCopy(m_renderer,mTexture,NULL,NULL);

    if( SDL_PollEvent( event ) )
        {
            //If a key was pressed
            if( event->type == SDL_KEYDOWN )
            {
                //Set the proper message surface
                switch( event->key.keysym.sym )
                {
                        case SDLK_w:
                        d = d+0.1;
                        break;

                        case SDLK_s:
                        d = d-0.1;
                        break;


                        case SDLK_SPACE:
                        firstshot=1;
                        game.ball.direction_x=cos(d)*sqrt(2);
                        game.ball.direction_y=sin(d)*sqrt(2);

                        break;

                        case SDLK_a:
                        game.bar.x-=20;
                        game.ball.x=game.bar.x+game.bar.w/2;

                        break;


                    case SDLK_d:
                        game.bar.x+=20;
                        game.ball.x=game.bar.x+game.bar.w/2;

                        break;

                    case SDLK_ESCAPE:
                    flag_end=0;
                    cout<<"score: "<<game.player.score<<endl;
                    break;
                }

            }


            else if( event->type == SDL_QUIT )
            {
                //Quit the program
                SDL_DestroyWindow( m_window );
                SDL_DestroyRenderer( m_renderer );
                IMG_Quit();
                SDL_Quit();
                return 0;
            }
        }}




    if(ball_select==1){
     //IMAGE FOR BALL
    SDL_Rect ball_image;
    SDL_QueryTexture(ball_img, NULL, NULL, &w3, &h3);
    ball_image.x = game.ball.x-game.ball.radius;
    ball_image.y = game.ball.y- game.ball.radius;
    ball_image.w = 2*game.ball.radius;
    ball_image.h = 2*game.ball.radius;
    SDL_RenderCopy( m_renderer, ball_img, NULL, &ball_image);
    }

     if(ball_select==2){
     //IMAGE FOR BALL
    SDL_Rect ball_image;
    SDL_QueryTexture(ball_img, NULL, NULL, &w3, &h3);
    ball_image.x = game.ball.x-game.ball.radius;
    ball_image.y = game.ball.y- game.ball.radius;
    ball_image.w = 2*game.ball.radius;
    ball_image.h = 2*game.ball.radius;
    SDL_RenderCopy( m_renderer, ball_img, NULL, &ball_image);
    }

     if(ball_select==3){
     //IMAGE FOR BALL
    SDL_Rect ball_image;
    SDL_QueryTexture(ball_img, NULL, NULL, &w3, &h3);
    ball_image.x = game.ball.x-game.ball.radius;
    ball_image.y = game.ball.y- game.ball.radius;
    ball_image.w = 2*game.ball.radius;
    ball_image.h = 2*game.ball.radius;
    SDL_RenderCopy( m_renderer, ball_img, NULL, &ball_image);
    }

    if(ball_select==4){
     //IMAGE FOR BALL
    SDL_Rect ball_image;
    SDL_QueryTexture(ball_img, NULL, NULL, &w3, &h3);
    ball_image.x = game.ball.x-game.ball.radius;
    ball_image.y = game.ball.y- game.ball.radius;
    ball_image.w = 2*game.ball.radius;
    ball_image.h = 2*game.ball.radius;
    SDL_RenderCopy( m_renderer, ball_img, NULL, &ball_image);
    }

    //IMAGE FOR BAR
    SDL_Rect bar_image;
    SDL_QueryTexture(bar_img, NULL, NULL, &w4, &h4);
    bar_image.x = game.bar.x;
    bar_image.y = game.bar.y;
    bar_image.w = w4*1.46;
    bar_image.h = h4*1;

    SDL_RenderCopy( m_renderer, bar_img, NULL, &bar_image);


    if( SDL_PollEvent( event ) )
        {
            //If a key was pressed
            if( event->type == SDL_KEYDOWN )
            {
                //Set the proper message surface
                switch( event->key.keysym.sym )
                {

                    case SDLK_a:
                        game.bar.x-=20;
                        break;

                    case SDLK_d:
                        game.bar.x+=20;
                        break;

                    case SDLK_c:
                        flag_cheat=1;
                        break;

                    case SDLK_p:
                        flag_pause=1;
                        break;

                    case SDLK_ESCAPE:
                    flag_end=0;
                    break;
                }

            }

            //If the user has Xed out the window
            else if( event->type == SDL_QUIT )
            {
                //Quit the program
                SDL_DestroyWindow( m_window );
                SDL_DestroyRenderer( m_renderer );
                IMG_Quit();
                SDL_Quit();
                return 0;
            }
        }


        //havaset be sorat bashe


      //  textRGBA(m_renderer,x_position-380,y_position-100,Printer(game.player.score),2 ,30,255,255,255,A);
      //  textRGBA(m_renderer,x_position-380,y_position,Printer(game.player.level),2 ,30,255,255,255,A);
       // textRGBA(m_renderer,x_position-380,y_position+90,Printer(game.player.lives),2 ,30,255,255,255,A);
       // print_number(m_renderer,x_position-380,y_position-100,game.player.score);
        SDL_RenderPresent(m_renderer);

        SDL_Delay(2);
        SDL_RenderCopy(m_renderer,mTexture,NULL,NULL);
        if(flag_cheat==1)
        {
            for(int j=0;j<8;j++)
            {
                brick[min_radif][j].strength=0;
            }
            flag_cheat=0;
        }
        if(flag_gameover==1)
        {

    gHelloWorld = SDL_LoadBMP( "gameover.bmp" );
    SDL_BlitSurface(gHelloWorld,NULL,gScreenSurface,NULL);
    SDL_UpdateWindowSurface( m_window );

    SDL_Delay(5000);
    //SDL_DestroyWindow(m_window);
        flag_gameover=0;
        flag_end=0;
        //game.player.lives=3;
        SDL_DestroyWindow(m_window);
        }

    if(flag_pause==1)
    {
    gHelloWorld = SDL_LoadBMP( "pause.bmp" );
    SDL_BlitSurface(gHelloWorld,NULL,gScreenSurface,NULL);

    }
        while(flag_pause==1)
        {

        SDL_UpdateWindowSurface( m_window );



    if( SDL_PollEvent( event ) )
        {
            //If a key was pressed
            if( event->type == SDL_KEYDOWN )
            {
                //Set the proper message surface
                switch( event->key.keysym.sym )
                {

                    case SDLK_ESCAPE:
                        flag_pause=0;
                        SDL_FreeSurface( gHelloWorld );
                        break;
                }

            }


            else if( event->type == SDL_QUIT )
            {

                SDL_DestroyWindow( m_window );
                SDL_DestroyRenderer( m_renderer );
                IMG_Quit();
                SDL_Quit();
                return 0;
            }
        }
        }

        SDL_Delay(9);

        //SDL_DestroyTexture(ball_img);


    }




    for(int i=0; i<5; i++)
    {
        history_score[i]=history_score[i+1];
    }
    history_score[4]=game.player.score;


    out.open(game.player.name.c_str());
    for(int i=0; i<5; i++)
    {
        out<<history_score[i]<<" ";
    }
    out<<game.player.score<<" "<<game.player.level<<" "<<game.player.lives<<" ";
    for(int i=0; i<30; i++)
    {
        for(int j=0; j<8; j++)
        {
            out<<brick[i][j].strength<<" ";
        }
    }
     for(int i=0; i<30; i++)
    {
        for(int j=0; j<8; j++)
        {
            out<<brick[i][j].x<<" ";
        }
    }
     for(int i=0; i<30; i++)
    {
        for(int j=0; j<8; j++)
        {
            out<<brick[i][j].y<<" ";
        }
    }
    out.close();

    return 0;
}



void rect(SDL_Renderer *Renderer, int x,int y,int w,int h,int R, int G, int B, int fill_boolian )
{
    SDL_Rect rectangle ;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = w;
    rectangle.h = h;


    SDL_SetRenderDrawColor(Renderer, R, G, B, 255);
    if (fill_boolian==1)
        SDL_RenderFillRect(Renderer, &rectangle);
    SDL_RenderDrawRect(Renderer, &rectangle);


}

void ellipse(SDL_Renderer *Renderer, int x, int y, int Radius1, int Radius2, int R, int G, int B, int fill_boolian)
{
    if(fill_boolian==1)
        filledEllipseRGBA(Renderer,x,y,Radius1,Radius2,R,G,B,255);
    if(fill_boolian==0)
        ellipseRGBA(Renderer,x,y,Radius1,Radius2,R,G,B,255);

}

void window_color(SDL_Renderer *Renderer, int R, int G, int B)
{
    SDL_SetRenderDrawColor( Renderer, R, G, B, 255 );
    SDL_RenderClear( Renderer );

    // Show the window
    SDL_RenderPresent( Renderer );

}

//for printing numbers on screen
//char * Printer (int score)
//{
//    string str="";
//    str=to_string(score);
//    char* ch=new char[str.length()+1];
//    return strcpy(ch,str.c_str());
//
//}

void print_number(SDL_Renderer *Renderer,int x, int y, int number)
{
    int n=number/10;
    while(number>9)
    {
        chap(Renderer,x,y,number-n*10);
        n/=10;
        number/=10;
        x-=15;
    }
    chap(Renderer,x,y,number);
}

void chap(SDL_Renderer *Renderer,int x, int y, int digit)
{
    if(digit==0)
    {
        int w0, h0;
        SDL_QueryTexture(digit0, NULL, NULL, &w0, &h0);
        SDL_Rect texr0;
        texr0.x = x;
        texr0.y = y;
        texr0.w = 30;
        texr0.h = 45;
        SDL_RenderCopy( Renderer, digit0, NULL, &texr0);
    }
    if(digit==1)
    {
        int w1, h1;
        SDL_QueryTexture(digit1, NULL, NULL, &w1, &h1);
        SDL_Rect texr1;
        texr1.x = x;
        texr1.y = y;
        texr1.w = 30;
        texr1.h = 45;
        SDL_RenderCopy( Renderer, digit1, NULL, &texr1);
    }
    if(digit==2)
    {
        int w2, h2;
        SDL_QueryTexture(digit2, NULL, NULL, &w2, &h2);
        SDL_Rect texr2;
        texr2.x = x;
        texr2.y = y;
        texr2.w = 30;
        texr2.h = 45;
        SDL_RenderCopy( Renderer, digit2, NULL, &texr2);
    }
    if(digit==3)
    {
        int w3, h3;
        SDL_QueryTexture(digit3, NULL, NULL, &w3, &h3);
        SDL_Rect texr3;
        texr3.x = x;
        texr3.y = y;
        texr3.w = 30;
        texr3.h = 45;
        SDL_RenderCopy( Renderer, digit3, NULL, &texr3);
    }
    if(digit==4)
    {
        int w4, h4;
        SDL_QueryTexture(digit4, NULL, NULL, &w4, &h4);
        SDL_Rect texr4;
        texr4.x = x;
        texr4.y = y;
        texr4.w = 30;
        texr4.h = 45;
        SDL_RenderCopy( Renderer, digit4, NULL, &texr4);
    }
    if(digit==5)
    {
        int w5, h5;
        SDL_QueryTexture(digit5, NULL, NULL, &w5, &h5);
        SDL_Rect texr5;
        texr5.x = x;
        texr5.y = y;
        texr5.w = 30;
        texr5.h = 45;
        SDL_RenderCopy( Renderer, digit5, NULL, &texr5);
    }
    if(digit==6)
    {
        int w6, h6;
        SDL_QueryTexture(digit6, NULL, NULL, &w6, &h6);
        SDL_Rect texr6;
        texr6.x = x;
        texr6.y = y;
        texr6.w = 30;
        texr6.h = 45;
        SDL_RenderCopy( Renderer, digit6, NULL, &texr6);
    }
    if(digit==7)
    {
        int w7, h7;
        SDL_QueryTexture(digit7, NULL, NULL, &w7, &h7);
        SDL_Rect texr7;
        texr7.x = x;
        texr7.y = y;
        texr7.w = 30;
        texr7.h = 45;
        SDL_RenderCopy( Renderer, digit7, NULL, &texr7);
    }
    if(digit==8)
    {
        int w8, h8;
        SDL_QueryTexture(digit8, NULL, NULL, &w8, &h8);
        SDL_Rect texr8;
        texr8.x = x;
        texr8.y = y;
        texr8.w = 30;
        texr8.h = 45;
        SDL_RenderCopy( Renderer, digit8, NULL, &texr8);
    }
    if(digit==9)
    {
        int w9, h9;
        SDL_QueryTexture(digit9, NULL, NULL, &w9, &h9);
        SDL_Rect texr9;
        texr9.x = x;
        texr9.y = y;
        texr9.w = 30;
        texr9.h = 45;
        SDL_RenderCopy( Renderer, digit9, NULL, &texr9);
    }
}


