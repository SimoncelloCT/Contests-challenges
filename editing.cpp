#include <iostream>
#include <fstream>
using namespace std;

int editing(string s1, string s2);


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
        string x,y;
        in>>x;
        in>>y;
        out<<editing(x,y)<<endl;
	}
	in.close();
	out.close();
	return 0;
}

int editing(string s1, string s2){
    int n = s1.length();
    int m = s2.length();
    int M[n+1][m+1];
    
    //casi base
    M[0][0] = 0;
    for(int i = 1; i <= n; i++) M[i][0] = i;
    for(int j = 1; j <= m; j++) M[0][j] = j;
    
    //Caso generale
    for(int i = 1; i<= n; i++){
        for(int j = 1; j<= m;j++){
            if(s1[i-1] == s2[j-1]) M[i][j] = M[i-1][j-1];
            else {
                M[i][j] = 1 + min(min(M[i][j-1], M[i-1][j]), M[i-1][j-1]);
            }
        }
    }

    return M[n][m];
}


