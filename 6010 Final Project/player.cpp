//
//  player.cpp
//  6010 Final Project
//
//  Created by Oliver Yu on 9/17/18.
//  Copyright © 2018 MSD. All rights reserved.
//

#include "player.hpp"
#include "world.hpp"

Ship::Ship(){
    //normal ship
    ship.setPointCount(5);
    ship.setPoint(0, sf::Vector2f(0, 0));
    ship.setPoint(1, sf::Vector2f(-40, 120));
    ship.setPoint(2, sf::Vector2f(-25, 105));
    ship.setPoint(3, sf::Vector2f(25, 105));
    ship.setPoint(4, sf::Vector2f(40, 120));
    ship.setFillColor(sf::Color(0, 0, 0));
    ship.setOutlineThickness(2);
    ship.setOutlineColor(sf::Color(255, 255, 255));
    
    //ship while moving forward/accelerating
    shipT.setPointCount(8);
    shipT.setPoint(0, sf::Vector2f(0, 0));
    shipT.setPoint(1, sf::Vector2f(-40, 120));
    shipT.setPoint(2, sf::Vector2f(-25, 105));
    shipT.setPoint(3, sf::Vector2f(0, 140));
    shipT.setPoint(4, sf::Vector2f(25, 105));
    shipT.setPoint(5, sf::Vector2f(-25, 105));
    shipT.setPoint(6, sf::Vector2f(25, 105));
    shipT.setPoint(7, sf::Vector2f(40, 120));
    shipT.setFillColor(sf::Color(0, 0, 0));
    shipT.setOutlineThickness(2);
    shipT.setOutlineColor(sf::Color(255, 255, 255));
}

void Ship::drawShip(sf::RenderWindow& window){
    window.draw(isAcc ? shipT: ship);
}

void Ship::setPos(sf::Vector2f pos){
    ship.setPosition(pos);
    shipT.setPosition(pos);
}

void Ship::move(sf::Vector2f dist){
    boundingBox = ship.getGlobalBounds();
    if(boundingBox.left < 0-50){
        dist.x = 1920;
    }
    if(boundingBox.left >= 1920){
        dist.x = -1920;
    }
    if(boundingBox.top < 0-115){
        dist.y = 1080;
    }
    if(boundingBox.top >= 1080){
        dist.y = -1080;
    }
    if(tLeft){
        dist.x -= 0.5;
        dist.y += 0.5;
    }
    
    if(tRight){
        dist.x += 0.5;
        dist.y -= 0.5;
    }
    
    ship.move(dist);
    shipT.move(dist);
    
    if(tLeft){
        turnLeft();
    }
    
    if(tRight){
        turnRight();
    }
}

void Ship::setAcc(bool isAcc){
    this -> isAcc = isAcc;
}

void Ship::turnLeft(){
    ship.rotate(-normalize(pi/16));
    shipT.rotate(-normalize(pi/16));
}

void Ship::turnRight(){
    ship.rotate(normalize(pi/16));
    shipT.rotate(normalize(pi/16));
}

double Ship::normalize (double angle)
{
    while (angle > 0)
    {
        angle -= 2 * pi;
    }
    while (angle < 0)
    {
        angle += 2 * pi;
    }
    return angle;
}
