//
//  SelectScene.cpp
//  King
//
//  Created by mac on 14-3-26.
//
//

#include "SelectScene.h"
#include "Define.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "GameData.h"
#include "PersonalAudioEngine.h"
#include "ShopBuy.h"
#include "XMLData.h"
#include "LoadingLayer.h"
#include "BeginLayer.h"
#include "ShopScene.h"
#include "Dalibao.h"
int SelectScene::xuanguan = 1;

void SelectScene::keyBackClicked()
{

	CCLOG("SelectScene");

	if (this->getChildByTag(999) != NULL)
	{
		this->removeChildByTag(999);
	}
	else if (this->getChildByTag(10101) == NULL) 
	{
		CCDirector::sharedDirector()->replaceScene(ShopScene::scene());
	}

}


SelectScene::SelectScene()
{
    drag = false;

}
bool SelectScene::init()
{
    if ( !BaseLayer::init() )
    {
        return false;
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	std::string _strs = "";
	JniMethodInfo methodInfo;
	bool ishave = JniHelper::getStaticMethodInfo(methodInfo, "com/vemobi/fight/fight", "JniCall", "(IILjava/lang/String;)V");
	if (ishave)
	{
		jint TypeInt = 4;//游戏界面——选关界面
		jint proInt = 3;
		jstring priceStr = methodInfo.env->NewStringUTF(_strs.c_str());
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, TypeInt, proInt, priceStr);
	}
#endif

    tip1 = CCSprite::create("duihuakuang/UI80.png");
    jiaoshi = CCSprite::create("duihuakuang/jiaoshi.png");
    this->addChild(jiaoshi,9999999);
    this->addChild(tip1,999999);
    jiaoshi->setPosition(ccp(-0.15*SIZE.width,10));
    jiaoshi->setAnchorPoint(ccp(0.5, 0));
    tip1->setPosition(ccp( -150, -120));
    label = UILabel::create();
    tip1->addChild(label);
    label->setFontName("CarterOne");
    label->setFontSize(20);
    label->setPosition(ccp(120, tip1->getContentSize().height));
    label->setAnchorPoint(ccp(0, 1));
    label->setColor(ccc3(241, 191, 194));
    label->setTextAreaSize(CCSize(200,150));
    tip1->setVisible(false);
    jiaoshi->setVisible(false);
    label->setTextVerticalAlignment(kCCVerticalTextAlignmentCenter);
    
    //将地图从大图中分离
    ul = UILayer::create();
    this->addChild(ul);
	Widget* Panel_bg = GUIReader::shareReader()->widgetFromJsonFile("NewProject_1/NewProject_1.ExportJson");
	Layout* Panel_20 = dynamic_cast<Layout*>(Panel_bg);
	//Panel_20->setBackGroundImage("NewProject_1/ditubg.png");

	CCSprite* ditubg_left = CCSprite::create("ditubg_left.jpg");
	ditubg_left->setPosition(ccp(1024*0.5,240));
	CCSprite* ditubg_right = CCSprite::create("ditubg_right.jpg");
	ditubg_right->setPosition(ccp(1024*1.5, 240));
	Panel_20->addNode(ditubg_left);
	Panel_20->addNode(ditubg_right);
	ditubg_left->setZOrder(-10);
	ditubg_right->setZOrder(-10);

	ul->addWidget(Panel_20);
    this->setTouchEnabled(true);
    
    menu = CCMenu::create();
    this->addChild(menu);
    menu->setPosition(0, 0);
	back = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("huiqu1.png"), CCSprite::createWithSpriteFrameName("huiqu2.png"), this, menu_selector(SelectScene::backScene));
    back->setPosition(ccp(SIZE.width*0.05, SIZE.height*0.05 ) );
    menu->addChild(back);
    
	jiantou1 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("jiantou.png"), CCSprite::createWithSpriteFrameName("jiantou.png"), this, menu_selector(SelectScene::fudong));
 
    menu->addChild(jiantou1);
    jiantou1->setPosition(ccp(SIZE.width*0.97, SIZE.height*0.5 ) );
    jiantou1->setVisible(false);
    
	jiantou2 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("jiantou.png"), CCSprite::createWithSpriteFrameName("jiantou.png"), this, menu_selector(SelectScene::fudong1));
    menu->addChild(jiantou2);
    jiantou2->setScaleX(-1);
    jiantou2->setPosition(ccp(SIZE.width*0.03, SIZE.height*0.5 ) );
    jiantou2->setVisible(false);

    xuanguan = KingData->getMapIndex();
     char uiChar[5] = {0};
     if(xuanguan>20)
     {
         xuanguan = 20;
     }
    
     for (int i = 1; i<=xuanguan; i++)
     {
        sprintf(uiChar, "%d",i);
        UIButton* button  = dynamic_cast<UIButton*>(ul->getWidgetByName(uiChar));
        button->setUserObject(CCInteger::create(i));
        button->setTouchEnabled(true);
        button->setOpacity(0);
        button->setScale(2);
        button->addTouchEventListener(this, toucheventselector(SelectScene::clickButtonCallback) );
     }

     current_Select = xuanguan;
     sprintf(uiChar, "%d",current_Select);
     curr_button  = dynamic_cast<UIButton*>(ul->getWidgetByName(uiChar));
     curr_button->setScale(1.1f);
     curr_button->setBright(true);
     curr_button->setOpacity(200);
     curr_button->runAction(CCRepeatForever::create(CCSequence::create(CCBlink::create(1.5, 2) , NULL))  );
     curr_button->setColor(ccc3(255, 0, 0));
    
     if(current_Select <= 10)
     {
         ul->setPositionX(0);
         jiantou1->setVisible(true);
         jiantou1->runAction(CCRepeatForever::create(CCBlink::create(0.5, 1)));
     }else if (current_Select>10 && current_Select <= 16)
     {
         ul->setPositionX(-SIZE.width + 20);
         jiantou1->setVisible(true);
         jiantou2->setVisible(true);
         jiantou1->runAction(CCRepeatForever::create(CCBlink::create(0.5, 1)));
         jiantou2->runAction(CCRepeatForever::create(CCBlink::create(0.5, 1)));
     }else
     {
         ul->setPositionX(-2048 + SIZE.width  );
         jiantou2->setVisible(true);
         jiantou2->runAction(CCRepeatForever::create(CCBlink::create(0.5, 1)));
     }
    
	 new2 = CCSprite::createWithSpriteFrameName("60.png");
    ul->addChild(new2);
    new2->setPosition(curr_button->getPosition());

	CCMenuItemSprite* shopbutton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("shangcheng1.png"), CCSprite::createWithSpriteFrameName("shangcheng2.png"), this, menu_selector(SelectScene::shopButtonCallback));

    menu->addChild(shopbutton);
    shopbutton->setPosition(ccp(SIZE.width*0.94, SIZE.height*0.07 ));
    
    
    CCMenuItemSprite* onlineLibao = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("zaixianlibao.png"), CCSprite::createWithSpriteFrameName("zaixianlibao.png"),this,menu_selector(SelectScene::onlineLibaoMenu));
    
    onlineLibao->runAction(CCRepeatForever::create( CCSequence::create(CCScaleTo::create(0.3, 1.2),CCScaleTo::create(0.3, 0.9),NULL )) );
  
    menu->addChild(onlineLibao);
    onlineLibao->setPosition(ccp(SIZE.width*0.82, SIZE.height*0.07 ));
    
	if (!KingData->getFirstTishiShuxing())
    {
        KingData->setFirstTishiShuxing(true);
        CCUserDefault::sharedUserDefault()->setBoolForKey("firstTishiShuxing", KingData->getFirstTishiShuxing());
        CCUserDefault::sharedUserDefault()->flush();

		//取消掉提示升级的地方

        //this->addTips();
        //canClick = false;

		canClick = true;
		CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(SelectScene::showLvup));
		this->runAction(call);
    }else
	{
		//在未执行引导的情况下弹窗
		canClick = true;

		int randsf = rand()%7;
		int level_total = KingData->getShengmingLevel() + KingData->getGongjiLevel() + KingData->getFangyuLevel() + KingData->getNuqiLevel();
		 if (level_total >= 40)
		 {
			 randsf = 0;
		 }

		if (randsf < 5)
		{
			ShowGift();
		}
		else
		{
			CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(SelectScene::showLvup));
			this->runAction(call);
		}
    }

    return true;
}

