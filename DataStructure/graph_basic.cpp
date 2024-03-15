/*
基于邻接矩阵和邻接表分别实现对图结构的操作，并对比效率 
图的基础操作可分为对“边”的操作和对“顶点”的操作。在“邻接矩阵”和“邻接表”两种表示方法下，实现方式有所不同。 
给定顶点数量为n的无向图。

【邻接矩阵的实现】 
1. 添加或删除边：直接在邻接矩阵中修改指定的边即可，使用O(1)时间。而由于是无向图，因此需要同时更新两个方向的边。
2. 添加顶点：在邻接矩阵的尾部添加一行一列，并全部填0即可，使用O(n)时间。
3. 删除顶点：在邻接矩阵中删除一行一列。当删除首行首列时达到最差情况，需要将(n-1)^2个元素“向左上移动”，从而使用O(n^2)时间。
4. 初始化：传入 n个顶点，初始化长度为n的顶点列表 vertices ，使用O(n)时间；初始化n*n大小的邻接矩阵 adjMat ，使用O(n^2)时间。
*/ 

#include <iostream> 
#include <vector> 
using namespace std; 

// 打印vector
void printVector(const vector<int> &v){
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
} 

// 打印vector<vector<int>> 
void printVectorMatrix(const vector<vector<int>> &v){
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
}

/* 基于邻接矩阵实现的无向图类 */
class GraphAdjMat {
    vector<int> vertices;       // 顶点列表，元素代表“顶点值”，索引代表“顶点索引”
    vector<vector<int>> adjMat; // 邻接矩阵，行列索引对应“顶点索引”

  public:
    /* 构造方法 */
    GraphAdjMat(const vector<int> &vertices, const vector<vector<int>> &edges) {
        // 添加顶点
        for (int val : vertices) {
            addVertex(val);
        }
        // 添加边
        // 请注意，edges 元素代表顶点索引，即对应 vertices 元素索引
        for (const vector<int> &edge : edges) {
            addEdge(edge[0], edge[1]);
        }
    }

    /* 获取顶点数量 */
    int size() const {
        return vertices.size();
    }

    /* 添加顶点 */
    void addVertex(int val) {
        int n = size();
        // 向顶点列表中添加新顶点的值
        vertices.push_back(val);
        // 在邻接矩阵中添加一行
        adjMat.emplace_back(vector<int>(n, 0));
        // 在邻接矩阵中添加一列
        for (vector<int> &row : adjMat) {
            row.push_back(0);
        }
    }

    /* 删除顶点 */
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
            row.erase(row.begin() + index);
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

