/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/* 
 * File:   main.cpp
 * Author: Travis
 *
 * Code Marked with the following "//Lazy Foo" are adapted from Lazy Foo' Productions (http://lazyfoo.net/) with Lazy Foo’s express permission
 * 
 * Created on September 20, 2017, 10:31 AM
 */

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
        bool LoadPlayers (std::string path);
        
        //Deallocates the texture.
        void Deallocate();
        
        //Sets the color modulation, blend mode, and the alpha
        void setColor(Uint8 red , Uint8 green , Uint8 blue);
	void setBlendMode(SDL_BlendMode blending);
	void setAlpha(Uint8 alpha);
        
        //Renders texture at specific point
	void Texture_Renderer(int x , int y , SDL_Rect* clip = NULL , double angle = 0.0 , SDL_Point* center = NULL , SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets Width and Height of the Image 
	int getWidth();
	int getHeight();
        
    private:
        //Image Texture
        SDL_Texture* I_Texture;

        //The Width and Height of the Image
        int Width;
        int Height;
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
	void Texture_Renderer();
        
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
    if( I_Texture != NULL )
    {
        SDL_DestroyTexture(I_Texture);
        I_Texture = NULL;
        Width = 0;
        Height = 0;
    }
}

//Sets color
void ATexture::setColor(Uint8 red, Uint8 green, Uint8 blue) //Lazy Foo
{
	SDL_SetTextureColorMod(I_Texture, red, green, blue);
}

//Sets blend mode
void ATexture::setBlendMode(SDL_BlendMode blending) //Lazy Foo
{
	SDL_SetTextureBlendMode(I_Texture, blending);
}
	
//Sets Alpha
void ATexture::setAlpha(Uint8 alpha) //Lazy Foo
{
	SDL_SetTextureAlphaMod(I_Texture, alpha);
}

//Starts SDL and then creates a window
bool init();

//Loads media
bool Load_Media(string s);

//Deallocates media and shuts down SDL
void close();

//The window being rendering to
SDL_Window* A_Window = NULL;

//The window renderer
SDL_Renderer* A_Renderer = NULL;

//Textures
ATexture A_Textures;

