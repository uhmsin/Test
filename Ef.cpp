//
//  Ef.cpp
//  King
//
//  Created by mac on 14-4-13.
//
//

#include "Ef.h"
Ef::Ef()
{
    armature = NULL;
    isRemove = true;
}

Ef* Ef::create(const char* name)
{
    Ef* ef = new Ef();
    ef->init(name);
    ef->autorelease();
    return ef;
}

Ef* Ef::create(const char* name,int index)
{
    Ef* ef = new Ef();
    ef->init(name,index);
    ef->autorelease();
    return ef;
}

Ef* Ef::create(const char* name,int index,int loopTimes)
{
    Ef* ef = new Ef();
    ef->init(name,index,loopTimes);
    ef->autorelease();
    return ef;
}
bool Ef::init(const char* name,int index,int loopTimes)
{
    char png[50] = {0};
    sprintf( png, "%s/%s/%s0.png","effect",name,name);
    char plist[50] = {0};
    sprintf( plist, "%s/%s/%s0.plist","effect",name,name);
    char json[50] = {0};
    sprintf( json, "%s/%s/%s.ExportJson","effect",name,name);
    CCArmatureDataManager::sharedArmatureDataManager()->purge();
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(json);
    armature = CCArmature::create(name);
    armature->getAnimation()->playWithIndex(index, -1, -1,  loopTimes, -1);
    armature->getAnimation()->setMovementEventCallFunc(this, SEL_MovementEventCallFunc(&Ef::actionCallback));
    this->addChild(armature);
    return true;
}

bool Ef::init(const char* name,int index)
{
    char png[50] = {0};
    sprintf( png, "%s/%s/%s0.png","effect",name,name);
    char plist[50] = {0};
    sprintf( plist, "%s/%s/%s0.plist","effect",name,name);
    char json[50] = {0};
    sprintf( json, "%s/%s/%s.ExportJson","effect",name,name);
    CCArmatureDataManager::sharedArmatureDataManager()->purge();
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(json);
    armature = CCArmature::create(name);
    armature->getAnimation()->playWithIndex(index);
    armature->getAnimation()->setMovementEventCallFunc(this, SEL_MovementEventCallFunc(&Ef::actionCallback));
    this->addChild(armature);
    return true;
}

void Ef::setSpeed(float rate)
{
    armature->getAnimation()->setSpeedScale(rate);
}

bool Ef::init(const char* name)
{
    char png[50] = {0};
    sprintf( png, "%s/%s/%s0.png","effect",name,name);
    char plist[50] = {0};
    sprintf( plist, "%s/%s/%s0.plist","effect",name,name);
    char json[50] = {0};
    sprintf( json, "%s/%s/%s.ExportJson","effect",name,name);
    CCArmatureDataManager::sharedArmatureDataManager()->purge();
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(json);
    armature = CCArmature::create(name);
    armature->getAnimation()->playWithIndex(0);
    armature->getAnimation()->setMovementEventCallFunc(this, SEL_MovementEventCallFunc(&Ef::actionCallback));
    this->addChild(armature);
    return true;
}

void Ef::actionCallback(CCArmature *pArmature,MovementEventType eventType, const char *animationID)
{
    if (eventType == LOOP_COMPLETE && isRemove)
    {
        this->removeFromParentAndCleanup(true);
    }
}

CCSize Ef::getSize()
{
    return this->armature->getContentSize();
}
