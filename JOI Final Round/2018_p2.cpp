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
#define vv vector
#define ff first
#define ss second
#define pll pair<ll,ll>
#define cd complex<double> 
#define ld long double
#define pld pair<ld,ld>
#define iii pair<ii,int>

using namespace std;

const int INF = 1e9;
const int MAXN = 400+5;
const int MAXK = 100+10;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	vv<pll> all;
	FOR(i,n){
		ll a,b;
		cin >> a >> b;
		all.pb({a,b});
	}
	sort(all.begin(), all.end());
	vv<ll> pref;
	for(auto e : all){
		if(pref.empty())pref.pb(e.ss);
		else pref.pb(pref.back() + e.ss);
	}
	set<ll> st;

	ll mx = -1e18;
	for(auto e : all)mx = max(mx,e.ss);
	int ptr = -1;
	for(auto e : all){
		st.insert(((ptr > -1)?pref[ptr]:0) - e.ff);
		mx = max(mx,pref[++ptr] - e.ff - (*st.begin()));
		
	}
	cout << mx << endl;
	return 0;
}