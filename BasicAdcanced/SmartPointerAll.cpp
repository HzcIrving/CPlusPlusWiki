/*
在 `PointerAll.cpp` demo07()中，可以看到每一次赋值，引用计数都加一，最后每次析构一次后引用计数减一，知道引用计数为 0，才真正释放资源。
要写出一个正确的管理资源的包装类还是蛮难的，比如上面那个例子就不是线程安全的，只能属于一个玩具，在实际工程中简直没法用。 

[Smart Pointer 智能指针知识点]  
1. C++11 中引入了智能指针（Smart Pointer），它利用了一种叫做 RAII（资源获取即初始化）的技术将普通的指针封装为一个栈对象。 

2. 当栈对象的生存周期结束后，会在析构函数中释放掉申请的内存，从而防止内存泄漏。这使得智能指针实质是一个对象，行为表现的却像一个指针。 

3. 智能指针主要分为shared_ptr、unique_ptr和weak_ptr三种，使用时需要引用头文件<memory>。

4. 而 C++11 中shared_ptr和weak_ptr都是参考boost库实现的。  

[总结] 
使用智能指针虽然能够解决内存泄漏问题，但是也付出了一定的代价。以shared_ptr举例：

- shared_ptr的大小是原始指针的两倍，因为它的内部有一个原始指针指向资源，同时有个指针指向引用计数。
- 引用计数的内存必须动态分配。虽然一点可以使用make_shared()来避免，但也存在一些情况下不能够使用make_shared()。
- 增加和减小引用计数必须是原子操作，因为可能会有读写操作在不同的线程中同时发生。比如在一个线程里有一个指向一块资源的shared_ptr可能调用了析构（因此所指向的资源的引用计数减一），同时，在另一线程里，指向相同对象的一个shared_ptr可能执行了拷贝操作（因此，引用计数加一）。原子操作一般会比非原子操作慢。但是为了线程安全，又不得不这么做，这就给单线程使用环境带来了不必要的困扰。 

我觉得还是分场合吧，看应用场景来进行权衡，我也没啥经验，但我感觉安全更重要，现在硬件已经足够快了，其他例如java这种支持垃圾回收的语言不还是用的很好吗。
*/  
#include <string> 
#include <iostream> 
#include <memory> 
using namespace std;

/*[Shared_ptr共享智能指针]
1) 初始化   
最安全的分配和使用动态内存的方法是调用一个名为 make_shared 的标准库函数。
此函数在动态内存中分配一个对象并初始化它，返回指向此对象的 shared_ptr。
与智能指针一样，make_shared 也定义在头文件 memory 中。  
    // 指向一个值为42的int的shared_ptr
    shared_ptr<int> p3 = make_shared<int>(42);

    // p4 指向一个值为"9999999999"的string
    shared_ptr<string> p4 = make_shared<string>(10,'9');

    // p5指向一个值初始化的int
    shared_ptr<int> p5 = make_shared<int>(); 

2) new返回指针来初始化智能指针 
还可以用 new 返回的指针来初始化智能指针，不过接受指针参数的智能指针构造函数是 explicit 的。 
因此，我们不能将一个内置指针隐式转换为一个智能指针，必须使用直接初始化形式来初始化一个智能指针： 
    // shared_ptr<int> pi = new int (1024); // 错误：必须使用直接初始化形式
    // shared_ptr<int> p2(new int(1024));	// 正确：使用了直接初始化形式  

3) 一个返回 shared_ptr 的函数不能在其返回语句中隐式转换一个普通指针
shared_ptr<int> clone(int p)
{
    return new int(p); // 错误：隐式转换为 shared_ptr<int>
} 

4) 常见操作  
 - make_shared<T>(args) 返回一个shared_ptr，指向动态分配类型为T的对象，使用args初始化 
 - shared_ptr<T> p(q) // p是shared_ptr q的拷贝；此操作会递增q中的引用计数。q中的指针必须能转换成T* 
 - p = q // p和q都是shared_ptr，所保存的指针必须能相互转换。此操作会递减p中的引用计数，递增q中的引用计数。若p中的引用计数变为0，则将其管理的原内存释放 
 - p.unique() // 若p.use_count()为1，返回true；否则返回false
 - p.use_count() // 返回与p共享对象的智能指针数量；可能很慢，主要用于调试 

 - 改变shared_ptr的其他方法
    p.reset() //若p是唯一指向其对象的shared_ptr，reset会释放此对象。
    p.reset(q) //若传递了可选的参数内置指针q，会令P指向q，否则会将P置为空。
    p.reset(q, d) //若还传递了参数d,将会调用d而不是delete 来释放q 
*/ 
class SharePTRTest{
public: 
    SharePTRTest(){
        cout << "SharePTRTest构造函数" << endl; 
    } 

