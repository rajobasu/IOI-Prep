/*
SOLUTION: First, we should match larger elements in first half and smaller in second. So overall just matching with
the sorted order of Bessie's cards work. Now, we need to try switching at each point and checking in either 
halfs the scores that we will obtain if we make a switch there. This can be done with a segment tree
with the information (#pairedup, #bessies cards, # elsie's cards). Rest is easy to figure out.
COMPLEXITY: O(nlogn)
*/

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
#include <stack>
#include <set>
#include <fstream>

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long int
#define vi vector<int>
#define ii pair<ll,ll>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define pll pair<ll,ll>


using namespace std;

const int MOD = 1000000007;
const ll INF = 100000000000000000;
const int MAXN = 200001;

class SegmentTree{
	pair<int,ii> st[4*MAXN];// ff = paired. ss.ff = elsie's ss.ss = Bessie's
	public:
	void update(int node,int ss,int se,int i,int val){// val = 0 is elsie's
		if(ss > i or i > se)return;
		if(ss == se){
			if(val == 0)st[node].ss.ff++;
			else st[node].ss.ss++;

			return;
		}
		int mid = (ss+se)/2;
		update(node*2+1,ss,mid,i,val);update(node*2+2,mid+1,se,i,val);
		int pairup = min(st[node*2+1].ss.ff,st[node*2+2].ss.ss);
		st[node] = {st[node*2+1].ff + st[node*2+2].ff + pairup,
			{st[node*2+1].ss.ff-pairup + st[node*2+2].ss.ff,
			st[node*2+1].ss.ss + st[node*2+2].ss.ss - pairup}};
	}
	int query(){
		return st[0].ff;
	}
};

#define cout fout
#define cin fin

int main(){	

	ifstream fin;
	ofstream fout;
	fin.open("cardgame.in");
	fout.open("cardgame.out");
	int n;
	cin >> n;
	int arr[n];
	FOR(i,n)cin >> arr[i];
	bool f[2*n+1];
	FOR(i,2*n+1)f[i] = 0;
	FOR(i,n)f[arr[i]] = 1;
	int arr2[n];
	int loc = 0;
	FOR(i,2*n+1){

		if(i>0 and !f[i])arr2[loc++] = i;
	}
	sort(arr2,arr2+n,greater<int>());
	//FOR(i,n)cout << arr2[i] << " ";cout << endl;
	int pref[n];
	int suf[n];
	SegmentTree segtree1,segtree2;
	int mx = 0;
	FOR(i,n){
		segtree1.update(0,0,MAXN,arr[i],0);
		segtree1.update(0,0,MAXN,arr2[i],1);
		segtree2.update(0,0,MAXN,2*n-arr[n-i-1]+1,0);
		segtree2.update(0,0,MAXN,2*n-arr2[n-i-1]+1,1);
		pref[i] = segtree1.query();
		suf[n-i-1] = segtree2.query();
	}
	mx = max(pref[n-1],suf[0]);
	FOR(i,n-1){
		mx = max(mx,pref[i] + suf[i+1]);
	}
	cout << mx << endl;
	return 0;
}
