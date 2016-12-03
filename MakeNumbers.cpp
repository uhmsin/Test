//
//  MakeNumbers.cpp
//  xiyou
//
//  Created by mac on 14-3-16.
//
//

#include "MakeNumbers.h"
#include <string>
using namespace std;
/*
 这个类主要是显示组合自定义图片类型的伤害数值。
 */
MakeNumbers::MakeNumbers(int attckmun)
{
	//解析数值转化为2中格式字符串string和CCString；
	char char_attckmun[100] = {0};
    sprintf(char_attckmun, "%d",attckmun);
    
	//这个主要用途拿来作为字符和int之间的相互转换
	CCString* numberstr = CCString::create(char_attckmun);
	//这个拿来截取字符
	string str = numberstr->getCString();
	//获取整张素材图片，图片内容为-0123456789；
	CCSprite* number_all = CCSprite::create("num/shuzixiao.png");
	//获取整张图片长宽
	float allwight= number_all->getContentSize().width;
    float allhigth= number_all->getContentSize().height;
	//获取单张图片长宽
   	float onewight = allwight/10;
	float onehigth = allhigth;
	//获取第一个符号扣血-作为首张图片的底图
	CCRect imgrect_moren = CCRect(0,0,onewight,onehigth);
	numbers = CCSprite::create();
    numbers->setContentSize(imgrect_moren.size);
    CCSprite* num = CCSprite::create("num/shuzixiao.png",imgrect_moren);
	//循环解析出“-”符号号后面的具体数值伤害
	for (int i = 0; i < numberstr->length(); i++)
	{
		//依次解析每个数值大小
		string nownumber =  str.substr(0+i,1);
		CCString* cc_nownumber = CCString::create(nownumber);
		//将解析数值去寻找图片
        CCRect imgrect_moren = CCRect(onewight*cc_nownumber->intValue(),0,onewight,onehigth);
        CCSprite* numbers_now = CCSprite::create("num/shuzixiao.png",imgrect_moren);
		//将得到的图片依次尾追在“-”图片得后面
        numbers_now->setPosition(ccp( num->getContentSize().width*0.8*i ,num->getContentSize().height/2));
        numbers->addChild(numbers_now,2,10+i);
	}
    
}

MakeNumbers::MakeNumbers(int attckmun,const char* name)
{
    //解析数值转化为2中格式字符串string和CCString；
	char char_attckmun[100] = {0};
    sprintf(char_attckmun, "%d",attckmun);
    
	//这个主要用途拿来作为字符和int之间的相互转换
	CCString* numberstr = CCString::create(char_attckmun);
	//这个拿来截取字符
	string str = numberstr->getCString();
	//获取整张素材图片，图片内容为-0123456789；
	CCSprite* number_all = CCSprite::create(name);
	//获取整张图片长宽
	float allwight= number_all->getContentSize().width;
    float allhigth= number_all->getContentSize().height;
	//获取单张图片长宽
   	float onewight = allwight/10;
	float onehigth = allhigth;
	//获取第一个符号扣血-作为首张图片的底图
	CCRect imgrect_moren = CCRect(0,0,onewight,onehigth);
	numbers = CCSprite::create();
    numbers->setContentSize(imgrect_moren.size);
    CCSprite* num = CCSprite::create(name,imgrect_moren);
	//循环解析出“-”符号号后面的具体数值伤害
	for (int i = 0; i < numberstr->length(); i++)
	{
		//依次解析每个数值大小
		string nownumber =  str.substr(0+i,1);
		CCString* cc_nownumber = CCString::create(nownumber);
		//将解析数值去寻找图片
        CCRect imgrect_moren = CCRect(onewight*cc_nownumber->intValue(),0,onewight,onehigth);
        CCSprite* numbers_now = CCSprite::create(name,imgrect_moren);
		//将得到的图片依次尾追在“-”图片得后面
        numbers_now->setPosition(ccp( num->getContentSize().width*0.8*i ,num->getContentSize().height/2));
        numbers->addChild(numbers_now,2,10+i);
	}
}



MakeNumbers::~MakeNumbers(void)
{
}