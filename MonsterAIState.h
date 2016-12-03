//
//  MonsterAIState.h
//  XiYouJi
//
//  Created by mac on 14-3-23.
//
//

#ifndef __XiYouJi__MonsterAIState__
#define __XiYouJi__MonsterAIState__

#include "State.h"

class Monster;
//------------------------------------------------------------------------
//    ¹ÖÎï³õÊ¼»¯×´Ì¬
//------------------------------------------------------------------------
class MonsterInitState : public State<Monster>    //¹ÖÎïÒÆ¶¯×´Ì¬»ú
{
private:
    MonsterInitState(){}
    //copy ctor and assignment should be private
    MonsterInitState(const MonsterInitState&);
    MonsterInitState& operator=(const MonsterInitState&);
    
public:
    
    static MonsterInitState* Instance();
    
    virtual void Enter(Monster* monster);
    
    virtual void Execute(Monster* monster);
    
    virtual void Exit(Monster* monster);
};

//------------------------------------------------------------------------
//    ¹ÖÎï¼¤»î×´Ì¬
//------------------------------------------------------------------------
class MonsterActiveState : public State<Monster>    //¹ÖÎïÒÆ¶¯×´Ì¬»ú
{
private:
    MonsterActiveState(){}
    //copy ctor and assignment should be private
    MonsterActiveState(const MonsterActiveState&);
    MonsterInitState& operator=(const MonsterActiveState&);
    
public:
    
    static MonsterActiveState* Instance();
    
    virtual void Enter(Monster* monster);
    
    virtual void Execute(Monster* monster);
    
    virtual void Exit(Monster* monster);
};

//------------------------------------------------------------------------
//  ¹ÖÒÆ¶¯×´Ì¬
//------------------------------------------------------------------------
class MonsterMoveState : public State<Monster>    //¹ÖÎïÒÆ¶¯×´Ì¬»ú
{
private:
    MonsterMoveState(){}
    //copy ctor and assignment should be private
    MonsterMoveState(const MonsterMoveState&);
    MonsterMoveState& operator=(const MonsterMoveState&);
    
public:
    
    static MonsterMoveState* Instance();
    
    virtual void Enter(Monster* monster);
    
    virtual void Execute(Monster* monster);
    
    virtual void Exit(Monster* monster);
};
//------------------------------------------------------------------------
//  ¹Ö¿¿½üÖ÷½Ç×´Ì¬
//------------------------------------------------------------------------
class MonsterApproachState : public State<Monster>    //¹ÖÎïÒÆ¶¯×´Ì¬»ú
{
private:
    MonsterApproachState(){}
    //copy ctor and assignment should be private
    MonsterApproachState(const MonsterApproachState&);
    MonsterApproachState& operator=(const MonsterApproachState&);
    
public:
    
    static MonsterApproachState* Instance();
    
    virtual void Enter(Monster* monster);
    
    virtual void Execute(Monster* monster);
    
    virtual void Exit(Monster* monster);
};
//------------------------------------------------------------------------
//  ¹Ö¹¥»÷Ö÷½Ç×´Ì¬
//------------------------------------------------------------------------
class MonsterAttackState : public State<Monster>    //¹ÖÎïÒÆ¶¯×´Ì¬»ú
{
private:
    MonsterAttackState(){}
    //copy ctor and assignment should be private
    MonsterAttackState(const MonsterAttackState&);
    MonsterAttackState& operator=(const MonsterAttackState&);
    
public:
    
    static MonsterAttackState* Instance();
    
    virtual void Enter(Monster* monster);
    
    virtual void Execute(Monster* monster);
    
    virtual void Exit(Monster* monster);
};


//------------------------------------------------------------------------
//  ¹ÖÊÜµ½¹¥»÷×´Ì¬
//------------------------------------------------------------------------
class MonsterBeAttackState : public State<Monster>    //¹ÖÎïÒÆ¶¯×´Ì¬»ú
{
private:
    MonsterBeAttackState(){}
    //copy ctor and assignment should be private
    MonsterBeAttackState(const MonsterBeAttackState&);
    MonsterBeAttackState& operator=(const MonsterBeAttackState&);
    
public:
    
    static MonsterBeAttackState* Instance();
    
    virtual void Enter(Monster* monster);
    
    virtual void Execute(Monster* monster);
    
    virtual void Exit(Monster* monster);
};


//------------------------------------------------------------------------
//  ¹ÖËÀÍö×´Ì¬
//------------------------------------------------------------------------
class MonsterDeadState : public State<Monster>    //¹ÖÎïÒÆ¶¯×´Ì¬»ú
{
private:
    MonsterDeadState(){}
    //copy ctor and assignment should be private
    MonsterDeadState(const MonsterDeadState&);
    MonsterDeadState& operator=(const MonsterDeadState&);
    
public:
    
    static MonsterDeadState* Instance();
    
    virtual void Enter(Monster* monster);
    
    virtual void Execute(Monster* monster);
    
    virtual void Exit(Monster* monster){};
};

//------------------------------------------------------------------------
//  ¹Öµ¹µØÆðÉí×´Ì¬
//------------------------------------------------------------------------
class MonserFallUpState : public State<Monster>    //¹ÖÎïÒÆ¶¯×´Ì¬»ú
{
private:
    MonserFallUpState(){}
    //copy ctor and assignment should be private
    MonserFallUpState(const MonserFallUpState&);
    MonserFallUpState& operator=(const MonsterDeadState&);
    
public:
    
    static MonserFallUpState* Instance();
    
    virtual void Enter(Monster* monster);
    
    virtual void Execute(Monster* monster);
    
    virtual void Exit(Monster* monster);
};




#endif /* defined(__XiYouJi__MonsterAIState__) */
