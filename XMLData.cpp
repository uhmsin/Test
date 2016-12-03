//
//  XMLData.cpp
//  King
//
//  Created by mac on 14-4-25.
//
//

#include "XMLData.h"
#include "GameData.h"
#include "Define.h"
static XMLData* xmldata = NULL;
static tinyxml2::XMLDocument *pDoc =NULL;




XMLData* XMLData::sharedXMLData()
{
  
    if (xmldata == NULL)
    {
        xmldata = new XMLData();
		if (xmldata && xmldata->init())
		{    
    		xmldata->autorelease();
		}
		else
		{
			CC_SAFE_DELETE(xmldata);
            xmldata = NULL;
		}
    }
	
    return xmldata;
}

bool XMLData::init()
{

    std::string filepath =  CCFileUtils::sharedFileUtils()->getWritablePath() + "kingdata2.xml";
    bool isFIleExist =  CCFileUtils::sharedFileUtils()->isFileExist(filepath.c_str());
	if (pDoc == NULL)
	{
		pDoc = new tinyxml2::XMLDocument();     //xmlDoc
	}
	CCLog("XMLData::init()-1");
    if (isFIleExist)
    {
        return true;
    }
    //tinyxml2::XMLDocument *pDoc = new tinyxml2::XMLDocument();     //xml文档
    if (NULL==pDoc)
    {
        return false;
    }
    tinyxml2::XMLDeclaration *pDel = pDoc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");   //xml声明
    if (NULL==pDel)
    {
        return false;
    }
	CCLog("XMLData::init()-2");
    pDoc->LinkEndChild(pDel);
    tinyxml2::XMLElement *plistElement = pDoc->NewElement("plist");     //节点plist
    plistElement->SetAttribute("version", "1.0");//给节点设置属性
    pDoc->LinkEndChild(plistElement);
    tinyxml2::XMLElement *dictElement = pDoc->NewElement("dict");   //节点dict
    plistElement->LinkEndChild(dictElement);
 	CCLog("XMLData::init()-3x");
    for (int i = 0; i<=20; i++) 
	{
        char guan[128] = {0};
		CCLog("XMLData::init()-i=%d",i);
        //sprintf(guan, "第%d关",i+1);
		//sprintf(guan, "%s%d%s",I18N_STR(82),i+1,I18N_STR(83));
		sprintf(guan, "di%dguan",i+1);
		CCLog("XMLData::init()-guan=%s",guan);
        tinyxml2::XMLElement *strEle = pDoc->NewElement(guan);
		//CCLog("XMLData::init()-81-%s",I18N_STR(81));
        strEle->LinkEndChild(pDoc->NewText("0"));
        //strEle->LinkEndChild(pDoc->NewText(I18N_STR(81)));
        dictElement->LinkEndChild(strEle);
        strEle->SetAttribute("score", 0);
        strEle->SetAttribute("times", 0);
    }
	CCLog("XMLData::init()-4x");
    pDoc->SaveFile(filepath.c_str());//保存文件 参数：路径
    pDoc->Print();//打印
    //delete pDoc;

    return true;
}

const char* XMLData::read(int guan)
{
	CCLog("XMLData::read=%d",guan);
    std::string filePath = CCFileUtils::sharedFileUtils()->getWritablePath() + "kingdata2.xml";   //xml文件路径
    CCLog("XMLData::read--1");
    
    CCLog("XMLData::read--2");
    pDoc->LoadFile(filePath.c_str());
	CCLog("XMLData::read--3");
	tinyxml2::XMLElement *dictEle  = NULL;
	tinyxml2::XMLElement *keyEle   = NULL;
    tinyxml2::XMLElement *rootEle  = NULL;      //得到跟节点
    const char* str   =	NULL;	
    rootEle = pDoc->RootElement();
    if (rootEle != NULL)
    {
	    dictEle = rootEle->FirstChildElement();
    }
	if (dictEle!=NULL)
	{
		keyEle = dictEle->FirstChildElement(); //dict下面的子节点 key
	}
  
    guan = min(guan,20);
	CCLog("XMLData::read--guan=%d",guan);
    for (int i=1;  i<=guan-1;i++)
    {
    	if (keyEle!=NULL)
    	{
        	keyEle = keyEle->NextSiblingElement();
    	}
    }
	CCLog("XMLData::read--4=%d",keyEle);
	if (keyEle!=NULL)
	{
		 CCLog("XMLData::read--keyEle!=NULL");
		 str = keyEle->GetText();
	}
    pDoc->SaveFile(filePath.c_str());
	CCLog("XMLData::read--5,str=%s",str);
    //delete pDoc;
    return str;
	
}

