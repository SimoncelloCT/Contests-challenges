//
//  main.cpp
//  lez5C.cpp
//
//  Created by Simone Scionti on 10/04/18.
//  Copyright © 2018 Mobo. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <deque>
#include <queue>
#define dim 100
using namespace std;

int ROW = 0;
int COL = 0;

struct Point
{
    int x;
    int y;
};

struct queueNode
{
    Point pt;
    int dist;
};


bool isValid(int row, int col)
{
    return (row >= 0) && (row < ROW) &&
    (col >= 0) && (col < COL);
}


int rowNum[] = {-1, 0, 0, 1, 1, -1, -1,  1,2,-2,0,0};
int colNum[] = {0, -1, 1, 0, 1, -1,  1, -1,0,0,2,-2};

class cella{
public:
    cella(){
        this->i = -1;
        this->j = -1;
    }
    cella(int _i,int _j){
        this->i = _i;
        this->j = _j;
    }
    int i,j;
};



class mappa{
public:
    int n;
    int m;
    char **a;
    cella e;
    cella u;
    int passi;
    int **mat;
    mappa(){
        n = 0;
        m = 0;
        e = u = cella(-1,-1);
        a = NULL;
        passi = 0;
        mat = NULL;
    }
    mappa(int _n,int _m){
        this->n = _n;
        this->m = _m;
        a = new char*[_n];
        for(int i = 0; i<_n;i++){
            a[i] = new char[_m];
        }
        mat = new int*[_n];
        for(int i = 0; i<_n;i++){
            mat[i] = new int[_m];
        }
        passi = 0;
    }
    mappa(mappa const &obj){ //copia un nuovo oggetto a partire da uno già inizializzato.
        n = obj.n;
        m = obj.m;
        e = obj.e;
        u = obj.u;
        a = new char*[obj.n];
        for(int i = 0; i<n;i++){
            a[i] = new char[obj.m];
            memcpy(a[i],obj.a[i],m*sizeof(char)); //più veloce di così..
        }
        mat = new int*[obj.n];
        for(int i = 0; i<n;i++){
            mat[i] = new int[obj.m];
            memcpy(mat[i],obj.mat[i],m*sizeof(int)); //più veloce di così..
        }
        passi = obj.passi;
    }
    void initMat(){
        for(int i = 0 ; i<n; i++){
            for(int j = 0;j<m;j++){
                if(a[i][j] == 'E'||a[i][j] == 'U'||a[i][j] == '_') mat[i][j] = 1;
                else mat[i][j] = 0;
            }
        }
    }
    void foundCells(){
        bool uFound = false;
        for(int i = 0; i<n;i++){
            for(int j = 0; j<m;j++){
                if(a[i][j] == 'U') {u = cella(i,j); uFound = true;}
                else if(a[i][j] == 'E') e = cella(i,j);
            }
        }
        if (!uFound){
            u = cella(-1,-1);
        }
    }
    void print(){
        for(int i = 0; i<n; i++){
            for(int j = 0; j<m;j++){
                cout<<this->a[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<"e: {i= "<<e.i<<" ,j="<<e.j<<" } u: {i="<<u.i<<" ,j="<<u.j<<"}"<<" numPassi = "<<passi<<" "<<endl;
        cout<<endl;
    }
    void printMat(){
        for(int i = 0; i<n; i++){
            for(int j = 0; j<m;j++){
                cout<<this->mat[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<"e: {i= "<<e.i<<" ,j="<<e.j<<" } u: {i="<<u.i<<" ,j="<<u.j<<"}"<<" numPassi = "<<passi<<" "<<endl;
        cout<<endl;
        
    }
};





/*class modifiedMappa: mappa{
public:
    int passi;
    modifiedMappa(int _n,int _m, int _passi ) : mappa(_n,_m){
        this->passi = _passi;
    }
    
};*/
int BFS(int **m, Point src, Point dest);

int main(){
    fflush(stdout);
    ifstream file;
    mappa vec[dim];
    
    int i = 0;
    file.open("./input.txt");
    ofstream out;
    out.open("output.txt");
    while(i<dim){
        int n,m;
        file>>n;
        file>>m;
        vec[i] = mappa(n,m);
        for(int j=0; j<vec[i].n;j++){
            for(int k = 0; k<vec[i].m;k++){
                file>>vec[i].a[j][k];
            }
        }
        vec[i].foundCells();
        vec[i].initMat();
        vec[i].print();
        //vec[i].printMat();
        Point s;
        s.x = vec[i].e.i;
        s.y = vec[i].e.j;
        Point d;
        d.x = vec[i].u.i;
        d.y = vec[i].u.j;
        ROW = vec[i].n;
        COL = vec[i].m;
        int ps = BFS(vec[i].mat,s,d);
        out<<ps<<endl;
        ROW = 0;
        COL = 0;
        i++;
    }
    
    
    file.close();
    out.close();
    return 0;
}

int BFS(int **m, Point src, Point dest)
{
    int mat[ROW][COL];
    for(int i = 0; i< ROW;i++){
        memcpy(mat[i],m[i],COL*sizeof(int));
    }
    for(int i = 0; i< ROW;i++){
        for(int j = 0; j<COL;j++){
            cout<<mat[i][j]<<" ";
        }
        cout<<endl;
    }

    if (!mat[src.x][src.y] || !mat[dest.x][dest.y])
        return -1;
    
    bool visited[ROW][COL];
    memset(visited, false, sizeof visited);

    visited[src.x][src.y] = true;

    queue <queueNode> q;
 
    queueNode s = {src, 0};
    q.push(s);
    while (!q.empty())
    {
        queueNode curr = q.front();
        Point pt = curr.pt;

        if (pt.x == dest.x && pt.y == dest.y)
            return curr.dist;

        q.pop();
        
        for (int i = 0; i < 12; i++)
        {
            int row = pt.x + rowNum[i];
            int col = pt.y + colNum[i];
 
            if (isValid(row, col) && mat[row][col] &&
                !visited[row][col])
            {

                visited[row][col] = true;
                queueNode Adjcell = { {row, col},
                    curr.dist + 1 };
                q.push(Adjcell);
            }
        }
    }

    return -1;
}






