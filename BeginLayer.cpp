//
//  BeginLayer.cpp
//  king04
//
//  Created by mac on 14-5-21.
//
//


#include "BeginLayer.h"
#include "Define.h"
#include "SelectScene.h"
#include "XMLData.h"
#include "PersonalAudioEngine.h"
#include "LoadingLayer.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif
BeginLayer* BeginLayer::create(int id)
{
    BeginLayer* layer = new BeginLayer();
    layer->init(id);
    layer->autorelease();
    return layer;
}
bool BeginLayer::init(int id)
{
	CCLog("BeginLayer::init-id=%d",id);
	
    if (!CCLayer::init())
    {
        return false;
    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	std::string _strs = "";
	JniMethodInfo methodInfo;
	bool ishave = JniHelper::getStaticMethodInfo(methodInfo, "com/vemobi/fight/fight", "JniCall", "(IILjava/lang/String;)V");
	if (ishave)
	{
		jint TypeInt = 4;
		jint proInt = 4;
		jstring priceStr = methodInfo.env->NewStringUTF(_strs.c_str());
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, TypeInt, proInt, priceStr);
	}
#endif

    this->id = id;
    bg = CCSprite::create("guanka1.png");
    this->addChild(bg);
    bg->setPosition(ccp(SIZE.width/2,SIZE.height/2));

	CCLog("BeginLayer::init-1");
    CCMenu* menu = CCMenu::create();
    this->addChild(menu);
    menu->setPosition(ccp(0, 0));
    
    xiaocha = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("scnl_gb.png"), CCSprite::createWithSpriteFrameName("scnl_gb_down.png"), this,menu_selector(BeginLayer::resume));
    menu->addChild(xiaocha);
    xiaocha->setPosition(SIZE.width*0.84, SIZE.height*0.80);
    
	guankajishao = CCSprite::createWithSpriteFrameName("guankakjieshao.png");
    bg->addChild(guankajishao);
    guankajishao->setPosition(ccp(165,240));

    CCLog("BeginLayer::init-2");
    label1 = UILabel::create();
    //label1->setText(title[id]);
    label1->setText(I18N_STR(id+19));
	
    bg->addChild(label1);
    label1->setFontSize(22);
    label1->setFontName("CarterOne");
    label1->setColor(ccc3(0xe3, 0x9e, 0x78));
    label1->setPosition(ccp(SIZE.width*0.4,SIZE.height*0.63));
    label1->setAnchorPoint(ccp(0.5, 0.5));

	CCLog("BeginLayer::init-3");
    font1 = UILabel::create();
	font1->ignoreContentAdaptWithSize(false);
	font1->setSize(CCSizeMake(400, 100));
    //font1->setText(descr[id]);
    font1->setText(I18N_STR(id+40));
    bg->addChild(font1);
    font1->setFontSize(18);
    font1->setFontName("CarterOne");
    font1->setTextAreaSize(CCSize(350,80));
    font1->setTextHorizontalAlignment(kCCTextAlignmentLeft);
    font1->setTextVerticalAlignment(kCCVerticalTextAlignmentTop);
    font1->setColor(ccc3(251, 234, 59));
    font1->setPosition(ccp(220,255));
    font1->setAnchorPoint(ccp(0, 1));
   
	moshiSprite = CCSprite::createWithSpriteFrameName("renwumubiaozi.png");

    
    bg->addChild(moshiSprite);
    moshiSprite->setPosition(ccp(165,155));
    CCLog("BeginLayer::init-4");
    font2 = UILabel::create();
    //font2->setText(moshiStr[id]);
	font2->setText(I18N_STR(id+61));
    bg->addChild(font2);
    font2->setFontSize(18);
    font2->setFontName("CarterOne");
    font2->setTextAreaSize(CCSize(350,80));
    font2->setTextHorizontalAlignment(kCCTextAlignmentLeft);
    font2->setTextVerticalAlignment(kCCVerticalTextAlignmentTop);
    font2->setColor(ccc3(251, 234, 59));
    font2->setPosition(ccp(220,165));
    font2->setAnchorPoint(ccp(0, 1));
    
    benguandefen = CCSprite::createWithSpriteFrameName("benguandefen.png");
    bg->addChild(benguandefen);
    benguandefen->setPosition(ccp(165,77));
	
	CCLog("BeginLayer::init-5");
    font3 = UILabel::create();
    bg->addChild(font3);
    font3->setFontSize(18);
    font3->setFontName("CarterOne");
    font3->setTextAreaSize(CCSize(350,80));
    font3->setTextHorizontalAlignment(kCCTextAlignmentLeft);
    font3->setTextVerticalAlignment(kCCVerticalTextAlignmentTop);
    font3->setColor(ccc3(251, 234, 59));
    font3->setPosition(ccp(220,90));
    font3->setAnchorPoint(ccp(0, 1));

	CCLog("BeginLayer::init-6");
    XMLData* data =   XMLData::sharedXMLData();
	CCLog("BeginLayer::init-7");
    const char* dataScore =  data->read(id);
	CCLog("BeginLayer::init-8 =%d",dataScore);
    char desc[120] = {0};
	if(dataScore!=NULL) 
	{
		sprintf(desc, "%s",dataScore);
	}
	CCLog("BeginLayer::init-9");
    font3->setText(desc);
	CCLog("BeginLayer::init-10");

	
	startGame = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("biao1.png"), CCSprite::createWithSpriteFrameName("biao2.png"), this, menu_selector(BeginLayer::start_game));
    menu->addChild(startGame);
    startGame->setPosition(SIZE.width*0.5, SIZE.height*0.2);
	CCLog("BeginLayer::init-end");
    return true;
}

void BeginLayer::start_game(CCObject* pSender)
{
     PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.mp3"/*.wav*/);
     CCDirector::sharedDirector()->replaceScene(LoadingLayer::scene(id, moshiID[id]));
}

void BeginLayer::resume(CCObject* pSender)
{
    PersonalAudioEngine::sharedEngine()->playEffect("music/backSound.mp3"/*.wav*/);
    this->removeFromParent();
}

void BeginLayer::resumeCall(CCObject* pSender)
{
     this->removeFromParent();
}
