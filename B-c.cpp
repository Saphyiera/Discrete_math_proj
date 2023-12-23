//#include <bits\stdc++.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <queue>
#include <stack>

using namespace std;

string V[5757];     //ds dinh
map<string , short> name_mp;  // map word->int

//ham nhap du lieu tu file word-sgb.txt va u,v
void input(){
    short i = 0;
    string s;
    ifstream sgb_word;
    sgb_word.open("sgb-words.txt" , ios_base::in);
    while(i < 5757){
        getline(sgb_word , s);
        V[i] = s;
        name_mp.insert({s , i});
        i ++;
    }   
    sgb_word.close();
}

//  u->v in E if last4char(u) in v
bool is_adj(string u, string v){
    short count = 0;
    bool check[5] = {false,false,false,false,false};
    for(short i = 0 ; i < 5 ; ++i){    //kiem tra cac ki tu trong v
        for(short ii = 1 ; ii < 5 ; ++ii){
            if (check[ii] == false && v[i] == u[ii]) //ki tu cua u chua xuat hien trong v
            {
                check[ii] = true;
                count ++;
                break;
            }  
        }
    }
    return count == 4;
}

int edges = 0;

//ham sinh ds ke
void Graph_gen(vector<string> D[]){
    for(short i = 0 ; i < 5757 ; ++i){
        for(short ii = 0 ; ii < 5757 ; ++ii){
            if (i != ii && is_adj(V[i] , V[ii])) //2 canh ke nhau thi day vao mang D
            {
                edges++;
                D[i].push_back(V[ii]);  // canh xuoi
            }
        }
    }
}

void BFS(string u, string v, vector<string> D[]){
    bool injected[5757];
    queue<string> Q;
    string prev[5757];
    for(short i = 0 ; i < 5757 ; ++i){
        prev[i] = "";
        injected[i] = false;
    }
    Q.push(u);
    while(!Q.empty()){
        string cur = Q.front();
        if(cur == v){
            break;
        }
        for(auto t : D[name_mp[cur]]){
            if(!injected[name_mp[t]]){
                Q.push(t);
                prev[name_mp[t]] = cur;
                injected[name_mp[t]] = true;
            }
        }   
        Q.pop();
    }
    if(prev[name_mp[v]] == ""){
        cout << "Khong co duong di tu " << u << " den " << v << "!" << endl;
        return;
    }
    stack<string> S;
    while(v != u){
        S.push(v);
        v = prev[name_mp[v]];
    }
    cout << u << " ";
    while(!S.empty()){
        cout << S.top() << " ";
        S.pop();
    }
    cout << endl;
}

int main(){
    input();
    vector<string> D[5757];   //ds canh ke cua D
    Graph_gen(D);
    string u,v;
    cin >> u >> v;
    BFS(u,v,D);
    return 0;
}

