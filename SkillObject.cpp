//
//  SkillObject.cpp
//  king04
//
//  Created by mac on 14-5-26.
//
//

#include "SkillObject.h"
#include "Hero.h"
#include "Define.h"
#include "GameScene.h"
SkillObject* SkillObject::create(int id)
{
    SkillObject* skillObject = new SkillObject();
    skillObject->init(id);
    skillObject->autorelease();
    return skillObject;
}
bool SkillObject::init(int id)
{
    this->id = id;
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("quanqiande/quanqiande.ExportJson");
    armature = CCArmature::create("quanqiande");
    armature->getAnimation()->playWithIndex(0);
	this->addChild(armature);

	std::string _picName = "";
	//根据不同类型选择不同的图片

	//0 1 2 3 四个技能
	CCPoint _pos = ccp(10,80);
	float sacle = 1.0f;
	{
		switch (id)
		{
		case 0:
			_picName = "object_0.png";
			break;
		case 1:
			_picName = "object_1.png";
			break;
		case 2:
			_picName = "object_2.png";
			break;
		case 3:
			_picName = "object_3.png";
			break;
		case 4:
			_picName = "1888jin.png";
			break;
		case 5:
			_picName = "2888jin.png";
			break;
		case 6:
			_picName = "5888jin.png";
			break;
		case 7:
			//免费的金币

		{
				  int rand_pic = rand() % 3;
				  switch (rand_pic)
				  {
				  case 0:
					  _picName = "scsc_tb1.png";
					  break;
				  case 1:
					  _picName = "scsc_tb2.png";
					  break;
				  case 2:
					  _picName = "scsc_tb3.png";
					  break;
				  default:
					  _picName = "scsc_tb4.png";
					  break;
				  }
				  sacle = 0.7f;
		}

			break;
		case 8:
			//收费的怒气
			_picName = "scnl_nqb.png";
			sacle = 0.53f;
			break;
		}
	}
	CCSprite* _node = CCSprite::createWithSpriteFrameName(_picName.c_str());
	_node->setScale(sacle);
	_node->setPosition(_pos);
	armature->addChild(_node);

	_node->runAction(CCRepeatForever::create(
		CCSequence::create(CCMoveBy::create(0.5f,ccp(0,20)),
		CCMoveBy::create(0.5f, ccp(0, -20)),NULL)
		));

    armature->setAnchorPoint(ccp(0,0));
    this->setAnchorPoint(ccp(0, 0));
    this->scheduleUpdate();
    return true;
}

void SkillObject::update(float dt)
{
    if (this->getBondingBox().intersectsRect(Role->getBondingBox()))
    {
        CCLOG("技能%d",id);
		y_pos = this->getPositionY();
		this->setPositionY(-1000);
        //this->removeFromParent();

		/*if (id > 3)
		{
			this->runAction(CCSequence::create(CCDelayTime::create(30), 
				CCCallFuncN::create(this, callfuncN_selector(SkillObject::DeleySHow)), NULL));
		}*/

        gameLayer->addCard(id);
    }
}

void SkillObject::DeleySHow(CCObject* pSender)
{

	int rans_three = -100 + (rand() % 200);
	this->setPositionX(this->getPositionX() + rans_three);
	this->setPositionY(y_pos);

}


CCRect SkillObject::getBondingBox()
{
    CCRect rect;
    rect.size = armature->getContentSize();
    rect.origin = this->getPosition();
    return rect;
}
