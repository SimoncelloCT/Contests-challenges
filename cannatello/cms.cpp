
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
#define dim 1
using namespace std;

void print(vector<int> a);


struct stackNode{
    int val;
    int vIndex;
    int sFrom;
    int dist;
};


class Node{
public:
    int val;
    bool past;
    int from;
    bool visited;
    int dist;
    vector<int> parents;
    Node(){
        dist = 0;
        val = -1;
        past = false;
        from = -1;
        visited = false;
        
    }
    Node(int val,bool past){
        this->val = val;
        this->past = past;
        from = -1;
        dist = 0;
        visited = false;
    }
    bool operator==( Node const  rhs) const { return this->val == rhs.val;}
};



void printV(vector<Node> v);
int findRoute(vector<Node> v,int source, int destination);
void printNode(Node n,vector<Node> v);
void printStack(vector<stackNode> v);
bool existsRoute(vector<Node> v, int source, int dest);
int find1(vector<stackNode> s, stackNode n);
void printDist(vector<stackNode> s,int d);
int main(){
    fflush(stdout);
    ifstream file;
    file.open("./input.txt");
    ofstream out;
    out.open("output.txt");
    for(int i = 0; i<dim; i++){
        cout<<"riga: "<<i+1<<endl<<endl;
        int n,m,k;
        file>>n; // numero di nodi // ci serve per la destinazione
        file>>m;//numero di strade(link)
        file>>k;
        vector<int> pasticcerie;
        vector <Node> v; //l'array della riga su cui lavoriamo
        for(int u = 0; u<k;u++) {
            int p;
            file>>p;
            Node tmp = Node(p,true);
            v.push_back(tmp);
            pasticcerie.push_back(p);
        }
        bool one = false;
        for(int j = 0; j<m;j++){
            int x,y;
            file>>x;
            file>>y;
            if(x == 1 || y ==1) one = true;
            Node nx  = Node(x,false);
            Node ny = Node(y,false);
            
            vector<int>:: iterator iter ;
            iter = find(pasticcerie.begin(), pasticcerie.end(),y);
            if(iter != pasticcerie.end()) ny.past =  true;
            iter = find(pasticcerie.begin(), pasticcerie.end(),x);
            if(iter != pasticcerie.end()) nx.past =  true;
            
            vector<Node>::iterator indX;
            indX = find(v.begin(),v.end(),nx);
            if(indX == v.end()){
                vector<Node>::iterator indY;
                indY = find(v.begin(),v.end(), ny);
                if(indY == v.end()){ //non esiste y;
                    v.push_back(nx);
                    v.push_back(ny);
                    v[v.size()-2].parents.push_back(v.size()-1);
                    v[v.size()-1].parents.push_back(v.size()-2);
                }
                else{
                    int iY =  distance(v.begin(),indY);
                    nx.parents.push_back(iY);
                    v.push_back(nx);
                    v[iY].parents.push_back(v.size()-1);
                }
            }
            else{
                int iX =  distance(v.begin(),indX);
                vector<Node>::iterator indY;
                indY = find(v.begin(),v.end(), ny);
                if(indY == v.end()){
                    ny.parents.push_back(iX);
                    v.push_back(ny);
                    v[iX].parents.push_back(v.size()-1);
                }
                else{
                    int iY =  distance(v.begin(),indY);
                    v[iY].parents.push_back(iX);
                    v[iX].parents.push_back(iY);
                }
            }
            
        }
        
        
        //printV(v);
        
        
        
        bool call = true;
        for(int t = 0; t<v.size();t++){
            if(v[t].val == 1){
                if(v[t].parents.size() == 1){
                    Node p = v[v[t].parents[0]];
                    if(p.parents.size() == 1 && v[p.parents[0]].val == 1){
                        call = false;
                    }
                }
            }
        }
        
      
        bool exPast = false;
        for(int y = 0; y< pasticcerie.size();y++){
            bool res = existsRoute(v,pasticcerie[y],1);
            if (res == true) {exPast = true; break;}
        }
        
        int res = -1;
        
        if(one && call && existsRoute(v,n,1) && exPast == true) {cout<<"esistono le strade"<<endl;  res = findRoute(v,n,1);}
        cout<<res<<endl;
        out<< res<<endl;
        
    }
    file.close();
    out.close();
    return 0;
}




