
//Using SDL and standard IO
#include <SDL2/SDL.h>   
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <iostream>


#ifdef main
#undef main
#endif

const int S_W = 640; //Screen Height
const int S_H = 480; //Screen Width

//Function Headers
//Initializes SDL and creates the window
bool init();

//Load Media
bool loadMedia();

//Frees media, closes window 
void close();

//Load individual image as texture
SDL_Texture* loadTexture( std::string path );

//The displayed window
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;



bool init()
{
    //Initialize Boolean Flag
    bool success = true;
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Initialize TTF
        if( TTF_Init() == -1 )
        {
            printf("TTF could not initialize! TTF Error: %s\n", TTF_GetError() );
            success = false;
        }
        else
        {
           //Load font 
            TTF_Font *font; 
            font = TTF_OpenFont( "OpenSans-Regular.ttf", 12 );
            if( !font )
            {
                printf( "Could not load font! TTF Error: %s\n", TTF_GetError() );
            }
            else
            {
            
            
                //Set texture filtering to linear
                         
                if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
                {
                    printf( "Warning: Linear texture filtering not enabled!" );
                }
        
                //Create Window
                gWindow = SDL_CreateWindow( "Timeline", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, S_W, S_H, SDL_WINDOW_SHOWN );
                if( gWindow == NULL )
                {
                    printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
                    success = false;
                }
                else
                {
                    //Create renderer for window
                    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
                    if( gRenderer == NULL )
                    {
                        printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
                        success = false;
                    }
                    else
                    {
                        //Initialize renderer color
                        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            
                        //Initialize PNG loading
                        int imgFlags = IMG_INIT_PNG;
                        if( !( IMG_Init( imgFlags ) & imgFlags ) )
                        {
                            printf( "SDL_image could not initalize! SDL_Error: %s\n", SDL_GetError() );
                            success = false;
                        }
            
                    }       
                }
            }
        }
               
    }
    
    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;
    
    //Nothing to load
    return success;
}

void close()
{
    //Destroy Window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    
    
    
    //Quit SDL Subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();    
}


