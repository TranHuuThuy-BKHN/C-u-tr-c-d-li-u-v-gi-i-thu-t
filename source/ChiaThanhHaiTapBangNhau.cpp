#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

int avg = 0;
vector<int> arr;
vector<int> mark;
vector<int> result;
int sum = 0;
bool check = false;

void backtracking(int pos) {
	if(check == false) {
		sum += arr[pos];
		if(sum == avg) {
			result.push_back(arr[pos]);
			mark[pos] = 1;	
			cout << "{";
			for(int i = 0; i < result.size(); i++)	
				cout << result[i] << ",";
			cout << "}, {";
			for(int i = 0; i < arr.size(); i++)
				if(mark[i] == 0)
					cout << arr[i] << ",";
			cout << "}\n";		
			check = true;
		}
		else if(sum < avg) {
			result.push_back(arr[pos]);
			mark[pos] = 1;
			for(int i = pos + 1; i < arr.size(); i++) {
				backtracking(i);
			}
			result.pop_back();
			sum -= arr[pos];
			mark[pos] = 0;		
		}
		else {
			sum -= arr[pos];
			mark[pos] = 0;	
		}
	}
}

int main(){
	ifstream ifs;
	ifs.open("int.txt");
	int data = 0;
	while(ifs.eof() == false) {
		ifs >> data;
		sum = sum + data;
		arr.push_back(data);
		mark.push_back(0);
	}
	if(sum % 2 == 1)
		cout << "Khong The Chi Thanh Hai Tap Do Tong Cua Chung La So Le";
	else {
		avg = sum / 2;
		for(int i = 0; i < arr.size(); i++) {
			sum = 0;
			result.clear();
			backtracking(i);
		}
	}	
	return 0;
}
