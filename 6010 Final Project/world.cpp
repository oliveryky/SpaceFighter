//
//  world.cpp
//  6010 Final Project
//
//  Created by Oliver Yu on 9/17/18.
//  Copyright © 2018 MSD. All rights reserved.
//

#include "world.hpp"
#include "player.hpp"
#include "bullet.hpp"
#include "enemy.hpp"
#include "background.hpp"

#include <vector>

Display::Display(){
    this -> window.create(sf::VideoMode(1080, 1920), "Asteroids");
    srand((unsigned)time(nullptr));
    window.setFramerateLimit(60); //can alter later if you want to increase graphical goodness
    //create variables
    Ship ship{};
    
    //create another window to prompt if the user wants to play
    if (playGame()){ //if they want to play, render the below information
        window.clear();
        window.display();
    }
    
    ship.setPos({860, 440});
    window.setKeyRepeatEnabled(true);
    
    //player code
    sf::Texture playerTex;
    playerTex.loadFromFile("starfox_ship.png");
    sf::Texture playerTexAccel;
    playerTexAccel.loadFromFile("starfox_ship.png");
    Player player(&playerTex, &playerTexAccel);
    player.shape.setPosition(window.getSize().x /2, window.getSize().y/2);
    player.shapeAcc.setPosition(window.getSize().x /2, window.getSize().y/2);
    std::vector<Bullet> bullets;
    int shootTimer = 0;
    player.score = 0;
    
    //Score init
    sf::Font scoreFont;
    if (!scoreFont.loadFromFile("CFGlitchCity-Regular.ttf")){
        std::cout << "ERROR: font failed to load.\n";
        exit(0);
    }
    sf::Text scoreText;
    scoreText.setFont(scoreFont);
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 10.f);
    
    //Hit points
    sf::Text hpText;
    sf::Font hpFont;
    if (!hpFont.loadFromFile("TravelingTypewriter.ttf")){
        std::cout << "ERROR: font failed to load.\n";
        exit(0);
    }
    hpText.setFont(hpFont);
    hpText.setCharacterSize(25);
    hpText.setFillColor(sf::Color::White);
    hpText.setStyle(sf::Text::Bold);
    hpText.setPosition(player.getPos().x, player.getPos().y + 100.f);
    
    //enemy related code
    sf::RectangleShape enemy;
    enemy.setFillColor(sf::Color::Magenta);
    enemy.setSize(sf::Vector2f(50.f, 50.f));
    
    std::vector<sf::RectangleShape> enemies;
    enemies.push_back(sf::RectangleShape(enemy));
    int enemySpawnTimer = 0;
    const int SPAWN_INCREMENT_TIMER = 1800; //spawnIncrementTimer set to 30 seconds
    
    //Vectors
    sf::Vector2f playerCenter;
    sf::Vector2f mousePosWindow;
    sf::Vector2f aimDir;
    sf::Vector2f aimDirNorm;
    
    //background related code
    sf::RectangleShape background;
    background.setFillColor(sf::Color::White);
    background.setSize(sf::Vector2f(5.f, 5.f));
    
    std::vector<sf::RectangleShape> backgrounds;
    backgrounds.push_back(sf::RectangleShape(background));
    int backgroundSpawnTimer = 0;
    
    //load textures/sprites
    sf::Texture bulletTex;
    bulletTex.loadFromFile("laser_sprite.jpg");
    
    while (window.isOpen())
    {
        
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        
        //player
        float moveSpeed = 10.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            player.direction.x = 0;
            player.direction.y = player.getPos().y <= 20 ? 12.f : -12.f;
            
            //            if (player.getPos().y <= 20){
            //                moveSpeed *= -1;
            //            }
            player.shape.move(player.direction.x, player.direction.y);
            player.shapeAcc.move(player.direction.x, player.direction.y);
            ship.isAcc = true; //reminder to do acceleration
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player.direction.x = 2.f;
            player.direction.y = 0.f;
            
            player.currentVel.y += player.currentVel.y > 0 ? -0.2f: 0.2f;
            if(player.currentVel.x < player.maxVel && player.direction.x > 0){
                player.currentVel.x += player.direction.x * 2.0 * player.acc;
            }
            
            if(player.currentVel.x > 0){
                player.currentVel.x -= player.friction;
                if(player.currentVel.x < 0){
                    player.currentVel.x = 0;
                }
            }else if(player.currentVel.x < 0){
                player.currentVel.x += player.friction;
                if(player.currentVel.x > 0){
                    player.currentVel.x = 0;
                }
            }
            
            if (player.getPos().x >= window.getSize().x - 100){
                player.currentVel.x *= -1;
            }
            //            player.currentVel.x = player.getPos().x >= window.getSize().x - 100 ? 2.f:-2.f;
            player.shape.move(player.currentVel);
            player.shapeAcc.move(player.currentVel);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player.direction.x = -2.f;
            player.direction.y = 0.f;
            player.currentVel.y += player.currentVel.y > 0 ? -0.2f:0.2f;
            if(player.currentVel.x > -player.maxVel && player.direction.x < 0){
                player.currentVel.x += player.direction.x * 2.0*player.acc;
            }
            
            
            if(player.currentVel.x > 0){
                player.currentVel.x -= player.friction;
                if(player.currentVel.x < 0){
                    player. currentVel.x = 0;
                }
            }else if(player.currentVel.x < 0){
                player.currentVel.x += player.friction;
                if(player.currentVel.x > 0){
                    player.currentVel.x = 0;
                }
            }
            if (player.getPos().x <= 0){
                player.currentVel.x *= -1;
            }
            player.shape.move(player.currentVel);
            player.shapeAcc.move(player.currentVel);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            if (player.getPos().y >= window.getSize().y - 100){
                moveSpeed *= -1;
            }
            player.shape.move(0.f, moveSpeed);
            player.shapeAcc.move(0.f, moveSpeed);
            ship.isAcc = false;
        }
        
        //Enemies
        enemySpawnTimer++;
        if (enemySpawnTimer >= SPAWN_INCREMENT_TIMER*4 && (enemySpawnTimer % 12 == 0)){
            enemy.setPosition((rand() % int(window.getSize().x - enemy.getSize().x)), 0.f);
            enemies.push_back(sf::RectangleShape(enemy));
        } else if (enemySpawnTimer < SPAWN_INCREMENT_TIMER*4 && enemySpawnTimer >= SPAWN_INCREMENT_TIMER*3 && (enemySpawnTimer % 36 == 0)){
            enemy.setPosition((rand() % int(window.getSize().x - enemy.getSize().x)), 0.f);
            enemies.push_back(sf::RectangleShape(enemy));
        } else if (enemySpawnTimer < SPAWN_INCREMENT_TIMER*3 && enemySpawnTimer >= SPAWN_INCREMENT_TIMER*2 && (enemySpawnTimer % 48 == 0)){
            enemy.setPosition((rand() % int(window.getSize().x - enemy.getSize().x)), 0.f);
            enemies.push_back(sf::RectangleShape(enemy));
        } else if (enemySpawnTimer < SPAWN_INCREMENT_TIMER*2 && enemySpawnTimer >= SPAWN_INCREMENT_TIMER && (enemySpawnTimer % 60 == 0)){
            enemy.setPosition((rand() % int(window.getSize().x - enemy.getSize().x)), 0.f);
            enemies.push_back(sf::RectangleShape(enemy));
        } else if (enemySpawnTimer < SPAWN_INCREMENT_TIMER && (enemySpawnTimer % 72 == 0)){ //less than 30 seconds
            enemy.setPosition((rand() % int(window.getSize().x - enemy.getSize().x)), 0.f);
            enemies.push_back(sf::RectangleShape(enemy));
        }
        
        for (size_t i = 0; i < enemies.size(); i++) { //if the enemy moves out of bounds, erase them
            enemies[i].move(0.f, 10.f);
            if(enemies[i].getGlobalBounds().intersects(player.getGlobalBounds())){ //collision check for player
                enemies.erase(enemies.begin() + i);
                player.HP--;
                if (player.HP <= 0){
                    if(gameOver()){
                        player.HP = 3;
                        player.score = 0;
                        enemySpawnTimer = 0;
                        backgroundSpawnTimer = 0;
                    }
                    
                }
            }
            if (enemies[i].getPosition().y > window.getSize().y){ //enemy goes out of bounds, so erase them
                enemies.erase(enemies.begin() + i);
                break;
            }
        }
        
        
        //Shooting
        if (shootTimer < 20) shootTimer++; //increment the timer.
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootTimer >= 20){
            player.bullets.push_back(Bullet(&bulletTex, player.shapeAcc.getPosition()));
            shootTimer = 0; //reset timer
        }
        
        //Bullets
        for (size_t i = 0; i < player.bullets.size(); i++)
        {
            //Move
            player.bullets[i].shape.move(0.f, -10.f);
            
            //Out of window bounds
            if (player.bullets[i].shape.getPosition().y < 0) //expire once it exits the playfield
            {
                player.bullets.erase(player.bullets.begin() + i);
                break;
            }
            
            //Enemy collision with bullets
            for (size_t k = 0; k < enemies.size(); k++)
            {
                if (player.bullets[i].shape.getGlobalBounds().intersects(enemies[k].getGlobalBounds())){
                    player.score += 100;
                    enemies.erase(enemies.begin() + k);
                    player.bullets.erase(player.bullets.begin() + i);
                    break;
                }
            }
        }
        //Score Update
        scoreText.setString("SCORE " + std::to_string(player.score));
        window.draw(scoreText); //display score
        
        //HP update
        hpText.setPosition(player.getPos().x, player.getPos().y + 100.f);
        window.draw(hpText); //display HP
        
        //Background
        if(backgroundSpawnTimer < 20){
            backgroundSpawnTimer++;
        }
        
        if (backgroundSpawnTimer >= 20){
            background.setPosition((rand() % int(window.getSize().x - background.getSize().x)), 0.f);
            backgrounds.push_back(sf::RectangleShape(background));
            backgroundSpawnTimer = 0;
        }
        
        for (size_t i = 0; i < backgrounds.size(); i++) {
            backgrounds[i].move(0.f, 5.f);
            if (backgrounds[i].getPosition().y > window.getSize().y) //star is leaving the screen
                backgrounds.erase(backgrounds.begin() + i);
        }
        
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed){
                window.close();
            }
            //            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down){
            //                ship.isAcc = true;
            //            }
            
            
            
            //HP Update
            hpText.setString(std::to_string(player.HP) + "/" + std::to_string(player.HPMax));
        }
        
        // end the current frame
        window.clear();
        
        //if statement for acceleration or not (player.isAcc? player.shapeT: player.shape)
        window.draw(player.isAcc? player.shapeAcc: player.shape);
        
        window.draw(scoreText); //display score
        window.draw(hpText); //display HP
        
        for (size_t i = 0; i < enemies.size(); i++) {
            window.draw(enemies[i]);
        }
        for (size_t i = 0; i < backgrounds.size(); i++) {
            window.draw(backgrounds[i]);
        }
        for (size_t i = 0; i < player.bullets.size(); i++)
        {
            window.draw(player.bullets[i].shape);
        }
        
        window.display();
    }
}

