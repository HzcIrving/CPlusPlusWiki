/*
总结了C++面试中最常考的<algorithm>包中的算法  
2024.03.10 
> https://mp.weixin.qq.com/s/JKAUneBFrlqel-6L6Yravw 
*/
#include <iostream>
#include <algorithm>  
#include <vector> 
#include <string> 

using namespace std;  

class Fibonacci{
    int f1; 
    int f2; 

public:
    Fibonacci(int start1, int start2) : f1(start1), f2(start2) {} 

    int operator()(){
        int r = f1 + f2; 
        f1 = f2; 
        f2 = r; 
        return r; 
    }
};

// 1. 填充类算法  
void FillTest(){ 
    // 1.1 fill 
    /*
    fill(begin, end, v)：填充某容器的值全为v  
    源码如下，非常简单有趣，把迭代器和值模板化，这样就使得fill可以应用在任意容器和任意类型的scalar  
    template< class ForwardIt, class T >
    void fill(ForwardIt first, ForwardIt last, const T& value)
    {
        for (; first != last; ++first) {
            *first = value;
        }
    }
    */
    vector<int> a(10); 
    fill(a.begin(), a.end(), 6);  
    for (auto & i : a){
        cout << i << " ";
    } cout << endl;  

    // 1.2 generate  
    /*
    generate(begin, end, func)/generate_n(begin, n, func) ：使用func生成数据填充到某容器的begin到end或者前n个位置中  
    generate/generate_n的源码也很有趣，很好理解，把迭代器和生成器通过模板泛化，这样就使得generate可以应用在任意容器和任意函数 
    
    template <class ForwardIterator, class Generator>
    void generate ( ForwardIterator first, ForwardIterator last, Generator gen )
    {
    while (first != last) {
        *first = gen(); //需要写一个gen() func的()重载函数 
        ++first;
    }
    }

    template <class ForwardIterator, class Generator>
    void generate_n ( ForwardIterator first, size n, Generator gen )
    {
    while (n>0) {
        *first = gen();
        ++first; --n;
    }
    }
    ----------------------------------------------
    案例: 以下根据斐波那契数列规则填充10个元素到vector
    */ 
    vector<int> b(10); 
    generate(b.begin(), b.end(), Fibonacci(0, 1));  
    for (auto & i : b){
        cout << i << " ";
    }cout << endl; 
}

// 2. 变换类算法 
void TransformTest(){ 
    // 2.1 transform 
    /*
    transform 简洁省事，支持unary和binary操作，并且支持inplace 
    当我们想要对某个容器做某种修改操作时，这可以替代掉很多繁重的for循环 
    
    // unary 操作 
    template <class InputIterator, class OutputIterator, class UnaryOperation>
    OutputIterator transform (InputIterator first1, InputIterator last1,
                                OutputIterator result, UnaryOperation op){
        while (first1 != last1) {
            *d_first++ = unary_op(*first1++);
        }
        return d_first;
    }  
    
    // binary 操作 
    template <class InputIterator1, class InputIterator2,
            class OutputIterator, class BinaryOperation>
    OutputIterator transform (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, OutputIterator result,
                                BinaryOperation binary_op){
    
        while (first1 != last1) {
            *d_first++ = binary_op(*first1++, *first2++);
        }
        return d_first;
    } 

    unary op 和 binary op 也可以是匿名函数 
    -------------------------------------
    1. unary 把每个字符都大写，并且大写后的结果原地保存在s  
    2. binary 把foo和bar两个vector相加结果保存在foo,结果为5个3 
    */ 
    string s("interesting"); 
    std::transform(s.begin(), s.end(), s.begin(), 
        [](unsigned char c){return std::toupper(c);} 
    ); 

    // 打印string 
    cout << s << endl;  

    vector<int> foo(5,1); 
    vector<int> bar(5,2);  
    std::transform(foo.begin(), foo.end(), bar.begin(), foo.begin(), 
        [](int a, int b){return a+b;});     // 33333
    // 替代 plus函数
    std::transform(foo.begin(), foo.end(), bar.begin(), foo.begin(), 
        std::plus<int>());  // 55555 

    // 打印结果 
    for(auto & i : foo){
        cout << i << " "; 
    }cout << endl;  
    
}

// 3. 区间最大最小值 
void MaxTest(){
    // max_element/ (iterator1/address, iterator2/address) 
    /*
    返回值：iterator或地址，加上解引用*即得最大最小值
    优点：当我们要求某个区间范围内的最大最小值或者最大最小值的index时, max_element和min_element直接传入这个区间的起始地址即可，会比循环max/min方便很多，尤其是数组是多维的时候。比如leetcode 120题的官方解法就用到了
    */ 
    int a[] = {1,2,3,4,5}; 
    int maxPosition = std::max_element(a, a+5) - a; // 最大值下标 左开右闭
    int maxVal = *std::max_element(a,a+5);   
    cout << maxPosition << endl; 
    cout << maxVal << endl;

    vector<int> n = {1,2,3,4}; 
    int minPosition = std::min_element(n.begin(), n.end()) - n.begin(); // 最小值下标 
    int minVal = *std::min_element(n.begin(), n.end());   
    cout << minPosition << endl; 
    cout << minVal << endl; 
} 

// 4. 复制函数  
void copyTest(){
    /*
    签名：copy(iterator1, iterator2, dst_iterator)
    类似函数：copy和memcpy都是copy，但是他们的最大区别是memcpy是byte by byte的copy，而copy是ele by ele的copy
             我们很多时候可能更多的是想做后者，但是却用成了前者，这也是很多memcpy相关bug的发生地
    例子：把a的三个元素从temp的首地址一直copy
    */ 
    std::vector<int> temp(3); 
    int a[3] = {1,2,3}; 
    std::copy(a, a+3, temp.begin());    

    for(auto & i : temp){
        cout << i << " "; 
    } cout << endl; 
}

int main(){
    // 1. fillTest 
    FillTest(); 

    // 2. tranformTest 
    TransformTest(); 

    // 3. min/maxTest 
    MaxTest(); 

    // 4. copyTest 
    copyTest();
}
