/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Card.h
 * Author: micah
 *
 * Created on September 20, 2017, 10:07 PM
 */

#ifndef CARD_H
#define CARD_H

#include <SDL2/SDL.h>

class Card {
public:
    Card();
    Card(int,int,int,int,char,char,char,char);
    char* get_coms(Card);
    char get_com(int);
    SDL_Renderer * Show_Card(Card, SDL_Rect);
    int *get_paths(Card);
    void print(Card);
    virtual ~Card();
private:
    int start[4];
    int end[4];
    char com[4];
    bool c_com[4];

};

#endif /* CARD_H */

