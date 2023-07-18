#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#define dim 100
using namespace std;
struct word{
    string s;
    int count;
};

string findEasyPsw(string A, int m);//senza interruzioni

string findWithIntPsw(string a, int m, int maxInterGroup, int maxInterNum);

string find1IntPsw(string A,int m);//una sola interruzione di massimo 4 char
string find2IntPsw(string A,int m);//due interruzioni di max 3 char
string find3IntPsw(string A,int m );//3 interruzioni di massimo 3 char


void print(string A);

int main(){
    fflush(stdout);
    ifstream file;
    int n;
    int m;
    string vec[dim];
    int i=0;
    file.open("./input.txt");
    ofstream out;
    out.open("output.txt");
    while(i<dim){
        cout<<endl<<"riga n. "<<i+1<<endl;
        file>>n;
        file>>m;
    	string vec;
        file>>vec;
        string ret;
    
        if(i<= 19)  ret = findEasyPsw(vec,m);
        else if(i >=20 && i<= 39) ret = findWithIntPsw(vec,m,1,4);
        else if(i >=40 && i<= 59) ret = findWithIntPsw(vec,m,2,3);
        else ret = findWithIntPsw(vec,m,3,3);
        cout<<ret<<endl;
         out<<ret<<endl;
        i++;
    }
   

    
    file.close();
    out.close();
    return 0;
}


string findEasyPsw(string a, int m){
    word maxRepeated;
    maxRepeated.s ="non trovato";
    maxRepeated.count = 0;
    for(int i=0; i< a.length()-m;i++){
        word w;
        w.s = a.substr(i,m); w.count = 0;
        string newA = a;
        newA.erase(newA.begin()+i,newA.begin()+i+m);
        for(int j = 0; j<newA.length()-m;j++){
            if(w.s[0] == newA[j]) {
                string s = newA;
                s.erase(s.begin(),s.begin()+j);
                int c = 1;
                while(c < w.s.length() && w.s[c] == s[c])c++;
                if(c == w.s.length()){ w.count++;}
            }
        }
        if(w.count > maxRepeated.count) maxRepeated = w;
    }
    return maxRepeated.s;
}


string findWithIntPsw(string a, int m, int maxInterGroup, int maxInterNum){
    word maxRepeated;
    maxRepeated.s ="non trovato";
    maxRepeated.count = 0;
    for(int i=0; i< a.length()-m+1;i++){
        word w;w.s = a.substr(i,m); w.count = 0;
        bool eq=false;
        for(int k=0;k<m;k++)
        {
        	for(int h=k+1;h<m;h++)
        	{
        		if(w.s[k]==w.s[h])eq=true;	
			}
		}
		if(!eq){
        string newA = a;
        newA.erase(newA.begin()+i,newA.begin()+i+m);
        for(int j = 0; j<newA.length()-m;j++){
            int canCountInter = 0;
            if(w.s[0] == newA[j]) 
			{
                string s = newA;
                s.erase(0,j);
                int c = 1;
                
                while(c < m){
                	
                    if(w.s[c] == s[c])
					{
						c++;
					}
                    else if(canCountInter < maxInterGroup&&w.s[c] != s[c]){ //sono diversi
                    
                        int inter = 0;
                        while(  w.s[c] != s[c]&&inter < maxInterNum&&c<s.length()) {inter++; s.erase(c,1);}//riduce la stringa levando le interruzioni
                        
                        canCountInter ++;
                        
                    }
                    else break; //non posso più contare interruzioni
                }
                
             //  cout<<"C:"<<c<<endl;
                
                if(c == m){ w.count++;}
            }
        }
        if(w.count > maxRepeated.count) 
		{
			cout<<"w.count > maxRepeated.count"<<w.count<<">"<<maxRepeated.count<<endl;
			cout<<w.s<<endl;
			maxRepeated = w;
				
		}
    }
}
    return maxRepeated.s;
}

