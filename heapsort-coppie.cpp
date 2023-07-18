#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
using namespace std;
/*
 heapsort normale(ordinamento crescente) usa un MAX HEAP, e ordina in loco lasciando gli elementi sull'array(non ostante diminuisca il size.
 
 */

template<class K> class Coppia{
public:
    K x;
    K y;
    string coppiaStr; // ristampo questa poi
    Coppia(){coppiaStr = "";}
    Coppia(string s1, string s2, string type){
        if(type == "double"){
            string sub1 = s1.substr(1);
            float n1 = atof(sub1.c_str());
            x = n1;
            string sub2 = s2.substr(0,s2.length()-1);
            float n2 = atof(sub2.c_str());
            y = n2;
            coppiaStr =  s1+" "+s2;
        }
        else if(type == "int" || type == "bool") {
            string sub1 = s1.substr(1);
            int n1 = atoi(sub1.c_str());
            x = n1;
            string sub2 = s2.substr(0,s2.length()-1);
            int n2 = atoi(sub2.c_str());
            y = n2;
            coppiaStr =  s1+" "+s2;
        }
        else if(type == "char") {
            x = s1[1];
            y = s2[0];
            coppiaStr = s1+" "+s2;
        }
    }
};
/*
template <class T> int confr(Coppia<T> a,Coppia<T>  b){
    if (a.x > b.x) return  1;
    else if (a.x < b.x) return -1;
    else if(a.x == b.x && a.y > b.y) return 1;
    else if(a.x == b.x && a.y < b.y) return -1;
    return 0;
    
}*/

template <class H>  class Heap{
private:
    int maxSize;
    int size;
    H* elements;
    
public:
    int heapifyCounter = 0;
    
    int confr(H a,H b){
        if (a.x > b.x) return  1;
        else if (a.x < b.x) return -1;
        else if(a.x == b.x && a.y > b.y) return 1;
        else if(a.x == b.x && a.y < b.y) return -1;
        return 0;
        
    }
    
    
    Heap(int s){
        this->maxSize = s;
        this->size = 0;
        elements = new H[s];
        
    }
    void build_max_heap(){
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
        if(getSxChild(i) < size && confr(elements[getSxChild(i)], elements[max]) >0)  max = getSxChild(i);
        if(getDxChild(i) < size && confr(elements[getDxChild(i)],elements[max]) >0) max = getDxChild(i);
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
    H extract_max(){
        swap(0,size-1);
        size--;
        heapify(0);
        return elements[size];
    }
    void increaseKey(int i, H key){
        elements[i] = key;
        while(i>=0 && confr(elements[getParent(i)],elements[i]) < 0){
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
            Heap<Coppia<int> > H =  Heap<Coppia<int> >(n);
            for(int j = 0; j<n;j++){
                string s1,s2;
                in>>s1>>s2;
                Coppia<int> val =  Coppia<int>(s1,s2,type);
                H.setKey(val);
            }
        
            H.build_max_heap();
            for(int j = 0; j<n;j++){
                H.extract_max();
            }
            out<<H.heapifyCounter-1<<" ";
            for(int j = 0; j<n;j++){
                out<<H.getKey(j).coppiaStr<<" ";
            }
        }
        
       else if(type == "double"){
           Heap<Coppia<double> > H =  Heap<Coppia<double> >(n);
           for(int j = 0; j<n;j++){
               string s1,s2;
               in>>s1>>s2;
               Coppia<double> val =  Coppia<double>(s1,s2,type);
               H.setKey(val);
           }
           H.build_max_heap();
           for(int j = 0; j<n;j++){
               H.extract_max();
           }
           out<<H.heapifyCounter-1<<" ";
           for(int j = 0; j<n;j++){
            out<<H.getKey(j).coppiaStr<<" ";
           }
       
       }
            
        else if(type == "char"){
            Heap<Coppia<char> > H =  Heap<Coppia<char> >(n);
            for(int j = 0; j<n;j++){
                string s1,s2;
                in>>s1>>s2;
                Coppia<char> val =  Coppia<char>(s1,s2,type);
                H.setKey(val);
            }
            H.build_max_heap();
            for(int j = 0; j<n;j++){
                H.extract_max();
            }
            out<<H.heapifyCounter-1<<" ";
            for(int j = 0; j<n;j++){
                out<<H.getKey(j).coppiaStr<<" ";
            }
        
        }
    
        out<<endl;
	}
	in.close();
	out.close();
	return 0;
}




