//
//  Counter.cpp
//  King
//
//  Created by mac on 14-4-20.
//
//

#include "Counter.h"

#include "Counter.h"
#include "Define.h"
USING_NS_CC;
enum{
    k_Counter_Action = 0
};
Counter::Counter()
{
    _digit = 0;
}
Counter* Counter::create(CCArray* presenters, int digit)
{
    Counter* counter = new Counter();
    counter->init(presenters, digit);
    counter->autorelease();
    return counter;
}
bool Counter::init(CCArray* presenters, int digit)
{
    _presenters = CCNode::create();
    for (int i = 0; i < 10; i++) {
        CCNode* node = (CCNode*)presenters->objectAtIndex(i);
        int y = node->getContentSize().height*i;
        node->setPosition(CCPointMake(0, y));
        _presenters->addChild(node, 0, i);
    }
    this->addChild(_presenters);
    this->setDigit(digit);
    return true;
}
void Counter::setDigit(int digit)
{
   // if(_digit != digit){
        _digit = digit;
        animation(digit);
    //}
}

void Counter::setDigit2(int digit)
{
    // if(_digit != digit){
    _digit = digit;
    animation2(digit);
    //}
}

void Counter::animation2(int digit)
{
    CCNode* presenter = _presenters->getChildByTag(digit);
    CCPoint dest = presenter->getPosition();
    _presenters->stopAllActions();
    _presenters->setPositionY(-dest.y);
}


int Counter::getDigit()
{
    return _digit;
}
void Counter::animation(int digit)
{
    CCNode* presenter = _presenters->getChildByTag(digit);
    CCPoint dest = presenter->getPosition();
    _presenters->stopAllActions();
    CCArray *arrayOfActions = CCArray::create();
    for (int i=0 ; i<50; i++) {
        int rands =  CCRANDOM_0_1()*8+1;
        CCNode* presenter1 = _presenters->getChildByTag(rands);
        CCPoint dest1 = presenter1->getPosition();
        CCMoveTo* move = CCMoveTo::create(0.05,CCPointMake(0,-dest1.y) );
        arrayOfActions->addObject(move);
    }
    CCMoveTo* moveTo = CCMoveTo::create(0.1, CCPointMake(0,-dest.y));
    arrayOfActions->addObject(moveTo);
    CCSequence* seq = CCSequence::create(arrayOfActions);
    _presenters->runAction(seq);
}

void Counter::visit()
{
    CCSize Truesize =CCDirector::sharedDirector()->getOpenGLView()->getFrameSize(); //CCDirector::sharedDirector()->getVisibleSize();
    glEnable(GL_SCISSOR_TEST);
    CCNode* presenter = _presenters->getChildByTag(_digit);
    CCSize size = presenter->getContentSize();
    CCPoint location = this->getParent()->convertToWorldSpaceAR(CCPointMake(this->getPosition().x-size.width*0.5, this->getPosition().y-size.height*0.5));
    glScissor(location.x*Truesize.width/SIZE.width, location.y*Truesize.height/SIZE.height, Truesize.width/SIZE.width*size.width, Truesize.height/SIZE.height*size.height);
    CCNode::visit();
    glDisable(GL_SCISSOR_TEST);
}