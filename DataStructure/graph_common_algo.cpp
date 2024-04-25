/*
图的两组基础算法 
1. 广度优先遍历 --- BFS
2. 深度有限遍历 --- DFS

知识点 ------------------------------------
1) 树的遍历可以看成图遍历的一种特例  
2) BFS需要依靠Queue数据结构（FIFO）, 如果是AD，需要借助优先级队列，优先级是依靠距离or其他规则 
3) DFS需要依靠Stack数据结构（LIFO）
-------------------------------------------

TODO 
[x]  

*/ 

#include <iostream>  
#include <queue>  
#include <vector> 
#include <unordered_set>
#include <cassert>
#include "common.hpp"
#include <algorithm>

using namespace std;  

/* BFS 
---------------------------------
队列的FIFO对应BFS“由远及近”的思路
1 将遍历起始顶点 startVertex 加入队列，并开启循环。
2 在循环的每轮迭代中，弹出队首顶点(弹出规则可以设置启发式函数) 并记录访问，然后将该顶点的所有邻接顶点加入到队列尾部。
3 循环步骤 2. ，直到所有顶点被访问完毕后结束。 
---------------------------------

时间复杂度：
- 所有顶点都会入队并出队一次，O(|V|)时间；遍历临接顶点的过程中，由于是无向图，所有节点都会被访问2次，使用O(2|E|)时间，总共时间复杂度 O(|V|+|E|) 
空间复杂度
- O(|V|) 
*/  
// 临接表形式的图  
vector <Vertex *> graphBFS(GraphList &graph, Vertex *startVertex){
    // 顶点遍历序列 
    vector<Vertex *> res; 

    // 错误检测 
    if(!graph.adjList.count(startVertex)){
        throw invalid_argument("不存在顶点"); 
    }  

    // 哈希表，记录访问过的顶点  
    unordered_set<Vertex *> visited = {startVertex}; 
    
    // 队列用于实现BFS 
    queue<Vertex *> que; 
    que.push(startVertex);

    while(!que.empty()){
        Vertex *vet = que.front(); // FIFO  
        que.pop(); // 头删，队首出队  
        res.emplace_back(vet); // 尾插，
        
        // 遍历该顶点邻接点 
        for(auto adjVet: graph.adjList[vet]){
            if(visited.count(adjVet)){
                // 已经访问过 
                continue; 
            } 
            // 放入visited中   
            visited.emplace(adjVet);  
            que.push(adjVet); 
        }
    }
    return res; 
} 

vector<int> graphBFSAdjMat(GraphAdj &graph, int start){
    /*顶点遍历序列*/   
    vector<int> res;     

    /*获得节点数量*/  
    int nNodes = graph.size(); 

    /*记录访问过的节点*/  
    unordered_set<int> visited = {start}; 

    /*队列，用于实现BFS，FIFO*/ 
    queue<int> que; 
    que.push(start);

    while(!que.empty()){
        int u = que.front();  // FIFO  
        /*获得u对应的节点编号*/ 
        int u_idx = graph.getIndex(u);  

        que.pop(); 
        res.emplace_back(u);  

        int tmp_vet;

        for(int i = 0; i<nNodes; i++){  
            pair<int,int> p = make_pair(u_idx,i);   
            tmp_vet = graph.getVet(i);
            if(graph[p] && visited.count(tmp_vet) == 0){
                visited.emplace(tmp_vet);  
                que.push(tmp_vet); 
            }
        } 
    } 
    return res;  
}

/* 
DFS
与广度优先遍历类似，深度优先遍历序列的顺序也不是唯一的。给定某顶点，先往哪个方向探索都可以，即邻接顶点的顺序可以任意打乱，都是深度优先遍历。

以树的遍历为例，“根 左 右”“左 根 右”“左 右 根”分别对应前序、中序、后序遍历，它们展示了三种遍历优先级，然而这三者都属于深度优先遍历。
-------------------------------------------------
时间复杂度: O(|V|) + 边2次访问O(2|E|) -> O(|V|+|E|) 
空间复杂度: 递归最大深度O|V|, O|V|空间
*/ 
/* 深度优先遍历辅助函数 */
void dfs(GraphList &graph, unordered_set<Vertex *> &visited, vector<Vertex *> &res, Vertex *vet) { 
    // 不存在提前终止 
    if (!graph.adjList.count(vet)) {
        return;
    }

    res.push_back(vet);   // 记录访问顶点
    visited.emplace(vet); // 标记该顶点已被访问
    // 遍历该顶点的所有邻接顶点
    for (Vertex *adjVet : graph.adjList[vet]) {
        if (visited.count(adjVet))
            continue; // 跳过已被访问的顶点
        // 递归访问邻接顶点
        dfs(graph, visited, res, adjVet);
    }
}

