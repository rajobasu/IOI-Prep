/*
Edges are when (a,b) a loves b or b loves a or both same color. Find each edge by binsrch.
degree can be 1 or 3 for a vertex. if 1, then color same. if 3, then we can find which vertex it loves by taking groups of 2 out of 3 neighbours at a time. 
*/

#include <stdio.h>     
#include <stdlib.h>    
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
#define ld long double
//#define int short
#define vi vector<int>
#define pb push_back
#define ff first
#define ss second
#define ii pair<int,int>
#define iii pair<int,ii>
#define pll pair<ll,ll>
#define plll pair<ll,pll>
#define mp make_pair
#define vv vector
#define endl '\n'

#include "chameleon.h"

using namespace std;

bool query(vi all, int extra){
	all.pb(extra);
	//for(auto e: all)cout << e << " ";cout << endl;
	return Query(all) == all.size();
}

int count(vi all, int extra){
	all.pb(extra);
	return ((int)all.size()) - Query(all);
}
int query3(int a,int b,int c){
	vi all;all.pb(a);all.pb(b);all.pb(c);
	return Query(all);
}

vi res;
bool ok = 1;
vi edges[1002];
int llst = 0;
void binsrch(vi allNum,int x){
	if(edges[x].size() >= 3)return;

	if(allNum.size() == 1){
		//cout << allNum[0] << " " << x << endl;
		edges[allNum[0]].pb(x);
		edges[x].pb(allNum[0]);
		llst = allNum[0];
		return;
	}
	//cout << allNum.size() << endl;;
	vi halves[2];
	//FOR(i,allNum.size())halves[i%2].pb(allNum[i]);
	int n = allNum.size();
	FOR(i,n/2)halves[0].pb(allNum[i]);
	FORE(i,n/2,n-1)halves[1].pb(allNum[i]);

	if(query(halves[0],x)){
		binsrch(halves[1],x);
	}else{
		binsrch(halves[0],x);
		//if(edges[x].size() < 3 and !query(halves[1],x))binsrch(halves[1],x);
	}
}
vi indsets[4];

void Solve(int n){
	n*=2;
	indsets[0].pb(1);
	FORE(i,2,n){
		FOR(j,4){
			if(indsets[j].empty() or query(indsets[j],i)){
				indsets[j].pb(i);
				break;
			}
		}
	}
	// everything has been partitioned.
	
	FOR(i,4){
		for(auto e : indsets[i]){
			//cout << "ATTACK: " << e << endl;
			FOR(j,i){
				if(i != j and !indsets[j].empty()){
					llst = -2;
					while(llst != -1 and edges[e].size() < 3){
						// one more edge might be found
						vi rdlst;
						for(auto x:indsets[j])if(x > llst)rdlst.pb(x);
						llst = -1;
						if(!rdlst.empty() and !query(rdlst,e))binsrch(rdlst,e);
					}

					/*
					ok = 1;
					if(query(indsets[j],e))continue;
					vi rdlst;
					for(auto x:indsets[j])if(x < e)rdlst.pb(x);
					if(rdlst.size() == 0)continue;
					binsrch(rdlst,e);
					*/
				}
			}
		}
	}
	
	FORE(i,1,n){
	//	cout << edges[i].size() << endl;
	}
	set<int> allSets[n+1];
	FOR(i,n+1)for(auto x:edges[i])allSets[i].insert(x);
	FORE(i,1,n){

		if(edges[i].size() == 1){
			continue;
		}
		//if(edges[i].size() != 3)while(1);
		// has 3 edges;
		int a = query3(i,edges[i][0],edges[i][1]);
		int b = query3(i,edges[i][1],edges[i][2]);
		int numTorem;
		if(a == 1){
			numTorem = edges[i][2];
		}else if(b == 1){
			numTorem = edges[i][0];
		}else{
			numTorem = edges[i][1];
		}
		allSets[i].erase(numTorem);
		allSets[numTorem].erase(i);
	}
	FORE(i,1,n){
		int x = *(allSets[i].begin());
		if(i < x)Answer(i,x);
	}
}
