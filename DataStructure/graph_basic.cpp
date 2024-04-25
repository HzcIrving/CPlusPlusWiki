/*
基于邻接矩阵和邻接表分别实现对图结构的操作，并对比效率 
图的基础操作可分为对“边”的操作和对“顶点”的操作。在“邻接矩阵”和“邻接表”两种表示方法下，实现方式有所不同。 
给定顶点数量为n的无向图。

【邻接矩阵的实现】 
1. 添加或删除边：直接在邻接矩阵中修改指定的边即可，使用O(1)时间。而由于是无向图，因此需要同时更新两个方向的边。
2. 添加顶点：在邻接矩阵的尾部添加一行一列，并全部填0即可，使用O(n)时间。
3. 删除顶点：在邻接矩阵中删除一行一列。当删除首行首列时达到最差情况，需要将(n-1)^2个元素“向左上移动”，从而使用O(n^2)时间。
4. 初始化：传入 n个顶点，初始化长度为n的顶点列表 vertices ，使用O(n)时间；初始化n*n大小的邻接矩阵 adjMat ，使用O(n^2)时间。 

【邻接表】
*/ 

#include <iostream> 
#include <vector> 
#include <unordered_map>  
#include "common.hpp" 

using namespace std; 

// 打印vector
// void printVector(const vector<int> &v){
//     for (int i = 0; i < v.size(); i++) {
//         cout << v[i] << " ";
//     }
//     cout << endl;
// } 

// 打印vector<vector<int>> 
// void printVectorMatrix(const vector<vector<int>> &v){
//     for (int i = 0; i < v.size(); i++) {
//         for (int j = 0; j < v[i].size(); j++) {
//             cout << v[i][j] << " ";
//         }
//         cout << endl;
//     }
// }

/* 基于邻接矩阵实现的无向图类 */
class GraphAdjMat {
    vector<int> vertices;       // 顶点列表，元素代表“顶点值”，索引代表“顶点索引”
    vector<vector<int>> adjMat; // 邻接矩阵，行列索引对应“顶点索引”

  public:
    /* 构造方法 */
    GraphAdjMat(const vector<int> &vertices, const vector<vector<int>> &edges) {
        // 添加顶点
        for (auto val : vertices) {
            addVertex(val);
        }
        // 添加边
        // 请注意，edges 元素代表顶点索引，即对应 vertices 元素索引
        for (const vector<int> &edge : edges) {
            addEdge(edge[0], edge[1]);
        } // O(n^2)
    }

    /* 获取顶点数量 */
    int size() const {
        return vertices.size();
    }

    /* 添加顶点
    O(n)，尾部加一行即可
     */
    void addVertex(int val) {
        int n = size();
        // 向顶点列表中添加新顶点的值
        vertices.push_back(val);
        // 在邻接矩阵中添加一行
        adjMat.emplace_back(vector<int>(n, 0));
        // 在邻接矩阵中向每一列添加0 
        for (vector<int> &row : adjMat) {
            row.push_back(0);
        }
    }

    /* 删除顶点 
    删除头行头列时，最差，此时需要将(n-1)^2个元素向左上↖移动，此时时间复杂度O((n-1)^2) 
    -----------------------------------------------------------------------------
    */
    void removeVertex(int index) {
        if (index >= size()) {
            throw out_of_range("顶点不存在");
        }
        // 在顶点列表中移除索引 index 的顶点
        vertices.erase(vertices.begin() + index);
        // 在邻接矩阵中删除索引 index 的行
        adjMat.erase(adjMat.begin() + index);
        // 在邻接矩阵中删除索引 index 的列
        for (vector<int> &row : adjMat) {
            row.erase(row.begin() + index); // O(n^2) 这里隐含了最坏的头节点删除的情况 
        }
    }

    /* 添加边 */
    // 参数 i, j 对应 vertices 元素索引
    void addEdge(int i, int j) {
        // 索引越界与相等处理
        if (i < 0 || j < 0 || i >= size() || j >= size() || i == j) {
            throw out_of_range("顶点不存在");
        }
        // 在无向图中，邻接矩阵关于主对角线对称，即满足 (i, j) == (j, i)
        adjMat[i][j] = 1;
        adjMat[j][i] = 1;
    }

    /* 删除边 */
    // 参数 i, j 对应 vertices 元素索引
    void removeEdge(int i, int j) {
        // 索引越界与相等处理
        if (i < 0 || j < 0 || i >= size() || j >= size() || i == j) {
            throw out_of_range("顶点不存在");
        }
        adjMat[i][j] = 0;
        adjMat[j][i] = 0;
    }

    /* 打印邻接矩阵 */
    void print() {
        cout << "顶点列表 = ";
        printVector(vertices);
        cout << "邻接矩阵 =" << endl;
        printVectorMatrix(adjMat);
    }
}; 


