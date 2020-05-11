/* majority element greedy + verification*/
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
#include <complex>
#include <chrono>
#include <random>
#include <stack>
#include <set>
#include <fstream>

#define FOR(i,n) for(int i = 0;i < n; i++)
#define FORE(i,a,b) for(int i = a; i <= b ; i++)
#define ss second
#define ff first
#define ll long long int
#define ii pair<ll,ll>
#define il pair<int,ll>
#define li pair<ll,int>
#define x ff
#define y ss
#define lii pair<ll,pair<int,int> > 
#define piil pair<int ,pair<int,int> > 
#define iii pair<pair<int,int>,int> 
#define vi vector<int>
#define pb push_back
#define mp make_pair
using namespace std;

const int MAXT = 11*1000*100;
const int MAXN = 500*1000 + 5;
struct SegmentTree{
	ii st[MAXT];
	SegmentTree(){
		FOR(i,MAXT)st[i] = {-1,0};
	}
	ii combine(ii a,ii b){
	//	cout << a.ff << " " << a.ss << " :: " << b.ff << " "<< b.ss << endl;
		if(a.ff == -1)return b;
		if(b.ff == -1)return a; 
		if(a.ff == b.ff)return {a.ff,a.ss+b.ss};
		else if(a.ss > b.ss)return {a.ff,a.ss - b.ss};
		else return {b.ff,b.ss-a.ss};
	}
	void build(int node,int ss,int se,int* arr){
		if(ss == se){
			st[node] = {arr[ss],1};
			return;
		}
		int mid = (ss+se)/2;
		build(node*2+1,ss,mid,arr);
		build(node*2+2,mid+1,se,arr);
		st[node] = combine(st[node*2+1],st[node*2+2]);
	//	cout << ss << " " << se << " " << st[node].ff << " " << st[node].ss << endl;
 	}
	
	ii get(int node,int ss,int se,int l,int r){
		if(l > se or ss > r)return {-1,0};
		if(l <= ss and se <= r)return st[node];
		int mid= (ss+se)/2;
		return combine(get(node*2+1,ss,mid,l,r),get(node*2+2,mid+1,se,l,r));
	}

} segtree;


vi freq[MAXN];

int count(int a,int b,int c){
	int ctr = 0;
	for(auto e : freq[c]){
		if(a <= e and e <= b)ctr++;
	}
	return ctr;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,q;
	cin >> n >> q;
	int arr[n];
	FOR(i,n)cin >> arr[i];
	segtree.build(0,0,n-1,arr);
	FOR(i,n){
		//segtree.update(0,0,MAXN,i,arr[i]);
		freq[arr[i]].pb(i);
	}
	FOR(i,q){
		int a,b;
		cin >> a >> b;
		a--;b--;
		int candidate = segtree.get(0,0,n-1,a,b).ff;

		int cnt = lower_bound(freq[candidate].begin(), freq[candidate].end(),b+1)
					- lower_bound(freq[candidate].begin(), freq[candidate].end(),a);
		//cout << cnt << " " << candidate << endl;
		//cnt = count(a,b,candidate);
		if(cnt*2 > (b-a+1)){
			cout << candidate << endl;
		}else{
			cout << 0 << endl;
		}

	}	

	return 0;
}