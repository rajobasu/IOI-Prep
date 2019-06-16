#include <iostream>
#include <vector>
#include <set>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <stdio.h>
#include <cmath>
#include <queue>
#include <string>
#include <map>
#include <fstream>
#include <complex>
#include <stack>
#include <set>

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long int
#define vi vector<int>
#define ii pair<int,int>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define pll pair<ll,ll>
#define cd complex<double> 
#define ld long double
#define pld pair<ld,ld>
#define iii pair<ii,int>

using namespace std;

const ll INF = 1e9+10;
const int MAXN = 10000*100+10;




struct Node{
	int left,right;
	int val;
};

Node BUF[20*MAXN];

int ppt = 0;
int init(int left=-1,int right=-1,int v=0){
	int x = ppt++;
	BUF[x].left = left; BUF[x].right = right;
	BUF[x].val = v;
	return x;
}


int versions[MAXN];
int len[MAXN];

inline void expand(int node){
	if(node == -1)node = init();
	//if(node->left == NULL)node->left = new Node(0);
	//if(node->right == NULL)node->right = new Node(0);
}

int update(int node,int ss,int se,int i,int val){
	if(ss > i or se < i)return node;
	//expand(node);
	if(ss == se){
		return init(BUF[node].left,BUF[node].right,val);
	}else{
		int mid = (ss+se)/2;
		auto l = BUF[node].left;
		auto r = BUF[node].right;
		if(i <= mid){
			if(BUF[node].left == -1)BUF[node].left = init();
			l = update(BUF[node].left,ss,mid,i,val);
		}
		else{
			if(BUF[node].right == -1)BUF[node].right = init();
			r = update(BUF[node].right,mid+1,se,i,val);
		}
		return init(l,r,0);
	}
}
int get(int node,int ss,int se,int i){
	if(ss > i or se < i)return -1;
	if(node == -1)return -1;
	if(ss==se)return BUF[node].val;
	int mid=(ss+se)/2;
	return max(get(BUF[node].left,ss,mid,i),get(BUF[node].right,mid+1,se,i));
}

int PTR = 0;

void Init(){
	versions[0] = init();
	len[0] = 0;
}

void TypeLetter(char a){
	PTR++;
	versions[PTR] = update(versions[PTR-1],0,MAXN,len[PTR-1],a);
	len[PTR] = len[PTR-1]+1;
}

void UndoCommands(int x){
	PTR++;
	versions[PTR] = versions[PTR-x-1];
	len[PTR] = len[PTR-x-1];
}

char GetLetter(int p){
	return (char)get(versions[PTR],0,MAXN,p);
}

/*
int main(){
	Init();
	TypeLetter('a');
	TypeLetter('b');
	cout << GetLetter(1) << endl;
	TypeLetter('d');
	UndoCommands(2);
	UndoCommands(1);
	cout << GetLetter(2) << endl;
	TypeLetter('e');
	UndoCommands(1);
	UndoCommands(5);
	TypeLetter('c');
	cout << GetLetter(2) << endl;
	UndoCommands(2);
	cout << GetLetter(2) << endl;



	return 0;
}


*/