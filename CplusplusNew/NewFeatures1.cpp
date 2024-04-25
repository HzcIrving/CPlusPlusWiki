/*
C++ 11新特性 --- 易用性的改进笔记  
- 这篇脚本里记录了
https://zhuanlan.zhihu.com/p/511673241  

1，auto的使用
2，decltype的使用
3，追踪函数的返回类型
4，初始化列表和成员
5，基于范围的for循环
6，静态断言
7，noexcept修饰符
8，nullptr的使用
9，强类型枚举
10，常量表达式
11，原生字符串
*/ 

#include <iostream> 
#include <string> 
#include <vector> 
#include <typeinfo>  
#include <cassert> 


using namespace std; 

/* 1. auto使用 ------------------------------------------------------------------------------------*/  
/*auto注意事项 (展开更多)
    ------------------
    1，定义变量时必须初始化：
    auto a;//没有初始化a，无法推导a的类型；
    a = 10;
    ------------------
    2. VS编译器不支持函数形参是auto变量；
    void func(auto a)
    {} 
    ------------------
    3，auto变量不能作为自定义类型结构体或者类的成员变量；
    class A
    {
    public:
        //auto a; //不可以作为成员变量；
        //auto b = 0; //即便初始化了，也不可以；
    }; 
    -------------------
    4，不可以定义一个auto数组；
    auto arr[] = {1, 2, 3};//不允许； 
    -------------------
    5，模板实例化类型不能是auto类型；
    vector<int> a;
    //vector<auto> b;//不可以；
    //vector<auto> c = { 1 };//即便初始化了，也不可以；
*/
/*
在C语言中：
auto修饰局部变量，局部变量也叫auto变量、自动变量；
自动变量：在栈区，自动分配空间，自动维护；
int a; 等价于 auto int a;

在C++ 11中：
根据用户初始化内容自动推导类型；
*/
double func01()
{
	return 1.1;
}
struct Test01
{
	int m_a;
	string m_b;
};
void TestAuto01()
{
	int a = 1;
	auto b = 1;//自动推导b为int类型；
	auto c = func01();//自动推导c为double类型；
	Test01 str;
	auto d = str;//自动推导d为自定义的Test01类型；
}
/*
auto另一个重要的作用就是方便迭代器遍历 
- 用auto自动推导为vector<int>的迭代器类型
*/ 
void TestAuto02(const vector<int> &v){
    // before 
    for(vector<int>::const_iterator it = v.begin(); it != v.end(); ++it){
        cout << *it;
    } cout << endl; 

    // after C++ 11 
    for(auto it = v.begin(); it != v.end(); ++it){ // 自动推导为 std::vector<int>::const_iterator
        cout << *it;
    } cout << endl;
}

/*
auto作为函数返回类型推导 
*/
auto TestAuto03(int i){ 
	//如果函数实现中含有多个return语句，这些表达式必须可以推断为相同的类型；

	//如果return语句返回初始化列表，返回值类型推导也会失败；
	//return { 1, 2, 3 }; // error

	//如果函数是虚函数，不能使用返回值类型推导；
	/*virtual auto func() 
	{ 
		return 1; 
	}*/


    //返回类型推导可以用在递归函数中，但是递归调用必须以至少一个返回语句作为先导；
	if (i == 1)
	{
		return i;  // return int
	}
	else
	{
		return TestAuto03(i - 1) + i; // ok
	}	
}

/* 2. decltype使用 ------------------------------------------------------------------------------------*/ 
/*
decltype类似auto的反函数，auto可以声明一个变量，而decltype可以从一个变量或表达式中得到其类型，再定义其他变量；
*/
enum //匿名枚举变量
{
	OK = 0,
	ERROR = 1
} flag;   

void TestDecltype01(){
    int i; 
    decltype(i) j = 0; //decltype(i)就是从i获取到i的类型为int，然后用这个类型定义变量j； 
    cout << typeid(j).name() << endl;//输出int，也就是j的类型也是int，是从i获取的；
	cout << typeid(j).hash_code() << endl; 

    float a;
	double b;
	decltype(a + b)c; // double  
	cout << typeid(c).name() << endl;//输出double 

    vector<int> tmp; 
    decltype(tmp.begin()) k; // std::vector<int>::iterator 
    for(k=tmp.begin(); k!=tmp.end(); k++){ tmp.push_back(1); } 
    
    decltype(flag) flag2;//可以用decltype获取到类型，再定义其他变量；
	cout << typeid(flag2).name() << endl;
	cout << typeid(flag2).hash_code() << endl;
    
    flag2 = OK; 
    cout << flag2 << endl; 
}

