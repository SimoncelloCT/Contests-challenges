#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

template <class H>  class Heap{
private:
    
    int maxSize;
    int size;
    H* elements;
public:
    Heap(int s){
        
        cout<<"costruttore"<<endl;
        this->maxSize = s;
        this->size = 0;
        elements = new H[s];
        
    }
    void build_min_heap(){
        cout<<"building"<<endl;
        for(int i = floor(size/2); i>=0; i--){
            heapify(i);
        }
    }
    void swap(int a,int b){
        H temp =  elements[a];
        elements[a] = elements[b];
        elements[b] = temp;
    }
    void heapify(int i){
        int min = i; //posizione
        if(getSxChild(i) < size && elements[getSxChild(i)] < elements[min]) min = getSxChild(i);
        if(getDxChild(i) < size && elements[getDxChild(i)] < elements[min]) min = getDxChild(i);
        if(min != i) {
            swap(min,i);
            heapify(min);
        }
    }
    void enqueue(H key){
        size++;
        decreaseKey(size-1, key);
        
    }
    void decreaseKey(int i, H key){
        elements[i] = key;
        while(i>=0 && elements[getParent(i)] > elements[i]){
            swap(i,getParent(i));
            i = getParent(i);
        }
    }
    
    H getKey(int i){
        return elements[i];
    }
    void setKey(H key){
        size++;
        elements[size-1] = key;
        
    }
    
    int getParent(int i){
        return floor((i-1)/2);
    }
    int getSxChild(int i){
        return i*2+1;
    }
    int getDxChild(int i){
        return i*2+2;
    }
    int getSize(){
        return size;
    }
    
    
    
};


int main(){
	fstream in;
	fstream out;
	in.open("./input.txt");
	out.open("./output.txt" , ios::out);
	
	for(int i=0; i<100;i++){
        string type;
        int n;
        in>> type;
        in>> n;
        
        if(type == "int" || type == "bool"){
            Heap<int> H =  Heap<int>(n);
            for(int j = 0; j<n;j++){
                int x;
                in>>x;
                H.enqueue(x);
            }
           // H.build_min_heap();
            for(int j = 0; j<n;j++){
                out<<H.getKey(j)<<" ";
            }
        }
        
       else if(type == "double"){
            Heap<double> H =  Heap<double>(n);
            for(int j = 0; j<n;j++){
                double x;
                in>>x;
                H.enqueue(x);
            }
           // H.build_min_heap();
            for(int j = 0; j<n;j++){
                out<<H.getKey(j)<<" ";
            }
       }
            
        else if(type == "char"){
                Heap<char> H =  Heap<char>(n);
                for(int j = 0; j<n;j++){
                    char x;
                    in>>x;
                    H.enqueue(x);
                }
               // H.build_min_heap();
                for(int j = 0; j<n;j++){
                    out<<H.getKey(j)<<" ";
                }
        }
    
        out<<endl;
	}
	in.close();
	out.close();
	return 0;
}