void SelectScene::showLvup()
{
	CCRenderTexture* renderTexture = CCRenderTexture::create(SIZE.width, SIZE.height);
	renderTexture->begin();
	this->visit();
	renderTexture->end();
	CCDirector::sharedDirector()->pushScene(ShopBuy::scene(renderTexture, true));
}

void SelectScene::ShowGift()
{
	int id = rand() % 4;
	if (id < 3 && this->getChildByTag(dalibaotag) == NULL)
	{
		//大礼包 技能 金币 随机
		int big_int = rand() % 3;// 0礼包 1金币 2技能
		if (big_int >= 3)
		{
			big_int = 2;
		}
		//如果随机到了技能 礼包 两个技能都拥有的时候 换成其他两个中的一个
		if (big_int == 2 && KingData->getJinjiDuobi() && KingData->getShoushen())
		{
			int big_or_gold = rand() % 2;
			if (big_or_gold >= 2)
			{
				big_or_gold = 1;
			}
			big_int = big_or_gold;
		}
		Dalibao* dalibao = Dalibao::create(big_int);// 0 1 2
		dalibao->setPosition(ccp(0, SIZE.height * 1));
		dalibao->runAction(CCEaseIn::create(CCMoveTo::create(0.5f, ccp(0, 0)), 2));
		this->addChild(dalibao, dalibaozorder, dalibaotag);
	}
	else
	{
		//在线大礼包
		if (this->getChildByTag(10101) == NULL) {
			Jihuo* jihuo = Jihuo::create();
			this->addChild(jihuo, 1010);
			jihuo->setTag(10101);
		}
	}
}

