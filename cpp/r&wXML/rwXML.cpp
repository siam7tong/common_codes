/****************************************************************************
name: r&wXML.cpp
date: 2020/5/23
func: 用于修改xml格式文件
maintainer: zhaoliang
****************************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "tinyxml2.h" 

using namespace tinyxml2;
using namespace std;

int main(int argc, char* argv[])
{
	XMLDocument doc;
	doc.LoadFile( "template.xml" );
	doc.Print();

    // 获取xml文件根节点
    XMLElement* root = doc.RootElement();
    vector<XMLElement*> del_elems;

/// 访问同一级别所有的object节点，并删除所有name==0.9%的object节点
    XMLElement* obj = root->FirstChildElement("object");
    // 访问节点字符串文本值
    const char* name = obj->FirstChildElement("name")->GetText();

    // 待删除节点指针放入vector
    if (strcmp(name, "0.9%")==0)
        del_elems.emplace_back(obj);
    // 访问该object节点之后的第一个同名节点
    obj = obj->NextSiblingElement("object");
    while(obj != NULL){
        name = obj->FirstChildElement("name")->GetText();
		if (strcmp(name, "0.9%")==0) 
            del_elems.emplace_back(obj);            
        obj = obj->NextSiblingElement("object");  
    }
    // 删除收集的子节点
    for(auto &e: del_elems)
        root->DeleteChild(e);
/// object节点访问结束

    doc.SaveFile("out.xml");
    // doc 变量指空，可以重新关联xml文件
    doc.Clear();
    
    return 0;
}
