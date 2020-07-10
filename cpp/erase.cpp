#include <iostream>
#include <vector>
using namespace std;
int main()
{
	vector<int> vec;
	for(int i=0;i<10;i++)
	{
 		vec.push_back(i);
	}
	vec.erase(vec.begin()+5);//erase the 6th element
	vec.erase(vec.begin(),vec.begin()+3);
	for(int i=0;i<vec.size();i++)
	{
	    cout << i  << ":" << vec[i] << ' ';
	}
	cout<<endl;
	system("pause");
	return 0;
}
