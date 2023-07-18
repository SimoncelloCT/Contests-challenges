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
#define dim 1
using namespace std;

int power(int x, int n){ //complessità O(n)
    if(n == 0) return 1;
    return x * power(x, n-1);
}
int power(int x, int n){ //complessità O(log n)
    if(n == 0) return 1;
    if(n%2 == 0) {
        int y = power(x,(n)/2);
        return y * y;
    }
    if(n%2 == 1){
        int y = power(x,(n-1)/2);
        return x * y * y;
    }
}


void print(vector<int> a);

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
int findRoute(vector<Node> v,int n);
void printNode(Node n,vector<Node> v);
void printStack(vector<Node> v);
bool existsRoute(vector<Node> v, int source, int dest);
int find1(vector<Node> s, Node n);

int main(){
    fflush(stdout);
    ifstream file;
    file.open("./input2.txt");
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
           // cout<<"esamino i nodi: {"<<x<<"-"<<y<<"}"<<endl;
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
            
            //printV(v);
            if(indX == v.end()){ // non esiste x
                vector<Node>::iterator indY;
                indY = find(v.begin(),v.end(), ny);
                if(indY == v.end()){ //non esiste y
                  //  cout<<"NON ESISTE X e NON ESISTE Y"<<endl;
                    v.push_back(nx);
                    v.push_back(ny);
                    v[v.size()-2].parents.push_back(v.size()-1);
                    v[v.size()-1].parents.push_back(v.size()-2);
                }
                else{
                    int iY =  distance(v.begin(),indY);
                     //cout<<"NON ESISTE X, MA ESISTE Y"<<endl;
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
                   // cout<<" ESISTE X, MA NON ESISTE Y"<<endl;
                    ny.parents.push_back(iX);
                    v.push_back(ny);
                    v[iX].parents.push_back(v.size()-1);
                }
                else{
                    int iY =  distance(v.begin(),indY);
                   // cout<<"ESISTE X ESISTE Y"<<endl;
                    v[iY].parents.push_back(iX);
                    v[iX].parents.push_back(iY);
                }
            }
        
        }
        printV(v);
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
            if (res == true) {exPast = true;break;}
        }
        
        int res = -1;
        
        if(one && call && existsRoute(v,n,1) && exPast == true) {cout<<"esistono le strade"<<endl; }//res = findRoute(v,n);}
        cout<<res<<endl;
        out<< res<<endl;
        
    }
    file.close();
    out.close();
    return 0;
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






int findRoute(vector<Node> v,int n){
   // cout<<"dentro funzione"<<endl;
    vector<Node>::iterator it;
    Node tmp =  Node(n,false);
    it = find(v.begin(),v.end(),tmp); // fisso il nodo di partenza
    int iFound = distance(v.begin(),it);
    //cout<<"parto dal nodo in posizione "<<iFound<<endl;
    if(it == v.end()) return -1; // se non esiste proprio la casa return -1;
    
    vector<Node> stack;
    v[iFound].from = -1;
    stack.push_back(v[iFound]);
    
    //cout<<"stack iniziale: ";
    //printStack(stack);
    int f = 0;
    do{
        //printStack(stack);
        Node first = stack[f];
        for(int i = 0; i<first.parents.size();i++){
            int fr = first.from;
            int from2 = -1;
            if(fr != -1) from2 = stack[fr].from;
            
            if(fr != -1 && (first.val == 1 && stack[fr]  == v[first.parents[i]])){} //{cout<<"esco per val  = 1 e io = mio nonno"<<endl;}
            else if(fr != -1 && (stack[fr] == v[first.parents[i]] && first.past == false)){}//{ cout<<"f= "<<f<<" from: "<< stack[fr].val<<" io: "<< first.val<<" figlio: "<<v[first.parents[i]].val<<endl;} // io non sono pasticceria e mio figlio == mio padre
            else if(from2 != -1 && (first == stack[from2] && stack[fr]  == v[first.parents[i]])){
                
               // cout<<"esco per io = mio nonno e mio padre = suo nonno(loop)"<<endl;
                
                
                
            }
          
            else{ //inserisco i parents
                if(v[first.parents[i]].val  == 1){ //ho trovato il nodo 1
                    //iniziamo il percorso a ritroso
                   // cout<<"inizio percorso a ritroso"<<endl;
                    v[first.parents[i]].from = f;
                    int from = f;
                    //cout<<v[first.parents[i]].val<<"->";
                    bool pasticc = false;
                    int count = 0;
                    while(from != -1) {
                      //  cout<<stack[from].val<<"->";
                        if(stack[from].past) {/*cout<<"i numero "<<stack[from].val <<"è pasticceria "<<endl;*/ pasticc = true;}
                        from = stack[from].from;
                        count++;
                    }
                   // cout<<"fuori while"<<endl;
                   // cout<<stack[first.from].val<<endl;
                   // cout<<endl;
                    if(pasticc) return count;
                }
                
                //else automatico
                //cout<<"else if"<<endl;
               /* int it;
                cout<<"cerco il parent: "<<v[first.parents[i]].val<<endl;
                it = find1(stack,v[first.parents[i]]);
                if(it != -1) cout<<stack[it].val<<endl;
                else cout<<"non trovato"<<endl;*/
                if(first.past == false && find1(stack, v[first.parents[i]]) != -1) {}//cout<<"non inserisco"<<endl;}
                else{
                    v[first.parents[i]].from = f;
                    //cout<<"settato from "<<stack[f].val<<endl;
                    v[first.parents[i]].dist = v[v[first.parents[i]].from].dist +1;
                    stack.push_back(v[first.parents[i]]);
                
                }
            }
            //cout<<"fine for"<<endl;
        }

        f++;
        //cout<<"F= "<<f<<endl;
        //printStack(stack);
    }while(f <= stack.size()-1);
    
    return -1;
 }







int find1(vector<Node> s, Node n){
    for(int i = 0; i< s.size();i++){
        if(n.val == s[i].val  && s[i].dist == n.dist - 1 ) return i;
    }
    return -1;
}
void printStack(vector<Node> v){
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
