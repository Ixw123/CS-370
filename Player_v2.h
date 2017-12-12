/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.h
 * Author: Travis
 *
 * Code Marked with the following "//Lazy Foo" are adapted from Lazy Foo' Productions (http://lazyfoo.net/) with Lazy Foo’s express permission
 * 
 * Created on October 10, 2017, 10:30 PM
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <SDL2\SDL.h> 
#include <string>
#include <SDL2\SDL_image.h> 
#include <windows.h>

using namespace std;

/*
 * 
 */

#ifdef main
#undef main
#endif

//Constants
const int WindowWidth = 640;
const int WindowHeight = 480;
string Player_Path_One = "C:/Users/Travis/Documents/NetBeansProjects/Timetravel_Player_v2/Tardis_v2_Ship.gif"; //Player_Piece.gif
string Player_Path_Two = "C:/Users/Travis/Documents/NetBeansProjects/Timetravel_Player_v2/DeLorean_v2_Ship.gif";
string Player_Path_Three = "C:/Users/Travis/Documents/NetBeansProjects/Timetravel_Player_v2/Time_Box_Ship.gif";
string Player_Path_Four = "C:/Users/Travis/Documents/NetBeansProjects/Timetravel_Player_v2/Timemachine_v2_Ship.gif";

class ATexture //Lazy Foo 
{
    public:
        //Initializes and then deallocates variables
        ATexture();
        ~ATexture();
        
        //Loads player images from specified system path. (Default 2 players, up to 4 or 5)
        bool LoadPlayers (std::string path_one , std::string path_two , std::string path_three , std::string path_four , int p);
        
        //Deallocates the texture.
        void Deallocate();
        
        //Sets the color modulation, blend mode, and the alpha
        void setColor(Uint8 red , Uint8 green , Uint8 blue);
	void setBlendMode(SDL_BlendMode blending);
	void setAlpha(Uint8 alpha);
        
        //Renders texture at specific point
	void Texture_Renderer(int p , int x , int y , SDL_Rect* clip = NULL , double angle = 0.0 , SDL_Point* center = NULL , SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets Width and Height of the Image 
	int getWidth();
	int getHeight();
        
        //Getter and Setter method for P
        int Get_P();
        void Set_P(int p);
        
    private: 
        
        //Player that is moving
        int P;

        //The Width and Height of the Image
        int Width;
        int Height;
};

//Image Texture
SDL_Texture* I_Texture[4];

//Returns P
int ATexture::Get_P()
{
    return (P);
};

//Sets P
void ATexture::Set_P(int p)
{
    P = p;
};

//The Image of the User that can move around the board
class Player //Lazy Foo
{
    public:
	//Constants
        static const int Player_Width = 30;
	static const int Player_Height = 30;
	static const int Player_Velocity = 5;

	//Initializes the variables
	Player(int Pos_X, int Pos_Y); //Not Lazy Foo

	//Takes key presses and adjusts the dot's velocity
	void handleEvent( SDL_Event& e );

	//Moves the Player and checks for a collision. If collision moves player away.
	void move_away();

	//Shows the dot on the screen
	void Texture_Renderer(int p);
        
        //Setter methods for velocity
        void Set_Vel_X (int x);
        void Set_Vel_Y (int y);

