/*
sort by first element. lets say we want ith item to be beginning point. end point will be
the kth largest value for all endpoints alredy visited. We can just maintain the top k choices
everytime greedily. hence kth largest is just the smallest in our set. 
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
#include <map>


#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long int
#define ld long double
#define vi vector<ll>
#define pb push_back
#define ff first
#define ss second
#define ii pair<int,int>
#define iii pair<ii,int>
#define vv vector

using namespace std;

const int MAXN = 200*1000+5;
const int MAXA = 202;
#define endl '\n'

vi g[MAXN];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,k;
	cin >> n >> k;

	iii arr[n];
	FOR(i,n)cin >> arr[i].ff.ff >> arr[i].ff.ss,arr[i].ss = i;
	sort(arr,arr+n);

	int a,b; a =1; b = 0;
	multiset<int> s;
	FOR(i,n){
		//cout << "ELEMENT INSERTED : " << arr[i].ff.ss << endl;
		s.insert(arr[i].ff.ss);
		//cout << s.size() << endl;

		while(s.size() > k){
		//	cout << "ELEMENT ERASED : " << *(s.begin()) << endl;
			s.erase(s.begin());
		}
		int nw = *(s.begin());
		//cout << arr[i].ff.ff << " " << nw << endl;
		if(s.size() >= k and nw - arr[i].ff.ff > b -a and nw > arr[i].ff.ff){
			b = nw;
			a = arr[i].ff.ff;
		}
	}






	//cout << b << " " << a << endl;
	vi lst;

	FOR(i,n){
		if(arr[i].ff.ff <= a and b <= arr[i].ff.ss){
			lst.pb(arr[i].ss);
			k--;
		}
		if(k == 0)break;
	}
	cout << b-a << endl;
	sort(lst.begin(), lst.end());
	for(auto e : lst)cout << e+1 << " ";cout << endl;

	return 0;
}