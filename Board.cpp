/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: micah
 *
 * Created on September 20, 2017, 11:39 PM
 */
#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "Time_Travel_Player.h"
#include "Board.h"
#include "Card.h"
#include "Deck.h"
#include <SDL2/SDL_image.h>
#include "Generic.h"


using namespace std;

static int DOT_VEL = 1;
static int DOT_WIDTH = 20;
static int DOT_HEIGHT = 20;


Board::Board() {
    d = Deck();
    for(int i = 0; i < 5; i++)
        Start_Array[i] = 17;
    for(int i = 0;i<28;i++)
    {
        for(int j = 0;j<5;j++)
        {
            Board_Commodities[i][j] = ' ';
            Paths[i][j] = 0;
        }
    }
    
};

void Board::start_game( ){
    Board b; //= Board();
    bool endturn = false;
    bool take;
    int start, end;
    //Draw basic grid for the cards
    //int Start_Array[5] = { 12, 12, 12, 12, 12 }; //Initialize the starting height of the cards
    //Initialize the Deck
    SDL_Rect win;
    int *x,*y;
    //Deck d = Deck();
       
    bool quit = false;
    SDL_Event e;
    SDL_Window *window;                    // Declare a pointer
    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2
    
    SDL_DisplayMode DM;
    SDL_GetDesktopDisplayMode( 0, &DM );
    int S_W = DM.w;
    int S_H = DM.h - 20;
    int i = 0;
    int Position_X = 300;
    int Position_Y = 300;
    int Velocity_X = 0;
    int Velocity_Y = 0;
    int path,col;
    //int S_W = 640;
    //int S_H = 480;
    
    /*cout << "empty board" << endl;
    for(int i = 0; i < 28; i++) 
        {
            for(int j = 0; j < 5; j ++)
            {
                cout << b.Board_Commodities[i][j];
            }
            cout << endl;
        }*/
    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "Time Traders",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        S_W,                               // width, in pixels
        S_H,                               // height, in pixels
        SDL_WINDOW_MAXIMIZED                  // flags - see below
    );
    win.x = 0;
    win.y = 0;
    win.w = S_W;
    win.h = S_H;
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture *texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, S_W, S_H);
    SDL_SetRenderTarget(renderer, texture);

        
        for(int i = 0; i < 5; i++) {
            b.c = b.d.draw();
            b.Add_Card( b.c, 12, i+1, S_W, S_H);
            //cout << "Start card " << i+1 << " is added"<<endl; 
            //b.c.print(b.c);
        }
        b.Display_Board(renderer, texture, S_W, S_H);
        /*c = d.draw();
        b.Add_Card( c, b.Card_Array, &Start_Array[0], 11, 1, S_W, S_H, b.Board_Commodities);
        
        
        c = d.draw();
        b.Add_Card( c, b.Card_Array, &Start_Array[0], 6, 1, S_W, S_H, b.Board_Commodities);
        
        c = d.draw();
        b.Add_Card( c, b.Card_Array, &Start_Array[0], 25, 2, S_W, S_H, b.Board_Commodities);
       
        
        c = d.draw();
        b.Add_Card( c, b.Card_Array, &Start_Array[0], 25, 2, S_W, S_H, b.Board_Commodities);
       
        //c4.Show_Card(c4,render_rect,renderer,S_W * 4 / 7, S_H * 3 / 7, S_W / 7, S_H / 7,texture );
        //SDL_RenderPresent(renderer);
        
        //render_rect = {S_W * 5 / 7, S_H * 3 / 7, S_W / 7, S_H / 7 };
        //b.Add_Card( c5, Card_Array, &Start_Array[0], 12, 5, S_W, S_H, b.Board_Commodities);
        //c5.Show_Card(c5,render_rect,renderer,S_W * 5 / 7, S_H * 3 / 7, S_W / 7, S_H / 7,texture );
        //SDL_RenderPresent(renderer);
         * */
        b.Display_Commodities(Board_Commodities);
        //b.Display_Board(renderer, texture, S_W, S_H);
        SDL_RenderPresent(renderer);    
        SDL_SetRenderTarget(renderer,NULL);
        //SDL_Init(SDL_INIT_VIDEO);
        IMG_Init(IMG_INIT_PNG);
        SDL_Surface * image = IMG_Load("Tardis_v2_Ship.gif");
        SDL_Texture * p1 = SDL_CreateTextureFromSurface(renderer,image);
        
        while (!quit)
    {
        while(SDL_PollEvent( &e ) != 0 && !quit){
 
        if( e.type == SDL_QUIT )
        {
                quit = true;
        }
        SDL_Rect scale;
                scale.x = Position_X;
                scale.y = Position_Y;
                scale.w = 20;
                scale.h = 20;
        SDL_RenderCopy(renderer, p1, NULL, &scale);
        SDL_RenderPresent(renderer);
        //b.texture = texture;
        //SDL_RenderClear(renderer);
        //
        handleEvent( e, &Velocity_X, &Velocity_Y, &scale.x, &scale.y,S_W,S_H,b,renderer,texture,&endturn);
        if (endturn)
        {
            cout << 1;
            SDL_SetRenderTarget(renderer,texture);
            SDL_RenderClear(renderer);
            b.Player_Location(S_W,S_H,scale.x+10,scale.y+10,&path,&col);
            if(col !=6 && col !=0)
            {
            //take = false;
            if(b.Check_Commodity( path,col ))
            {
                b.Display_Commodities(Board_Commodities);
                cout << "X:"<<path<<" Y:"<<col<<endl;
                cout << "Commodity:"<< Board_Commodities[path][col-1]<<endl;
                cout << "true" << endl;
                c = d.draw();
                //b.Add_Card(c,path,col,S_W,S_H);
                //b.Add_Card(c,path,col,S_W,S_H);
                b.Add_Card(c,path,col,S_W,S_H);
                b.Pickup_Commodity(path,col);
                
                //b.Display_Board(renderer, texture, S_W, S_H);
                //b.Display_Commodities(Board_Commodities);
                //SDL_RenderPresent(renderer);
                //SDL_SetRenderTarget(renderer,NULL);
                //SDL_RenderCopy(renderer,texture,NULL,&win);
                //SDL_RenderPresent(renderer);
            }
            
            //cout<< "Checked:"<<path<<","<<col-1<<endl;
            b.Display_Board(renderer, texture, S_W, S_H);
                b.Display_Commodities(Board_Commodities);
                SDL_RenderPresent(renderer);
                SDL_SetRenderTarget(renderer,NULL);
                //SDL_RenderCopy(renderer,texture,NULL,&win);
                SDL_RenderPresent(renderer);
            
            //b.Display_Commodities(Board_Commodities);
            //cout << "card added" << endl;
            //SDL_RenderClear(renderer);
            }
            if(col == 6) {
                b.Display_Board(renderer, texture, S_W, S_H);
                //b.Display_Commodities(Board_Commodities);
                SDL_RenderPresent(renderer);
                SDL_SetRenderTarget(renderer,NULL);
                //SDL_RenderCopy(renderer,texture,NULL,&win);
                SDL_RenderPresent(renderer);
                quit = Generic_Window("You win", "Congragulations Micah, you win!!!");
                //b.Path_Trace(path,col,&start,&end);
                //cout << "Start:"<<start<<" End:"<<end<<endl;
                quit = !quit;
                cout << !quit;
            }
        }      
            endturn = false;
        }
        
        SDL_SetRenderTarget(renderer,NULL);
        SDL_RenderClear(renderer);
        //SDL_SetRenderTarget(renderer,texture);
        //b.Display_Board(renderer, texture, S_W, S_H);
        //(renderer);
        //endturn = false;
        cout << 2;
        move(&Position_X,&Position_Y,Velocity_X,Velocity_Y);
        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
        //SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,texture,NULL,&win);
        SDL_Rect new_Pos;
            new_Pos.x = Position_X;
            new_Pos.y = Position_Y;
            new_Pos.w = 20;
            new_Pos.h = 20;
        SDL_RenderCopy(renderer, p1, NULL, &new_Pos); 
        SDL_RenderPresent(renderer);
        }
        /*for(int i = 0; i < 28; i++) 
        {
            for(int j = 0; j < 5; j ++)
            {
                cout << b.Board_Commodities[i][j];
            }
            cout << endl;
        }*/
        SDL_Quit();
}
/*Function inputs the number of players (set at 4) and displays the starting board*/
void Init_Board( int num )
{
    
}
void Board::Player_Location( int S_W, int S_H, int x, int y, int* path, int* col )
{
    double ytemp, xtemp; 
    xtemp = ( double(x) * 7 ) / S_W;
        
    for( int i = 0; i < 7; i++ )
    {
        if( (xtemp > ( i ) && xtemp < (i + 1)) || xtemp == i)
        {
            *col = i ;
        }

    }
    
    
    ytemp = double(y) * 28 / S_H;

    for( int j = 0; j < 28; j++ )
    {
        if( (ytemp > j && ytemp < (j + 1)) || ytemp == j)
        {
            *path = j;
        }
    } 
}


