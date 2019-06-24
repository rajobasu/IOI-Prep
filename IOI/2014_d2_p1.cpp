#include <bits/stdc++.h>

#define ll long long int
#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i = a;i<=b;i++)
#define vi vector<int>
#define ii pair<int,int>
#define ff first
#define pb push_back
#define ss second

#include "gondola.h"

using namespace std;

const int INF = 1e7;
const int MAXV = 250000+10;
const ll MOD = 1e9 + 9;

int f[MAXV];


ll fxp(ll a,ll b){
	if(b == 0)return 1;
	if(b%2 == 0){
		ll x =  fxp(a,b/2);
		return (x*x)%MOD;
	}else{
		return (a*fxp(a,b-1))%MOD;
	}
}

int findMinIndex(int n,int s[]){
	int mn = INF;
	int ind = 0;
	FOR(i,n){
		if(s[i] < mn){
			mn = s[i];
			ind = i;
		}
	}
	return ind;
}

int findMax(int n,int s[]){
	int mx = 0;
	FOR(i,n)mx = max(mx,s[i]);
	return mx;
}

int valid(int n, int inputSeq[]){
	int arr[n];
	int ind = findMinIndex(n,inputSeq);

	FOR(i,n){
		arr[(ind + i)%n] = i+1;
	}
	bool b = 1;
	FOR(i,n){
		b &= (arr[i]==inputSeq[i]);
	}
	return b;
}

bool isRelaxedValid(int n,int s[]){
	int ind = findMinIndex(n,s);
	if(s[ind] > n)return 1;
	int arr[n];
	FOR(i,n){
		arr[(ind+i)%n] = (s[ind] + i - 1)%n + 1; 
	}
	FOR(i,n){
		if(s[i] > n)continue;
		if(arr[i] != s[i])return 0;
	}
	return 1;
}

int replacement(int n, int gondolaSeq[], int replacementSeq[]){
	int arr[n];
	int ind = findMinIndex(n,gondolaSeq);
	set<int> st;
	FOR(i,n)f[gondolaSeq[i]]++;
	if(gondolaSeq[ind] <= n){
		FOR(i,n){
			arr[(ind + i)%n] = (gondolaSeq[ind]+i-1)%n+1;
		}
		FOR(i,n){
			if(arr[i] != gondolaSeq[i])st.insert(arr[i]);
		}
	}else{
	//	while(1);
		FOR(i,n)arr[i] = i+1;
		FOR(i,n)st.insert(i+1);
	}

	vector<ii> all;
	FOR(i,n){
		if(gondolaSeq[i] > n)all.pb({gondolaSeq[i],i});
	}
	sort(all.begin(), all.end());
	int last = n;
	int ptr = 0;
	for(auto e : all){
		FORE(i,last+1,e.ff){
			replacementSeq[ptr++] = arr[e.ss];
			arr[e.ss] = i;
		}
		last = e.ff;
	}
	
	return ptr;
}
int countReplacement(int n, int inputSeq[]){
	if(!isRelaxedValid(n,inputSeq)){
		return 0;
	}
	if(findMax(n,inputSeq) <= n)return 1;
	int* gondolaSeq = inputSeq;
	vector<ii> all;
	FOR(i,n){
		if(gondolaSeq[i] > n)all.pb({gondolaSeq[i],i});
	}
	sort(all.begin(), all.end());
	int last = n;
	bool b = inputSeq[findMinIndex(n,inputSeq)] > n;
	ll ans = 1;
	//cout <<"d" << endl;
	FOR(i,all.size()){
		ll x = all[i].ff - last - 1;
		ll y = (int)all.size() - i;
		ans *= fxp(y,x);
		ans %= MOD;
		last = all[i].ff;
	}
	if(b){
		ans *= n;
		ans %= MOD;
	}
	if(ans < 0)while(1);
	return ans;
}

int mai1n(){
	int n = 4;
	int g[4] = {1,2,7,6};
	cout << countReplacement(n,g) << endl;; 
	return 0;
	int c[100];
	int x = replacement(n,g,c);
	cout << x << endl;
	FOR(i,x)cout << c[i] << " ";
	cout << endl;
	return 0;
}