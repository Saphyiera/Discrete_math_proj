//#include <bits\stdc++.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

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

//  (u,v) in E if last4char(u) in v
bool is_adj(string u, string v){
    short count = 0;
    for(short i = 0 ; i < 5 ; ++i){    //kiem tra cac ki tu trong v
        for(short ii = 1 ; ii < 5 ; ++ii){
            if (u[ii] != 0) //ki tu cua u chua xuat hien trong v
            {
                if (v[i] == u[ii])
                {
                    u[ii] = 0;
                    count ++;
                    break;
                }  
            }  
        }
    }
    return count == 4;
}

//ham sinh ds ke
void Graph_gen(vector<string> D[], vector<string> D_r[]){
    for(short i = 0 ; i < 5757 ; ++i){
        for(short ii = 0 ; ii < 5757 ; ++ii){
            if (i != ii && is_adj(V[i] , V[ii])) //2 canh ke nhau thi day vao mang D, Dr
            {
                D[i].push_back(V[ii]);  // canh xuoi
                D_r[ii].push_back(V[i]);    // canh nguoc
            }
        }
    }
}

short part = 0;
short sorted_post[5757] = {0};
short post[5757] = {0};
short Clock = 0 ;
bool visited[5757] = {false};
short TPLT[5757] = {0};

void explore(int i , vector<string> D[]){
    Clock++;
    visited[i] = true;
    TPLT[i] = part;
    for(auto v : D[i]){
        short ii = name_mp[v];
        if(visited[ii] == false){   //tham dinh chua tham
            explore(ii , D);
        }
    }
    post[i] = Clock++;
}

void DFS(vector<string> D[]){
    for(short i = 0 ; i < 5757 ; ++i){
        if(!visited[i]){
            part++;
            explore(i , D);
        }
    }
}

int main(){
    input();
    vector<string> D[5757],D_r[5757];   //ds canh ke cua D va D_r
    Graph_gen(D , D_r);
    map<short , short> post_mp;
    DFS(D_r);
    for(short i = 0 ; i < 5757 ; ++i){
        post_mp.insert({post[i],i});
        sorted_post[i] = post[i]; //reset bien dung lai ben duoi =D
        visited[i] = false;
    }   
    sort(sorted_post , sorted_post + 5757);
    //Tim cac thanh phan lien thong manh cua D
    part = 0;
    for(short i = 5756 ; i > -1 ; --i){
        short cur = post_mp[sorted_post[i]];
        if(!visited[cur]){
            part++;
            explore(cur , D);
        }
    }
    string u;   cin >> u;
    short u_id = name_mp[u];
    //hien thi cac tu cung tplt manh voi u
    for(short i = 0 ; i < 5757 ; ++i){
        if(TPLT[i] == TPLT[u_id] && i != u_id){
            cout << V[i] << " " ;
        }
    }
    return 0;
}

