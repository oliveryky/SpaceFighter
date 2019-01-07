//
//  player.hpp
//  6010 Final Project
//
//  Created by Oliver Yu on 9/17/18.
//  Copyright © 2018 MSD. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "bullet.hpp"
using namespace std;

const double pi = 3.14159265358979323846;
class Player
{
public:
    sf::Sprite shape;
    sf::Texture *texture;
    sf::Sprite shapeAcc;
    sf::Texture *textureAcc;

    bool isAcc;
    int HP;
    int HPMax;
    int score;
    std::vector<Bullet> bullets;
    sf::Vector2f direction;
    sf::Vector2f currentVel;
    float maxVel, acc, friction;
    //used for collision
    inline const sf::Vector2f getPos()const{return shapeAcc.getPosition();}
    inline const sf::FloatRect getGlobalBounds()const{return shapeAcc.getGlobalBounds();};

    Player(sf::Texture *texture, sf::Texture *textureAcc)
    {
        this->HPMax = 3;
        this->HP = this->HPMax;

        this->texture = texture;
        this->shape.setTexture(*texture);
        
        this->textureAcc = textureAcc;
        this-> shapeAcc.setTexture(*textureAcc);
        this->shape.setScale(1.1f, 1.1f);
        this->shapeAcc.setScale(1.1f, 1.1f);
        
        maxVel = 15.f;
        acc = 0.8f;
        friction = 0.5f;
        isAcc = true;
    }

    ~Player() {}

};


class Ship{
    int x, y;
    sf::ConvexShape ship;
    sf::ConvexShape shipT;
    vector<float> direction = {0, 0};
    double normalize (double angle);
    
    //TODO: for collision
    sf::FloatRect boundingBox;
    
public:
    bool isAcc, tLeft, tRight, shooting;
    Ship();
    
    void drawShip(sf::RenderWindow& window);
    
    void setPos(sf::Vector2f pos);
    
    float getX() {return x;}
    
    float getY() {return y;}
    
    void move(sf::Vector2f dist);
    
    void setAcc(bool isAcc);
    
    void turnLeft();
    
    void turnRight();
};

#endif /* player_hpp */