/*Add a card at the appropriate location given a player's path and column*/
void Board::Add_Card( Card c, int path, int col, int S_W, int S_H)
{
    int index = 0;
    char temp;
    int num = 0;
    
    for(int i = 0; i < 28; i++) //Increment the location of the commodities by one within the matrix representing the shift of one path by the cards
    {
        if (Board_Commodities[i][col-1] != ' ' ) 
        {
            num++;
            Board_Commodities[i-1][col-1] = Board_Commodities[i][col-1];
            Board_Commodities[i][col - 1] = ' ';
            Paths[i-1][col-1] = Paths[i][col - 1];
            Paths[i][col - 1] = 0;
        }
        
    }
    
    index = num/4; //index represents the number of cards in a given column
    //cout << index << " " << num << endl;
    if( path > ( Start_Array[ col - 1 ] + num - 1 ) )
    {
        
        
        for (int i = 0; i < 4; i++) 
        {
            Board_Commodities[Start_Array[col-1] + num + i ][col-1] = c.get_com(i);
            Paths[Start_Array[col-1] + num + i ][col-1] = c.get_path(i)-i+1;
        }
        Start_Array[ col - 1 ] -= 1; //Decrement the value of Start_Height to account for vertical slide of cards

        Card_Array[ col - 1 ][index] = c; //Add a new card to the array below the current card
    }    
    else if( path < Start_Array[col-1] )
    {
        for (int i = 1; i < 5; i++)
        {
            
            Board_Commodities[Start_Array[col-1] - i ][col-1] = c.get_com(4-i);
            Paths[Start_Array[col-1] - i - 1][col-1] = c.get_path(4-i)-5+i;
            cout << Start_Array[col-1] - i - 1 << "  " << Paths[Start_Array[col-1] - i][col-1]<<endl;
        }
        
        Start_Array[ col - 1 ] -= 5; //Decrement to account for vertical slide of cards and addition of new card
        for( int k = index; k > 0; k-- )
        {   
            Card_Array[ col - 1 ][ k ] = Card_Array[ col - 1 ][k-1];
        }
        Card_Array[ col - 1 ][0] = c;
        
    }
    else
    {
        Start_Array[col - 1] -= 1;
    }
        
}

