// 使用fstream标准库实现文件读写 
#include <iostream> 
#include <fstream> 
#include <string>

using namespace std; 

int main(){ 
    //////////////////////////////////////////////////////////////////
    // 1. 创建一个file pointer  
    // ofstream is used to write to a file，具体功能是：创建一个文件，如果文件已经存在，则覆盖原有文件
    ofstream Myfile("File_tutorial/sample.txt");  

    // Write to the file
    Myfile << "This is me\n";
    Myfile << "This is also me\n";

    // close the file pointer
    Myfile.close();

    //////////////////////////////////////////////////////////////////  
    // 2. 读取操作
    // Create a text string, which is used to output the text file
    string myText;
    // Read from the text file
    ifstream MyReadFile("File_tutorial/Read.txt"); 
    // Use a while loop together with the getline() function to read the file line by line
    while (getline (MyReadFile, myText)) {
        // Output the text from the file
        cout << myText << endl;
    }
    // Close the file
    MyReadFile.close();

    return 0;  



}