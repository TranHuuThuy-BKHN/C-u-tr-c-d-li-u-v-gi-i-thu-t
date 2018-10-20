#include<iostream>
#include<fstream>
#include<windows.h>
#include<PrefixTree.h>
#define EH 0
#define LH -1
#define RH 1

using namespace std ;

struct AVLNode{
	string word, mean;
	int balance;
	AVLNode *left, *right;	
};

typedef AVLNode* AVLTree;

void init(AVLTree &T){
	T = NULL;	
}

AVLNode *creatNode(string word, string mean){//ham tao ra node
	AVLNode *p = new AVLNode;
	p->word = word; p->mean = mean;
	p->balance = EH;
	p->left = p->right = NULL;
	return p;
}

void left_left(AVLTree &T){ //quay con trai lech trai
	AVLNode *T1 = T->left, *r = T1->right;
	T->left = r; T1->right = T;
	switch(T1->balance){
		case LH :                 //neu ban dau T->left lech trai
			T1->balance = T->balance = EH; break;
		case EH : T->balance = LH; // neu cay trai ban dau can bang
				  T1->balance = RH;			  
	}
	T = T1;
}

void right_right(AVLTree &T){ //quay con phai lech phai
	AVLNode *T1 = T->right, *r = T1->left;
	T->right = r ; T1->left = T;
	switch(T1->balance){
		case RH : 
			T1->balance = T->balance = EH; break;
		case EH:
			T->balance = RH;
			T1->balance = LH;	
	}
	T = T1;	
}

void right_left(AVLTree &T){ //quay con trai lech phai  
	AVLNode *T1 = T->left, *r = T1->right, *r_left = r->left, *r_right = r->right;
	r->left = T1; r->right = T;
	T1->right = r_left;
	T->left = r_right;
	switch(r->balance){
		case EH : T1->balance = T->balance = EH; break;
		case RH : T1->balance = LH; T->balance = EH; break;
		case LH : T1->balance = EH; T->balance = RH;
	}
	r->balance = EH;
	T = r;
}

void left_right(AVLTree &T){ //quay con phai lech trai
	 AVLNode *T1 = T->right, *r = T1->left,  *r_left = r->left, *r_right = r->right;
	 r->left = T; r->right = T1;
	 T->right = r_left;
	 T1->left = r_right;
	 switch(r->balance){ 
	 	case EH : T->balance = T1->balance = EH; break;
		case RH : T->balance = LH; T1->balance = EH; break;
		case LH : T->balance = EH; T1->balance = RH;   
	 }
	 r->balance = EH;
	 T = r;
}

void balLeft(AVLTree &T){ //ham quay khi cay bi lech trai
	AVLNode *T1 = T->left;
	switch(T1->balance){
		case LH : left_left(T); break;
		case RH : right_left(T); 
	}
}

void balRight(AVLTree &T){ //ham quay can bang lech phai
	AVLNode *T1 = T->right;
	switch(T1->balance){
		case RH : right_right(T); break;
		case LH : left_right(T); 
	}
}

int insertAVLTree(AVLTree &T, string word, string mean){
	if(T == NULL){
		T = creatNode(word, mean);
		return 2;//tra ve gia tri de thong bao cay co do lech khac 0
	}
	else{
		int res, cmp = T->word.compare(word);
		if(cmp == 0) return 0; //cay da co word
		if(cmp > 0){//can chen vao ben trai
			res = insertAVLTree(T->left, word, mean);
			if(res < 2) return res;             // neu cay khong mat can bang thi khong can dieu chinh
			//dieu chinh lai do lech cua T va xoay
			switch(T->balance){ 
				case EH : T->balance =  LH; return 2; 
				case RH : T->balance = EH; return 1;
				case LH : balLeft(T); return 1;
			}
		}
		if(cmp < 0){
			res = insertAVLTree(T->right, word, mean);
			if(res < 2) return res;// neu cay khong mat can bang thi khong can dieu chinh
			switch(T->balance){//dieu chinh lai do lech cua T
				case EH : T->balance = RH; return 2;
				case LH : T->balance = EH; return 1;
				case RH : balRight(T); return 1;
			}
		} 
	}
}

AVLNode *AVLSearch(AVLTree T, string word){
	if(T == NULL) return NULL;
	int cmp = T->word.compare(word);
	if(cmp == 0) return T;
	else if(cmp > 0) 
		return AVLSearch(T->left, word);
	return AVLSearch(T->right, word);		
}

void printWord(PrefixTree pf, string word){ //ham in ra cac goi y
	char *temp = new char[word.length()];
	for(int i = 0 ; i < word.length() ; i++)
		temp[i] = word[i];
	PrefixTree t = Search(pf, temp, word.length());
	if(t != NULL)
		Print(t, word);
}

void menu(AVLTree T, PrefixTree pf){
	int LuaChon;
	string word ;
	do{
		cout << "\n==============MENU==============\n";
		cout << "\n0.Thoat";
		cout << "\n1.Hien thi nghia";
		cout << "\n2.Tu goi y";
		cout << "\n==============END==============\n";
		cout << "\nNhap word : " ; fflush(stdin);
		getline(cin, word);
		do{
			cout << "Lua Chon : "; cin >> LuaChon;
		}while(LuaChon < 0 || LuaChon > 2);
		if(LuaChon == 1){
			AVLNode* t = AVLSearch(T, word);
			if(t != NULL)
				cout << t->mean << endl;
		}
		if(LuaChon == 2){
			printWord(pf, word);
		}
		if(LuaChon){
			system("pause") ; system("cls");
		}
	}while(LuaChon);	
}

int getHight(AVLTree T){
	if(T == NULL) return -1;
	return max(getHight(T->left), getHight(T->right)) + 1;
}
int main(){
	SetConsoleOutputCP(65001);
	PrefixTree pf = new NODE_PrefixTree;
	AVLTree T;
	init(T);
	init(pf);
	ifstream ifs;
	ifs.open("Anh-Viet.txt");
	string temp, word, mean;
	while(ifs.eof() == false){
		getline(ifs, temp);
		getline(ifs, word);
		getline(ifs, mean);
		mean = " " + mean; 
		insertAVLTree(T, word, mean);
		Insert(pf, word);
	}
	ifs.close();
	menu(T, pf);
 	return 0;
}
