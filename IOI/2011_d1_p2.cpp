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

#include "race.h"


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
#define vv vector

using namespace std;

const int MAXN = 200*1000+10;
const int MOD = 1e9 + 7;

int n,k;
vector<ii> g[MAXN];

bool usedAsCentroid[MAXN];
int subtree[MAXN];

int best = MAXN;

map<int,int> uribaba;
vector<ii> newToInsert;

int C;
void dfs_main(int node,int p,int len,int tot){

	if(tot > k)return;
	if(tot == k){
		best = min(best,len);
		return;
	}
	if(C != node){
		if(uribaba.find(k-tot) != uribaba.end()){
			best = min(best,len + uribaba[k-tot]);
		}
		newToInsert.pb({tot,len});
	}

	for(auto e : g[node]){
		if(e.ff == p or usedAsCentroid[e.ff])continue;
		dfs_main(e.ff,node,len+1,tot + e.ss);
		if(C == node){
			for(auto x : newToInsert){
				if(uribaba.find(x.ff) != uribaba.end()){
					uribaba[x.ff] = min(uribaba[x.ff],x.ss);
				}else{
					uribaba[x.ff] = x.ss;
				}
			}
			newToInsert.clear();
		}
	}
}



void dfs_setup(int node,int p){
	subtree[node] = 1;
	for(auto e : g[node]){
		if(e.ff == p)continue;
		if(usedAsCentroid[e.ff])continue;
		dfs_setup(e.ff,node);
		subtree[node] += subtree[e.ff];
	}
}
int getCentroid(int node,int p,int S){
	for(auto e : g[node]){
		if(e.ff == p)continue;
		if(usedAsCentroid[e.ff])continue;
		//cout << e.ff << " " << subtree[e.ff] << " " << S << endl;
		if(subtree[e.ff]*2 > S+5)return getCentroid(e.ff,node,S);
	}
	return node;
}

void doCentroid(){
	FOR(i,n){
		if(usedAsCentroid[i])continue;
		dfs_setup(i,-1);
		//FOR(j,n)cout << subtree[j] << " ";cout << endl;
		int cent = getCentroid(i,-1,subtree[i]);
		C = cent;
		//cout << C << endl;
		uribaba.clear();
		dfs_main(cent,-1,0,0);
		usedAsCentroid[cent] = 1;
		i--;
	}
}

int best_path(int N,int K,int H[][2],int L[]){
	n = N;
	k = K;
	//cout << "f" << endl;
	FOR(i,n-1){
		int a = H[i][0];
		int b = H[i][1];
		int c = L[i];
		g[a].pb({b,c});
		g[b].pb({a,c});
	}
	//cout <<"d" << endl;
	doCentroid();
	if(best == MAXN){
		return -1;
	}else{
		return best;
	}

}
int mai11n(){
	int n = 4;
	int k = 3;
	int H[3][2] = {{0,1},{1,2},{1,3}};
	int L[3] = {1,2,4};
	cout << best_path(n,k,H,L) << endl;
	return 0;
}


int mai1n(){
	//subtree[0] = 5;
	//cout << subtree[0] << endl;
	int n = 3;
	int k = 3;
	int H[2][2] = {{0,1},{1,2}};
	int L[2] = {1,1};
	cout << best_path(n,k,H,L) << endl;
	return 0;
}