//
//  BaseLayer.h
//  King
//
//  Created by mac on 14-3-26.
//
//

#ifndef __King__BaseLayer__
#define __King__BaseLayer__

#include "cocos2d.h"
#include "PersonalAudioEngine.h"
USING_NS_CC;
class BaseLayer : public CCLayer
{
public:
    CREATE_FUNC(BaseLayer);
    virtual bool init();
    virtual void keyBackClicked();
    virtual void keyMenuClicked();
  
    bool isExit;
};
#endif /* defined(__King__BaseLayer__) */