void SelectScene::onlineLibaoMenu(CCObject* pSender)
{
 
	onlineLibaoMenu();
}

void SelectScene::onlineLibaoMenu()
{

	if (this->getChildByTag(10101) == NULL) {
		Jihuo* jihuo = Jihuo::create();
		this->addChild(jihuo, 1010);
		jihuo->setTag(10101);
	}
}

void SelectScene::fudong(CCObject* pSender)
{
    
    jiantou1->stopAllActions();
    jiantou2->stopAllActions();
    ul->stopAllActions();
    CCPoint pp = CCPoint( MAX(- (2048 - ul->getContentSize().width) , MIN(0,  ul->getPositionX() + -SIZE.width) ) , ul->getPositionY());
    float x = ul->getPositionX() - pp.x;
    
    ul->runAction(CCMoveTo::create(x/SIZE.width, pp ));
    
    if (pp.x > -0.2f) {
        jiantou1->setVisible(true);
        jiantou2->setVisible(false);
        jiantou1->runAction(CCRepeatForever::create(CCBlink::create(0.5, 1)));
        
    }else  if (pp.x < -0.2f && pp.x > -SIZE.width - 0.2f) {
        jiantou1->setVisible(true);
        jiantou2->setVisible(true);
        jiantou1->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.25),CCFadeOut::create(0.25),NULL)  ));
        jiantou2->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.25),CCFadeOut::create(0.25),NULL)  ));
    }else{
        jiantou1->setVisible(false);
        jiantou2->setVisible(true);
        jiantou2->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.25),CCFadeOut::create(0.25),NULL)   ));
    }
    
    drag = true;
}

