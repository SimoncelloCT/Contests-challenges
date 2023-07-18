#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
using namespace std;

template <class H> class Nodo{
private:
    H key;
    Nodo<H>* parent;
    Nodo<H>* childSx;
    Nodo<H>* childDx;
    
public:
    Nodo<H>(){
        parent = NULL;
        childDx = NULL;
        childDx = NULL;
    }
    Nodo<H>(H k){
        parent = NULL;
        childDx = NULL;
        childDx = NULL;
        key = k;
    }
    void setParent(Nodo* n){
        this->parent = n;
    }
    Nodo<H>* getParent(){
        return parent;
    }
    void setSxChild(Nodo* n){
        this->childSx = n;
    }
    void setDxChild(Nodo* n){
        this->childDx = n;
    }
    Nodo<H>* getSxChild(){
        return childSx;
    }
    Nodo<H>* getDxChild(){
        return childDx;
    }
    H getKey(){
        return key;
    }
    void setKey(H k){
        key = k;
    }

    
};

template <class K> class BST{
private:
    Nodo<K>* root;
    Nodo<K>* NIL;
    int size;
public:
    BST(){
        NIL = new Nodo<K>(-1);
        root = NIL;
        size = 0;
    }
    Nodo<K>* search(K key){
        Nodo<K>* current = root;
        while(current != NIL){
            if(current->getKey() == key) return current;
            if(key  <=  current->getKey()) current = current->getSxChild();
            else current = current->getDxChild();
        }
        return current;
    }
    Nodo<K>* successore(Nodo<K>* n){
        Nodo<K>* current = n;
        if(current->getDxChild() != NIL){ // se ha un sottoalbero a destra cerco il successore a destra
            current = current->getDxChild(); // un passo a destra
            while(current->getSxChild() != NIL){
                current =  current->getSxChild();
            }
        }
        else{ // se non ne ha allora guardo il padre e salgo finchè non becco una chiave maggiore
            while(current != NIL && n->getKey() <= current->getKey()){
                current =  current->getParent();
            }
        }
        return current;
    }
    void _remove(K item, Node<K>* start){
        Node<K>* searched = _search(item, start);
        if (searched == NIL) {return;} //non esiste il nodo che voglio cancellare
        Node<K>* parent = searched->getParent(); //salva il parent, verrà controllato nei vari casi
        if (searched->getLeft() == NIL || searched->getRight() == NIL){ //non ha figli, o ha al più un figlio
            size--;
            Node<K>* figlio; //metto qui il figlio che ha, che sia destro o sinistro.
            if(searched->getLeft() != NIL) figlio = searched->getLeft();
            else figlio = searched->getRight();
            //dopo i due if sopra, il figlio potrebbe ancora essere NULL, se il nodo da cancellare non ha figli!
            if (parent == NIL) {root = figlio;} //era la radice il nodo da cancellare, lo sostituisco con il figlio
            else{ //esiste un padre
                if (searched->getKey() < parent->getKey()) parent->setLeft(figlio); //searched era figlio sinistro, sostituisco con quello
                else parent->setRight(figlio); //searched era figlio destro
            }
            if (figlio!= NIL){figlio->setParent(parent);} //non avevo separato il caso in cui il nodo non aveva figli
        }
        else{ //il nodo ha due figli
            Node<K>* succ = _successor(searched);
            searched->setKey(succ->getKey());
            _remove(succ->getKey(), searched->getRight());
        }
        return;
    }
    
    void canc(K key){
        _remove(key, root);
    }
    /*
    void canc(K key){
        //prendo il nodo da cancellare con una ricerca
        Nodo<K>* n = search(key);
        if(n == NIL) return;
        if (n->getSxChild() == NIL && n->getDxChild() == NIL){ // il nodo non ha figli
            if(n == root) {root = NIL; return; } // se è root la elimino
            //cancello il nodo
            Nodo<K>* padre = n->getParent();
            if(n->getKey() <= padre->getKey()){ //vengo da sinistra
                padre->setSxChild(NIL);
            }
            else { //vengo da destra
                padre->setDxChild(NIL);
            }
        }
        // il nodo ha un SOLO figlio
        else if ((n->getSxChild() != NIL && n->getDxChild() == NIL)|| (n->getDxChild() != NIL && n->getSxChild() == NIL)){
            
            
            //salvo su figlio il figlio che sia sinistro o destro.
            Nodo<K>* figlio;
            if(n->getSxChild() != NIL) figlio = n->getSxChild();
            else figlio = n->getDxChild();
            
            if(n == root){ // se il nodo da cancellare è la root allora metto il figlio come root
                root = figlio;
                figlio->setParent(NIL);
                return;
            }
        
            //cambio n con figlio
            //devo controlllare se n viene da sinistra o da destra
            Nodo<K>* padre = n->getParent();
            if(n->getKey() <= padre->getKey()) {
                padre->setSxChild(figlio);
                figlio->setParent(padre);
            }
            else{
                padre->setDxChild(figlio);
                figlio->setParent(padre);
            }
        }
        else {// il nodo ha DUE FIGLI
            Nodo<K>* succ = successore(n);
            if(n->getDxChild() == succ){ // se il  successore è figlio del nodo
                //scambio le chiavi
                K keySucc = succ->getKey();
                n->setKey(keySucc);
                //elimino l'ex successore facendo un ponticello con il suo sottoalbero destro
                n->setDxChild(succ->getDxChild());
                succ->getDxChild()->setParent(n);
            }
            else{ // il successore non è figlio del nodo MA è NEL SUO SOTTOALBERO perchè il nodo ha due figli
                //devo cambiare il valore di n con il suo successore, e poi mettere al posto del ex succ il suo sottoalbero di destra.
                //metto la chiave del succ in n
                K keySucc = succ->getKey();
                n->setKey(keySucc);
                //sostituisto al posto del succ, il suo sottoalbero destro
                //quindi prendo il padre del successore //succ è SEMPRE da sinistra(sono andato a scendere a sinistra sempre)
                Nodo<K>* padreSucc = succ->getParent();
                padreSucc->setSxChild(succ->getDxChild());
                succ->getDxChild()->setParent(padreSucc);
            }
        }
        
        size--;
    }*/
    void insert(K key){ // insert bst
        cout<<"inserisco "<<key<<" ";
        Nodo<K> *newNodo = new Nodo<K>(key);
        Nodo<K>* prec = NIL;
        Nodo<K>* current = root;
        while(current != NIL){
            prec = current;
            if(key  <=  current->getKey()) current = current->getSxChild();
            else current = current->getDxChild();
        }
        if(prec == NIL){ //radice
            root = newNodo;
            root->setSxChild(NIL);
            root->setDxChild(NIL);
        }
        else{
            if(key < prec->getKey()){
                prec->setSxChild(newNodo);
                newNodo->setParent(prec);
                newNodo->setSxChild(NIL);
                newNodo->setDxChild(NIL);
            }
            else {
                prec->setDxChild(newNodo);
                newNodo->setParent(prec);
                newNodo->setSxChild(NIL);
                newNodo->setDxChild(NIL);
            }
        }
        size++;
    }
    
   
    void rotateLeft(Nodo<K>* z){
        Nodo<K>* x = z->getDxChild(); //lavoro con questo
        if (z == NIL || x == NIL) return;
        if (z == root){ //setto radice = x
             root = x;
        }
        else{ //setto puntatori ex padre di z - x
            Nodo<K>* padre = z->getParent();
            if(z->getKey() <= z->getParent()->getKey()) padre->setSxChild(x); //sinistra
            else padre->setDxChild(x);
            x->setParent(padre);
        }
        
        Nodo<K>* xsx = x->getSxChild(); //beta
        z->setDxChild(xsx);
        xsx->setParent(z);
        x->setSxChild(z);
        z->setParent(x);
    }
    
    void rotateRight(Nodo<K>* z){
        Nodo<K>* x = z->getSxChild(); //lavoro con questo
        if (z == NIL || x == NIL) return;
        if (z == root){ //setto radice = x
            root = x;
        }
        else{ //setto puntatori ex padre di z - x
            Nodo<K>* padre = z->getParent();
            if(z->getKey() <= z->getParent()->getKey()) padre->setSxChild(x); //sinistra
            else padre->setDxChild(x);
            x->setParent(padre);
        }
        Nodo<K>* xdx = x->getDxChild(); //beta
        z->setSxChild(xdx);
        xdx->setParent(z);
        x->setDxChild(z);
        z->setParent(x);
        
    }
    
    void call_preorder(fstream & out){
        preorder(root,out);
    }
    void call_inorder(fstream & out){
        inorder(root,out);
    }
    void call_postorder(fstream & out){
        postorder(root,out);
    }
    
    void preorder(Nodo<K>* n, fstream & out){
        if(n == NIL) return;
        out<<n->getKey()<<" ";
        preorder(n->getSxChild(),out);
        preorder(n->getDxChild(),out);
    }
    void inorder(Nodo<K>* n, fstream & out){
        if(n == NIL) return;
        inorder(n->getSxChild(),out);
        out<<n->getKey()<<" ";
        inorder(n->getDxChild(),out);
    }
    void postorder(Nodo<K>* n, fstream & out){
        if(n == NIL) return;
        postorder(n->getSxChild(),out);
        postorder(n->getDxChild(),out);
        out<<n->getKey()<<" ";
    }
};


    
    
    
    

