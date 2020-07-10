/****************************************************************************
name: createXML.cpp
date: 2020/5/23
func: 用于直接生成labelImg标注工具对应的xml标注文件， 安检机工程样例
maintainer: zhaoliang
****************************************************************************/

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include <dirent.h>  
#include <unistd.h>
#include <time.h>
#include <stdio.h>

#include "tinyxml2.h" 

using namespace std;
using namespace tinyxml2;

char *Labels[]={"knife", "liquid", "gun", "power_bank", "metal_tool", "scissors", "flammable_material", "electric_shocking_device"};

XMLElement* setElement(XMLDocument* xml, const char* tag, const char* text)
{
    // 创建字符串文本节点并赋值
	XMLElement* elem = xml->NewElement(tag);
    elem->SetText(text);
	return elem;
}

XMLElement* setElement(XMLDocument* xml, const char* tag, const int text)
{
    // 创建整型文本节点并赋值
	XMLElement* elem = xml->NewElement(tag);
    elem->SetText(text);
	return elem;
}

XMLElement* setObject(XMLDocument* xml, const char* obj_name,  vector<int>& box)
{
    // 创建obj节点并赋值
	XMLElement* obj = xml->NewElement("object");
	XMLElement* name = setElement(xml, "name", obj_name);
	XMLElement* pose = setElement(xml, "pose", "Unspecified");
	XMLElement* truncated = setElement(xml, "truncated", "0");
	XMLElement* difficult = setElement(xml, "difficult", "0");
	XMLElement* bndbox = xml->NewElement("bndbox");
	bndbox->InsertEndChild(setElement(xml, "xmin", box[0]));
	bndbox->InsertEndChild(setElement(xml, "xmax", box[1]));
	bndbox->InsertEndChild(setElement(xml, "ymin", box[2]));
	bndbox->InsertEndChild(setElement(xml, "ymax", box[3]));
	
	obj->InsertEndChild(name);
	obj->InsertEndChild(pose);
	obj->InsertEndChild(truncated);
	obj->InsertEndChild(difficult);
	obj->InsertEndChild(bndbox);
	
	return obj;
}

void createXML(const string save_path, const string image_name, const int width, const int height, vector<int>& objs, vector<vector<int> >& boxes)
{
    if (objs.size()==0) return;
    
    // 创建新的XMLDocument
	XMLDocument* xml = new XMLDocument();
    // 创建根节点
	XMLElement* root = xml->NewElement("annotation");
    // 根节点插入到(空)文件末尾
    xml->InsertEndChild(root);

    // 分批创建节点
	XMLElement* folder = setElement(xml, "folder", "bova");
	XMLElement* filename = setElement(xml, "filename", image_name.c_str());
	XMLElement* path = setElement(xml, "path", "bova");
	
	XMLElement* source = xml->NewElement("source");
    // database子节点插入到source节点末尾
	source->InsertEndChild(setElement(xml, "database", "Unknown"));
	
	XMLElement* size = xml->NewElement("size");
    // width子节点插入到size节点首位
	size->InsertFirstChild(setElement(xml, "width", width));
	size->InsertEndChild(setElement(xml, "height", height));
	size->InsertEndChild(setElement(xml, "depth", 0));
	
	XMLElement* segmented = setElement(xml, "segmented", "0");

    vector<XMLElement*> vobjs;
    for(unsigned i=0; i<objs.size(); i++)
		vobjs.push_back(setObject(xml, Labels[objs[i]], boxes[i]));

    // 将创建的各节点插入到文件中
    root->InsertFirstChild(folder);
    root->InsertEndChild(filename);
    root->InsertEndChild(path);
    root->InsertEndChild(source);
    root->InsertEndChild(size);
    root->InsertEndChild(segmented);
    for(auto& it: vobjs)
		root->InsertEndChild(it);

    // xml文件打印
    xml->Print();
    string xml_name = save_path+"/"+image_name.substr(0, image_name.size()-4)+".xml";
cout << xml_name << endl;
    // xml文件保存
    xml->SaveFile(xml_name.c_str());
    delete xml;

}

int main(int argc, char* argv[])
{
    // 生成labelImg工具对应的xml标注文件
    string save_path = ".";
    string image_name = "demo.jpg";
    int width = 416, height= 416;
    vector<int> objs={1, 4, 7};   // 标签对应在Labels中的索引
    vector<vector<int>> boxes={{100, 100, 200, 200}, {200, 200, 300, 300}, {50, 50, 100, 100}};  // obj对应的box
    createXML(save_path, image_name, width, height, objs, boxes);
 
    return 0;   
}

