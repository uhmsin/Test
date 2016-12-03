//
//  ShopBuyLayer.cpp
//  King
//
//  Created by mac on 14-3-28.
//
//

#include "ShopBuyLayer.h"
#include "Define.h"
ShopBuyLayer* ShopBuyLayer::create(const char* backgroundImage)
{
    ShopBuyLayer* shopBuyLayer = new ShopBuyLayer();
    shopBuyLayer->init(backgroundImage);
    shopBuyLayer->autorelease();
    return shopBuyLayer;
}

bool ShopBuyLayer::init(const char* backgroundImage)
{
    if(!CCLayer::init()){
        return false;
    }
    CCSprite* background = CCSprite::create(backgroundImage);
    this->addChild(background);
  
    CCMenu* shopMenu = CCMenu::create();
    
    this->addChild(shopMenu,2);
    
    CCMenuItem* back = CCMenuItemImage::create("changjingb0001.png", "changjingb0001.png", this, menu_selector(ShopBuyLayer::back));
    
    back->setContentSize(CCSize(500,800));
    
    back->setPosition(background->getContentSize().width/3,30);
    
    back->setPosition(0,0);

    shopMenu->addChild(back);
    
    HUB->setTouchEnabled(false);
    
    return true;
}

void ShopBuyLayer::back(CCObject* pSender)
{
    this->removeFromParentAndCleanup(true);
    HUB->setTouchEnabled(true);
    HUB->removeChild(this);
    gameLayer->resume();
}