#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
using namespace std;

template <class H>  class Heap{
private:
    
    int maxSize;
    int size;
    H* elements;
    
public:
    int heapifyCounter = 0;
    
    Heap(int s){
        
       // cout<<"costruttore"<<endl;
        this->maxSize = s;
        this->size = 0;
        elements = new H[s];
        
    }
    void build_max_heap(){
        //cout<<"building"<<endl;
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
        if(size == 0) return;
        heapifyCounter++;
        int max = i; //posizione
        if(getSxChild(i) < size && elements[getSxChild(i)] > elements[max]) max = getSxChild(i);
        if(getDxChild(i) < size && elements[getDxChild(i)] > elements[max]) max = getDxChild(i);
        if(max != i) {
            swap(max,i);
            heapify(max);
        }
    }
    H getKey(int i){
        return elements[i];
    }
    void setKey(H key){
        size++;
        elements[size-1] = key;
        
    }
    void enqueue(H key){
        size++;
        increaseKey(size-1, key);
    }
    int extract_max(){
        swap(0,size-1);
        size--;
        heapify(0);
        return elements[size];
    }
    void increaseKey(int i, H key){
        elements[i] = key;
        while(i>=0 && elements[getParent(i)] < elements[i]){
            swap(i,getParent(i));
            i = getParent(i);
        }
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
                int val;
                in>>val;
                H.setKey(val);
            }
            H.build_max_heap();
            for(int j = 0; j<n;j++){
                H.extract_max();
            }
            out<<H.heapifyCounter-1<<endl;
            /*for(int j = 0; j<H.getSize();j++){
                out<<H.getKey(j)<<" ";
            }*/
        }
        
       else if(type == "double"){
           Heap<double> H =  Heap<double>(n);
           for(int j = 0; j<n;j++){
               double val;
               in>>val;
               H.setKey(val);
           }
           H.build_max_heap();
           for(int j = 0; j<n;j++){
               H.extract_max();
           }
           out<<H.heapifyCounter-1<<endl;
           /*for(int j = 0; j<H.getSize();j++){
            out<<H.getKey(j)<<" ";
            }*/
       
       }
            
        else if(type == "char"){
            Heap<char> H =  Heap<char>(n);
            for(int j = 0; j<n;j++){
                char val;
                in>>val;
                H.setKey(val);
            }
            H.build_max_heap();
            for(int j = 0; j<n;j++){
                H.extract_max();
            }
            out<<H.heapifyCounter-1<<endl;
            /*for(int j = 0; j<H.getSize();j++){
             out<<H.getKey(j)<<" ";
             }*/
        
        }
    
     //   out<<endl;
	}
	in.close();
	out.close();
	return 0;
}




