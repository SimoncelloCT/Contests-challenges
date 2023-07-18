#include <iostream>
#include <fstream>
using namespace std;


int main(){
    ifstream in;
    ofstream out;
    file.open("./input.txt");
    out.open("output.txt");
    int n[10];
    float pesi[10];
    float* v[10];
    for(int i = 0; i<10; i++){
        in>>pesi[i];
        in>>n[i];
        v[i] = new float[n[i]];
        for(int j=0; j<n[i];j++){
            file>>v[i][j];
        }
    }
    
    
    
    for(int i=0; i<10;i++){
        float sum = 0;
        int count = 0;
        bool cond = false;
        while(cond == false){
            float m = vet[i][0];
            int minPos = 0;
            for(int c = 0; c<n; c++){
                if(vet[i][c] < m) {
                    m = vet[i][c];
                    minPos = c;
                }
            }
            vet[i][minPos] = INT_MAX;
            if(sum+m <= pesi[i]){
                sum += m;
                count++;
            }
            else cond = true;
        }
        out<<count<<" "<<sum<<endl;
    }
    
    file.close();
    out.close();
    return 0;
}

