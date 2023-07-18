#include <iostream>
#include <fstream>
using namespace std;
//ogni partita ha tot mosse, le mosse partono dal brancata e si alternano con l'altro giocatore. dalla quinta mossa in poi si deve iniziare a controllare da ogni mossa, e vedere se si verificano simboli uguali in uno di questi casi:
//diag princ- diag secondaria- una qualunque riga, una qualunque colonna.
//riempio quindi inizialmente una matrice 3x3 con tutti -1, e poi i controlli li faccio escludendo il -1, dopo aver caricato nella matrice almeno 5 mosse.

//quindi se abbiamo un contatore di mosse ad ogni partita, le mosse dispari sono quelle del brancata, mentre quelle pari sono del carcannazzu
#define dim 100
void initMatrix(int (&a)[3][3]);
bool control(int (&a)[3][3], int &p1, int &p2);
void insertMossa(int (&a)[3][3], string mos,int p);

int main(){
    fflush(stdout);
    ifstream in;
    int n[dim];
   // string** mosse[dim];
    int m[3][3];
    in.open("./input.txt");
    ofstream out;
    out.open("output.txt");
    int i=0;
  
    while(i<dim){
        int p1Win = 0,p2Win = 0;
        in>>n[i];
        cout<<"RIGA : "<<i<<endl;
        cout<<"numero di partite in questa riga = "<<n[i]<<endl;
        for(int j=0; j<n[i];j++){ //per ogni partita
             string mosseEseguite  = "";
           // cout<<"prendo partita n. "<<j<<endl;
            initMatrix(m);
            bool vittoria = false;
            bool newMatch = false;
            for(int c = 0; !newMatch && !vittoria; c++){ //per ogni mossa della partita
                //cout<<"mosseEseguite = "<<mosseEseguite<<"\t"<<"nMosse: "<<c <<endl;
                string moss;
                in>>moss;
                //cout<<"moss = "<<moss<<endl;
                
                if(mosseEseguite.find(moss) != -1 && moss.find(",")  != -1){ // se simao sicuri che è una mossa, e che è già stata eseguita
                   cout<<"newMatch = true- è una nuova partita"<<endl;
                    cout<<"moss = "<<moss<<endl;
                    newMatch = true;
                    in.seekg(-moss.length() , ios::cur);
                    
                    // devi tornare indietro per rileggere la stessa mossa nella prossima partita
                }
                else if(moss.find("(") == -1){
                    cout<<"newMatch = true- non è una mossa"<<endl;
                    cout<<"moss = "<<moss<<endl;
                    newMatch = true;
                    in.seekg(-moss.length() , ios::cur);
                   // in>>moss;
                    //cout<<"prova seekg"<<moss<<endl;
                
                    
                }
                else{
                    mosseEseguite+=moss;
                    //cout<<"prendo  mossa n. "<<c<<endl;
                    //chiamo il riempimento della matrice m con la mossa
                    int player = 0;
                    if (c % 2 ==  0) player = 1;
                    else player = 2;
                    insertMossa(m,moss,player);
                    //cout<<"controllo vittoria"<<endl;
                    if(!vittoria) vittoria = control(m,p1Win,p2Win);
                    //cout<<"vittoria = "<<vittoria<<endl;
                    //cout<<"p1Win = "<<p1Win<<" "<<"p2Win = "<<p2Win<<endl;
                    
                }
                
            }
            
          
            //stampo matrice partita
          /*  for(int i = 0; i< 3;i++){
                for(int j = 0; j<3; j++){
                    cout<<m[i][j]<<" ";
                }
                cout<<endl;
            }*/
        }
        cout<<"RIGA =  p1Win = "<<p1Win<<" "<<"p2Win = "<<p2Win<<endl;
        out<<p1Win<<" "<<p2Win<<endl;
        
        i++;
    }
    
    
   /* for(int i = 0; i<dim; i++){
        for(int j = 0; j< n[i]; j++){
            cout<<" [";
            for(int c = 0; c < 7; c++){
                cout<<mosse[i][j][c];
                
            }
            cout<<"] ";
        }
        cout<<endl;
    }*/
    
    
   
    
    
    
    
   
    
    
    
    in.close();
    out.close();
    return 0;
}
//brancata = p1->> 0 , carcannazzu  = p2->> 1;
void insertMossa(int (&a)[3][3], string mos, int p){
    //cout<<"mos= "<<mos<<endl;
    int i = mos[1] - '0';
    
    int j = mos[3] - '0';
    //cout<<"piazzo "<<p-1 <<" in posizione "<<i<<" "<<j<<endl;
    //cout<< i<<"  "<<j<<"  valori"<<endl;
    a[i][j] = p-1;
}

bool control(int (&a)[3][3], int &p1, int &p2){
    //controlla se c'è la vittoria di qualcuno ad ogni colpo
    //il simbolo 0 indica il brancata, il simbolo 1 indica l'altro.
    //controllo le diagonali
    if((a[0][0] == 1 && a[1][1] == 1 && a[2][2] == 1) || (a[0][2] == 1 && a[1][1] == 1 && a[2][0] == 1)){ //ha vinto l'altro questa partita
        p2++;
        cout<<"vittoria per diagonale di p2"<<endl;
        return true;
        
    }
    else if ((a[0][0] == 0 && a[1][1] == 0 && a[2][2] == 0) || (a[0][2] == 0 && a[1][1] == 0 && a[2][0] == 0)) { // ha vinto il brancata
        p1++;
         cout<<"vittoria per diagonale di p1"<<endl;
        return true;
        
    }
    //controllo se c'è una vittoria per una riga
    for(int i = 0; i<3; i++){
        int equalsColumnNumbers = 1;
        int lastSymbol = a[i][0];
        for(int j = 1; j<3 && lastSymbol == a[i][0]; j++){
            if(a[i][j] == lastSymbol) {
                equalsColumnNumbers++;
            }
            else{
                lastSymbol = a[i][j];
            }
        }
        if(equalsColumnNumbers == 3){ //ha vinto il brancata in una riga
            if(lastSymbol == 0) {
                cout<<"vittoria per riga di p1"<<endl;
                p1++;
                return true;
                
            }
            else if (lastSymbol == 1){ // ha vinto l'altro
                p2++;
               cout<<"vittoria per riga di p2"<<endl;
                return true;
                
            }
        }
    }
    //controllo se c'è una vittoria per colonna
    for(int i = 0; i<3; i++){
        int equalsRowNumbers = 1;
        int lastSymbol = a[0][i];
        for(int j = 1; j<3 && lastSymbol == a[0][i]; j++){
            if(a[j][i] == lastSymbol) {
                equalsRowNumbers++;
            }
            else{
                lastSymbol = a[j][i];
            }
        }
        if(equalsRowNumbers == 3){
            if(lastSymbol == 0) {p1++;  cout<<"vittoria per colonna di p1"<<endl; return true;} //ha vinto il brancata in una colonna
            else if (lastSymbol == 1) {p2++;  cout<<"vittoria per colonna di p2"<<endl; return true;}// ha vinto l'altro
            }
    }
    bool pareggio = true;
    //controllo se è pareggio
    for(int i = 0 ; i< 3; i++){
        for(int j = 0 ; j<3;j++){
            if(a[i][j] == -1)  pareggio = false;
        }
    }
    if(pareggio) cout<<" è un pareggio"<<endl;
    return pareggio;
}

void initMatrix(int (&a)[3][3]){
    for(int i =0 ; i<3; i++){
        for(int j =0 ; j< 3; j++){
            a[i][j] = -1;
        }
    }
}

    
    
 