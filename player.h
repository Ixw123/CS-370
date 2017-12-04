
/* 
 * File:   player.h
 * Author: Khrys' Pc
 *
 * Created on October 18, 2017, 9:45 PM
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <cstdlib>
#include <string>


using namespace std;

class player {
public:
    player();
    void set_xpos (int);
    void set_ypos (int);
    void set_pname (string);
    void set_resource (int,int,int,int);
    void set_pscore (int);
    void set_num_of_players (int);
    int getxpos();
    int getypos();
    int get_pscore();
    void get_presource();
    int get_num_of_players();
    string get_pname();


private:
    int xpos;
    int ypos;
    int presource;
    int pscore;
    int num_of_players;

};

#endif /* PLAYER_H */

