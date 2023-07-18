
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
#define dim 5
using namespace std;


void print(vector<int> a);
/*

struct stackNode{
    int val;
    int vIndex;
    int sFrom;
    int dist;
};
*/

class Node{
public:
    int source;
    int dest;
    int timeFree;
    int startLav;
    vector<int> adj;
    int time;
    int dist;
    int vIndex;
    
    Node(){
        source  = -1;
        dest = -1;
        timeFree = -1;
        startLav = -1;
        time = 0;
        dist = 0;
        vIndex = -1;
        
    }
    Node(int s,int d, int tf, int sl){
        source  = s;
        dest = d;
        timeFree = tf;
        startLav = sl;
        time = 0;
        dist = 0;
        vIndex = -1;
    }
    bool operator==( Node const  rhs) const { return this->source == rhs.source;}
};


void printV(vector<Node> v);
/*
int findRoute(vector<Node> v,int source, int destination);
void printNode(Node n,vector<Node> v);
void printStack(vector<stackNode> v);
bool existsRoute(vector<Node> v, int source, int dest);
int find1(vector<stackNode> s, stackNode n);
void printDist(vector<stackNode> s,int d);*/
void setAdj(vector<Node> &v);
//int getRoute(vector<Node> v, int source, int dest);
void getRoute(vector<Node> v, int sourceIndex, int dest, int &best, int time);
bool existsRoute(vector<Node> v, int source, int dest);
int itRoute(vector<Node> v, int source, int dest);
void find1(vector<Node> s, vector<int> & ret, Node now);

int main(){
    fflush(stdout);
    ifstream file;
    file.open("./input.txt");
    ofstream out;
    out.open("output.txt");
    for(int i = 0; i<dim; i++){
        cout<<"riga: "<<i+1<<endl<<endl;
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
            if(s != n-1){ v.push_back(n1); v.back().vIndex = v.size()-1;}// se il source è uguale al punto di arrivo allora metto solo la coppia inversa.
            if(s != 0 && d != n-1) {Node n2 = Node(d,s,tf,sl); v.push_back(n2); v.back().vIndex = v.size()-1;} // se non è una coppia che parte con 0 metto l'inversa
            
        }
        //l'inserimento delle quadruple è terminato
        //cerco in v elementi che partono con il mio destination e metto i loro indici come adiacenti
        setAdj(v);
        printV(v);
        cout<<endl;
        int best = INT_MAX;
        for(int h =0; h< v.size();h++){
            int ris = INT_MAX;
            if(v[h].source == 0) {
                ris = itRoute(v,h,n-1);
                cout<<"ris= "<<ris<<endl;
                if (ris != -1 && ris < best) best = ris;
            }
        }
        if(best == INT_MAX) best = -1;
        cout<<best<<endl;
        out<<best<<endl;
        
    }
    file.close();
    out.close();
    return 0;
}

int itRoute(vector<Node> v, int source, int dest){
   // cout<<"itRoute"<<endl;
    vector<Node> stack;
    stack.push_back(v[source]);
    stack[0].time = stack[0].timeFree + 1;
   // cout<<v[source].source<<"->"<<v[source].dest<<" ";
    if (stack[0].dest == dest) return stack[0].timeFree +1;
    stack[0].dist = 0;
    int sIndex = 0;
    
    do{
        Node first = stack[sIndex];
        //cout<<"numero di adiacenti= "<<first.adj.size()<<endl;
        int lenght = stack.size();
        for(int i = 0; i<first.adj.size();i++){
            //printV(stack);
            //cout<<endl;
            int c = first.adj[i];
            if(first.time < v[c].startLav){
                stack.push_back(v[c]);
                if(first.time < v[c].timeFree) {
                    stack.back().time = stack.back().timeFree+1;
                    stack.back().dist = first.dist+1;
                }
                else {
                    stack.back().time = first.time+1;
                    stack.back().dist = first.dist+1;
                }
                //controllo se il figlio che ho inserito è destinazione
                
            }
        }
       // cout<<"terminato l'insermento degli adiacenti"<<endl;
        for(int i = lenght ;i<stack.size();i++){
            if(stack[i].dest == dest) {
             //   cout<<"il figlio al tempo : "<<stack[i].time <<" è destinazione, continuo i controlli"<<endl;
                int waitTime = stack[i].time - stack[i].dist;
                if(waitTime == 0) {/*cout<<"waitTime = 0"<<endl;*/ return stack[i].time; }
                else { // ho sicuramente aspettato, devo permettere agli altri nodi di proseguire per waitTime-1 volte
                    //cerco i nodi che rispettano la condizione e li passo tutti a getRoute con best= wait-Time
                    vector<int> found;
                    find1(stack,found,stack[i]);
                    if(found.size() == 0){/*cout<<"found.size() = 0, time = "<<stack.back().time<<endl; */ return stack[i].time;}
                    int lastBest;
                    int best = lastBest = waitTime;
                   // cout<<"avevo aspettato per "<<waitTime<<"secondi"<<endl;
                    int modSIndex = -1;
                    
                    for(int j = 0; j< found.size(); j++){
                        
                        getRoute(v,stack[found[j]].vIndex,dest,best,stack[found[j]].time); //da rivedere
                       // cout<<"al ciclo "<<j<<"ho trovato best = "<<best<<endl;
                        if(best < lastBest) {lastBest = best; modSIndex = j;}
                    }
                    if(lastBest < waitTime) return lastBest + stack[modSIndex].time;   //modSIndex dovrebbe essere necessariamente modificato se è cambiato il best rispetto al waitTime;
                    else return stack[i].time;
                }
            }
            
        }
        sIndex++;
    } while(sIndex < stack.size());
    return -1;
}

