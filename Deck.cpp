/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Deck.cpp
 * Author: micah
 * The class that defines all of deck's funcions
 * plays a sound when shuffled and when a card is drawn from the deck
 * Netbeans (g++ target)
 * 
 * Created on September 20, 2017, 9:52 PM
 */
#include <iostream>
#include <string>
#include <random>
#include <cstdlib>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_gfxPrimitives.h>   
#include <ctime>

#include "Deck.h"

Deck::Deck() {
    //initialize SDL video and audio
    SDL_Init(SDL_INIT_VIDEO && SDL_INIT_AUDIO);
        SDL_Window *window;                    // Declare a pointer


    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "Card and Deck Objects",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);
    //initialize mixer audio
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    //make an item to play a noise
    Mix_Chunk *shuffle = NULL;
    //that that noise to the shuffle sound
    shuffle = Mix_LoadWAV("shuffle.wav");
    //play the chunk shuffle on the next open channel 3 times
    Mix_PlayChannel(-1, shuffle, 2);
    //keep the window open for 1000 miliseconds
    SDL_Delay(1000);
    for (int i = 0; i < 46; i++)
	{
		c_deck[i] = false;
	}
	deck[0] = Card(1,2,4,3,'b','o','m','n');
	deck[1] = Card(1,3,2,4,'b','m','o','n');
	deck[2] = Card(1,4,2,3,'o','m','n','b');
	deck[3] = Card(1,3,4,2,'m','o','b','n');
	deck[4] = Card(1,4,3,2,'b','m','o','n');
	deck[5] = Card(2,1,3,4,'o','b','m','n');
	deck[6] = Card(2,1,4,3,'b','o','n','m');
	deck[7] = Card(3,1,2,4,'o','b','m','n');
	deck[8] = Card(4,1,2,3,'o','n','m','b');
	deck[9] = Card(3,1,4,2,'n','m','o','b');
	deck[10] = Card(4,1,3,2,'m','o','b','n');
	deck[11] = Card(2,3,1,4,'b','n','m','o');
	deck[12] = Card(2,4,1,3,'n','o','m','b');
	deck[13] = Card(3,2,1,4,'b','n','o','m');
	deck[14] = Card(4,2,1,3,'n','o','b','m');
	deck[15] = Card(3,4,1,2,'m','o','b','n');
	deck[16] = Card(4,3,1,2,'o','m','b','n');
	deck[17] = Card(2,3,4,1,'n','o','m','b');
	deck[18] = Card(2,4,3,1,'b','o','n','m');
	deck[19] = Card(3,2,4,1,'m','o','n','b');
	deck[20] = Card(4,2,3,1,'m','o','n','b');
	deck[21] = Card(3,4,2,1,'o','m','b','n');
	deck[22] = Card(4,3,2,1,'o','m','b','n');
	deck[23] = Card(1,2,4,3,'b','o','n','m');
	deck[24] = Card(1,3,2,4,'b','o','m','n');
	deck[25] = Card(1,4,2,3,'o','m','n','b');
	deck[26] = Card(1,3,4,2,'m','n','o','b');
	deck[27] = Card(1,4,3,2,'b','m','o','n');
	deck[28] = Card(2,1,3,4,'o','b','m','n');
	deck[29] = Card(2,1,4,3,'b','o','n','m');
	deck[30] = Card(3,1,2,4,'o','b','m','n');
	deck[31] = Card(4,1,2,3,'o','n','m','b');
	deck[32] = Card(3,1,4,2,'n','m','o','b');
	deck[33] = Card(4,1,3,2,'m','o','b','n');
	deck[34] = Card(2,3,1,4,'b','n','m','o');
	deck[35] = Card(4,3,2,1,'o','m','b','n');
	deck[36] = Card(2,4,1,3,'n','o','m','b');
	deck[37] = Card(3,2,1,4,'b','n','o','m');
	deck[38] = Card(4,2,1,3,'n','o','b','m');
	deck[39] = Card(3,4,1,2,'m','o','b','n');
	deck[40] = Card(4,3,1,2,'o','m','b','n');
	deck[41] = Card(2,3,4,1,'n','o','m','b');
	deck[42] = Card(2,4,3,1,'b','o','n','m');
	deck[43] = Card(3,2,4,1,'m','o','n','b');
	deck[44] = Card(4,2,3,1,'m','o','n','b');
	deck[45] = Card(3,4,2,1,'o','m','b','n');
        
        Mix_CloseAudio();
}
//a function that take nothing and returns a card
Card Deck::draw() {
    //initialize SDL video and audio
        SDL_Init(SDL_INIT_VIDEO && SDL_INIT_AUDIO);
        SDL_Window *window;                    // Declare a pointer of type window


    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "Card and Deck Objects",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);//make the window red and opague
    SDL_RenderClear(renderer);
    //initialize the mixer audio channel
                Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
                //make a chunk to be played when needed
                Mix_Chunk *Draw = NULL;
                //set the chuck to the draw.wav sound
                Draw = Mix_LoadWAV("draw.wav");
                //play the sound on the first open channel found
                Mix_PlayChannel(-1, Draw, 0);
                //wait to close the window for 200 miliseconds
                SDL_Delay(200);
	Card drawn;//card to be drawn
	int ran;
	bool picked = false;//bool for determining if the card is there or not
	//get a true random int
        std::random_device rd; 
	std::mt19937 mt(rd()); 

	while (!picked) {
                //get the uniform int distribution and pick a number from 0 to 45(46 cards in deck)
		std::uniform_int_distribution<int> dist(0,45);
                //set ran to that distribution based on mt
		ran = dist(mt);
                //check to see if the card is there
		if(!c_deck[ran])
		{
                    //if it is than take it and make it so a card is no longer there in the deck
			c_deck[ran] = true;
			picked = !picked;
			drawn = deck[ran];
		}

	}
        //free and close all sdl things to ensure there are no leaks
        Mix_CloseAudio();
        SDL_Quit();
	return drawn;
}

Deck::Deck(const Deck& orig) {
}

SDL_Renderer * Deck::Show_Card(Card c){
    
    bool quit = false;
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
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_Texture *card = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET, 480, 640);
    SDL_SetRenderTarget(renderer, card);
    filledCircleRGBA(renderer, 200,300,10,0,0,200,400);
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderPresent(renderer);
    SDL_RenderDrawLine(renderer,200,300,300,400);
    SDL_RenderPresent(renderer);
    SDL_RenderDrawLine(renderer,300,400,0,700);
    SDL_RenderPresent(renderer);
    roundedBoxRGBA(renderer,0,0,640,480,255,255,255,255,255); 
    SDL_RenderPresent(renderer);
    SDL_SetRenderTarget(renderer,NULL);
    SDL_RenderCopy(renderer,card,NULL,NULL);
    SDL_RenderPresent(renderer);
    SDL_DestroyWindow(window);
    return renderer;
}

Deck::~Deck() {
}

