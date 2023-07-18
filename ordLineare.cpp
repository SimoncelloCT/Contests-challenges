#include <iostream>
#include <fstream>
using namespace std;


int * countingSort(int *A, int n,fstream &out);
int findMax(int *A, int n);
int findMin(int *A,int n);
int main(){
	fstream in;
	fstream out;
	in.open("./input.txt");
	out.open("./output.txt" , ios::out);
	
    for(int i=0; i<100;i++){
        int n;
        string type;
        in>>type;
        in>>n;
        if(type == "bool" || type == "int"){
            int A[n];
            for(int j=0; j<n;j++ ){
                int v;
                in>>v;
                A[j] = v;
            }
            int* B = countingSort(A,n, out);
            //stampo A ordinato
            for(int j = 0; j<n;j++){
                int v = B[j];
                out<<v<<" ";
            }
        }
        else if(type == "double"){
            int A[n];
            for(int j=0; j<n;j++ ){
                float v;
                in>>v;
                float vMult = v*10;
                int val = (int) vMult;
                A[j] = val;
            }
            int* B = countingSort(A,n, out);
            //stampo B ordinato
            for(int j = 0; j<n;j++){
                float v = B[j];
                v = v / 10;
                out<<v<<" ";
            }
        }
        else if(type == "char"){
            int A[n];
            for(int j=0; j<n;j++ ){
                char v;
                in>>v;
                int val = (int) v;
                A[j] = val;
            }
            int* B = countingSort(A,n, out);
            //stampo B ordinato
            for(int j = 0; j<n;j++){
                char c = (char) B[j];
                out<<c<<" ";
            }
        }
        out<<endl;
    }
	in.close();
	out.close();
	return 0;
}

int * countingSort(int *A, int n, fstream &out){
    int max =  findMax(A,n);
    int min = findMin(A,n);
    int offset = max-min+1;
    int C[offset];
    for(int i = 0; i<offset; i++) C[i] = 0;
    for(int i = 0; i<n; i++) C[A[i]-min]++;
    for(int i = 1; i< offset;i++)C[i] += C[i-1];
    int *B =  new int[n];
    for(int i = 0; i< n;i++) B[i] = 0;
    //DA RICORDARE
    for(int i = n-1; i >= 0; i--){
        B[C[A[i]-min]-1] = A[i];
        C[A[i]-min]--;
    }
    for(int j = 0; j< offset;j++){ //stampo C
        out<<C[j]<<" ";
    }
   /* for(int j = 0; j< n;j++){ //stampo B
        out<<B[j]<<" ";
    }*/
    return B;
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

