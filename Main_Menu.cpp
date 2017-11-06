/*
 File: Main_Menu.cpp
 Author: Micah A Church
 Created on November 2, 2017, 4:26PM
*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "Main_Menu.h"
#include "Card.h"
#include "Deck.h"

#include <iostream>
#include <cstring>
#include <string>

using namespace std;

/*
Makes The main Menu window for the game with numerous options for the user to choose from
New Game - Start a new game
Load Game - Load a previously saved game
Instructions - Display the instructions for the user
Quit - Exit the game
*/

void Main_Menu() {

    Mix_Music *music = NULL;
    bool quit = false;
    int ans = 0;
    int x,y,Screen_H, Screen_W;
    int flags=MIX_INIT_OGG|MIX_INIT_MOD;
        
    Screen_H = 480;
    Screen_W = 640;
        
    SDL_Init( SDL_INIT_VIDEO && SDL_INIT_AUDIO );
    Mix_Init(flags); 
    TTF_Init();
    
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    
    SDL_Event event;
    SDL_Window *window;
    window = SDL_CreateWindow(
	"Main Menu", 
	SDL_WINDOWPOS_UNDEFINED, //Starting x coordinate for window
	SDL_WINDOWPOS_UNDEFINED, //Starting y coordinate for window
	Screen_W,                     //Width of the window
	Screen_H,                     //Height of the window
	0                        //Flags
	);
    music = Mix_LoadMUS( "menu.MP3" );
    Mix_PlayMusic(music, -1);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0,0,255,255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    TTF_Font * font = TTF_OpenFont("arial.ttf", 50);
    SDL_Color black = {0, 0, 0};
    SDL_Color white = {255,255,255};
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_Surface * surface = TTF_RenderText_Solid(font, "Time Traders", black);
    
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surface);
    
    /*
     Create a text box rectangle for the question
    */
    SDL_Rect Message_rect;
    Message_rect.x = 0;  //controls the rect's x coordinate  
    Message_rect.y = 0;    //controls the rect's y coordinte
    Message_rect.w = 640;  //controls the width of the rect
    Message_rect.h = 50;   //controls the height of the rect
    
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    SDL_RenderPresent(renderer);

    surface = TTF_RenderText_Solid(font, "New Game", white);
    Message = SDL_CreateTextureFromSurface(renderer, surface);
    /*
    Create a Yes button to return a 1 to the call 
    */
    SDL_Rect New; //create a rectangle to hold a message
    New.x = 540/2;  //controls the rect's x coordinate 
    New.y = 100;    //controls the rect's y coordinte
    New.w = 100;  //controls the width of the rect
    New.h = 30;   //controls the height of the rect
    SDL_RenderCopy(renderer, Message, NULL, &New);
    SDL_RenderPresent(renderer);
    
    //SDL_RenderFillRect(renderer, &Yes_rect);

    surface = TTF_RenderText_Solid(font, "Load Game", white);
    Message = SDL_CreateTextureFromSurface(renderer, surface);
    /*
     Create a no button to return a 0
    */
    SDL_Rect Load; //create a rectangle to hold a message
    Load.x = 540/2;  //controls the rect's x coordinate 
    Load.y = 200;    //controls the rect's y coordinte
    Load.w = 100;  //controls the width of the rect
    Load.h = 30;   //controls the height of the rect
    SDL_RenderCopy(renderer, Message, NULL, &Load);
    SDL_RenderPresent(renderer);
    
    surface = TTF_RenderText_Solid(font, "Instructions", white);
    Message = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect Ins_rect; //create a rectangle to hold a message
    Ins_rect.x = 540/2;  //controls the rect's x coordinate 
    Ins_rect.y = 300;    //controls the rect's y coordinte
    Ins_rect.w = 100;  //controls the width of the rect
    Ins_rect.h = 30;   //controls the height of the rect
    SDL_RenderCopy(renderer, Message, NULL, &Ins_rect);
    SDL_RenderPresent(renderer);
    
    surface = TTF_RenderText_Solid(font, "Quit", white);
    Message = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect Quit; //create a rectangle to hold a message
    Quit.x = (640-70)/2;  //controls the rect's x coordinate 
    Quit.y = 400;    //controls the rect's y coordinte
    Quit.w = 70;  //controls the width of the rect
    Quit.h = 30;   //controls the height of the rect
    SDL_RenderCopy(renderer, Message, NULL, &Quit);
    SDL_RenderPresent(renderer);

    while (!quit){
       SDL_WaitEvent(&event);
       		SDL_GetMouseState(&x, &y);//set x and y to where the mouses coordinates are
                //SDL_RenderPresent(renderer);

       		if (x >= New.x && x <= New.x + New.w && y >= New.y && y <= New.y + New.h)
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
                        
			else if (x >= Load.x && x <= Load.x + Load.w && y >= Load.y && y <= Load.y + Load.h) 
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
                else if (x >= Ins_rect.x && x <= Ins_rect.x + Ins_rect.w && y >= Ins_rect.y && y <= Ins_rect.y + Ins_rect.h) 
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
                else if (x >= Quit.x && x <= Quit.x + Quit.w && y >= Quit.y && y <= Quit.y + Quit.h) 
			/*
			Checks if the pointer is inside the area of the rect, 
			Checks if the mouse's x-coordinate is greater than the origin but less than the origin plus
			width
			*/
			{
				//SDL_SetTextureColorMod(Message, 255, 0, 128);//Changes the color if the mouse is over the button
                                
				if (event.type == SDL_MOUSEBUTTONUP)//on mouse release
					if (event.button.button == SDL_BUTTON_LEFT) {
						quit = true;
					}

			}
		else if (event.type == SDL_QUIT)
			quit = true;
                switch (ans){
                    case 1:
                        SDL_DestroyWindow(window);
                        Start_Game();
                        break;
                    case 2:
                        SDL_DestroyWindow(window);
                        Load_Game();
                        break;
                    case 3:
                        SDL_DestroyWindow(window);
                        Ins();
                        break;
                };
	}
    Event_Ignore();
    Mix_FreeMusic( music );
    Mix_CloseAudio();
    music = NULL;
    Mix_Quit();
    SDL_Quit();
  
} 

