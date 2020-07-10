/****************************************************************************
name: dictTraversal.cpp
date: 2020/5/22
func: 用于读取给定文件路径下一定后缀的所有文件
maintainer: zhaoliang
****************************************************************************/

#include <sys/stat.h>
#include <dirent.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

/** @brief 返回文件列表
根据后缀suffix递归筛选path路径下符合要求的文件，返回vector
@param path_str: 输入的查找路径
@param files: 返回的文件列表
@param suffix: 后缀，默认为空，此时返回所有文件
 */
void getFiles(const string path_str, vector<string>& files, string suffix=".jpg")
{
    // 根据后缀suffix筛选path路径下符合要求的文件，返回vector
    string path0;
    if(*(path_str.end()-1)!='/')
        path0=path_str+'/';
    else
        path0=path_str;

    const char* path = path_str.c_str();  // must be const char*

    DIR* pDir;
    struct dirent* ptr;

    struct stat s;
    lstat(path, &s);

    if(!S_ISDIR(s.st_mode)){
        cout << "not a valid directory: " << path << endl;
        return;
    }

    if(!(pDir = opendir(path))){
        cout << "opendir error: " << path << endl;
        return;
    }
    int i = 0;
    string subFile;
    while((ptr = readdir(pDir)) != 0){
        subFile = ptr->d_name;
        if(subFile == "." || subFile == "..")
            continue;
        subFile = path0 + subFile;
// cout << ++i << ": " << subFile << endl;
        // 根据后缀suffix筛选
        int suffix_len = suffix.length();
        if(suffix_len!=0){
// cout << subFile.substr(subFile.length()-suffix_len) << endl;  // 分割出来的疑似后缀
            if(subFile.substr(subFile.length()-suffix_len) == suffix){
// cout << "push" << endl;
                files.push_back(subFile);
            }
        }
        else
            files.push_back(subFile);
    }

    closedir(pDir);
}


int main(int argc, char* argv[])
{
    string path="/media/zl/Elements/infusionbagdata/total_pics/segment_data";
    vector<string> files;
    getFiles(path, files, ".jpg");
    for(auto &f: files)
    {
        cout << f << endl;
    }
    return 0;
}






