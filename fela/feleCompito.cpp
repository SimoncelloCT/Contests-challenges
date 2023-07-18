#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#define dim 100
using namespace std;
class Node{
public:
    int S;
    int D;
    int inizio;
    int fine;
    vector<int> Ad;
    bool visitato;
    int tempo;
    Node(){
        S  = -1;
        D = -1;
        inizio = -1;
        fine = -1;
        visitato = false;
        tempo = 0;
        
    }
    Node(int s,int d, int f, int l){
        S  = s;
        D = d;
        inizio = f;
        fine = l;
        visitato = false;
        tempo = 0;
    }
    bool operator==( Node const  rhs) const { return this->S == rhs.S;}
};

void Adiacenti(vector<Node> &vec);
void viaggio(vector<Node> vec, int indice, int D, int &Tbest, int tempo);
bool ControlViaggio(vector<Node> vec, int S, int D);

int main(){
    ifstream fs("input.txt");
    ofstream ofs("output.txt");
    int y=0;
    while(y<dim){
	    cout<<"riga: "<<y+1<<endl<<endl;
        int n,m;
        fs>>n; 
        fs>>m;
        vector <Node> vec; 
        
        for(int j = 0; j<m;j++){ 
            int s,d,f,l;
            fs>>s;
            fs>>d;
            fs>>f;
            fs>>l;
            Node n1 = Node(s,d,f,l);
            if(s != n-1) vec.push_back(n1); 
            if(s != 0 && d != n-1) {Node n2 = Node(d,s,f,l); vec.push_back(n2);} 
            
        }
        Adiacenti(vec);
        int Tbest = 15;
        for(int h =0; h< vec.size();h++){
            if(vec[h].S == 0 && ControlViaggio(vec,h,n-1)) {
                viaggio(vec,h,n-1,Tbest,vec[h].inizio+1);
                
            }
        }
        if(Tbest == 15) Tbest = -1;
        cout<<Tbest<<endl;
        ofs<<Tbest<<endl;
        y++;
        
    }
    return 0;
}



void viaggio(vector<Node> vec, int indice, int D, int &Tbest, int tempo){
    
    if(tempo >= Tbest){ return;}
    if(vec[indice].D == D) if(tempo < Tbest) { Tbest = tempo;  return;}
    
    
     for(int i = 0; i<vec[indice].Ad.size();i++){
         int c = vec[indice].Ad[i];
         if(tempo < vec[c].fine){
             if(tempo < vec[c].inizio) { 
                  viaggio(vec,c,D,Tbest,vec[c].inizio+1);
             
             }
             else{
                 viaggio(vec,c,D,Tbest,tempo+1);
             }
        }
     }
}

bool ControlViaggio(vector<Node> vec, int S, int D){

    vector<Node> ST;
    ST.push_back(vec[S]);
    vec[S].visitato = true;
    while(ST.size() != 0 ){
        Node Elem = ST.back();
        ST.pop_back();
        for(int i = 0; i<Elem.Ad.size();i++){
            if(vec[Elem.Ad[i]].visitato == false){
                if(vec[Elem.Ad[i]].D == D) return true;
                ST.push_back(vec[Elem.Ad[i]]);
                vec[Elem.Ad[i]].visitato = true;
            }
        }
    }
    return false;
}
void Adiacenti(vector<Node> &vec){ 
    for(int i = 0; i<vec.size();i++){
        for(int j = 0; j<vec.size();j++){
            if(vec[i].D == vec[j].S && vec[i].S != vec[j].D){
                int tempo =  vec[i].inizio + 1;
                if(tempo < vec[j].fine) vec[i].Ad.push_back(j);
            }
        }
    }
}

