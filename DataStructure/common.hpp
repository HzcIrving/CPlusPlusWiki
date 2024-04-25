#pragma once 
#include <vector> 
#include <unordered_map> 
#include <algorithm>
using namespace std; 


// Graph节点类 
/* 
在邻接表中使用 Vertex 类来表示顶点，这样做的原因是：如果与邻接矩阵一样，用列表索引来区分不同顶点，那么假设要删除索引为i的顶点，则需遍历整个邻接表，将所有大于i的索引全部减，效率很低。

而如果每个顶点都是唯一的 Vertex 实例，删除某一顶点之后就无须改动其他顶点了。
*/
struct Vertex{
    int val; 
    Vertex(int x): val(x){
    }
}; 

/* 输入值列表 vals ，返回顶点列表 vets */
vector<Vertex *> valsToVets(vector<int> vals) {
    vector<Vertex *> vets;
    for (int val : vals) {
        vets.push_back(new Vertex(val));
    }
    return vets;
}

/* 输入顶点列表 vets ，返回值列表 vals */
vector<int> vetsToVals(vector<Vertex *> vets) {
    vector<int> vals;
    for (Vertex *vet : vets) {
        vals.push_back(vet->val);
    }
    return vals;
}


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

// 图 
class GraphList{
public:  
    // 临接表  
        // key: 顶点,  value: 所有与该顶点相连的节点 
        // 采样Vertex节点: 邻接矩阵一样，用列表索引来区分不同顶点，那么假设要删除索引为i的顶点，则需遍历整个邻接表，将所有大于i的索引全部减1，效率很低。
        // 而如果每个顶点都是唯一的 Vertex 实例，删除某一顶点之后就无须改动其他顶点了。
    unordered_map<Vertex *, vector<Vertex *>> adjList;    

    // 构造 
    GraphList(const vector<vector<Vertex *>> &edges){
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


class GraphAdj { 
    vector<int> vertices;       // 顶点列表，元素代表“顶点值”，索引代表“顶点索引”
    vector<vector<int>> adjMat; // 邻接矩阵，行列索引对应“顶点索引”

  public:
    /* 构造方法 */
    GraphAdj(const vector<int> &vertices, const vector<vector<int>> &edges) {
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

    /*重载[][]*/
    int &operator[](const pair<int, int> &p) {
        return adjMat[p.first][p.second];
    } 

    /* 依据节点，获得其他节点，而非节点索引 */
    // vector<int> getNeighbors(int val) {
    //     int index = find(vertices.begin(), vertices.end(), val) - vertices.begin();
    //     if (index == size()) {
    //         throw out_of_range("顶点不存在");
    //     }
    //     vector<int> neighbors;
    //     for (int i = 0; i < size(); i++) {
    //         if (adjMat[index][i] == 1) {
    //            neighbors.push_back(vertices[i]);
    //         }
    //     }
    // } 

    int getVet(int index){
        // cout << "节点:" << vertices[index] << endl; 
        return vertices[index]; 
    }

    int getIndex(int val){
        int index = find(vertices.begin(), vertices.end(), val) - vertices.begin();
        if (index == size()) {
            throw out_of_range("顶点不存在");
        }
        return index; 
    }
}; 