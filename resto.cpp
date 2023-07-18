#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
using namespace std;

void getMinTagli(int *monete,int n, int resto, fstream &out);
int *sort(int*A, int n);
int main(){
	fstream in;
	fstream out;
	in.open("./input.txt");
	out.open("./output.txt" , ios::out);
	for(int i=0; i<100;i++){
        int r;
        in>>r;
        int n;
        in>>n;
        int monete[n];
        monete[0] = -1; //  osì gli indici partono da 1
        int size = 1 ;
        for(int j = 0 ; j< n;j++){
            int m;
            in>>m;
            size++;
            monete[size-1] = m;
        }
        
        //int ris =
        getMinTagli(monete,size,r, out);
      //  out<<ris<<endl;
      
	}
	in.close();
	out.close();
	return 0;
}

void getMinTagli(int *monete,int n, int resto, fstream &out){
    //r+1 perchè parte da 0 la matrice e a me serve proprio la posizione con il resto = r;
    resto++;
    long M[resto][n];
    // inizializzo prima colonna e prima riga con INT_MAX
    for(int i = 0; i< n;i++){
        M[0][i] = INT_MAX;
    }
    for(int i = 0; i< resto;i++){
        M[i][0] = INT_MAX;
    }
    for(int r = 1; r<resto;r++){ // sui resti
        for(int i = 1; i< n;i++){ //sugli indici monete
            if(monete[i] > r) M[r][i] = INT_MAX;
            else if(monete[i] == r) M[r][i] = 1;
            else{ // monete[i] < r
                long min = INT_MAX;
                for(int k = 1; k<n ; k++){
                    long val =  M[r-monete[i]][k];
                    if(val<min) min = val;
                }
                min = min+1;
                M[r][i] = min;
            }
        }
    }
    //prendo il risultato, è dato dal minimo dell'ultima riga della matrice
    
    int min =  INT_MAX;
    int posMin = 0;
    for(int i = 0; i<n;i++){
        if(M[resto-1][i] < min ) {
            min =  M[resto-1][i];
            posMin = i;
        }
    }
    // il risultato è su min.
    //prendo resti e li stampo
    
    int resti[min]; //dichiaro array resti di dimensione = numero minimo di monete trovato(soluzione)
    // inserisco l'ultima moneta trovata, nella prima posizione
    int restiSize = 1;
    resti[0] = monete[posMin];// è il taglio del primo resto
    
    //decremento resto iniziale che avevo incrementato per avere l'indice corrispondente nella matrice, che partiva da 0
    int restoIniziale = resto-1;
    restoIniziale -= monete[posMin];
    
    while(restoIniziale > 0){ // finchè non arrivo a resto 0
        // cerco il minimo della riga in cui mi trovo(indice restoIniziale)
        int minimo =  INT_MAX;
        int posMin = -1;
        for(int i = 1; i<n;i++){
            if(M[restoIniziale][i] < minimo ) {
                minimo =  M[restoIniziale][i];
                posMin = i; // salvo la posizione in cui ho trovato il minimo, sarà l'indice del taglio di moneta usato
            }
        }
            restiSize++;
            resti[restiSize-1] = monete[posMin]; // inserisco la moneta usata nell'array resti(delle monete usate)
            restoIniziale -= monete[posMin]; //sottraggo la moneta usata al restoIniziale
    }
    
    //ordino l'array resti in ordine crescente
    int * ris = sort(resti,restiSize);
    out<<min<<" ";
    for(int i = 0; i<restiSize;i++){
        out<<ris[i]<<" ";
    }
    out<<endl;
}


int *sort(int*A, int n){
    for(int i = 0; i< n;i++){
        for(int j = i+1 ; j<n;j++){
            if(A[i] > A[j]){
                int tmp = A[i];
                A[i] = A[j];
                A[j] = tmp;
            }
        }
    }
    return A;
}
