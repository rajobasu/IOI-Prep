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
#include <random>
#include <stack>
#include <chrono>
#include <set>

#include "ricehub.h"

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long int
#define vi vector<int>
#define ii pair<int,int>
#define pb push_back
#define mp make_pair
#define ff first
#define il pair<int,ll>
#define li pair<ll,int>
#define ss second
#define pll pair<ll,ll>
#define cd complex<double> 
#define ld long double
#define pld pair<ld,ld>
#define iii pair<ii,ll>
#define vv vector

using namespace std;

const ll INF = 1e16+10;
const int MAXN = 100*100*10+10;
const int MAXVAL = 1e9+10;

struct Node{
	int left;
	int right;
	ll p1;
	int p2;
	Node(){
		left = -1;
		right = -1;
		p1 = 0;
		p2 = 0;
	}
	void init(){
		left = -1;
		right = -1;
		p1 = 0;
		p2 = 0;
	}
};
Node B[(int)5*1000*1000];
int PTR= 0;
int get__(){
	B[++PTR].init();
	//cout << PTR << endl;
	return PTR;
}
struct Segtree{

	

	int head = get__();
	inline void expand(int node){
		if(B[node].left == -1)B[node].left = get__();
		if(B[node].right == -1)B[node].right = get__();
	}
	void update(int node,int ss,int se,int i,ll val){
		if(i > se or i < ss)return;
		expand(node);
		//cout << node << endl;
		if(ss==se){
			B[node].p1 += val;
			B[node].p2 += 1;
			return;
		}
		int mid = (ss+se)/2;
		update(B[node].left,ss,mid,i,val);
		update(B[node].right,mid+1,se,i,val);
		B[node].p1 = B[B[node].left].p1 + B[B[node].right].p1;
		B[node].p2 = B[B[node].left].p2 + B[B[node].right].p2;
	}
	li get(int node,int ss,int se,int l,int r){
		if(node == -1)return {0,0};
		if(l > se or ss > r)return {0,0};
		if(l <= ss and se <= r)return {B[node].p1,B[node].p2};
		int mid = (ss+se)/2;
		li a = get(B[node].left,ss,mid,l,r);
		li b = get(B[node].right,mid+1,se,l,r);
		return {a.ff+b.ff,a.ss+b.ss};
	}
};
Segtree st;
int besthub(int r,int l,int h[],ll b){

	FOR(i,r){
		st.update(st.head,0,MAXVAL,h[i],h[i]);
	}
	int best = 1;

	FOR(i,r){
		int lo = 0;
		int hi = l+10;
		while(lo <= hi){
			int mid = (lo+hi)>>2;

			
			int s = h[i]-mid;
			int e = h[i]+mid;

			li cost1 = st.get(st.head,0,MAXVAL,h[i],min(h[i]+mid,MAXVAL-1));
			cost1.ff -= (ll)h[i]*cost1.ss;

			li cost2 = st.get(st.head,0,MAXVAL,max(h[i]-mid,0),h[i]-1);
			cost2.ff = (ll)h[i]*cost2.ss - cost2.ff;
			
			li cc = {0,0};
			li costs = s >= 0? st.get(st.head,0,MAXVAL,s,s) : cc;
			li coste = e <= MAXVAL-1?st.get(st.head,0,MAXVAL,e,e) : cc;
			li csts = {((ll)costs.ss*h[i] - costs.ff) + (coste.ff - (ll)h[i]*coste.ss), costs.ss + coste.ss};

			ll perThingycost = 0;
			ll offset = 0;
			ll prod = 0;
			if(csts.ss > 0){
				perThingycost = csts.ff / csts.ss;

			
				ll left = max((ll)0,(cost2.ff + cost1.ff) - b);
				prod = ceil(left*1.0/perThingycost);
				prod = min(prod,(ll)csts.ss);
				offset = prod*perThingycost;
			}	
			//cout << prod << " " << offset << " " << lo << " " << hi << endl;
			if(cost2.ff + cost1.ff - offset <= b){
				best = max(best,cost1.ss+cost2.ss - (int)prod);
				if(lo == hi)break;
				lo = mid+1;
			}else{
				if(lo == hi)break;
				hi = mid-1;
			}
		}
	}

	return best;
}

int ma1in(){
	int a[5] = {1,2,10,12,14};
	cout << besthub(5,50,a,6) << endl;
	return 0;
}