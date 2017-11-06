/*
 * File: Main_Menu.cpp
 * Author: Micah A Church
 * Created on November 4, 2017, 2:20 PM
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "Main_Menu.h"

#include <iostream>
#include <cstring>
#include <string>

using namespace std;

/*
 Makes the Pause Menu; stops all movement and waits for the player who paused to 
 select a choice
 
 Continue - Resume the game where left off
 Save - Saves the game state for all players and quits the game for the user
 Cancel - Resumes the game
*/
int Pause() {
    
    Mix_Music *music = NULL;
    bool quit = false;
    int ans = 0;
    int x,y,Screen_H, Screen_W;
    int flags=MIX_INIT_OGG|MIX_INIT_MOD;
        
    Screen_H = 480;
    Screen_W = 640;
        
    SDL_Init(SDL_INIT_VIDEO && SDL_INIT_AUDIO);
    Mix_Init(flags);
    TTF_Init();
    
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
        
    SDL_Event event;
    SDL_Window *window;
    window = SDL_CreateWindow(
        "Pause Menu", 
	SDL_WINDOWPOS_UNDEFINED, //Starting x coordinate for window
	SDL_WINDOWPOS_UNDEFINED, //Starting y coordinate for window
	Screen_W,                     //Width of the window
	Screen_H,                     //Height of the window
	0                        //Flags
	);
    music = Mix_LoadMUS( "song.MP3" );
    Mix_PlayMusic(music, -1);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0); 
    SDL_SetRenderDrawColor(renderer, 0,0,255,255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    TTF_Font * font = TTF_OpenFont("arial.ttf", 50);
    SDL_Color black = {0, 0, 0};
    SDL_Color white = {255,255,255};
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_Surface * surface = TTF_RenderText_Solid(font, "Pause", black);  
    
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surface);
    
    /*
     Create a text box rectangle for the question
    */
    SDL_Rect Message_rect;
    Message_rect.x = 50;  //controls the rect's x coordinate  
    Message_rect.y = 20;    //controls the rect's y coordinte
    Message_rect.w = 540;  //controls the width of the rect
    Message_rect.h = 50;   //controls the height of the rect
    
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    SDL_RenderPresent(renderer);

    surface = TTF_RenderText_Solid(font, "Continue", white);
    Message = SDL_CreateTextureFromSurface(renderer, surface);
    /*
    Create a Yes button to return a 1 to the call 
    */
    SDL_Rect Continue; //create a rectangle to hold a message
    Continue.x = 540/2;  //controls the rect's x coordinate 
    Continue.y = 150;    //controls the rect's y coordinte
    Continue.w = 100;  //controls the width of the rect
    Continue.h = 30;   //controls the height of the rect
    SDL_RenderCopy(renderer, Message, NULL, &Continue);
    SDL_RenderPresent(renderer);
    
    //SDL_RenderFillRect(renderer, &Yes_rect);

    surface = TTF_RenderText_Solid(font, "Save", white);
    Message = SDL_CreateTextureFromSurface(renderer, surface);
    /*
     Create a no button to return a 0
    */
    SDL_Rect Save; //create a rectangle to hold a message
    Save.x = 540/2;  //controls the rect's x coordinate 
    Save.y = 250;    //controls the rect's y coordinte
    Save.w = 100;  //controls the width of the rect
    Save.h = 30;   //controls the height of the rect
    SDL_RenderCopy(renderer, Message, NULL, &Save);
    SDL_RenderPresent(renderer);
    
    surface = TTF_RenderText_Solid(font, "Cancel", white);
    Message = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect Cancel; //create a rectangle to hold a message
    Cancel.x = 540/2;  //controls the rect's x coordinate 
    Cancel.y = 350;    //controls the rect's y coordinte
    Cancel.w = 100;  //controls the width of the rect
    Cancel.h = 30;   //controls the height of the rect
    SDL_RenderCopy(renderer, Message, NULL, &Cancel);
    SDL_RenderPresent(renderer);

    while (!quit){
       SDL_WaitEvent(&event);
       		SDL_GetMouseState(&x, &y);//set x and y to where the mouses coordinates are
                //SDL_RenderPresent(renderer);

       		if (x >= Continue.x && x <= Continue.x + Continue.w && y >= Continue.y && y <= Continue.y + Continue.h)
			/*
			Checks if the pointer is inside the area of the rect, 
			Checks if the mouse's x-coordinate is greater than the origin but less than the origin plus
			width
			*/
			{
				//SDL_SetTextureColorMod(Message, 255, 0, 0);//Changes the color if the mouse is over the button 
                                SDL_RenderPresent(renderer);
				if (event.type == SDL_MOUSEBUTTONUP)//on mouse release
					if (event.button.button == SDL_BUTTON_LEFT) {
						ans = 1;
						quit = true;
					}

			}
                        
			else if (x >= Save.x && x <= Save.x + Save.w && y >= Save.y && y <= Save.y + Save.h) 
			/*
			Checks if the pointer is inside the area of the rect, 
			Checks if the mouse's x-coordinate is greater than the origin but less than the origin plus
			width
			*/
			{
				//SDL_SetTextureColorMod(Message, 255, 0, 128);//Changes the color if the mouse is over the button
                                
				if (event.type == SDL_MOUSEBUTTONUP)//on mouse release
					if (event.button.button == SDL_BUTTON_LEFT) {
						ans = 2;
						quit = true;
					}

			}
                else if (x >= Cancel.x && x <= Cancel.x + Cancel.w && y >= Cancel.y && y <= Cancel.y + Cancel.h) 
			/*
			Checks if the pointer is inside the area of the rect, 
			Checks if the mouse's x-coordinate is greater than the origin but less than the origin plus
			width
			*/
			{
				//SDL_SetTextureColorMod(Message, 255, 0, 128);//Changes the color if the mouse is over the button
                                
				if (event.type == SDL_MOUSEBUTTONUP)//on mouse release
					if (event.button.button == SDL_BUTTON_LEFT) {
						ans = 3;
						quit = true;
					}

			}
		else if (event.type == SDL_QUIT)
			quit = true;
                switch (ans){
                    case 1:
                        SDL_DestroyWindow(window);
                        break;
                    case 2:
                        SDL_DestroyWindow(window);
                        //Save_Game();
                        Main_Menu();
                        break;
                    case 3:
                        SDL_DestroyWindow(window);
                        break;
                };
	}
    Mix_FreeMusic( music );
    Mix_CloseAudio();
    music = NULL;
    Mix_Quit();
    SDL_Quit();
    return ans;
} 





