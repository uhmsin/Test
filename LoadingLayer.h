//
//  LoadingLayer.h
//  king04
//
//  Created by mac on 14-5-15.
//
//

#ifndef __king04__LoadingLayer__
#define __king04__LoadingLayer__

#include "cocos2d.h"
#include "BaseLayer.h"
USING_NS_CC;
#include "cocos-ext.h"
USING_NS_CC_EXT;


class LoadingLayer : public BaseLayer
{
public:
    virtual bool init(int current_Select, int modeid);
    
    static cocos2d::CCScene* scene(int current_Select, int modeid);
    
    static LoadingLayer* create(int current_Select, int modeid);
    
    void loadingBack(CCObject* pSender);
    
    UILabel* label;
    
    void Loading_Over(float dt);

	void Loading_Res(float dt);
    
    CCArmature* meinv;
    
    int current_Select;
    
    int modeid;
};

#endif /* defined(__king04__LoadingLayer__) */
