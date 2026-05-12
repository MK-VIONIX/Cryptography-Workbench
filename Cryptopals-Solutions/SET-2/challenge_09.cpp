#include <bits/stdc++.h>
using namespace std;
string bytes_to_hex(const vector<unsigned char>& bytes){

    string hex_table = "0123456789abcdef";
    string result;

    for(unsigned char byte : bytes){

        int high = byte >> 4;
        int low  = byte & 15;

        result += hex_table[high];
        result += hex_table[low];
    }

    return result;}

int main(){

    string text;
    getline(cin, text);   
    vector<unsigned char> byte(text.begin(), text.end());

    int block_size = 16;
    int pad = block_size - (byte.size() % block_size);

    if(pad == 0) pad = block_size;

    for(int i = 0; i < pad; i++){
        byte.push_back((unsigned char)pad);
    }
    cout<<bytes_to_hex(byte)<<endl;

    
}
