#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>

string file_name = "path"; 
############ 判断文件是否存在，从上到下耗时逐渐变少
1. 使用ifstream打开文件流
ifstream f(file_name.c_str());
if (f.good()) 
    cout << "文件存在" << endl;

2. 使用fopen方式打开文件
if (FILE *file = fopen(file_name.c_str(), "r")) {
    fclose(file);
    cout << "文件存在" << endl;
}

3. 使用access函数获取文件状态
if (access(file_name.c_str(), F_OK ) != -1)
    cout << "文件存在" << endl;

4. 使用stat函数获取文件状态
struct stat buffer;
if (stat(file_name.c_str(), &buffer)==0)
    cout << "文件存在" << endl;
