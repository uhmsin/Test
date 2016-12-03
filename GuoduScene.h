//
//  GuoduScene.h
//  King
//
//  Created by mac on 14-4-18.
//
//

#ifndef __King__GuoduScene__
#define __King__GuoduScene__
#include "cocos2d.h"
USING_NS_CC;
/*class GuoduScene : public CCScene
{
public:
    static GuoduScene* create(int guodu);
    bool init(int guodu);
    void yanchi(float dt);
    int guodu;
};*/
class GuoduScene2 : public CCScene
{
public:
    static GuoduScene2* create();
    bool init();
    void yanchi(float dt);
    int guodu;
};
#endif /* defined(__King__GuoduScene__) */
