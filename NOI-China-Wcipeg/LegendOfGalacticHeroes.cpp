/*
SOLUTION: we can maintain the lists using, well, a linkedlist. Also note that the distance between two
indexes cant change once merged, hence we process it offline afterwards.
COMPLEXITY: O(nlogn)
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
#include <map>
#include <complex>
#include <stack>
#include <set>
#include <fstream>

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long int
#define vi vector<int>
#define ii pair<int,int>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define pll pair<ll,ll>
#define ld long double

using namespace std;

const int MOD = 1000000007;
const ll INF = 1000000000000000000;
const int MAXN = 30000;

class LinkedList{
	class Node{
		public : 
		Node* next;
		Node* prev;
		int val;
		Node(int val){
			this->val = val;
			next = prev = NULL;
		}
	};

	Node* head;
	Node* tail;
	public : 
	LinkedList(int val){
		Node* node = new Node(val);
		head = node;
		tail = node;
	}
	void append(LinkedList* l2){
		tail->next = l2->head;
		l2->head->prev = tail;
		tail = l2->tail;
	}	
	void traverse(vector<int>& v){
		Node* curr = head;
		while(curr != NULL){
			v.pb(curr->val);
			curr = curr->next;
		}
	}
};

int parent[MAXN];
int rnk[MAXN];
LinkedList* currList[MAXN];
void init(){
	FOR(i,MAXN){
		parent[i] = i;
		currList[i] = new LinkedList(i);
		rnk[i] = 1;
	}

}
int find(int node){
	if(parent[node] != node)parent[node] = find(parent[node]);
	return parent[node];
}
void merge(int a,int b){
	int pa = find(a);
	int pb = find(b);
	if(rnk[pb] > rnk[pa]){
		parent[pa] = pb;
		currList[pb]->append(currList[pa]);
	}else{
		parent[pb] = pa;
		currList[pb]->append(currList[pa]);
		currList[pa] = currList[pb];
	}
	if(rnk[pb] == rnk[pa])rnk[pa]++;
}



int main(){
	int T;
	cin >> T;
	init();
	vector<pair<ii,int> > allQ;
	while(T--){
		char m;
		cin >> m;
		int a,b;
		cin >> a >> b;
		a--;b--;
		if(m == 'M'){
			merge(a,b);
		}else{
			allQ.pb(mp(mp(a,b),(find(a) == find(b))));
		}
		//cout << "1 QUERY DONE" << endl;
	}
	set<int> st;
	FOR(i,MAXN)st.insert(find(i));
	int loc[MAXN];
	for(auto ele: st){
		vector<int> v;
		currList[ele]->traverse(v);
		FOR(i,v.size()){
			loc[v[i]] = i;
		}
	}
	FOR(i,allQ.size()){
		if(allQ[i].ss == 0){
			cout << -1 << endl;
		}else{
			cout << abs(loc[allQ[i].ff.ff] - loc[allQ[i].ff.ss])-1 << endl;
		}
	}

	return 0;
}