/* Adds corresponding entries to the data matrices when a card is entered*/
/*void Board::Add_Entries( int Path_Change[28][5][2], bool Card_Presence[28][5], Card c, int path, int col )
{
    int * end_paths = c.get_paths( c );
    for( int i = 0; i < 4; i++ )
    {
      Path_Change[path + i][col][1] =  end_paths[i] -  i;
      Card_Presence[path + i][col] = true;
    }
}*/

void Board::handleEvent( SDL_Event& e,int *x, int *y, int *px, int *py,int S_W, int S_H,Board b, SDL_Renderer *renderer,SDL_Texture *texture, bool *endturn)
{
    int path,col;
    int i;
    i = 1;
    //int Start_Height[5];
    int num = 0;
    bool newcard = false;
    //Board b;
    //tests for key being pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjusts velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: 
                *y -= DOT_VEL;  
                break;
            case SDLK_DOWN: 
                *y += DOT_VEL; 
                break;
            case SDLK_LEFT: 
                *x -= DOT_VEL; 
                break;
            case SDLK_RIGHT:
                *x += DOT_VEL; 
                break;
            case SDLK_RETURN:
                Card c = d.draw();
                c.print(c);
                cout << endl;
                newcard = true;
                *endturn = true;
                break;
        }
        
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: 
                *y += DOT_VEL;   
                break;
            case SDLK_DOWN: 
                *y -= DOT_VEL; 
                break;
            case SDLK_LEFT: 
                *x += DOT_VEL; 
                break;
            case SDLK_RIGHT: 
                *x -= DOT_VEL; 
                break;
            
                /*for(int i = 0; i < 28; i++) //Increment the location of the commodities by one within the matrix representing the shift of one path by the cards
                {
                    if (b.Board_Commodities[i][col-1] != ' ' ) 
                    {
                        num++;
                        b.Board_Commodities[i-1][col-1] = b.Board_Commodities[i][col-1];
                        b.Board_Commodities[i][col - 1] = ' ';
                    }
        
                }
                int index = num/4;
                if( path > ( Start_Height[ col - 1 ] + num - 1 ) )
    {
        
        
        for (int i = 0; i < 4; i++) //adds commodities to matrix from new card
        {
            b.Board_Commodities[Start_Height[col-1] + num + i ][col-1] = c.get_com(i);
        }
        Start_Height[ col - 1 ] -= 1; //Decrement the value of Start_Height to account for vertical slide of cards

        b.Card_Array[ col - 1 ][index] = c; //Add a new card to the array below the current card
    }    
    /*else if( path < Start_Height[col-1] )
    {
        for (int i = 1; i < 5; i++)
        {
            
            b.Board_Commodities[Start_Height[col-1] - i ][col-1] = c.get_com(4-i);
            
        }
        
        Start_Height[ col - 1 ] -= 5; //Decrement to account for vertical slide of cards and addition of new card
        for( int k = index; k > 0; k-- )
        {   
            Card_Array[ col - 1 ][ k ] = Card_Array[ col - 1 ][k-1];
        }
        Card_Array[ col - 1 ][0] = c;
        
    }*/
         //b.Add_Card(c,path,col,S_W,S_H);
         
    }
    
    }}


