#include <iostream>
#include <fstream>
using namespace std;


int lcs(string s1, string s2, int n, int m );
string printLcs(string s1, string s2, int n, int m );


int main(){
	fstream in;
	fstream out;
	in.open("./input.txt");
	out.open("./output.txt" , ios::out);
	
	for(int i=0; i<100;i++){
		int n; 								
		in>>n;
        int m;
        in>>m;
        string s1,s2;
        in>>s1;
        in>>s2;
        //out<<lcs(s1,s2,n,m)<<endl;
        out<<printLcs(s1,s2,n,m)<<endl;
	}
	in.close();
	out.close();
	return 0;
}

int lcs(string s1, string s2, int n, int m ){
    int C[n+1][m+1];
    for(int i = 0; i<= n; i++) C[i][0] = 0;
    for(int i = 0; i<= m; i++) C[0][i] = 0;
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            if(s1[i-1] == s2[j-1]) C[i][j] = C[i-1][j-1]+1;
            else C[i][j] = max(C[i-1][j],C[i][j-1]);
        }
    }
    return C[n][m];
}


string printLcs(string s1, string s2, int n, int m ){
    int M[n+1][m+1];
    for(int i = 0; i<= n; i++) M[i][0] = 0;
    for(int i = 0; i<= m; i++) M[0][i] = 0;
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            if(s1[i-1] == s2[j-1]) M[i][j] = M[i-1][j-1]+1;
            else M[i][j] = max(M[i-1][j],M[i][j-1]);
        }
    }
    
    //trova la stringa
    string subseq= "";
    int i = s1.length();
    int j = s2.length();
    while(i>0 && j>0){
        if(s1[i-1] == s2[j-1]){ //se le stringhe in posizione i-1, j-1 sono uguali
                                // metto in subseq il carattere in pos i-1 e incremento gli indici
            subseq += s1[i-1];
            i--;
            j--;
        }
        else if (M[i-1][j] > M[i][j-1]) i--; // se la matrice nella riga precedente è maggiore di quella nella colonna precedente, incremento la riga
        else j--; // viceversa incremento la colonna
    }
    reverse(subseq.begin(), subseq.end()); // inverto la stringa
    return subseq;
}


