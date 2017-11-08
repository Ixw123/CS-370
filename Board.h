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
    void start_game();
    Init_Board( int);
    Display_Board( bool );
    Player_Location( int, int, int, int, int*, int* );
    Add_Card( int ,int );
    Add_Entries( int, bool, Card, int, int );
    Check_Commodity( int, int, int );
    Pickup_Commodity( int, int, int );
    Increment_Entries( int, bool, int );
    Path_Trace( int, int, int, int*, int* );
    
private:
    int Path_Change[28][5][2] ;
    bool Card_Precense[28][5];
           
    
};



#endif /* BOARD_H */

