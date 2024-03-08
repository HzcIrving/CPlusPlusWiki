/*
C++支持多维数组定义 
int A[5][10][4]   >>> 3维数组 
*/
#include <iostream> 
using namespace std; 

int main(){
    
    // 初始化二维数组: 指定值初始化  3行4列 
    int A[3][4] = {
        {0,1,2,3}, 
        {4,5,6,7}, 
        {8,9,10,11}, 
    };   

    // B与A等价     
    int B[3][4] = {0,1,2,3,4,5,6,7,8,9,10,11}; 

    // 访问多维数组 
    // 输出A中的每个值
    for(int i=0; i<3; i++){
        for (int j=0; j<4; j++){
            cout << "a[" << i << "][" << j << "] = " << A[i][j] << endl; 
        }
    }

    return 0; 

}