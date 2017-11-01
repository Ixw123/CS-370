/*
 * This is the header file to define a class player and serialize and deserialize it
 */

/* 
 * File:   Player.h
 * Author: Micah A Church
 *
 * Created on October 19, 2017, 12:28 AM
 */
#include <string>


using namespace std;

#ifndef PLAYER_H
#define PLAYER_H
class Player {
	public:
		Player();
		Player(std::string,int,int,int,int,int,int);
		void Serialize(Player);
                void Deserialize(string);
                void setName(string);
                void setPosX(int);
                void setPosY(int);
                void setMilkbread(int);
                void setNucleons(int);
                void setBeetcandy(int);
                void setOilpetrol(int);
                string getName(); 
                int getPosX();
                int getPosY();
                int getMilkbread();
                int getNucleons();
                int getBeetcandy();
                int getOilpetrol();
                
                Player * p1;
	private:
		string name;
		int x;
		int y;
		int milkbread;
		int nucleons;
		int beetcandy;
		int oilpetrol;
};


#endif /* PLAYER_H */

