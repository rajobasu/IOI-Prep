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
#define vv vector

using namespace std;

const int MAXN = 250*1000+10;
int arr[MAXN];
int n;

struct SegTrMax{
	int st[4*MAXN];
	void update(int node,int ss,int se,int i,int val){
		if(i > se or i < ss)return;
		if(ss == se){
			st[node] = val;
			return;
		}
		int mid = (ss+se)/2;
		update(node*2+1,ss,mid,i,val);
		update(node*2+2,mid+1,se,i,val);
		st[node] = max(st[node*2+1],st[node*2+2]);
	}
	inline int get(int node,int ss,int se,int l,int r){
		if(l > se or r < ss)return 0;
		if(l <= ss and se <= r)return st[node];
		int mid = (ss+se)/2;
		return max(get(node*2+1,ss,mid,l,r),get(node*2+2,mid+1,se,l,r));
	}
	inline int getL(int node,int ss,int se,int r,int mx){
		if(st[node] < mx)return -1;
		if(ss > r){
			return -1;
		}
		if(ss==se)return ss;
		int mid = (ss+se)/2;
		int x = getL(node*2+2,mid+1,se,r,mx);
		if(x == -1)return getL(node*2+1,ss,mid,r,mx);
		return x;
	}
	inline int getR(int node,int ss,int se,int l,int mx){
		if(st[node] < mx)return n;

		if(se < l){
			return n;
		}
		//cout << ss << " " << se << " " << st[node] << endl;
		if(ss==se)return ss;
		int mid = (ss+se)/2;
		int x = getR(node*2+1,ss,mid,l,mx);
		if(x == n)return getR(node*2+2,mid+1,se,l,mx);
		return x;
	}
};	
set<pair<ll,int>,greater<pair<ll,int> > > st;
#define endl '\n'
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int a;
	cin >> n >> a;
	a--;
	SegTrMax stm;
	FOR(i,n){
		cin >> arr[i];
		stm.update(0,0,MAXN,i,arr[i]);
		st.insert({arr[i],i});
	}
	int q;
	cin >> q;
	while(q--){
		/*
		FOR(i,n)cout << arr[i] << " ";cout << endl;
		for(auto e : st)cout << e.ss+1 << " ";cout << endl;
		cout << endl;*/
		char c;
		cin >> c;
		if(c == 'E'){
			int i,e;
			cin >> i >> e;
			i--;
			st.erase({arr[i],i});
			if(e == 1){
				st.insert({(*st.begin()).ff+1,i});

				arr[i] = (*st.begin()).ff;
				stm.update(0,0,MAXN,i,arr[i]);
				continue;	
			}
			vector<pair<ll,int> > v;
			FOR(i,e-1){
				v.pb(*st.begin());
				st.erase(*st.begin());
			}
			//cout << "got till here" << endl;
			st.insert({v.back().ff,i});
			arr[i] = v.back().ff;
			stm.update(0,0,MAXN,i,arr[i]);
			for(auto e: v){
				st.insert({e.ff+1,e.ss});
				arr[e.ss] = e.ff+1;
				stm.update(0,0,MAXN,e.ss,arr[e.ss]);
			}
		}else{
			int b;
			cin >> b;
			b--;
			if(b == a)cout << 0 << endl;
			else if(b < a){
				int mx = stm.get(0,0,MAXN,b,a-1);
				int c = stm.getR(0,0,MAXN,a+1,mx);
				cout << c - b - 1 << endl;
			}else{
				int mx = stm.get(0,0,MAXN,a+1,b);
				int c = stm.getL(0,0,MAXN,a-1,mx);
				cout << b - c - 1 << endl;
			}
		}
	}
	return 0;
}