int XMLData::getScore(int guan)
{

	CCLog("XMLData::getScore--1,guan=%d",guan);
    std::string filePath = CCFileUtils::sharedFileUtils()->getWritablePath() + "kingdata2.xml";   //xml文件路径
    //tinyxml2::XMLDocument *pDoc = new tinyxml2::XMLDocument();     //xmlDoc
    
    pDoc->LoadFile(filePath.c_str());
    tinyxml2::XMLElement *rootEle  = NULL;    //得到跟节点
    
    tinyxml2::XMLElement *dictEle  = NULL;//rootEle->FirstChildElement();
    tinyxml2::XMLElement *keyEle   = NULL;//dictEle->FirstChildElement(); //dict下面的子节点 key
    int str = 0;
	
	rootEle = pDoc->RootElement();  
    if (rootEle != NULL)
	{
		dictEle = rootEle->FirstChildElement();
	}
	if(dictEle != NULL)
	{
		keyEle = dictEle->FirstChildElement();
	}
    guan = min(guan,20);
    for (int i=1;  i<=guan-1;i++)
    {
    	if(keyEle!=NULL)
		{
			keyEle = keyEle->NextSiblingElement();
		}
       
    }
	if (keyEle != NULL)
	{
		str = keyEle->IntAttribute("score");
	}
    CCLog("XMLData::getScore--2,str=%d",str);
    pDoc->SaveFile(filePath.c_str());
    //delete pDoc;
	
    return str;

}

int XMLData::getTimes(int guan)
{
	CCLog("XMLData::getTimes--1,guan=%d",guan);
    std::string filePath = CCFileUtils::sharedFileUtils()->getWritablePath() + "kingdata2.xml";   //xml文件路径
    //tinyxml2::XMLDocument *pDoc = new tinyxml2::XMLDocument();     //xmlDoc
    pDoc->LoadFile(filePath.c_str());
    tinyxml2::XMLElement *rootEle = pDoc->RootElement();      //得到跟节点
    tinyxml2::XMLElement *dictEle = NULL;//rootEle->FirstChildElement();
    tinyxml2::XMLElement *keyEle = NULL;//dictEle->FirstChildElement(); //dict下面的子节点 key
	int str = 0;


	if (rootEle != NULL)
	{
		dictEle = rootEle->FirstChildElement();
	}
	if(dictEle != NULL)
	{
		keyEle = dictEle->FirstChildElement();
	}
    guan = min(guan,20);
    for (int i=1;  i<=guan-1;i++)
    {
    	if(keyEle!=NULL)
		{
			keyEle = keyEle->NextSiblingElement();
		}
       
    }
	if (keyEle != NULL)
	{
		str = keyEle->IntAttribute("times");
	}
    CCLog("XMLData::getTimes--2,str=%d",str);
    pDoc->SaveFile(filePath.c_str());
    //delete pDoc;
    return str;
	
}


void XMLData::update(int guan,int score,int times)
{
	CCLog("XMLData::update--1");
    std::string filePath = CCFileUtils::sharedFileUtils()->getWritablePath() + "kingdata2.xml";   //xml文件路径

	//tinyxml2::XMLDocument *pDoc = new tinyxml2::XMLDocument();
	
  	
    pDoc->LoadFile(filePath.c_str());
	CCLog("XMLData::update--2");
    tinyxml2::XMLElement *rootEle = pDoc->RootElement();      //得到跟节点
    tinyxml2::XMLElement *dictEle = NULL;//rootEle->FirstChildElement();
    tinyxml2::XMLElement *keyEle = NULL;//dictEle->FirstChildElement(); //dict下面的子节点 key
	CCLog("XMLData::update--3");
	if (rootEle!=NULL)
	{
		dictEle = rootEle->FirstChildElement();
	}
	if(dictEle!=NULL )
	{
		keyEle =  dictEle->FirstChildElement();
	}
	CCLog("XMLData::update--4");
    for (int i=1;  i<=guan-1;i++)
    {
    	if(keyEle!=	NULL)
		{
			keyEle = keyEle->NextSiblingElement();
		}
        
    }
	CCLog("XMLData::update--5");
	if (keyEle!=NULL)
	{
		keyEle->DeleteChildren();
		keyEle->SetAttribute("score", score);
		keyEle->SetAttribute("times", times);
	}
    char newScore[128] = {0};
	CCLog("XMLData::update--6");
    //sprintf(newScore, "%d分",score);
    sprintf(newScore, "%d%s",score,I18N_STR(84));
	if (keyEle != NULL )
	{
		keyEle->LinkEndChild(pDoc->NewText(newScore));//给节点设置值
	}
    
    CCLog("XMLData::update--7");
    pDoc->SaveFile(filePath.c_str());
	
}