bool Display::playGame(){
    bool pressedSpace = false;
    
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        sf::Font font;
        if (!font.loadFromFile("CFGlitchCity-Regular.ttf")){
            std::cout << "ERROR: font failed to load.\n";
            exit(0);
        }
        
        sf::Text textTitle;
        sf::Text textPrompt;
        // select the font
        textTitle.setFont(font);
        textPrompt.setFont(font);
        // set the string to display
        textTitle.setString("STAR FOX");
        textPrompt.setString("PRESS THE SPACEBAR TO PLAY");
        // set the character size
        textTitle.setCharacterSize(100); // in pixels, not points!
        textPrompt.setCharacterSize(40);
        // set the color
        textTitle.setFillColor(sf::Color::White);
        textPrompt.setFillColor(sf::Color::Red);
        // set the text style
        textTitle.setStyle(sf::Text::Bold);
        textPrompt.setStyle(sf::Text::Italic);
        //change where the text appears
        sf::FloatRect textRect = textTitle.sf::Text::getLocalBounds();
        textTitle.setPosition(sf::Vector2f(textRect.height/.5f,textRect.width/.5f));
        textPrompt.setPosition(sf::Vector2f(textRect.height/.47f,textRect.width/.47f));
        
        //clear the window and draw the text
        window.clear();
        window.draw(textTitle);
        window.draw(textPrompt);
        window.display();
        
        
        //get either space bar or close pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            pressedSpace = true;
            break; //space is pressed so now you can exit loop
        }
        
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
    }
    return pressedSpace;
}


