#include <iostream>
#include <unordered_map>  
#include <vector>
#include <memory> // 使用智能指针
#include <string>
#include <chrono> // 计算时间复杂度

using namespace std; 

/*
目标：
给定Target，一个数组
查看数组中是否存在两个数，其和为Target  

要求分别用暴力法和Hash法实现 
并计算时间复杂度  

要求使用工厂模式实现两种方法，根据用户的输入，选则暴力法或者Hash法，同时要考虑不同类型的实现（用模板）
*/

template <typename T> 
class BaseSearch{
    public: 
    virtual bool search(T target, pair<int, int> &indices) = 0; //纯虚函数  
    virtual ~BaseSearch(){}; // 这里析构的目的：为了防止内存泄漏，因为纯虚函数不能实例化对象，所以这里需要析构函数，否则会报错
}; 

// 产品1：暴力法
template <typename T> 
class BruteForceSearch : public BaseSearch<T> {
    public:
        BruteForceSearch(const vector<T>& data): _data(data) {}; // 构造函数,初始化_data 

        bool search(T target,  pair<int, int> &indices) override { // 重写search函数
            for(size_t i = 0; i<this->_data.size(); i++){
                for(size_t j = i+1; j<this->_data.size(); j++){
                    if(this->_data[i] + this->_data[j] == target){
                        indices = make_pair(static_cast<int>(i), static_cast<int>(j));
                        return true;
                    }
                }
            }
        return false;
        }

    private:
        vector<T> _data; 
};  

// 产品2：Hash法 
template <typename T>
class HashSearch: public BaseSearch<T> {
    public:
        HashSearch(const vector<T>& data): _data(data) {}; // 构造函数,初始化_data
        
        bool search(T target, pair<int, int> &indices) override { // 重写search函数
            unordered_map<T, int> hashTable; // Hash表，存储数组中的元素及其索引
            for(size_t i = 0; i < this->_data.size(); ++i){
                T num = _data[i]; 
                T res = target - num;  
                if (hashTable.find(res) != hashTable.end()){
                    indices = make_pair(static_cast<int>(hashTable[res]), static_cast<int>(i)); 
                    return true; 
                }
                hashTable[num] = i; 
            }
            return false; 
        }


    private:
        vector<T> _data;
}; 

template <typename T> 
class SolutionFactory{
    public: 
        static unique_ptr<BaseSearch<T>> createSearch(const string& methodType, const vector<T>& data){ 
            // 为什么用BaseSearch<T>* createSearch: 因为BaseSearch<T>是抽象类，不能实例化对象，所以要用指针
            if(methodType == "BruteForceSearch"){
                return make_unique<BruteForceSearch<T>>(data);
            } else if(methodType == "HashSearch"){
                return make_unique<HashSearch<T>>(data);
            } else {
                return nullptr; 
            }
        }
}; 

int main(){
    // 测试两种不同的搜索方法, 并比较时间 
    vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; 
    int target = 10; 
    string method; 
    pair<int, int> indices; 

    cout << "Enter method type (BruteForceSearch or HashSearch): " ; 
    cin >> method; 

    auto searchMethod = SolutionFactory<int>::createSearch(method, data);

    if (searchMethod){
        // 开始时间
        auto start = chrono::high_resolution_clock::now();

        if(searchMethod->search(target, indices)){ 
            // 结束时间
            auto endTime = chrono::high_resolution_clock::now();
            cout << "Found target " << target << " at indices " << indices.first << " and " << indices.second << endl;  
            cout << "Time taken: " << chrono::duration_cast<chrono::microseconds>(endTime - start).count() << " ms" << endl;
        } else {
            // 结束时间
            auto endTime = chrono::high_resolution_clock::now();
            cout << "Target " << target << " not found" << endl;  
            cout << "Time taken: " << chrono::duration_cast<chrono::microseconds>(endTime - start).count() << " ms" << endl;
        }
    }else{
        cout << "Invalid method type" << endl;
    } 

    return 0; 
}