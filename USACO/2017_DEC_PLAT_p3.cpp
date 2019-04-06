/*
SOLUTION: binsrch + greedy.
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
const int MAXN = 500*500+1;

/*
*/
#define cin fin
#define cout fout
/*
*/

bool check(int* arr,int k){
	int arr2[k];FOR(i,k)arr2[i] = arr[i];
	sort(arr2,arr2+k);
	int mx = 0;
	FOR(i,k){
		mx = max(mx,arr2[i]);
		if(mx <= i)return true;
	}
	return false;
}


int main(){
	ifstream fin;
	ofstream fout;
	/*
	*/
	fin.open("greedy.in");
	fout.open("greedy.out");
	/*
	*/

	int n;
	cin >> n;
	int arr[n];
	FOR(i,n)cin >> arr[i];
	FOR(i,n)arr[i] = n -1- arr[i];
	int mx = -1;
	int best = n;
	int low = 0;
	int hi = n-1;
	while(low <= hi){
		int i = (low+hi)/2;
		bool b = 0;
		if(low == hi)b=1;
		if(check(arr,i+1)){
			best = min(best,i);
			//cout << n-i-1 << endl;
			//return 0;
			hi = i-1;
		}else{
			low = i+1;
		}
		if(b)break;
		
	}
	cout << n-1- best << endl;
	//while(1);
	
	return 0;
}
