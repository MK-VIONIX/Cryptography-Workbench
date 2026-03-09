#include <bits/stdc++.h>
using namespace std;

vector<unsigned char> hex_to_bytes(string s){

    vector<unsigned char> bytes;

    for(int i=0;i<s.size();i+=2){
        string part = s.substr(i,2);
        unsigned char value = stoi(part,0,16);
        bytes.push_back(value);
    }

    return bytes;
}

string bytes_to_hex(const vector<unsigned char>& bytes){

    string hex_table = "0123456789abcdef";
    string result;

    for(unsigned char byte : bytes){

        int high = byte >> 4;
        int low  = byte & 15;

        result += hex_table[high];
        result += hex_table[low];
    }

    return result;
}

int main(){

    string s1,s2;
    cin >> s1 >> s2;

    vector<unsigned char> x1,x2,x3;

    x1 = hex_to_bytes(s1);
    x2 = hex_to_bytes(s2);

    for(int i=0;i<x1.size();i++){
        x3.push_back(x1[i] ^ x2[i]);
    }

    cout << bytes_to_hex(x3);
}