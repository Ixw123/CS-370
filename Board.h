/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Board.h
 * Author: Douglas
 *
 * Created on November 6, 2017, 1:04 PM
 */

#ifndef BOARD_H
#define BOARD_H

#include "Card.h"
#include "Deck.h"
#include "SDL.h"

class Board {
public: 
    Board();
    void handleEvent( SDL_Event& ,int *, int * ,int *,int *,int,int,Board,SDL_Renderer*,SDL_Texture*, bool*);
    void start_game();
    void Display_Commodities(char [28][5]);
    void move(int* ,int*,int,int);
    void Init_Board( int);
    void Display_Board( SDL_Renderer*, SDL_Texture*, int, int);
    void Player_Location( int, int, int, int, int*, int* );
    void Add_Card( Card, int, int, int, int);
    void Add_Entries( int, bool, Card, int, int );
    bool Check_Commodity( int, int );
    void Pickup_Commodity( int, int );
    void Increment_Entries( int, bool, int );
    void Path_Trace( int, int, int*, int* );
    
private:
    Deck d;
    int Paths[28][5];
    Card c;
    int Path_Change[28][5][2];
    bool Card_Precense[28][5];
    char Board_Commodities[28][5];
    Card Card_Array[5][7];
    int Start_Array[5];
    
};



#endif /* BOARD_H */

