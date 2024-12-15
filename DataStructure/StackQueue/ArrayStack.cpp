#include <iostream> 
#include <vector>  
using namespace std;  

/*
使用数组实现栈时，我们可以将数组的尾部作为栈顶 
*/
class ArrayStack{
    public:
        ArrayStack(){} 

        // 默认构造 
        // ArrayStack(int capacity){
        //     data.resize(capacity);
        // }

        // 拷贝构造
        ArrayStack(const ArrayStack& other){
            data = other.data;
        }

        // 析构函数
        ~ArrayStack(){}   

        // getSize 
        int getSize(){
            return data.size();
        } 

        // 判空 
        bool isEmpty(){
            return data.empty();
        }

        // 入栈 
        void push(int num){
            data.push_back(num); 
        } 

        // 出栈 
        int pop(){
            /*
            底        顶 
            [a, b,  <<<] 
            [a, b,  >>>] 
            */
           int num = this->top(); 
           data.pop_back(); 
           return num; 
        } 

        // peek 
        int top(){ 
            if(this->isEmpty()){
                throw out_of_range("Stack is empty");
            }
            return data.back();
        } 

        // 打印数据
        void print(){
            // auto
            cout << "[";
            for(auto i : data){
                // 最后一个不打印
                if (i == data.back()){
                    cout << i;
                }else{
                    cout << i << ","; 
                }
            }
            cout << "]";
            cout << endl;
        }

    private:
        vector<int> data; // 数据 
};

/*类模板*/ 
template <typename T>
class ArrayStack2 {
public:
    ArrayStack2() {}

    ArrayStack2(const ArrayStack& other) {
        data = other.data;
    }

    ~ArrayStack2() {}

    int getSize() {
        return data.size();
    }

    bool isEmpty() {
        return data.empty();
    }

    void push(const T& element) {
        data.push_back(element);
    }

    T pop() {
        T element = this->top();
        data.pop_back();
        return element;
    }

    T top() {
        if (this->isEmpty()) {
            throw out_of_range("Stack is empty");
        }
        return data.back();
    }

    void print() {
        cout << "[";
        for (typename vector<T>::iterator it = data.begin(); it != data.end(); ++it) {
            if (it != data.begin()) {
                cout << ",";
            }
            cout << *it;
        }
        cout << "]";
        cout << endl;
    }

private:
    vector<T> data;
};

int main(){
    ArrayStack stack; 
    stack.push(1);
    // stack.push(2); 

    stack.print();
    cout << stack.pop() << endl;
    cout << stack.getSize() << endl; 
    cout << stack.isEmpty() << endl; 
    // cout << stack.top() << endl; 

    ArrayStack2<string> stringStack;
    stringStack.push("Hello");
    stringStack.push("World");
    stringStack.print();
    cout << stringStack.pop() << endl;
    cout << stringStack.getSize() << endl;
    cout << stringStack.isEmpty() << endl;

    return 0; 
}