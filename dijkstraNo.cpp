#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
using namespace std;



int searchElement(int *A, int n, int searched){
    for(int i = 0; i<n;i++) if(A[i] == searched) return i;
    return -1;
}



template<class H> class Graph{
private:
    H nodi[100];
    int adj[100][100];
    int size;
public:
    Graph(){
        size = 0;
        for(int i = 0; i<100;i++){
            for(int j = 0; j<100;j++){
                if (i == j) adj[i][j] = 0;
                else adj[i][j] = -1;
            }
        }
    }
    void insert(H key){
        size++;
        nodi[size-1] = key;
    }
    int getIndex(H key){
        return search(key);
    }
    int search(H key){
        for(int i = 0; i< size; i++) if(nodi[i] == key) return i;
        return -1;
    }
    
    void setAdj(H a, H b,int peso){
        int posA = getIndex(a);
        int posB = getIndex(b);
        adj[posA][posB] = peso;
    }
    /*Considerando d[v] = stima di cammino minimo dalla sorgente a v
    Assegnamo  d[s] = 0 e d[v] = infinito per qualsiasi altro vertice v.
    
    Consideriamo un array visited
    NodoCorrente = s.
    
    While (visited.lenght < grafo.numVertici ){ // finchè non ho visitato tutti i nodi
        while(ci sono nodi adiacenti adj tali che visited.contains(adj) == false){
            se d[nodoCorrente] + w(nodoCorrente , adj) < d[adj]{
                //rilasso il nodo.
                d[adj] = d[nodoCorrente] + w(nodoCorrente , adj)
            }
            visited.push = nodoCorrente
            nodoCorrente = nodo la cui stima d[v] = min(d).
        }
    }
     */
    void relax(int a, int b, int* d){ // a = indice nodo -> b indice nodo da rilassare
        if(d[a]+adj[a][b] < d[b]) d[b] = d[a]+adj[a][b];
    }
    
    int getMinNode(int* visited,int n, int* d){ //prende il minimo come stima, dei non visitati
        int min = INT_MAX;
        int minPos = -1;
        for(int i = 0; i< size; i++){
            if(d[i] < min && searchElement(visited,n,i) == -1) {min = d[i]; minPos = i;}
        }
        return minPos;
    }
    
    int dijkstra(H a, H b){
        int sorg = getIndex(a);
        int dest = getIndex(b);
        int d[size];
        for(int i = 0; i<size;i++) d[i] = INT_MAX;
        d[sorg] = 0;
        //array di nodi visitati
        int visited[size]; // contiene gli indici dei nodi visitati
        for(int i = 0; i<size;i++) visited[i] = 0;
        int visitedSize = 0;
        
        //inizio algoritmo
        int index = sorg;
        while(visitedSize != size){
            //cerco nodi adiacenti al nodo index
            for(int i = 0; i< size; i++){ //per tutti i nodi possibilmente adicenti al nodo index
                //se l'indice i è di un nodo che non è stato visitato
                if(adj[index][i] != -1 && searchElement(visited,visitedSize,i) == -1) relax(index, i,d);
            }
            visitedSize++;
            visited[visitedSize-1] = index;
            index = getMinNode(visited,visitedSize,d);
        }
        return d[dest];
    }
};
int main(){
	fstream in;
	fstream out;
	in.open("./input.txt");
	out.open("./output.txt" , ios::out);
	for(int i=0; i<100;i++){
        int n,a;
        string type;
        in>>n>>a;
        in>>type;
        if(type == "int"||type == "bool"){
            Graph<int> G;
            for(int i = 0; i<n;i++){ //prendo nodi
                int nodo;
                in>>nodo;
                G.insert(nodo);
            }
            for(int i = 0; i<a;i++){ //prendo archi
                string sorg,dest,peso;
                in>>sorg>>dest>>peso;
                cout<<sorg<<" "<<dest<<" "<<peso<<endl;
                sorg = sorg.substr(1);
                peso = peso.substr(0,peso.length()-1);
                int s = atoi(sorg.c_str());
                int d = atoi(dest.c_str());
                int p = atoi(peso.c_str());
                G.setAdj(s,d,p);
            }
            int dsorg,ddest;
            in>>dsorg>>ddest;
            int lungh = G.dijkstra(dsorg,ddest);
            
            if(lungh == INT_MAX) out<<"inf"<<endl;
            else out<< lungh<<endl;
        }
        else {
            Graph<double> G;
            for(int i = 0; i<n;i++){ //prendo nodi
                double nodo;
                in>>nodo;
                G.insert(nodo);
            }
            for(int i = 0; i<a;i++){ //prendo archi
                string sorg,dest,peso;
                in>>sorg>>dest>>peso;
                cout<<sorg<<" "<<dest<<" "<<peso<<endl;
                sorg = sorg.substr(1);
                peso = peso.substr(0,peso.length()-1);
                double s = atof(sorg.c_str());
                double d = atof(dest.c_str());
                int p = atoi(peso.c_str());
                G.setAdj(s,d,p);
            }
            double dsorg,ddest;
            in>>dsorg>>ddest;
            int lungh = G.dijkstra(dsorg,ddest);
            
            if(lungh == INT_MAX) out<<"inf"<<endl;
            else out<< lungh<<endl;
            
        }
	}
	in.close();
	out.close();
	return 0;
}




