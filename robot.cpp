#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <fstream>
#include <sstream>

#define infty INT_MAX
#define SIZE 100
#define STOP 1000000

using namespace std;

vector<pair<int,int>> Adjacent[SIZE]; // neighbor,weight
vector<pair<int,int>> Result;
set<pair<int,int>> Visitted;

int Distance[SIZE][SIZE] = {};
int n,m,a,b,c,d,r;
size_t count = 0;

void fileinput(){
    int x,y,w;
    ifstream f;
    f.open("test1.txt", ios::in);
    string s;
    getline(f,s);
    stringstream ss(s);
    ss >> n >> m;
    for(size_t i {} ; i < m ; ++i){
        string sss;
        getline(f,sss);
        stringstream ssss(sss);
        ssss >> x >> y >> w;
        Adjacent[x].push_back({y,w});
        Adjacent[y].push_back({x,w});
    }
    string s1;
    getline(f,s1);
    stringstream ss1(s1);
    ss1 >> a >> b >> c >> d >> r; 
}

void input(){
    cin >> n >> m;
    int x , y , w;
    for(size_t i {} ; i < n ; ++i){
        for(size_t ii {} ; ii < n ; ++ii){
            Distance[i][ii] = infty;
        }
    }
    for(size_t i {} ; i < m ; ++i){
        cin >> x >> y >> w;
        Adjacent[x].push_back({y,w});
        Adjacent[y].push_back({x,w});
    }
    cin >> a >> b >> c >> d;
    cin >> r;
}

void dijsktra(int source){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; //dist,id
    bool alarmed[n] {};
    pair<int , int> cur {};
    int current_distance[n] {};
    for(size_t i{} ; i < n ; ++i)   current_distance[i] = infty; //khoi tao
    current_distance[source] = 0;
    pq.push({0,source});
    while(!pq.empty()){
        cur = pq.top();
        pq.pop();
        if(cur.first > current_distance[cur.second]){
            continue;   
        }
        for(auto v : Adjacent[cur.second]){
            int name = v.first;
            if(alarmed[name]) continue;
            int add_on_weight = v.second;
            if(current_distance[cur.second] + add_on_weight < current_distance[name]){
                current_distance[name] = current_distance[cur.second] + add_on_weight;
                pq.push({current_distance[name] , name});
            }    
        }
        alarmed[cur.second] = true;
    }
    for(size_t i {} ; i < n ; ++i){
        Distance[source][i] = Distance[i][source] = current_distance[i];
    }
}

void distances_gen(){
    for(size_t i {} ; i < n ; ++i){
        dijsktra(i);
    }
}

void schedule(int current_A, int current_B){
    Visitted.insert({current_A , current_B});
    Result.push_back({current_A , current_B});
    if (current_A == c && current_B == d){
        for(auto x : Result){
            cout << x.first << " " << x.second << " " << Distance[x.first][x.second] << endl;
        }
        exit(0);
    }
    else{
        for(auto next_V : Adjacent[current_A]){
            int next_A = next_V.first;
            if(Distance[next_A][current_B] > r && !Visitted.contains({next_A , current_B})){
                count++;
                schedule(next_A ,current_B);
                Visitted.erase({next_A , current_B});
                Result.pop_back();
            }
        }
        for(auto next_V : Adjacent[current_B]){
            int next_B = next_V.first;
            if(Distance[next_B][current_A] > r && !Visitted.contains({current_A , next_B})){
                count++;
                schedule(current_A , next_B);
                Visitted.erase({current_A , next_B});
                Result.pop_back();
            }
        }
    }
}

int main(){
    input();
//    fileinput();
    distances_gen();
    if (Distance[a][c] == infty || Distance[b][d] == infty){
        cout << "Khong the!" << endl;
    }
    else{
        schedule(a,b);   
    }
    return 0;
}