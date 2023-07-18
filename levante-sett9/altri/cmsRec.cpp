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
#define dim 3
using namespace std;

void print(vector<int> a);

class Node{
public:
    int coppia[2];
    Node(){
        coppia[0] = -1;
        coppia[1] = -1;
    }
    void printNode(){
        cout<<"{"<<coppia[0]<<","<<coppia[1]<<"}"<<"  ";
    }
};
void printV(vector<Node> v);
void findRoute(Node now, vector<Node> w, int t, int n, int passi, int &bestConf);

int main(){
    fflush(stdout);
    ifstream file;
    file.open("./input2.txt");
    ofstream out;
    out.open("output1.txt");
    for(int i = 0; i<dim; i++){
        cout<<"riga: "<<i+1<<endl;
        int n,m,t;
        file>>n;
        file>>m;
        file>>t;
        vector <Node> v;
        for(int j=0; j<m;j++){
            v.push_back(Node());
            int a,b;
            file>>a;
            file>>b;
            v[j].coppia[0] = a;
            v[j].coppia[1] = b;
        }
        int best = INT_MAX;
        vector<Node> w = v;
        for(int i = 0 ; i<v.size(); i++){
            if(v[i].coppia[0] == 0){
                Node tmp = w[i];
                w.erase(w.begin()+i);
                findRoute(tmp,w,t,n,1,best);
            }
            else if(v[i].coppia[1] == 0){
                    Node tmp = Node();
                    tmp.coppia[0] = w[i].coppia[1];
                    tmp.coppia[1] = w[i].coppia[0];
                    w.erase(w.begin()+i);
                    findRoute(tmp,w,t+1,n,t+1,best);
            }
            w = v;
        }
        if(best == INT_MAX) best = -1;
        cout<<best<<endl;
        out<<best<<endl;
    }
    file.close();
    out.close();
    return 0;
}
void invert(vector<Node> &v){
    for(int i = 0; i<v.size(); i++){
        int tmp = v[i].coppia[0];
        v[i].coppia[0] = v[i].coppia[1];
        v[i].coppia[1] = tmp;
    }
}

void findRoute(Node now, vector<Node> w, int t, int n, int passi, int &bestConf){
    if(now.coppia[1] == n-1){ //caso base principale abbiamo finito
        if(passi < bestConf) {bestConf = passi;}
        return;
    }
    if(passi >= bestConf) return;
    vector<Node> newW = w;
    if(t == passi) {  invert(w);}

    if(passi<t){ //provo aspettando l'alta marea
        passi  = passi + (t-passi); //arriva l'alta marea
        findRoute(now,newW, t, n, passi,bestConf);
    }
    
    for(int i = 0; i<w.size() ;i++){
        if(newW[i].coppia[0] == now.coppia[1]) {
            Node tmp = w[i];
            newW.erase(newW.begin()+i);
            findRoute(tmp, newW, t, n, passi+1,bestConf);
        }
        newW = w;
    }
}


void print(vector<int> a){
    cout<<"{ ";
    for(int i = 0; i<a.size();i++){
        cout<<a[i]<<" ";
    }
    cout<<"}"<<endl;
}
void printV(vector<Node> v){
    for(int i = 0; i< v.size(); i++) v[i].printNode();
        
}
