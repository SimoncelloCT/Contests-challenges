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
#include <numeric>

#define dim 100
using namespace std;
void print(vector<int> a);
//void findSolution(vector<int> tagli, int r,vector<int> &ret);
void findSolution(vector <int> tagli , int r, vector<int> & ret, vector<int> v);
bool sforatoOrTrovato(int r, vector<int> v, bool& trovato);
int chiamate  = 0 ;
int main(){
    fflush(stdout);
    ifstream file;
    
    
    file.open("./input.txt");
    ofstream out;
    out.open("output.txt");
    for(int i = 0; i<dim; i++){
        cout<<"riga: "<<i+1<<endl;
        int n,r;
        file>>n;
        file>>r;
        vector<int> tagli;
        for(int j=0; j<n;j++){
            int f;
            file>>f;
            tagli.push_back(f);
        }
        
        vector<int> ris;
        print(tagli);
        sort(tagli.begin(),tagli.end());
        vector<int> t = tagli;
        vector<int> v;
        
        for(int i = 0; i< tagli.size();i++){
            findSolution(t,r,ris,v);
            t.pop_back();
        
        }
        chiamate = 0;

        for(int j=0;j<ris.size();j++){
            out<<ris[j]<<" ";
            cout<<ris[j]<<" ";
        }
        out<<endl;
        cout<<endl;
      
    }
    
    
    file.close();
    out.close();
    return 0;
}

void findSolution(vector <int> tagli , int r, vector<int> & ret, vector<int> v){
    chiamate++;
  //  cout<<"chiamate: " << chiamate<<endl;
    
    if(ret.size() != 0){
        if(v.size() > ret.size()) return;
        if(v.size() != 0){
            
            if( accumulate(v.begin(),v.end()-1 ,0) + (v.back() * ((ret.size() - v.size())+1)) < r) {
               // cout<<"eseguo :" << v.back()<<" * "<<ret.size() <<" - "<< v.size()<<" + "<<accumulate(v.begin(),v.end()-1 ,0)<<endl;
                
                return;
            }
        }
       
    }
    bool trovato = false;
    if(sforatoOrTrovato(r,v,trovato)){
        if(trovato){
            vector<int> t;
            if(ret.size() == 0 || v.size() < ret.size()) {
                t = v;
                sort(t.begin(),t.end());
                ret = t;
            }
            else if(v.size() == ret.size()){
                t = v;
                sort(t.begin(),t.end());
                for(int i = 0; i< v.size(); i++){
                    if(t[i] < ret[i]) {
                        ret = t;
                        break;
                    }
                    else if(v[i] > ret[i]) break;
                }
            }
        }
        else return;
    }
    
    v.push_back(tagli.back());
   
    //print(v);

    vector<int> t = tagli;
    for(int i = 0; i< tagli.size(); i++){
        findSolution(t,r,ret,v);
        t.pop_back();
        
    }
    
}

bool sforatoOrTrovato(int r, vector<int> v, bool& trovato){
   // cout<<"sofratoOrTrovato"<<endl;
    bool sforato = trovato = false;
    while(!sforato && !trovato) {
        int sum = accumulate(v.begin(),v.end(),0);
        if(sum > r) sforato = true;
        else if(sum == r) trovato = true;
        else return false;
    }
    return sforato || trovato;
}

void print(vector<int> a){
    cout<<"{ ";
    for(int i = 0; i<a.size();i++){
        cout<<a[i]<<" ";
    }
    cout<<"}"<<endl;
}


