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

#define FOR(i,n) for(int i = 0;i < n; i++)
#define FORE(i,a,b) for(int i = a; i <= b ; i++)
#define ss second
#define ff first
#define ii pair<int,int>
#define ll long long int
#define piil pair<pair<int,int>,ll> 
#define iii pair<pair<int,int>,int> 
#define vi vector<int>
#define pb push_back

using namespace std;

const ll MOD = 1000000009;

//#define cin fin
//#define cout fout

ll dp[1001][1001][11];
ll a[1001];
ll b[1001];


ll DP(int n,int m,int k){
	if(k == 0){
		return 1;
	}
	if(n < 0 or m < 0)return 0;
	if(dp[n][m][k] != -1)return dp[n][m][k];

	ll ctr = 0;
	FORE(i,0,n){
		FORE(j,0,m){
			if(a[i] > b[j]){
				ctr += DP(i-1,j-1,k-1);
				ctr %= MOD;
			}
		}
	}
	dp[n][m][k] = ctr;
	return ctr;
}


int main(){
	ifstream fin;
	ofstream fout;
	//fin.open("team.in");
	//fout.open("team.out");

	int n,m,k;
	cin >> n >> m >> k;
	
	int nm = min(n,m);
	
	FOR(i,n)cin >> a[i];
	FOR(i,m)cin >> b[i];
	sort(a,a+n,greater<ll>());
	sort(b,b+n,greater<ll>());

	FOR(i,1001)FOR(j,1001)FOR(l,11){
		dp[i][j][l] = 0;
	}
	ll suff = 0;
	ll suffMat[n+1][m+1][2];

	int last[m];
	FOR(i,m)last[i] = -1;

	FOR(i,m){
		FOR(j,n){
			if(a[j] > b[i]){
				last[i] = j;
			}
		}
	}
	//FOR(i,m)cout << last[i] << " ";cout << endl;
	FOR(l,k+1){
		FOR(i,n+1)FOR(j,m+1){suffMat[i][j][0] = suffMat[i][j][1];suffMat[i][j][1] = 0;};

		FOR(i,n){
			//FOR(i,n+1)FOR(j,m+1)suff[i] = 0;
			suff = 0;
			FOR(j,m){
				if(l == 0)dp[i][j][l] = 1;
				else{
					//if(i > 0)dp[i][j][l] += dp[i-1][j][l]            ;
					//if(j > 0)dp[i][j][l] += dp[i][j-1][l]            ;
					//if(i > 0 and j > 0)dp[i][j][l] += dp[i-1][j-1][l];

				 	ll dsuff = suff;
				 	if(l == 1){
				 		dsuff += max(0,min(i,last[j])+1);
				 	}else
				 		if(min(i,last[j]) > 0){
				 		if(j > 0){
				 			dsuff += suffMat[min(i,last[j])-1][j-1][0];// - suffMat[0][j-1][0];
				 		}
				 	}
					/*
					FOR(i2,min(i+1,last[j]+1)){
						if(l-1 == 0)suff += 1;
						else if(i2 == 0 or j == 0){

						}else{
							suff += dp[i2-1][j-1][l-1];
						}
						suff %= MOD;
						
						
					}
					*/
					suff = dsuff;
					suff %= MOD;
					dsuff %= MOD;

					dp[i][j][l] += dsuff;
					dp[i][j][l] %= MOD;
					
				}
				suffMat[i][j][1] = ((i>0)?suffMat[i-1][j][1]:0);// + ((j>0)?suffMat[i][j-1][1]:0) - ((i>0 and j>0)?suffMat[i-1][j-1][1]:0);
				suffMat[i][j][1] += dp[i][j][l];
				suffMat[i][j][1] %= MOD;
			}
		}/*
		cout << endl << endl;
		FOR(i,n){
			FOR(j,m){
				cout << dp[i][j][l]  << " ";
			}
			cout << endl;
		}
		cout << "--------------------" << endl;
		FOR(i,n){
			FOR(j,m){
				cout << suffMat[i][j][1]  << " ";
			}
			cout << endl;
		}
		*/
	}


	ll ans = dp[n-1][m-1][k] % MOD;
	cout << ans << endl;


	return 0;
}