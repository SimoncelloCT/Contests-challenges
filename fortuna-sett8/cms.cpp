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
void print(vector<int> a);
void findSolution(vector<int> seq, vector<int> amp, vector<int> & ret);
int main(){
    fflush(stdout);
    ifstream file;
    
    
    file.open("./input.txt");
    ofstream out;
    out.open("output.txt");
    for(int i = 0; i<dim; i++){
        cout<<"riga: "<<i+1<<endl;
        int n;
        file>>n;
        vector<int> sequenza;
        for(int j=0; j<2*n;j++){
            int f;
            file>>f;
            sequenza.push_back(f);
        }
        int rotaz = 0;
        file>>rotaz;
        vector<int> ampiezze;
        for(int j = 0; j< rotaz; j++){
            int f;
            file>>f;
            ampiezze.push_back(f);
        }
        vector<int> ris;
        
        
        print(sequenza);
        //print(ampiezze);
        cout<<endl;
        findSolution(sequenza,ampiezze,ris);
        cout<<endl;
        print(ris);
        for(int j=0;j<ris.size();j++){
            out<<ris[j]<<" ";
        }
        out<<endl;
      
    }
    
    
    file.close();
    out.close();
    return 0;
}
void findSolution(vector<int> seq, vector<int> amp, vector<int> & ret){
    vector<int> v = seq;
    for(int i = 0; i<amp.size(); i++){
        int ampiezza = amp[i];
        for(int j = 0;j<ampiezza;j++){
            int last = v.back();
            v.pop_back();
            v.insert(v.begin(),last);
        }
        print(v);
        int m = seq.size()/2;
        vector<int> left;
        vector<int> right;
        left.insert(left.begin(),v.begin(),v.begin()+m);
        right.insert(right.begin(),v.begin()+m,v.end());
        int min = *min_element(left.begin(),left.end());
        int max = *max_element(right.begin(),right.end());
        ret.push_back(min);
        ret.push_back(max);
    }
}

void print(vector<int> a){
    cout<<"{ ";
    for(int i = 0; i<a.size();i++){
        cout<<a[i]<<" ";
    }
    cout<<"}"<<endl;
}


