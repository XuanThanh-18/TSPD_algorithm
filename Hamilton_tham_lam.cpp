#include<bits/stdc++.h>

using namespace std;

void readFile(int **c, int n, ifstream &f){
	for( int i = 0; i < n; i++)
		for( int j = 0; j < n; j++){
			f>> c[i][j];
		}
}

void greedy_tsp(int **c, int n, int *nut, int *PA, int &sum){
	int min;
	
	int current_city = 0;
	
	int nearest_city;
	
	for(int i=1; i<n; i++){
		min = INT_MAX;
		for(int j=1; j<n; j++){
			if (!nut[j] && c[current_city][j]<min){
				nearest_city = j;
				min = c[current_city][j];
			}  
		}
		sum += min; // Cap nhat tong chieu dai quang duong
		nut[nearest_city] = 1; // Danh dau thanh pho da duoc tham
		PA[i] = nearest_city+1; // Cap nhat thanh pho vao duong di
		current_city = nearest_city;
	}
	sum += c[PA[n-1]-1][0]; // Tinh them quang duong nguoi giao hang quay lai
}

void print(int *PA, int n, int min){
	cout<<min<<endl;
	for( int i = 0; i<=n; i++) cout<<PA[i]<<" ";
}

int main(){
	clock_t start, end;   // Khai báo bi?n th?i gian
    double time_use;  
    start = clock();
	int n;
	ifstream f("Test_ct_Hamilton_vet_can.txt", ios::in);
	f>> n;
	// Khai bao mang c dong 2 chieu 
	int **c;
	c = new int *[n];
	for( int i = 0; i < n; i++) c[i] = new int[n];
	// Doc File
	readFile(c, n, f);
	f.close();
	
	int *nut = new int[n]{0}; // Khoi tao mang danh dau nut da di qua
	
	int sum = 0; // Tong quang duong di
	
	int *PA = new int[n+1]{0}; // Khoi tao mang phuong an
	PA[0] = 1; //Phan tu dau tien trong mang PA la thanh pho dau tien
	PA[n] = 1; //Phan tu cuoi cung trong mang PA la thanh pho dau tien, khi nguoi giao hang tro ve
	
	greedy_tsp(c, n, nut, PA, sum);

	print(PA, n, sum);
	end = clock();  // ket thuc
    time_use = (double)(end - start) / CLOCKS_PER_SEC;    
    cout<<"\nThoi gian chay: "<<time_use;
	return 0;
}
