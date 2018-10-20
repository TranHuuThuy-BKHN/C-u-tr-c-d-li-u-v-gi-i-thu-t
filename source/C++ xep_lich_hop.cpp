#include<iostream>
#include<algorithm>
#include<cstdlib>
#define n 10
using namespace std ;
struct CuocHop{
	int str , end ;
};
struct Phong{
	int SoCuocHop ;
	CuocHop C[n] ;
};
bool ThoaMan( CuocHop A , CuocHop B ){
	return B.str-A.end >= 15 ;
}
Phong *P = new Phong[n] ;
int SoPhong = 1 ;
void XepCacCuocHop( CuocHop *A , int SoCuocHop ){
	CuocHop *B = new CuocHop[SoCuocHop] ;
	P[SoPhong-1].C[0] = A[0] ;
	int S = 1 , d = 0 ;
	for( int i = 1 ; i < SoCuocHop ; i++ ){
		if( ThoaMan( P[SoPhong-1].C[S-1] , A[i] ) ){
			P[SoPhong-1].C[S++] = A[i] ;			
		}
		else B[d++] = A[i] ;
	}
	P[SoPhong-1].SoCuocHop = S ;
	if( d != 0 ){
		SoPhong++ ;
		XepCacCuocHop(B,d) ;
	}
	delete []B ;
}
void RandomCuocHop( CuocHop *C ){
	int ThoiLuong = rand()%120 + 1 ;
	for( int i = 0 ; i < n ; i++ ){
		C[i].str = rand()%1320 ; C[i].end = C[i].str + ThoiLuong ;
	}
}
void Output_Phong(){
	for( int i = 0 ; i < SoPhong ; i++ ){
		cout << "\nPHONG " << i+1 << endl ;
		for( int j = 0 ; j < P[i].SoCuocHop ; j++ ){
			CuocHop C = P[i].C[j] ;
			cout << C.str/60 <<"h"<<C.str%60<<"' : " << C.end/60 <<"h"<<C.end%60<<"'\n" ;
		}
	}
}
bool cmp_s( const CuocHop &A , const CuocHop &B ){
	return A.str < B.str ;
}
int main(){
	CuocHop *C = new CuocHop[n] ;
	RandomCuocHop(C) ;
	sort( C , C + n , cmp_s );
	XepCacCuocHop(C,n) ;
	Output_Phong() ;
	delete []C ;
	delete []P ;
	return 0 ;
}