/*


string findWithIntPsw(string a, int m, int maxInterGroup, int maxInterNum){
    word maxRepeated;
    maxRepeated.s.reserve(a.length());
    maxRepeated.s ="non trovato";
    maxRepeated.count = 0;
    for(int i=0; i< a.length()-m;i++){
        word w;
        w.s = a.substr(i,m); w.count = 0;
        bool eq = false;
        for(int u = 0; u< w.s.length(); u++){
            for(int e = u+1; e<w.s.length();e++){
                if(w.s[u] == w.s[e]) eq =  true;
            }
        }
        if(!eq){
             cout<<"word scelta: "<<w.s<<endl;
            string newA;
            newA.reserve(a.length());
            newA = a;
            newA.erase(newA.begin()+i,newA.begin()+i+m);
            cout<<"lunghezza iniziale della stringa, eliminando quella presa = "<<newA.length()<<endl;
            
            for(int j = 0; j<newA.length()-m;j++){
                if(w.s[0] == newA[j]) {
                    cout<<"possibile inizio at index: "<<j<<endl;
                    cout<<"possible psw= "<<w.s<<endl;
                    //possibile occorrenza dell psw
                    string s;
                    s.reserve(newA.length());
                    s = newA;
                    s.erase(s.begin(),s.begin()+j);
                    int c = 1;
                    cout<<"lunghezza di s accorciata per partire dallo stesso indice: "<<s.length()<<endl;
                    cout<<"s= "<<s<<endl;
                    
                    int canCountInter = 0;
                    
                    while(c < w.s.length()){
                        cout<<"lunghezza di s dopo il while che controlla se incrementare o andare alle interruzioni : "<<s.length()<<endl;
                        if(w.s[0] == s[c]) cout<<"TRA LE INTERRUZIONI C'� UN CARATTERE CHE � UGUALE A W.S[0]"<<endl;
                        if(w.s[c] == s[c]){cout<<"char uguale c++"<<endl;c++;}
                        else if(canCountInter < maxInterGroup){ //sono diversi
                            int inter = 0;
                            while(inter < maxInterNum && w.s[c] != s[c] && c<s.length()) {
                                inter++;
                                s.erase(s.begin()+c);
                                cout<<"interruzioni= "<<inter<<endl;
                                cout<<"s= "<<s<<endl;//riduce la stringa levando le interruzioni
                            }
                            if(inter >= maxInterNum) cout<<"oltre il max di interruzioni"<<endl;
                            canCountInter ++;
                        }
                        else {cout<<"oltre i num di gruppi di interruzioni"<<endl; break; }//non posso pi� contare interruzioni
                        
                    }
                    
                    cout<<"c:  "<<c<<" w.s.length()= "<<w.s.length()<<endl;
                    if(c == w.s.length()){ w.count++; cout<<"trovata "<<w.count<<" volte"<<endl;}
                     else {cout<<"non trovata"<<endl;}
                     cout<<endl;
                }
            }
            if(w.count > maxRepeated.count) maxRepeated = w;
            
        }
    }
    return maxRepeated.s;
}

/*
string find1IntPsw(string a,int m){
    word maxRepeated;
    maxRepeated.s ="non trovato";
    maxRepeated.count = 0;
    
    for(int i=0; i< a.length()-m;i++){
        word w;
        w.s = a.substr(i,m);
        w.count = 0;
       // cout<<"word scelta = "<<w.s<<endl;
        string newA = a;
        newA.erase(newA.begin()+i,newA.begin()+i+m); // elimino la parte che ho preso come word
        
        for(int j = 0; j<newA.length() -m;j++){
            if(w.s[0] == newA[j]) {
                string s = newA;
                s.erase(s.begin(),s.begin()+j);
                int c = 1;
                int canCountInter = 0;
                while(c < w.s.length()){
                    if(w.s[c] == s[c])c++;
                    else if(canCountInter < 1){ //sono diversi
                        int inter = 0;
                        while(inter < 4 && w.s[c] != s[c]) inter++; s.erase(s.begin()+c);//riduce la stringa levando le interruzioni
                        canCountInter ++;
                    }
                    
                    else break; //non posso più contare interruzioni
                    
                }
                if(c == w.s.length()){ w.count++;}
            }
        }
        if(w.count >= maxRepeated.count) maxRepeated = w;
    }
    return maxRepeated.s;
    
}
*/




