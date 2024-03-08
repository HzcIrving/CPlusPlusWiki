/*
员工分组 
- 公司今天招聘了10个员工（ABCDEFGHIJ），10名员工进入公司之后，需要指派员工在那个部门工作
- 员工信息有: 姓名 工资组成；部门分为：策划、美术、研发
- 随机给10名员工分配部门和工资
- 通过multimap进行信息的插入 key(部门编号) value(员工) 
    - multimap 可重复 
- 分部门显示员工信息 
------------------------------
1. 创建10名员工，放到vector中
2. 遍历vector容器，取出每个员工，进行随机分组
3. 分组后，将员工部门编号作为key，具体员工作为value，放入到multimap容器中
4. 分部门显示员工信息
*/

#include <iostream> 
#include <ctime> 
#include <random> 
#include <math.h> 
#include <vector> 
#include <map>
#include <string> 

using namespace std;  

// 部分预定义
#define CEHUA 1
#define MEISHU 2
#define YANFA 3 

class Worker{ 
    public:
        Worker(string name, int salary);
        void display();   

        void assignDepart(int depart_num){
            this->m_Department = depart_num;
        } 

        int getSalary(){
            return this->m_Salary;
        }

    private: 
        string m_Name; 
        int m_Salary; 
        int m_Department;
}; 

Worker::Worker(string name, int salary){
    this->m_Name = name; 
    this->m_Salary = salary; 
} 

void Worker::display(){
    cout << "姓名:" << this->m_Name <<" 薪资:" << this->m_Salary;   
    switch(this->m_Department){
            case CEHUA: 
                cout << " 部门：策划" << endl; 
                break; 
            case MEISHU: 
                cout << " 部门：美术" << endl; 
                break; 
            case YANFA: 
                cout << " 部门：研发" << endl; 
                break;  
            default:
                cout << " 部门未分配" << endl; 
                break;
        }
    }


void workerInfo(vector<Worker> &w){
    for(vector<Worker>::iterator it = w.begin(); it!= w.end(); it++){
        it->display();
    }
}

void createWorker(vector<Worker> &w){
    string nameSeed = "EFGHIJABCD"; 
    uniform_int_distribution<int> u(10000, 19999);   
    default_random_engine e(time(NULL));
    for (int i=0; i<nameSeed.size(); i++){ 
        // 左闭右闭 
        int Salary = u(e); 
        string Name = "Worker-"; 
        Name += nameSeed[i];
        Worker worker(Name, Salary);  
        w.push_back(worker);
    } 
    workerInfo(w); 
}  

// 分组函数 
void setGroup(vector<Worker> &w, multimap<int, Worker> &m){ 
    uniform_int_distribution<int> u(1,3); // 1,2,3 
    default_random_engine e(time(NULL)); 
    for(vector<Worker>::iterator it = w.begin(); it!=w.end(); it++){ 
        int depart_num = u(e);
        it->assignDepart(depart_num); 
        m.insert(make_pair(depart_num, *it)); 
    }
    workerInfo(w);
}

void showWorker(int depart, multimap<int, Worker> &m){ 
    string departInfo; 
    switch(depart){
        case CEHUA: 
            departInfo = "策划"; 
            break; 
        case MEISHU: 
            departInfo = "美术"; 
            break; 
        case YANFA: 
            departInfo = "研发"; 
            break; 
        default: 
            departInfo = "未分配"; 
            break; 
    } 
    // cout 打印部门信息
    cout << "----------" << departInfo << "部门信息------------" << endl;  
    cout << "【部门人数】: " << m.count(depart) << endl;
    for(multimap<int, Worker>::iterator it = m.begin(); it!=m.end(); it++){ 
        if(it->first == depart){
            it->second.display(); 
        }
    }
} 

// 按组打印 
void showWorkerByDepartment(multimap<int, Worker> &m){
    showWorker(CEHUA, m); 
    showWorker(MEISHU, m); 
    showWorker(YANFA, m); 
}

int main(){
    vector<Worker> w; 
    multimap<int, Worker> g;
    createWorker(w);   
    cout << "----------------------------" << endl;
    setGroup(w,g);
    // cout << "----------------------------" << endl; 
    showWorkerByDepartment(g);

    return 0; 
}