/* 补充**
   基于邻接表实现  
   1 -- 5 -- 4
      ↘↓↙(双向)
        2  
   顶点| 与该顶点相连的所有节点  
    1   -> 2 -> 5 
    2   -> 1 -> 5 -> 4 
    5   -> 1 -> 2 -> 4 
    4   -> 2 -> 5 
    ----------------------------------------------------------
   设无向图的顶点总数为n、边总数为m 
   1. 添加边： 在顶点对应链表的末尾添加边即可，O(1)复杂度； 无向图，需要同时添加两个方向边；  
   2. 删除边： 在顶点对应链表中查找并删除指定边, O(m)复杂度；无向图，需要同时删除两个；
   3. 添加顶点：在邻接表中添加一个链表，并将新增顶点作为链表头节点，使用O(1)时间； 
   4. 删除顶点：遍历整个邻接表，删除包含指定顶点的边， 使用O(n+m)时间； 
   5. 初始化： 创建n个顶点 + 2m条边，O(n+m)时间 (每个顶点包含一个vector)；
*/
// 图 
class GraphAdjMatList{
public:  
    // 临接表  
        // key: 顶点,  value: 所有与该顶点相连的节点 
        // 采样Vertex节点: 邻接矩阵一样，用列表索引来区分不同顶点，那么假设要删除索引为i的顶点，则需遍历整个邻接表，将所有大于i的索引全部减1，效率很低。
        // 而如果每个顶点都是唯一的 Vertex 实例，删除某一顶点之后就无须改动其他顶点了。
    unordered_map<Vertex *, vector<Vertex *>> adjList;    

    // 构造 
    GraphAdjMatList(const vector<vector<Vertex *>> &edges){
        // 添加所有 顶点 & 边  
        for(auto &edge: edges){
            addVertex(edge[0]);
            addVertex(edge[1]);
            addEdge(edge[0], edge[1]);
        }
    }

    /* 节点数量 */ 
    int size(){
        return adjList.size();  
    } 

    /* 添加边 */ 
    void addEdge(Vertex *v1, Vertex *v2){ 
        if(!adjList.count(v1) || !adjList.count(v2) || v1 == v2){
            throw invalid_argument("不存在顶点");
        }
        adjList[v1].push_back(v2); // 直接尾插 
        adjList[v2].push_back(v1);
    } 

    /* 删除边 */   
    // 1. 在vector中删除指定节点 
    void remove(vector<Vertex *> &vec, Vertex *vet){
        for(int i = 0; i < vec.size(); i++){
            if(vec[i] == vet){
                vec.erase(vec.begin() + i);
                return;
            }
        }
    }

    // 2. 删除边 
    void removeEdge(Vertex *v1, Vertex *v2){
        if(!adjList.count(v1) || !adjList.count(v2) || v1 == v2){
            throw invalid_argument("不存在顶点"); 
        }
        remove(adjList[v1], v2); 
        remove(adjList[v2], v1); 
    } 

    /* 3. 添加顶点 */  
    void addVertex(Vertex *v){
        if(adjList.count(v)){
            return; // 重复添加
        }
        // 创建新链表 
        adjList[v] = vector<Vertex *>();  
    } 

    /* 4. 删除顶点 */  
    void removeVertex(Vertex *v){
        if(!adjList.count(v)){
            return; // 没这个节点  
        }  
        
        // 4.1 删除顶点对应链表 
        adjList.erase(v);  

        // 4.2 遍历其他链表，删除存在的v 
        for(auto &adj : adjList){
            remove(adj.second, v); // 删除vector<Vertex *> 中的v节点
        } 
    }

    /* 5. 打印 */ 
    void print(){
        cout << "邻接表图 =" << endl; 
        for(auto &adj: adjList){
            const auto &key = adj.first; 
            const auto &vec = adj.second; 
            cout << key->val << ":"; 
            printVector(vetsToVals(vec)); 
        }
    }
};

// 写测试GraphAdjMat各个功能的main函数
int main() {
    // 顶点列表
    vector<int> vertices = {1, 2, 3, 4, 5};
    // 边列表
    vector<vector<int>> edges = {{0, 1}, {0, 4}, {1, 2}, {1, 3}, {1, 4}, {2, 3}, {3, 4}}; 

    GraphAdjMat graph(vertices, edges);
    graph.print(); 

    // 增加顶点 
    graph.addVertex(6);  
    graph.print(); 
    // 删除顶点 
    graph.removeVertex(0);
    graph.print();  
    // 增加边 
    graph.addEdge(0, 4);
    graph.print();  
    // 删除边
    graph.removeEdge(0, 1);
    graph.print(); 
    return 0;
}


// 测试GraphAdjMatList各个功能的main函数 
// int main() {
//     /* 初始化无向图 
    
    
    
//     */ 
    
//     vector<Vertex *> v = valsToVets(vector<int>{1, 3, 2, 5, 4});
//     vector<vector<Vertex *>> edges = {{v[0], v[1]}, {v[0], v[3]}, {v[1], v[2]},
//                                       {v[2], v[3]}, {v[2], v[4]}, {v[3], v[4]}};
//     GraphAdjMatList graph(edges);
//     cout << "\n初始化后，图为" << endl;
//     graph.print();

//     /* 添加边 */
//     // 顶点 1, 2 即 v[0], v[2]
//     graph.addEdge(v[0], v[2]);
//     cout << "\n添加边 1-2 后，图为" << endl;
//     graph.print();

//     /* 删除边 */
//     // 顶点 1, 3 即 v[0], v[1]
//     graph.removeEdge(v[0], v[1]);
//     cout << "\n删除边 1-3 后，图为" << endl;
//     graph.print();

//     /* 添加顶点 */
//     Vertex *v5 = new Vertex(6);
//     graph.addVertex(v5);
//     cout << "\n添加顶点 6 后，图为" << endl;
//     graph.print();

//     /* 删除顶点 */
//     // 顶点 3 即 v[1]
//     graph.removeVertex(v[1]);
//     cout << "\n删除顶点 3 后，图为" << endl;
//     graph.print();

//     // 释放内存
//     for (Vertex *vet : v) {
//         delete vet;
//     }

//     return 0;
// }