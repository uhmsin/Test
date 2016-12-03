//
//  GuoduScene.cpp
//  King
//
//  Created by mac on 14-4-18.
//
//

#include "GuoduScene.h"
#include "GameScene.h"
#include "SelectScene.h"
/*GuoduScene* GuoduScene::create(int guodu)
{
    GuoduScene* SCENE = new GuoduScene();
    SCENE->init(guodu);
    SCENE->autorelease();
    return SCENE;
}

bool GuoduScene::init(int guodu)
{
    CCLayer* layer = CCLayer::create();
    this->addChild(layer);
    this->guodu = guodu;
    this->scheduleOnce(schedule_selector(GuoduScene::yanchi), 0.02f);
    return true;
}
void GuoduScene::yanchi(float dt)
{
    CCDirector::sharedDirector()->replaceScene( SelectScene::scene());
}*/

GuoduScene2* GuoduScene2::create()
{
    GuoduScene2* SCENE = new GuoduScene2();
    SCENE->init();
    SCENE->autorelease();
    return SCENE;
}

bool GuoduScene2::init()
{
    CCLayer* layer = CCLayer::create();
    this->addChild(layer);
    this->scheduleOnce(schedule_selector(GuoduScene2::yanchi), 0.02f);
    return true;
}
void GuoduScene2::yanchi(float dt)
{
   
    CCScene* scene = GameScene::scene(100,5);
    CCDirector::sharedDirector()->replaceScene(scene);
}

