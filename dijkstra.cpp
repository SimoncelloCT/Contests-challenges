#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
using namespace std;

template<class H> class Graph{
private:
    H nodi[100];
    int adj[100][100];
    int size;
    
    bool visited[100]; // serve per dijstra
    int d[100]; // stime di cammini minimi
    
    int search(H key){
        for(int i = 0; i< size; i++) if(nodi[i] == key) return i;
        return -1;
    }
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
    void setAdj(H a, H b,int peso){
        int posA = getIndex(a);
        int posB = getIndex(b);
        adj[posA][posB] = peso;
    }
    void printNodi(){
        for (int i = 0; i< size;i++){
            cout<<nodi[i]<<" ";
        }
        cout<<endl;
    }
    bool allVisited(){
        for(int i = 0; i<size;i++){
            if(visited[i] == false) return false;
        }
        return true;
    }
    
    int getStimaMinimaIndex(){
        int min  = INT_MAX;
        int posMin = -1;
        for(int i = 0; i<size; i++){
            if(visited[i] == false) if(d[i] < min){
                min = d[i];
                posMin = i;
            }
        }
        return posMin;
    }
    
    
    void relax(int a, int b){ // a = indice nodo -> b indice nodo da rilassare
        if(d[a]+adj[a][b] < d[b]) d[b] = d[a]+adj[a][b];
    }
    
    int dijkstra(H a, H b){
        int sorg = getIndex(a);
        int dest = getIndex(b);
        for(int i = 0; i<size;i++) visited[i] = false; //inizializzo visite a false
        for(int i = 0; i<size;i++) d[i] = INT_MAX; // inizializzo stime a +inf
        d[sorg] = 0;
        //inizio algoritmo
        int index = sorg;
        while(!allVisited()){
            for(int i = 0; i< size; i++){ //per tutti i nodi possibilmente adicenti al nodo index
                //se l'indice i è di un nodo che non è stato visitato
                if(adj[index][i] != -1 && visited[i] == false) relax(index, i);
            }
            visited[index] = true;
            index = getStimaMinimaIndex();
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
     //   cout<<"n: "<<n<<endl;
       // cout<<"a: "<<a<<endl;
        
        if(type == "int"||type == "bool"){
            Graph<int> G;
            for(int j = 0; j<n;j++){ //prendo nodi
                int nodo;
                in>>nodo;
                G.insert(nodo);
            }
            for(int j = 0; j<a;j++){ //prendo archi
                
                string sorg,dest,peso;
                in>>sorg>>dest>>peso;
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
        else { //double
            Graph<double> G;
            for(int i = 0; i<n;i++){ //prendo nodi
                double nodo;
                in>>nodo;
               // nodo = nodo/10;
                G.insert(nodo);
            }
            for(int i = 0; i<a;i++){ //prendo archi
                string sorg,dest,peso;
                in>>sorg>>dest>>peso;
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




