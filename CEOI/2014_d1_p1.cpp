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
#include <fstream>

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long int
#define vi vector<int>
#define v vector
#define ii pair<ll,ll>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define pll pair<ll,ll>
#define cd complex<double> 
#define iil pair<ii,ll>

const ll INF = 4e15;
using namespace std;
const int MAXN = 151;

int n;

int grid[MAXN][MAXN];
int color[MAXN];
inline int countcolor(int lo,int hi){
	set<int> st;
	FORE(i,lo,hi){
		st.insert(color[i]);
	}
	return st.size();
}
inline int interact(int lo,int hi,int nd){
	cout << (hi-lo+1)+1 << " ";
	FORE(i,lo,hi){
		cout << i+1 << " ";
	}
	cout << nd+1 << endl;
	int x;
	cin >> x;
	return x;
}

int binsrch(int lo,int hi,int nd){
	if(lo == hi){
		int cc = interact(lo,hi,nd);
		if(cc == 1){
			return lo;	
		}else{
			return -1;
		}
	}
	int mid = (lo+hi)/2;
	int pcolor = countcolor(lo,mid);
	int ncolor = interact(lo,mid,nd);
	if(ncolor == pcolor){
		return binsrch(lo,mid,nd);
	}else{
		return binsrch(mid+1,hi,nd);
	}
}

int main(){
	cin >> n;
	int ptr = 1;
	FOR(i,n){
		if(i == 0){
			color[i] = ptr++;
		}else{
			int x = binsrch(0,i-1,i);
			if(x == -1){
				color[i] = ptr++;
			}else{
				color[i] = color[x];
			}
		}
	}	
	cout << 0 << " ";
	FOR(i,n)cout << color[i] << " ";cout << endl;


	return 0;
}