void SelectScene::fudong1(CCObject* pSender)
{
    jiantou1->stopAllActions();
    jiantou2->stopAllActions();
    ul->stopAllActions();
    CCPoint pp = CCPoint( MAX(- (2048 - ul->getContentSize().width) , MIN(0,  ul->getPositionX() + SIZE.width) ) , ul->getPositionY());
    float x = pp.x - ul->getPositionX();
    ul->runAction(CCMoveTo::create(x/SIZE.width, pp ));
    if (pp.x > -0.2f) {
        jiantou1->setVisible(true);
        jiantou2->setVisible(false);
        jiantou1->runAction(CCRepeatForever::create(CCBlink::create(0.5, 1)));
    }else  if (pp.x < -0.2f && pp.x > -SIZE.width - 0.2f) {
        jiantou1->setVisible(true);
        jiantou2->setVisible(true);
        jiantou1->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.25),CCFadeOut::create(0.25),NULL)  ));
        jiantou2->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.25),CCFadeOut::create(0.25),NULL) ));
    }else{
        jiantou1->setVisible(false);
        jiantou2->setVisible(true);
        jiantou2->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.25),CCFadeOut::create(0.25),NULL)  ));
    }

    drag = true;
}

void SelectScene::backScene(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene( ShopScene::scene() );
}

void SelectScene::addTips()
{
    //addTip("敌人太多强化一下属性");
	addTip(I18N_STR(150));
    sprite = CCSprite::createWithSpriteFrameName("help11.png");
    sprite->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.3f, ccp(0, 30)),CCMoveBy::create(0.3f, ccp(0, -30)),NULL)));
    this->addChild(sprite,1,9898);
    sprite->setScale(0.6f);
    sprite->setPosition(ccp(SIZE.width*0.93, SIZE.height*0.12));

	tishi_sprite = CCSprite::create("tishi.png");
	this->addChild(tishi_sprite, 1, 9899);
	tishi_sprite->setScale(8.0f);
	tishi_sprite->setPosition(ccp(SIZE.width*0.94, SIZE.height*0.075));
	tishi_sprite->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(1.0f, 0.0f), CCScaleTo::create(0.0f, 8.0f), NULL)));

}

void SelectScene::shopButtonCallback()
{
	if (biaozhi == 10)
	{
		return;
	}
	if (canClick == false)
	{
		resetTip();
		sprite->setVisible(false);
		tishi_sprite->setVisible(false);
		biaozhi = 10;
		canClick = true;
		this->removeChildByTag(9900);
		sprite->setScale(0.5f);
		sprite->setPosition(ccp(SIZE.width*0.80, SIZE.height*0.25));
		PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.mp3"/*.wav*/);
		CCRenderTexture* renderTexture = CCRenderTexture::create(SIZE.width, SIZE.height);
		renderTexture->begin();
		this->visit();
		renderTexture->end();
		CCDirector::sharedDirector()->pushScene(ShopBuy::scene(renderTexture, false, 20));
	}
	else
	{
		PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.mp3"/*.wav*/);
		CCRenderTexture* renderTexture = CCRenderTexture::create(SIZE.width, SIZE.height);
		renderTexture->begin();
		this->visit();
		renderTexture->end();
		CCDirector::sharedDirector()->pushScene(ShopBuy::scene(renderTexture, false));
	}
}


void SelectScene::shopButtonCallback(CCObject* pSender)
{
	shopButtonCallback();
}

void SelectScene::shopButtonCallbackAuto()
{
	shopButtonCallback();
	//PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.mp3"/*.wav*/);
	/*CCRenderTexture* renderTexture = CCRenderTexture::create(SIZE.width, SIZE.height);
	renderTexture->begin();
	this->visit();
	renderTexture->end();
	CCDirector::sharedDirector()->pushScene(ShopBuy::scene(renderTexture, false, 666));*/
}


void SelectScene::shopButtonCallback(CCObject* pSender,TouchEventType type)
{
  
    if ( biaozhi == 10)
    {
        return;
    }
    switch (type) {
        case  cocos2d::gui::TOUCH_EVENT_BEGAN:
        {
            if (canClick == false)
            {
                biaozhi = 10;
                
                canClick = true;
                this->removeChildByTag(9900);
                sprite->setScale(0.5f);
                sprite->setPosition(ccp(SIZE.width*0.80, SIZE.height*0.3));
                PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.mp3"/*.wav*/);
                CCRenderTexture* renderTexture = CCRenderTexture::create(SIZE.width, SIZE.height);
                renderTexture->begin();
                this->visit();
                renderTexture->end();
                CCDirector::sharedDirector()->pushScene( ShopBuy::scene(renderTexture,false,20));
            }else
            {
                PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.mp3"/*.wav*/);
                CCRenderTexture* renderTexture = CCRenderTexture::create(SIZE.width, SIZE.height);
                renderTexture->begin();
                this->visit();
                renderTexture->end();
                CCDirector::sharedDirector()->pushScene( ShopBuy::scene(renderTexture,false));
            }
 
            break;
        }
        case cocos2d::gui::TOUCH_EVENT_ENDED:
        {
        }
        default:
            break;
    }
}

