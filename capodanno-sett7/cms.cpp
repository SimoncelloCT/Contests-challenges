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

class Invito{
public:
    int start, durata, end;
    Invito(int start, int durata){
        this->start = start;
        this->durata = durata;
        this->end = durata+start;
    }
    
    void printInvito(){
        cout<<"(start: "<<start<<" durata: "<<durata<<" end: "<<end<<" )"<<endl;
    }
    
};
class Giornata{
private:
    vector<Invito> workVec;
public:
    vector<Invito> vec;
    int ore;
    int oreCalc;
    int oreRimanenti;
    Giornata(){
        ore = 0;
        oreCalc = 0;
        oreRimanenti = INT_MAX;
        
    };
    Giornata(int ore){
        this->ore = ore;
        oreCalc = 0;
        oreRimanenti = INT_MAX;
    }
    void removeUselessInvite();
    void findHoursCombinations(vector <Invito> A,vector<Invito> B, int oreImp, int oreDisp);
    void removeTouchInvite();
    void printVec(){
        cout<<"{ ore a disposizione: "<<ore<<endl;;
        for(int i = 0; i<vec.size(); i++){
            vec[i].printInvito();
            cout<<" ";
        }
        
        cout<<endl<<"}"<<endl;
    }
    bool touch(Invito a, Invito b){
        if( (a.end > b.start && a.end <= b.end) || (b.end > a.start && b.end <= a.end)) return true;
        return false;
    }
    bool touch(Invito a, vector<Invito> b){
        bool touched =  false;
        for(int i = 0; i< b.size(); i++){
            if(touch(a,b[i])) touched = true;
        }
        return touched;
    }
    void printWorkVec(){
        cout<<"{ ore a disposizione: "<<ore<<" ,ore impegnate: "<<oreCalc<<endl;;
        for(int i = 0; i<workVec.size(); i++){
            workVec[i].printInvito();
            cout<<" ";
        }
        
        cout<<endl<<"}"<<endl;
    }
};

int main(){
    fflush(stdout);
    ifstream file;
    int n[dim];
    Giornata giornate[dim];
    file.open("./input.txt");
    ofstream fout;
    fout.open("output.txt");
    for(int i = 0; i<dim;i++){
        cout<<endl<<"riga n. "<<i<<endl;
        file>>n[i]; //numero di inviti in questa riga
        int numOre;
        file>>numOre;
        giornate[i] = Giornata(numOre);
        for(int j=0; j<n[i];j++){ //inserimento
            int start ,durata;
            file>>start;
            file>>durata;
            Invito obj = Invito(start,durata);
            giornate[i].vec.push_back(obj);
        }
       // giornate[i].printVec();
        giornate[i].removeUselessInvite();
       // giornate[i].printWorkVec();
        for(int j = 0; j<giornate[i].vec.size();j++){
          //  cout<<"chiamata ciclo main"<<endl;
            vector<Invito> A;
            vector<Invito> vec = giornate[i].vec;
            Invito obj = vec[j];
            A.push_back(obj);
            vec.erase(vec.begin()+j);
            int oreImp = giornate[i].oreCalc + obj.durata;
            int oreDisp = giornate[i].ore - obj.durata;
            giornate[i].findHoursCombinations(A,vec,oreImp,oreDisp);
            
        }
        fout<<giornate[i].oreRimanenti<<endl;
        cout<<giornate[i].oreRimanenti<<endl;
       
    }
    file.close();
    fout.close();
    return 0;
}


void Giornata::removeUselessInvite(){
    workVec = vec;
    oreCalc += workVec[0].durata;
    ore -= workVec[0].durata;
    vector<int> pos;
    for(int i = 1; i< workVec.size();i++){
        if(touch(workVec[0],workVec[i])) pos.push_back(i);
    }
    for(int i = 0; i< pos.size();i++){
        workVec.erase(workVec.begin()+pos[i]-i);
    }
    workVec.erase(workVec.begin());
    vec = workVec;
}

void Giornata::findHoursCombinations(vector <Invito> A,vector<Invito> B, int oreImp, int oreDisp){
    
   
    
    
   
    vector<Invito>:: iterator it = B.begin();
   
    while(it != B.end()){
        vector<Invito> newA = A;
        vector<Invito> newB = B;
        int newDisp = oreDisp;
        int newImp = oreImp;
        if(!touch(*it,A)){
            //cout<<"non si toccano con:  ";
            //it->printInvito();
            //cout<<endl;
            if(oreDisp - it->durata >= 0){
                newImp+= it->durata;
                newDisp-= it->durata;
                //cout<<"oreDisp: "<<oreDisp<<endl;
                newA.push_back(*it);
                newB.erase(newB.begin()+distance(B.begin(),it)); // elimino l'elemento che ho preso
                findHoursCombinations(newA,newB,newImp,newDisp);
                it++;
            }
            else it = B.erase(it); //sforo se lo prendo quindi lo elimino in questo caso
        }
        else{
           // cout<<"elimino l'invito "<<i<<endl;
            it = B.erase(it);
            //cout<<"postErase n= "<<n<<endl;
        }
        
    }
    
    if(B.size() == 0) {
       // cout<<"n == 0"<<endl;
        if(oreRimanenti > oreDisp) oreRimanenti = oreDisp;
       // cout<<"caso base con oreDisp:"<<oreDisp<<endl;
        return;
        
    }
}



