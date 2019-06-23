#include <bits/stdc++.h>

#define ll long long int
#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i = a;i<=b;i++)
#define vi vector<int>
#define ii pair<int,int>
#define ff first
#define ss second

//#include "game.h"

using namespace std;

const int INF = 1e9;
const int MAXN = 1501;

int cnt[MAXN];

void initialize(int n){
	FOR(i,n){
		cnt[i] = i;
	}
}

int hasEdge(int a,int b){
	if(a < b)swap(a,b);
	cnt[a]--;
	if(cnt[a] == 0)return 1;
	return 0;

}

int mai1n(){
	initialize(4);
	cout << hasEdge(0,3) << endl;
	cout << hasEdge(0,1) << endl;
	cout << hasEdge(0,2) << endl;
	cout << hasEdge(1,3) << endl;
	cout << hasEdge(1,2) << endl;
	cout << hasEdge(2,3) << endl;

}