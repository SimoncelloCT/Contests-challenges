#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;


//una funzione calcola tutte le possibili parole con lettere adiacenti a partire dalla parola data -> array di stringhe
//
#define dim 100
void combinations(string word,int i, vector<string> & ret);


string swapp(string word,int i,int j);
void findPermutations(string str, int index, int n, vector<string>& ret);
int main(){
    fflush(stdout);
    fflush(stdin);
    ifstream in;
    string rows[dim];
    string parole[dim];
    in.open("./input.txt");
    ofstream out;
    out.open("output.txt");
    for(int i = 0 ; i< dim; i++){
        in>>parole[i];
        //cout<<parole[i]<<endl;
        rows[i].reserve(INT_MAX);
        in>>rows[i];
        //cout<<rows[i]<<endl;
        //rows[i] = rows[i].substr(1,rows[i].length());
    }
    cout<<"inserimento completato"<<endl;
    
    for(int i = 0; i< dim; i++){
        vector<string> r; //contiene le combinazioni adiacenti
        vector<int> trovati;
       // int nTrovati = 0;
       // cout<<"chiamo i combinations"<<endl;
        //r.push_back(parole[i]);
        //combinations(parole[i],0,r);
        findPermutations(parole[i],0,parole[i].length(),r);
        cout<<"ho finito le combinazioni della parola "<<parole[i]<<endl;
       
        for (vector<string>::iterator it = r.begin() ; it != r.end(); ++it)
            cout << *it<<endl;
        
        //controlli se una delle parole nell'array r è si trova nella riga
        
        for(int j = 0; j<r.size(); j++){
            //cout<<"cerco per "  <<r[j]<<endl;
            int removed = 0;
            string s;
            s.reserve(INT_MAX);
            s = rows[i];
            if(r[j] != ""){
                int found = -1;
                do{
                    cout<<"found at "<<found<<endl;
                    found = s.find(r[j],found+1);
                    if(found!= -1) trovati.push_back(found);
                }while(found != -1);
            }
        }
        sort(trovati.begin(), trovati.end());
        for(int i = 0; i< trovati.size(); i++){
            out<<trovati[i]<<" ";
        }
        out<<endl;
    }
    in.close();
    out.close();
    return 0;
}


string swapp(string word,int i,int j){
    char app;
    app = word[i];
    word[i] = word[j];
    word[j] = app;
    return word;
}
void combinations(string word,int i, vector<string> & ret){  //troppo lenta 
  //  cout<<"dentro il combinations: "<<i<<endl;
    //cout<<"wordLength() = "<< word.length()<<endl;
    if (i >= word.length() -1)return;
        string w = swapp(word,i,i+1);
        if(find(ret.begin(), ret.end(), w) != ret.end()) {}
        else ret.push_back(w);
        combinations(w,i+2,ret);
        string w1 = swapp(w,i,i+1);
        //combinations(w1,i+2,ret,n);
        combinations(w1,i+1,ret);
       
    
}


void findPermutations(string str, int index, int n, vector<string>& ret)
{
    //cout<< "permut "<<index<<endl;
    if (index >= n || (index + 1) >= n) {
       // cout << str << endl;
        if(find(ret.begin(), ret.end(), str) != ret.end()) {}
        else ret.push_back(str);
        return;
    }
    
    findPermutations(str, index + 1, n,ret);
    swap(str[index], str[index + 1]);
    findPermutations(str, index + 2, n,ret);
    swap(str[index], str[index + 1]);
}





