/* 
SOLUTION: 
let pile be of form 110 110 (in binary). Then we need to disbalance it (1,1->0,2 and similar)
in all turns which lets us use 1 turn less overall for the heap. Else just remove from the highest pile. For player B, try to keep everything same same, and disbalance only if you have to. 
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

// count number of 1s in the beginning
int ld1(int n) {
  int cnt = 0;
  for (int i = 30; i >= 0; i--) {
    if (((1<<i) & n) > 0) cnt++;
    else if (cnt > 0) break;
  }
  return cnt;
}

int sz(int n){
	int cnt = 0;
	while(n > 0){
		cnt++;
		n/=2;
	}
	return cnt;
}


int main(){
	int n;
	cin >> n;
	int ctr = 0;
	priority_queue<int> pq;
	FOR(i,n){
		int a;
		cin >> a;
		ctr += 2*(sz(a)+1); // total number of moves needed to destroy without considering special moves; 	
		pq.push(ld1(a));
	}
	// assume we have removed everything after the first 0 in x(x=a+b, a and b are stones in piles);now we can use disbalancing moves. Note that if a pile has K leading 0s, we need exactly K disbalancing moves. 

	pq.pop(); // first time everything is balanced so just remove one of the piles. this forces the opponent to create a disbalance somewhere. 
	while(!pq.empty()){
		auto f = pq.top();pq.pop();
		// the player B always disbalances the largest pile, hence we choose that pile (largest pile == most number of leading 1s becoz we already removed everything to the left of the first 0). Now, if the size was 1,1 then it had become 0,2 and we could have removed the entire thing and player 2 would again have to disbalance stuff. If not, then after we remove one of the piles, the player can just make stuff even and we cant really get a free move from here becoz as mentioned, we would need exactly k disbalances for a pile with k leading 0s, and anything less wont suffice. Hence, its a wasted pile. on its removal though one other pile will be disbalanced. Thats why we push (f-1, to account for the disbalance) and then pop() since the largest pile (not necessarily the current) will be wasted. 
		if(f == 1)ctr-=2;
		else{
			pq.push(f-1);
			pq.pop();
		}
	}	
	cout << ctr-1 << endl;

	
	return 0;
}