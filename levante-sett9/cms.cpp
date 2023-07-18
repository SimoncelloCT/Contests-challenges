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
void findRoute1(vector<Node> w, bool first, Node now,int t, int n, int passi, int &best);



int main(){
    fflush(stdout);
    ifstream file;
    file.open("./input.txt");
    ofstream out;
    out.open("output.txt");
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
        for(int u = 0 ; u<v.size(); u++){
            if(v[u].coppia[0] == 0){
                Node tmp = w[u];
                w.erase(w.begin()+u);
                    findRoute1(w,true,tmp,t,n,0,best);
                
            }
            else if(v[u].coppia[1] == 0){
                Node tmp = Node();
                tmp.coppia[0] = w[u].coppia[1];
                tmp.coppia[1] = w[u].coppia[0];
                w.erase(w.begin()+u);
                    findRoute1(w,true,tmp,t,n,t,best);
                
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



void findRoute1(vector<Node> w, bool first, Node now,int t, int n, int passi, int & best){
    if(first && passi == t) invert(w);
    //first = false;
    if(now.coppia[1] == n-1) { if(first && passi == t) best = passi; else best = passi+1; return;}
        vector<Node> stack;
        stack.push_back(now);
        passi++;
        while(true){
            if(passi == t) invert(w);
            //printV(stack);
           //cout<<endl;
           // cout<<"primo passi++"<<endl;
            vector<Node> newStack;
            while(stack.size()!= 0){
                //cout<<"stack back() passo a alta marea: ";
                //stack.back().printNode();cout<<endl;
                
                if(passi < t) findRoute1(w,false,stack.back(),t,n,t-1,best);
            
                
                
                vector<Node>::iterator it = w.begin();
                while(it != w.end()){
                   // cout<<"esamino: ";stack.back().printNode();  cout<<"con : "; it->printNode();cout<<endl;
                   // cout<<"lo stack è: ";
                   // printV(newStack);cout<<endl;
                    //cout<<"passi = "<<passi<<endl;
                    //cout<<"w1 = "; printV(w); cout<<endl;
                    
                    if(it->coppia[0] == stack.back().coppia[1]) {
                        if(it->coppia[1] == n-1){if(passi+1 < best)best = passi+1; return;}
                        newStack.push_back(*it);
                        it = w.erase(it);
                    }
                    //ho inserito tutte le coppie linkabili
                    else it++;
                }
                
                stack.pop_back();
            }
            if(newStack.size() == 0) {return;}
            passi++;
            stack = newStack;

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
