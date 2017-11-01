/*
This is a program to quickly understand how serilization works in C++
and how to update that class to an html file and decipher it on other computers

File:Player_initializer_spike.cpp
Author:Micah A Church
Created on October 19, 2017, 2:17

*/
#include <cstring>
#include <string>
#include <fstream> //class for binary serialization (contiguous bytes)
#include <iostream>
#include <sstream>

#include "Player.h"

using namespace std;
 
Player::Player() {
}
void Player::Serialize(Player player){
        try
        {
        p1 = &player;
        string temp;    
        ofstream file;
	file.open("test.txt");  
        
	file << "Player: " << p1->getName() << "\n";
        cout << "Player: " << p1->getName() << "\n";
        file << "PosX: " << p1->getPosX() << "\n";
        cout << "PosX: " << p1->getPosX() << "\n";
        file << "PosY: " << p1->getPosY() << "\n";
        cout << "PosY: " << p1->getPosY() << "\n";
        file << "Milkbread: " << p1->getMilkbread() << "\n";
        cout << "Milkbread: " << p1->getMilkbread() << "\n";
        file << "Beetcandy: " << p1->getBeetcandy() << "\n"; 
        cout << "Beetcandy: " << p1->getBeetcandy() << "\n";
        file << "Nucleons: " << p1->getNucleons() << "\n"; 
        cout << "Nucleons: " << p1->getNucleons() << "\n";
        file << "Oilpetrol: " << p1->getOilpetrol(); 
        cout << "Oilpetrol: " << p1->getOilpetrol() << "\n";
        
        file.close();
        }
        catch(exception e){
                cout << "File Error :Failed to serialize!!!";}
}
void Player::setName(string name){
    name = name;
}
void Player::setPosX(int a){
    x = a;
}
void Player::setPosY(int a){
    y = a;
}
void Player::setMilkbread(int a) {
    milkbread = a;
}
void Player::setNucleons(int a){
    nucleons = a;
}
void Player::setBeetcandy(int a){
    beetcandy = a;
}
void Player::setOilpetrol(int a){
    oilpetrol = a;
}
string Player::getName(){
    return name;
}
int Player::getPosX(){
    return x;
}
int Player::getPosY(){
    return y;
}
int Player::getMilkbread() {
    return milkbread;
}
int Player::getNucleons(){
    return nucleons;
}
int Player::getBeetcandy(){
    return beetcandy;
}
int Player::getOilpetrol(){
    return oilpetrol;
}
Player::Player(string name, int x, int y, int m, int n, int b, int o){
	name = name;
	x = x;
	y = y;
	milkbread = m;
	nucleons = n;
	beetcandy = b;
	oilpetrol = o;
}
void Player::Deserialize(string  file){
    string info;
    int number;
    p1 = new Player();
    
    ifstream input;
    try {
    input.open("text.txt", ios::in);
    while(getline(input,info)){
        p1->setName(info);
        cout << p1->getName();
        istringstream iss (info);
        iss >> number;
        p1->setPosX(number);
        cout << p1->getPosX();
        iss >> number;
        p1->setPosY(number);
        iss >> number;
        p1->setMilkbread(number);
        iss >> number;
        p1->setNucleons(number);
        iss >> number;
        p1->setBeetcandy(number);
        iss >> number;
        p1->setOilpetrol(number);
    }
    
    //getline(input,info);
    
    input.close();
    }
    catch (exception e){ 
        cout << "unable to open file\n" ;}
}