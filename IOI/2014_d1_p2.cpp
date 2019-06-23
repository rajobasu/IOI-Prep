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
const int MAXN = 2e6+10;

int st[4*MAXN];
ii lazy[4*MAXN];//{lower, upper}

void print(ii a){
	//cout << a.ff << " " << a.ss << endl;
}

inline ii combineTag(ii tag1,ii tag2){
	if(tag1.ff == -2)return tag2;
	int mn = max(tag1.ff,tag2.ff);
	int mx = min(tag1.ss,tag2.ss);
	// mn < mx
	if(mn <= mx)return {mn,mx};
	if(tag2.ff > tag1.ss)return {tag2.ff,tag2.ff};
	if(tag2.ss < tag1.ff)return {tag2.ss,tag2.ss};
}

inline void push_down(int node,int ss,int se){
	if(ss != se){
		lazy[node*2+1] = combineTag(lazy[node*2+1],lazy[node]);
		lazy[node*2+2] = combineTag(lazy[node*2+2],lazy[node]);
	}
}

inline void process_lazy(int node,int ss,int se){
	if(lazy[node].ff == -2)return;
	//cout << ss << " " << se << " : ";print(lazy[node]);
	if(ss==se){
		if(st[node] > lazy[node].ss)st[node] = lazy[node].ss;
		if(st[node] < lazy[node].ff)st[node] = lazy[node].ff;
	}else
		push_down(node,ss,se);

	//cout << ss << " " << se << " :: " << st[node] << endl;
	lazy[node] = {-2,INF};
}

void update(int node,int ss,int se,int l,int r,int t,int val){
	process_lazy(node,ss,se);
	if(l > se or ss > r)return;
	//cout << ss << " " << se << endl;
	if(l <= ss and se <= r){
		if(t == 1){
			// lowerbounding
			lazy[node] = {val,INF};
		}else{
			lazy[node] = {-1,val};
		}
		process_lazy(node,ss,se);
		return;
	}
	int mid = (ss+se)/2;
	update(node*2+1,ss,mid,l,r,t,val);
	update(node*2+2,mid+1,se,l,r,t,val);

	//st[node] = {max(st[node*2+1].ff,st[node*2+2].ff),min(st[node*2+1].ss,st[node*2+2].ss)};
	//print(st[node]);
	//print(st[node*2+1]);
	//print(st[node*2+2]);
	//cout << endl;
}

int get(int node,int ss,int se,int i){
	//cout << ss << " " << se << endl;
	process_lazy(node,ss,se);
	if(i > se or i < ss)return -1;
	if(ss == se){
	//	cout << ss << " " << se << " " << st[node] << endl;
		return st[node];
	}
	int mid = (ss+se)/2;
	return max(get(node*2+1,ss,mid,i),get(node*2+2,mid+1,se,i));
}

void buildWall(int n, int k, int op[], int left[], int right[],int height[], int finalHeight[]){
	FOR(i,4*MAXN)lazy[i] = {-2,INF};
	FOR(i,k){
		update(0,0,MAXN,left[i],right[i],op[i],height[i]);
	}
	FOR(i,n){
		finalHeight[i] = get(0,0,MAXN,i);
	}
}



int m1ain(){


	int n = 10;
	int k = 6;
	int op[6] = {1,2,2,1,1,2};
	int left[6] = {1,4,3,0,2,6};
	int right[6] = {8,9,6,5,2,7};
	int height[6] = {4,1,5,3,5,0};
	int fin[10];
	buildWall(n,k,op,left,right,height,fin);
	FOR(i,10)cout << fin[i] << " ";
	cout << endl;
	return 0;
}