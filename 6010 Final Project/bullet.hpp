//
//  bullet.hpp
//  Asteroids
//
//  Created by Will Dunn on 9/18/18.
//  Copyright © 2018 Will Dunn. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <math.h>
#include <vector>
#include <cstdlib>

//LENGTH OF VECTOR: |V| = sqrt(V.x^2 + V.y^2)
//NORMALIZE VECTOR: U = V / |V|

class Bullet
{
public:
    sf::Sprite shape;
    
//    sf::CircleShape shape;
//    sf::Vector2f currVelocity;
//    float maxSpeed;
//    Bullet(float radius = 5.f): currVelocity(0.f, 0.f), maxSpeed(15.f) {
//        this->shape.setRadius(radius);
//        this->shape.setFillColor(sf::Color::Red);
//    }
    Bullet(sf::Texture *texture, sf::Vector2f pos) {
        this->shape.setTexture(*texture);
        
        this->shape.setScale(1.f, 1.f);
        this->shape.setPosition(pos);
//        this->shape.setPosition(pos.x + 50, pos.y - 50);
    }
    ~Bullet(){}
};
