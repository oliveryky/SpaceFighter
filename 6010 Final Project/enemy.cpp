//
//  player.cpp
//  6010 Final Project
//
//  Created by Oliver Yu on 9/17/18.
//  Copyright © 2018 MSD. All rights reserved.
//

#include "enemy.hpp"

//default constructor
Enemy::Enemy(){
}

void Enemy::drawEnemy(sf::RenderWindow& window){
    window.draw(isAcc ? enemyT: enemy);
}

void Enemy::setPos(sf::Vector2f pos){
    enemy.setPosition(pos);
    enemyT.setPosition(pos);
}

void Enemy::move(sf::Vector2f dist){
    boundingBox = enemy.getGlobalBounds();
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
    
    enemy.move(dist);
    enemyT.move(dist);
}


double Enemy::normalize (double angle)
{
    while (angle > 0)
    {
        angle -= 2 * pie;
    }
    while (angle < 0)
    {
        angle += 2 * pie;
    }
    return angle;
}