void Start_Game (){
}

void Load_Game(){
}

void Ins(){
    bool quit = false;
    int win,ans,x,y,Screen_H, Screen_W, page, Instructions;
    ifstream file;
    streampos pos = 1;
    
    file.open("Instruction.txt");
    
    pos = file.tellg();
    
    page = 1;
    Instructions = 2;
    ans = 0;
        
        Screen_H = 480;
        Screen_W = 640;
            
        SDL_Init(SDL_INIT_EVERYTHING);
        TTF_Init();
        
	SDL_Event event;
	SDL_Window *window;
	window = SDL_CreateWindow(
		"Instructions", 
		SDL_WINDOWPOS_UNDEFINED, //Starting x coordinate for window
		SDL_WINDOWPOS_UNDEFINED, //Starting y coordinate for window
		Screen_W,                     //Width of the window
		Screen_H,                     //Height of the window
		0                        //Flags
		);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0,0,255,255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    TTF_Font * font = TTF_OpenFont("arial.ttf", 50);
    SDL_Color black = {0, 0, 0};
    SDL_Color white = {255,255,255};
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_Surface * surface = TTF_RenderText_Solid(font, "How to Play", black);
    
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surface);
    
    /*
     Create a text box rectangle for the question
    */
    SDL_Rect Header;
    Header.x = 0;  //controls the rect's x coordinate  
    Header.y = 0;    //controls the rect's y coordinte
    Header.w = 640;  //controls the width of the rect
    Header.h = 50;   //controls the height of the rect
    
    SDL_RenderCopy(renderer, Message, NULL, &Header);
    SDL_RenderPresent(renderer);
    
    SDL_Rect Rules;
    Rules.x = 0;  //controls the rect's x coordinate  
    Rules.y = 0;    //controls the rect's y coordinte
    Rules.w = 640;  //controls the width of the rect
    Rules.h = 50;   //controls the height of the rect
    
    SDL_RenderCopy(renderer, Message, NULL, &Rules);
    SDL_RenderPresent(renderer);
    
    surface = TTF_RenderText_Solid(font, "Next", white);
    Message = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect Next;
    Next.x = 540;  //controls the rect's x coordinate  
    Next.y = 450;    //controls the rect's y coordinte
    Next.w = 100;  //controls the width of the rect
    Next.h = 30;   //controls the height of the rect
    
    SDL_RenderCopy(renderer, Message, NULL, &Next);
    SDL_RenderPresent(renderer);
    
    if(page == 0)
        surface = TTF_RenderText_Solid(font, "Cancel", white);
    else
        surface = TTF_RenderText_Solid(font, "Back", white);
    
    Message = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect Back_Cancel;
    Back_Cancel.x = 0;  //controls the rect's x coordinate  
    Back_Cancel.y = 450;    //controls the rect's y coordinte
    Back_Cancel.w = 100;  //controls the width of the rect
    Back_Cancel.h = 30;   //controls the height of the rect
    
    SDL_RenderCopy(renderer, Message, NULL, &Back_Cancel);
    SDL_RenderPresent(renderer);
    
    while (!quit)
    {
        SDL_WaitEvent(&event);
        SDL_GetMouseState(&x, &y);//set x and y to where the mouses coordinates are
                //SDL_RenderPresent(renderer);

       		if (x >= Next.x && x <= Next.x + Next.w && y >= Next.y && y <= Next.y + Next.h && page <= Instructions)
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
                        
			else if (x >= Back_Cancel.x && x <= Back_Cancel.x + Back_Cancel.w && y >= Back_Cancel.y && y <= Back_Cancel.y + Back_Cancel.h) 
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
                        else if (x >= Back_Cancel.x && x <= Back_Cancel.x + Back_Cancel.w && y >= Back_Cancel.y && y <= Back_Cancel.y + Back_Cancel.h && page == 0) 
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
                        Load_Next();
                        page++;
                        break;
                    case 2:
                        Load_Previous();
                        page--;
                        break;
                    case 3:
                        SDL_DestroyWindow(window);
                        Main_Menu();
                        break;
                };
                
     }
    SDL_Quit();
}

void Load_Next() {
    /*streampos newpos;
    string buffer;
    streamoff off;
    
    getline(file,buffer);
    line = &buffer;
    //file.ignore(std::numeric_limits<std::streamsize>::max(), '\n')
    newpos = oldpos + sizeof(buffer);
    
    return newpos;*/
}

void Load_Previous() {
    /*string buffer;
    streampos newpos;
    
    buffer = *line;
    newpos = oldpos - (sizeof(buffer));
    
    return newpos;*/
}

void Event_Ignore() {
    int Screen_H = 480;
        int Screen_W = 640;
            
        SDL_Init(SDL_INIT_EVERYTHING);
        TTF_Init();
        
	SDL_Event event;
	SDL_Window *window;
	window = SDL_CreateWindow(
		"Instructions", 
		SDL_WINDOWPOS_UNDEFINED, //Starting x coordinate for window
		SDL_WINDOWPOS_UNDEFINED, //Starting y coordinate for window
		Screen_W,                     //Width of the window
		Screen_H,                     //Height of the window
		0                        //Flags
		);
    
}
