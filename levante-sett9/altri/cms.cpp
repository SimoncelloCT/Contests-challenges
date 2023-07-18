//
//  main.cpp
//  CMS
//
//  Created by Simone Scionti on 24/05/18.
//  Copyright © 2018 Mobo. All rights reserved.
//



#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#define dim 100
using namespace std;

class Passegero{
public:
    int prenotato;
    int occupato;
    Passegero(){
        prenotato = -1;
        occupato = -1;
    }
    Passegero(int p, int o){
        prenotato = p;
        occupato = o;
    }
    Passegero(int p){
        prenotato = p;
        occupato = -1;
    }
    
}
class Treno{
public:
    vector<int> posti;
    int nPosti;
    int spostamenti;
    void remove(int index){ //rimouove la persona seduta nel posto.
        posti.erase(posti.begin()+index);
    }
    void insert(Passeggero p){
        
    }
    Treno(int nPosti){
        this->nPosti = nPosti;
        spostamenti = 0;
    }
    printTreno(){
        cout<<"{ ";
        for(int i = 0; i<a.size();i++){
            cout<<posti[i]<<" ";
        }
        cout<<"}"<<endl;
    }
    
}


int main(){
    fflush(stdout);
    ifstream file;
    file.open("./input.txt");
    ofstream out;
    out.open("output.txt");
    for(int i = 0; i<dim; i++){
        cout<<"riga: "<<i+1<<endl;
        int n,m;
        file>>n;//posti
        file>>m;//coppie
        Treno t(n);
        for(int j=0; j<m;j++){
            char azione; //insert-remove
            int actIndex;
            file>>azione;
            file>>actIndex;
            /*if(azione=='b') insert();
            else remove(actIndex);*/
        }
        
        //cout<<t.spostamenti<<endl;
        //out<<t.spostamenti<<endl;
    }
    file.close();
    out.close();
    return 0;
}