void SelectScene::onEnter()
{
	biaozhi = 0;
    CCLayer::onEnter();
    PersonalAudioEngine::sharedEngine()->playBackgroundMusic("music/jiemianbgmusic.mp3",true);
}

void SelectScene::clickButtonCallback(CCObject* pSender, TouchEventType type)
{
    if (canClick == false) {
        return;
    }
    
    if (drag == true)
    {
        return;
    }
    
    if (this->getChildByTag(999)) {
        return;
    }
    
    for (int i = 1; i<=xuanguan; i++)
    {
        char uiChar[5] = {0};
        sprintf(uiChar, "%d",i);
        UIButton* button  = dynamic_cast<UIButton*>(ul->getWidgetByName(uiChar));
        button->setVisible(true);
        button->setBright(true);
        button->setOpacity(0);
        button->stopAllActions();
    }
      UIButton* button  = dynamic_cast<UIButton*>(pSender);
      CCInteger* integer = dynamic_cast<CCInteger*>(button->getUserObject());
      current_Select = integer->getValue();
      button->setScale(1.1f);
      button->setBright(true);
      button->setOpacity(200);
      button->runAction(CCRepeatForever::create(CCSequence::create(CCBlink::create(1.5, 2) , NULL))  );
      button->setColor(ccc3(255, 0, 0));
 
    switch (type) {
        case  cocos2d::gui::TOUCH_EVENT_BEGAN:
        {
            break;
        }
        case cocos2d::gui::TOUCH_EVENT_ENDED:
        {
            BeginLayer* layer = BeginLayer::create(current_Select);
            this->addChild(layer,999,999);
            layer->setPosition(ccp(0, 0));
            layer->setVisible(true);
            break;
        }
        default:
           break;
    }
}

void SelectScene::start_game(CCObject* pSender, TouchEventType type)
{
    if (!canClick)
    {
        return;
    }
    switch (type)
    {
        case  cocos2d::gui::TOUCH_EVENT_BEGAN:
        {
            PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.mp3"/*.wav*/);
            CCDirector::sharedDirector()->replaceScene(LoadingLayer::scene(current_Select, moshiID[current_Select]));
            break;
        }
        case cocos2d::gui::TOUCH_EVENT_ENDED:
        {
            
        }
        default:
            break;
    }
}

void SelectScene::Back(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(MenuScene::scene());
}

cocos2d::CCScene* SelectScene::scene()
{
    CCScene *scene = CCScene::create();
    SelectScene *layer = SelectScene::create();
    scene->addChild(layer);
    return scene;
}

void SelectScene::onExit()
{
    PersonalAudioEngine::sharedEngine()->stopAllEffects();
    PersonalAudioEngine::sharedEngine()->stopBackgroundMusic(true);
    CCLayer::onExit();
}

