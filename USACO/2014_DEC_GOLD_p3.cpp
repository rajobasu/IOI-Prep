/**
SOLUTION: Find where the cars will be at the end of T seconds. sort using this value. Each lane will 
have a increasing subsequence. Count number of increasing subsequences we need to break this into.
Apply dilworths theorem.
COMPLEXITY : nlogn

PS: i used segtree, sets can also be used.

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
const int MAXN = 100001;
ll st[4*MAXN];



void update(int node,int ss,int se,int i,ll val){
	if(i < ss or i > se)return ;
	if(ss==se){
		st[node] = max(val,st[node]);
		return;
	}
	int mid = (ss+se)/2;
	update(node*2+1,ss,mid,i,val);
	update(node*2+2,mid+1,se,i,val);
	st[node] = max(st[node*2+1],st[node*2+2]);
}
ll get(int node,int ss,int se,int l,int r,ll val){
	if(ss > r or se < l)return 0;
	if(ss==se){
		if(st[node] > val){
			return ss;
		}else{
			return 0;
		}
	}
	int mid = (ss+se)/2;
	if(l <= ss and se <= r){
		if(st[node*2+2] > val){
			return get(node*2+2,mid+1,se,l,r,val);
		}else{
			return get(node*2+1,ss,mid,l,r,val);
		}
	}

	return max(get(node*2+1,ss,mid,l,r,val),get(node*2+2,mid+1,se,l,r,val));
}


#define cout fout
#define cin fin

int main(){
	ifstream fin;
	ofstream fout;
	fin.open("cowjog.in");
	fout.open("cowjog.out");

	int n,t;
	cin >> n >> t;

	pll all[n];
	FOR(i,n){
		cin >> all[i].ff >> all[i].ss;
	}

	FOR(i,n){
		all[i].ss = (t*all[i].ss + all[i].ff);
		all[i].ff = -all[i].ff;  
		swap(all[i].ff,all[i].ss);
	}

	sort(all,all + n);
	FOR(i,n)all[i].ss *=-1;
	int dp[n];
	dp[0] = 1;
	update(0,0,MAXN,1,all[0].ss);

	FOR(i,n){
		//cout << all[i].ss << "  " << all[i].ff << endl;
	}

	int mx = 0;
	FOR(i,n){
		if(i == 0)continue;
		dp[i] = 1 + get(0,0,MAXN,0,MAXN,all[i].ss);
		update(0,0,MAXN,dp[i],all[i].ss);
		mx = max(mx,dp[i]);
	}

	cout << mx << endl;




	return 0;
}