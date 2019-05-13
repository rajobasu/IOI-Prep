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

const int INF = 1e9;
using namespace std;

int main(){
	int n;
	cin >> n;
	int arr[n];
	FOR(i,n)cin >> arr[i];
	ll ctr = 0;
	sort(arr,arr+n);
	FOR(i,n){
		int ind = lower_bound(arr,arr+n,ceil(0.9*arr[i]))-arr;
		ctr += i - ind;
	}
	cout << ctr << endl;
	return 0;
}