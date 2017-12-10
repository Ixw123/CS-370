/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Travis
 *
 * Created on September 10, 2017, 10:42 PM
 */

#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include <string>
#include "Board.h"
#include "Card.h"
#include "Deck.h"
#include <SDL_image.h>

using namespace std;

/*
 * 
 */
#ifdef main
#undef main
#endif

//Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
  
//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables and then deallocates memory
		LTexture();
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );
                
		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set Alpha
		void setAlpha( Uint8 alpha );
		
		//Renders texture at specific point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets Width and Height of image 
		int getWidth();
		int getHeight();

	private:
		//The texture
		SDL_Texture* Texture;

		//Image Width and Height
		int Width;
		int Height;
};

//The image(dot) that user can move around the screen
class Dot
{
    public:
	//The Width and Height of the dot
        static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	//Maximum X velocity of the dot
	static const int DOT_VEL = 10;

	//Initializes the variables
	Dot();

	//Takes key presses and adjusts the dot's velocity
	void handleEvent( SDL_Event& e );

	//Moves the dot and checks for a collision
	void move();

	//Shows the dot on the screen
	void render();

    private:
	//The X and Y offsets of the dot
	int Position_X, Position_Y;

	//The velocity of the dot
	int Velocity_X, Velocity_Y;
};

//Starts up SDL and creates a window
bool init();

//void Player_move( SDL_Renderer* );

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window being rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture gDotTexture;

LTexture::LTexture()
{
	//Initialize
	Texture = NULL;
	Width = 0;
	Height = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Erasing previous texture
	free();

	//Final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format , 0 , 0xFF , 0xFF ) );

		//Create texture from surface pixels
                newTexture = SDL_CreateTextureFromSurface( gRenderer , loadedSurface );
		
		//Get image Width and Height
		Width = loadedSurface->w;
                Height = loadedSurface->h;   
                        
		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	Texture = newTexture;
	return Texture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if( Texture != NULL )
	{
		SDL_DestroyTexture( Texture );
		Texture = NULL;
		Width = 0;
		Height = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture RGB
	SDL_SetTextureColorMod( Texture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( Texture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( Texture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, Width, Height };

	//Set clip rendering Width and Height
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, Texture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	return Width;
}

int LTexture::getHeight()
{
	return Height;
}


Dot::Dot()
{
    //Initialize the offsets
    Position_X = 320;
    Position_Y = 240;

    //Initialize the velocity
    Velocity_X = 0;
    Velocity_Y = 0;
}

void Dot::handleEvent( SDL_Event& e )
{
    //tests for key being pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjusts velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: 
                Velocity_Y -= DOT_VEL; 
                break;
            case SDLK_DOWN: 
                Velocity_Y += DOT_VEL; 
                break;
            case SDLK_LEFT: 
                Velocity_X -= DOT_VEL; 
                break;
            case SDLK_RIGHT:
                Velocity_X += DOT_VEL; 
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
                Velocity_Y += DOT_VEL; 
                break;
            case SDLK_DOWN: 
                Velocity_Y -= DOT_VEL; 
                break;
            case SDLK_LEFT: 
                Velocity_X += DOT_VEL; 
                break;
            case SDLK_RIGHT: 
                Velocity_X -= DOT_VEL; 
                break;
        }
    }
}

void Dot::move()
{
    //Move the dot left or right
    Position_X += Velocity_X;

    //If the dot went too far to the left or right
    if( ( Position_X < 0 ) || ( Position_X + DOT_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        Position_X -= Velocity_X;
    }

    //Move the dot up or down
    Position_Y += Velocity_Y;

    //If the dot went too far up or down
    if( ( Position_Y < 0 ) || ( Position_Y + DOT_HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        Position_Y -= Velocity_Y;
    }
}

void Dot::render()
{
    //Show dot
	gDotTexture.render( Position_X, Position_Y );
}

bool init()
{
	//Initialization flag
	bool success = true;
        
        
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		
			//Create vsynced renderer for window
				//Initialize renderer color
				

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                                        
					success = false;
				}
			}
		
	

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load dot texture
	if( !gDotTexture.loadFromFile( "C:/Users/T420/Documents/NetBeansProjects/Time_Traders/Tardis_v2_Ship.gif"  ))
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded images
	gDotTexture.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void Player_move( SDL_Renderer *renderer )
{
                if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The Players that will be moving around on the screen
			Dot dot;
                        //Dot dot_blue;
                        //Dot dot_green;
                        //Dot dot_red;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle input for the dot
					dot.handleEvent( e );
				}

				//Move the dot
				dot.move();

				//Clear screen
				SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );

				//Render objects

				//Update screen
				SDL_RenderPresent( renderer );
			}
		}
	}
}

	//Free resources and close SDL


