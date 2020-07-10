```
vector<char> str={'a', 'b', 'x', 'g', 'c', 'e'};
```
## 获取指定元素的索引
```
#include <algorithm> // 包含算法头文件
#include <vector>
//此迭代器用来判断查找元素在不在容器内 
vector<char>::iterator it;	
it = find(str.begin(), str.end(), 'c');
if(it != v.end())
    //distance计算第一个参数到第二个参数之间的距离。如果第二个参数的顺序在第一个参数前面的话,函数是会返回负值的；如果迭代器不在一个容器内,程序会抛出异常。
    int index = distance(v.begin(), it); 
```


## 快速删除中间元素，适用于对元素顺序无要求的情况
```
str.at(2)=str.back();
str.pop_back()
```

## 删除指定位置元素
```
str.erase(str.begin()+3);  //删除第四个元素
str.erase(str.begin(), str.begin()+3); // 删除第1个到第3个元素
for(int i=0;i<str.size();i++)
    cout << i  << ":" << vec[i] << ' ';

```
