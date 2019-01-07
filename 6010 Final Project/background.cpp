//
//  player.cpp
//  6010 Final Project
//
//  Created by Oliver Yu on 9/17/18.
//  Copyright © 2018 MSD. All rights reserved.
//

#include "background.hpp"

Background::Background(){
    //normal enemy
    background.setPointCount(5);
    background.setPoint(0, sf::Vector2f(0, 0));
    background.setPoint(1, sf::Vector2f(-40, 120));
    background.setPoint(2, sf::Vector2f(-25, 105));
    background.setPoint(3, sf::Vector2f(25, 105));
    background.setPoint(4, sf::Vector2f(40, 120));
    background.setFillColor(sf::Color(0, 0, 0));
    background.setOutlineThickness(2);
    background.setOutlineColor(sf::Color(255, 255, 255));
}

void Background::drawBackground(sf::RenderWindow& window){
    window.draw(isAcc ? backgroundT: background);
}

void Background::setPos(sf::Vector2f pos){
    background.setPosition(pos);
    backgroundT.setPosition(pos);
}

void Background::move(sf::Vector2f dist){
    boundingBox = background.getGlobalBounds();
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
    
    background.move(dist);
    backgroundT.move(dist);
    
}


double Background::normalize (double angle)
{
    while (angle > 0)
    {
        angle -= 2 * piee;
    }
    while (angle < 0)
    {
        angle += 2 * piee;
    }
    return angle;
}
