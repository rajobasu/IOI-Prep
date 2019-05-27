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
//#define mp make_pair
#define ff first
#define ss second
#define pll pair<ll,ll>
#define cd complex<double> 
#define ld long double
#define pld pair<ld,ld>
#define iii pair<ii,int>

const ld INF = 1e9+10;
using namespace std;
const int MAXN = 1000*100*2+10;
const int MAXVAL = 1e9+10;

const int N = 1000;
int mp[N];
void precalc(){
	int ptr = 0;
	FOR(mask,1<<12){
		int ctr = 0;
		FOR(i,12){
			if((mask&(1<<i))>0)ctr++;
		}
		if(ctr == 6){
			mp[ptr] = mask;
			ptr++;
		}
	}
	cout << ptr << endl;
}

#define endl '\n'
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	precalc();
	//return 0;
	int n,t;
	int typ;
	cin >> typ >> n >> t;
	if(typ == 1){
		while(t--){
			int a,b;
			cin >> a >> b;
			int ptr = 0;
			while(1){
				if((mp[a]&(1<<ptr))>0){
					if((mp[b]&(1<<ptr)) == 0){
						break;
					}
				}
				ptr++;
			}
			cout << ptr+1 << endl;
		}
	}else{
		while(t--){
			int q,h;
			cin >> q >> h;
			h--;
			if(mp[q]&(1<<h)){
				cout << "yes" << endl;
			}else{
				cout << "no" << endl;
			}
		}
	}

	return 0;
}