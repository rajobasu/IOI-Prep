/*
SOLUTION : Have a DS to find unique element count in L to R (here, MST in log^2(n) time)
binsrch for each index. 
overall nlog^3(n) soln
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
#define cd complex<double> 

const ll INF = 4e18;
using namespace std;
const int MAXN = 100005;

vi st[4*MAXN];
int arr[MAXN];
void build(int node,int ss,int se){
	if(ss == se){
		//cout << "boo " << endl;
		
		st[node].pb(arr[ss]);
	}else{
		int mid = (ss+se)/2;
		build(node*2+1,ss,mid);
		build(node*2+2,mid+1,se);
		//st[node] = new vi(st[node*2+1].size() + st[node*2+2].size());//.reserve(st[node*2+1].size() + st[node*2+2].size());
		for(auto e:st[node*2+1])st[node].pb(e);
		for(auto e:st[node*2+2])st[node].pb(e);
		sort(st[node].begin(), st[node].end());
		//merge(st[node*2+1].begin(), st[node*2+1].end(), st[node*2+2].begin(), st[node*2+2].end(),st[node].begin());
		//cout << ss << " " << se;
		//cout << " :: ";
		//for(auto e:st[node])cout<<e<< " ";
		//	cout << endl;
	}
}
int query(int node,int ss,int se,int l,int r,int val){
	if(ss > r or se < l)return 0;
	if(l <= ss and se <= r){
		int ans = lower_bound(st[node].begin(), st[node].end(),val) - st[node].begin();
		return ans;
	}
	int mid = (ss+se)/2;
	return query(node*2+1,ss,mid,l,r,val) + query(node*2+2,mid+1,se,l,r,val);
}

#define cin fin
#define cout fout
int main(){
	ifstream fin;
	ofstream fout;
	fin.open("lineup.in");
	fout.open("lineup.out");

	int n,k;
	cin >> n >> k;
	ii a[n];
	FOR(i,n)cin >> a[i].ff,a[i].ss = i;
	sort(a,a+n);
	int b[n];
	int ptr = 0;
	FOR(i,n){
		if(i > 0 and a[i].ff != a[i-1].ff)ptr++;
		b[a[i].ss] = ptr;
	}
	vi all[n];
	FOR(i,n)all[i].pb(-1);
	FOR(i,n){
		arr[i] = all[b[i]].back();
		all[b[i]].pb(i);
	}
	build(0,0,n);
	int dp[n];
	FOR(i,n){
		int lo = i;
		int hi = n-1;
		int best = i;
		while(lo <= hi){
			int mid = (lo+hi)/2;
			if(query(0,0,n,i,mid,i) <= k+1){
				best = max(best,mid);
				lo = mid+1;
			}else{
				hi = mid-1;
			}
		}
		dp[i] = best;
	}
	int mx = 0;
	FOR(i,n){
		int calc = lower_bound(all[b[i]].begin(), all[b[i]].end(),dp[i]+1)-lower_bound(all[b[i]].begin(), all[b[i]].end(),i) ;
		//FORE(j,i,dp[i]){
		//	calc += b[i]==b[j];
		//}
		mx = max(mx,calc);
	}
	cout << mx << endl;
	return 0;
}