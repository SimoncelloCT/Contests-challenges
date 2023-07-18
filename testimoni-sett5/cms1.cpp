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
bool conf_sorter(vector<int> const& l, vector<int> const& r );
void printRis(vector<int> a);
class Conf{
public:
    Conf(int min){
        this->min = min;
    }
    int min;
    vector<vector<int> > A;
    void getMinConf(vector<int> & ret){
        sort(A.begin(), A.end(), &conf_sorter);
        ret = A[0];
    }
    void printConfs(){
        cout<<"min = "<<min<<endl;
        for(int i = 0; i< A.size(); i++){
            cout<<"conf n: "<<i<<endl;
            printRis(A[i]);
            
        }
    }
    
};
class Testimone{
public:
    Testimone(){
        min = 0;
        max = 0;
        media = 0;
    }
    Testimone(int min, int max){
        this->min = min;
        this->max = max;
        this->media = (min+max)/2;
    }
    int min;
    int max;
    int media;
};

void print(Testimone vec[], int n);
bool test_sorter(Testimone const& lhs, Testimone const& rhs);
void calculate(vector<int> & A,vector<Testimone> T);
int calc_min(int &f, int &l, vector<int> A);
void initA(vector<Testimone>T,vector <int> & A);
void printT(vector<Testimone> vec);
void printRisFile(vector<int> a,ofstream &out);


int main(){
    fflush(stdout);
    ifstream file;
    int n[dim];
    Testimone* vec[dim];
    file.open("./input.txt");
    ofstream fout;
    fout.open("output.txt");
    for(int i = 0; i<dim;i++){
        cout<<endl<<"riga n. "<<i<<endl;
        file>>n[i]; //numero di testimoni in questa riga
        vec[i] = new Testimone[n[i]];
        for(int j=0; j<n[i];j++){ //inserimento
            int min ,max;
            file>>min;
            file>>max;
            Testimone obj = Testimone(min,max);
            vec[i][j] = obj;
        }
        //print(vec[i],n[i]); //stampa
        sort(vec[i], vec[i]+n[i], &test_sorter);
        //print(vec[i],n[i]);
        //calcolo risultati chiamate
        vector<int> ris;
        vector<Testimone> vet = vector<Testimone>(vec[i],vec[i]+n[i]);
        calculate(ris,vet);
        //printT(vet);
        printRisFile(ris,fout);
        //cout<<"risultato conf = "<<endl;
        //printRis(ris);
        
        
    
    }
    file.close();
    fout.close();
    return 0;
}

void calculate(vector<int> & A,vector<Testimone> T){
    initA(T,A);
    vector<Conf> conf;
    int maxMin = 0;
    while (true){
        int i,j; int dMin = calc_min(i,j,A);
        if(maxMin < dMin) maxMin = dMin;
        bool found = false;
        for(int k = 0; k<conf.size();k++){
            if(conf[k].min == dMin){ conf[k].A.push_back(A); found = true;}
        }
        if(!found){
            Conf obj = Conf(dMin);
            obj.A.push_back(A);
            conf.push_back(obj);
        }
        
        int diffBig = T[j].max - A[j];
        
        
        if(diffBig > 0) A[j]++;
        else{
            for(int k = 0; k<conf.size(); k++){
                if(conf[k].min == maxMin){
                    //conf[k].printConfs();
                    conf[k].getMinConf(A);
                    return;
                }
            }
        }
    }
}





void initA(vector<Testimone>T,vector <int> & A){
    for(int i = 0; i< T.size();i++){
        A.push_back(T[i].min);
    }
}
int calc_min(int &f, int &l, vector<int> A){
    int dMin = INT_MAX;
    f = l = 0;
    for(int i = 0; i< A.size()-1;i++){
        if((A[i+1]-A[i]) < dMin) {
            dMin = A[i+1]-A[i];
            f = i;
        }
    }
    l = f+1;
    return dMin;
    
}

void print(Testimone vec[], int n){
    cout<<"{ ";
    for(int i =0; i<n; i++){
        cout<<"("<<vec[i].min<<","<<vec[i].max<<")"<<" ";
    }
    cout<<"}"<<endl;
    
}
void printT(vector<Testimone> vec){
    cout<<"{ ";
    for(int i =0; i<vec.size(); i++){
        cout<<"("<<vec[i].min<<","<<vec[i].max<<")"<<" ";
    }
    cout<<"}"<<endl;
    
}
void printRis(vector<int> a){
    cout<<"{ ";
    for(int i = 0; i< a.size();i++){
        cout<<a[i]<<" ";
    }
     cout<<"}"<<endl;
}
void printRisFile(vector<int> a,ofstream & out){
    
    for(int i = 0; i< a.size();i++){
        out<<a[i]<<" ";
    }
    out<<endl;
}
bool test_sorter(Testimone const& lhs, Testimone const& rhs) {
    if(lhs.min == rhs.min) {
        return lhs.max < rhs.max;
    }
    return lhs.min < rhs.min;
}
bool conf_sorter(vector<int> const& l, vector<int> const& r ){
    bool cond = true;
    for(int i = 0; i< l.size(); i++){
        if(l[i] > r[i]) cond = false;
    }
    return cond;
}
