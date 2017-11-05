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
using namespace std;

#ifdef main
#undef main
#endif

//const int S_W = 800; //Screen Height
//const int S_H = 600; //Screen Width

/*
 * 
 */
int main(int argc, char** argv) {
    
    
    bool quit = false;
    SDL_Event event;
    SDL_Window *window;                    // Declare a pointer
    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2
    
    SDL_DisplayMode DM;
    SDL_GetDesktopDisplayMode( 0, &DM );
    int S_W = DM.w;
    int S_H = DM.h - 20;
    
    SDL_Surface *card = SDL_LoadBMP( "x.bmp" );
    
    
    
    


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
    
    while (!quit)
    {
        SDL_WaitEvent(&event);
 
        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
        }
        SDL_RenderPresent(renderer);
        
        //Draw basic grid for the cards
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
                
        //Draw points representing commodity placement
        for( int j = 8; j < 49; j += 7 )
        {
            for( int i = 3; i < 224; i += 8 )
            {
                SDL_RenderDrawPoint( renderer, S_W * j / 49, S_H * i / 224 );
                filledCircleRGBA( renderer, S_W * j / 49, S_H * i / 224 , 3, 0xFF, 0x00, 0x00, 0xFF);
            }
        }
        
        SDL_Texture *cardtex = SDL_CreateTextureFromSurface( renderer, card );
        SDL_Rect cardrect { S_W * 1 / 7, S_H * 3 / 7 , S_W / 7, S_H / 7 };
        SDL_RenderCopy( renderer, cardtex, NULL, &cardrect );
        
        
        SDL_RenderPresent( renderer );
                
                
        //filledCircleRGBA(renderer, 200,300,10,0,0,200,400);
        //SDL_RenderPresent(renderer);
        //SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        //SDL_RenderDrawLine(renderer,200,300,300,400);
        //SDL_RenderPresent(renderer);
        //SDL_RenderDrawLine(renderer,300,400,0,700);
        //SDL_RenderPresent(renderer);
        //roundedBoxRGBA(renderer,500,100,2000,2000,10,255,255,255,255);
        //SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
        
   

    return 0;
}

