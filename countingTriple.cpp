#include <iostream>
#include <fstream>
using namespace std;

//to_string(int);

class Tripla{
public:
    string tripla;
    double first;
    int firstMult;
    Tripla(){first = 0; tripla =  "";}
    Tripla(string first, string second, string third){ // costruttore per spazi
        tripla =  first+" "+second+" "+third;
        string f = first.substr(1);
        double fi = atof(f.c_str());
        this->first = fi;
        double m  = this->first*10;
        firstMult = (int) m;
    }
    
    Tripla(string c){ // costruttore per virgola da sistemare
        tripla = c;
        int virg =  c.find(",");
        string f = c.substr(1,c.length()-(c.length()-virg)-1);
        double first = atof(f.c_str());
        string s = c.substr(virg+1, c.length()-virg-2);
        this->first = first;
        double m  = first*10;
        firstMult = (int) m;
    }
    Tripla(double f, string c){
        tripla = c;
        first = f;
        double m  = first*10;
        firstMult = (int) m;
    }
};


void countingSort(Tripla *A, int n,fstream &out);
int findMax(Tripla *A, int n);
int findMin(Tripla *A,int n);
int main(){
	fstream in;
	fstream out;
	in.open("./input.txt");
	out.open("./output.txt" , ios::out);
	
	for(int i=0; i<100;i++){
		int n; 								
		in>>n;
        Tripla A[n];
        
        for(int j=0; j<n;j++ ){
            string v,v1,v2;
            in>>v;
            in>>v1;
            in>>v2;
           // v = v+","+v1;
            //cout<<v<<endl;
            A[j] = Tripla(v,v1,v2);
        }
        
        
         countingSort(A,n, out);
	}
	in.close();
	out.close();
	return 0;
}

void countingSort(Tripla *A, int n, fstream &out){
    
    int max =  findMax(A,n);
    int min = findMin(A,n);
    int offset = max-min+1;
    int C[offset];
    for(int i = 0; i<offset; i++) C[i] = 0;
    for(int i = 0; i<n; i++) C[A[i].firstMult-min]++;
    for(int i = 1; i< offset;i++)C[i] += C[i-1];
    Tripla B[n];
    //for(int i = 0; i< n;i++) B[i] = 0;
    //DA RICORDARE
    for(int i = n-1; i >= 0; i--){
        B[C[A[i].firstMult-min]-1] = A[i];
        C[A[i].firstMult-min]--;
    }
    for(int j = 0; j< offset;j++){ //stampo C
        out<<C[j]<<" ";
    }
    for(int j = 0; j< n;j++){ //stampo B
        out<<B[j].tripla<<" ";
    }
    out<<endl;
}
int findMax(Tripla *A, int n){
    double max = A[0].firstMult;
    for(int i = 0; i <n;i++){
        if (A[i].firstMult > max) max =  A[i].firstMult;
    }
    //cout<<max<<endl;
    return max;
    
}
int findMin(Tripla *A,int n){
    double min = A[0].firstMult;
    for(int i = 0; i <n;i++){
        if (A[i].firstMult < min) min =  A[i].firstMult;
    }
    //cout<<min<<endl;
    return min;
    
}

