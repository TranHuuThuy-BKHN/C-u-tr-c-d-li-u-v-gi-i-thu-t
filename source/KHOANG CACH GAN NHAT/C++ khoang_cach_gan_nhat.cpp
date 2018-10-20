#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std ;
struct Diem{
	float HoangDo,TungDo ;
};
float KC( Diem A , Diem B ){
	return sqrt( pow(A.HoangDo-B.HoangDo , 2) + pow(A.TungDo-B.TungDo,2) ) ;
}
float VetCan( Diem *C , int L , int R ){
	float Min = pow(10,10) ;
	for( int i = L ; i < R ; i++ ){
		for( int j = i+1 ; j <= R ; j++ ){
			float x = KC( C[i] , C[j] ) ;
			if( Min > x ) Min = x ;
		}
	}
	return Min ;
}
void Tim_dai( Diem *C , float d, int &Mid_L , int &Mid_R , int L , int R ){
	int Mid = (L+R)/2 ;
	for( int i = L ; i <= R ; i++ )
		if( C[i].HoangDo >= C[Mid].HoangDo-d ){
			Mid_L = i ; break ;
		}
	for( int i = R ; i >= L ; i-- )
		if( C[i].HoangDo <= C[Mid].HoangDo + d ){
			Mid_R = i ; break ;
		}
}
bool TrongHinhVuong( Diem a , Diem A , float d ){
	return A.HoangDo-d <= a.HoangDo && A.HoangDo+d >= a.HoangDo && A.TungDo+d >= a.TungDo && A.TungDo-d <= a.TungDo ;
}
bool cmp_x( const Diem &a , const Diem &b ){
	return a.HoangDo < b.HoangDo ;
}
bool cmp_y( const Diem &a , const Diem &b ){
	return a.TungDo < b.TungDo ;
}
float KC_Mid( Diem *C , int L , int R , float d ){
	float Min = pow(10,10) ;
	for( int i = L ; i <= R ; i++ ){//Tuy hai vong for nhung thoi gian chi la O(n) do moi diem chi kiem tra voi
		for( int j = L ; j < i ; j++ ){                                                    //toi da 6 diem khac
			if( TrongHinhVuong( C[j] , C[i] , d ) ){
					float x = KC(C[i] , C[j]) ;
					if( Min > x ) Min = x ;
			    }
		}
	}
	return Min ;
}
float KC_Min( Diem *C , int L , int R ){
	if( R - L <= 2 ) return VetCan( C,L,R ) ;//neu co it hon 4 diem thi ta vet can
	int Mid = ( L + R )/2 , Mid_L , Mid_R ;
	float d_left = KC_Min(C,L,Mid) , d_right = KC_Min(C,Mid+1,R) ;//tim ra khoang cach o nua trai va phai
	float d = min(d_left , d_right) ;
	Tim_dai( C , d , Mid_L , Mid_R , L , R ) ;//tim dai o giua
	float d_mid = KC_Mid(C , Mid_L , Mid_R , d ) ;//tim khoang cach nho nhat o nua giua
	return min(d,d_mid) ;
}
int main(){
	int n  ;
	cin >> n ;
	Diem *C = new Diem[n] ;
	for( int i = 0 ; i < n ; i++ ){
		cout << "Nhap Toa Do Diem Thu " << i+1 <<endl ;
		cin >> C[i].HoangDo >> C[i].TungDo ;
	}
	sort(C,C+n,cmp_x) ;
	float d_min = KC_Min(C,0,n-1) ;
	cout << "Khoang Cach Min : "<< d_min ;
	cout << "\nHai Diem Co Khoang Cach Min : " ;
	for( int i = 0 ; i < n ; i++ ){
		int danh_dau = 0 ; 
		for( int j = i+1 ; j < n ; j++ ){
			if( TrongHinhVuong(C[j],C[i],d_min) ){
				if( KC( C[i],C[j] ) == d_min ){
					cout << "(" << C[i].HoangDo << "," << C[i].TungDo << ") : " << "("<<  C[j].HoangDo << "," << C[j].TungDo << ")" ;
					danh_dau = 1 ; break ;
				}
			}
		}
		if( danh_dau == 1 ) break ; 
	}
	delete []C ;
	return 0 ;
}
