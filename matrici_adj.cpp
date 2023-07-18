
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
template<class H> class Graph{
private:
    H nodi[100];
    int adj[100][100];
    int size;
public:
    Graph<H>(){
        size = 0;
        for(int i = 0; i<100; i++){
            nodi[i] = -1;
            for(int j = 0; j<100;j++){
                adj[i][j] = -1;
            }
        }
    }
    Graph(H *A,int n){ // costruttore che setta l'array di nodi
        size = n;
        for(int i = 0; i< n;i++){
            nodi[i] = A[i];
        }
        for(int i = 0; i<100; i++){
            for(int j = 0; j<100;j++){
                adj[i][j] = -1;
            }
        }
    }
    void setKey(H key){
        size++;
        nodi[size-1] = key;
    }
    int getIndex(H k){
        return search(k);
    }
    int search(H k){
        for(int i = 0 ; i< size; i++){
            if(k  ==  nodi[i]) return i;
        }
        return -1;
    }
    void setAdj(H a, H b, int p){
        int ai = getIndex(a);
        int bi = getIndex(b);
        adj[ai][bi] = p;
    }
    H* getAdjs(H nodo){ //costruisce gli array per l'output
        int nodoi = getIndex(nodo);
        H* ris = new H[size+2];
        ris[0] = nodo;
        int risSize = 1;
        //cout<< "nodo "<<nodo<<" collegato con:"<<" ";
        for(int i = 0; i<size;i++){
            if(adj[nodoi][i] != -1){
                //cout<< nodi[i]<< " ";
                risSize++;
                ris[risSize-1] = nodi[i];
            }
        }
        risSize++;
        ris[risSize-1] = -1;
        /*for(int i = 0; i< risSize;i++){
            cout<<ris[i]<<" ";
        }
        cout<<endl;*/
     //   if(risSize == 2) return NULL;
        return ris;
    }
    void printAdj(){
        for(int i = 0; i< size; i++){
            for(int j = 0; j< size; j++){
                cout<<adj[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    
    
};
char* sortC(char * A, int n){
    for(int i =0; i< n; i++){
        for(int j = i+1; j< n;j++){
            if(A[i] > A[j]) {
                char tmp = A[i];
                A[i] = A[j];
                 A[j] = tmp;
            }
        }
    }
    return A;
}
int* sortI(int * A, int n){
    for(int i =0; i< n; i++){
        for(int j = i+1; j< n;j++){
            if(A[i] > A[j]) {
                int tmp = A[i];
                A[i] = A[j];
                 A[j] = tmp;
            }
        }
    }
    return A;
}
double* sortD(double * A, int n){
    for(int i =0; i< n; i++){
        for(int j = i+1; j< n;j++){
            if(A[i] > A[j]) {
                double tmp = A[i];
                A[i] = A[j];
                A[j] = tmp;
            }
        }
    }
    
    return A;
}

int main(){
    fstream in;
    fstream out;
    in.open("input.txt");
    out.open("output.txt", ios::out);
    for(int r = 0; r< 100; r++){
        cout<<"riga"<<r<<endl;
        int numNodi;
        int numArchi;
        string type;
        in>> numNodi;
        in>>numArchi;
        in>>type;
        if(type ==  "int"){
            Graph<int> G;
            int nodi[numNodi];
            int sizeNodi = 0;
            cout<<"inserisco nodi"<<endl;
            for(int i = 0; i< numNodi;i++){ // inserisco nodi
                int nodo;
                in>>nodo;
                sizeNodi++;
                nodi[sizeNodi-1] = nodo;
               // G.setKey(nodo);
            }
            int *nSorted = sortI(nodi, sizeNodi);
            for(int i = 0; i< sizeNodi;i++) G.setKey(nSorted[i]);
            
            
            cout<<"inserisco archi"<<endl;
            for(int i = 0; i< numArchi;i++){ // inserisco archi
                string s1,s2;
                in>>s1>>s2;
                s1 = s1.substr(1);
                s2 = s2.substr(0, s2.length()-1);
                int sorg = atoi(s1.c_str());
                int dest = atoi(s2.c_str());
                G.setAdj(sorg,dest,1);
            }
            
           // G.printAdj();
            // prendo gli archi per l'output e li stampo
            for(int i = 0; i< sizeNodi;i++){
                int * ris = G.getAdjs(nodi[i]);
               // if (ris != NULL){ // se era un nodo che aveva adiacenti
                    int j = 0;
                    out<<"(";
                    while(ris[j] != -1){
                        out<< ris[j];
                        if(ris[j+1] != -1) out<<",";
                        j++;
                    }
                   out<<") ";
                    
              //  }
            }
          
            out<<endl;
        }
    
    
    else if(type ==  "double"){
        Graph<double> G;
        double nodi[numNodi];
        int sizeNodi = 0;
        cout<<"inserisco nodi"<<endl;
        for(int i = 0; i< numNodi;i++){ // inserisco nodi
            double nodo;
            in>>nodo;
            sizeNodi++;
            nodi[sizeNodi-1] = nodo;
            //G.setKey(nodo);
        }
        double *nSorted = sortD(nodi, sizeNodi);
        for(int i = 0; i< sizeNodi;i++) G.setKey(nSorted[i]);
        
        
        
        cout<<"inserisco archi"<<endl;
        for(int i = 0; i< numArchi;i++){ // inserisco archi
            string s1,s2;
            in>>s1>>s2;
            s1 = s1.substr(1);
            s2 = s2.substr(0, s2.length()-1);
            double sorg = atof(s1.c_str());
            double dest = atof(s2.c_str());
            G.setAdj(sorg,dest,1);
        }
        
        // G.printAdj();
        // prendo gli archi per l'output e li stampo
        for(int i = 0; i< sizeNodi;i++){
            double * ris = G.getAdjs(nodi[i]);
           // if (ris != NULL){ // se era un nodo che aveva adiacenti
                int j = 0;
                out<<"(";
                while(ris[j] != -1){
                    out<< ris[j];
                    if(ris[j+1] != -1) out<<",";
                    j++;
                }
                out<<") ";
                
            //}
        }
        
        out<<endl;
    }
    else if(type ==  "char"){
        Graph<char> G;
        char nodi[numNodi];
        int sizeNodi = 0;
        cout<<"inserisco nodi"<<endl;
        for(int i = 0; i< numNodi;i++){ // inserisco nodi
            char nodo;
            in>>nodo;
            sizeNodi++;
            nodi[sizeNodi-1] = nodo;
           // G.setKey(nodo);
        }
        char *nSorted = sortC(nodi, sizeNodi);
        for(int i = 0; i< sizeNodi;i++) G.setKey(nSorted[i]);
        
        cout<<"inserisco archi"<<endl;
        for(int i = 0; i< numArchi;i++){ // inserisco archi
            string s1,s2;
            in>>s1>>s2;
            s1 = s1.substr(1);
            s2 = s2.substr(0, s2.length()-1);
            char sorg = s1[0];
            char dest = s2[0];
            G.setAdj(sorg,dest,1);
        }
        
        // G.printAdj();
        // prendo gli archi per l'output e li stampo
        for(int i = 0; i< sizeNodi;i++){
            char * ris = G.getAdjs(nodi[i]);
            //if (ris != NULL){ // se era un nodo che aveva adiacenti
                int j = 0;
                out<<"(";
                while(ris[j] != -1){
                    out<< ris[j];
                    if(ris[j+1] != -1) out<<",";
                    j++;
                }
                out<<") ";
           // }
        }
        out<<endl;
    }
}
    
    in.close();
    out.close();
    return 0;
}
