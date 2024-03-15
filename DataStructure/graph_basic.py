import numpy as np 

class GraphAdjMat: 
    # 邻接矩阵的无向图 
    
    def __init__(self, vertices, edges):
        """构造方法""" 
        # V 
        self.vertices = []  
        # Adjacency matrix 
        self.adj_matrix: List[List[int]] = [] 
        
        # 添加顶点 
        for vtc in vertices: 
            self.add_vertex(vtc)  # O(n)
        # print(self.adj_matrix) # n*n 全0矩阵  
        
        # 添加边 O(1)
        # 请注意，edges 元素代表顶点索引，即对应 vertices 元素索引 
        for edge in edges: 
            self.add_edge(edge) # O(1)
        # print(self.adj_matrix) 
        
    def size(self)->int:
        """顶点数量""" 
        return len(self.vertices)    
    
    def add_vertex(self, val:int):
        """添加顶点"""
        n = self.size() 
        # 添加新顶点 
        self.vertices.append(val) 
        # 临接矩阵中添加一行 
        new_row = [0] * n   
        self.adj_matrix.append(new_row) 
        # 临接矩阵中添加一列 
        # 即遍历行，每个行append一个额外的0 
        for row in self.adj_matrix: 
            row.append(0)    
            
    def remove_vertex(self, index):
        """删除顶点""" 
        if index > self.size():
            raise IndexError() 

        # 在顶点列表中删除index的顶点
        self.vertices.pop(index) 
        # 在临接矩阵中删除索引index的行 
        self.adj_matrix.pop(index) 
        # 在临接矩阵的每行中删除索引index的列
        for row in self.adj_matrix: 
            row.pop(index)
        
        
    def add_edge(self, edge): 
        """添加边""" 
        v1,v2 = edge 
        # 越界处理
        if v1<0 or v2<0 or v1>=self.size() or v2>=self.size() or v1 == v2:
            raise IndexError() 
        
        # v1, v2分别代表vertices元素索引   
        # 在无向图中，邻接矩阵关于主对角线对称，即满足 (i, j) == (j, i)
        self.adj_matrix[v1][v2] = 1 
        self.adj_matrix[v2][v1] = 1  
        
    def remove_edge(self, edge):
        """删除边"""  
        v1,v2 = edge  
        # 越界处理
        if v1<0 or v2<0 or v1>=self.size() or v2>=self.size() or v1 == v2:
            raise IndexError()  
        else:
            self.adj_matrix[v1][v2] = 0 
            self.adj_matrix[v2][v1] = 0 
    
    def print(self):
        """打印邻接矩阵"""
        print("顶点列表 =", self.vertices)
        print("邻接矩阵 =")
        # print(self.adj_matrix)
        for i in self.adj_matrix:
            print(i)
        
    

if __name__ == "__main__":
    vertices = [1, 3, 2, 5, 4]
    edges = [[0, 1], [0, 3], [1, 2], [2, 3], [2, 4], [3, 4]]
    graph = GraphAdjMat(vertices, edges) 
    graph.print()
    # 添加边
    # 顶点 1, 2 的索引分别为 0, 2
    graph.add_edge([0,2]) 
    graph.print()
    # 删除边
    # 顶点 1, 3 的索引分别为 0, 1
    graph.remove_edge(edges[0])
    graph.print()
    # 添加顶点
    graph.add_vertex(6)
    graph.print()
    # 删除顶点
    # 顶点 3 的索引为 1
    graph.remove_vertex(1)
    graph.print()