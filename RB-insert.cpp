#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
using namespace std;

template <class H> class Nodo{
private:
    bool red;
    H key;
    Nodo<H>* parent;
    Nodo<H>* childSx;
    Nodo<H>* childDx;
    
public:
    Nodo<H>(){
        red = true;
        parent = NULL;
        childDx = NULL;
        childDx = NULL;
    }
    Nodo<H>(H k){
        red = true;
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
    Nodo<H>* getChildSx(){
        return childSx;
    }
    Nodo<H>* getChildDx(){
        return childDx;
    }
    void setBlack(){
        red = false;
    }
    void setRed(){
        red = true;
    }
    H getKey(){
        return key;
    }
    bool isRed(){
        return red;
    }
    
};

template <class K> class RBTree{
private:
    Nodo<K>* root;
    Nodo<K>* NIL;
public:

    string pre;
    string post;
    string in;
    
    RBTree(){
        NIL = new Nodo<K>(-1);
        NIL->setBlack();
        root = NIL;
        in =  "";
        pre = "";
        post = "";
    }
    void insert(K key){ // insert bst
        Nodo<K> *newNodo = new Nodo<K>(key);
        Nodo<K>* prec = NIL;
        Nodo<K>* current = root;
        while(current != NIL){
            prec = current;
            if(key  <=  current->getKey()) current = current->getChildSx();
            else current = current->getChildDx();
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
         insert_fixup(newNodo);
    }
    
    void insert_fixup(Nodo<K>* z){
        if(z == root){
            z->setBlack();
            return;
        }
        if(z->getParent()->isRed() ==  false) return; //se è figlio di un nodo nero finisce qui
        //è figlio di un nodo rosso, devo guardare lo zio, che può essere a sinistra o a destra
        Nodo<K>* padre = z->getParent();
        Nodo<K>* nonno = padre->getParent();
        Nodo<K>* zio ;
        //stabilisco chi è lo zio
        if(padre->getKey() <= nonno->getKey()) zio = nonno->getChildDx();
        else zio = nonno->getChildSx();
       
        //CASO 1: ZIO ROSSO
        if(zio->isRed()){ //coloro di nero il padre e lo zio e di rosso il nonno. Rieseguo sul nonno la procedura
            padre->setBlack();
            zio->setBlack();
            nonno->setRed();
            insert_fixup(nonno);
            return;
        }
        //CASO 2: ZIO NERO
        //se z è esterno rotazione sul nonno , se z interno rotazione al contrario sul padre
        //per stabilire se è esterno o meno devo prima vedere da dove vengo
        
        if(padre->getKey() <= nonno->getKey()){ //se vengo da sinistra
            if(z->getKey() <= padre->getKey()){ //2.1 z è esterno essendo a sinistra
                rotateRight(nonno);
                nonno->setRed(); //cambio colore padre-nonno
                padre->setBlack();
            }
            else{ //2.2 z è interno, rotazione sul padre e rieseguo procedura
                rotateLeft(padre);
                insert_fixup(padre);
            }
        }
        else{ //vengo da destra
            if(z->getKey() > padre->getKey()){ //2.1 z è esterno essendo a destra
                rotateLeft(nonno);
                nonno->setRed(); //cambio colore padre-nonno
                padre->setBlack();
            }
            else{ //2.2 z è interno , rotazione sul padre e rieseguo procedura
                rotateRight(padre);
                insert_fixup(padre);
            }
        }
    }
    void rotateLeft(Nodo<K>* z){
        Nodo<K>* x = z->getChildDx(); //lavoro con questo
        if (z == root){ //setto radice = x
             root = x;
        }
        else{ //setto puntatori ex padre di z , x
            Nodo<K>* padre = z->getParent();
            if(z->getKey() <= z->getParent()->getKey()) padre->setSxChild(x); // da sinistra
            else padre->setDxChild(x); //da destra
            x->setParent(padre);
        }
        
        Nodo<K>* xsx = x->getChildSx(); //beta
        z->setDxChild(xsx);
        xsx->setParent(z);
        x->setSxChild(z);
        z->setParent(x);
    }
    
    
    void rotateRight(Nodo<K>* z){
        Nodo<K>* x = z->getChildSx(); //lavoro con questo
        if (z == root){ //setto radice = x
            root = x;
        }
        else{ //setto puntatori ex padre di z , x
            Nodo<K>* padre = z->getParent();
            if(z->getKey() <= z->getParent()->getKey()) padre->setSxChild(x); //sinistra
            else padre->setDxChild(x);
            x->setParent(padre);
        }
        Nodo<K>* xdx = x->getChildDx(); //beta
        z->setSxChild(xdx);
        xdx->setParent(z);
        x->setDxChild(z);
        z->setParent(x);
    }
    
    void call_preorder(){
        preorder(root);
    }
    void call_inorder(){
        inorder(root);
    }
    void call_postorder(){
        postorder(root);
    }
    void preorder(Nodo<K>* n ){
        if(n == NIL) return;
        char color;
        if (n->isRed()) color = 'R';
        else color = 'B';
        pre += "("+fixCast(to_string(n->getKey()))+","+color+") ";
        preorder(n->getChildSx());
        preorder(n->getChildDx());
    }
    void inorder(Nodo<K>* n){
        if(n == NIL) return;
        char color;
        if (n->isRed()) color = 'R';
        else color = 'B';
        inorder(n->getChildSx());
        in += "("+fixCast(to_string(n->getKey()))+","+color+") ";
        inorder(n->getChildDx());
    }
    void postorder(Nodo<K>* n){
        if(n == NIL) return;
        char color;
        if (n->isRed()) color = 'R';
        else color = 'B';
        postorder(n->getChildSx());
        postorder(n->getChildDx());
        
        post += "("+fixCast(to_string(n->getKey()))+","+color+") ";
    }
    
    string fixCast(string s){
        if(s.find(".") == -1) return s;
        for(int i = s.length()-1; i>=0; i--){
            if(s[i] != '0') {
                if(s[i] == '.') return s.substr(0,i);
                return s.substr(0,i+1);
            }
        }
        return s;
    }
};
int main(){
	fstream in;
	fstream out;
	in.open("./input.txt");
	out.open("./output.txt" , ios::out);
	for(int i=0; i<100;i++){
        string type,oper;
        int n;
        in>>type;
        in>>n;
        in>>oper;
        if(type == "int"){
            RBTree<int> A;
            for(int j = 0; j<n;j++){
                int val;
                in>>val;
                A.insert(val);
            }
            if(oper == "preorder") {A.call_preorder(); out<<A.pre;}
            if(oper == "postorder"){ A.call_postorder();out<<A.post;}
            if(oper == "inorder"){ A.call_inorder(); out<<A.in;}
        }
        else{
            RBTree<float> A;
            for(int j = 0; j<n;j++){
                float val;
                in>>val;
                A.insert(val);
            }
            if(oper == "preorder") {A.call_preorder(); out<<A.pre;}
            if(oper == "postorder"){ A.call_postorder();out<<A.post;}
            if(oper == "inorder"){ A.call_inorder(); out<<A.in;}
        }
        
        out<<endl;
	}
	in.close();
	out.close();
	return 0;
}




