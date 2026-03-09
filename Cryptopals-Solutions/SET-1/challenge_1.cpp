#include <bits/stdc++.h>
using namespace std;

string hex_to_base64(string s){

    string table =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    vector<unsigned char> bytes;

    // hex → bytes
    for(int i=0;i<s.size();i+=2){
        string part = s.substr(i,2);
        unsigned char value = stoi(part,0,16);
        bytes.push_back(value);
    }

    string ans;

    int val = 0;
    int valb = -6;

    for(unsigned char c : bytes){

        val = (val << 8) + c;
        valb += 8;

        while(valb >= 0){
            int index = (val >> valb) & 63;
            ans += table[index];
            valb -= 6;
        }
    }

    if(valb > -6){
        int index = ((val << 8) >> (valb + 8)) & 63;
        ans += table[index];
    }

    while(ans.size() % 4)
        ans += '=';

    return ans;
}

int main(){

    string s;
    cin >> s;

    cout << hex_to_base64(s);

}