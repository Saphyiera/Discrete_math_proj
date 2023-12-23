/*
Dem so thanh phan lien thong cua do thi G 
*/
#include <bits\stdc++.h>

using namespace std;

string V[5757];     //ds dinh
vector<string> Adj[5757];   //ds canh ke
map<string , short> M;  // map word->int

//ham nhap du lieu tu file word-sgb.txt va u,v
void input(){
    short i = 0;
    string s;
    ifstream sgb_word;
    sgb_word.open("sgb-words.txt",ios_base::in);
    while(i < 5757){
        getline(sgb_word,s);
        V[i] = s;
        M.insert({s,i});
        i++;
    }   
    sgb_word.close();
}

//ham kiem tra canh ke
// 2 canh ke nhau neu khac nhau 1 chu
bool is_adj(string u, string v){
    short count = 0;
    for(short i = 0; i < 5; ++i){
        if(u[i] != v[i])    count++;
    }
    return count == 1;
}

//ham sinh ds ke
void Graph_gen(){   //  O(n^2)
    for(short i = 0 ; i < 5757 ; ++i){
        for(short ii = i+1 ; ii < 5757 ; ++ii){
            if (is_adj(V[i] , V[ii])) //2 canh ke nhau thi day vao mang Adj
            {
                Adj[i].push_back(V[ii]);
                Adj[ii].push_back(V[i]);
            }
        }
    }
}


short part = 0;
bool visited[5757]={false};
short TPLT[5757];

void explore(int i){
    visited[i] = true;
    TPLT[i] = part;
    for(auto v : Adj[i]){
        short ii = M[v];
        if(visited[ii] == false){
            explore(ii);
        }
    }
}

void DFS(){
    for(short i = 0 ; i < 5757 ; ++i){
        if(!visited[i]){
            part++;
            explore(i);
        }
    }
}

//Nguyen Vu Minh Duc 20224956
int main(){
    input();
    Graph_gen();
    DFS();
    cout << part << endl; //hien thi so thanh phan lien thong
    return 0;
}