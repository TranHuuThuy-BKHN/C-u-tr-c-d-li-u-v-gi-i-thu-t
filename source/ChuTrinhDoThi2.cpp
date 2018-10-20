#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>

using namespace std;

struct Top {
	int pos, par, pre, post;
	bool visited;
	vector<int> neb;
};

struct Edge {
	int start, end;
};

typedef Top* top;
typedef vector<top> graph;
vector<Edge> edge, backEdge;

top init(int pos) {
	top p = new Top;
	p->pos = pos;
	return p;	
}

void previsit(top &v, int &clock) {
	v->pre = clock;
	clock = clock + 1;	
}

void postvisit(top &v, int &clock) {
	v->post = clock;
	clock = clock + 1;
}

void explore(graph &G, top &u, int &clock) {
	u->visited = true;
	previsit(u, clock);
	int index = 0;
	for(int i = 0; i < u->neb.size(); i++) {
		index = u->neb[i];
		if(G[index]->visited == false)
			explore(G, G[index], clock);
		else {
			Edge ed;
			ed.start = u->pos;
			ed.end = G[index]->pos;
			edge.push_back(ed);
		}	
	}
	postvisit(u, clock);
}

void dfs(graph &G) {
	int clock = 1;
	for(int i = 0 ; i < G.size() ; i++)
		G[i]->visited = false;
	for(int i = 0 ; i < G.size() ; i++)
		if(G[i]->visited == false)
			explore(G, G[i], clock);			
}
//===========================================================================================
//ham tim ra tat ca cac canh back cua do thi
void findBack(graph &G) {
	dfs(G);
	for(int i = 0; i < edge.size(); i++) {
		int u = edge[i].start, v = edge[i].end;
		if(G[v]->pre < G[u]->pre && G[v]->post > G[u]->post)
			backEdge.push_back(edge[i]);
	}	
}


void readFile(ifstream &ifs, graph &G) {
	ifs.open("data.txt");
	vector<int> arr;
	int data = 0, size = 0, r = 0, c = 0;
	while(ifs.eof() == false) {
		ifs >> data;
		arr.push_back(data);
	}
	size = sqrt(arr.size());
	for(int i = 0; i < size; i++) {
		top p = init(i);
		G.push_back(p);
	}
	for(int i = 0; i < arr.size(); i++) {
		if(arr[i] != 0) {
			r = i / size;
			c = i - r * size;
			G[r]->neb.push_back(G[c]->pos);
		}
	} 	
}

void print(graph G, top u, top v) {
	int i = v->pos;
	do {
		cout << i << "<--";
		i = G[G[i]->par]->pos;
	} while(i != u->pos);
	cout << i << endl;
}
//ham tim ra cac chu trinh tu mot canh back
void explore(graph &G, top &u, top &v,const int end) {
	u->visited = true;
	int index = 0;
	for(int i = 0; i < u->neb.size(); i++) {
		index = u->neb[i];
		if(G[index]->pos != v->pos && G[index]->visited == false) {
			G[index]->par = u->pos;
			explore(G, G[index], v, end);
		}
		else if(G[index]->pos == v->pos) {
			G[index]->par = u->pos;
			print(G, G[end], v);
		}
	}
} 

int main(){
	ifstream ifs;
	graph G;
	readFile(ifs, G);
	findBack(G);
	for(int i = 0; i < backEdge.size(); i++) {
		for(int j = 0; j < G.size(); j++)
			G[j]->visited = false;
		top u = G[backEdge[i].end];
		top v = G[backEdge[i].start];
		explore(G, u, v, u->pos);
	}
	return 0 ;
}
