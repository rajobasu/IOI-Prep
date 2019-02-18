/**
SOLUTION : process for each segment and then combine the dp
COMPLEXITY : nlogn
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

ii points[MAXN];

inline ll dist(ii a,ii b){
	return abs(a.ff-b.ff) + abs(a.ss-b.ss);
}

ii vals[4*MAXN];//{no skips used, skips used} , border elements not considered to skip
void update(int node,int ss,int se,int i){
	if(ss > i or se < i){
		return;
	}
	if(ss == se){
		vals[node].ff = 0;
		vals[node].ss = 0;
		return;
	}
	int mid = (ss+se)/2;
	update(node*2+1,ss,mid,i);
	update(node*2+2,mid+1,se,i);

	ll dd = dist(points[mid],points[mid+1]);
	vals[node].ff = vals[node*2+1].ff + vals[node*2+2].ff + dd;
	vals[node].ss = min(vals[node*2+1].ff + vals[node*2+2].ss,vals[node*2+1].ss + vals[node*2+2].ff) + dd;
	// check if border elements can be skipped
	if(mid > ss){
		vals[node].ss = min(vals[node].ss, vals[node*2+1].ff + vals[node*2+2].ff + dist(points[mid-1],points[mid+1]) - dist(points[mid-1],points[mid]));
	}
	if(mid+1 < se){
		vals[node].ss = min(vals[node].ss, vals[node*2+1].ff + vals[node*2+2].ff + dist(points[mid],points[mid+2]) - dist(points[mid+2],points[mid+1]));
	}
}
ii get(int node,int ss,int se,int l,int r){
	if(l > se or r < ss)return {-1,-1};
	if(l <= ss and se <= r)return vals[node];
	int mid = (ss+se)/2;
	ii left = get(node*2+1,ss,mid,l,r);
	ii right = get(node*2+2,mid+1,se,l,r);
	
	ii res;
	if(left.ff == -1)return right;
	if(right.ff == -1)return left;

	ll dd = dist(points[mid],points[mid+1]);
	res.ff = left.ff + right.ff + dd;
	res.ss = min(left.ff + right.ss,left.ss + right.ff) + dd;
	// check if border elements can be skipped
	// cout << l << ":" << r << " <> " << ss << ":" << se << ":" << mid <<  " <> " << res.ff << ":" << res.ss << endl;
	// cout << "LEFT  : " << left.ff << ":" << left.ss << endl;
	// cout << "RIGHT : " << right.ff << ":" << right.ss << endl;

	if(mid > l){
		res.ss = min(res.ss, left.ff + right.ff + dist(points[mid-1],points[mid+1]) - dist(points[mid-1],points[mid]));
	}
	if(mid+1 < r){
		res.ss = min(res.ss, left.ff + right.ff + dist(points[mid],points[mid+2]) - dist(points[mid+2],points[mid+1]));
	}
	// cout << l << ":" << r << " <> " << ss << ":" << se << ":" << mid <<  " <> " << res.ff << ":" << res.ss << endl;
	
	return res;
}




#define cout fout
#define cin fin

int main(){
	ifstream fin;
	ofstream fout;
	fin.open("marathon.in");
	fout.open("marathon.out");

	int n,q;
	cin >> n >> q;
	FOR(i,n){
		cin >> points[i].ff >> points[i].ss;
	}

	FOR(i,n)update(0,0,MAXN,i);
	FOR(i,q){
		char v;cin >> v;
		if(v == 'Q'){
			int l,r;
			cin >> l >> r;l--;r--;
			ii res = get(0,0,MAXN,l,r);
			if(res.ff == -1)cout << res.ss << endl;
			else if(res.ss == -1)cout << res.ff << endl;
			else cout << min(res.ff , res.ss) << endl;
		}else{
			int a,b,c;
			cin >> a >> b >> c;
			a--;
			points[a] = {b,c};
			update(0,0,MAXN,a);
		}
	}


	return 0;
}