/*

string find2IntPsw(string a,int m){
    word maxRepeated;
    maxRepeated.s ="non trovato";
    maxRepeated.count = 0;
    
    for(int i=0; i< a.length()-m;i++){
        word w;
        w.s = a.substr(i,m);
        w.count = 0;
      //  cout<<"word scelta = "<<w.s<<endl;
        string newA = a;
        newA.erase(newA.begin()+i,newA.begin()+i+m); // elimino la parte che ho preso come word
        
        
        for(int j = 0; j<newA.length()-m;j++){
            if(w.s[0] == newA[j]) { //è un possibile inizio della sequenza
             //   cout<<"possibile inizio con la lettera "<< w.s[0]<<endl;
                //elimino i caratteri inutili che ci stavano prima
                string s = newA; // uso questa string s per eliminare il carattere d'interruzione ogni volta che lo trovo
                s.erase(s.begin(),s.begin()+j);
                int c = 0;
               
                
                int canCountInter = 0;
                while(c != w.s.length()){
                  //  cout<<"{"<<w.s<<"}"<<" "<<"{"<<s<<"}  c = "<<c<<endl;
                    
                    if(w.s[c] == s[c])c++;
                    else if(canCountInter < 2){ //lettere non uguali, conto interruzioni
                        int inter = 0;
                        bool equals = false;
                        while(inter < 5 && !equals ){ //ciclo che conta le interruzioni
                            if(w.s[c] != s[c]) {inter++; s.erase(s.begin()+c);}//cout<<"s= "<<s<<endl;}
                            else equals = true;
                        }
                        canCountInter++;
                    }
                    else{//non posso più contare interruzioni
                        break;
                    }
                }
                
                
                if(c == w.s.length()){ w.count++;}// cout<<"FOUND "<<w.count<<" TIMES "<<w.s<<endl;}
                //else{cout<<"not found"<<endl;}
               // cout<<endl;
            }
        }
        if(w.count >= maxRepeated.count) maxRepeated = w;
    }
    return maxRepeated.s;
   
}

string find3IntPsw(string a,int m){
    word maxRepeated;
    maxRepeated.s ="non trovato";
    maxRepeated.count = 0;
    
    for(int i=0; i< a.length()-m;i++){
      //  cout<<"dentro il primo ciclo"<<endl;
        word w;
        w.s = a.substr(i,m);
        w.count = 0;
        //cout<<"word scelta = "<<w.s<<endl;
        string newA = a;
        newA.erase(newA.begin()+i,newA.begin()+i+m); // elimino la parte che ho preso come word
        
        
        for(int j = 0; j<newA.length()-m;j++){
           // cout<<"dentro il secondo ciclo"<<endl;
            if(w.s[0] == newA[j]) { //è un possibile inizio della sequenza
              //  cout<<"possibile inizio con la lettera "<< w.s[0]<<endl;
                //elimino i caratteri inutili che ci stavano prima
                string s = newA; // uso questa string s per eliminare il carattere d'interruzione ogni volta che lo trovo
                s.erase(s.begin(),s.begin()+j);
                int c = 0;
                int canCountInter = 0;
                while(c != w.s.length()){
                  //  cout<<"conto interruzioni"<<endl;
                   // cout<<"{"<<w.s<<"}"<<" "<<"{"<<s<<"}  c = "<<c<<endl;
                    if(w.s[c] == s[c])c++;
                    else if(canCountInter < 3){ //lettere non uguali, conto interruzioni
                        int inter = 0;
                        bool equals = false;
                        while(inter < 5 && !equals ){ //ciclo che conta le interruzioni
                            if(w.s[c] != s[c]) {inter++; s.erase(s.begin()+c);}//cout<<"s= "<<s<<endl;}
                            else equals = true;
                        }
                        canCountInter++;
                    }
                    else{//non posso più contare interruzioni
                        break;
                    }
                }
                
                
                if(c == w.s.length()){ w.count++;}// cout<<"FOUND "<<w.count<<" TIMES "<<w.s<<endl;}
              //  else{cout<<"not found"<<endl;}
                //cout<<endl;
            }
        }
        if(w.count >= maxRepeated.count) maxRepeated = w;
    }
    return maxRepeated.s;
    
}

string find3IntPsw(string a,int m){
    word maxRepeated;
    maxRepeated.s ="";
    maxRepeated.count = -1;
    
    for(int i=0; i< a.length()-m;i++){
        word w;
        w.s = a.substr(i,m);
        w.count = 0;
        cout<<"word scelta = "<<w.s<<endl;
        string newA = a;
        newA.erase(newA.begin()+i,newA.begin()+i+m); // elimino la parte che ho preso come word
        
        
        for(int j = 0; j<newA.length();j++){
            if(w.s[0] == newA[j]) { //è un possibile inizio della sequenza
                cout<<"ho trovato un possibile inizio con la lettera"<< w.s[0]<<endl;
                //elimino i caratteri inutili che ci stavano prima
                newA.erase(newA.begin(),newA.begin()+j);
                cout<<"adesso lavoro con "<<newA<<endl;
                int c = 1;
                int inter = 0;
                string s = newA; // uso questa string s per eliminare il carattere d'interruzione ogni volta che lo trovo
                
                while(c != w.s.length() && inter < 3){
                    cout<<"{"<<w.s<<"}"<<" "<<"{"<<s<<"}  c = "<<c<<endl;
                    if(w.s[c] != s[c]) {
                        inter++;
                        s.erase(s.begin()+c);
                    }
                    else if(w.s[c] == s[c])c++;
                }
                if(c == w.s.length()){ w.count++; cout<<"FOUND "<<w.count<<" TIMES "<<w.s<<endl;}
                else{cout<<"not found"<<endl;}
                cout<<endl;
            }
        }
        if(w.count > maxRepeated.count) maxRepeated = w;
    }
    return maxRepeated.s;
}
*/

void print(string A){
    int n =  A.length();
    cout<<"{";
    for(int i = 0; i<n; i++){
        cout<<A[i]<<" ";
    }
    cout<<"}"<<endl;
}