    ~SharePTRTest(){
        cout << "SharePTRTest析构函数" << endl; 
    } 
}; 

void demo01(){
    std::shared_ptr<SharePTRTest> p1 = std::make_shared<SharePTRTest>();   // std::make_shared里面调用了 new 操作符分配内存；
    std::cout << "1 Ref: " <<  p1.use_count() << std::endl; 
    {
        std::shared_ptr<SharePTRTest> p2 = p1;  
        std::cout << "2 Ref: " << p2.use_count() << std::endl; //类似于前面的m_used 
    } // 增加了引用对象 p2，而随着大括号的结束，p2 的作用域结束，所以 p1 的引用计数变回 1
    std::cout << "3 ref: " << p1.use_count() << std::endl;  // main 函数的结束，p1 的作用域结束，此时检测到计数为 1，那就会在销毁 p1 的同时，调用 p1 的析构函数 delete 掉之前分配的内存空间；
}  //

/*
shared_ptr的循环陷阱 --- 内存泄漏
*/
class Parent;  // Parent类的前置声明
class Child {
public:
    Child() { std::cout << "hello child" << std::endl; }
    ~Child() { std::cout << "bye child" << std::endl; }

    std::shared_ptr<Parent> father;
};
class Parent {
public:
    Parent() { std::cout << "hello Parent" << std::endl; }
    ~Parent() { std::cout << "bye parent" << std::endl; }

    std::shared_ptr<Child> son;
};

void testParentAndChild() {
    std::shared_ptr<Parent> parent(new Parent());  // 1  资源A
    std::shared_ptr<Child> child(new Child());  // 2   资源B
    parent->son = child;     // 3   child.use_count() == 2 and parent.use_count() == 1  是一个智能指针的赋值操作
    child->father = parent;  // 4   child.use_count() == 2 and parent.use_count() == 2  同理，执行完语句4，资源A的引用计数也变成了2

    // 析构时，先回析构指针child，此时B变成1， 再析构parent，资源A变成1，此时count都不为0, 这种情况就是个死循环: 
    // 如果资源A的引用计数想变成0，则必须资源B先析构掉（从而析构掉内部管理资源A的共享智能指针），资源B的引用计数想变为0，又得依赖资源A的析构，这样就陷入了一个死循环。

} 

/*
要想解决上面循环引用的问题，只能引入新的智能指针std::weak_ptr。std::weak_ptr有什么特点呢？与std::shared_ptr最大的差别是
--- 在赋值的时候，不会引起智能指针计数增加。 

weak_ptr被设计为与shared_ptr共同工作，可以从一个shared_ptr或者另一个weak_ptr对象构造，获得资源的观测权。
但weak_ptr没有共享资源，它的构造不会引起指针引用计数的增加。 

同样，在weak_ptr析构时也不会导致引用计数的减少，它只是一个静静地观察者。
weak_ptr没有重载operator*和->，这是特意的，因为它不共享指针，不能操作资源，这是它弱的原因。  

如要操作资源，则必须使用一个非常重要的成员函数lock()从被观测的shared_ptr获得一个可用的shared_ptr对象，从而操作资源。

1. 当我们创建一个weak_ptr时，要用一个shared_ptr来初始化它： 
auto p = make_shared<int>(42);
weak_ptr<int> wp(p); // wp弱共享p; p的引用计数未改变  

2. 常用操作 
weak_ptr<T> w;	// 空weak_ptr可以指向类型为T的对象
weak_ptr<T> w(shared_ptr p);	// 与p指向相同对象的weak_ptr, T必须能转换为shared_ptr指向的类型
w = p;	// p可以是shared_ptr或者weak_ptr，赋值后w和p共享对象
w.reset();	// weak_ptr置为空
w.use_count();	// 与w共享对象的shared_ptr的计数
w.expired();	// w.use_count()为0则返回true，否则返回false
w.lock();	// w.expired()为true，返回空的shared_ptr; 否则返回指向w的shared_ptr 

*/
class ParentWeak;  // Parent类的前置声明

class ChildWeak {
public:
    ChildWeak() { std::cout << "hello child" << std::endl; }
    ~ChildWeak() { std::cout << "bye child" << std::endl; }

    // 测试函数
    void testWork()
    {
        std::cout << "testWork()" << std::endl;
    }

    std::weak_ptr<ParentWeak> father;
};

