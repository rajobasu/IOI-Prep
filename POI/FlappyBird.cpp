/*
SOLUTION: Find min allowed by going from right to left. and then traverse left to right and try
going to minimum position possible position always. 

*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <deque>
#include <iomanip>
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
#define vi vector<int>
#define pb push_back
#define ff first
#define ss second
#define ii pair<int,int>
#define iii pair<int,ii>
#define pll pair<ll,ll>
#define plll pair<ll,pll>
#define vv vector
#define endl '\n'

using namespace std;

const int MAXN = 200*1000 + 5;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n,m;
	cin >> n >> m;
	plll arr[n+1];
	FOR(i,n)cin >> arr[i].ff >> arr[i].ss.ff >> arr[i].ss.ss;

	arr[n] = {0LL,{0LL,0LL}};
	sort(arr,arr+n+1,greater<plll>());
	FOR(i,n){
		if((arr[i].ss.ff+arr[i].ff)%2 == 0){
			arr[i].ss.ff+=2;
		}else arr[i].ss.ff++;
		
		if((arr[i].ss.ss+arr[i].ff)%2 == 0){
			arr[i].ss.ss-=2;
		}else arr[i].ss.ss--;

	//	if(arr[i].ss.ss%2 == 0)arr[i].ss.ss-=2;else arr[i].ss.ss--;
		if(arr[i].ss.ff > arr[i].ss.ss){
			cout << "NIE" << endl;
			return 0;
		}
	}

	ll minAllowed[n+1];
	FOR(i,n+1){

		if(i == 0){
			minAllowed[i] = arr[i].ss.ff;
			continue;
		}
		
		ll dist = abs(arr[i-1].ff-arr[i].ff);
		minAllowed[i] = max(arr[i].ss.ff,minAllowed[i-1] - dist);	
	
		if(minAllowed[i] > arr[i].ss.ss or minAllowed[i] - dist > arr[i-1].ss.ss){
			cout << "NIE" << endl;
			return 0;
 		}
	}
	ll tot = 0;
	reverse(arr,arr+n+1);
	reverse(minAllowed,minAllowed + n+1);
	//FOR(i,n+1)cout << minAllowed[i] <<" ";cout << endl;
	ll curr = 0;
	FOR(i,n+1){
		if(i>0){
			ll dist = abs(arr[i-1].ff-arr[i].ff);
			ll nextGo = max(minAllowed[i],curr - dist);
			tot += (nextGo - (curr-dist))/2;
			curr = nextGo;
		}
	}
	cout << tot << endl;


	return 0;
}