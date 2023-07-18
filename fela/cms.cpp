
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
#include <math.h>
#define dim 85
using namespace std;
/*void delayProgram(double secondsToDelay)
{
    clock_t startTime = clock(); //Start timer
    
    clock_t testTime;
    clock_t timePassed;
    double secondsPassed;
    
    while(true)
    {
        testTime = clock();
        timePassed = startTime - testTime;
        secondsPassed = timePassed / (double)CLOCKS_PER_SEC;
        
        if(secondsPassed >= secondsToDelay)
        {
            cout << secondsToDelay << "seconds have passed" << endl;
            break;
        }
        
    }
    
    
}*/
int riga = 0;
class Node{
public:
    int source;
    int dest;
    int timeFree;
    int startLav;
    vector<int> adj;
    bool visited;
    int time;
    Node(){
        source  = -1;
        dest = -1;
        timeFree = -1;
        startLav = -1;
        visited = false;
        time = 0;
        
    }
    Node(int s,int d, int tf, int sl){
        source  = s;
        dest = d;
        timeFree = tf;
        startLav = sl;
        visited = false;
        time = 0;
    }
    bool operator==( Node const  rhs) const { return this->source == rhs.source;}
};


void printV(vector<Node> v);
void setAdj(vector<Node> &v);
void getRoute(vector<Node> v, int sourceIndex, int dest, int &best, int time);
bool existsRoute(vector<Node> v, int source, int dest);

int main(){
    fflush(stdout);
    ifstream file;
    file.open("./input.txt");
    ofstream out;
    out.open("output.txt");
    for(int i = 0; i<dim; i++){
        cout<<"riga: "<<i+1<<endl<<endl;
        riga = i;
        int n,m;
        file>>n; // numero di nodi // ci serve per la destinazione
        file>>m;//numero di strade(link)
        vector <Node> v; //l'array della riga su cui lavoriamo
        
        for(int j = 0; j<m;j++){ //inserisco le quadruple
            //cout<<"inserisco le quadruple"<<endl;
            int s,d,tf,sl;
            file>>s;
            file>>d;
            file>>tf;
            file>>sl;
            Node n1 = Node(s,d,tf,sl);
            if(s != n-1) v.push_back(n1); // se il source è uguale al punto di arrivo allora metto solo la coppia inversa.
            if(s != 0 && d != n-1) {Node n2 = Node(d,s,tf,sl); v.push_back(n2);} // se non è una coppia che parte con 0 metto l'inversa
            
        }
        //l'inserimento delle quadruple è terminato
        //cerco in v elementi che partono con il mio destination e metto i loro indici come adiacenti
        setAdj(v);
        
        
        
        //printV(v);
        //cout<<endl;
        int best = 20;
        for(int h =0; h< v.size();h++){
            if(v[h].source == 0 && existsRoute(v,h,n-1)) {
              
                getRoute(v,h,n-1,best,v[h].timeFree+1);
                //cout<<"chiamate eseguite = "<<chiamate<<endl;
                
            }
        }
        if(best == 20) best = -1;
        cout<<best<<endl;
        out<<best<<endl;
        
    }
    file.close();
    out.close();
    return 0;
}



//il tempo dal main non parte da 0 ma parte da timeFree+1;
void getRoute(vector<Node> v, int sourceIndex, int dest, int &best, int time){
    //cout<<"best = "<<best<<endl;
    if(time >= best){ return;}
    //if(!existsRoute(v,sourceIndex,dest)) return;
    if(v[sourceIndex].dest == dest) if(time < best) { cout<<" return time = "<<time<<endl; best = time;  return;}
     for(int i = 0; i<v[sourceIndex].adj.size();i++){ // per ogni adiacente
         int c = v[sourceIndex].adj[i]; // indice corrispondente su v
         if(time < v[c].startLav){
             if(time < v[c].timeFree) { // faccio una chiamata con quel time perchè aspetto per passare e poi vado nel adiacente strada
                  getRoute(v,c,dest,best,v[c].timeFree+1);
             }
             else{//non devo aspettare posso già passare
                 getRoute(v,c,dest,best,time+1);
             }
        }
     }
}







bool existsRoute(vector<Node> v, int source, int dest){
    /*for(int i = 0; i< v.size(); i++){
        v[i].visited = false;
    }*/
    vector<Node> stack;
    stack.push_back(v[source]);
    v[source].visited = true;
    while(stack.size() != 0 ){
        //cout<<"nel while"<<endl;
        Node first = stack.back();
        //cout<<"firast: "<<first.source<<endl;
        stack.pop_back();
        for(int i = 0; i<first.adj.size();i++){
            if(v[first.adj[i]].visited == false){
          //      cout<<"non visitato"<<endl;
                if(v[first.adj[i]].dest == dest) return true;
                stack.push_back(v[first.adj[i]]);
                v[first.adj[i]].visited = true;
            }
        }
    }
    return false;
}

/*

void getRoute(vector<Node> v, int sourceIndex, int dest, int &best){ // source è un indice passato dal main
   
    vector<int> stack;
    stack.push_back(sourceIndex);
    v[sourceIndex].visited = true;
    
    while(stack.size() != 0 ){
        int vIndex = stack.back();
        stack.pop_back();
        v[vIndex].time = v[vIndex].timeFree + 1; // parto dal tempo necessario per attraversare la prima strada
        
        for(int i = 0; i<v[vIndex].adj.size();i++){ // per ogni adiacente
            int c = v[vIndex].adj[i]; // indice corrispondente su v
            if(time < v[c].startLav){
                if(time < v[c].timeFree) time = v[c].timeFree // aspetto che la strada si libera per passare
            }
            if(v[first.parents[i]].val == dest) return true;
                stack.push_back(v[first.parents[i]]);
                v[first.parents[i]].visited = true;
            
        }
    }
    return false;
}
*/


void setAdj(vector<Node> &v){ // setta gli adiacenti di ogni nodo di v
    for(int i = 0; i<v.size();i++){
        for(int j = 0; j<v.size();j++){
            if(v[i].dest == v[j].source && v[i].source != v[j].dest){
                int time =  v[i].timeFree + 1; // il tempo minimo al quale la strada non ha lavori, + il passaggio dalla strada stessa
                if(time < v[j].startLav) v[i].adj.push_back(j);
            }
        }
    }
}

void printNode(Node n,vector<Node> v){
    cout<<"{source: "<<n.source<<" dest: "<<n.dest<<" timeFree: "<<n.timeFree<<" startL: "<<n.startLav <<" , adj: ";
    for(int i =  0; i< n.adj.size();i++){
        cout<<n.adj[i]<<" ";
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


/*

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
                    if(pasticc) { cout<<"numero nodi nello stack = "<<nNodi<<endl; return count;}
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
 
*/





