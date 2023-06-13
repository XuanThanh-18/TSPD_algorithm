//#include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#include <chrono>
#include<climits> 
using namespace std;

void readFile(int **c, int n, ifstream &f){
	for( int i = 0; i < n; i++)
		for( int j = 0; j < n; j++){
			f>> c[i][j];
		}
}

void update_PA(int *PA, int *tv_tt, int n){
	for( int i = 0; i < n; i++) PA[i] = tv_tt[i];
}

void vet_can(int **c, int *nut, int vt, int duongdi, int d, int &min, int n, int *tv_tt, int *PA){
	nut[vt] = 1; 
	d++;
	if (d == n){
		if (duongdi + c[0][vt] < min){
			min = duongdi + c[0][vt];
			update_PA(PA, tv_tt, n);
		}
	}
	else{
		for( int i = 1; i < n; i++){
			if (nut[i] == 0){
				tv_tt[d] = i;
				duongdi += c[vt][i];
//				cout<<duongdi<<endl;
//				cout<<"vet_can(c, nut, "<<i<<", "<<duongdi<<", "<<d<<", "<<min<<", "<<n<<")"<<endl;
				vet_can(c, nut, i, duongdi, d, min, n, tv_tt, PA);
				duongdi -= c[vt][i];
				nut[i] = 0;
			}
		}
	}	
}

void print(int *PA, int n, int min){
	cout<<min<<endl;
	for( int i = 0; i < n+1; i++) cout<<PA[i]+1<<" ";
}

int main(){
	
//	auto start = std::chrono::high_resolution_clock::now();
	
	int n;
	ifstream f("Test_ct_Hamilton_vet_can.txt", ios::in);
	f>> n;
	// Khai bao mang c dong 2 chieu 
	int **c;
	c = new int *[n];
	for( int i = 0; i<n; i++) c[i] = new int[n];
	// Doc File
	readFile(c, n, f);
	f.close();
	
	int *nut = new int[n]{0}; // Khoi tao mang danh dau nut da di qua
	int *tv_tt = new int[n]{0};  // Khoi tao mang truy vet tam thoi
	tv_tt[0] = 0; // Phan tu dau tien trong mang truy vet tam thoi la diem 1
	int *PA = new int[n+1]{0}; // Khoi tao mang phuong an
	
	int min = INT_MAX; 
	
	vet_can(c, nut, 0, 0, 0, min, n, tv_tt, PA);

//	auto end = std::chrono::high_resolution_clock::now();
//	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	print(PA, n, min);
	
//	std::cout << "Running time: " << duration.count() << " milliseconds" << std::endl;
	
	return 0;
}













