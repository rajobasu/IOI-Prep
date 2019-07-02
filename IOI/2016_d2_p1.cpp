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

const int MAXN = 200*1000 + 10;
const int MAXK = 100+10;


int psumw[MAXN];
int psumb[MAXN];
bool pref[MAXK][MAXN];
bool suf[MAXK][MAXN];
bool posW[MAXN];
bool posB[MAXN];
vi pos[MAXK];
int n;
inline int nw(int l,int r){
	r = min(r,n-1);
	if(l <= 0)return psumw[r];
	return psumw[r] - psumw[l-1];
}
inline int nb(int l,int r){
	r = min(r,n-1);
	if(l <= 0)return psumb[r];
	return psumb[r] - psumb[l-1];
}

string solve_puzzle(string s,vi c){
	n = s.length();
	int k = c.size();

	psumw[0] = s[0]=='_';
	FORE(i,1,n-1){
		psumw[i] = psumw[i-1] + (s[i]=='_');
	}

	psumb[0] = s[0] == 'X';
	FORE(i,1,n-1){
		psumb[i] = psumb[i-1] + (s[i] == 'X');
	}
	// we calculate the prefix dp
	bool d = 0;
	FOR(i,k+1){
		FOR(j,n){
			if(i == 0){
				pref[i][j] = (nb(0,j) == 0);
				continue;
			}
			
			bool a = (j>0)?pref[i][j-1]:0;
			bool b = 0;

			if(j < c[i-1]-1){
				b = 0;
			}else if(j == c[i-1]-1){
				b = (i == 1)  and (j == n-1 or s[j+1] != 'X');
			}else if(j == c[i-1]){
				b = (i == 1) and (s[j-c[i-1]] != 'X'  and (j == n-1 or s[j+1] != 'X'));
			}else{
				b = pref[i-1][j-c[i-1]-1] and (s[j-c[i-1]] != 'X' and (j == n-1 or s[j+1] != 'X'));
			}
			if(nw(j-c[i-1]+1,j) > 0)b = 0;
			if(d)cout << i << " " << j << " " <<  b << endl;
			if(s[j] == '_'){
				pref[i][j] = a;
			}else if(s[j] == 'X'){
				if(b)pos[i-1].pb(j);
				pref[i][j] = b;
			}else{
				if(b)pos[i-1].pb(j);
				pref[i][j] = a|b;
			}
		}

	}
	if(d){
	FOR(i,n){
		cout << i << " : ";
		FOR(j,k+1){
			cout << pref[j][i];
		}
		cout << endl;
	}
	}
	// we calculate the suffix dp
	reverse(c.begin(), c.end());
	FOR(i,k+1){
		for(int j = n-1;j>=0;j--){
			if(i == 0){
				suf[i][j] = nb(j,n-1) == 0;
				continue;
			}
			
			bool a = (j<n-1)?suf[i][j+1]:0;
			bool b = 0;

			if(j > n-c[i-1]){
				b = 0;
			}else if(j == n-c[i-1]){
				b = (i == 1) and (j == 0 or s[j-1] != 'X');
			}else if(j+1 == n-c[i-1]){
				b = (i == 1) and (s[j+c[i-1]] != 'X' and (j == 0 or s[j-1] != 'X'));
			} else{
				b = suf[i-1][j+c[i-1]+1] and (s[j+c[i-1]] != 'X' and (j == 0 or s[j-1] != 'X'));
			}
			if(nw(j,j+c[i-1]-1) > 0)b = 0;
			if(s[j] == '_'){
				suf[i][j] = a;
			}else if(s[j] == 'X'){
				suf[i][j] = b;
			}else{
				suf[i][j] = a|b;
			}
		}
	}
	if(d){
	cout << endl;
	FOR(i,n){
		cout << i << " : ";
		FOR(j,k+1){
			cout << suf[j][i];
		}
		cout << endl;
	}
	}	
	// find all the possible locations for being white
	FOR(i,n){
		if(s[i] == '_'){
			posW[i] = 1;
			continue;
		}else if(s[i] == 'X')continue;
		FORE(j,0,k){ // number of books that will be to the left of i
			bool a,b;a=b=0;
			if(i == 0)a = j==0;
			else a = pref[j][i-1];
			if(i == n-1)b = j==k; 
			else b = suf[k-j][i+1];

			
			posW[i] |= a&b;
		}
	}
	// find all the possible locations for being black
	reverse(c.begin(), c.end());
	FOR(j,k){
		int lo = MAXN;
		int hi = 0;
		for(auto e : pos[j]){
			if(e+2 > n-1 and j < k-1)continue;
			if(e+2 <= n-1 and !suf[k-j-1][e+2])continue;
			if(d)cout << j << " " << e << endl;
			FORE(x,e-c[j]+1,e)posB[x] = 1;
		}
	}
	if(d){FOR(i,n)cout << posB[i];cout << endl;}
	if(d){FOR(i,n)cout << posW[i];cout << endl;}
	string ss;
	FOR(i,n){
		if(posB[i] and posW[i])ss += "?";
		else if(posW[i])ss += "_";
		else ss+="X";
	}
	return ss;
}

int ma1in(){
	int n = 13;
	int k = 4;
	vi c = {};
	string s = "........";
	s = solve_puzzle(s,c);
	cout << s << endl;
	return 0;
}