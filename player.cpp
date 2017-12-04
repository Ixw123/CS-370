
/* 
 * File:   player.cpp
 * Author: Khrys' Pc
 * 
 * Created on October 18, 2017, 9:45 PM
 */

#include "player.h"
#include <iostream> 
#include <string>
#include <cstdlib>



using namespace std;
int xpos;
int ypos ;
string pname;
int milkbread ;
int oilpetrol ;
int beatcandy ;
int nucleons ;
int pscore;
int num_of_players;

/*creates instance of player*/ 
player::player()
{
    cout << "Player Created!"  ;  
}
/*sets x */    
set_xpos (int x)
    {
        xpos = x;
    }
/*sets y*/
void set_ypos (int y)
    {
        ypos = y;
    }
/*sets player name*/   
void set_pname (string n)
    {
        string pname = n;
    }
/*sets specific resource*/
    void set_resource (int m, int o, int b, int n)
    {
         milkbread = m;
         oilpetrol = o;
         beatcandy = b;
         nucleons = n;
        
    }
/*set player score*/
    void setpscore (int s)
    {
        pscore = s;
    }
/*sets number of players*/
    void set_num_of_players (int nop)
    {
        num_of_players = nop;
    }
/*returns x pos*/
    int getxpos()
    {
        return xpos ;
    }
/*returns y pos*/    
    int getypos()
    {
        return ypos;
/*returns player score*/
    int get_pscore()
    {
        return pscore;
    }
/*returns which resources were collected*/    
    void get_presource()
    {
        
        cout << "Milkbread = "<< milkbread ;
        cout << "Oilpetrol = "<< oilpetrol ;
        cout << "Beatcandy = "<< beatcandy ;
        cout << "Nucleons = "<< nucleons ;
        
    }
/*returns number of players*/
    int get_num_of_players()
    {
        return num_of_players;
    }
/*saves name for player*/
    string get_pname()
    {
        return pname;
    }
    

 