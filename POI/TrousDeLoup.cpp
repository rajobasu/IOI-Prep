/*
2 ptr, while using a deque to maintain largest contiguous region within the 2 ptr zone.
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

const int MAXN = 20*100*1000+5;//0*1000+5;
const ll MOD = 1e9 + 7;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);


	int n,d;
	ll p;
	cin >> n >> p >> d;


	int arr[n];
	FOR(i,n)cin >> arr[i];

	int largest = d;
	int ptr = 0;
	ll b[n];
	ll sum_phase1 = 0;
	FOR(i,d)sum_phase1 += arr[i];
	b[0] = sum_phase1;
	for(int i = d;i<n;i++){
		sum_phase1 += arr[i];
		sum_phase1 -= arr[i-d];
		b[i-d+1] = sum_phase1;
	}
	b[n-1] = arr[n-1];
	for(int i = n-2;i > n-d;i--){
		b[i] = arr[i] + b[i+1];
	}
	//FOR(i,n)cout << b[i] << " ";cout << endl;
	ll sum = 0;
	deque<pair<ll,int> > dq;
	FOR(i,n){
		while(!dq.empty() and dq.front().ss < i)dq.pop_front();
		while(ptr < n){
			ll bestCancel = 0;
			if(ptr >= i + d - 1){
				auto e = make_pair(b[ptr-d+1],ptr-d+1);
				// add element to the deque
				while(!dq.empty() and dq.back() < e)dq.pop_back();
				dq.push_back(e);
			}

			//FORE(j,i,ptr-d+1)bestCancel = max(bestCancel,b[j]);
			// adding element done.
			if(!dq.empty())bestCancel = dq.front().ff;
			if(sum + arr[ptr] - bestCancel <= p or i+d > ptr){
				//cout << i << " " << sum << " " << bestCancel << " " << ptr << endl;
				sum += arr[ptr];
				ptr++;
				
				largest = max(largest,ptr-i);
			}else{
				//cout << i << " " << sum << " " << bestCancel << " " << ptr << " FAILED" << endl;
				
				break;
			}
		}
		sum -= arr[i];
		
	}
	cout << largest << endl;


	return 0;
}