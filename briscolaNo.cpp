#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
using namespace std;
//61

class Activity{
public:
    int g;
    int s;
    int f;
    int t;
    int v;
    
    Activity(){
        
    }
    Activity(int giorno,int start, int end,int tax, int vinc){
        g = giorno;
        s = start;
        f = end;
        t = tax;
        v = vinc;
    }
};
int maximizeActivity(Activity* A,int offset, int n,int budget);
Activity* sort(Activity* A, int n);
Activity* sortbyEndTime(Activity* A,int n);
int main(){
	fstream in;
	fstream out;
	in.open("./input.txt");
	out.open("./output.txt" , ios::out);
	for(int i=0; i<100;i++){
        int n,budget;
        in>>n;
        in>>budget;
        Activity A[500];
        int size = 1;
        A[0] = Activity(0,0,0,0,0); // così l'array parte da 1 come indici a1 a2 a3.. an
        //else  A[0] = Activity(1,0,0,0,0);
        for(int j = 0; j<n ;j++){
            int g,s,f,t,v;
            in>>g>>s>>f>>t>>v;
            size++;
            A[size-1] = Activity(g,s,f,t,v);
        }
        
        Activity* Asorted = sort(A, size);
        for(int j = 0; j< size; j++){
            cout<<"("<<A[j].g<<" "<<A[j].s<<" "<<A[j].f<<" "<<A[j].t<<" "<<A[j].v<<""<<") ";
        }
        cout<<endl;
        int offsetArray[100];
        int offSize = 1;
        offsetArray[0] = 0;
        int h = 1;
        for(int k = 1; k< size;k++){
            if( A[k-1].g != A[k].g){
                
                for(int b = size;b>k;b--){
                    A[b] = A[b-1];
                }
               // A[k] = Activity(h,0,0,0,0);
                size++;
                offSize++;
                offsetArray[h] = k;
                h++;
            }
            if(k == size-1){
                offsetArray[h] = size;
                offSize++;
            }
            
        }
        for(int u = 0;u<offSize;u++) cout<<offsetArray[u]<<" ";
        for(int j = 0; j< size; j++){
            cout<<"      "<<A[j].g<<" "<<A[j].s<<" "<<A[j].f<<" "<<A[j].t<<" "<<A[j].v<<""<<"     ";
        }
        //return 0;
        int acc = budget;
        for(int k = 1; k< offSize;k++){
            cout<<"COLPO N."<<k<<endl;
           int ris = maximizeActivity(A,offsetArray[k-1],offsetArray[k],acc);
            acc = ris;
            //acc+=ris;
        }
        
        
        out<<acc<<endl;
	}
	in.close();
	out.close();
	return 0;
}

int getMaxTime(Activity *A,int offset, int n){
    int max =  INT_MIN;
    for(int i = offset; i< n;i++){
        if(max < A[i].f) max = A[i].f;
    }
    return max;
}

int maximizeActivity(Activity* A,int offset, int n, int budget){
    cout<<"entro con i: "<<offset<<" end: "<<n<<endl;
    cout<<"parto con budget: "<<budget<<endl;
    int maxTime = getMaxTime(A,offset,n);
    maxTime += 1; // considero il caso tempo = 0
    //((n è corretto perchè l'array parte da 1 delle atttività))
    //n+=1;
    int M[maxTime][n-offset];
    for(int t = 0;t<maxTime;t++){ // indice tempi(righe)
        for(int i = 0; i< n-offset; i++){ // indice attività iesima(colonne)
            if(i == 0 || t == 0 ) M[t][i] = 0;
            //|| (A[i+offset].s < A[i+offset-1].f)
            else if(t<A[i+offset].f || budget < A[i+offset].t ) M[t][i] = M[t][i-1];
            else {
                if(M[t][i-1] > M[A[i+offset].s][i-1] + (A[i+offset].v-A[i+offset].t)){
                    M[t][i] = M[t][i-1];
                }
                else{
                   // cout<<"vincite attuali:"<< M[A[i].s][i-1]<<endl;;
                    cout<<"seleziono attività: "<<i+offset<<endl;
                    M[t][i] = M[A[i+offset].s][i-1] + (A[i+offset].v-A[i+offset].t);
                    cout<<"vincita di questa attività: "<<A[i+offset].v-A[i+offset].t<<endl;
                   // budget += A[i+offset].v-A[i+offset].t;
                    //cout<<"vincite :"<< M[t][i]<<endl;;
                }
               // M[t][i] = max(M[t][i-1],M[A[i].s][i-1] + A[i].v);
            }
            
        
        }
    }
    cout<<"ritorno"<<M[maxTime-1][n-offset-1]+budget<<endl;;
    return M[maxTime-1][n-offset-1]+budget;
}

Activity* sort(Activity* A, int n){
    for(int i = 1; i< n;i++){
        for(int j = i+1;j<n;j++){
            if(A[i].g > A[j].g) {
                Activity tmp = A[i];
                A[i] = A[j];
                A[j] = tmp;
            }
        }
    }
    Activity * B = sortbyEndTime(A,n);
    return B;
}
Activity* sortbyEndTime(Activity* A,int n){
    for(int i = 1; i< n;i++){
        for(int j = i+1;j<n;j++){
            
            if(A[i].g == A[j].g && A[i].f > A[j].f) {
                Activity tmp = A[i];
                A[i] = A[j];
                A[j] = tmp;
            }
        }
    }
    
    return A;
}
