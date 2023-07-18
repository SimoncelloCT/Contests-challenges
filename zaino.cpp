#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;



int main(){
	fstream in;
	fstream out;
	in.open("./input.txt");
	out.open("./output.txt" , ios::out);
	
	for(int i=0; i<100;i++){
        int n,pesoMassimo;
        in>>n;
        in>>pesoMassimo;
        int A[n];
        for(int j = 0; j< n;j++){
            int val;
            in>>val;
            A[j] = val;
        }
        int somma = 0;
        for(int k = 0; k<pesoMassimo;k++){
            int massimo = A[0];
            int posMassimo = 0;
            for(int j = 0; j< n;j++){
                if(A[j] > massimo) {massimo =  A[j]; posMassimo = j; }
            }
            somma += massimo;
            A[posMassimo] = INT_MIN;
        }
        out<<somma<<endl;
        
        
        
        
	}
	in.close();
	out.close();
	return 0;
}




