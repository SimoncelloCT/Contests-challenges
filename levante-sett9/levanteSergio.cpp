#include <vector>
#include <string>
#include <iostream>
#include <fstream> 
#define dim 100
using namespace std;

struct Tcanale{
	int enter;
	int exit;
};
void viaggio(vector<Tcanale> w, Tcanale now,int AM, int dest, int p, int &topV,bool control);
void revers(vector<Tcanale> &canale){
    for(int i = 0; i<canale.size(); i++){
        int tmp = canale[i].enter;
        canale[i].enter = canale[i].exit;
        canale[i].exit = tmp;
    }
}
int main()
{
    ifstream fs("input.txt",ios::in );
	ofstream ofs("output.txt",ios::out);
	int y=0;
	while(y<dim)
	{
        cout<<"riga: "<<y+1<<endl;
        int destinazione,ncoppie,AM;
        fs>>destinazione;
        fs>>ncoppie;
        fs>>AM;
        vector <Tcanale> v;
		Tcanale p;
        for(int j=0; j<ncoppie;j++){
            int a,b;
            fs>>a;
            fs>>b;
            p.enter = a;
            p.exit = b;
        	v.push_back(p);
        }
        int topV = INT_MAX;
        vector<Tcanale> w = v;
        for(int i = 0 ; i<v.size(); i++){
            if(v[i].enter == 0){
            	
            	//cout<<"sx"<<endl;
                Tcanale tmp = w[i];
                w.erase(w.begin()+i);
                bool c=false;
                viaggio(w,tmp,AM,destinazione,0,topV,c);
                
            }
            else if(v[i].exit == 0){
            	//cout<<"destra"<<endl;
                Tcanale tmp ;
                tmp.enter = w[i].exit;
                tmp.exit = w[i].enter;
                w.erase(w.begin()+i);
                bool c=true;
                viaggio(w,tmp,AM,destinazione,AM,topV,c);
                
            }
            w = v;
            //cout<<"top"<<topV<<endl;
        }
        if(topV == INT_MAX) topV = -1;
        cout<<topV<<endl;
        ofs<<topV<<endl;
        y++;
    }
    fs.close();
    ofs.close();
    return 0;
}



void viaggio(vector<Tcanale> w, Tcanale now,int AM, int dest, int p, int & topV,bool control){
	//cout<<"destra"<<now.exit<<endl;
    if(control==true)if(p == AM) revers(w);
    if(now.exit == dest-1 ) { topV = p+1;return;}
        vector<Tcanale> stack;
        stack.push_back(now);
        p++;
        //cout<<"p"<<p<<endl;
        while(true){  if(p == AM) revers(w);
            vector<Tcanale> newStack;
            while(stack.size()!= 0){
                if(p < AM) viaggio(w,stack.back(),AM,dest,AM-1,topV,control);
                vector<Tcanale>::iterator it = w.begin();
                while(it != w.end()){
                //	cout<<"it:"<<stack.back().enter<<","<<stack.back().exit<<endl;
                    if(it->enter == stack.back().exit) {
                        if(it->exit == dest-1){if(p+1 < topV)topV = p+1; return;}// cout<<"topV interno"<<topV<<endl;
                        newStack.push_back(*it);
                        it = w.erase(it);
                    }
                    else it++;
                }
                
                stack.pop_back();
            }
            if(newStack.size() == 0) {return;}
            p++;
            stack = newStack;

        }
}