    private:
	//The X and Y positions and the velocities of the dot
	int Position_X;
        int Position_Y;
	int Velocity_X;
        int Velocity_Y;
};

//Sets x velocity
void Player::Set_Vel_X(int x)
{
  
    Velocity_X = x;
    
};

//Sets y velocity
void Player::Set_Vel_Y(int y)
{
  
    Velocity_Y = y;
    
};

//Deallocates Texture
void ATexture::Deallocate()
{
    if( I_Texture[0] != NULL )
    {
        SDL_DestroyTexture(I_Texture[0]);
        I_Texture[0] = NULL;
        Width = 0;
        Height = 0;
    }
    if( I_Texture[1] != NULL )
    {
        SDL_DestroyTexture(I_Texture[1]);
        I_Texture[1] = NULL;
        Width = 0;
        Height = 0;
    }
    if( I_Texture[2] != NULL )
    {
        SDL_DestroyTexture(I_Texture[2]);
        I_Texture[2] = NULL;
        Width = 0;
        Height = 0;
    }
    if( I_Texture[3] != NULL )
    {
        SDL_DestroyTexture(I_Texture[3]);
        I_Texture[3] = NULL;
        Width = 0;
        Height = 0;
    }
}

//Sets color
void ATexture::setColor(Uint8 red, Uint8 green, Uint8 blue) //Lazy Foo
{
	SDL_SetTextureColorMod(I_Texture[0], red, green, blue);
        SDL_SetTextureColorMod(I_Texture[1], red, green, blue);
        SDL_SetTextureColorMod(I_Texture[2], red, green, blue);
        SDL_SetTextureColorMod(I_Texture[3], red, green, blue);
}

//Sets blend mode
void ATexture::setBlendMode(SDL_BlendMode blending) //Lazy Foo
{
	SDL_SetTextureBlendMode(I_Texture[0], blending);
        SDL_SetTextureBlendMode(I_Texture[1], blending);
        SDL_SetTextureBlendMode(I_Texture[2], blending);
        SDL_SetTextureBlendMode(I_Texture[3], blending);
}
	
//Sets Alpha
void ATexture::setAlpha(Uint8 alpha) //Lazy Foo
{
	SDL_SetTextureAlphaMod(I_Texture[0], alpha);
	SDL_SetTextureAlphaMod(I_Texture[1], alpha);
	SDL_SetTextureAlphaMod(I_Texture[2], alpha);
	SDL_SetTextureAlphaMod(I_Texture[3], alpha);
}

//Starts SDL and then creates a window
bool init();

//Loads media
bool Load_Media(string s_one , string s_two , string s_three , string s_four , int p);

//Deallocates media and shuts down SDL
void close();

//The window being rendering to
SDL_Window* A_Window = NULL;

//The window renderer
SDL_Renderer* A_Renderer;

//Textures
ATexture A_Textures;

//Sets rendering variables for space, clip, and then renders to the screen
void ATexture::Texture_Renderer(int p , int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) //Lazy Foo
{
	SDL_Rect renderQuad = {x, y, Width, Height};
	if(clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
        switch(p)
        {
            case 0: 
                SDL_RenderCopyEx(A_Renderer, I_Texture[0], clip, &renderQuad, angle, center, flip);
                break;
            case 1: 
                SDL_RenderCopyEx(A_Renderer, I_Texture[1], clip, &renderQuad, angle, center, flip);
                break;
            case 2: 
                SDL_RenderCopyEx(A_Renderer, I_Texture[2], clip, &renderQuad, angle, center, flip); 
                break;
            case 3: 
                SDL_RenderCopyEx(A_Renderer, I_Texture[3], clip, &renderQuad, angle, center, flip); 
                break;
        }
        /*SDL_RenderCopyEx(A_Renderer[1], I_Texture[1], clip, &renderQuad, angle, center, flip);
        SDL_RenderCopyEx(A_Renderer[2], I_Texture[2], clip, &renderQuad, angle, center, flip);
        SDL_RenderCopyEx(A_Renderer[3], I_Texture[3], clip, &renderQuad, angle, center, flip);*/
}

ATexture::ATexture()
{
	//Initialize
        I_Texture[1] = NULL;
        I_Texture[2] = NULL;
        I_Texture[3] = NULL;
	I_Texture[0] = NULL;
	Width = 0;
	Height = 0;
}

ATexture::~ATexture()
{
	//Deallocates
	Deallocate();
}


SDL_Surface* loadedSurface[4];

SDL_Texture* Texture_List[4];

bool ATexture::LoadPlayers(std::string path_one , std::string path_two , std::string path_three , std::string path_four , int p)
{
        //Sets Player
        Set_P(p);
    
	//Erasing previous texture
	Deallocate();

	//Load image at specified path, colors, and displays it
	loadedSurface[0] = IMG_Load(path_one.c_str());
        loadedSurface[1] = IMG_Load(path_two.c_str());
        loadedSurface[2] = IMG_Load(path_three.c_str());
        loadedSurface[3] = IMG_Load(path_four.c_str());
        Texture_List[0] = SDL_CreateTextureFromSurface(A_Renderer , loadedSurface[0]);
        Texture_List[1] = SDL_CreateTextureFromSurface(A_Renderer , loadedSurface[1]);
        Texture_List[2] = SDL_CreateTextureFromSurface(A_Renderer , loadedSurface[2]);
        Texture_List[3] = SDL_CreateTextureFromSurface(A_Renderer , loadedSurface[3]);
		
	//Get image Width and Height
	Width = loadedSurface[p]->w;
        Height = loadedSurface[p]->h;   
                        
	//Get frees old surface
        SDL_FreeSurface(loadedSurface[0]);
        SDL_FreeSurface(loadedSurface[1]);
        SDL_FreeSurface(loadedSurface[2]);
        SDL_FreeSurface(loadedSurface[3]);

	//Return success
        I_Texture[0] = Texture_List[0];
        I_Texture[1] = Texture_List[1];
        I_Texture[2] = Texture_List[2];
        I_Texture[3] = Texture_List[3];
	return I_Texture[P] != NULL;
}

//Gets Width
int ATexture::getWidth()
{
	return Width;
}

//Gets Height
int ATexture::getHeight()
{
	return Height;
}
class PlayerInput
{
    //Asks for number of Players. (default 2, max 4)
    int PlayerCount();
};

Player::Player(int Pos_X, int Pos_Y)
{
    //Initialize the offsets
    Position_X = Pos_X;
    Position_Y = Pos_Y;

    //Initialize the velocity
    Velocity_X = 0;
    Velocity_Y = 0;
}

void Player::handleEvent(SDL_Event& e)
{
    //Tests for key press
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //Changes velocity according to arrow key pressed
        switch(e.key.keysym.sym)
        {
            case SDLK_UP: 
                Velocity_Y = Velocity_Y - Player_Velocity; 
                break;
            case SDLK_DOWN: 
                Velocity_Y = Velocity_Y + Player_Velocity; 
                break;
            case SDLK_LEFT: 
                Velocity_X = Velocity_X - Player_Velocity; 
                break;
            case SDLK_RIGHT:
                Velocity_X = Velocity_X + Player_Velocity; 
                break;
            case SDLK_RETURN:
                Velocity_X = 0;
                Velocity_Y = 0;
                break;
        }
    }
    //Tests for key release
    else if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        //Changes velocity according to arrow key pressed
        switch(e.key.keysym.sym)
        {
            case SDLK_UP:  
                Velocity_X = 0;
                Velocity_Y = 0;
                //Velocity_Y = Velocity_Y + Player_Velocity; 
                break;
            case SDLK_DOWN:  
                Velocity_X = 0;
                Velocity_Y = 0;
                //Velocity_Y = Velocity_Y - Player_Velocity; 
                break;
            case SDLK_LEFT:  
                Velocity_X = 0;
                Velocity_Y = 0;
                //Velocity_X = Velocity_X + Player_Velocity; 
                break;
            case SDLK_RIGHT:  
                Velocity_X = 0;
                Velocity_Y = 0;
                //Velocity_X = Velocity_X - Player_Velocity; 
                break;
            case SDLK_RETURN:
                Velocity_X = 0;
                Velocity_Y = 0;
                break;
        }
    }
}

