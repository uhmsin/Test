//
//  GoldCounterLayer.cpp
//  King
//
//  Created by mac on 14-4-20.
//
//

#include "GoldCounterLayer.h"
#include "Counter.h"

USING_NS_CC;

GoldCounterLayer::~GoldCounterLayer()
{
    CC_SAFE_RELEASE_NULL(arraysCounter);
}

GoldCounterLayer::GoldCounterLayer()
{
    weishu = 0;
    arraysCounter = NULL;
}
GoldCounterLayer* GoldCounterLayer::create(int number)
{
    GoldCounterLayer* goldCounterLayer = new GoldCounterLayer();
    goldCounterLayer->init(number);
    goldCounterLayer->autorelease();
    return goldCounterLayer;
}
bool GoldCounterLayer::init(int number)
{
    arraysCounter = CCArray::create();
    arraysCounter->retain();

    char weishuChar[10] = {0};
    sprintf(weishuChar, "%d",number);
    weishu = strlen(weishuChar);
    for(int i = 0 ;i < weishu;i++){
        int count = 10;
        CCArray* presenters = CCArray::createWithCapacity(count);
        for(int j = 0;j < count;j++){
			CCSprite* label = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("qtsz_%d.png", j)->getCString());
            label->setScale(0.6);
            presenters->addObject(label);
        }
		CCSprite* label1 = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("qtsz_%d.png", 1)->getCString());
        label1->setScale(0.6);
        Counter* counter = Counter::create(presenters);
        counter->setPosition(CCPointMake(0.6*label1->getContentSize().width*i, 0));
        this->addChild(counter, 0, i);
        arraysCounter->addObject(counter);
    }
    this->setNumber(number);
    return true;
}
void GoldCounterLayer::setNumber(int number, int ceiling)
{
    number = MIN(ceiling, number);
    number = MAX(number, 0);
    _number = number;
    for(int i = 0 ;i < weishu;i++){
        Counter* counter =dynamic_cast<Counter*>(arraysCounter->objectAtIndex(i));
        int digit = _number / (int)(pow(10.0, weishu-i-1)) % 10;
        counter->setDigit(digit);
    }
}

void GoldCounterLayer::setNumbet2(int number,int ceiling)
{
    number = MIN(ceiling, number);
    number = MAX(number, 0);
    _number = number;
    for(int i = 0 ;i < weishu;i++){
        Counter* counter =dynamic_cast<Counter*>(arraysCounter->objectAtIndex(i));
        int digit = _number / (int)(pow(10.0, weishu-i-1)) % 10;
        counter->setDigit2(digit);
    }
}
