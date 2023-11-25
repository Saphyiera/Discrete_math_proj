/*output: file DFS3.dot luu rung dfs cua do thi, phia tren ben trai moi node la (pre,post)
			node ket thuc mau vang
			node can tim mau xanh dam hon
			node bat dau mau xanh nhat
		  file Full_Graph3.dot luu do thi va rung dfs(canh co arrow mau do)
		  
		  moi lan chay chuong trinh cho ra 1 rung dfs khac nhau do thu tu duyet la ngau nhien 
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>

using namespace std;

//ham sinh hoan vi
short temp[6];
short perm[720][6];
bool check[6] = {false,false,false,false,false,false};
short count = 0;
void perm_gen(short n, short i)
{
	if (n == i)
	{
		for(short j = 0 ; j < n ; ++j)
		{
			perm[count][j] = temp[j];
		}
		count++;
	}
	else
	{
		for(short j = 0 ; j < n ; ++j)
		{
			if(check[j] == 0)
			{
				check[j] = true;
				temp[i] = j;
				perm_gen(n,i+1);
				check[j] = false;
			}
		}
	}
}

bool exist[1075]; //mang danh dau co ton tai
bool visited[11][8][5]; //mang danh dau dinh (x,y,z) da tham
bool colored[11][8][5]; // mang danh dau mau
short pre[1075];
short post[1075];
/*
Co cac cach do nuoc sau, goi la a --> b voi V <-- Va, V' <-- Vb
x --> y		x --> z		Dieu kien do nuoc: V > 0
y --> x		y --> z
z --> z		z --> y
Chi xay ra 2 TH binh b day va binh a het

==> do co 6 cach do nuoc nen dinh (x,y,z) co nhieu nhat 6 dinh ke
*/
short adj[11][8][5][6] = {0}; //mang luu dinh ke cua dinh (x,y,z) duoi dang short: (x,y,z) ~ 100x+10y+z

void graphgen()
{
	for(short i = 0 ; i < 1075 ; ++ i)
	{
		char x = i / 100 , y = (i % 100) / 10 , z = i % 10;
		if(x + y + z != 11 || y > 7 || z > 4) //khong co dinh nao nhu nay
		{
			exist[i] = false;
			continue;
		}	
		exist[i] = true; //dinh co the ton tai
		char j = 0;
		if(x > 0) 
		{
			// x-->y
			if(y < 7)
			{
				if(x + y > 6)	adj[x][y][z][j++] = (x + y - 7) * 100 + 70 + z; // binh y day
				else			adj[x][y][z][j++] = (x + y) * 10 + z;		//binh x het					
			}
			// x-->z
			if(z < 4)
			{
				if(x + z > 3)	adj[x][y][z][j++] = (x + z - 4) * 100 + y * 10 + 4; // binh z day
				else			adj[x][y][z][j++] = y * 10 + (z + x);		//binh x het						
			}		
		}
		if(y > 0)
		{
			// y-->x
			if(x < 10)
			{
				if(x + y > 9)	adj[x][y][z][j++] = 1000 + (x + y - 10) * 10 + z; // binh x day
				else			adj[x][y][z][j++] = (x + y) * 100 + z;		//binh y het				
			}
			// y-->z
			if(z < 4)
			{
				if(z + y > 3)	adj[x][y][z][j++] = x * 100 + (y + z - 4) * 10 + 4; // binh z day
				else			adj[x][y][z][j++] = x * 100 + (y + z);		//binh y het					
			}
		}
		if(z>0)
		{
			// z-->x
			if(x < 10)
			{
				if(z + x > 9)	adj[x][y][z][j++] = 1000 + y * 10 + (x + z - 10); // binh x day
				else			adj[x][y][z][j++] = (x + z) * 100 + y * 10;		//binh z het			
			}
			// z-->y
			if(y < 7)
			{
				if(z + y > 6)	adj[x][y][z][j++] = x * 100 + 70 + (z + y - 7); // binh y day
				else			adj[x][y][z][j++] = x * 100 + (z + y) * 10;		//binh z het				
			}
		}
	}
}
int _i = 0;
short res[100]; //mang luu ket qua
short next[100] = {0};
short cclock = 1;

