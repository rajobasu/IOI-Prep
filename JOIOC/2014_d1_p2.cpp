/*
SOLUTION : For each item we calculate separately. Separate for each number the queries into 3 regions. Anything
in middle region basically keeps higher->higher and lower->higher. so find last region-type-2. count #region-typ
e-3 after that. (region-type-1 has no effect). Also, take acnt of the initial swap.
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
#define ff first
#define ss second
#define pll pair<ll,ll>
#define cd complex<double> 
#define ld long double
#define pld pair<ld,ld>
#define iii pair<ii,int>

const ld INF = 1e9+10;
using namespace std;
const int MAXN = 1000*100*2+10;
const int MAXVAL = 1e9+10;

struct Node{
	Node* left;
	Node* right;
	int val;
	Node(int v){
		left = right = NULL;
		val = v;
	}
};

struct MaxSegtree{
	Node* head;
	inline void expand(Node* node){
		if(node->left == NULL)node->left = new Node(-1);
		if(node->right == NULL)node->right = new Node(-1);
	}
	void update(Node* node,int ss,int se,int i,int val){
		if(i < ss or i > se)return;
		expand(node);
		if(ss == se){
			node->val = val;
			return;
		}
		int mid = (ss+se)/2;
		update(node->left,ss,mid,i,val);
		update(node->right,mid+1,se,i,val);
		node->val = max(node->left->val,node->right->val);
	}
	int get(Node* node,int ss,int se,int l,int r){
		if(node == NULL)return -1;
		if(l > se or ss > r)return -1;
		if(l <= ss and se <= r)return node->val;
		int mid = (ss+se)/2;
		return max(get(node->left,ss,mid,l,r),get(node->right,mid+1,se,l,r));
	}
	MaxSegtree(){
		head = new Node(-1);
	}
};

struct SumSegtree{
	Node* head;
	inline void expand(Node* node){
		if(node->left == NULL)node->left = new Node(0);
		if(node->right == NULL)node->right = new Node(0);
	}
	void update(Node* node,int ss,int se,int i,int val){
		if(i < ss or i > se)return;
		expand(node);
		if(ss == se){
			node->val += val;
			return;
		}
		int mid = (ss+se)/2;
		update(node->left,ss,mid,i,val);
		update(node->right,mid+1,se,i,val);
		node->val = (node->left->val + node->right->val);
	}
	int get(Node* node,int ss,int se,int l,int r){
		if(node == NULL)return 0;
		if(l > se or ss > r)return 0;
		if(l <= ss and se <= r)return node->val;
		int mid = (ss+se)/2;
		return (get(node->left,ss,mid,l,r) + get(node->right,mid+1,se,l,r));
	}
	SumSegtree(){
		head = new Node(0);
	}
};

int ans[MAXN];

void brute(int* a,int* b,int* t,int n,int k){
	ll sum = 0;
	FOR(i,n){
		FOR(j,k){
			if(t[j] >= a[i]){
				swap(a[i],b[i]);
			}
		}
		sum += a[i];
		cout << a[i] << " ";
	}
	cout << sum << endl;
}

int main(){
	int n,k;
	cin >> n >> k;
	vector<iii> all;
	int aa[n];
	int bb[n];
	FOR(i,n){
		int a,b;
		cin >> a >> b;
		aa[i] = a;
		bb[i] = b;
		if(b>a){
			swap(a,b);
			ans[i] = 1;
		}else{
			ans[i] = 0;
		}
		all.pb({{a,b},i});
	}
	MaxSegtree mst;
	SumSegtree sst;

	vector<ii> t;
	int t2[k];
	//mst.update(mst.head,0,MAXVAL,1e9+1,0);
	//t.pb({1e9+1,0});
	FOR(i,k){
		int x;
		cin >> x;
		t2[i] = x;
		t.pb({x,i+1});
		mst.update(mst.head,0,MAXVAL,x,i+1);
	}


	
	//brute(aa,bb,t2,n,k);
	//cout << endl;
	//return 0;

	sort(all.begin(), all.end());

	
	

	sort(t.begin(), t.end());

	reverse(all.begin(), all.end());
	reverse(t.begin(), t.end());
	int ptr = 0;
	for(auto e : all){
		while(ptr < (int)t.size() and t[ptr].ff >= e.ff.ff){
			sst.update(sst.head,0,MAXVAL,t[ptr].ss,1);
			ptr++;
		}

		int lst = 1 + mst.get(mst.head,0,MAXVAL,e.ff.ss,e.ff.ff-1);
		//ns[e.ss] += lst > 0;
		if(ans[e.ss] == 1 and lst > 0)ans[e.ss] = 0;
		//cout << e.ss+1 << " " << e.ff.ff << " "  << lst << " " << ptr << " ";
		int x = sst.get(sst.head,0,MAXVAL,lst,MAXVAL-2);
		//cout << x << " " << ans[e.ss] << endl;;
		ans[e.ss] += x;
	}

	ll sum = 0;
	ll tos[n];
	for(auto e:all){
		if(ans[e.ss]%2 == 0){
			sum += e.ff.ff;
			tos[e.ss] = e.ff.ff;
		}else{
			sum += e.ff.ss;
			tos[e.ss] = e.ff.ss;
		}
	}
	//FOR(i,n)cout << tos[i] << " ";
	cout << sum << endl;
	return 0;
}

