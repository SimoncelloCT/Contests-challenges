//
//  main.cpp
//  lez5C.cpp
//
//  Created by Simone Scionti on 10/04/18.
//  Copyright © 2018 Mobo. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#define dim 100
using namespace std;
int BubbleSort(int A[], int n);
void print(int A[], int n);

int main(){
    fflush(stdout);
    ifstream file;
    int n[dim];
    int* vec[dim];
    int i=0;
    file.open("./input.txt");
    ofstream out;
    out.open("output.txt");
    while(i<dim){
        cout<<endl<<"riga n. "<<i<<endl;
        file>>n[i];
        vec[i] = new int[n[i]];
        for(int j=0; j<n[i];j++){
            file>>vec[i][j];
        }
        //print(vec[i],n[i]);
        int c = BubbleSort(vec[i], n[i]);
        out<< c<<endl;
        i++;
    }
   

    
    file.close();
    out.close();
    return 0;
}

int BubbleSort(int array[], int elemN){
    int cons = 0;
    int alto;
    for (alto = elemN - 1; alto > 0; alto-- )
    {
        for (int i=1; i<alto; i++)
        {
            if (array[i-1]>array[i+1])
            {
                cons++;
                int tmp = array[i-1];
                array[i-1] = array[i+1];
                array[i+1] = tmp;
            }
        }
    }
    return cons;
}
/*
int BubbleSort(int A[], int n){
    int cons = 0;
    for(int i = 1; i<n-1; i++){
        if(A[i-1] > A[i+1]){
            int tmp =  A[i+1];
            A[i+1] = A[i-1];
            A[i-1] = tmp;
        cons++;
        }
    }
    return cons;
}
*/
void print(int A[], int n){
    cout<<"{";
    for(int i = 0; i<n; i++){
        cout<<A[i]<<" ";
    }
    cout<<"}"<<endl;
}

