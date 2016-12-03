//
//  MenuLayer.cpp
//  King
//
//  Created by mac on 14-3-30.
//
//

#include "MenuLayer.h"
#include "GameScene.h"
#include "Define.h"
#include "MenuScene.h"
#include "GameData.h"
#include "ShopScene.h"
#include "SelectScene.h"
USING_NS_CC;

void MenuLayer::keyBackClicked()
{
	CCLOG("MenuLayer");


}

void MenuLayer::onEnter()
{
	CCLayer::onEnter();
	PersonalAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void MenuLayer::onExit()
{
	CCLayer::onExit();
	PersonalAudioEngine::sharedEngine()->resumeBackgroundMusic();
}



CCScene* MenuLayer::scene(CCRenderTexture* sqr,int id)
{
    CCScene *scene = CCScene::create();
	MenuLayer* layer = MenuLayer::create(id);
    scene->addChild(layer,100);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite *_spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
    _spr->setPosition(ccp(size.width / 2, size.height / 2));
    _spr->setFlipY(true);
    _spr->setColor(ccGRAY);
    scene->addChild(_spr);
    return scene;
}

/*CCScene* MenuLayer::scene(int id)
{
    CCScene *scene = CCScene::create();
    MenuLayer* layer = MenuLayer::create(id);
    scene->addChild(layer,100);
    return scene;
}*/

MenuLayer* MenuLayer::create(int id)
{
    MenuLayer* layer = new MenuLayer();
    layer->autorelease();
    layer->init(id);
    return layer;
}

bool MenuLayer::init(int id)
{
    if(CCLayer::init()){
        
        this->id = id;
        this->setTouchEnabled(true);
        bg = CCScale9Sprite::create("scnl_dk1.png");
        this->addChild(bg);
        bg->setPosition(ccp(SIZE.width/2, SIZE.height/2));
        bg->setContentSize(CCSize(SIZE.width*0.9,SIZE.height*0.8));
        this->createMenu();
        return true;
    }
    return false;
}

void MenuLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-129,true);
}

bool MenuLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
 
    if(this->isVisible())
    {
        if(sound_music->boundingBox().containsPoint(pTouch->getLocation()));
        {
            return false;
        }
        return true;
    }else
    {
        return false;
    }
}
void MenuLayer::createBackground()
{
    CCLayerColor* colorBackground = CCLayerColor::create(ccc4(0, 0, 0, 128));
    this->addChild(colorBackground);
}
void MenuLayer::createMenu()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	std::string _strs = "";
	JniMethodInfo methodInfo;
	bool ishave = JniHelper::getStaticMethodInfo(methodInfo, "com/vemobi/fight/fight", "JniCall", "(IILjava/lang/String;)V");
	if (ishave)
	{
		jint TypeInt = 4;//µ¯´°-----------ÔÝÍ£
		jint proInt = 17;
		jstring priceStr = methodInfo.env->NewStringUTF(_strs.c_str());
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, TypeInt, proInt, priceStr);
	}
