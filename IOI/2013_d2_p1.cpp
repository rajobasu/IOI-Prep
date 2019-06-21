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

#include "cave.h"

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long int
#define vi vector<int>
#define ii pair<int,int>
#define pb push_back
#define mp make_pair
#define vv vector
#define ff first
#define ss second
#define pll pair<ll,ll>
#define cd complex<double> 
#define ld long double
#define pld pair<ld,ld>
#define iii pair<ii,int>

using namespace std;

const int MAXN = 5e3+1;

int n;
/*
int S[4] = {1,1,1,1};
int D[4] = {3,1,0,2};
int tryCombination(int* c){
	int x[4];
	FOR(i,n){
		x[i] = (c[i] == S[i]);
	}
	//bool ok[4];
	if(x[2] == 0)return 0;
	if(x[1] == 0)return 1;
	if(x[3] == 0)return 2;
	if(x[0] == 0)return 3;
	return -1;
}

void answer(int* c,int* d){
	FOR(i,n){
		cout << c[i] << " ";
	}
	cout << endl;
	FOR(i,n)cout << d[i] <<" ";cout << endl;
}
*/

int ans = -1;
int id;
int val;
int cc[MAXN];
int d[MAXN];
int c[MAXN];
void constructC(int low,int high,int setMeans){
	FOR(i,n){
		if(d[i] != -1)c[i] = cc[i];
		else if(low <= i and i <= high){
			c[i] = setMeans;
		}else{
			c[i] = 1-setMeans;
		}
	}
}
void binsrch(int low,int high,int setMeans){
	if(low == high){
		ans = low;
		return;
	}
	int mid = (low+high)/2;
	constructC(low,mid,setMeans);
	int a = tryCombination(c);
	if(a == -1)a = n;
	if(a > id)
		binsrch(low,mid,setMeans);
	else
		binsrch(mid+1,high,setMeans);
}

void exploreCave(int n){
	::n = n;
	FOR(i,n)d[i] = -1;
	//int cc[n];
	FOR(i,n){
		id = i;
		constructC(0,n-1,0);
		ans = -1;
		int a = tryCombination(c);
		if(a == -1)a = n;
		if(a > id){
		//	cout << "CASE 1 : " << id << endl;
			// means door is open
			binsrch(0,n-1,0);

		}else{
			//cout << id << endl;
			binsrch(0,n-1,1);
		}
		//cout << i << " " << ans << endl;
		d[ans] = i;
		cc[ans] = a<=id;
	}
	//FOR(i,n)d[i] = i;
	answer(cc,d);
}
/*
int main(){
	exploreCave(4);
	return 0;
}
*/
