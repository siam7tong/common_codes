/****************************************************************************
name: stringSplit.cpp
date: 2020/5/22
func: 用于将string类型字符串用分隔符分开
maintainer: zhaoliang
****************************************************************************/

#include <vector>
#include <string.h>
#include <iostream>
#include <sstream>

using namespace std;

template<class Type>
void stringSplit(const string& str, const string& delimiter, vector<Type>& ret) 
{  
	if("" == str) 
        return;  
	//先将要切割的字符串从string类型转换为char*类型  
	char * cstr = new char[str.length() + 1] ; //不要忘了加1,，为末尾的"\0"留位置
	strcpy(cstr, str.c_str());   
 
	char * d = new char[delimiter.length() + 1];  
	strcpy(d, delimiter.c_str());  
 
	char *p = strtok(cstr, d);  
	while(p) {
        string value = p;
        std::istringstream iss(value);  
        Type ph;
        iss >> ph;
	    ret.emplace_back(ph); //存入结果数组  
        p = strtok(NULL, d);  
	}  
 
	return;  
} 


int main(int argc, char* argv[])
{
    string folder = "a/b/c/d";

    vector<string> vs;
    stringSplit(folder, "/", vs);
    for(auto &v: vs) cout << v << endl;

    string number = "0,8,2,7";
    vector<int> vi;
    stringSplit(number, ",", vi);
    for(auto &v: vi) cout << v << endl;

    return 0;
}

