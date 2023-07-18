#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
using namespace std;
/*
 heapsort normale(ordinamento crescente) usa un MAX HEAP, e ordina in loco lasciando gli elementi sull'array(non ostante diminuisca il size.
 
 */

template<class K> class Tripla{
public:
    K x;
    K y;
    K z;
    string triplaStr; // ristampo questa poi
    Tripla(){triplaStr = "";}
    Tripla(string s1, string s2,string s3, string type){
        if(type == "double"){
            string sub1 = s1.substr(1);
            float n1 = atof(sub1.c_str());
            x = n1;
            
            float n2 = atof(s2.c_str());
            y = n2;
            
            string sub3 = s3.substr(0,s3.length()-1);
            float n3 = atof(sub3.c_str());
            z = n3;
        }
        else if(type == "int" || type == "bool") {
            string sub1 = s1.substr(1);
            int n1 = atoi(sub1.c_str());
            x = n1;
            
            int n2 = atoi(s2.c_str());
            y = n2;
            
            string sub3 = s3.substr(0,s3.length()-1);
            int n3 = atoi(sub3.c_str());
            z = n3;
            
        }
        else if(type == "char") {
            x = s1[1];
            y = s2[0];
            z = s3[0];
            
        }
         triplaStr =  s1+" "+s2+" "+s3;
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
    
    //MOLTO IMPORTANTE
    int confr(H a,H b){
        if (a.x > b.x) return  1;
        else if (a.x < b.x) return -1;
        else if(a.x == b.x && a.y > b.y) return 1;
        else if(a.x == b.x && a.y < b.y) return -1;
        else if(a.x == b.x && a.y == b.y && a.z > b.z) return 1;
        else if(a.x == b.x && a.y == b.y && a.z < b.z) return -1;
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
            Heap<Tripla<int> > H =  Heap<Tripla<int> >(n);
            for(int j = 0; j<n;j++){
                string s1,s2,s3;
                in>>s1>>s2>>s3;
                Tripla<int> val =  Tripla<int>(s1,s2,s3,type);
                H.setKey(val);
            }
        
            H.build_max_heap();
            for(int j = 0; j<n;j++){
                H.extract_max();
            }
            out<<H.heapifyCounter-1<<" ";
            for(int j = 0; j<n;j++){
                out<<H.getKey(j).triplaStr<<" ";
            }
        }
        
       else if(type == "double"){
           Heap<Tripla<double> > H =  Heap<Tripla<double> >(n);
           for(int j = 0; j<n;j++){
               string s1,s2,s3;
               in>>s1>>s2>>s3;
               Tripla<double> val =  Tripla<double>(s1,s2,s3,type);
               H.setKey(val);
           }
           H.build_max_heap();
           for(int j = 0; j<n;j++){
               H.extract_max();
           }
           out<<H.heapifyCounter-1<<" ";
           for(int j = 0; j<n;j++){
            out<<H.getKey(j).triplaStr<<" ";
           }
       
       }
            
        else if(type == "char"){
            Heap<Tripla<char> > H =  Heap<Tripla<char> >(n);
            for(int j = 0; j<n;j++){
                string s1,s2,s3;
                in>>s1>>s2>>s3;
                Tripla<char> val =  Tripla<char>(s1,s2,s3,type);
                H.setKey(val);
            }
            H.build_max_heap();
            for(int j = 0; j<n;j++){
                H.extract_max();
            }
            out<<H.heapifyCounter-1<<" ";
            for(int j = 0; j<n;j++){
                out<<H.getKey(j).triplaStr<<" ";
            }
        
        }
    
        out<<endl;
	}
	in.close();
	out.close();
	return 0;
}




