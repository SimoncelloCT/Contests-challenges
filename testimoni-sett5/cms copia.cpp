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

struct indexConf{
    vector<int> map;
    bool isLast;
    
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
void printRis(vector<int> a);
void calculate(vector<int> & A,vector<Testimone> T);
int calc_min(int &f, int &l, vector<int> A);
float calc_med(vector<int> A);
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
        print(vec[i],n[i]); //stampa
        sort(vec[i], vec[i]+n[i], &test_sorter);
        print(vec[i],n[i]);
        //calcolo risultati chiamate
        vector<int> ris;
        vector<Testimone> vet = vector<Testimone>(vec[i],vec[i]+n[i]);
        calculate(ris,vet);
        printRisFile(ris,fout);
        
        
    
    }
   

    
    file.close();
    fout.close();
    return 0;
}

void calculate(vector<int> & A,vector<Testimone> T){
    
    initA(T,A);
    int x, y;
    int initialDMin = calc_min(x,y,A);
    indexConf saved[2];

    while (true){
        //salva i due numeri che tocca,
        if(saved[0].isLast){
            saved[1].map = vector<int>(A);
            saved[0].isLast = false;
            saved[1].isLast = true;
            cout<<"salvo: in saved[1] :";
            printRis(A);
        }
        else{
            saved[0].map = vector<int>(A);
            saved[1].isLast = false;
            saved[0].isLast = true;
            
            cout<<"salvo: in saved[0] :";
            printRis(A);
        }
        
        int i,j;
        int dMin = calc_min(i,j,A);
        cout<<"i: "<<i<<" j: "<<j<<endl;
        printT(T);
        printRis(A);
        float dMed = calc_med(A);
        if(j == A.size()-1){ //sono alla fine
            vector<int> newA = vector<int>(A);
            newA.pop_back();
            int a,b; dMin = calc_min(a,b,newA);
            //cout<<"sono alla fine: "<<A[j]<<"dMin = "<<dMin<<endl;
            A[j] = A[i]+dMin;
            
            while(A[j] > T[j].max) A[j]--;
        }
        else{
            
            int diffBig = T[j].max - A[j];
            int diffMin = A[i] - T[i].min;
            if(diffBig >= diffMin ) A[j]++;
            else A[i]--;
            cout<<"controllo se è una conf salvata questa: ";
            printRis(A);
            /*if((!saved[0].isLast  && saved[0].map == A) ||(!saved[1].isLast && saved[1].map == A)) {
                cout<<"conf salvata"<<endl;
                A[j+1]++;
                return;
                
                
                
            }*/
            
           
        }
        float newMed = calc_med(A);
        int newMin = calc_min(i,j,A);
        if (newMed > dMed && newMin > initialDMin) return; //dovrei aver calcolato la distanza massima possibile tra tutti gli orari.
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
float calc_med(vector<int> A){
    int sum = 0;
    for(int i = 0; i<A.size() - 1;i++){
        sum += A[i+1]-A[i];
    }
    float dMed = (float)sum/A.size();
    return dMed;
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
    return lhs.media < rhs.media;
}
