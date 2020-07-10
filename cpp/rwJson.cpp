/****************************************************************************
name: read&writeJson.cpp
date: 2020/5/22
func: 用于读取template.json文件内容，或修改template.json生成需要的json文件, 或
      直接生成json文件， 输液袋工程样例
maintainer: zhaoliang
****************************************************************************/

#include <jsoncpp/json/json.h>
#include <iostream>
#include <fstream>
#include <string>
#include <opencv2/opencv.hpp>   // 如果用到opencv

#include "base64.h"     // 如果需要图片的base64编码

using namespace std;

int main(int argc, char* argv[])
{
    string json_template = "template.json";
    // 以二进制形式读取json文件内容，创建文件流
    ifstream is(json_template, ios::binary);
 
    if (!is.is_open())
    {
        cout << "open json file failed." << endl;
        return -1;
    }
    
    Json::Reader reader;
    Json::Value root;     // 用来维护整个解析结果

    // 也可以用字符串保存json数据  
	const char* json_str="{\"name\":\"Tong\",\"age\":\"21\",\"sex\":\"man\"}";

    // 解析json文件内容
    if (reader.parse(is, root))
    {
/// 以下内容通过tmplate生成labelme工具对应的json标注文件， 需要修改shapes节点中的points数组， 以及imagePath和imageData节点
        // 统一用Json::Value来表示变量——字符串，数组，整型，浮点型
        // 修改时需要引用&，读取时不需要
        const Json::Value& shapes_arr = root["shapes"];
        // 如果是数组，即[]变量
        for(int i=0; i<shapes_arr.size(); i++)
        {
            const Json::Value points_arr = shapes_arr[i]["points"];
            // 访问嵌套数组
            for(int j=0; j<points_arr.size(); j++)
            {
                // 访问浮点数.asFloat()
                // 同理，访问整型.asInt()， 访问字符串.asString();
                const Json::Value point_arr = points_arr[j];
                float x = point_arr[0].asFloat();
                float y = point_arr[1].asFloat();
                cout << "x, y: " << x << ", " << y << endl;
            }   
        }
        // 访问字符串变量并修改
		Json::Value& imagePath_str = root["imagePath"];   // 修改imagePath字符串
        imagePath_str = jpg_name.c_str();
        Json::Value& imageData_str = root["imageData"];   // 修改imageData字符串

        // 这里使用了base64编码的图片 
        cv::Mat frame = cv::imread(image_path);
        std::vector<unsigned char> buffer;
		cv::imencode(".jpg", frame, buffer);
		string img(buffer.begin(), buffer.end());
		string base64_img = base64_encode((BYTE const *) img.c_str(), img.length());
        imageData_str = base64_img.c_str();  

/// 以上内容生成labelme工具对应的json标注文件

        // 访问子节点
        String subnode = root["flags"]["subnode"].asString();     
    }

    is.close();

    // 输出文件流生成通过修改template得到的json文件
    ofstream ofs;
    ofs.open("out.json");
    ofs<<root.toStyledString();
    ofs.close();

    // 直接生成需要的json文件
    Json::Value root1;
 
    // 组装json内容, 普通变量
    root1["occupation"]  = "paladin";
    root1["camp"]        = "alliance";
    root1["role_id"]     = 1;

	Json::Value subnode;
 	//子节点属性  
	subnode["friend_name"] = Json::Value("ZhaoWuxian");
	subnode["friend_age"] = Json::Value(21);
	subnode["friend_sex"] = Json::Value("man");
 
	//子节点挂到根节点上  
	root1["subnode"] = Json::Value(subnode);
 
	//数组形式  
	root1["hobby"].append("sing");
	root1["hobby"].append("run");
	root1["hobby"].append("Tai Chi");

    ofstream ofs1;
    ofs1.open("out1.json");
	// 直接输出  
	// Json::FastWriter fw;
	// ofs1 << fw.write(root)
    // 缩进输出
    Json::StyledWriter writer;
    ofs1 << writer.write(root1);
    ofs1.close();
 
    return 0;
}

