/*
maintain incoming and outgoing edges for all. 
If there is forward and reverse edge between two cliques, then merge them. Note that this may result in further clique mergings that needs to be taken care off. Also take care when updating edge count. 
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

using namespace std;
const int MAXN = 1e5+5;
int D = 0;
int E = 0;
int F = 0;
int G = 0;
struct DSU{
	ll tot = 0;
	int parent[MAXN];
	set<int> allINC[MAXN];
	set<int> allOUT[MAXN];
	map<int,set<int>/*set of all a, a->b*/ > incoming[MAXN];// individual nodes 
	map<int,set<int>/*set of all a, a->b*/ > outgoing[MAXN];
	
	set<int> allNodes[MAXN];
	DSU(){
		FOR(i,MAXN)parent[i] = i;
		FOR(i,MAXN)allNodes[i].insert(i);
	}
	int find(int a){
		if(a != parent[a])parent[a] = find(parent[a]);
		return parent[a];
	}
	bool isSame(int a,int b){
		return find(a) == find(b);
	}
	
	inline void addEdge(int a,int b){
		// pa -> pb
		int pa = find(a);
		int pb = find(b);
		if(pa == pb)return;
		if(incoming[pb][pa].find(a) == incoming[pb][pa].end()){
			//cout << pa << " <--> " << pb << endl;
			allINC[pb].insert(a);
			allOUT[pa].insert(a);
			incoming[pb][pa].insert(a);
			outgoing[pa][pb].insert(a);
			tot += allNodes[pb].size();
			handleEdge(a,b);
		}
	}

	



	void merge(int a,int b){
		int pa = find(a);
		int pb = find(b);
		tot += 2*allNodes[pa].size()*allNodes[pb].size(); // new internal edges of the clique.
		if(allNodes[pa].size() < allNodes[pb].size())swap(pa,pb);
		tot -= incoming[pa][pb].size()*allNodes[pa].size();
		tot -= incoming[pb][pa].size()*allNodes[pb].size();

		// we are going to make pa the parent of pb;
		// lets iterate over everything of pb
		vi all;
		for(auto e: outgoing[pb]){
			if(find(e.ff) == pa)continue;
			if(find(e.ff) != e.ff)continue;
			all.pb(e.ff);
			for(auto x: e.ss)outgoing[pa][e.ff].insert(x);
			for(auto x: incoming[e.ff][pb]){
				allINC[e.ff].insert(x);
				incoming[e.ff][pa].insert(x);
			}
		}
		
		for(auto x: incoming[pa][pb])allINC[pa].erase(x);

		int cnt = allINC[pa].size();

		for(auto e: incoming[pb]){
			if(find(e.ff) == pa)continue;
			if(find(e.ff) != e.ff)continue;
			all.pb(e.ff);
			for(auto x: e.ss){
				// means x->pb exists; also x lies in component of e.ff
				// check if x->pa exists or not
				
				if(incoming[pa][e.ff].find(x) != incoming[pa][e.ff].end()){
					// means it is there:
					// then no need to do anything bleh
					cnt--;
				}else{
					// we need to add it there. 
					allINC[pa].insert(x);
					outgoing[e.ff][pa].insert(x);
					incoming[pa][e.ff].insert(x);
					
					tot += allNodes[pa].size();
				}
			}
		}
		
		tot += cnt*allNodes[pb].size();

		for(auto x : allNodes[pb])allNodes[pa].insert(x);
		parent[pb] = pa;
		for(auto e : all)handleEdge(e,pa);
	}


	bool check(int a,int b){
		int pa = find(a);
		int pb = find(b);
		return pa!=pb and !incoming[pa][pb].empty() and !incoming[pb][pa].empty();
	}

	void handleEdge(int a,int b){
		//cout <<a << " " << b << endl;
		if(isSame(a,b))return;
		
		if(!check(a,b))return;
		merge(a,b);
	}
};	

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	int n,m;
	cin >> n >> m;
	DSU dsu;
	FOR(i,m){
		int a,b;
		cin >> a >> b;
		a--;b--;
		dsu.addEdge(a,b);
		cout << dsu.tot << endl;
	}
	return 0;
}