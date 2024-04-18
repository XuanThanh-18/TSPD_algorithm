#include<iostream>
#include<math.h>
#include<map>
#include <cstdlib>
#include <ctime>
using namespace std;
int random(int minN, int maxN)
{
	return minN +rand() % (maxN+1-minN);
}
struct diem
{
	float x;
	float y;
};
void toado(diem a[100],int &n)
{
	for(int i=0;i<n;i++)
	{
		cout<<"Nhap diem thu "<<i+1<<" : ";cin>>a[i].x>>a[i].y;
	}
}
void khoangcach(diem a[100],float kc[20][20],int n)
{
	for(int i=0;i<n;i++)
	for(int j=0;j<n;j++)
	{
		kc[i][j]=(float)sqrt(pow(a[i].x-a[j].x,2) + pow(a[j].y-a[i].y,2));
	}
}
void swap(int &a,int&b)
{
	int tg=a;a=b;b=tg;
}
void thichnghi(int **a,float kc[20][20],int fitness[200],int &soluong,int n)
{
	for(int i=0;i<soluong;i++)
	a[i][n]=a[i][0];
	fitness[soluong];
	for(int i=0;i<soluong;i++)
	{
		int s=0,j=0;
		for(int j=0;j<n;j++)
		{
			s+=kc[a[i][j]][a[i][j+1]];
			if(j==n-1)
			{
				s-=kc[a[i][j]][a[i][j+1]];
				s+=kc[a[i][j]][a[i][0]];
			}
		}
		fitness[i]=s;
	}
	// sap xep
	for(int i=0;i<soluong;i++)
	{
		int k=i;
		for(int j=i+1;j<soluong;j++)
		{
			if(fitness[j]<fitness[k]) k=j;
		}
		swap(fitness[k],fitness[i]);
		int tg[n];
		for(int t=0;t<n;t++)
		swap(a[k][t],a[i][t]);
	}
//	for(int i=0;i<n;i++)
//	{
//		for(int j=0;j<n;j++)
//		cout<<a[i][j]<<" ";
//		cout<<endl;
//	}
}
void chonloc(int **a,int fitness[200],int &soluong,int n)
{
	int dem=0.2*soluong;
	int tg=soluong;
	while(dem>0)
	{
		int k=random(tg-2*dem,tg);
		for(int i=k;i<soluong;i++)
		{
			for(int j=0;j<n;j++)
			{
				a[k][j]=a[k+1][j];
			}
		}
		dem--;
		soluong--;
	}
}
void laighep(int **a,int &soluong ,int n)
{
	int cha=random(0,soluong-1);int me;
	do{
		me=random(0,soluong-1);
	}while(cha==me);
	int k=random(1,n-1);
	int tg=0;
//	cout<<cha<<" "<<me<<" "<<k<<endl;
	for(int j=k;j<n;j++)
		{
			a[soluong][tg]=a[me][j];
			tg++;
		}
	int d=0;
	for(int j=0;j<n;j++)
	{
		for(int t=0;t<n-k;t++)
		{
			if(a[cha][j]==a[soluong][t]) break;
			else if(t==n-k-1)
			{
				d++;
				a[soluong][d+t]=a[cha][j];
			}
		}
	}
	soluong++;
}
void dotbien(int **a, int &soluong, int n)
{
	int count=2;
	while(count>0)
	{
		int cha=random(0,soluong-1),k2;
		int k1=random(0,n-1);
		do{
			k2=random(0,n-1);
		}while(k1==k2);
//		cout<<cha<<" "<<k1<<" "<<k2<<endl;
		swap(a[cha][k1],a[cha][k2]);
		count--;
	}
}
int main()
{
	int **a;
	diem b[100];
	a=new int*[200];
	int soluong=200;
	int fitness[soluong];
	int n;cout<<"Nhap so thanh pho: ";
	cin>>n;
//	nhap khoang cach thanh pho
	float kc[20][20];
	toado(b,n);
	khoangcach(b,kc,n);
// 	tao quan the ngau nhien
	srand((int) time(0));
	for(int i=0;i<soluong;i++)
	{
		a[i]=new int[n];
		map<int, bool> vis;
		for(int j=0;j<n;j++)
		{
			do{
				a[i][j]=random(0,n-1);
			}while(vis.find(a[i][j]) != vis.end());
			vis[a[i][j]]= true;
		}
	}
	// giai thuat di truyen
	int dem=0;
	while(dem<100)
	{
		thichnghi(a,kc,fitness,soluong,n);
		chonloc(a,fitness,soluong,n);
		laighep(a,soluong,n);
		dotbien(a,soluong,n);
		dem++;
	}
	thichnghi(a,kc,fitness,soluong,n);
	cout<<"Duong di ngan nhat la: ";
	for(int i=0;i<n;i++)
	cout<<(char)(a[0][i]+65)<<" ";
	cout<<"fitness: "<<fitness[0];
	for(int i=0;i<n;i++)
	delete [] a[i];
	delete[] a;
}
/*
5
0 3 4 2 7
3 0 4 6 3
4 4 0 5 8
2 6 5 0 6
7 3 8 6 0
*/
/*
4
0 3 1 9
3 0 5 1
1 5 0 2
9 1 2 0
*/
/*
20
20 20
20 40
60 80
40 120
20 160
60 200
80 180
100 160
100 120
140 180
180 200
200 160
180 100
140 140
120 80
180 60
200 40
160 20
100 40
60 20
*/
