/*
SOLUTION:
For every pair of (i,j), in candy 1 and candy2 segments i to j form a rectangle of possibilities.
Find largest (x+y), st (x,y) is covered by a rectangle of candy1 as well as candy2.
To do this, do offline sweep over x, and using dynamic lazy segree+ binrsch for y..
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
#define vi vector<int>
#define pb push_back
#define ff first
#define ss second
#define ii pair<int,int>
#define iii pair<int,ii>
#define iiii pair<iii,int>
#define pll pair<ll,ll>
#define plll pair<ll,pll>
#define vv vector
#define endl '\n'
 
using namespace std;
 
const int MAXN = 100*1000 + 5;
int MAX_VAL = 1e9;

// ================================================
// ============== Segtree Code ===============
// ================================================
struct Node{
	int left;
	int right;
	int data;
	int lzd;
	Node(int a=-1,int b=-1,int c=0){
		left = a;
		right = b;
		data = c;// data just maintains the maximum value in the range. 
		lzd = 0;
	}
};


Node buffer[(int)6e6];
int PTR = 0;
	
void push(int node,int ss,int se){
	buffer[node].data += buffer[node].lzd;
	if(ss == se){
		buffer[node].lzd = 0;
		return;
	}

	if(buffer[node].left == -1)buffer[node].left = PTR++;
	if(buffer[node].right == -1)buffer[node].right = PTR++;
	
	if(buffer[node].lzd == 0)return;

	//cout << buffer[node].lzd << endl;
	buffer[buffer[node].left].lzd += buffer[node].lzd;
	buffer[buffer[node].right].lzd += buffer[node].lzd;
	buffer[node].lzd = 0;
}

void update(int node,int ss,int se,int l,int r,int val){
	//cout << buffer[node].data << " " << ss << " " << se << " " << val << endl;
	if(ss > r or se < l)return;
	push(node,ss,se);
	if(l <= ss and se <= r){
		buffer[node].lzd += val;
		push(node,ss,se);
		//cout << "OOF: " << buffer[node].data << " " << ss << " " << se << " " << val << endl;
		return;
	}	
	int mid = (ss+se)/2;
	update(buffer[node].left, ss,mid,l,r,val);
	update(buffer[node].right,mid+1,se,l,r,val);
	buffer[node].data = max(buffer[buffer[node].left].data, buffer[buffer[node].right].data);
}

int binary_search(int node1,int node2,int ss,int se){
	int lo = ss;
	int hi = se;
	push(node1,lo,hi);
	push(node2,lo,hi);
	//cout << buffer[node1].data << endl;
	if(buffer[node1].data == 0 or buffer[node2].data == 0)return -1;
	while(hi >= lo){
		// the assumption is this range has data>0 for both trees
		if(hi == lo)return lo;
		int mid = (lo+hi)/2;
		push(buffer[node1].left,lo,mid);
		push(buffer[node1].right,mid+1,hi);

		push(buffer[node2].left,lo,mid);
		push(buffer[node2].right,mid+1,hi);
		//cout << lo << " " << hi << " " << buffer[buffer[node1].right].data << " " << buffer[buffer[node2].right].data << endl;
		if(buffer[buffer[node1].right].data > 0 and buffer[buffer[node2].right].data > 0){
			lo = mid+1;
			node1 = buffer[node1].right;
			node2 = buffer[node2].right;
		}else if(buffer[buffer[node1].left ].data > 0 and buffer[buffer[node2].left ].data > 0){
			node1 = buffer[node1].left;
			node2 = buffer[node2].left;
			hi = mid;
		}else{
			return -1;
		}
	
	}
}
// ================================================
// ================================================
// ================================================


struct Rect{
	int x1,x2;
	int y1,y2;
	Rect(int a,int b,int c,int d){
		x1 = a;
		x2 = b;
		y1 = c;
		y2 = d;
	}
};

void formRects(int n,pair<char,int>* arr,vv<Rect>& result){
	int w[n];
	int b[n];
	w[0] = b[0] = 0;
	FOR(i,n){
		if(i > 0){
			w[i] = w[i-1];
			b[i] = b[i-1];
		}
		if(arr[i].ff == 'W')w[i] += arr[i].ss;
		else b[i] += arr[i].ss;
	}
	
	FOR(i,n){
		FOR(j,i+1){
			int maxww = w[i] - (j == 0?0:w[j-1]);
			int maxbb = b[i] - (j == 0?0:b[j-1]);

			int minww = maxww;
			if(arr[j].ff == 'W')minww -= arr[j].ss-1;// since we want to include atleast one from that portion. 
			if(j != i and arr[i].ff == 'W')minww -= arr[i].ss-1;

			int minbb = maxbb;
			if(arr[j].ff == 'T')minbb -= arr[j].ss-1;// since we want to include atleast one from that portion. 
			if(j != i and arr[i].ff == 'T')minbb -= arr[i].ss-1;

			result.pb(Rect(minww,maxww,minbb,maxbb));
		}
	}

}


void printR(Rect e){

	cout << e.x1 << " " << e.x2 << " " << e.y1 << " " << e.y2 << endl;
}


struct Event{
	int tm; // time
	bool type; // start/end
	bool id; // well, id
	// assumption is a <= b;
	int a;
	int b;
	Event(int a1,bool a2,bool a3,int a4,int a5){
		tm = a1;
		type = a2;
		id = a3;
		a = a4;
		b = a5;
	}
};


vi allVec_map;
int index(int n){
	return lower_bound(allVec_map.begin(), allVec_map.end(),n) - allVec_map.begin();
}
int rindex(int n){
	return allVec_map[n];
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	pair<char,int> num1[n];
	FOR(i,n)cin >> num1[i].ff >> num1[i].ss;

	int m;
	cin >> m;
	pair<char,int> num2[m];
	FOR(i,m)cin >> num2[i].ff >> num2[i].ss;

	
	vv<Rect> list1;formRects(n,num1,list1);
	vv<Rect> list2;formRects(m,num2,list2);
	
	int best = 0;
	MAX_VAL = 0;
	vv<Event> allEvents;
	set<int> allSet;
	for(auto e : list1){
		allEvents.pb(Event(e.x1,1,0,e.y1,e.y2));
		allEvents.pb(Event(e.x2+1,0,0,e.y1,e.y2));
		allSet.insert(e.y1);
		allSet.insert(e.y2);
		//MAX_VAL = max(MAX_VAL,max(e.y1,e.y2));
	}
	for(auto e : list2){
		allEvents.pb(Event(e.x1,1,1,e.y1,e.y2));
		allEvents.pb(Event(e.x2+1,0,1,e.y1,e.y2));
		allSet.insert(e.y1);
		allSet.insert(e.y2);
		//MAX_VAL = max(MAX_VAL,max(e.y1,e.y2));
	}
	sort(allEvents.begin(), allEvents.end(), [&](Event e1, Event e2){
		return e1.tm < e2.tm;
	});

	for(auto e : allSet)allVec_map.pb(e);
	allSet.clear();
	MAX_VAL =10+ allVec_map.size();

	list1.clear();
	list2.clear();

	// lets process the events yay. 
	int allN = allEvents.size();
	int head1 = PTR++;
	int head2 = PTR++;
	int best2;
	FOR(i,allN){
		Event e = allEvents[i];
		if(i > 0 and allEvents[i].tm > allEvents[i-1].tm){
			int f = binary_search(head1,head2,0,MAX_VAL);
		//	cout << f << endl;
			if(f >= 0)best = max(best,e.tm-1+rindex(f));
		}
		if(!e.id)update(head1,0,MAX_VAL,index(e.a),index(e.b),(e.type)*2-1);
		else update(head2,0,MAX_VAL,index(e.a),index(e.b),(e.type)*2-1);
	}
	cout << best << endl;

	return 0;
}
