#include <iostream>
#include <fstream>
using namespace std;

//to_string(int);

class Activity{
public:
    string coppia;
    int s;
    int f;
    Activity(){s = 0; f = 0; coppia =  "";}
    Activity(string first, string second){ // costruttore per spazi
        coppia =  first+" "+second;
        string firstNumberString = first.substr(1);
        int si = atoi(firstNumberString.c_str());
        string secondNumberString = second.substr(0,second.length()-1);
        int fi = atoi(secondNumberString.c_str());
        s = si;
        f = fi;
        
    }
};


int maxActivity(Activity *A,int n);
void sortActivity(Activity *A,int n);
int main(){
	fstream in;
	fstream out;
	in.open("./input.txt");
	out.open("./output.txt" , ios::out);
	
	for(int i=0; i<100;i++){
		int n; 								
		in>>n;
        Activity A[n];
        
        for(int j=0; j<n;j++ ){
            string v,v1;
            in>>v;
            in>>v1;
            A[j] = Activity(v,v1);
            
        }
        out<<maxActivity(A,n)<<endl;
	}
	in.close();
	out.close();
	return 0;
}

int maxActivity(Activity *A,int n){
    sortActivity(A,n);
    int cardinalita = 1;
    int i,j;
    i = 0;
    j = 1;
    while(i<n && j<=n){
        if(A[i].f <= A[j].s) {
            cardinalita++;
            i = j;
            j++;
        }
        else{
            j++;
        }
    }
    return cardinalita;
}

void sortActivity(Activity *A,int n){
    for(int i = 0; i< n; i++){
        for(int j = i+1; j<n;j++){
            if(A[i].f > A[j].f) {
                Activity tmp = A[i];
                A[i] = A[j];
                A[j] = tmp;
            }
        }
    }
}
