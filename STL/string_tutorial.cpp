/* 
STL容器: string 

- string是C++风格的字符串，而string本质上是一个类 

1. string和char * 区别：
    - char * 是一个指针
    - string是一个类，类内部封装了char*，管理这个字符串，是一个char*型的容器。 

2. string封装了多种成员算法 
    - 查找find，拷贝copy，删除delete 替换replace，插入insert
    - string管理char*所分配的内存，不用担心复制越界和取值越界等，由类内部进行负责 

3. 构造、赋值(assign)、拼接(append)、查找代替(find、replace)、比较(compare)、存取([]或者at)、插入和删除(insert、erase)、子串(substr)
*/ 

#include <iostream> 
#include <string> 
using namespace std; 

/*
tutorial-1. string构造函数
    // 重构 
    string(); //创建一个空的字符串 例如: string str;
    string(const char* s); //使用字符串s初始化
    string(const string& str); //使用一个string对象初始化另一个string对象
    string(int n, char c); //使用n个字符c初始化
*/ 

void C1_StringConstructor(){
    // 创建空字符串 string()
    string s1;   
    cout << "str1 = " << s1 << endl; 

    // 使用字符串s初始化  string(const char* s) 
    const char* str = "hello world"; 
    string s2(str); //把c_string转换成了string 
    cout << "str2 = " << s2 << endl;   

    // 拷贝构造调用  string(const string& str);
	string s3(s2);  
	cout << "str3 = " << s3 << endl; 

    // 使用n个字符c初始化 string(int n, char c) 
    string s4(10,'a'); 
    cout << "str3 = " << s4 << endl; 

}  

/*
tutorial-2. string赋值操作
赋值的函数原型：
    string& operator=(const char* s); //char*类型字符串 赋值给当前的字符串
    string& operator=(const string &s); //把字符串s赋给当前的字符串
    string& operator=(char c); //字符赋值给当前的字符串
    string& assign(const char *s); //把字符串s赋给当前的字符串
    string& assign(const char *s, int n); //把字符串s的前n个字符赋给当前的字符串
    string& assign(const string &s); //把字符串s赋给当前字符串
    string& assign(int n, char c); //用n个字符c赋给当前字符串
*/
void C2_StringAssignment(){

    // string& operator=(const char* s);  =重载
	string str1;
	str1 = "hello world";
	cout << "str1 = " << str1 << endl;

    // string& operator=(const string &s); 
	string str2;
	str2 = str1;
	cout << "str2 = " << str2 << endl;

    // string& operator=(char c); //字符赋值给当前的字符串 
	string str3;
	str3 = 'a';
	cout << "str3 = " << str3 << endl;

    // string& assign(const char *s); assign函数 
	string str4;
	str4.assign("hello c++");
	cout << "str4 = " << str4 << endl;

    // 把字符串前n个数复制给str5 
    // string& assign(const char *s, int n); 
	string str5;
	str5.assign("hello c++",5);
	cout << "str5 = " << str5 << endl;  // 0,1,2,3,4 

    // string& assign(const string &s); //把字符串s赋给当前字符串
	string str6;
	str6.assign(str5);
	cout << "str6 = " << str6 << endl;

    // string& assign(int n, char c); //用n个字符c赋给当前字符串
	string str7;
	str7.assign(5, 'x');
	cout << "str7 = " << str7 << endl; 
}

/*
tutorial-3. string拼接
实现在字符串末尾拼接字符串
函数原型：
    string& operator+=(const char* str); //重载+=操作符
    string& operator+=(const char c); //重载+=操作符
    string& operator+=(const string& str); //重载+=操作符
    string& append(const char *s); //把字符串s连接到当前字符串结尾
    string& append(const char *s, int n); //把字符串s的前n个字符连接到当前字符串结尾
    string& append(const string &s); //同operator+=(const string& str)
    string& append(const string &s, int pos, int n);//字符串s中从pos开始的n个字符连接到字符串结尾
*/
void C3_StringSplice(){
    string str1 = "我"; 
    
    // 重载+=  
    // string& operator+=(const char* str); //重载+=操作符
    str1 += "爱的游戏"; 
    
    // string& operator+=(const char c); //重载+=操作符
    str1 += ":";

    // string& operator+=(const string& str); //重载+=操作符 
    string str2 = "LOL DNF "; 
    str1 += str2;  
    cout << "str1 = " << str1 << endl;    

    // append用法 
    // string& append(const char *s); //把字符串s连接到当前字符串结尾
    // string& append(const char *s, int n); //把字符串s的前n个字符连接到当前字符串结尾
    const char* str3 = "I am a student. ";  
    str1.append(str3); 
    str1.append(str3, 5); 
    cout << "str1 = " << str1 << endl;   

    // string& append(const string &s); //同operator+=(const string& str)
    // string& append(const string &s, int pos, int n);//字符串s中从pos开始的n个字符连接到字符串结尾
    string str4 = "a gamer !!!!!!"; 
    str1.append(str4); 
    str1.append(str4, 7, 6); 
    cout << "str1 = " << str1 << endl; 
}

