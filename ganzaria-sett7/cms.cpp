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
#include <deque>
#include <queue>
#define dim 100
using namespace std;
int absV(int a);

class cella{
public:
    cella(){
        this->i = -1;
        this->j = -1;
    }
    cella(int _i,int _j){
        this->i = _i;
        this->j = _j;
    }
    int i,j;
    void printC(){
        cout<<"("<<i<<","<<j<<")"<<endl;
    }
};



class mappa{
public:
    int n;
    int m;
    int **a;
    cella e;
    cella u;
    mappa(){
        n = 0;
        m = 0;
        e = u = cella(-1,-1);
        a = NULL;
    }
    mappa(int _n,int _m){
        this->n = _n;
        this->m = _m;
        a = new int*[_n];
        for(int i = 0; i<_n;i++){
            a[i] = new int[_m];
        }
    }
    void print(){
        for(int i = 0; i<n; i++){
            for(int j = 0; j<m;j++){
                cout<<this->a[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<"e: {i= "<<e.i<<" ,j="<<e.j<<" } u: {i="<<u.i<<" ,j="<<u.j<<"}"<<" "<<endl;
        cout<<endl;
    }
};

void getAllRoutes(mappa map, cella start,int& minDisliv,int dislivello,vector<vector<int> > &disMap);
void printVect(vector<cella> a);
void printIntMat(vector<vector<int> > a);
void findDirections(int (&a)[4],int (&b)[4],cella start, cella end);

int main(){
    fflush(stdout);
    ifstream file;
    
    
    file.open("./input.txt");
    ofstream out;
    out.open("output.txt");
    for(int i = 0; i<dim; i++){
        cout<<"riga: "<<i+1<<endl;
        mappa vec;
        int n,m;
        file>>n;
        file>>m;
        vec = mappa(n,m);
        int x,y;
        file>>x;
        file>>y;
        cella start = cella(x,y);
        file>>x;
        file>>y;
        cella end = cella(x,y);
        vec.e = start;
        vec.u = end;
        for(int j=0; j<vec.n;j++){
            for(int k = 0; k<vec.m;k++){
                file>>vec.a[j][k];
            }
        }
        
        int minDisliv = INT_MAX;
        int dislivello = 0;
        vector<vector<int> > disM( vec.n, vector<int>(vec.m, INT_MAX));
        getAllRoutes(vec, vec.e,minDisliv,dislivello, disM);
        out<<minDisliv<<endl;
        cout<<minDisliv<<endl;
    }
    
    
    file.close();
    out.close();
    return 0;
}


int absV(int a){
    if (a > 0) return a;
    return -a;
}


void getAllRoutes(mappa map, cella start,int& minDisliv,int dislivello,vector<vector<int> > &disMap){
    
    if(start.i == map.u.i && start.j == map.u.j){ // sono arrivato alla fine
        if(dislivello < minDisliv) minDisliv = dislivello;
        return;
    }
    if(disMap[start.i][start.j] <= dislivello){return;}//cout<<"già passato in questa cella con dislivello= "<<disMap[start.i][start.j]<<endl; return;}//inutile continuare nella chiamata.
    disMap[start.i][start.j] = dislivello;
    if(dislivello >= minDisliv) {return;}//cout<<"inutile continuare con dislivello= "<<dislivello<<endl; return;}//inutile continuare nella chiamata.
    int dis = dislivello;
    cella act = cella(start.i,start.j);
    int x[4];
    int y[4];
    findDirections(x,y,start,map.u); // modifica gli array di direzioni
    
    for(int i = 0; i<4;i++){
        cella newC = cella(start.i+x[i],start.j+y[i]);
        if(newC.i >= 0 && newC.i<map.n &&  newC.j >=0 && newC.j< map.m){ //se non sfora
            
            if (map.a[newC.i][newC.j] > map.a[act.i][act.j] ) dis += map.a[newC.i][newC.j] - map.a[act.i][act.j]; // setto il dislivello attuale
           
            getAllRoutes(map,newC,minDisliv,dis,disMap);
            dis = dislivello;
        }
        //else {cout<<"sforo con start: ";newC.printC();}
    }
}

void findDirections(int (&a)[4],int (&b)[4],cella start, cella end){
    int diffRiga = end.i - start.i;
    int diffCol = end.j - start.j;
    if(diffRiga >= 0){ // destinazione più sotto
        if(diffCol >= 0){//destinazione sotto destra
            if(diffRiga > diffCol){ // si trova molto sotto e poco a destra(sotto-destra-sinistra-sopra)
                int x[4]={1,0,0,-1};
                int y[4]={0,1,-1,0};
                memcpy(a,x,4*sizeof(int));
                memcpy(b,y,4*sizeof(int));
                return;
            }
            else{ // si trova molto a destra e poco sotto(destra-sotto-sopra-sinistra)
                int x[4]={0,1,-1,0};
                int y[4]={1,0,0,-1};
                memcpy(a,x,4*sizeof(int));
                memcpy(b,y,4*sizeof(int));
                return;
            }
        }
        if(diffCol < 0){// destinazione sotto sinistra
            if(diffRiga > absV(diffCol)){ // molto sotto e poco a sinistra(sotto-sinistra-destra-sopra)
                int x[4]={1,0,0,-1};
                int y[4]={0,-1,1,0};
                memcpy(a,x,4*sizeof(int));
                memcpy(b,y,4*sizeof(int));
                return;
            }
            else{ // molto a sinistra e poco sotto(sinistra-sotto-sopra-destra)
                int x[4]={0,1,-1,0};
                int y[4]={-1,0,0,1};
                memcpy(a,x,4*sizeof(int));
                memcpy(b,y,4*sizeof(int));
                return;
            }
            
        }
    }
    if(diffRiga < 0){ // si trova sopra
        if(diffCol >= 0){ // si trova sopra a destra
            if(absV(diffRiga) > diffCol){ //molto sopra e poco a destra(sopra-destra-sinistra-sotto)
                int x[4]={-1,0,0,1};
                int y[4]={0,1,-1,0};
                memcpy(a,x,4*sizeof(int));
                memcpy(b,y,4*sizeof(int));
                return;
            }
            else{ // molto a destra e poco sopra(destra-sopra-sotto-sinistra)
                int x[4]={0,-1,1,0};
                int y[4]={1,0,0,-1};
                memcpy(a,x,4*sizeof(int));
                memcpy(b,y,4*sizeof(int));
                return;
            }
        }
        if (diffCol < 0){ // si trova sopra a sinistra
            if(absV(diffRiga) > absV(diffCol)){ //molto sopra e poco a sinistra(sopra-sinistra-destra-sotto)
                int x[4]={-1,0,0,1};
                int y[4]={0,-1,1,0};
                memcpy(a,x,4*sizeof(int));
                memcpy(b,y,4*sizeof(int));
                return;
            }
            else{ // molto a sinistra e poco sopra(sinistra-sopra-sotto-destra)
                int x[4]={0,-1,1,0};
                int y[4]={-1,0,0,1};
                memcpy(a,x,4*sizeof(int));
                memcpy(b,y,4*sizeof(int));
                return;
            }
        }
    }
}






void printVect(vector<cella> a){
    cout<<"{ ";
    for(int i = 0; i< a.size(); i++){
        a[i].printC();
    }
    cout<<"}"<<endl;
}
void printIntMat(vector<vector<int> > a){
    cout<<"{ ";
    for(int i = 0 ; i< a.size(); i++){
        for(int j = 0; j< a[i].size();j++){
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"}"<<endl;
}


