#include <iostream>
#include <fstream>
using namespace std;


void countingSort(int *A, int n,fstream &out);

int findMax(int *A, int n);
int findMin(int *A,int n);

int main(){
	fstream in;
	fstream out;
	in.open("./input.txt");
	out.open("./output.txt" , ios::out);
	
	for(int i=0; i<100;i++){
		int n; 								
		in>>n;
        int A[n];
        for(int j=0; j<n;j++ ){
            int v;
            in>>v;
            A[j] = v;
           
        }
         countingSort(A,n, out);
	}
	in.close();
	out.close();
	return 0;
}

void countingSort(int *A, int n, fstream &out){
    int max =  findMax(A,n);
    int min = findMin(A,n);
    int range = max-min+1; // salvo range di variabilità
    int C[range]; // dichiaro l'array C
    for(int i = 0; i<range; i++) C[i] = 0; // inizializzo C
    for(int i = 0; i<n; i++) C[A[i]-min]++; //incremento le posizioni in C, sulla base dei valori in A
    for(int i = 1; i< range;i++)C[i] += C[i-1]; //sommo con il precedente, partendo da 1
    int B[n];
    for(int i = 0; i< n;i++) B[i] = 0;
    //costruisco B
    for(int i = n-1; i >= 0; i--){ // DA RICORDARE
        B[C[A[i]-min]-1] = A[i];
        C[A[i]-min]--;
    }
    for(int j = 0; j< range;j++){ //stampo C
        out<<C[j]<<" ";
    }
    for(int j = 0; j< n;j++){ //stampo B
        out<<B[j]<<" ";
    }
    out<<endl;
}
int findMax(int *A, int n){
    int max = A[0];
    for(int i = 0; i <n;i++){
        if (A[i] > max) max =  A[i];
    }
    //cout<<max<<endl;
    return max;
    
}
int findMin(int *A,int n){
    int min = A[0];
    for(int i = 0; i <n;i++){
        if (A[i] < min) min =  A[i];
    }
    //cout<<min<<endl;
    return min;
    
}