void Board::move(int *x,int *y,int vel_x,int vel_y) {
    SDL_DisplayMode DM;
    SDL_GetDesktopDisplayMode( 0, &DM );
    int SCREEN_WIDTH = DM.w;
    int SCREEN_HEIGHT = DM.h - 20;
    //Move the dot left or right
    *x += vel_x;
    
    //If the dot went too far to the left or right
    if( ( *x < 0 ) || ( *x + DOT_WIDTH > SCREEN_WIDTH ) ) 
    {
        //Move back
        *x -= vel_x;
    }

    //Move the dot up or down
    *y += vel_y;

    //If the dot went too far up or down
    if( ( *y < 0 ) || ( *y + DOT_HEIGHT > SCREEN_HEIGHT ) ) 
    {
        //Move back
        *y -= vel_y;
    }
}
SDL_Rect render(int x,int y, SDL_Rect s) {
    s.x = x;
    s.y = y;
    return s;
}
void Board::Display_Commodities(char Commodities[28][5]) {
    for(int i = 0; i < 28; i++) 
        {
            for(int j = 0; j < 5; j ++)
            {
                cout << Board_Commodities[i][j];
            }
            cout << endl;
        }
}
void Board::Display_Board( SDL_Renderer* renderer, SDL_Texture* texture, int S_W, int S_H) {
    int index,num,k;
    Card c ;
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor( renderer, 0xCC, 0xCC, 0xCC, 0xFF );
        for( int i = 1; i < 8; i += 1 )
        {
            SDL_RenderDrawLine( renderer, 0, S_H * i/ 7, S_W, S_H * i / 7 );
            SDL_RenderDrawLine( renderer, S_W * i / 7, 0, S_W * i / 7, S_H );
        }
        //Reset the color to darker grey
        SDL_SetRenderDrawColor( renderer, 0xB0, 0xB0, 0xB0, 0xFF );
                
        //Draw the underlying path lines
        for( int i = 25; i < 32; i += 2 )
        {
            SDL_RenderDrawLine( renderer, 0, S_H * i / 56, S_W / 7, S_H * i / 56 );
        }
                
        for( int i = 1; i < 56; i += 2 )
        {
            SDL_RenderDrawLine( renderer, S_W / 7, S_H * i / 56, S_W, S_H * i / 56 );
        }
        SDL_Surface * start = SDL_LoadBMP( "Starting_Card.bmp" );
        SDL_Texture * start_tex = SDL_CreateTextureFromSurface( renderer, start );
        SDL_FreeSurface(start);
        
        SDL_Surface * market = SDL_LoadBMP( "Market_Card.bmp" );
        SDL_Texture * market_tex = SDL_CreateTextureFromSurface( renderer, market );
        SDL_FreeSurface(market);
        
        SDL_Rect start_rect = {0, S_H * 3 / 7, S_W / 7, S_H / 7 };
        SDL_Rect market_rect = { S_W * 6 / 7, S_H * 3 / 7, S_W / 7, S_H / 7 };
        
        SDL_RenderCopy( renderer, start_tex, NULL, &start_rect );
        SDL_RenderCopy( renderer, market_tex, NULL, &market_rect );
        SDL_RenderPresent(renderer);
    for( int i = 1; i < 6; i++ )
        {
        num = 0;
        for(int j = 0; j < 28; j++) {
            if(Board_Commodities[j][ i-1 ] != ' ')
                num++;
        }
        index = num/4;
            for( int k = 0; k < index; k++ )
            {
                {
                    SDL_Rect render_rect = {S_W * i / 7, S_H * ( Start_Array[ i - 1 ] + ( 4 * k ) ) / 28, S_W / 7, S_H / 7 };
                    c.Show_Card( Card_Array[i - 1][k],render_rect,renderer,S_W * i / 7, S_H * ( Start_Array[ i - 1 ] + ( 4 * k ) ) / 28 , S_W / 7, S_H / 7,texture);
                    SDL_RenderPresent(renderer);
                }
            }
        }            
}