class ParentWeak {
public:
    ParentWeak() { std::cout << "hello Parent" << std::endl; }
    ~ParentWeak() { std::cout << "bye parent" << std::endl; }

    std::weak_ptr<ChildWeak> son;
};

void testParentAndChild_Weak() {
    std::shared_ptr<ParentWeak> parent(new ParentWeak());
    std::shared_ptr<ChildWeak> child(new ChildWeak());
    parent->son = child;
    child->father = parent;
    std::cout << "parent_ref:" << parent.use_count() << std::endl;  // 1
    std::cout << "child_ref:" << child.use_count() << std::endl;  // 1 

    // 把std::weak_ptr类型转换成std::shared_ptr类型，以调用内部成员函数
    std::shared_ptr<ChildWeak> tmp = parent.get()->son.lock();
    tmp->testWork();
    std::cout << "tmp_ref:" << tmp.use_count() << std::endl; // 2 

    // 由以上代码运行结果我们可以看到：

    // 所有的对象最后都能正常释放，不会存在上一个例子中的内存没有释放的问题;
    //parent 和 child 在 main 函数中退出前，引用计数均为 1，也就是说，对 --- std::weak_ptr的相互引用，不会导致计数的增加。
}


/*
unique_ptr独占的智能指针

1. unique_ptr的基本使用
unique_ptr相对于其他两个智能指针更加简单，它和shared_ptr使用差不多，但是功能更为单一，它是一个独占型的智能指针:
 - 不允许其他的智能指针共享其内部的指针，更像原生的指针（但更为安全，能够自己释放内存）。
 - 不允许赋值和拷贝操作，只能够移动。 
 std::unique_ptr<int> ptr1(new int(0));
 std::unique_ptr<int> ptr2 = ptr1; // 错误，不能复制 ERROR !!!
 std::unique_ptr<int> ptr3 = std::move(ptr1); // 可以移动 

2. 在 C++11 中，没有类似std::make_shared的初始化方法，但是在 C++14 中，对于std::unique_ptr引入了std::make_unique方法进行初始化。 

3. unique_ptr常有操作 
unique_ptr<T> u1 // 空unique_ptr，可以指向类型为T的对象。u1会使用delete来释放它的指针
unique_ptr<T, D> u2 // u2会使用一个类型为D的可调用对象来释放它的指针
unique_ptr<T, D> u(d) // 空unique_ptr，指向类型为T的对象，用类型为D的对象d替代delete
u = nullptr // 释放u指向的对象，将u置为空
u.release() // u放弃对指针的控制权，返回指针，并将u置为空
u.reset() // 释放u指向的对象
u.reset(q) // 如果提供了内置指针q，另u指向这个对象；否则将u置为空
u.reset(nullptr)    

4. 调用 release 会切断unique_ptr和它原来管理的对象间的联系，如果我们不用另一个智能指针来保存 release 返回的指针，我们的程序就要负责资源的释放： 
p2.release(); // 错误：p2不会释放内存，而且我们丢失了指针
auto p = p2.release(); // 正确，但我们必须记得 delete(p)
delete(p); 

5. 传递unique_ptr参数和返回unique_ptr
不能拷贝 unique_ptr 的规则有一个例外：我们可以拷贝或赋值一个将要被销毁的 unique_ptr。
常见的例子是从函数返回一个unique_ptr： 
unique_ptr<int> clone (int p) 
{
	unique_ptr<int> ret(new int (p));
	// ...
    return ret;
}

*/ 

void testUniquePtr(){
    unique_ptr<string> ptr1(new string("unique_ptr"));
    cout << "ptr1 is " << *ptr1 << endl; 

    unique_ptr<string> ptr2 = make_unique<string>("Make Unique init!!");
    cout << "ptr2 is" << *ptr2 << endl;  

    // 虽然我们不能拷贝或赋值unique_ptr，但可以通过调用 release 或 reset 将指针的所有权从一个（非const）unique_ptr转移给另一个unique_ptr： 
    unique_ptr<string> ptr3(new string("AAAAA")); 
    // 改变所有权，从ptr3转移给ptr4  
    // unique_ptr<string> ptr4(ptr3, release()); // release 将 p1 置为空  
    unique_ptr<string> p3(new string("Trex")); 
    // 将所有权从p3转移给ptr3
    ptr3.reset(p3.release()); // reset 释放了 p2 原来指向的内存
}


int main(){
    // demo01(); 
    // testParentAndChild(); // shared_ptr管理资源，没有调用 Parent 和 Child 的析构函数，表示资源最后还是没有释放！内存泄漏还是发生了。 
    testParentAndChild_Weak(); 

    testUniquePtr();


    return 0; 
}

 