/* 3. 模板+Auto+decltype实现返回类型追踪 ----------------------------------------------------------------------*/ 
// t2和t2类型是不确定的，是泛型的，所以要用decltype来指定类型，用auto自动推导；
template <class T1, class T2> 
auto mul(const T1 &t1, const T2 &t2)->decltype(t1 * t2) //返回类型为t1*t2的类型
{   
	return t1 * t2; 
} 

void TestAutoDecl01(){
    auto m = 8; 
    auto n = 12.6; 
    auto k = mul(m,n); //返回类型为int*double -> double  
    cout << "k=" << "typeid=" << typeid(k).name() << endl;  // k=typeid=d
}

/* 4. 初始化列表和成员的新方式 ------------------------------------------------------- ------------------*/  
/*
  用{}的方式赋值就叫列表初始化
*/

class A{
    public: 
        int m_a; 
        int m_b; 

        // 直接赋值初始化，不依赖构造
        int m_c{1};  
        string m_name{"Tom"};  

    public:  
        // 初始化列表， 等价于有参构造
        A(int a, int b):m_a(a), m_b(b){};  

        // 默认构造的初始化
        A(): m_a(1), m_b(2){};  

        void print(){
            cout << "m_a:" << m_a << " |m_b:" << m_b << endl; 
        }
}; 

struct Test04_01{
    int a; 
    int b; 
    string name;  
};

void TestListInit(){
    Test04_01 test={1, 2, "string"};  //用{}的方式赋值就叫列表初始化 
    int arr2[]{ 1, 2, 3, 4 }; //列表初始化  
    int arr3[] = {1,2,3}; //传统写法  
    vector<int> arr4{ 1, 2, 3 }; //列表初始化  
}  

/* 5. 基于范围的for循环 ------------------------------------------------------- ------------------*/  
template<class T>
void func05_01(T &a)// 原写法func05_01(int *a)是把数组a的元素地址传入，形参中的数组是指针变量，不是数组，无法确定元素个数
{
	for (auto temp : a)//基于范围的for循环，数组的范围需要是确定的；改成模板后可以使用；
	{
		cout << temp << " ";
	}
	cout << endl;
}

void test05AutoFor()
{
	int a[]{ 1,2,3,4,5 };
	int len = sizeof(a) / sizeof(a[0]);

    //#if 0
	for (int i = 0; i < len; i++)//传统写法
	{
		int temp = a[i];
		temp *= 2;
		cout << temp << " ";
	}
	cout << endl;

	for (auto temp : a) //等价于上述写法
	{
		temp *= 2;
		cout << temp << " ";
	}
	cout << endl;
    
    //#endif //条件编译

	for (int i = 0; i < len; i++)//传统写法
	{
		int &temp = a[i]; //引用，可以改数组元素的值
		temp *= 2;
		cout << temp << " ";
	}
	cout << endl;

	for (auto &temp : a) //引用
	{
		temp *= 2;
		cout << temp << " ";
	}
	cout << endl;

	//基于范围的for循环，数组的范围需要是确定的
	func05_01(a);//把数组a的元素地址传入
}

/* 6. 静态断言 -----------------------------------------------------------------------------------------------*/ 
/*
C++提供了调试工具assert，是一个宏，用于在运行阶段对断言进行检查，如果条件为真，执行程序，否则调用abort()； 
--------------------------------
C++11新增了static_assert，静态断言
    - 不用等到运行阶段检查，在编译阶段就检查，可以更早报告错误，同时减少运行时的开销；
*/

void assertTest(){
    bool flat = true; 
    assert(flag==false);  //断言，如果flag == true，就继续往下执行；否则中断，提示错误
    cout << "hello!" << endl;  
} 

void staticAssertTest(){ 
    //静态断主语法：static_assert(条件(常量表达式), "提示的字符串"); //因为是编译阶段就检查，所以条件是常量，不能是变量；
    static_assert(sizeof(void *) == 8, "32位系统不支持");  //  "message": "static assertion failed: 64位系统不支持",
    cout << "Hello C++11" << endl;  

    const int a = 1001; // 常量表达式  
    static_assert(a == 1001, "a != 1001"); 
    cout << "Hello  static assert!" << endl; 
}

int main(){
    vector<int> testAuto = {1,2,3,4,5};
    // TestAuto02(testAuto); 

    // auto arr[] = {1,2,3};  error!  

    // TestDecltype01(); 

    // TestAutoDecl01(); 

    // A a;   
    // a.print(); 
    // A b(11,22);
    // b.print();


    // test05AutoFor();  
    // assertTest();
    staticAssertTest();
    return 0;  
}

