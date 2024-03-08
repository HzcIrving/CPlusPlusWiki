/*
2023-11-12 
需求：有5名选手：选手ABCDE，10个评委分别对每一名选手打分，去除最高分，去除评委中最低分，取平均分。

去除最高分 & 最低分 --- 排序 deque头删、尾删 

最终结果---------------------
候选人: 【选手A】 分数: 【77】
候选人: 【选手B】 分数: 【75】
候选人: 【选手C】 分数: 【82】
候选人: 【选手D】 分数: 【79】
候选人: 【选手E】 分数: 【76】
---------------------------- 

*/  
#include <deque> 
#include <vector> 
#include <iostream> 
#include <algorithm>  
#include <string> 
#include <random> 
#include <ctime>
#include "math.h"

using namespace std;  // 标准模板库  


class Candidate{
public:  
    Candidate(string name, int score);   
    void CandidateInfo();
    string m_Name; 
    int m_Score; 
};  

Candidate::Candidate(string name, int score){
    this->m_Score = score; 
    this->m_Name = name; 
} 

void Candidate::CandidateInfo(){
    cout << "候选人: 【" << this->m_Name << "】 分数: 【" << this->m_Score << "】" <<  endl;
}

// Create Candidate 
// 指定人数 
void CreateCandidate(vector<Candidate> &candidates, int num){
    string nameSeed = "ABCDE"; 
    for(int i = 0; i<num; i++){
        string name = "选手";
        name += nameSeed[i];
        int score = 0; // 成绩初始化
        Candidate p(name, score); 
        candidates.push_back(p);
    }
} 

// 评委打分
void JudgeScoringAndReprocessing(vector<Candidate> &candidates, int JudgeNum){ 
    uniform_int_distribution<int> Score(50,101);  
    default_random_engine e(time(NULL));
    for (vector<Candidate>::iterator it = candidates.begin(); it != candidates.end(); it++){

        // 评委打分记录 
        deque<int> scores;  
        for (int i = 0; i < JudgeNum; i++){
            int score = Score(e); 
            scores.push_back(score);  
        } 

        // 排序
        sort(scores.begin(), scores.end());

        // 去除最高分与最低分 
        scores.pop_front(); 
        scores.pop_back();  

        // 缩容 
        // deque<int> scores.swap(scores);  
        scores.shrink_to_fit(); 

        // 计算平均分 
        int sum = 0; 
        for (deque<int>::iterator dit = scores.begin(); dit != scores.end(); dit++){
            sum += *dit;
        } 

        double avg = double(sum) / scores.size(); 

        // 记录均分 
        it->m_Score = avg; 
    }
} 

void ShowScore(vector<Candidate> &candidates){
    for (int i=0; i< candidates.size(); i++ ){
        candidates[i].CandidateInfo();
    }
}

int main(){ 

    // 1. 创建5位选手 
    vector<Candidate> candidates; 
    int CanNum = 5; 
    CreateCandidate(candidates, CanNum);  

    // 2. 评委打分  
    JudgeScoringAndReprocessing(candidates,10);

    // 3. 显示最终得分 
    ShowScore(candidates); 


    return 0; 
}