int main(int argc, char** argv) {

    printf("Hello");
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load Media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Main loop flag
            bool quit = false;
            
            //Even handler
            SDL_Event e;
            
            //Run loop
            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    else if( e.type == SDL_MOUSEBUTTONDOWN )
                    {
                     
                    //Reset color to white
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderClear( gRenderer );
                
                    //Reset color to grey
                    SDL_SetRenderDrawColor( gRenderer, 0xCC, 0xCC, 0xCC, 0xCC );
                
                    //Draw basic grid for the cards
                    for( int i = 1; i < 8; i += 1 )
                    {
                        SDL_RenderDrawLine( gRenderer, 0, S_H * i/ 7, S_W, S_H * i / 7 );
                        SDL_RenderDrawLine( gRenderer, S_W * i / 7, 0, S_W * i / 7, S_H );
                    }
                
                    //Reset the color to darker grey
                    SDL_SetRenderDrawColor( gRenderer, 0xB0, 0xB0, 0xB0, 0xB0 );
                
                    //Draw the underlying path lines
                    for( int i = 25; i < 32; i += 2 )
                    {
                        SDL_RenderDrawLine( gRenderer, 0, S_H * i / 56, S_W / 7, S_H * i / 56 );
                    }
                
                    for( int i = 1; i < 56; i += 2 )
                    {
                    SDL_RenderDrawLine( gRenderer, S_W / 7, S_H * i / 56, S_W, S_H * i / 56 );
                    }
                
                    //Reset color to red
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0x00 );
                
                    //Draw points representing commodity placement
                    for( int j = 8; j < 49; j += 7 )
                    {
                        for( int i = 3; i < 224; i += 16 )
                        {
                            SDL_RenderDrawPoint( gRenderer, S_W * j / 49, S_H * i / 224 );
                        }
                    }
                
                    for( int j = 13; j < 49; j += 7 )
                    {
                        for( int i = 11; i < 224; i += 16 )
                        {
                            SDL_RenderDrawPoint( gRenderer, S_W * j / 49, S_H * i / 224 );
                        }
                    }
                
                
                    //Draw Starting card
                    SDL_Rect start = { 0, S_H * 3 / 7, S_W * 1 / 7, S_H * 1 / 7 };
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
                    SDL_RenderFillRect( gRenderer, &start );
                
                    //Draw cards in first column
                    for( int i = 11; i < 16; i +=4 )
                    {
                        SDL_Rect rect20 = { S_W * 1  / 7, S_H * i / 28, S_W * 1 / 7, S_H * 1 / 7 };
                        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
                        SDL_RenderFillRect( gRenderer, &rect20 );
                    }
                
                    //Fill in remaining, unchanged cards
                    for( int i = 2; i < 7; i += 1 )
                    {    
                        SDL_Rect rect21 = { S_W * i  / 7, S_H * 3 / 7, S_W * 1 / 7, S_H * 1 / 7 };
                        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
                        SDL_RenderFillRect( gRenderer, &rect21 );
                    }
                
                    SDL_RenderPresent( gRenderer ); 
                    SDL_Delay( 2000 );
                    break;
                    
                    
                    }
                    else if( e.type == SDL_KEYDOWN )
                    {
                       SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );
                
                
                SDL_SetRenderDrawColor( gRenderer, 0xCC, 0xCC, 0xCC, 0xCC );
                
                //Draw basic underlying grid
                for( int i = 1; i < 8; i += 1 )
                {
                    SDL_RenderDrawLine( gRenderer, 0, S_H * i/ 7, S_W, S_H * i / 7 );
                    SDL_RenderDrawLine( gRenderer, S_W * i / 7, 0, S_W * i / 7, S_H );
                }
                
                SDL_SetRenderDrawColor( gRenderer, 0xB0, 0xB0, 0xB0, 0xB0 );
                
                //Draw underlying paths
                for( int i = 25; i < 32; i += 2 )
                {
                    SDL_RenderDrawLine( gRenderer, 0, S_H * i / 56, S_W / 7, S_H * i / 56 );
                }
                
                for( int i = 1; i < 56; i += 2 )
                {
                    SDL_RenderDrawLine( gRenderer, S_W / 7, S_H * i / 56, S_W, S_H * i / 56 );
                }
                
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0x00 );
                
                //Draw underlying proposed commodity spaces
                for( int j = 8; j < 49; j += 7 )
                {
                    for( int i = 3; i < 224; i += 16 )
                    {
                        SDL_RenderDrawPoint( gRenderer, S_W * j / 49, S_H * i / 224 );
                    }
                }
                
                for( int j = 13; j < 49; j += 7 )
                {
                    for( int i = 11; i < 224; i += 16 )
                    {
                        SDL_RenderDrawPoint( gRenderer, S_W * j / 49, S_H * i / 224 );
                    }
                }
                
                SDL_Rect start = { 0, S_H * 3 / 7, S_W * 1 / 7, S_H * 1 / 7 };
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0xFF, 0x00 );
                SDL_RenderFillRect( gRenderer, &start );
                
                //Fill First column
                for( int i = 10; i < 19; i += 4 )
                {    
                SDL_Rect rect30 = { S_W * 1  / 7, S_H * i / 28, S_W * 1 / 7, S_H * 1 / 7 };
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0xFF, 0x00 );
                SDL_RenderFillRect( gRenderer, &rect30 );
                }
                
                for( int i = 9; i < 22; i += 4 )
                {
                SDL_Rect rect31 = { S_W * 2  / 7, S_H * i / 28, S_W * 1 / 7, S_H * 1 / 7 };
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0xFF, 0x00 );
                SDL_RenderFillRect( gRenderer, &rect31 );
                }
                
                SDL_Rect rect32 = { S_W * 3 / 7, S_H * 3 / 7, S_W * 1 / 7, S_H * 1 / 7 };
                SDL_SetRenderDrawColor( gRenderer , 0xFF, 0x00, 0xFF, 0x00 );
                SDL_RenderFillRect( gRenderer, &rect32 );
                
                for( int i = 8; i < 25; i += 4 )
                {
                    SDL_Rect rect33 = { S_W * 4 / 7, S_H * i / 28, S_W * 1 / 7, S_H * 1 / 7 };
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0xFF, 0x00 );
                    SDL_RenderFillRect( gRenderer, &rect33);               
                }
                
                for( int i = 7; i < 12; i += 4 )
                {
                    SDL_Rect rect34 = { S_W * 5 / 7, S_H * i / 28, S_W * 1 / 7, S_H * 1 / 7 };
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0xFF, 0x00 );
                    SDL_RenderFillRect( gRenderer, &rect34 );
                    
                }
                
                //Draw necessary market cards
                for( int i = 1; i < 4; i += 1 )
                {
                    SDL_Rect rect35 = { S_W * 6 / 7, S_H * i / 7, S_W * 1 / 7, S_H * 1 / 7 };
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0xFF, 0x00 );
                    SDL_RenderFillRect( gRenderer, &rect35 );
                }
                    

                SDL_RenderPresent( gRenderer );
                        
                SDL_Delay( 2000 ); 
                break;
                    }
                }
                
                
                
                
                
                
                
                //Set the color to white
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );
                
                //Set the color to grey
                SDL_SetRenderDrawColor( gRenderer, 0xCC, 0xCC, 0xCC, 0xCC );
                
                //Draw the grid, where each space is the size of one card
                for( int i = 1; i < 8; i += 1 )
                {
                    SDL_RenderDrawLine( gRenderer, 0, S_H * i/ 7, S_W, S_H * i / 7 );
                    SDL_RenderDrawLine( gRenderer, S_W * i / 7, 0, S_W * i / 7, S_H );
                }
                
                //Change the draw color to a darker grey
                SDL_SetRenderDrawColor( gRenderer, 0xB0, 0xB0, 0xB0, 0xB0 );
                
                //Draw the underlying paths or the start card
                for( int i = 25; i < 32; i += 2 )
                {
                    SDL_RenderDrawLine( gRenderer, 0, S_H * i / 56, S_W / 7, S_H * i / 56 );
                }
                
                //Draw the underlying paths for all other cards
                for( int i = 1; i < 56; i += 2 )
                {
                    SDL_RenderDrawLine( gRenderer, S_W / 7, S_H * i / 56, S_W, S_H * i / 56 );
                }
                
                //Change color to red
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0x00 );
                
                //Draw points that represent possible commodity points
                for( int j = 8; j < 49; j += 7 )
                {
                    for( int i = 3; i < 224; i += 16 )
                    {
                        SDL_RenderDrawPoint( gRenderer, S_W * j / 49, S_H * i / 224 );
                    }
                }
                
                for( int j = 13; j < 49; j += 7 )
                {
                    for( int i = 11; i < 224; i += 16 )
                    {
                        SDL_RenderDrawPoint( gRenderer, S_W * j / 49, S_H * i / 224 );
                    }
                }
                
                //Create the starting layout of cards               
                for( int i = 0; i < 7; i += 1 )
                {
                SDL_Rect rect = { S_W * i  / 7, S_H * 3 / 7, S_W * 1 / 7, S_H * 1 / 7 };
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0x00 );
                SDL_RenderFillRect( gRenderer, &rect );
                }
                
            SDL_RenderPresent( gRenderer );    
            
            SDL_Delay( 2000 );
            
                
                        
                
            
                
                
                
            
            
            
                
            }
            
            
        }
    }  
    close();
    
    return 0;
}


