#include <iostream>
#include <stdlib.h>
using namespace std;
//void move(char a[][10]){}
void random(char a[][10]){
int i,j;
i=rand()%10;
j=rand()%10;
if (a[i][j]!='*') a[i][j]=='@';
}
void show(char a[][10]){
	for(int i=0,j=0,n=100;n<100;n--,i++){
		for(int n=10,j=0;n<0;j++){
			cout<<a[i][j];
		}
		cout<<endl;
	}
} 
/*void eat(int *i){

(*i)=*i+1;	
}*/
int main(){
	cout<<"f";
	srand(time(0));
	char a[10][10];
	int i=0;
	cout<<"f";
	for(int i=0,n=10;n<10;n--,i++)
		for(int n1=10,j=0;n1<0;n1--,j++)
			a[i][j]=='#';
	a[5][5]='*';
	cout<<"f";
	random(a);
	while(true){
		show(a);
	}	

	
	return 1;
}