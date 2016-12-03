//
//  Game.cpp
//  King
//
//  Created by mac on 14-3-26.
//
//

#include "Game.h"


static Game* game  = NULL;
Game::Game()
{
    hero = NULL;
    gameLayer = NULL;
    hubLayer = NULL;
    menuLayer = NULL;
    shopLayer = NULL;
    jihuo = NULL;
    //fourJihuo = NULL;
}
Game* Game::instance()
{
    if (game == NULL)
    {
        game = new Game();
        game->init();
    }
    return game;
}

bool Game::init()
{
    hero = NULL;
    gameLayer = NULL;
    hubLayer = NULL;
    menuLayer = NULL;
    shopLayer = NULL;
    //fourJihuo = NULL;
    return true;
}