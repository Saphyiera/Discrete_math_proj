#include <iostream>
#include <list>
#include <fstream>
#include <sstream>

using namespace std;
//ham to mau
void vertex_coloring(int dinh , int * color , list<int> * canhke , int maxcolor)
{
	for(int i = dinh ; i > 0 ; -- i) //to tu cuoi len dau
	{
		if(!color[i]) // dinh chua to mau
		{
			bool mau_da_to[maxcolor + 1]= {0} ; //mang danh dau mau da to
			//duyet cac dinh ke
			for(list<int>::iterator it = canhke[i].begin() ; it != canhke[i].end() ; ++it)
			{
				if(color[*it]) mau_da_to[color[*it]] = true;
				//danh dau mau da to cua cac dinh ke voi dinh dang xet
			}
			for(int j = 1 ; j <= maxcolor ; ++j)
			{
				if(mau_da_to[j] == false) //gan mau chua to be nhat cho dinh dang xet
				{
					color[i] = j;
					break;
				}
			}
			//to mau cac canh ke
			for(list<int>::iterator it = canhke[i].begin() ; it != canhke[i].end() ; ++it)
			{
				if(!color[*it])
				{
					bool mau_da_to[maxcolor + 1];
					for(int j = maxcolor ; j > 0 ; --j)		mau_da_to[j] = false;	
					for(list<int>::iterator it1 = canhke[*it].begin() ; it1 != canhke[*it].end() ; ++it1)
					{
						if(color[*it1]) mau_da_to[color[*it1]] = true;
					}
					for(int j = 1; j <= maxcolor ; ++j)
					{
						if(!mau_da_to[j])
						{
							color[*it] = j;
							break;
						}
					}
				}
			}
		}
	}
}


int main(){
	int dinh, canh;
	//nhap dinh, canh tu file dothi.txt?
	fstream input;
	input.open("dothi.txt",ios::in|ios::out|ios::app);
	string s;
	int temp;
	getline(input,s);
	stringstream ss(s);
	ss>>temp; dinh = temp;
	ss>>temp; canh = temp;
	int dscanh[canh][2];	//mang ghi danh sach canh
	int deg[dinh + 1] = {0};	//mang ghi bac cua dinh
	int color[dinh + 1] = {0};	//mang ghi mau to cho dinh color[i] = 0 -> chua to mau
	string dsmau[30] ={"none","red","lavender","azure","coral","blue","blueviolet","brown","burlywood",
	"cadetblue","cadetblue1","chartreuse","chocolate","bisque","cornflowerblue","cornsilk","yellow",
	"orchid","darkgoldenrod1","darkolivegreen1","grey","deeppink","cyan","white",
	"turquoise","royalblue","navy","lawngreen","aqua","seashell"};
	//ds mau
	bool chinhquy = true;
	list<int> canhke[dinh + 1];	//danh sach canh cua moi dinh
	int k, maxcolor;
	
	for(int i = 0 ; i < canh ; ++i)
	{
		//nhap canh tu file
		getline(input,s);
		stringstream sss(s);
		sss>>temp; dscanh[i][0] = temp;
		sss>>temp; dscanh[i][1] = temp;
		++deg[dscanh[i][0]];	++deg[dscanh[i][1]];	//tang deg cua cac dinh cua canh len 1
		canhke[dscanh[i][0]].push_back(dscanh[i][1]);
		canhke[dscanh[i][1]].push_back(dscanh[i][0]);
	}

	//kiem tra do thi chinh quy
	for(int i = 1 ; i < dinh ; ++i)
	{
		if(deg[i] != deg[i+1]) 
		{
			chinhquy = false;
			break;
		}
	}
	//xd k = sac so cua do thi
	k = deg[0];
	for(int i = 1 ; i < dinh + 1 ; ++i)		k=deg[i]>k?deg[i]:k;
	
	if(chinhquy) maxcolor = k + 1;
	else maxcolor = k;
	vertex_coloring(dinh,color,canhke,maxcolor);
	fstream output;
	output.open("dothitomau.dot",ios::trunc|ios::in|ios::out);
	output<<"graph dothi\n{\n";
	for(int i=dinh;i>0;--i)
	{
		output<<"\t"<<i<<" "<<"[fillcolor="<<"\""<<dsmau[color[i]]<<"\", "<<"style=filled];\n";
	}
	for(int i = 0 ; i < canh ; ++i)
	{
		output<<"\t"<<dscanh[i][0]<<" -- "<<dscanh[i][1]<<";\n";
	}
	output<<"}";
	output.close();
	
	return 0;
}
