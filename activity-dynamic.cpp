#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
using namespace std;


class Activity{
public:
    int s;
    int f;
    Activity(){
        
    }
    Activity(int start, int end){
        s = start;
        f = end;
    }
};
int maximizeActivity(Activity* A, int n);
Activity* sort(Activity* A, int n);
int main(){
	fstream in;
	fstream out;
	in.open("./input.txt");
	out.open("./output.txt" , ios::out);
	for(int i=0; i<100;i++){
        int n;
        in>>n;
        Activity A[n];
        int size = 1;
        A[0] = Activity(0,0); // così l'array parte da 1 come indici a1 a2 a3.. an
        for(int j = 0; j<n ;j++){
            string s1,s2;
            in>>s1>>s2;
            s1 = s1.substr(1);
            s2 = s2.substr(0,s2.length()-1);
            int s = atoi(s1.c_str());
            int f = atoi(s2.c_str());
            size++;
            A[size-1] = Activity(s,f);
        }
        
        Activity* Asorted = sort(A, size);
        for(int j = 0; j< size; j++){
            cout<<"("<<A[j].s<<" "<<A[j].f<<")"<<" ";
        }
        int ris = maximizeActivity(A,size);
        out<<ris<<endl;
	}
	in.close();
	out.close();
	return 0;
}

int getMaxTime(Activity *A, int n){
    int max =  INT_MIN;
    for(int i = 0; i< n;i++){
        if(max < A[i].f) max = A[i].f;
    }
    return max;
}

int maximizeActivity(Activity* A, int n){
    int maxTime = getMaxTime(A, n);
    maxTime += 1; // considero il caso tempo =0
    //((n è corretto perchè l'array parte da 1 delle atttività))
    int M[maxTime][n];
    for(int t = 0;t<maxTime;t++){ // indice tempi(righe)
        for(int i = 0; i< n; i++){ // indice attività iesima(colonne)
            if(i == 0 || t == 0 ) M[t][i] = 0;
            else if(t<A[i].f) M[t][i] = M[t][i-1];
            else {
                M[t][i] = max(M[t][i-1],M[A[i].s][i-1] + (A[i].f - A[i].s));
            }
        
        }
    }
    return M[maxTime-1][n-1];
}

Activity* sort(Activity* A, int n){
    for(int i = 1; i< n;i++){
        for(int j = i+1;j<n;j++){
            if(A[i].f > A[j].f) {
                Activity tmp = A[i];
                A[i] = A[j];
                A[j] = tmp;
            }
        }
    }
    return A;
}
