#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
using namespace std;
int matrix_chain(int* dim, int n);

int main(){
	fstream in;
	fstream out;
	in.open("./input.txt");
	out.open("./output.txt" , ios::out);
	for(int i=0; i<100;i++){
        int nMatrici;
        in>>nMatrici;
        int dim[nMatrici+1];
        int dimSize = 0;
        
        for(int j = 0; j<nMatrici ;j++){
            string s;
            in>>s;
            int x =  s.find("x");
            string dimN = s.substr(0,x); //(1
            string dimM = s.substr(x+1); //1)
            dimN = dimN.substr(1);
            dimM = dimM.substr(0,dimM.length()-1);
            int n = atoi(dimN.c_str());
            int m = atoi(dimM.c_str());
            
            if(j == 0) {//inserisco n ed m
                dimSize++;
                dim[dimSize-1]= n;
                dimSize++;
                dim[dimSize-1] = m;
            }
            else{
                dimSize++;
                dim[dimSize-1] = m;
            }
            
        }
        int ris = matrix_chain(dim,dimSize);
        out<<ris<<endl;
	}
	in.close();
	out.close();
	return 0;
}


int matrix_chain(int* dim, int n){ // è la dimensione del vettore di dimensioni matrici, c'è una dim in più rispetto al num di matrici
    int m = n-1; //num matrici
    int M[m][m];
    // inizializzo tutti i casi base a 0 (diagonale)
    for(int i = 0; i< m;i++) M[i][i] = 0;
   
    // offset serve per spostare la j di 1 ogni volta, e riempire la matrice per diagonali a partire da quella sopra quella principale
    for(int offset = 1; offset < m ;offset++){
        int i = 0; // i riparte da 0 e offset si è spostato di uno, quindi riempirò la diagonale sopra la precedente
        int j = offset;
        while(j< m){
            // prendo il minimo delle parentesizzazioni possibili facendo variare k da i a j-1
            int min = INT_MAX;
            for(int k = i; k<j;k++){
                int val = M[i][k] + M[k+1][j] + dim[i] * dim[k+1] * dim[j+1];
                if (val < min ) min = val;
            }
            M[i][j] = min;
            
            i++;
            j++;
        }
    }
    return M[0][m-1];
}

