
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
#include <boost/archive/basic_binary_oarchive.hpp>
#include <boost/archive/basic_binary_iarchive.hpp>


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

player::player()
{
    cout << "Player Created!"  ;  
}
    set_xpos (int x)
    {
        xpos = x;
    }
    void set_ypos (int y)
    {
        ypos = y;
    }
    void set_pname (string n)
    {
        string pname = n;
    }
    void set_resource (int m, int o, int b, int n)
    {
         milkbread = m;
         oilpetrol = o;
         beatcandy = b;
         nucleons = n;
        
    }
    void setpscore (int s)
    {
        pscore = s;
    }
    void set_num_of_players (int nop)
    {
        num_of_players = nop;
    }
    int getxpos()
    {
        return xpos ;
    }
    int getypos()
    {
        return ypos;
    }
    int get_pscore()
    {
        return pscore;
    }
    void get_presource()
    {
        
        cout << "Milkbread = "<< milkbread ;
        cout << "Oilpetrol = "<< oilpetrol ;
        cout << "Beatcandy = "<< beatcandy ;
        cout << "Nucleons = "<< nucleons ;
        
    }
    int get_num_of_players()
    {
        return num_of_players;
    }
    string get_pname()
    {
        return pname;
    }
    
    void save ()
    {
        //serialize 
    }
    void load ()
    {
        //deserialize
    }