void explore(short v)
{
	char x=v/100, y = (v%100)/10, z = v%10;
	visited[x][y][z] = true;
	pre[v] = cclock++;
	
	//chon ngau nhien 1 to hop so tu bo perm
	short rand_perm[6];
	short rand_int = rand();
	rand_int = rand_int%720;
	for( char i = 0 ; i < 6 ; ++i)		rand_perm[i] = perm[rand_int][i];
	
	for ( char i = 0 ; i < 6 ; ++ i ) //duyet cac dinh u ke voi v
	{
		short j = rand_perm[i];
		if(!adj[x][y][z][j]) continue; // da duyet dinh ke nay
		short u = adj[x][y][z][j];
		if(!visited[u/100][(u%100)/10][u%10]) //neu dinh u chua tham thi explore u
		{
			res[_i] = v;
			if(y == 2 || z == 2) colored[x][y][z] = 1; //danh dau mau
			else colored[x][y][z] = 0;
			next[_i] = u;
			_i++;
		    explore(u);	
		}
	}
	post[v] = cclock++;
}
//Nguyen Vu Minh Duc 20224956
int main()
{
	srand(time(NULL));
	perm_gen(6,0);
	graphgen();
	explore(74);

//output ra rung dfs vao file DFS3.dot

	fstream output;
	output.open("DFS3.dot" , ios::in | ios::out | ios::trunc);
	output << "digraph DFS_forest3\n{\n";
	//dinh
	for(short v = 0 ; v < 1075 ; ++v)
	{
		short x = v / 100 , y = (v % 100) / 10 , z = v % 10;
		if(exist[v] && visited[x][y][z])
		if(colored[x][y][z] == 0)
			output << "\t" << v << "[label=\"(" << x << "," << y << "," << z <<")\",xlabel=\"("<<pre[v]<<","<<post[v]<<")\"];\n";
		else
			output << "\t" << v << "[label=\"(" << x << "," << y << "," << z <<")\",xlabel=\"("<<pre[v]<<","<<post[v]<<")\",fillcolor=\"cyan\",style=filled];\n";			
	}
	output << "\t" << next[_i-1] << "[fillcolor=\"yellow\",style=filled];\n";
	output << "\t74[fillcolor=\"skyblue\",style=filled];\n";
	//canh
	for(int i = 0 ; i < _i ; ++i)
	{
		short v = res[i];
		short u = next[i];
		output << "\t" << v << "->" << u << "[fillcolor = \"red\",color = \"red\"];\n";
	}
	output << "}";
	output.close();

//ve do thi vao file Full_Graph3.dot

	output.open("Full_Graph3.dot" , ios::in | ios::out | ios::trunc);
	output << "digraph Full\n{\n";
	for(short v = 0 ; v < 1075 ; ++v)
	{
		short x = v / 100 , y = (v % 100) / 10 , z = v % 10;
		if(exist[v] && visited[x][y][z])
		if(colored[x][y][z] == 0)
			output << "\t" << v << "[label=\"(" << x << "," << y << "," << z <<")\",xlabel=\"("<<pre[v]<<","<<post[v]<<")\"];\n";
		else
			output << "\t" << v << "[label=\"(" << x << "," << y << "," << z <<")\",xlabel=\"("<<pre[v]<<","<<post[v]<<")\",fillcolor=\"cyan\",style=filled];\n";			
	}
	//dinh (0,7,4) mau do vi e thich the =))
	output << "\t74[fillcolor=\"skyblue\",style=filled];\n";
	for(int v = 0 ; v < 1075 ; ++v)
	{
		short x = v / 100 , y = (v % 100) / 10 , z = v % 10;
		if(exist[v] && visited[x][y][z])
		{
			for(char i = 0 ; i < 6 ; ++i)
			{
				if(adj[x][y][z][i]) output << "\t" << v << "->" << adj[x][y][z][i] << ";\n";
			}			
		}
	}
	for(int i = 0 ; i < _i ; ++i)
	{
		short v = res[i];
		short u = next[i];
		output << "\t" << v << "->" << u << "[fillcolor = \"red\",color = \"red\"];\n";
	}
	output << "}";
	output.close();
	return 0;
}
