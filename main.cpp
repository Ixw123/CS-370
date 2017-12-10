/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: T420
 *
 * Created on November 7, 2017, 11:52 PM
 */

#include <cstdlib>
#include "Main_Menu.h"
#include "Board.h"

using namespace std;

#ifdef main
#undef main
#endif

int main(int argc, char** argv) 

{
    int Path_Change[28][5][2];
    bool Card_Presence[28][5];
    
    //Card Card_Array[5][7];
    //int Start_Array[5];
    Board b;
    b.start_game();
    cout << 3;
    //start_game( &Path_Change[0][0][0], Card_Array, &Start_Array[0] );
    return 0;
}
