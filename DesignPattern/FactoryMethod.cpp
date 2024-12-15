#include <iostream> 
#include <memory>  
#include <string> 
#include <list>  

using namespace std; 

/* 
Demo 01 简单的工厂模式（Factory Pattern） 
*/ 
class Product {
public:
    virtual ~Product() {}   // 是一个虚析构函数，确保通过基类指针删除派生类对象时，能够正确调用派生类的析构函数。
    virtual void operation() = 0;  // 纯虚函数，派生类必须实现
};   

class ProductA: public Product{ 
public: 
    void operation() override{
        cout << "制造A产品中 ..." << endl; 
    }
}; 

class ProductB: public Product{ 
public: 
    void operation() override{
        cout << "制造B产品中 ..." << endl; 
    }
}; 

class Factory {
public: 
    virtual ~Factory() {} // 是一个虚析构函数，确保通过基类指针删除派生类对象时，能够正确调用派生类的析构函数。
    // virtual Product* createProduct() = 0; // 纯虚函数，派生类必须实现  
    virtual std::unique_ptr<Product> createProduct() = 0; // 纯虚函数，派生类必须实现
};  

// A工厂 制造A产品
class FactoryA : public Factory {
public:
    std::unique_ptr<Product> createProduct() override {
        return std::make_unique<ProductA>();
    }
};

// B工厂 制造B产品
class FactoryB : public Factory {
public:
    std::unique_ptr<Product> createProduct() override {
        return std::make_unique<ProductB>();
    }
};   


/*
Demo 02  
通过工厂模式来创建不同类型文档的页面。 
需求：客户端代码可以创建不同类型的文档，而无需了解这些文档的具体实现细节  

1) 定义了一个抽象的产品接口Page，以及多个具体的产品类（如SkillsPage、EducationPage等），这些产品类都实现了Page接口 
2) 定义了一个抽象的工厂类Document，以及两个具体的工厂类Resume和Report，这些工厂类都实现了Document类。
*/ 

//Abstract Product
class Page
{
public:
    virtual ~Page() {}; 
    virtual string GetPageName(void) = 0;
}; 

//Concrete Product --- return string 
class SkillsPage : public Page
{
public:
    string GetPageName(void) override
    {
        return "SkillsPage";
    }
}; 

//Concrete Product
class EducationPage : public Page
{
public:
    string GetPageName(void) override
    {
        return "EducationPage";
    }
}; 

//Concrete Product
class ExperiencePage : public Page
{
public:
    string GetPageName(void) override
    {
        return "ExperiencePage";
    }
};

//Concrete Product
class IntroductionPage : public Page
{
public:
    string GetPageName(void) override 
    {
        return "IntroductionPage";
    }
};
 
// Abstract Factory 
class Document{
public: 
    virtual ~Document() {}; // 虚析构函数，确保通过基类指针删除派生类对象时，能够正确调用派生类的析构函数。 
    Document() = default;  

    void AddPages(unique_ptr<Page> page){
        pages_.push_back(std::move(page)); // std::move 将page的所有权转移给pages_，page将变为空指针 
    }

    const list<unique_ptr<Page>>& GetPages(){
        return pages_; // 返回一个const引用，防止对pages_的修改 
    } 

    // 工厂模式 
    virtual void CreatePages(void) = 0; // 纯虚函数，派生类必须实现

private:
    list<unique_ptr<Page>> pages_;
}; 

// 基于工厂模式快速实现一个Resumu简历 
class Resume : public Document{
public: 
    Resume(){
        cout << "创建简历中 ..." << endl; 
        this->CreatePages();
    }

    void CreatePages(void) override{
        AddPages(std::make_unique<IntroductionPage>());
        AddPages(std::make_unique<SkillsPage>());
        AddPages(std::make_unique<EducationPage>());
        AddPages(std::make_unique<ExperiencePage>());
    }
};




int main(){
    // Demo01 分别制造A产品和B产品 
    std::unique_ptr<Factory> factoryA = std::make_unique<FactoryA>(); 
    std::unique_ptr<Product> productA = factoryA->createProduct(); 
    productA->operation(); 

    std::unique_ptr<Factory> factoryB = std::make_unique<FactoryB>();
    std::unique_ptr<Product> productB = factoryB->createProduct();
    productB->operation();


    // Demo 02 创建简历  
    // 使用指针，创建在堆区
    std::unique_ptr<Document> resume = std::make_unique<Resume>(); 
    cout << "\nResume Pages -------------" << endl;
    for(const auto& page : resume->GetPages()){
        cout << page->GetPageName() << endl; 
    }

    return 0;
}