int findRoute(vector<Node> v,int source, int destination){
    vector<Node>::iterator it;
    Node tmp =  Node(source,false);
    it = find(v.begin(),v.end(),tmp); // fisso il nodo di partenza
    int iFound = distance(v.begin(),it);
    if(it == v.end()) return -1; // se non esiste proprio la casa return -1;
    vector<stackNode> stack;
    stackNode s;
    s.val = v[iFound].val;
    s.vIndex = iFound;
    s.sFrom = -1;
    s.dist = 0;
    stack.push_back(s);
    int f = 0;
    int nNodi = 0;
    do{
      //  cout<<"entro nel do"<<endl;
        Node first = v[stack[f].vIndex];
        for(int i = 0; i<first.parents.size();i++){ // per ogni figlio del nodo in esame
            int fr = first.from; // da dove provengo io
            int from2 = -1; // da dove proviene mio padre
            if(fr != -1) from2 = stack[fr].sFrom;
            if(fr != -1 && (first.val == 1 && v[stack[fr].vIndex]  == v[first.parents[i]])){}
            else if(fr != -1 && (v[stack[fr].vIndex] == v[first.parents[i]] && first.past == false)){}
            else if(from2 != -1 && (first == v[stack[from2].vIndex] && v[stack[fr].vIndex]  == v[first.parents[i]])){}
            else{
                //inserisco i parents
                if(v[first.parents[i]].val  == destination){ //ho trovato il nodo 1
                    int from = f;
                    bool pasticc = false;
                    int count = 0;
                    while(from != -1) {
                        if(v[stack[from].vIndex].past) {pasticc = true;}
                        from = stack[from].sFrom;
                        count++;
                    }
                    if(pasticc) { cout<<"numero nodi nello stack = "<<nNodi<<endl;/* printStack(stack);*/ return count;}
                }
                    stackNode s;
                    s.val = v[first.parents[i]].val;
                    s.vIndex = first.parents[i];
                    s.sFrom = f;
                    s.dist = stack[f].dist+1;
                    if((first.past == true && v[s.vIndex].past == false)  || find1(stack,s) == -1){ // controlla se ce n'è altri uguali
                        stack.push_back(s);
                        nNodi++;
                    }
            }
        }
        f++;
       // printStack(stack);
    }while(f < stack.size()   );
    
    return -1;
}
                                                        
                                                        
int find1(vector<stackNode> s, stackNode n){
  for(int i = 0; i< s.size();i++){
        if(n.val == s[i].val  && s[i].dist <= n.dist) return i;
  }
  return -1;
}





void printNode(Node n,vector<Node> v){
    cout<<"{val: "<<n.val<<" past: "<<n.past<<" , parents: ";
    for(int i =  0; i< n.parents.size();i++){
        cout<<v[n.parents[i]].val<<" ";
    }
    cout<<"}"<<endl;
    
}
//source fine  dest 1
bool existsRoute(vector<Node> v, int source, int dest){
    vector<Node>::iterator it;
    Node tmp =  Node(source,false);
    it = find(v.begin(),v.end(),tmp); // fisso il nodo di partenza
    int iFound = distance(v.begin(),it);
    if(it == v.end()) return false; // se non esiste proprio la casa return -1;
    
    vector<Node> stack;
    stack.push_back(v[iFound]);
    v[iFound].visited = true;
    while(stack.size() != 0 ){
        Node first = stack.back();
        stack.pop_back();
        for(int i = 0; i<first.parents.size();i++){
            if(v[first.parents[i]].visited == false){
                if(v[first.parents[i]].val == dest) return true;
                stack.push_back(v[first.parents[i]]);
                v[first.parents[i]].visited = true;
            }
        }
    }
    return false;
}


void printDist(vector<stackNode> s,int d){
    cout<<"dist"<<d<<": {";
    for(int i = 0; i<s.size();i++){
        if(s[i].dist == d)
            
            cout<<"val: "<<s[i].val<<" ";
    }
    cout<<"}"<<endl;
}



void printStack(vector<stackNode> v){
    cout<<"{ ";
    for(int i = 0;i< v.size();i++){
        cout<<v[i].val<<" ";
    }
    cout<<"}"<<endl;
}



void print(vector<int> a){
    cout<<"{ ";
    for(int i = 0; i<a.size();i++){
        cout<<a[i]<<" ";
    }
    cout<<"}"<<endl;
}
void printV(vector<Node> v){
    for(int i = 0; i< v.size(); i++) printNode(v[i],v);
    
}
