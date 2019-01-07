//
//  enemy.hpp
//  Asteroids
//
//  Created by Will Dunn on 9/18/18.
//  Copyright © 2018 Will Dunn. All rights reserved.
//

#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

const double pie = 3.14159265358979323846;

class Enemy{
    int x, y;
    sf::ConvexShape enemy;
    sf::ConvexShape enemyT;
    std::vector<float> direction = {0, 0};
    double normalize (double angle);
    
    //TODO: for collision
    sf::FloatRect boundingBox;
    
public:
    bool isAcc, tLeft, tRight, shooting;
    Enemy();
    
    void drawEnemy(sf::RenderWindow& window);
    
    void setPos(sf::Vector2f pos);
    
    void move(sf::Vector2f dist);
    
};
