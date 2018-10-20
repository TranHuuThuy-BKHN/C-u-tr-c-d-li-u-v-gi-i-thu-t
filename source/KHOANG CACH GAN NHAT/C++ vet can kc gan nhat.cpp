#include<iostream>
#include<cmath>
#include<fstream>
#define n 50
using namespace std ;
struct WayPoint{
	float Abscissa ;//hoanh do
	float Ordinate ; //tung do
};
//ham tinh khoang cach giua hai diem trong khong gian hai chieu
float Distance( WayPoint A , WayPoint B ){
	return sqrt( pow( A.Abscissa - B.Abscissa , 2 ) + pow( A.Ordinate - B.Ordinate , 2 )  ) ;
}
float Min_Distance( WayPoint *C  ){
	float Min_D = pow(10 , 10);
	for( int i = 0 ; i < n ; i++ ){
		for( int j = i + 1 ; j < n ; j++ ){
			float kc = Distance( C[i] , C[j] ) ;
			if( kc < Min_D ) Min_D = kc ;
		}
	}
	return Min_D ;
}
//ham in ra cac cap diem co khoang cach nho nhat
int count = 0 ;
void CacCapDiemMin( WayPoint *C , float kc_min ){
	int dem = 0 ;
	for( int i = 0 ; i < n - 1; i++ ){
		for( int j = i+1 ; j < n ; j++ ){
			if( Distance(C[i] , C[j]) == kc_min ){
				printf(" (%5.0f,%-5.0f) - (%5.0f,%-5.0f)   \t" , C[i].Abscissa ,
				 C[i].Ordinate ,  C[j].Abscissa , C[j].Ordinate ) ;
				 dem++ ;
				 count++ ;
				 if( dem % 2 == 0 ) cout << endl ;
			}
		}
	}
}
int main(){
	WayPoint *C = new WayPoint[n] ; 
	ifstream filein ;
	filein.open("INPUT10.txt") ;
	if( filein.fail() ){
		cout << "MO FILE KHONG THANH CONG " ;
	}
	for( int i = 0 ; i < n ; i++ ){
		filein >> C[i].Abscissa ;
		filein >> C[i].Ordinate ;
	}
	float kc_min =  Min_Distance(C) ;
	cout <<"KHOANG CACH NHO NHAT : " <<kc_min ;
//	cout << "\nCAC CAP DIEM CO KHOANG CACH NHO NHAT\n" ;
//	CacCapDiemMin(C , kc_min )  ;
//	cout << "\n\nCO TAT CA " << count << " CAP" ;
	filein.close() ;
	delete C ;
	return 0 ;
}

