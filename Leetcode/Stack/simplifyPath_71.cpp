/*
71. 简化路径 
https://leetcode.cn/problems/simplify-path/description/?envType=study-plan-v2&envId=top-interview-150 

考察点: 栈 
我们首先将给定的字符串 path\textit{path}path 根据 / 分割成一个由若干字符串组成的列表，记为 names。根据题目中规定的「规范路径的下述格式」，names 中包含的字符串只能为以下几种：
1. 空字符串。例如当出现多个连续的 /\texttt{/}/，就会分割出空字符串；
2. 一个点 .；
3. 两个点 ..；
4. 只包含英文字母、数字或_的目录名。

对于「空字符串」以及「一个点」，我们实际上无需对它们进行处理，因为「空字符串」没有任何含义，而「一个点」表示当前目录本身，我们无需切换目录。
对于「两个点」或者「目录名」，我们则可以用一个栈来维护路径中的每一个目录名。当我们遇到「两个点」时，需要将目录切换到上一级，因此只要栈不为空，我们就弹出栈顶的目录。当我们遇到「目录名」时，就把它放入栈。

这样一来，我们只需要遍历 names 中的每个字符串并进行上述操作即可。在所有的操作完成后，我们将从栈底到栈顶的字符串用 / 进行连接，再在最前面加上/表示根目录，就可以得到简化后的规范路径。

作者：力扣官方题解
链接：https://leetcode.cn/problems/simplify-path/solutions/1193258/jian-hua-lu-jing-by-leetcode-solution-aucq/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

*/ 
#include <string> 
#include <vector>
#include <iostream> 
using namespace std; 

class Solution {
public:
    string simplifyPath(string path) { 
        vector<string> path_split = split(path, '/');
        printX(path_split);  

        // 创建LIFO的栈  
        vector<string> path_stack; 
        for(string & name: path_split){
            printX(path_stack); 
            if (name == ".."){ 
                if (!path_stack.empty()){
                    // 移除上一个  
                    path_stack.pop_back(); 
                }
            }else if(name!="" && name!="."){
                path_stack.push_back(name);
            }
        } 

        string ans;

        if (path_stack.empty()){
            ans = "/"; 
        }else{
            for(string &name: path_stack){
                ans += "/" + name; 
            }
        }

        return ans; 
    }

    vector<string> split(const string &s, char delim){
        // delim 分割符 e.g. "/"
        vector<string> ans; 
        string cur; 
        for(char ch:s){
            if(ch == delim){
                ans.push_back(cur); 
                cur.clear(); 
                continue; 
            }else{
                cur += ch; 
            }
        }
        return ans; 
    } 

    template<class T> 
    void printX(const T &a){
        for(auto it = a.begin(); it!=a.end(); ++it){
            cout << *it << " "; 
        } cout << endl; 
    }
}; 

int main(){
    // string path = "/home/A/B/C/../D/end/.//./"; 
    string path = "/a//b////c/d//././/.."; 
    string ans = Solution().simplifyPath(path); 
    cout << ans << endl; 

}