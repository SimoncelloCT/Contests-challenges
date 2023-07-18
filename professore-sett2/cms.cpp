#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include<stdio.h>
#include<stdlib.h>
using namespace std;


void Swap(char* strC,int i,int j); 
void Perm(char *strC,int i ,int n,int fact,char ** Matrix);
int c(0);
int main()
{
	ifstream fs;
	ofstream ofs("output.txt",ios::out);
	fs.open("input.txt",ios::in );
	while(fs.good())
	{
		int n;
		fs>>n;
		cout<<"cifre combinazione="<<n<<endl;
		
		string c[n];
		cout<<"F [";
		for(int i=0;i<n;i++)
		{
			fs>>c[i];
			cout<<c[i]<<"-";		
		}
		cout<<"]"<<endl;
		string w;
		fs>>w;
		cout<<"wildCard: "<<w<<endl;
		
		string str;string indexast="";
		int ast=0;
	for(int i=0;i<n;i++)
	{
	bool trovato=false;
		for(int j=0;j<w.length();j++)
		{
			if(c[i][0]==w[j]) trovato=true;
		}
		if(!trovato) str+=c[i];
	}
	
	for(int i=0;i<w.length();i++)
	{
	
		if(w[i]=='*') 
		{
			ast++;
			
		}
	}
	cout<<"num ast "<<ast<<endl;
	char strC[ast];
	for(int k=0;k<ast;k++)
	{
		 strC[k]=(char)str[k];
		 cout<<strC[k];
	}
	cout<<endl;
	
	int fact=1;
	for(int j=1;j<=ast;j++)
	fact*=j;
	
	char **Matrix;
	Matrix = new char * [fact];
	for(int i=0;i<fact;i++)
	Matrix[i] = new char[ast];
	::c=0;
	Perm(strC,0,ast-1,fact,Matrix);
	cout<<endl; 
	int x=::c;

int i,k;
char *temp;
for(i = 0; i<fact-1; i++)
 {
 for(k = 0; k<fact-1-i; k++)
  {
 	
         if(strcmp(Matrix[k+1] , Matrix[k])<0) 
		 {
         		
				 temp = Matrix[k+1];
		  		Matrix[k+1] = Matrix[k];
			Matrix[k] = temp;
         }
 }
}

	for(int i=0;i<fact;i++)
	{
		for(int j=0;j<ast;j++)
		cout<<Matrix[i][j];
		cout<<endl;
	}
	
	char array[fact][w.length()];int a=0,s=0;
	for(int j=0;j<fact;j++)
	{s=0;
		for(int i=0;i<w.length();i++)
		{
			if(w[i]!='*') array[j][i]=w[i];
			else
			{
				array[j][i]=Matrix[a][s];
				s++;
			}
		}
		a++;
	}
	
	for(int i=0;i<fact;i++)
	{	cout<<"\t";
		for(int j=0;j<w.length();j++)
		{
			cout<<array[i][j];
			ofs<<array[i][j];
		}
		ofs<<" ";
		cout<<endl;	
	}
	ofs<<"\n";
	
	for(int i=0;i<fact;i++)
	delete Matrix[i];
	
	delete Matrix;

	}
}
	
	//deollocare la matrice
	
void Perm(char *strC,int i ,int n,int fact,char ** Matrix){
	int j;	
if(i==n){
		for(j=0;j<=n;j++)
		{
			Matrix[c][j]=strC[j];
		}		
		c++;
	}
	else{
		for( j=i ; j<=n ; j++ ){
			Swap(strC,i,j);
			Perm(strC,i+1,n,fact,Matrix);
			Swap(strC,i,j);
		}
	}
}
 
void Swap(char* strC,int i,int j){

	int temp;
	temp = strC[i];
	strC[i] = strC[j];
	strC[j] = temp;
}
