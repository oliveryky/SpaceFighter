//
//  world.hpp
//  6010 Final Project
//
//  Created by Oliver Yu on 9/17/18.
//  Copyright © 2018 MSD. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <string>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
using namespace std;

class Display{
    sf::RenderWindow window;
    
    
public:
    Display();
    bool playGame();
    bool gameOver();
};