void Player::move_away()
{
    //Move the player left or right
    Position_X = Position_X + Velocity_X;

    //If the player moved too far to the left or right
    if((Position_X < 0) || (Position_X + Player_Width > WindowWidth))
    {
        //Move away
        Position_X = Position_X - Velocity_X;
    }

    //Move the player up or down
    Position_Y = Position_Y + Velocity_Y;

    //If the player moved too far up or down
    if((Position_Y < 0) || (Position_Y + Player_Height > WindowHeight))
    {
        //Move away
        Position_Y = Position_Y - Velocity_Y;
    }
}

void Player::Texture_Renderer(int p)
{
    //Render Player to screen
    A_Textures.Texture_Renderer(p , Position_X, Position_Y);
}

bool init()
{
    bool success = true;
        
    //Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

        //Create window
        A_Window = SDL_CreateWindow("Player Mover", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowWidth, WindowHeight, SDL_WINDOW_SHOWN);
        if(A_Window == NULL)
        {
            success = false;
        }
        else
        {
            //Create "vsynced" renderer for window
            A_Renderer = SDL_CreateRenderer(A_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(A_Renderer == NULL)
            {
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor(A_Renderer, 255, 255, 255, 255);

                //Initialize PNG
                int imgFlags = IMG_INIT_PNG;
                if( !(IMG_Init(imgFlags) & imgFlags) )
                {
                    success = false;
                }
            }
            
	}
    }
    return success;
}

//Loads player textures
bool Load_Media(string s_one , string s_two , string s_three , string s_four , int p)
{
    bool success = true;
    if( !A_Textures.LoadPlayers(s_one, s_two , s_three , s_four , p))
    {
	success = false;
    }
    return success;
}

void close()
{
	//Deallocate loaded images
	A_Textures.Deallocate();

	//Destroy renderer and window	
	SDL_DestroyRenderer(A_Renderer);
	SDL_DestroyWindow(A_Window);
	A_Window = NULL;
	A_Renderer = NULL;

	//Stop SDL
	IMG_Quit();
	SDL_Quit();
}

class Player_One : public Player
{
public:
    Player_One(int Pos_X , int Pos_Y):Player (Pos_X , Pos_Y)
    {
        
    }
};

class Player_Two : public Player
{
public:
    Player_Two(int Pos_X , int Pos_Y):Player (Pos_X , Pos_Y)
    {
        
    }
};

class Player_Three : public Player
{
public:
    Player_Three(int Pos_X , int Pos_Y):Player (Pos_X , Pos_Y)
    {
        
    }
};

class Player_Four : public Player
{
public:
    Player_Four(int Pos_X , int Pos_Y):Player (Pos_X , Pos_Y)
    {
        
    }
};

#endif /* PLAYER_H */