/*

if(stack.back().dest == dest) {
    cout<<"il figlio al tempo : "<<stack.back().time <<" è destinazione, continuo i controlli"<<endl;
    int waitTime = stack.back().time - stack.back().dist;
    if(waitTime == 0) { return stack.back().time; }
    else { // ho sicuramente aspettato, devo permettere agli altri nodi di proseguire per waitTime-1 volte
        //cerco i nodi che rispettano la condizione e li passo tutti a getRoute con best= wait-Time
        vector<int> found;
        find1(stack,found,stack.back());
        if(found.size() == 0){ return stack.back().time;}
        int lastBest;
        int best = lastBest = waitTime;
        cout<<"avevo aspettato per "<<waitTime<<"secondi"<<endl;
        int modSIndex = -1;
        
        for(int j = 0; j< found.size(); j++){
            
            getRoute(v,stack[found[j]].vIndex,dest,best,stack[found[j]].time); //da rivedere
            cout<<"al ciclo "<<j<<"ho trovato best = "<<best<<endl;
            if(best < lastBest) {lastBest = best; modSIndex = j;}
        }
        if(lastBest < waitTime) return lastBest + stack[modSIndex].time;   //modSIndex dovrebbe essere necessariamente modificato se è cambiato il best rispetto al waitTime;
        else return stack.back().time;
    }
    }

*/
void find1(vector<Node> s, vector<int> & ret, Node now){
    for(int i = 0; i< s.size();i++){
        if(now.dist == s[i].dist  && s[i].time < now.time-1) ret.push_back(i);
    }
}


//il tempo dal main non parte da 0 ma parte da timeFree+1;
void getRoute(vector<Node> v, int sourceIndex, int dest, int &best, int time){
    //cout<<v[sourceIndex].source<<"->"<<v[sourceIndex].dest<<" "<<"(time= "<<time<<") ";
    //cout<<"entro con time = "<<time<<endl;
   // if(!existsRoute(v,sourceIndex,dest)) return;
    if(time >= best){ return;}
    if(v[sourceIndex].dest == dest) if(time < best) { /*cout<<" return time = "<<time<<endl; */best = time;  return;}
    
    
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

    vector<Node> stack;
    stack.push_back(v[source]);
    //v[source].visited = true;
    while(stack.size() != 0 ){
        //cout<<"nel while"<<endl;
        Node first = stack.back();
        //cout<<"firast: "<<first.source<<endl;
        stack.pop_back();
        for(int i = 0; i<first.adj.size();i++){
          //  if(v[first.adj[i]].visited == false){
          //      cout<<"non visitato"<<endl;
                if(v[first.adj[i]].dest == dest) return true;
                stack.push_back(v[first.adj[i]]);
               // v[first.adj[i]].visited = true;
           // }
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
    cout<<"}";
    
}





void print(vector<int> a){
    cout<<"{ ";
    for(int i = 0; i<a.size();i++){
        cout<<a[i]<<" ";
    }
    cout<<"}"<<endl;
}

void printV(vector<Node> v){
    for(int i = 0; i< v.size(); i++) { cout<<"riga : "<< i<<" "; ;printNode(v[i],v); cout<<endl;}
    
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