/* 深度优先遍历 */
// 使用邻接表来表示图，以便获取指定顶点的所有邻接顶点
vector<Vertex *> graphDFS(GraphList &graph, Vertex *startVet) {
    // 顶点遍历序列
    vector<Vertex *> res;
    // 哈希表，用于记录已被访问过的顶点
    unordered_set<Vertex *> visited;
    dfs(graph, visited, res, startVet);
    return res;
}


/*邻接矩阵版本的DFS*/ 
void dfsAdjMat(GraphAdj &graph, unordered_set<int> &visited, vector<int> &res, int vet){  
    visited.emplace(vet);  
    int vet_idx = graph.getIndex(vet);    
    res.emplace_back(vet);  

    for(int i = 0; i<graph.size(); i++){
        pair<int,int> p = make_pair(vet_idx,i);   
        int neighbor = graph.getVet(i);
        if(graph[p] && !visited.count(neighbor)){
            dfsAdjMat(graph, visited, res, neighbor);
        }
    }

}

vector<int> graphDFSAdjMat(GraphAdj &graph, int start){
    /*遍历结果*/ 
    vector<int> res;  

    /*记录访问节点*/ 
    unordered_set<int> visited;   

    // dfs(graph) 
    dfsAdjMat(graph, visited, res, start); 

    return res; 
}


void testBfsAdj(){
    // 顶点列表
    vector<int> vertices = {0, 1, 2, 3, 4, 5, 6};
    // 边列表
    vector<vector<int>> edges = {{0, 1}, {0, 3}, {1, 2}, {2, 5}, {5, 4}, {5, 6}}; 
    GraphAdj graph(vertices, edges);
    // graph.print();  


    vector<int> res = graphBFSAdjMat(graph, 0);  
    vector<int> res_dfs = graphDFSAdjMat(graph, 0);

    cout << "BFS遍历结果"; 
    for(auto& vet:res){
        cout << vet << " ";
    }cout << endl;

    cout << "DFS遍历结果"; 
    for(auto& vet:res_dfs){
        cout << vet << " ";
    }cout << endl;

}
int main(){
    // 测试用例 
    // vector<Vertex *> v = valsToVets(vector<int>{1, 3, 2, 5, 4});
    // vector<vector<Vertex *>> edges = {{v[0], v[1]}, {v[0], v[3]}, {v[1], v[2]},
    //                                   {v[2], v[3]}, {v[2], v[4]}, {v[3], v[4]}}; 

    vector<Vertex *> v = valsToVets(vector<int>{0, 1, 2, 3, 4, 5, 6});
    vector<vector<Vertex *>> edges = {{v[0], v[1]}, {v[0], v[3]}, 
                                      {v[1], v[2]},
                                      {v[2], v[5]}, 
                                      {v[5], v[4]}, {v[5], v[6]}}; // 这里会自动建立双边edge(无向图) 

    GraphList graph(edges);
    cout << "\n初始化后，图为" << endl;
    graph.print(); 
    
    
    vector<Vertex *> BFS_res = graphBFS(graph, v[0]); 
    vector<int> BFS_res_vec = vetsToVals(BFS_res);    
    cout << "BFS遍历结果:" ;
    printVector(BFS_res_vec);  


    vector<Vertex *> DFS_res = graphDFS(graph, v[0]);  
    vector<int> DFS_res_vec = vetsToVals(DFS_res); 
    cout << "DFS遍历结果:" ;
    printVector(DFS_res_vec);

    cout << "===临接矩阵版本======" << endl; 
    testBfsAdj(); 

    
    return 0; 


}
