#include <iostream>
#include <fstream>
using namespace std;
long selectMinDistance(float* vet, int n, int k);
void sorting(long* vet, int n); 

int main(){
    fflush(stdin);
    fflush(stdout);
    ifstream file;
    ofstream out;
    file.open("./input.txt");
    out.open("output.txt");
    int n[10];
    int k[10];
    float* vec[10];
    for(int i = 0; i<10; i++){
        file>>n[i];
        file>>k[i];
        vec[i] = new float[n[i]];
        for(int j=0; j<n[i];j++){
            file>>vec[i][j];
        }
        sorting(vec[i], n[i]);
        
        //float ret = selectMinDistance(vec[i],n[i],k[i]);
        //cout<<ret<<endl;
    }
    
    
    // stampo vedo se è ordinata
    for(int i = 0; i<10; i++){
        for(j = 0; j<n[i]; j++){
            cout<<vet[i][j]<<" ";
        }
        cout<<endl;
    }
    
    
    file.close();
    out.close();
    return 0;
}


void sorting(long* vet, int n){
    int temp, i, j;
    for(i = 0; i <n; i++){
        for(j = 0; j <n-1; j++) {
            if(arr[j] > arr[i]){
                temp = arr[i]; //swap them
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}
    
long selectMinDistance(float* vet, int n,int k){ // k = perquisibili , n = totale locali
    // devo trovare la distanza minima
    long distanza = INT_MAX;
    //int t = k-1;
    int i = 0;
    k = - 1;
    while (k<n){
        if(vet[i] - vet[k] < distanza) distanza =  vet[c] - vet[k];
        k++;
        i++;
    }
    
    
 /*   for(int c = 0; c<n-t; c++){
        for(int i = c; i<k; i++){
            if(vet[c] - vet[k-1] < distanza) distanza =  vet[c] - vet[k-1];
        }
    }*/
    
    
    return distanza;
}
    


