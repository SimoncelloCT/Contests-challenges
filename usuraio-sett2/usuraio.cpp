#include <iostream>
#include <fstream>
#define dim  100
using namespace std;
long selectMinDistance(long* vet, int n, int k);
void sorting(long* vet, int n); 

int main(){
    fflush(stdin);
    fflush(stdout);
    ifstream file;
    ofstream out;
    file.open("./input.txt");
    out.open("output.txt");
    int n[dim];
    int k[dim];
    long* vec[dim];
    for(int i = 0; i<dim; i++){
        file>>n[i];
        file>>k[i];
        vec[i] = new long[n[i]];
        for(int j=0; j<n[i];j++){
            file>>vec[i][j];
        }
        sorting(vec[i], n[i]);
        
        long ret = selectMinDistance(vec[i],n[i],k[i]);
        out<<ret<<endl;
        cout<<ret<<endl;
    }
    
    
    // stampo vedo se è ordinata
    /*for(int i = 0; i<dim; i++){
        for(int j = 0; j<n[i]; j++){
            cout<<vec[i][j]<<" ";
        }
        cout<<endl;
    }*/
    
    
    file.close();
    out.close();
    return 0;
}


void sorting(long* vet, int n){
    int temp, i, j;
    for(i = 0; i <n; i++){
        for(j = 0; j <n-1; j++) {
            if(vet[j] > vet[i]){
                temp = vet[i]; //swap them
                vet[i] = vet[j];
                vet[j] = temp;
            }
        }
    }
}
    
long selectMinDistance(long* vet, int n,int k){ // k = perquisibili , n
    // devo trovare la distanza minima
    long distanza = INT_MAX;
    int i = 0;
    k = k - 1;
    while (k<n){
        if(vet[k] - vet[i] < distanza) distanza =  vet[k] - vet[i];
        k++;
        i++;
    }
    return distanza;
}
    


