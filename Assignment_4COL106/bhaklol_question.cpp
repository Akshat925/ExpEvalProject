#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

int val(char c){
    if(c=='A'){
        return 1;
    }
    else if(c=='B'){
        return 10;
    }
    else if(c=='C'){
        return 100;
    }
    else if(c=='D'){
        return 1000;
    }
    else if(c=='E'){
        return 10000;
    }
    else{
        return 1;
    }
}

int compute(string a){
    vector<string> b;
    int j=a.size()-1;
    while(j>=0){
        string c;
        c+=a[j];
        char p=a[j];
        j--;
        while(j>=0 && a[j]<p){
            c+=a[j];
            j--;
        }
        b.push_back(c);
    }
    int s=0;
    for(int i=0;i<b.size();i++){
        int m=0;
        m+=val(b[i][0]);
        for(int j=1;j<b[i].size();j++){
            m-=val(b[i][j]);
        }
        s+=m;
    }
    return s;
}

int main(){
    int t;
    cin>>t;
    for(int i=0;i<t;i++){
        string a;
        cin>>a;
        int ma=compute(a);
        for(int j=0;j<a.size();j++){
            char p=a[j];
            a[j]='A';
            ma=max(ma,compute(a));
            a[j]='B';
            ma=max(ma,compute(a));
            a[j]='C';
            ma=max(ma,compute(a));
            a[j]='D';
            ma=max(ma,compute(a));
            a[j]='E';
            ma=max(ma,compute(a));
            a[j]=p;
        }
        cout<<ma<<endl;
    }
    return 0;
}