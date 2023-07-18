#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
using namespace std;

//devo ordinare gli archi con con (u,v) (u1,v1) u< u1 | u= u1 -> v< v1

template<class H> class Graph{
private:
    H nodi[100];
    int adj[100][100];
    int size;
    
    long d[100]; // stime di cammini minimi
    
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
                else adj[i][j] = INT_MIN; // essendoci pesi negativi -1 NON VA BENE!!
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
    void printAdj(){
        for(int i = 0; i< size; i++){
            for(int j = 0; j< size;j++){
                cout<<"("<<i<<" "<<j<<" "<<adj[i][j]<<")"<< " ";
            }
        }
    }
    
    bool relax(int a, int b){ // a = indice nodo -> b indice nodo da rilassare
        if(d[a]+adj[a][b] < d[b])
        {
            d[b] = d[a]+adj[a][b];
            return true; // ho rilassato
        }
        return false; // non ho rilassato
    }
    
    
    int bellman_ford(H a, H b, int k){
        int sorg = getIndex(a);
        int dest = getIndex(b);
        for(int i = 0; i<size;i++) d[i] = INT_MAX; // inizializzo stime a +inf
        d[sorg] = 0;
        
        for(int i = 0; i< k;i++){ // k volte //bellman-p
            
            //per ogni arco
            for(int j = 0; j<size;j++){ // per ogni nodo del grafo
                for(int k = 0; k<size;k++) // per ogni adiacente del nodo preso in considerazione
                    if(adj[j][k] != INT_MIN) { // se sono adiacenti
                        bool relaxed = relax(j,k); // prova a rilassarlo
                    }
            }
        }
        //bool correct = control_correct(sorg,dest);
        //if(correct)
        return d[dest];
        //else return INT_MIN;
        
    }
    
    bool control_correct(int s, int d){
        
        for(int j = 0; j<size;j++){ // per ogni nodo del grafo
            for(int k = 0; k<size;k++){ // per ogni adiacente del nodo preso in considerazione
                if(adj[j][k] != INT_MIN) { // se sono adiacenti
                    bool relaxed = relax(j,k); // prova a rilassarlo
                    if (relaxed) return false; // ho rilassato di nuovo errore.
                }
            }
        }
        return true; // non ho rilassato tutto ok.
    }
    
};

int searchArray(int*A, int n, int key){
    for(int i = 0; i<n;i++){
        if(key == A[i]) return i;
    }
    return -1;
}
int* sort(int *A,int n){
    for(int i = 0; i< n;i++){
        for(int j = i+1;j<n;j++){
            if(A[j] < A[i]){
                int tmp = A[i];
                A[i] =  A[j];
                A[j] = tmp;
            }
        }
    }
    return A;
}
class Arco{
public:
    int s;
    int d;
    int peso;
    Arco(){}
    Arco(int sorg,int dest,int p){
        s = sorg;
        d = dest;
        peso = p;
    }
};

int main(){
	fstream in;
	fstream out;
	in.open("./input.txt");
	out.open("./output.txt" , ios::out);
	for(int i=0; i<100;i++){
        int n,a;
        int k;
        in>>n>>a;
        in>>k;
        Graph<int> G;
        int nodi[n];
        int sizeNodi = 0;
        Arco archi[a];
        int sizeArchi = 0;
        for(int j = 0; j<a;j++){ //prendo archi per costruire array nodi
            string sorg,dest,peso;
            in>>sorg>>dest>>peso;
            sorg = sorg.substr(1);
            peso = peso.substr(0,peso.length()-1);
            int s = atoi(sorg.c_str());
            int d = atoi(dest.c_str());
            int p = atoi(peso.c_str());
            sizeArchi++;
            archi[sizeArchi-1] = Arco(s,d,p);//salvo l'arco perchè non posso rileggerlo dal file
            //costruisco l'array nodi dagli archi
            if(searchArray(nodi,sizeNodi,s) == -1){
                sizeNodi++;
                nodi[sizeNodi-1] = s;
            }
            if(searchArray(nodi,sizeNodi,d) == -1){
                sizeNodi++;
                nodi[sizeNodi-1] = d;
            }
        }
        //ordino in modo crescente nodi
        int *sortedNodi = sort(nodi,sizeNodi);
        for(int j = 0;j<sizeNodi;j++){//inserisco nodi nel grafo
            G.insert(sortedNodi[j]);
        }
        
        for(int j = 0; j<sizeArchi;j++){ //prendo archi per settare adj(ho già i nodi nell'array della classe)
            G.setAdj(archi[j].s,archi[j].d,archi[j].peso);
        }
        
        int dsorg,ddest;
        in>>dsorg>>ddest;
        G.printNodi();
        G.printAdj();
        int lungh = G.bellman_ford(dsorg,ddest,k);
        
        if(lungh == INT_MAX) out<<"inf."<<endl;
        //else if(lungh == INT_MIN) out<<"undef."<<endl;
        else out<<lungh<<endl;
	}
	in.close();
	out.close();
	return 0;
}




