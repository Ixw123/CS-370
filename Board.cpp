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
#include "Board.h"
#include "Card.h"
#include "Deck.h"


using namespace std;

void start_game();

void start_game(){
    //Draw basic grid for the cards
    
    //Initialize the Deck
    Deck d = Deck();
       
    bool quit = false;
    SDL_Event event;
    SDL_Window *window;                    // Declare a pointer
    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2
    
    SDL_DisplayMode DM;
    SDL_GetDesktopDisplayMode( 0, &DM );
    int S_W = DM.w;
    int S_H = DM.h - 20;
    /*int S_W = 640;
    int S_H = 480;*/
           
    
    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "Gfx_Spike",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        S_W,                               // width, in pixels
        S_H,                               // height, in pixels
        SDL_WINDOW_MAXIMIZED                  // flags - see below
    );
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
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
        
        SDL_Surface * market = SDL_LoadBMP( "Market_Card.bmp" );
        SDL_Texture * market_tex = SDL_CreateTextureFromSurface( renderer, market );
        
        SDL_Rect start_rect = {0, S_H * 3 / 7, S_W / 7, S_H / 7 };
        SDL_Rect market_rect = { S_W * 6 / 7, S_H * 3 / 7, S_W / 7, S_H / 7 };
        
        SDL_RenderCopy( renderer, start_tex, NULL, &start_rect );
        SDL_RenderCopy( renderer, market_tex, NULL, &market_rect );
        SDL_RenderPresent(renderer);
        
        for( int i = 1; i < 6; i++ )
        {
            SDL_Rect render_rect = {S_W * i / 7, S_H * 3 / 7, S_W / 7, S_H / 7 };
            Card c = d.draw();
            c.Show_Card(c,render_rect,renderer,S_W * i / 7, S_H * 3 / 7, S_W / 7, S_H / 7);
            SDL_RenderPresent(renderer);
            
        }
        
       
        while (!quit)
    {
        SDL_WaitEvent(&event);
 
        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
        }
        
        }
                
}
/*Function inputs the number of players (set at 4) and displays the starting board*/
void Init_Board( int num )
{
    
}

/* Displays appropriate cards at given locations*/
void Display_Board( bool Card_Presence )
{
    
}

/* Determines the appropriate path and column for a player given their x, y coordinates */
void Player_Location( int S_W, int S_H, int x, int y, int* path, int* col )
{
    double ytemp, xtemp; 
    ytemp = ( double(y) * 7 ) / S_W;
        
    for( int i = 0; i < 7; i++ )
    {
        if( ytemp > ( i ) && ytemp < (i + 1) )
        {
            *col = i - 1 ;
        }

    }
    
    
    xtemp = double(x) * 28 / S_H;

    for( int j = 0; j < 28; j++ )
    {
        if( xtemp > j && xtemp < (j + 1))
        {
            *path = j;
        }
    } 
}

/*Add a card at the appropriate location given a player's path and column*/
void Add_Card( int path, int col )
{
    //load card
    //Add_Entries(Path_Change, Card_Presence, card, path, col);
}

/* Adds corresponding entries to the data matrices when a card is entered*/
void Add_Entries( int Path_Change[28][5][2], bool Card_Presence[28][5], Card c, int path, int col )
{
    int * end_paths = c.get_paths( c );
    for( int i = 0; i < 4; i++ )
    {
      Path_Change[path + i][col][1] =  end_paths[i] -  i;
      Card_Presence[path + i][col] = true;
      
    }
}


/*Checks to see if a location landed on by a player possesses a commodity*/
bool Check_Commodity( int Path_Change[28][5][2], int path, int col )
{
    if(Path_Change[path][col][2] != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
/* Handles the even when a player lands on a location that possesses a commodity*/
void Pickup_Commodity( int Path_Change[28][5][2], int path, int col )
{
    
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
void Path_Trace( int Path_Change[28][5][2], int path, int col, int* begin, int* end )
{
    int j = 0, endpath = 0, beginpath = 0;
    
    endpath = path;
    for( int i = col; i < 6; i++)
    {
        endpath = endpath + Path_Change[endpath][i][1];
    }
    *end = endpath; 

    beginpath = path;
    if( col > 0 )
    {
        for( int i = ( col - 1 ); i > -1; i-- )
        {
            j = 0;
            while(beginpath != j + Path_Change[j][i][1] )
            {
                j++;
            }
            beginpath = j;
        }
    }
    *begin = beginpath;
}
/*
 * 
 */

/*int main(int argc, char** argv) 

{
    start_game();
    
    return 0;
}*/



