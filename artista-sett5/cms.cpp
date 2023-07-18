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
#define dim 1
using namespace std;

struct conf{
    int i;
    int j;
    int cof;
    bool ok;
    
};
struct object{
    int a,b,c;
};

void combinations(object *vet, int n, vector <conf> & ret);
bool canPutInside(object el1,object el2);
int findRoute(vector <conf> &v, vector<conf>  ret);


int main(){
    fflush(stdout);
    ifstream file;
    int n[dim];
    object* vec[dim];
    int i=0;
    file.open("./input.txt");
    ofstream out;
    out.open("output.txt");
    while(i<dim){
        cout<<endl<<"riga n. "<<i<<endl;
        file>>n[i];
        vec[i] = new object[n[i]];
        for(int j=0; j<n[i];j++){
            file>>vec[i][j].a;
            file>>vec[i][j].b;
            file>>vec[i][j].c;
        }
        
        //chiamo il combinations
        vector <conf> indexConf;
        combinations(vec[i], n[i], indexConf);
        /*for(int o = 0; o< indexConf.size();o++){
            cout<<indexConf[o].i<<"X"<<indexConf[o].j<<" i: "<<o<<endl;
        }*/
        
        
        vector<conf> ris;
        int max = 0;
        for(int o = 0; o< indexConf.size();o++){
            if(indexConf[o].ok){
               // cout<<"ricomincio con indici "<<indexConf[o].i<<"X"<<indexConf[o].j<<endl;
                ris.clear();
                ris.push_back(indexConf[o]);
                ris[0].cof = 2;
                //int start = 2;
                int val = findRoute(indexConf,ris);
                if(val > max) max = val;
            }
        }
        
        /*cout<<"post"<<endl;
        for(int p = 0; p< indexConf.size();p++){
            cout<<p<<") ok"<< indexConf[p].ok <<endl;
        }*/

        out<<max<<endl;
        cout<<max<<endl;
        cout<<endl;
        i++;
    }
   

    
    file.close();
    out.close();
    return 0;
}
bool canContains(object el1,object el2){
    if(el1.a > el2.a)
        if(el1.b > el2.b)
            if(el1.c > el2.c) return true;
            else return false;
        else return false;
    else return false;
    
}
void combinations(object *vet, int n, vector <conf> &ret){
    
    for(int i = 0; i<n;i++){
        for(int j = i+1; j<n;j++){
            if(canContains(vet[i],vet[j])) {
                conf * elem = new conf;
                elem->i = i;
                elem->j = j;
                elem->ok = true;
                ret.push_back(*elem);
                
            }
            else if(canContains(vet[j],vet[i])){
                conf * elem = new conf;
                elem->i = j;
                elem->j = i;
                elem->ok = true;
                ret.push_back(*elem);
            }
        }
    }
}

int findRoute(vector <conf> & v, vector<conf>  ret){
    
    int max = 2;
    do{
        vector<conf> newRet;
        for(int j = 0; j<ret.size();j++){
            for(int i = 0; i<v.size();i++){
                    if(ret[j].j == v[i].i){
                        v[i].cof = ret[j].cof+1;
                        newRet.push_back(v[i]);
                        max = v[i].cof;
                        v[i].ok = false;
                }
            }
        }
       
        ret.clear();
        ret = newRet;
    }while(ret.size() != 0);
    return max;
}