/*Checks to see if a location landed on by a player possesses a commodity*/
bool Board::Check_Commodity(  int path, int col )
{
    bool ans = false;
    cout <<"Checking :"<< path+1 << "," << col-1 <<endl;
    if(Board_Commodities[path+1][col-1] != '0')
    {
        ans = true;
    }
    return ans;
}
/* Handles the even when a player lands on a location that possesses a commodity*/
void Board::Pickup_Commodity( int path, int col )
{
    Board_Commodities[path][col-1] = '0';
    cout <<"Pickup: "<< path<<" "<< col-1<<endl;
}

/*Adjusts matrix entries as a result of picking up a commodity */
void Increment_Entries( int Path_Change[28][5][2], bool Card_Presence[28][5], int col )
{
    int temp = Path_Change[0][col][1];
    bool tempbool = Card_Presence[0][col];
    for( int i = 0; i < 27; i++ )
    {
        Path_Change[i][col][1] = Path_Change[i+1][col][1];
        Card_Presence[i][col] = Card_Presence[i+1][col];
    }
    Path_Change[27][col][1] = temp;
    Card_Presence[27][col] = tempbool;
    
}

/*Inputting a player's path and column and outputting the beginning and ending path representing the connected commodity and market
 This can be modified to return locations in between to access valid player moves*/
void Board::Path_Trace( int path, int col, int* begin, int* end )
{
    int j = 0, endpath = 0, beginpath = 0;
    
    endpath = path;
    for( int i = col; i < 6; i++)
    {
        endpath = endpath + Paths[endpath][i];
    }
    *end = endpath; 

    beginpath = path;
    if( col > 0 )
    {
        for( int i = ( col - 1 ); i > -1; i-- )
        {
            cout << "Begin path:"<< beginpath<<endl;
            j = 0;
            while(beginpath != j + Paths[j][i] )
            {
                j++;
            }
            beginpath = j;
           
        }
    }
    cout << "exit" << beginpath << endl;
    *begin = beginpath;
}
/*
 * 
 */
#ifdef main
#undef main
#endif

/*int main(int argc, char** argv) 

{
    Board b = Board();
    b.start_game();
    
    return 0;
}*/



