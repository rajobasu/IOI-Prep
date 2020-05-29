/*
Simple NTT
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <deque>
#include <iomanip>
#include <list>
#include <cmath>
#include <set>
#include <stack>
#include <map>
#include <unordered_map>

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long 
//#define int long long
#define ld long double
#define vi vector<ll>
#define pb push_back
#define ff first
#define ss second
#define ii pair<int,int>
#define iii pair<int,ii>
#define il pair<ll,ll>
#define vv vector
#define endl '\n'

using namespace std;

const int MAXN = 200*100*10 + 5;
const ll INF = 1e15;

ll n;
ll m;

ll* calc(ll* poly, ll n, ll q){
	ll* arr = new ll[n];
	if(n == 1){
		arr[0] = poly[0]%m;
		return arr;
	}
	ll* a = new ll[n/2];
	ll* b = new ll[n/2];
	FOR(i,n){
		if(i%2 == 0){
			a[i/2] = poly[i]%m;
		}else{
			b[i/2] = poly[i]%m;
		}
	}
	ll* A = calc(a,n/2,(q*q)%m);
	ll* B = calc(b,n/2,(q*q)%m);
	ll qq = 1;
	FOR(i,n){
		arr[i] = A[i%(n/2)] + qq*B[i%(n/2)];
		qq *= q;
		qq %= m;
		arr[i] %= m;
	}
	delete[] A;
	delete[] B;
	delete[] a;
	delete[] b;
	//cout << "SOME OUTPUT: " << q << endl;
	//FOR(i,n)cout << poly[i] << " ";cout << endl;
	//FOR(i,n)cout << arr[i] << " ";cout << endl;
	return arr;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,q;
	cin >> n >> m >> q;
	ll arr[n];
	FOR(i,n)cin >> arr[i];
	ll* res = calc(arr,n,q);
	ll sum = 0;
	FOR(i,n)sum += res[i];
	sum %= m;
	cout << sum << endl;
	FOR(i,n)cout << res[(i+1)%n]%m << " ";cout << endl;
	return 0;
}