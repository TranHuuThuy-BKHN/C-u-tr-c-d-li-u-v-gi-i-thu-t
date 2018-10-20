#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
using namespace std ;
int main(){
	ofstream fileout ;
	fileout.open("INPUT10.txt") ;
	srand(time(NULL)) ;
	for( int i = 0 ; i < 100000 ; i++ ){
		int x = rand()%10000; 
		int y = rand() %10000;
		fileout << x << " " << y << endl ;
	}
	fileout.close() ;
	return 0 ;
}