/*
tutorial-4. string查找和替换
功能描述：
    查找：查找指定字符串是否存在
    替换：在指定的位置替换字符串
函数原型：
    int find(const string& str, int pos = 0) const; //查找str第一次出现位置,从pos开始查找
    int find(const char* s, int pos = 0) const; //查找s第一次出现位置,从pos开始查找
    int find(const char* s, int pos, int n) const; //从pos位置查找s的前n个字符第一次位置
    int find(const char c, int pos = 0) const; //查找字符c第一次出现位置
    int rfind(const string& str, int pos = npos) const; //查找str最后一次位置,从pos开始查找
    int rfind(const char* s, int pos = npos) const; //查找s最后一次出现位置,从pos开始查找
    int rfind(const char* s, int pos, int n) const; //从pos查找s的前n个字符最后一次位置
    int rfind(const char c, int pos = 0) const; //查找字符c最后一次出现位置 
    ----- 
    string& replace(int pos, int n, const string& str); //替换从pos开始n个字符为字符串str
    string& replace(int pos, int n,const char* s); //替换从pos开始的n个字符为字符串s 
总结：
    find查找是从左往后，rfind从右往左
    find找到字符串后返回查找的第一个字符位置，找不到返回-1
    replace在替换时，要指定从哪个位置起，多少个字符，替换成什么样的字符串
*/ 

void C4_StringFindReplace(){
    string str1 = "abcdefgde";

    // int find(const string& str, int pos = 0) const; //查找str第一次出现位置,从pos开始查找 
	int pos = str1.find("de", 0); // 3  
	if (pos == -1)
	{
		cout << "未找到" << endl;
	}
	else
	{
		cout << "pos = " << pos << endl;
	} 

    // 最后一次出现位置 
    pos = str1.rfind("de");
	cout << "pos = " << pos << endl;

    // Replace 
    //替换 
    // string& replace(int pos, int n,const char* s); //替换从pos开始的n个字符为字符串s
	string str2 = "abcdefgde"; 
    cout << "str2 = " << str2 << endl;
	str2.replace(1, 3, "1111"); // 1是第二位 
	cout << "str2 = " << str2 << endl;
} 

/*
tutorial-5. string比较 
功能描述：
    字符串之间的比较
比较方式：
    字符串比较是按字符的ASCII码进行对比
    = 返回 0
    > 返回 1
    < 返回 -1 
函数原型：
    int compare(const string &s) const; //与字符串s比较
    int compare(const char *s) const; //与字符串s比较 

总结：字符串对比主要是用于比较两个字符串是否相等，判断谁大谁小的意义并不是很大 
*/
//字符串比较
void C5_StringCompare()
{

	string s1 = "hello";
	string s2 = "aello";

	int ret = s1.compare(s2);
    
    // 0 表示相同 
	if (ret == 0) {
		cout << "s1 等于 s2" << endl;
	}
	else if (ret > 0)
	{
		cout << "s1 大于 s2" << endl;
	}
	else
	{
		cout << "s1 小于 s2" << endl;
	}
}

/*
tutorial-6. string字符存取  
string中单个字符存取方式有两种
char& operator[](int n); //通过[]方式取字符---重载[]
char& at(int n); //通过at方法获取字符 

总结：string字符串中单个字符存取有两种方式，利用 [ ] 或 at
*/
void C6_StringAccess()
{
	string str = "hello world";

	for (int i = 0; i < str.size(); i++)
	{
		cout << str[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < str.size(); i++)
	{
		cout << str.at(i) << " ";
	}
	cout << endl;


	//字符修改
	str[0] = 'x';
	str.at(1) = 'x';
	cout << str << endl;
} 

/*
tutorial-7. string字符插入和删除 
功能描述：
    对string字符串进行插入和删除字符操作
函数原型：
    string& insert(int pos, const char* s); //插入字符串
    string& insert(int pos, const string& str); //插入字符串
    string& insert(int pos, int n, char c); //在指定位置插入n个字符c
    string& erase(int pos, int n = npos); //删除从Pos开始的n个字符
*/ 

void C7_StringInsertAndErase(){
    string basic_str = "hello"; 
    
    // insert string& insert(int pos, const char* s); //插入字符串
    string str1 = basic_str.insert(5, " world"); 
    cout << str1 << endl; 

    // insert2 string& insert(int pos, const string& str); //插入字符串
    string insert_str = " I am coming";
    string str2 = basic_str.insert(11, insert_str); 
    cout << str2 << endl; 

    // insert 3  string& insert(int pos, int n, char c); //在指定位置插入n个字符c  
    string str3 = basic_str.insert(basic_str.size(), 3, '!'); 
    cout << str3 << endl;  

    // erase掉最后一个感叹号 
    string str4 = basic_str.erase(basic_str.size()-2, 2); 
    cout << str4 << endl; 
}

/*
tutorial-8. string子串 
功能描述：
    从字符串中获取想要的子串 
函数原型：
    string substr(int pos = 0, int n = npos) const; //返回由pos开始的n个字符组成的字符串 

总结：灵活的运用求子串功能，可以在实际开发中获取有效的信息
*/ 
void C8_StringSubStr(){
    string str = "1234567"; 
    string sub_str = str.substr(2, 3); // 从2开始，3个字符 
    cout << sub_str << endl; 

    // 结合搜索
    string email = "AAA@126.com" ;
    int pos = email.find("@");  
    string sub_email = email.substr(pos+1);
    
    // 获取用户名 
    string user_name = email.substr(0, pos); 
    cout << "username: " << user_name << endl;  

}

int main(){
    // C1_StringConstructor(); 
    // C2_StringAssignment(); 
    // C3_StringSplice();  
    // C4_StringFindReplace(); 
    // C5_StringCompare();  
    // C6_StringAccess();
    // C7_StringInsertAndErase();
    C8_StringSubStr(); 
    return 0; 
}