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
	freopen("challenge_4.txt","r",stdin);  
   
    string line;

    int score =0  ;
    string ans;
    while(getline(cin,line)){
    string s1=line;
    
   
     vector<unsigned char> bytes,temp;
     bytes=hex_to_bytes(s1);
    for (int k = 0; k < 256; ++k)
    {	temp=bytes;
    	for (int j = 0; j <bytes.size() ; ++j)
    	{
    		temp[j]=temp[j]^k;
    	}
    	string result(temp.begin(), temp.end());
    	int point =0;

    	for (int i = 0; i < result.size(); ++i)
    	{
    		if(result[i]==' ')point+=6;
    		else if(result[i]=='E'||result[i]=='e')point+=5;
    		else if(result[i]=='T'||result[i]=='t'||result[i]=='A'||result[i]=='a')point+=4;
    		else if(result[i]=='O'||result[i]=='o'||result[i]=='i'||result[i]=='I'||result[i]=='n'||result[i]=='N')point+=3;
    		else if(result[i]=='s'||result[i]=='S'||result[i]=='h'||result[i]=='H'||result[i]=='r'||result[i]=='R')point+=2;
	    	else if(result[i]=='^'||result[i]=='@'||result[i]=='#'||result[i]=='$'||result[i]=='%'||result[i]=='*'||result[i]=='{'||result[i]=='}')point-=10;
	    	else if((result[i]>'A'&&result[i]<='Z')||(result[i]>'a'&&result[i]<='z'))point+=1;
	    	else point-=2;

    	}
    	if(point>score){
    		ans=result;
    		score=point;
    	}
    }}
    
    cout<<"Plain text is:"<<endl<<ans<<endl;


}
        
       