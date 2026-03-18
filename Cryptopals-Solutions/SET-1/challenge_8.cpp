#include <bits/stdc++.h>
using namespace std;

vector<unsigned char> hex_to_bytes(string s) {
    vector<unsigned char> bytes;

    for(int i = 0; i < s.size(); i += 2) {
        string part = s.substr(i, 2);
        unsigned char value = stoi(part, 0, 16);
        bytes.push_back(value);
    }

    return bytes;
}

int main() {

    freopen("challenge_8.txt", "r", stdin);

    string line, ency;
    int points = 0;

    while(getline(cin, line)) {

        vector<unsigned char> bytes = hex_to_bytes(line);
        unordered_set<string> strings;

        for(int i = 0; i < bytes.size(); i += 16) {

            string temp = "";

            for(int j = 0; j < 16 && i + j < bytes.size(); j++) {
                temp += bytes[i + j];
            }

            strings.insert(temp);
        }

        int score = (int)bytes.size()/16 - (int)strings.size();

        if(score > points) {
            points = score;
            ency = line;
        }
    }

    cout <<points<<endl<< ency << endl;
}