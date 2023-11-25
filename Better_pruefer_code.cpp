#include <iostream>
#define MAXV 100000

using namespace std;

int main()
{
	int n; cin>>n; //n la so canh cua cay dan nhan tu 0->n
	int v[n][2]={0}; //ma tran luu cac canh cua cay
	int deg[n+1]={0}; //day luu bac cua dinh dinh[0]-->dinh[n]
	int pruefer_code[n-1]; //pruefer code cua cay
	int min,temp;
	//nhap cac canh cua cay
	for(int i=0;i<n;i++)
	{
		cin>>v[i][0]>>v[i][1]; //nhap canh
		deg[v[i][0]]++; //tang bac cua dinh
		deg[v[i][1]]++;
	}
	//sinh pruefer code
	for(int i=0;i<n-1;i++)
	{
		min=MAXV;
		for(int j=0;j<n;j++) //duyet tim canh co deg = 1 nho nhat
		{
			if(deg[v[j][0]]==1&&v[j][0]!=0)
			{
				if(min>v[j][0])
				{
					min=v[j][0];
					temp=j;
				}
			}
			if(deg[v[j][1]]==1&&v[j][1]!=0)
			{
				if(min>v[j][1])
				{
					min=v[j][1];
					temp=j;
				}
			}
		}
		deg[v[temp][0]]--; deg[v[temp][1]]--;
		if (deg[!v[temp][0]])pruefer_code[i]=v[temp][0];
		else pruefer_code[i]==v[temp][1];
	}
	for(int i=0;i<n-1;i++)	cout<<pruefer_code[i]<<" "; //in pruefer code
	return 0;
}
