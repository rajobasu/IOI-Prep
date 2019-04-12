/*
SOLUTION: just some lowerbounds.
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
#include <unordered_map>
#include <map>
#include <complex>
#include <stack>
#include <set>
#include <fstream>

#define FOR(i,n) for(int i = 0;i < n; i++)
#define FORE(i,a,b) for(int i = a; i <= b ; i++)
#define ss second
#define ff first
#define ll long long int
#define ii pair<int,int>
#define il pair<int,ll>
#define li pair<ll,int>
#define x ff
#define y ss
#define lii pair<ll,pair<int,int> > 
#define piil pair<int ,pair<int,int> > 
#define iii pair<pair<int,int>,int> 
#define vi vector<int>
#define pb push_back
#define mp make_pair
using namespace std;

const int MOD = 1000000009;
const int INF = 1e9;
const int MAXN = 1000*1000+1;

vi pos[2][MAXN];
int arr[MAXN];
int seq1[MAXN];
int seq2[MAXN];
int ans[2][MAXN];
int pre[MAXN];
vi tmp2;

void solve(int n,int* arr,int m,int* seq,int k,int e){
	FOR(i,n)ans[e][i] = n;
	reverse(seq,seq+m);
	for(auto x:pos[e][seq[0]])ans[e][x]=x;//{ans[x] = x;cout << x << " ";}cout << endl;
	FORE(j,1,m-1){
		for(auto x:pos[e][seq[j]]){
			vi::iterator it = lower_bound(pos[e][seq[j-1]].begin(),pos[e][seq[j-1]].end(),x+1);
			if(it == pos[e][seq[j-1]].end()){
				ans[e][x] = n;
			}else{
				ans[e][x] = ans[e][*it];
			}
		}
	}
}


int main(){
	ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n,k;
    cin >> n >> k;

    FOR(i,n)cin >> arr[i];
	FOR(i,n)arr[i]--;
    
    FOR(i,n)pos[0][arr[i]].pb(i);
	//FOR(i,n)cout << pre[i] << " ";cout << endl;
	reverse(arr,arr+n);
	FOR(i,n)pos[1][arr[i]].pb(i);
	reverse(arr,arr+n);
    int m,l;
    cin >> m >> l;
    FOR(i,m)cin >> seq1[i];
    FOR(i,m)seq1[i]--;
    solve(n,arr,m,seq1,k,0);
    FOR(i,l)cin >> seq2[i];
    FOR(i,l)seq2[i]--;
    reverse(arr,arr+n);
    solve(n,arr,l,seq2,k,1);
    reverse(arr,arr+n);
	int sp = seq1[0];
	pre[0] = arr[0]==sp;
	FORE(i,1,n-1){
		pre[i] = pre[i-1] + (arr[i] == sp);
	}

	int best = 0;
	reverse(seq1,seq1+m);
	reverse(seq2,seq2+l);
	int lw = n;
	int hi = -1;
	FOR(color,k){
		if(pos[0][color].size() < 2)continue;
		int mn = pos[0][color].front();
		int mx = pos[1][color].front();

		int ind1,ind2;

		auto it = lower_bound(pos[0][seq1[0]].begin(),pos[0][seq1[0]].end(),mn+1);
		if(it == pos[0][seq1[0]].end()){
			ind1 = n;
		}else{
			ind1 = ans[0][*it];
		}

		it = lower_bound(pos[1][seq2[0]].begin(),pos[1][seq2[0]].end(),mx+1);
		if(it == pos[1][seq2[0]].end()){
			ind2 = n;
		}else{
			ind2 = ans[1][*it];
		}		
		ind2 = n-ind2-1;
		//cout << color << "  " << ind1 << " " << ind2 << endl;
		if(ind1 >= n or ind2 >= n or ind1 > ind2)continue;
		lw = min(lw,ind1);
		hi = max(hi,ind2);
	}

	auto it = lower_bound(pos[0][sp].begin(), pos[0][sp].end() , lw);
		while(it != pos[0][sp].end()){
			if(*it > hi)break;
			tmp2.pb(*it);
			it++;
		}
	
	cout << tmp2.size() << endl;
	for(auto x : tmp2){
		cout << x+1 << " ";
	}
	cout << endl;
    
	return 0;
}