#endif
   

    CCSprite* pause = CCSprite::createWithSpriteFrameName("yxzt.png");
    this->addChild(pause);
    pause->setPosition(ccp(SIZE.width/2,SIZE.height*0.75));
    
	CCSprite* pause_lb = CCSprite::createWithSpriteFrameName("yxzt_lb.png");
    this->addChild(pause_lb);
    pause_lb->setPosition(ccp(SIZE.width/2,SIZE.height*0.6));
    pause_lb->setScale(1.5f);
    
	CCSprite* pause_yy = CCSprite::createWithSpriteFrameName("yxzt_yy.png");
    this->addChild(pause_yy);
    pause_yy->setPosition(ccp(SIZE.width/2,SIZE.height*0.4));
    pause_yy->setScale(1.5f);
    
    CCMenu* menu = CCMenu::create();
	duihao = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("yxzt_dh.png"), CCSprite::createWithSpriteFrameName("yxzt_dh.png"));
	cuohao = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("yxzt_xh.png"), CCSprite::createWithSpriteFrameName("yxzt_xh.png"));
    
    bool flag = KingData->getSoundVolume()>0;
    if (flag) {
         sound_music = CCMenuItemToggle::createWithTarget(this,  menu_selector(MenuLayer::sound),duihao,  cuohao,NULL);
    }else
    {
         sound_music = CCMenuItemToggle::createWithTarget(this,  menu_selector(MenuLayer::sound),cuohao,  duihao,NULL);
    }
    
    menu->addChild(sound_music);
    sound_music->setPosition(ccp( 100+SIZE.width/2,SIZE.height*0.6));
    duihao->setScale(1.5f);
    cuohao->setScale(1.5f);
    
	duihao1 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("yxzt_dh.png"), CCSprite::createWithSpriteFrameName("yxzt_dh.png"));
	cuohao1 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("yxzt_xh.png"), CCSprite::createWithSpriteFrameName("yxzt_xh.png"));
    
    bool flag2 = KingData->getMusicVolume() > 0;
    if (flag2) {
         music_sound = CCMenuItemToggle::createWithTarget(this,  menu_selector(MenuLayer::music), duihao1,cuohao1,NULL);
    }else
    {
         music_sound = CCMenuItemToggle::createWithTarget(this,  menu_selector(MenuLayer::music), cuohao1,duihao1,NULL);
    }
    
    menu->addChild(music_sound);
    music_sound->setPosition(ccp( 100+SIZE.width/2,SIZE.height*0.4));
    duihao1->setScale(1.5f);
    cuohao1->setScale(1.5f);
    
    if (id == 1) {
		jixu = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ggjm_jx.png"), CCSprite::createWithSpriteFrameName("ggjm_jxdown.png"), this, menu_selector(MenuLayer::resume));
        jixu->setPosition(ccp(SIZE.width*0.40,SIZE.height*0.2));
        menu->addChild(jixu);
		zhucaidan = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("fanhuijidi1.png"), CCSprite::createWithSpriteFrameName("fanhuijidi2.png"), this, menu_selector(MenuLayer::back));
        menu->addChild(zhucaidan);
        zhucaidan->setPosition(ccp(SIZE.width*0.60,SIZE.height*0.2));

    }else if (id == 2)
    {
		congxin = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("chongxinkaishi1.png"), CCSprite::createWithSpriteFrameName("chongxinkaishi2.png"), this, menu_selector(MenuLayer::congxinCall));
        menu->addChild(congxin);
        congxin->setPosition(ccp(SIZE.width*0.70,SIZE.height*0.2));
		fanhuijidi = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("fanhuijidi1.png"), CCSprite::createWithSpriteFrameName("fanhuijidi2.png"), this, menu_selector(MenuLayer::fanhuijidiCall));
        menu->addChild(fanhuijidi);
        fanhuijidi->setPosition(ccp(SIZE.width*0.30,SIZE.height*0.2));
		qianghuashuxing = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("qianghuashuxing1.png"), CCSprite::createWithSpriteFrameName("qianghuashuxing2.png"), this, menu_selector(MenuLayer::qianghuashuxingCall));
        menu->addChild(qianghuashuxing);
        qianghuashuxing->setPosition(ccp(SIZE.width*0.50,SIZE.height*0.2));
    }

	CCMenuItemSprite* xiaocha = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("scnl_gb.png"), CCSprite::createWithSpriteFrameName("scnl_gb_down.png"), this, menu_selector(MenuLayer::resume));
    menu->addChild(xiaocha);
    
    xiaocha->setPosition(ccp(SIZE.width*0.915,SIZE.height*0.845));
    this->addChild(menu);
    menu->setPosition(ccp(0,0));
}

void MenuLayer::back(CCObject* pSender)
{
    PersonalAudioEngine::sharedEngine()->playEffect("music/backSound.mp3"/*.wav*/);
    if (gameLayer != NULL)
    {
        gameLayer->resume();
        gameLayer->unscheduleAllSelectors();
    }
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,  MenuScene::scene()) );
}

void MenuLayer::shop()
{
    this->resume(NULL);
    if (gameLayer != NULL)
    {
       gameLayer->shop();
    }else
    {
        CCDirector::sharedDirector()->replaceScene( ShopBuy::scene() );
    }
}

void MenuLayer::resume(CCObject* pSender)
{
    CCDirector::sharedDirector()->popScene();
}
void MenuLayer::congxinCall(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(GameScene::scene(gameLayer->id,gameLayer->modeID));
}

void MenuLayer::fanhuijidiCall(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	std::string _strs = "";
	JniMethodInfo methodInfo;
	bool ishave = JniHelper::getStaticMethodInfo(methodInfo, "com/vemobi/fight/fight", "JniCall", "(IILjava/lang/String;)V");
	if (ishave)
	{
		jint TypeInt = 11;//¹Ø¿¨Ê§°Ü
		jint proInt = 0;
		jstring priceStr = methodInfo.env->NewStringUTF(_strs.c_str());
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, TypeInt, proInt, priceStr);
	}
#endif

	CCDirector::sharedDirector()->replaceScene(SelectScene::scene());
   // CCDirector::sharedDirector()->replaceScene(ShopScene::scene());
}

void MenuLayer::qianghuashuxingCall(CCObject* pSender)
{
    gameLayer->shop(100);
}

void MenuLayer::sound(CCObject* pSender)
{
    PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.mp3"/*.wav*/);
    GameScene* gameScene = (GameScene*)this->getParent();
    gameScene->sound();
}
void MenuLayer::music(CCObject* pSender)
{
    PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.mp3"/*.wav*/);
    GameScene* gameScene = (GameScene*)this->getParent();
    gameScene->music();
}

void MenuLayer::setSoundAndMusicVolume(float soundVolume, float musicVolume)
{
    bool soundFlag = soundVolume>0;
    bool musicFlag = musicVolume>0;
    _sound->setSelectedIndex(soundFlag);
    _music->setSelectedIndex(musicFlag);
}
