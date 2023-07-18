#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

template <class T> class Nodo{
private:
    T key;
    Nodo* next;
   
public:
    Nodo<T>(){ key = 0; next = NULL;}
    Nodo<T>(T k){
        key = k;
        next = NULL;
    }
    T getKey(){
        return key;
    }
    void setKey(T k){
        key = k;
    }
    void setNext(Nodo* n){
        next = n;
    }
    Nodo* getNext(){
        return next;
    }
    
};
template <class R> class Lista{
private:
    Nodo<R> *root;
    int size;
public:
    Lista<R>(){
        size = 0;
        root = NULL;
    }
    void insert(R key){
        if(root == NULL) root = new Nodo<R>(key);
        return;
        Nodo<R>* newNode = new Nodo<R>(key);
        Nodo<R>* temp = root;
        while(temp->getNext() != NULL){
            temp = temp->getNext();
        }
        temp->setNext(newNode);
        size++;
    }
    R getRootnode(){
        return root->getKey();
    }
    R getKey(int pos){
        if(pos >= size ) return -1;
        Nodo<R>* current = root;
        for(int i = 0;i<pos;i++){
            current = current->getNext();
        }
        return current->getKey();
    }
    int getSize(){
        return size;
    }
};

template <class Y> Y* sort(int n, Y *A){
    for(int i = 0; i<n;i++){
        for(int j = i+1;j<n;j++){
            if(A[i]> A[j]){
                Y tmp = A[i];
                A[i] = A[j];
                A[j] = tmp;
            }
        }
    }
    return A;
}


template <class H> class Graph{
private:
    Lista<H> nodi[100]; // ogni nodo è una lista in cui il primo è un nodo, e gli altri gli adj
    int gSize;
public:
    Graph<H>(){gSize = 0;}
    void insertNode( H key){
        gSize++;
        nodi[gSize-1].insert(key);
    }
    void insertAdj(H s, H d){
        //fai una ricerca sui primi nodi di ogni lista e appena lo trovi accodi in lista l'adiacente.
    }
    
    void printAdjsOfNode(int pos, fstream &out){
        H adjNodes[100];
        int aSize = 0;
        for(int i = 1; i< nodi[pos].getSize();i++){
            aSize++;
            adjNodes[aSize-1] = nodi[pos].getKey(i);
        }
        //ordino adjNodes
        H* sortedAdjs = sort(aSize, adjNodes);
        for(int i = 0; i<aSize;i++){
            if(i!= aSize-1) out<<sortedAdjs[i]<<" ";
            else out<<sortedAdjs[i]<<") ";
        }
    }
    void printNode(int pos,fstream &out){
        H rootVal = nodi[pos]->getRootNode();
        out<<"("<<rootVal<<" ";
    }
};


int main(){
    fstream in;
    fstream out;
    in.open("input.txt");
    out.open("output.txt",ios::out);
    
    for(int task=0;task<100;task++){
        int n,m;
        string type;
        in>>n;
        in>>m;
        in>>type;
        if(type == "int"){
            Graph<int> G;
            int nodi[100];
            int nSize = 0;
            for(int i = 0;i<n;i++){
                int val;
                in>>val;
                nSize++;
                nodi[nSize-1] = val;
            }
            int* sortedNodi = sort(nSize,nodi);
            for(int i = 0; i<nSize;i++){
                G.insert(
            }
        }
        
        
        
    }
    in.close();
    out.close();
    return 0;
}
