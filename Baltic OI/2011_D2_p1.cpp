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

const ll INF = 4e18;
using namespace std;
const int MAXN = 50005;

int main(){
	ll n;
	cin >> n >> p >> k;
	ll mn = n*p+k;
	//FOR(i,MAXN)dp[i] = -1;
	FORE(i,2,100){
		ll x = (ll)floor(pow(n,1.0/i));
		ll sum = 0;
		ll y = x;
		FOR(j,i){
			if(y*pow(x+1,i-j-1)>=n){
				sum += x;
				y *= x;
			}else{
				FORE(l,j,i-1)sum += x+1;
				break;
			}
		}
		mn = min(mn,i*k + sum*p);
	}
	cout << mn << endl;
	return 0;
}