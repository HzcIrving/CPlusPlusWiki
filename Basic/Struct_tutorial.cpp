/*
结构体/结构
- 结构是 C++ 中另一种用户自定义的可用的数据类型 
- 允许您存储不同类型的数据项 

结构用于表示一条记录，假设您想要跟踪图书馆中书本的动态，您可能需要跟踪每本书的下列属性： 
    Title
    Author
    Subject
    Book ID 

1. 结构的定义，需要使用struct语句。
   struct [structure tag] {
        member definition; 
        member definition; 
        ... 
        member definition; 
   }[one or more structure vars]  

2.  定义一个指针，指向 Book2  
    指向该结构的指针访问结构的成员，您必须使用 -> 运算符
    struct Books *bookptr;  

3.  typedef关键字 
    更简单的定义结构的方式，您可以为创建的类型取一个"别名"。 
    typedef struct
    {
    char  title[50];
    char  author[50];
    char  subject[100];
    int   book_id;
    }Books;

案例：将结构作为函数传参 
*/  
#include <iostream> 
#include <cstring> 
using namespace std;  

struct Books{
    char title[50]; 
    char author[50];
    char subject[100];
    int book_id;
}; 

// 别名 
typedef struct{
    char title[50]; 
    char author[50];
    char subject[100];
    int book_id;
} Bookss;  

void printBook_Info(struct Books book); 
void printBook_Info_ptr(struct Books *book);  
void printBook_Info_typedef(Bookss book);

int main(){
    struct Books Book1;        // 声明 Book1，类型为 Book
    struct Books Book2;        // 声明 Book2，类型为 Book 
    Bookss Book3;  // typedef别名，可以直接用Books2来声明变量 

    // 定义一个指针，指向 Book2  
    // 指向该结构的指针访问结构的成员，您必须使用 -> 运算符
    struct Books *bookptr; 
 
    // Book1 详述 
    // strcpy 这个函数将一个字符串复制到另一个字符串。
    strcpy( Book1.title, "Learn C++ Programming");
    strcpy( Book1.author, "Chand Miyan"); 
    strcpy( Book1.subject, "C++ Programming");
    Book1.book_id = 6495407;

    // Book2 详述
    strcpy( Book2.title, "Telecom Billing");
    strcpy( Book2.author, "Yakit Singha");
    strcpy( Book2.subject, "Telecom");
    Book2.book_id = 6495700; 

    // Book3 详述
    strcpy( Book3.title, "Telecom Billing");
    strcpy( Book3.author, "Yakit Singha");
    strcpy( Book3.subject, "Telecom2");
    Book3.book_id = 6495710;
 
    // 输出 Book1 信息
    printBook_Info( Book1 );

    // 输出 Book2 信息
    printBook_Info( Book2 ); 

    // 输出指针指向  
    bookptr = &Book1;
    printBook_Info_ptr(bookptr); 

    // 起别名 
    printBook_Info_typedef(Book3);

    return 0;
}


void printBook_Info(struct Books book){
    cout << "Book title : " << book.title << endl;
    cout << "Book author : " << book.author << endl;
    cout << "Book subject : " << book.subject << endl;
    cout << "Book id : " << book.book_id << endl;
}

void printBook_Info_ptr(struct Books *book){
    cout << "Book title : " << book->title << endl;
    cout << "Book author : " << book->author << endl;
    cout << "Book subject : " << book->subject << endl;
    cout << "Book id : " << book->book_id << endl;
}

void printBook_Info_typedef(Bookss book){
    cout << "Book title : " << book.title << endl;
    cout << "Book author : " << book.author << endl;
    cout << "Book subject : " << book.subject << endl;
    cout << "Book id : " << book.book_id << endl;
}
