#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*
* 逐行读取 txt 文件
* input: string file
*/
void readTxt(string file){
    ifstream infile(file);
    string s;
    getline(infile, s);
    cout << s << endl;
    getline(infile, s);
    cout << s << endl;
    // while(getline(infile, s)) {
    //     cout << s << endl;
    // }
    infile.close();
}