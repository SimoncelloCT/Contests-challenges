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
int getMinCombination(vector<int> vec);
struct greater{
    template<class T>
    bool operator()(T const &a, T const &b) const { return a > b; }
};


int main(){
    fflush(stdout);
    ifstream file;
    int n[dim];
    int* vec[dim];
    int i=0;
    file.open("./input.txt");
    while(i<dim){
        file>>n[i];
        vec[i] = new int[n[i]];
        for(int j=0; j<n[i];j++){
            file>>vec[i][j];
        }
        i++;
    }
    ofstream out;
    out.open("output.txt");
    
    for(int i = 0; i<dim;i++){
        vector <int> v = vector <int>(vec[i], vec[i] + n[i]);
        int ris = getMinCombination(v);
        out<<ris<<endl;
        cout<<ris<<endl;
    }
    file.close();
    out.close();
    return 0;
}

int getMinCombination(vector<int> vec){
    
    
    sort(vec.begin(), vec.end(), greater<int>());
    int sec,c,i;
    sec = c = i = 0;
    int minA = vec[vec.size()-1];
    int minB = vec[vec.size()-2];
    while(c<(vec.size()/2)-1){
        int add = minA+(minB * 2)+vec[i];
        sec+=add;
        i+=2;
        c+=1;
    }
    if(vec.size()%2 == 0 && vec.size() != 2) sec+=minB;
    if(vec.size()==3 || (vec.size()%2 == 1 && vec.size() != 1)){
        int add = minA+minB+vec[i];
        sec+=add;
    }
    if(vec.size() == 2) sec+=minB;
    if(vec.size() == 1) sec+=vec[i];
    return sec;
    
    
}

