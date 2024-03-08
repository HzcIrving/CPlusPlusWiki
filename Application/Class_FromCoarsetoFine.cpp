#include <iostream> 
using namespace std; 

/*
1. 数据隐藏是面向对象编程的一个重要特点 
2. 防止函数直接访问类类型的内部成员 
3. 类成员的访问限制是通过在类主体内部对各个区域标记 public、private、protected 来指定的
4. 关键字 public、private、protected 称为访问说明符  

5. public 公有成员  
-- 程序中类的外部是可访问的。
-- 您可以不使用任何成员函数来设置和获取公有变量的值 

6. private 私有成员 
-- 私有成员变量或函数在类的外部是不可访问的，甚至是不可查看的。 
-- 只有 【类】 和 【友元函数】 可以访问私有成员。 
-- 默认情况下，类的所有成员都是私有的。 

7. protected 保护成员 
-- 保护成员变量或函数与私有成员十分相似，但有一点不同，保护成员在【派生类（即子类）】中是可访问的。 

8. friend 友元  
-- 友元可以是一个函数，该函数被称为友元函数；友元也可以是一个类，该类被称为友元类，在这种情况下，整个类及其所有成员都是友元。 
-- 类的友元函数是定义在类外部，但有权访问类的所有私有（private）成员和保护（protected）成员。
-- 尽管友元函数的原型有在类的定义中出现过，但是友元函数并不是成员函数。 
-- 如果要声明函数为一个类的友元，需要在类定义中该函数原型前使用关键字 friend
*/

class ClassPublicPrivateProtected{ 
    public: 
        double length; 
        void setLength(double len); 
        void setWidth(double wid);  
        double getLength(void);   
        double getWidth(void);  

        // 找到自己的友元，可以访问自己所有的成员 
        // 1) 构造函数，初始化属性 
        // ClassPublicPrivateProtected(double h, double w, double l); 
        // friend void printBoxInfo(double h,double w,double l);  

        // 找到自己的友元类 
        friend class BoxFriend; 

    private: // 默认都是private  
        double width; 

    protected: 
        // double width_pro;  
        double height;  // length * width * height  
}; 


// 成员函数 --- 访问public成员 
double ClassPublicPrivateProtected::getLength(void){
    return length; 
} 

void ClassPublicPrivateProtected::setLength(double len){
    length = len; 
}  

// 成员函数 --- 访问private成员  
double ClassPublicPrivateProtected::getWidth(void){
    return width;
} 

void ClassPublicPrivateProtected::setWidth(double wid){
    width = wid; 
}

// 派生类 --- 可以访问protected  
class Box:ClassPublicPrivateProtected{
    public: 
        double getVolume(double l, double h, double w); 
};

double Box::getVolume(double l, double h, double w){   
    length = l; 
    height = h;

    // width = w; // 不可以直接访问私有成员
    double wid = Box::getWidth();  
    return length * w * height; 
}

class Box1{ 
    public: 
        double length; 
        
        // 找到自己的友元，可以访问自己所有的成员 
        // 1) 构造函数，初始化属性 
        Box1(double h, double w, double l);  
        ~Box1(); 

        friend void printBoxInfo(Box1 box);  

        // 找到自己的友元类 
        friend class BoxFriend; 

    private: // 默认都是private  
        double width; 

    protected: 
        // double width_pro;  
        double height;  // length * width * height  
}; 
// 构造函数 --- 初始化属性 
Box1::Box1(double h, double w, double l){
    length = l; 
    width = w; 
    height = h; 
}
 
Box1::~Box1(){
    cout << "友元教程结束..." << endl; 

}
// 友元函数，可以访问所有 
void printBoxInfo(Box1 box){
    cout << "Box Info:" << " h:" << box.height << " w:" << box.width << " l:" << box.length << endl; 
}

// 程序的主函数
int main( )
{
   ClassPublicPrivateProtected line;
 
   // 设置长度
   line.setLength(6.0); 
   cout << "Length of line : " << line.getLength() <<endl;
 
   // 不使用成员函数设置长度
   line.length = 10.0; // OK: 因为 length 是公有的
   cout << "Length of line : " << line.length <<endl;
   
   ClassPublicPrivateProtected box; 
   // 不使用成员函数设置长度
   box.length = 10.0; // OK: 因为 length 是公有的
   cout << "Length of box : " << box.length <<endl;
 
   // 不使用成员函数设置宽度
   // !!! box.width = 10.0; // Error: 因为 width 是私有的，不可以直接赋值 
   box.setWidth(10.0);  // 使用成员函数设置宽度 
   cout << "Width of box : " << box.getWidth() <<endl;
   
   // 派生类访问double 
   Box mybox; 
   // 设置私有成员 
   cout << "Volumn of my box: " << mybox.getVolume(10.0,10.0,10.0) << endl;  

   // 友元访问所有成员 
   Box1 boxBro1(10.0, 6.0, 8.0);  
   printBoxInfo(boxBro1); 

   return 0; 

}