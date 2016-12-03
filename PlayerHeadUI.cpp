//
//  PlayerHeadUI.cpp
//  King
//
//  Created by mac on 14-4-1.
//
//

#include "PlayerHeadUI.h"
#include "Hero.h"
#include "GameData.h"
#include "Define.h"
using namespace cocos2d;
using namespace cocos2d::extension;

PlayerHeadUI::PlayerHeadUI(void)
:uiLayer(NULL),player(NULL)
{
    uiLayer = UILayer::create();
    initWidget();
    this->addChild(uiLayer);
    schedule(schedule_selector(PlayerHeadUI::update2), 0.1);
}

PlayerHeadUI::~PlayerHeadUI(void)
{
    
}

void PlayerHeadUI::initWidget()
{
    UIWidget* widget =  dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("touxiang1/touxiang1.ExportJson"));
    uiLayer->addWidget(widget);
    nuqi = dynamic_cast<UILoadingBar*>
    (uiLayer->getWidgetByName("nuqi"));
    life = dynamic_cast<UILoadingBar*>
    (uiLayer->getWidgetByName("xuetiao1"));
    shuzi = dynamic_cast<ImageView*>(uiLayer->getWidgetByName("shuzi"));
    shuzi->setScale(1.4);
    life->setPercent(100);
    nuqi->setPercent(0);
    
    moneyHead = UILabel::create();
    uiLayer->addChild(moneyHead,10000);
    moneyHead->setFontSize(18);
    moneyHead->setFontName("CarterOne");
    moneyHead->setTextHorizontalAlignment(kCCTextAlignmentCenter);
    moneyHead->setTextVerticalAlignment(kCCVerticalTextAlignmentCenter);
    moneyHead->setColor(ccc3(255, 255, 0));
    uiLayer->setAnchorPoint(ccp(0,1));
    moneyHead->setPosition(ccp(250,205));
    char money[25] = {0};
    //sprintf(money,"½ð±Ò : %d",KingData->getMoney());
    sprintf(money,"%s : %d",I18N_STR(10),KingData->getMoney());
    moneyHead->setText(money);
	moneyHead->setPositionX(moneyHead->getPositionX()-25);

}

void PlayerHeadUI::changeMoney()
{
    char money[25] = {0};
    //sprintf(money,"½ð±Ò : %d",KingData->getMoney());
	sprintf(money,"%s : %d",I18N_STR(10),KingData->getMoney());
    moneyHead->setText(money);
    
}

void PlayerHeadUI::processPlayerLife()
{
    
}
void PlayerHeadUI::processPlayerHP()
{
    setHPBarPercent((int)(100*Role->getHP()/Role->getMaxHp()) );
    setMPBarPercent((int)player->getNuqiPercent());
}

void PlayerHeadUI::setHPBarPercent(int percent)
{
    life->setPercent(percent);
    if (Role!=NULL && Role->isDie)
    {
        life->setPercent(0);
    }
}

void PlayerHeadUI::setMPBarPercent(int percent)
{
	int aag = player->nuqi;
    if (player->nuqi  > (player->maxNengliangdou )*100 + 99)
    {
        player->nuqi = (player->maxNengliangdou )*100 + 99;
    }
    if(Role->nuqi + KingData->getExtraNuqi() >(Role->maxNengliangdou+1)*100 + 99)
    {
        player->nuqi = (player->nuqi/100)*100 + 99;
    }
    nuqi->setPercent((player->nuqi + KingData->getExtraNuqi()) %100);
    if ((player->nuqi + KingData->getExtraNuqi()) %100 == 99) {
        nuqi->setPercent(100);
    }
    char shuziChar[20] = {0};
    if ((player->nuqi + KingData->getExtraNuqi())/100 >9)
    {
        shuzi->removeAllChildren();
        int value = (player->nuqi + KingData->getExtraNuqi())/100;
        char valueChar[20] = {0};
        sprintf(valueChar, "%d",value);
        int weishu = strlen(valueChar);
        for (int i = 0; i<weishu; i++)
        {
            int value1 = (value/(int)pow(10.0, weishu-i-1))%10  ;
            ImageView* view1 = ImageView::create();
            char shuziChar1[20] = {0};
            sprintf(shuziChar1,"num/suzi-%d.png",value1);
            if(i==0)
            {
				shuzi->loadTexture(shuziChar1);
            }else
            {
                view1->loadTexture(shuziChar1);
                shuzi->addChild(view1,1,100);
                view1->setPosition(ccp(view1->getContentSize().width*i , 0));
            }
        }
    }else
    {
        shuzi->removeAllChildren();
        sprintf(shuziChar, "num/suzi-%d.png",(player->nuqi + KingData->getExtraNuqi())/100);
        shuzi->loadTexture(shuziChar);
    }
}

void PlayerHeadUI::update2(float dt)
{
	if (player == NULL)
	{
		
	}
	else
	{
		processPlayerLife();
		processPlayerHP();
		changeMoney();
	}
}

void PlayerHeadUI::openNuqiUp()
{
	schedule(schedule_selector(PlayerHeadUI::updateNuqi), 0.02f);
}

void PlayerHeadUI::updateNuqi(float dt)
{
	nuqi->setPercent(100);

	int aag = player->nuqi;
	if (player->nuqi  > (player->maxNengliangdou) * 100 + 99)
	{
		player->nuqi = (player->maxNengliangdou) * 100 + 99;
	}
	if (ShopRole->nuqi + KingData->getExtraNuqi() >(ShopRole->maxNengliangdou + 1) * 100 + 99)
	{
		player->nuqi = (player->nuqi / 100) * 100 + 99;
	}
	nuqi->setPercent((player->nuqi + KingData->getExtraNuqi()) % 100);
	if ((player->nuqi + KingData->getExtraNuqi()) % 100 == 99) {
		nuqi->setPercent(100);
	}
	char shuziChar[20] = { 0 };
	if ((player->nuqi + KingData->getExtraNuqi()) / 100 >9)
	{
		shuzi->removeAllChildren();
		int value = (player->nuqi + KingData->getExtraNuqi()) / 100;
		char valueChar[20] = { 0 };
		sprintf(valueChar, "%d", value);
		int weishu = strlen(valueChar);
		for (int i = 0; i<weishu; i++)
		{
			int value1 = (value / (int)pow(10.0, weishu - i - 1)) % 10;
			ImageView* view1 = ImageView::create();
			char shuziChar1[20] = { 0 };
			sprintf(shuziChar1, "num/suzi-%d.png", value1);
			if (i == 0)
			{
				shuzi->loadTexture(shuziChar1);
			}
			else
			{
				view1->loadTexture(shuziChar1);
				shuzi->addChild(view1, 1, 100);
				view1->setPosition(ccp(view1->getContentSize().width*i, 0));
			}
		}
	}
	else
	{
		shuzi->removeAllChildren();
		sprintf(shuziChar, "num/suzi-%d.png", (player->nuqi + KingData->getExtraNuqi()) / 100);
		shuzi->loadTexture(shuziChar);
	}

}