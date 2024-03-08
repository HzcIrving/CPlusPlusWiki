/*
Map & Multi-map  
1. map中所有元素都是pair
2. pair中第一个元素为key（键值），起到索引作用，第二个元素为value（实值）
3. 所有元素都会根据元素的键值自动排序 

map/multimap属于关联式容器，底层结构是二叉树 

- 可以根据key值快速找到value值 O(1)时间复杂度，类似于Hash 

Map vs. Multi-map 
- map不允许容器中有重复key值元素
- multimap允许容器中有重复key值元素

*/ 


#include <string> 
#include <iostream> 
#include <map> 
using namespace std; 

// template <class T> 
// void printMap(map<int, T> &m){
//     for (map<int, T>::iterator it = m.begin(); it!=m.end(); it++){
//         cout << "[key = " << it->first << "value = " << it->second << " ]"; 
//     }
//     cout << endl; 
// } 

void printMap(map<int, int> &m){
    for (map<int, int>::iterator it = m.begin(); it!=m.end(); it++){
        cout << "[key = " << it->first << "value = " << it->second << " ]"; 
    }
    cout << endl; 
} 

void printMap(map<int, string> &m){
    for (map<int, string>::iterator it = m.begin(); it!=m.end(); it++){
        cout << "[key = " << it->first << "value = " << it->second << " ]"; 
    }
    cout << endl; 
}  

void printMap(multimap<int, int> &m){
    for (multimap<int, int>::iterator it = m.begin(); it!=m.end(); it++){
        cout << "[key = " << it->first << "value = " << it->second << " ]"; 
    }
    cout << endl; 
} 

void emptyCheck(map<int,int> &m1){
    if (m1.empty())
    {
    cout << "m为空" << endl;
    }
    else
    {
    cout << "m不为空" << endl;
    cout << "m的大小为： " << m1.size() << endl;
    } 
}
/*
Test01 - 构造 & 赋值 
    map<T1, T2> mp; //map默认构造函数:
    map(const map &mp); //拷贝构造函数  
    map& operator=(const map &mp); //重载等号操作符
*/ 
void test01(){
    map<int, int> m1;  // 默认构造  
    // map中所有元素都是成对出现，插入数据时候要使用对组
    m1.insert(pair<int, int>(1, 10)); 
    m1.insert(pair<int, int>(2, 20));
    m1.insert(pair<int, int>(3, 30)); 
    printMap(m1); 

    map<int, int> m2(m1); // 拷贝构造 
    printMap(m2);   

    map<int, int> m3; 
    m3 = m1; // 赋值 
    printMap(m3);
    
} 

/*
Test02 - 统计map容器大小以及交换map容器 
    size(); //返回容器中元素的数目
    empty(); //判断容器是否为空
    swap(st); //交换两个集合容器
*/
void test02(){
    map<int, int> m1;
    for (int i=1; i<10; i++){
        m1.insert(pair<int, int>(i, i*10)); 
    }  

    map<int, int> m2; 
    for(int i=10; i>1; i--){
        m2.insert(pair<int, int>(i, i*10)); 
    }

    printMap(m1); 
    printMap(m2);

    cout << "交换后 ... " << endl; 
    m1.swap(m2); 
    printMap(m1);
    printMap(m2); 

    emptyCheck(m1); 
    m1.clear(); 
    // 清零后
    emptyCheck(m1);
} 

/*
Test03 - map容器进行插入数据和删除数据 
    insert(elem); //在容器中插入元素。
    clear(); //清除所有元素
    erase(pos); //删除pos迭代器所指的元素，返回下一个元素的迭代器。
    erase(beg, end); //删除区间[beg,end)的所有元素 ，返回下一个元素的迭代器。
    erase(key); //删除容器中值为key的元素。
*/ 
void InsertandErase(){
    map<int, string> m; 
    
    // 1.直接插入 
    m.insert(pair<int, string>(1, "insert"));

    // 2.make_pair接口
    m.insert(make_pair(2,"make_pair")); 

    // 3. value_type 
    m.insert(map<int,string>::value_type(3, "map<int,string>::value_type"));  

    // 4. 第四种 
    m[4] = "[]重载"; 
    printMap(m); 

    // 5. erase 1 -- 头删
    m.erase(m.begin()); 
    printMap(m); 

    // 6. erase 2 -- pos删除 
    m.erase(2); 
    printMap(m); 

    // 7. erase 3 -- 迭代器 
    m.erase(m.begin(), m.end()); 
    printMap(m);   
}

/*
Test04 - map容器进行查找和统计 
    find(key); //查找key是否存在,若存在，返回该键的元素的迭代器；若不存在，返回set.end();
    count(key); //统计key的元素个数
*/
void FindandCount(){
    map<int, int> m;  // 不允许重复元素 
    m.insert(pair<int, int>(1, 10));
    m.insert(pair<int, int>(2, 20));
    m.insert(pair<int, int>(3, 30)); 
    m.insert(pair<int, int>(3,200));  

    multimap<int, int> m1;  
    m1.insert(pair<int, int>(1, 10));
    m1.insert(pair<int, int>(2, 20));
    m1.insert(pair<int, int>(3, 30)); 
    m1.insert(pair<int, int>(3,200));   

    cout << "map:" << endl; 
    printMap(m); 
    cout << "multimap:" << endl; 
    printMap(m1); 

    // 查找
    map<int,int>::iterator pos = m.find(3); 

    if (pos != m.end())
    {
        cout << "找到了元素 key = " << (*pos).first << " value = " << (*pos).second << endl;
    }
    else
    {
        cout << "未找到元素" << endl;
    }    

    // 统计 
    int num = m.count(3); 
    cout << "map num = " << num << endl; 

    // 统计multimap 
    int num2 = m1.count(3); 
    cout << "multimap num = " << num2 << endl; 
}

/*
Test05 - 容器排序 
- map容器默认排序规则 -- 依据key值，从小到大 
- 利用仿函数，可以改变排序规则 

- 利用仿函数可以指定map容器的排序规则
- 对于自定义数据类型，map必须要指定排序规则,同set容器
*/
class MyCompare{
    public:
        bool operator()(int v1, int v2){
            return v1 > v2;  // True or False 
        }
}; 

void Sort(){
    //默认从小到大排序
    //利用仿函数实现从大到小排序
    map<int, int, MyCompare> m;
    m.insert(make_pair(1, 10));
    m.insert(make_pair(2, 20));
    m.insert(make_pair(3, 30));
    m.insert(make_pair(4, 40));
    m.insert(make_pair(5, 50)); 

    for (map<int, int, MyCompare>::iterator it = m.begin(); it!=m.end(); it++){
        cout << "key:" << it->first << " value:" << it->second << endl; // 从大到小
    }
}



int main(){
    // 1. 构造与赋值 
    // test01();  

    // 2. empty(), swap()
    // test02(); 

    // 3. insert & erase 
    // InsertandErase(); 

    // 4. find & count  
    // FindandCount(); 

    // 5. Sort 
    Sort();
    return 0; 
}