bool SelectScene::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    if (canClick == false) {
        return false;
    }
    beginP = touch->getLocation();
    return true;
}
void SelectScene::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{

}
void SelectScene::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    endP = touch->getLocation();
   
    if ( endP.x - beginP.x > 100)
    {
        jiantou1->stopAllActions();
        jiantou2->stopAllActions();
        ul->stopAllActions();
        CCPoint pp = CCPoint( MAX(- (2048 - ul->getContentSize().width) , MIN(0,  ul->getPositionX() + SIZE.width) ) , ul->getPositionY());
        float x = pp.x - ul->getPositionX();
        
        ul->runAction(CCMoveTo::create(x/SIZE.width, pp ));
  
        if (pp.x > -0.2f) {
            jiantou1->setVisible(true);
            jiantou2->setVisible(false);
            jiantou1->runAction(CCRepeatForever::create(CCBlink::create(0.5, 1)));
         
        }else  if (pp.x < -0.2f && pp.x > -SIZE.width - 0.2f) {
            jiantou1->setVisible(true);
            jiantou2->setVisible(true);
            jiantou1->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.25),CCFadeOut::create(0.25),NULL)  ));
            jiantou2->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.25),CCFadeOut::create(0.25),NULL)  ));
        }else{
            jiantou1->setVisible(false);
            jiantou2->setVisible(true);
            jiantou2->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.25),CCFadeOut::create(0.25),NULL)  ));
        }
        
        drag = true;
    }else if (endP.x - beginP.x < -100)
    {
        jiantou1->stopAllActions();
        jiantou2->stopAllActions();
        ul->stopAllActions();
        CCPoint pp = CCPoint( MAX(- (2048 - ul->getContentSize().width) , MIN(0,  ul->getPositionX() + -SIZE.width) ) , ul->getPositionY());
        float x = ul->getPositionX() - pp.x;
        
        ul->runAction(CCMoveTo::create(x/SIZE.width, pp ));
       
        if (pp.x > -0.2f) {
            jiantou1->setVisible(true);
            jiantou2->setVisible(false);
            jiantou1->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.25),CCFadeOut::create(0.25),NULL)  ));
            
        }else  if (pp.x < -0.2f && pp.x > -SIZE.width - 0.2f) {
            jiantou1->setVisible(true);
            jiantou2->setVisible(true);
            jiantou1->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.25),CCFadeOut::create(0.25),NULL)  ));
            jiantou2->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.25),CCFadeOut::create(0.25),NULL)  ));
        }else{
            jiantou1->setVisible(false);
            jiantou2->setVisible(true);
            jiantou2->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.25),CCFadeOut::create(0.25),NULL)  ));
        }
        
        drag = true;
    }else
    {
        drag = false;
    }
   
  }


void SelectScene::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-126,false);
}

void SelectScene::addTip(std::string text)
{
    jiaoshi->setFlipX(false);
    tip1->runAction(CCMoveTo::create(0.2f, ccp(210,70)));
    jiaoshi->runAction(CCSequence::create(CCDelayTime::create(0.2f),CCMoveTo::create(0.2f, ccp(SIZE.width*0.085, 2))
                                          ,NULL ));
    
    label->setPosition(ccp(220, tip1->getContentSize().height));
    tip1->setVisible(true);
    jiaoshi->setVisible(true);
    label->setText(text);

	//文字换行
	label->ignoreContentAdaptWithSize(false);
	label->setSize(CCSizeMake(250, 100));
}

void SelectScene::addTip2(std::string text)
{
    jiaoshi->setVisible(false);
    tip1->setVisible(false);
    jiaoshi->setPosition(ccp(1.15*SIZE.width,10));
    tip1->setPosition(ccp( SIZE.width+150, -120));
    tip1->setVisible(true);
    jiaoshi->setVisible(true);
    jiaoshi->setFlipX(true);
    label->setPosition(ccp(100, tip1->getContentSize().height));
    tip1->runAction(CCMoveTo::create(0.2f, ccp(SIZE.width-210,70)));
    jiaoshi->runAction(CCSequence::create(CCDelayTime::create(0.2f),CCMoveTo::create(0.2f, ccp(SIZE.width-SIZE.width*0.085, 2))
                                          ,NULL ));
    
    label->setText(text);
	//文字换行
	label->ignoreContentAdaptWithSize(false);
	label->setSize(CCSizeMake(250, 100));
}


void SelectScene::resetTip()
{
    tip1->setVisible(false);
    jiaoshi->setVisible(false);
    label->setText("");
    jiaoshi->setPosition(ccp(-0.15*SIZE.width,10));
    tip1->setPosition(ccp( -150, -120));
	//文字换行
	label->ignoreContentAdaptWithSize(false);
	label->setSize(CCSizeMake(250, 100));
}