int main(){
	fstream in;
	fstream out;
	in.open("./input.txt");
	out.open("./output.txt" , ios::out);
	for(int i=0; i<100;i++){
        string type,stampa;
        int nOper,nRot;
        in>>type;
        in>>nOper;
        in>>nRot;
        in>>stampa;
        if(type == "int"){
            BST<int> A;
            for(int j = 0; j<nOper;j++){
                string operVal;
                in>>operVal;
                int dp = operVal.find(":");
                string oper = operVal.substr(0,dp);
                string val = operVal.substr(dp+1);
                int valore = atoi(val.c_str());
                if(oper == "ins"){
                    cout<<"ins"<<endl;
                     A.insert(valore);
                }
                else{ // canc
                    A.canc(valore);
                    
                }
            }
            for(int j = 0; j< nRot;j++){
                string rotVal;
                in>>rotVal;
                int dp = rotVal.find(":");
                string rot = rotVal.substr(0,dp);
                string val = rotVal.substr(dp+1);
                int valore = atoi(val.c_str());
                if(rot == "right"){
                    Nodo<int> * nodo = A.search(valore);
                    A.rotateRight(nodo);
                }
                else{ // left
                    Nodo<int> * nodo = A.search(valore);
                    A.rotateLeft(nodo);
                }
            }
            
            cout<<stampa<<endl;
            if(stampa == "preorder") {A.call_preorder(out); }//out<<A.pre;}
            if(stampa == "postorder"){ A.call_postorder(out);}//out<<A.post;}
            if(stampa == "inorder"){ A.call_inorder(out); }//out<<A.in;}
        }
        else{
            BST<double> A;
            for(int j = 0; j<nOper;j++){
                string operVal;
                in>>operVal;
                int dp = operVal.find(":");
                string oper = operVal.substr(0,dp);
                string val = operVal.substr(dp+1);
                double valore = atof(val.c_str());
                if(oper == "ins"){
                    A.insert(valore);
                }
                else{ // canc
                    A.canc(valore);
                    
                }
            }
            for(int j = 0; j< nRot;j++){
                string rotVal;
                in>>rotVal;
                int dp = rotVal.find(":");
                string rot = rotVal.substr(0,dp);
                string val = rotVal.substr(dp+1);
                double valore = atof(val.c_str());
                if(rot == "right"){
                    Nodo<double> * nodo = A.search(valore);
                    //  cout<<"trovato il nodo "<<nodo->getKey()<<endl;
                    A.rotateRight(nodo);
                }
                else{ // left
                    Nodo<double> * nodo = A.search(valore);
                    A.rotateLeft(nodo);
                }
            }
            
            cout<<stampa<<endl;
            if(stampa == "preorder") {A.call_preorder(out); }//out<<A.pre;}
            if(stampa == "postorder"){ A.call_postorder(out);}//out<<A.post;}
            if(stampa == "inorder"){ A.call_inorder(out); }//out<<A.in;}
        }
        
        out<<endl;
	}
	in.close();
	//out.close();
	return 0;
}




