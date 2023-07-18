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
    bool operator==( Passegero const rhs) const { return this->prenotato == rhs.prenotato;}
    
};
class Treno{
public:
    vector<Passegero> posti;
    int nPosti;
    int spostamenti;
    void remove(int index){ //rimouove la persona seduta nel posto.
       // cout<<"RIMUOVO PASSEGGERO "<<index<<endl;
        Passegero p = Passegero();
        posti[index] = p;
    }
    void insert(Passegero p);
    Treno(int nPosti){
        this->nPosti = nPosti;
        spostamenti = 0;
        for(int i = 0; i< nPosti;i++){
            Passegero p;
            posti.push_back(p);
        }
    }
    void printTreno(){
        cout<<"{ ";
        for(int i = 0; i<posti.size();i++){
            cout<<"( ";
            cout<<posti[i].prenotato<<" , "<<posti[i].occupato;
            cout<<" )";
        }
        cout<<"}"<<endl;
    }
    
};



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
            Passegero p(actIndex);
            if(azione=='b') t.insert(p);
            else{
                Passegero p1 = Passegero(actIndex);
                int it = distance(t.posti.begin(), find(t.posti.begin(), t.posti.end(), p1));
                t.remove(it);
            }
        }
       // t.printTreno();
        cout<<t.spostamenti<<endl;
        out<<t.spostamenti<<endl;
    }
    file.close();
    out.close();
    return 0;
}

void Treno::insert(Passegero p){
    bool foundFree  = false;
    bool foundMyPren = false;
    int i = 0;
    while(i < nPosti && !foundFree && !foundMyPren){
        if(posti[i].prenotato == -1) {//posto libero
            foundFree = true;
            posti[i] = p;
            posti[i].occupato = i;
           
            
        }
        else if(i == p.prenotato ){ //c'è qualcuno al mio posto
           // cout<<"c'è qualcuno al mio posto"<<endl;
            
            foundMyPren = true;
            //metto nello stack il passeggero p
            vector<Passegero> stack;
            stack.push_back(p);
            while(stack.size() != 0){
                //printTreno();
                
                int j = stack.back().prenotato;
                //cout<<"posto: "<<j<<endl;
                if(posti[j].prenotato != -1){//è occupato
                    //cout<<"posto occupato"<<endl;
                    Passegero tmp = posti[j];//faccio alzare il passeggero dal mio posto
                    spostamenti++;
                    posti[j] = stack.back(); //mi siedo al mio posto
                    stack.pop_back();
                    //cout<<"stackSize() "<<stack.size()<<endl;
                    posti[j].occupato = j;
                    
                    stack.push_back(tmp);
                    
                }
                else {
                    
                    //cout<<"trovato posto libero "<<endl;
                    posti[j] = stack.back();
                    posti[j].occupato = j;
                    stack.pop_back();
                }
            }
            
            //cout<<"fuori while"<<endl;
            
        }
       
        i++;
    }
    
    
}



