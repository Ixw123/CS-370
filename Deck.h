/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Deck.h
 * Author: micah
 *
 * Created on September 20, 2017, 9:52 PM
 */

#ifndef DECK_H
#define DECK_H

#include "Card.h"

class Deck {
public:
    Deck();
    Deck(const Deck& orig);
    Card draw ();
    virtual ~Deck();
private:
    Card deck[46];
    bool c_deck[46];
};

#endif /* DECK_H */

