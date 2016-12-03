//
//  LoadingLayer.cpp
//  king04
//
//  Created by mac on 14-5-15.
//
//
#include "GameScene.h"
#include "LoadingLayer.h"
#include "Define.h"
#include "NpcMap.h"

bool LoadingLayer::init(int current_Select, int modeid)
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
		jint TypeInt = 4;//游戏界面——游戏加载界面
		jint proInt = 5;
		jstring priceStr = methodInfo.env->NewStringUTF(_strs.c_str());
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, TypeInt, proInt, priceStr);
	}
#endif

    this->current_Select = current_Select;
    this->modeid = modeid;
    char json[50] = {0};
    sprintf( json, "%s/%s.ExportJson","meinvdazhan","meinvdazhan");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(json);
    meinv = CCArmature::create("meinvdazhan");
    meinv->getAnimation()->playWithIndex(0);
    this->addChild(meinv);
    meinv->setPosition(ccp(SIZE.width/2, SIZE.height*0.53));
    meinv->setAnchorPoint(ccp(0.5, 0.5));
    label = UILabel::create();
    label->setFontName("CarterOne");
    label->setFontSize(16);
    label->setPosition(ccp(SIZE.width/2, SIZE.height*0.35));
    label->setAnchorPoint(ccp(0.5, 1));
    label->setColor(ccc3(0xee, 0xee, 0xee));
    int ran = CCRANDOM_0_1()*5;

	int a[] = {13,14,15,16,17};

    CCLog("LoadingLayer::init---%s,%d",I18N_STR(a[ran]),ran);
    label->setText(I18N_STR(a[ran]));
    this->addChild(label);
	this->scheduleOnce(schedule_selector(LoadingLayer::Loading_Res), 0.5f);
    this->scheduleOnce(schedule_selector(LoadingLayer::Loading_Over), 1.0f);
    return true;
}

CCScene* LoadingLayer::scene(int current_Select, int modeid)
{
    CCScene *scene = CCScene::create();
    LoadingLayer *layer = LoadingLayer::create(current_Select,modeid);
    scene->addChild(layer);
    return scene;
}

LoadingLayer* LoadingLayer::create(int current_Select, int modeid)
{
    LoadingLayer* LAYER = new LoadingLayer();
    LAYER->init(current_Select, modeid);
    LAYER->autorelease();
    return LAYER;
}

void LoadingLayer::loadingBack(CCObject* pSender)
{
    
}

void LoadingLayer::Loading_Over(float dt)
{
    CCDirector::sharedDirector()->replaceScene(GameScene::scene(current_Select,modeid));
}


void LoadingLayer::Loading_Res(float dt)
{
	//预加载的地方
	//在loading的地方先把要出现的怪物加载一次，防止
	int index = current_Select;
	if (index == 2)
	{
		index = 8;
	}

	int modeId = modeid;
	for (int i = 0; i<sizeof(NpcMapDate2[index]) / sizeof(int); i++)
	{
		if (NpcMapDate2[index][i] == -1)
		{
			break;
		}
		Monster* m = Monster::create(NpcMapDate2[index][i], 0);
	}

	

}