//Sets rendering variables for space, clip, and then renders to the screen
void ATexture::Texture_Renderer(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) //Lazy Foo
{
	SDL_Rect renderQuad = {x, y, Width, Height};
	if(clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(A_Renderer, I_Texture, clip, &renderQuad, angle, center, flip);
}

//Scene textures
ATexture PlayerTexture;

ATexture::ATexture()
{
	//Initialize
	I_Texture = NULL;
	Width = 0;
	Height = 0;
}

ATexture::~ATexture()
{
	//Deallocates
	Deallocate();
}

bool ATexture::LoadPlayers( std::string path )
{
	//Erasing previous texture
	Deallocate();

	//Final texture
	SDL_Texture* New_Texture = NULL;

	//Load image at specified path, colors, and displays it
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format , 0 , 0xFF , 0xFF));
        New_Texture = SDL_CreateTextureFromSurface(A_Renderer , loadedSurface);
		
	//Get image Width and Height
	Width = loadedSurface->w;
        Height = loadedSurface->h;   
                        
	//Get frees old surface
	SDL_FreeSurface(loadedSurface);
	
	//Return success
	I_Texture = New_Texture;
	return I_Texture != NULL;
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
        }
    }
    //Tests for key release
    else if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        //Changes velocity according to arrow key pressed
        switch(e.key.keysym.sym)
        {
            case SDLK_UP: 
                Velocity_Y = Velocity_Y + Player_Velocity; 
                break;
            case SDLK_DOWN: 
                Velocity_Y = Velocity_Y - Player_Velocity; 
                break;
            case SDLK_LEFT: 
                Velocity_X = Velocity_X + Player_Velocity; 
                break;
            case SDLK_RIGHT: 
                Velocity_X = Velocity_X - Player_Velocity; 
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

void Player::Texture_Renderer()
{
    //Render Player to screen
    A_Textures.Texture_Renderer( Position_X, Position_Y );
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
bool Load_Media(string s)
{
    bool success = true;
    if( !A_Textures.LoadPlayers(s))
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

//////////////////////////////////////////////////////
/*MAIN*/
//////////////////////////////////////////////////////

int main(int argc, char** argv) 
{
    //Start SDL and create a window
    init();
    
    //Variables
    bool stop = false;
    int counter = 4;
    int Player_Cycler = 0;
    
    //Get the state of keys
    //const Uint8 *Key_States = SDL_GetKeyboardState(NULL);
    
    //Array of paths for Player textures
    string Player_Paths[4];
    Player_Paths[0] = Player_Path_One;
    Player_Paths[1] = Player_Path_Two;
    Player_Paths[2] = Player_Path_Three;
    Player_Paths[3] = Player_Path_Four;
    
    //Load Media
    Load_Media(Player_Paths[0]);
    //Load_Media(Player_Paths[1]);
    //Load_Media(Player_Paths[2]);
    //Load_Media(Player_Paths[3]);
   
    //Create an instance of event handler
    SDL_Event e;
    
    /*
    //Asks for Player count
    cout<<"How many players? (min 2, max 4)\n";
    cin>>counter;
    
    //If Player count user entered is not valid, try again.
    while (2 > counter > 4)
    {
        if ((counter > 4) || (counter < 2))
        {
            cout<<"You have entered an incorrect number. Please try again.\n";
        } 
        cout<<"How many players? (min 2, max 4)\n";
        cin>>counter;
    }*/
    Player_One ONE (50 , 50);
    Player_Two TWO (50 , 100);
    Player_Three THREE (50 , 150);
    Player_Four FOUR (50 , 200);
    
    /*
    //Creates Players equal to user input
    Player *P_List = new Player[counter](XX, YY);
    
    //Player P_List [counter] = new Player(int x,int y) [counter];
    if (counter = 2)
    {
        Player P_List[2] = {Player(50 , 50) , Player(50 , 100)};
    }
    else if (counter = 3)
    {
        Player P_List[3] = {Player(50 , 50) , Player(50 , 100) , Player(50 , 150)};
    }
    else if (counter = 4)
    {
        Player P_List[4] = {Player(50 , 50) , Player(50 , 100) , Player(50 , 150) , Player(50 , 200)};
    }
    else
    {
        cout<<"An error occurred. Please start again.";
        return 0;
    }*/
    
    //Possible solution to if statements. (?)
    /*for(int i = 0 ; i < counter ; i = i + 1)
    {
        Player P_List [counter];
        P_List [i] = new Player(50 , (50 + (i * 75)));
    }*/
    
    ONE.handleEvent(e);
    TWO.handleEvent(e);
    THREE.handleEvent(e);
    FOUR.handleEvent(e);
    
    //While application is running
    while(!stop)
    {
        //Handle events
        while(SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if(e.type == SDL_QUIT)
            {
                stop = true;
            }

            //Handle input for the player.
            switch (Player_Cycler)
            {
                case 0:    
                    ONE.handleEvent(e);
                    Load_Media(Player_Paths[0]);
                    break;
                    
                case 1:    
                    TWO.handleEvent(e);
                    Load_Media(Player_Paths[1]);
                    break;
                    
                case 2:    
                    THREE.handleEvent(e);
                    Load_Media(Player_Paths[2]);
                    break;
                    
                case 3:    
                    FOUR.handleEvent(e);
                    Load_Media(Player_Paths[3]);
                    break;
            }
        //}
        
        //Test for key press
        if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
        {
        //Changes player upon press of enter key (Player ends turn)
            switch(e.key.keysym.sym)
            {
                case SDLK_RETURN:    
                switch (Player_Cycler)
                {
                    case 0:    
                        Player_Cycler = 1;
                        ONE.Set_Vel_X(0);
                        ONE.Set_Vel_Y(0);
                        TWO.Set_Vel_X(0);
                        TWO.Set_Vel_Y(0);
                        THREE.Set_Vel_X(0);
                        THREE.Set_Vel_Y(0);
                        FOUR.Set_Vel_X(0);
                        FOUR.Set_Vel_Y(0);
                        break;

                    case 1:    
                        Player_Cycler = 2;
                        ONE.Set_Vel_X(0);
                        ONE.Set_Vel_Y(0);
                        TWO.Set_Vel_X(0);
                        TWO.Set_Vel_Y(0);
                        THREE.Set_Vel_X(0);
                        THREE.Set_Vel_Y(0);
                        FOUR.Set_Vel_X(0);
                        FOUR.Set_Vel_Y(0);
                        break;

                    case 2:    
                        Player_Cycler = 3;
                        ONE.Set_Vel_X(0);
                        ONE.Set_Vel_Y(0);
                        TWO.Set_Vel_X(0);
                        TWO.Set_Vel_Y(0);
                        THREE.Set_Vel_X(0);
                        THREE.Set_Vel_Y(0);
                        FOUR.Set_Vel_X(0);
                        FOUR.Set_Vel_Y(0);
                        break;

                    case 3:    
                        Player_Cycler = 0;
                        ONE.Set_Vel_X(0);
                        ONE.Set_Vel_Y(0);
                        TWO.Set_Vel_X(0);
                        TWO.Set_Vel_Y(0);
                        THREE.Set_Vel_X(0);
                        THREE.Set_Vel_Y(0);
                        FOUR.Set_Vel_X(0);
                        FOUR.Set_Vel_Y(0);
                        break;
                }
                    
                    //SDL_Delay(50);
                    break;
            }
        }
        
        //If Player 4 ends turn, goes back to player 1
        if (Player_Cycler > 3)
        {
            Player_Cycler = 0;
        }
        
        }
        
        //Move the dot
        ONE.move_away();
        TWO.move_away();
        THREE.move_away();
        FOUR.move_away();

        //Clear screen
        SDL_SetRenderDrawColor(A_Renderer, 255, 255, 255, 255);
        SDL_RenderClear(A_Renderer);

        //Render objects
        //P_List[num].Texture_Renderer();
        ONE.Texture_Renderer();
        TWO.Texture_Renderer();
        THREE.Texture_Renderer();
        FOUR.Texture_Renderer();

        //Update screen
        SDL_RenderPresent(A_Renderer);
         
    }
    
    return 0;
}

