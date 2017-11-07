/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Card.cpp
 * Author: micah
 * 
 * Created on September 20, 2017, 10:08 PM
 */

#include "Card.h"
#include <SDL2/SDL.h>
#include <ctime>

#include <SDL2/SDL2_gfxPrimitives.h>
#include <random>

#include <iostream>

using namespace std;

Card::Card() {
}

Card::Card(int e1, int e2, int e3, int e4, char c1, char c2, char c3, char c4) {
    for(int i = 0; i < 4; i++) {
        start [i] = i + 1;
        c_com[i] = false;
    }
    end[0] = e1;
    end[1] = e2;
    end[2] = e3;
    end[3] = e4;
    com[0] = c1;
    com[1] = c2;
    com[2] = c3;
    com[3] = c4;
}
void Card::print(Card card) {
    for(int i = 0; i < 4; i++)
    {
        cout << card.start[i] << card.com[i] << card.end[i] << endl; 
    }
}

SDL_Renderer* Card::Show_Card(Card c, SDL_Rect Output_rect){ 
    
    SDL_Init(SDL_INIT_VIDEO && SDL_INIT_AUDIO);
    char *coms;
    std::random_device rd; 
    std::mt19937 mt(rd());
    //bool paths [4] = {false,false,false,false};
    bool commodities[4] = {false,false,false,false};
    bool picked = false;
    //char commoditys[4];
    int *paths;
    int path, sy,ey,x,y, ran;
    coms = c.get_coms(c);
    /*for (int i = 0; i < 4; i++)
        commoditys[i] = *(coms+i)*/
    paths = c.get_paths(c);
    bool quit = false;
    char ch;
    SDL_Event event;
    SDL_Window *window;                    // Declare a pointer
    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2


    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "in show",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Texture *card = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET, 480, 640);
    SDL_SetRenderTarget(renderer, card);
    SDL_RenderClear(renderer);
    
    roundedBoxRGBA(renderer,0,0,300,400,10,255,255,255,255); 
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderDrawLine(renderer,0,50,75,50);
    SDL_RenderDrawLine(renderer,218,50,300,50);
    SDL_RenderDrawLine(renderer,0,150,75,150);
    SDL_RenderDrawLine(renderer,218,150,300,150);
    SDL_RenderDrawLine(renderer,0,250,75,250);
    SDL_RenderDrawLine(renderer,218,250,300,250);
    SDL_RenderDrawLine(renderer,0,350,75,350);
    SDL_RenderDrawLine(renderer,218,350,300,350);
    sy = 50;
    for(int i = 0; i < 4; ++i){
        path = (*(paths + i ))-1 ;
        switch (path){
            case 0:
                ey = 50;
                SDL_RenderDrawLine(renderer, 75,sy,218,ey);
                sy += 100;
                break;
            case 1:
                ey = 150;
                SDL_RenderDrawLine(renderer, 75,sy,218,ey);
                sy += 100;
                break;
            case 2:
                ey = 250;
                SDL_RenderDrawLine(renderer, 75,sy,218,ey);
                sy += 100;
                break;
            case 3:
                ey = 350;
                SDL_RenderDrawLine(renderer, 75,sy,218,ey);
                sy += 100;
                break;
            default:
                break;
            
            
        };
        
    }
    sy = 50;
    for (int i = 0; i < 4; ++i){
       ch = (*(coms + i));
       
       if(ch == 'b'){
           filledCircleRGBA(renderer, 20,sy,10,0,0,255,255); //blue == beet candy
           sy += 100;
       }
       else if(ch == 'n'){
           filledCircleRGBA(renderer, 20,sy,10,0,255,0,255);//green == nucleons
           sy += 100;
       }
       else if(ch == 'm'){
           filledCircleRGBA(renderer, 20,sy,10,0,0,0,255);  //black == milkbread
           sy += 100;
       }

       else if(ch == 'o'){
           filledCircleRGBA(renderer, 20,sy,10,255,0,0,255);//red == oilpetrol
           sy += 100;
       }
           
        }
    //filledCircleRGBA(renderer, 100*(1/4) + 10,400*(2/4),10,0,0,200,400);
    //filledCircleRGBA(renderer, 100*(1/4) + 10,400*(3/4),10,0,0,200,400);
    //filledCircleRGBA(renderer, 100*(1/4) + 10,300,10,0,0,200,400);
    //SDL_RenderPresent(renderer);
    
    SDL_SetRenderTarget(renderer,NULL);
    SDL_RenderCopy(renderer, card, NULL, &Output_rect);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);
    SDL_DestroyWindow(window);
    return renderer;
}

char Card::get_com(int i) { 
    if(!c_com[i]) 
    {
        c_com[i] = true;
        return com[i];
    }
    return 'p';
}
char * Card::get_coms(Card c) {
    return com;
}
int * Card::get_paths(Card c) {
    return end;
}

Card::~Card() {
}

