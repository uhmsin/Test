//
//  State.h
//  XiYouJi
//
//  Created by mac on 14-3-23.
//
//

#ifndef __XiYouJi__State__
#define __XiYouJi__State__

template <class entity_type>
class State
{
public:
    
    virtual ~State(){}
    
    //this will execute when the state is entered
    virtual void Enter(entity_type*)=0;
    
    //this is the states normal update function
    virtual void Execute(entity_type*)=0;
    
    //this will execute when the state is exited. (My word, isn't
    //life full of surprises... ;o))
    virtual void Exit(entity_type*)=0;
};
#endif /* defined(__XiYouJi__State__) */
