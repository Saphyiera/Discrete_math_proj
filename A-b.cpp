#include <bits\stdc++.h>

using namespace std;

string V[5757];     //ds dinh
vector<string> Adj[5757];   //ds canh ke
map<string , short> M;  // map word->int

//ham nhap du lieu tu file word-sgb.txt va u,v
void input(string& u, string& v){
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
    cin >> u;   cin >> v;
}

//ham kiem tra canh ke
// 2 canh ke nhau neu khac nhau 1 chu
bool is_adj(string u, string v){
    short count = 0;
    for(short i = 0; i < 5; ++i){
        if(u[i] != v[i])    count++;
    }
    return (count == 1);
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


void BFS(string u, string v){
    if(TPLT[M[u]] != TPLT[M[v]]){   // kiem tra u va v cung thanh phan lien thong
        cout << "Khong co duong di tu u den v!" << endl;
        return;
    }
    else if ( u == v ){
        cout << u << " " << v;
        return;
    }
    string prev[5757];
    queue<string> Q;
    Q.push(u);  visited[M[u]] = true;
    while(Q.front() != v){
        string cur = Q.front();
        for(auto t : Adj[M[cur]]){
            if(!visited[M[t]]){
                Q.push(t);
                visited[M[t]] = true;
                prev[M[t]] = cur;
            }
        }
        Q.pop();
    }
    stack<string> S;
    do{
        S.push(v);
        v = prev[M[v]];
    } while(v != u);
    S.push(u);
    while(!S.empty()){
        cout << S.top() << " ";
        S.pop();
    }
}

//Nguyen Vu Minh Duc 20224956
int main(){
    string u,v;
    input(u,v);
    Graph_gen();
    DFS();
    for(short i = 0 ; i < 5757 ; ++i){
        visited[i] = false;
    }   
    BFS(u,v);
    return 0;
}