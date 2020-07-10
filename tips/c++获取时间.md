############c++获取时间

#include <ctime>
#include <sys/time.h>
struct timeval now_ac;
struct tm now;
#获取 毫秒
gettimeofday(&now_ac, nullptr);
localtime_r(&now_ac.tv_sec, &now);
int msec = now_ac.tv_usec / 1000;
#获取 年月日时分秒
char date[30] = {0};
strftime(date, sizeof(date), "[%Y-%m-%d %H:%M:%S", &now);
#生成日期标识
char date_ac[30]={0};
snprintf(date_ac, sizeof(date_ac), "%s.%03d] ", date, msec);

############计算时间间隔
#include<chrono>
auto start = chrono::steady_clock::now();
...
auto stop = chrono::steady_clock::now();
auto timing = chrono::duration_cast<chrono::duration<double>>(stop - start);
cout << timing.count() << endl;
