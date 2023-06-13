#include<bits/stdc++.h>
#include<fstream>
#include<climits> 
using namespace std;

void readFile(int **c, int n, ifstream &f){
	for( int i = 0; i < n; i++)
		for( int j = 0; j < n; j++){
			f>> c[i][j];
		}
}

void update_PA(int *PA, int *tv_tt, int n){
	for(int i = 0; i < n; i++) PA[i] = tv_tt[i];
}


void nhanh_can(int **c, int *nut, int vt, int d, int n, 
int duongdi, int &min, int *PA, int *tv_tt){
	nut[vt] = 1;
	d++;
	if (d == n){
		if (duongdi + c[0][vt] < min){
			min = duongdi + c[0][vt];
			update_PA(PA, tv_tt, n);
		}
	}
	else{
		for( int i = 0; i < n; i++){
			if (nut[i] == 0){
				tv_tt[d] = i;
				duongdi += c[i][vt];				
				if (duongdi < min) nhanh_can(c, nut, i, d, n, duongdi, min, PA, tv_tt);				
//				cout<<"nhanhcan(c, nut, "<<i<<", "<<d<<", "<<n<<", "<<duongdi<<", "<<min<<", "<<CD<<")"<<endl;
				duongdi -= c[i][vt];
				nut[i] = 0;
			}
		}	
	}
}

void print(int *PA, int n, int min){
	cout<<min<<endl;
	for( int i = 0; i<=n; i++) cout<<PA[i]+1<<" ";
}

int main(){
	
	const int numMeasurements = 30; // Number of measurements to take
	

	
	// Measure the running time multiple times
 //   for (int i = 0; i < numMeasurements; ++i) {
    	
    int n;
	ifstream f("Test_ct_Hamilton_vet_can.txt", ios::in);
	f>> n;
	clock_t start, end;   // Khai báo bi?n th?i gian
    double time_use;  
    start = clock();
	// Khai bao mang c dong 2 chieu 
	int **c;
	c = new int *[n];
	for( int i = 0; i<n; i++) c[i] = new int[n];
	// Doc File
	readFile(c, n, f);
	f.close();
	
	int *nut = new int[n]{0};
	int *tv_tt = new int[n]{0};
	tv_tt[0] = 0;
	int *PA = new int[n+1]{0};
	PA[n] = 0;
	
	int TGT = 0, CD = 0, GTNN_TT = INT_MAX;
	int min = INT_MAX;
	
	nhanh_can(c, nut, 0, 0, n, 0, min, PA, tv_tt);
	
	cout<<min<<endl;
	end = clock();  // ket thuc
    time_use = (double)(end - start) / CLOCKS_PER_SEC;    
    cout<<"\nThoi gian chay: "<<time_use;
	
	return 0;
}