bool Display::gameOver(){
    bool pressedSpace = false;
    
    while (window.isOpen())
    {
        window.clear();
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        sf::Font font;
        if (!font.loadFromFile("CFGlitchCity-Regular.ttf")){
            std::cout << "ERROR: font failed to load.\n";
            exit(0);
        }
        
        sf::Text textTitle;
        sf::Text textPrompt;
        // select the font
        textTitle.setFont(font);
        textPrompt.setFont(font);
        // set the string to display
        textTitle.setString("GAME OVER");
        textPrompt.setString("PRESS THE SPACEBAR TO PLAY AGAIN");
        // set the character size
        textTitle.setCharacterSize(100); // in pixels, not points!
        textPrompt.setCharacterSize(40);
        // set the color
        textTitle.setFillColor(sf::Color::White);
        textPrompt.setFillColor(sf::Color::Red);
        // set the text style
        textTitle.setStyle(sf::Text::Bold);
        textPrompt.setStyle(sf::Text::Italic);
        //change where the text appears
        sf::FloatRect textRect = textTitle.sf::Text::getLocalBounds();
        textTitle.setPosition(sf::Vector2f(textRect.height/1.f,textRect.width/1.f));
        textPrompt.setPosition(sf::Vector2f(textRect.height/.75f,textRect.width/.75f));
        
        //clear the window and draw the text
        window.clear();
        window.draw(textTitle);
        window.draw(textPrompt);
        window.display();
        
        
        //get either space bar or close pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            pressedSpace = true;
            break; //space is pressed so now you can exit loop
        }
        
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
    }
    return pressedSpace; //TODO this might go in above bracket
}







