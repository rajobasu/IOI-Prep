/*
https://wcipeg.com/problem/smac081p4

SOLUTION: process from right to left. when we get a value, we try to distribute it efficiently.
 If we distribute one by one, it is too slow for the full solution. What we do is, we assume the blocks are
 already arranged in ascending order. so obviously we would fill in this order. Now, we only keep distinct block
 sizes and their frequencies. Now when we have filled the first one to the level of the second one, we now basically
 merge these two blocks. We will also sometimes need to split some blocks. but we never touch too many differnt block
 sizes. The mergings and going to the next level parts amortizes.

Complexity: O(nlogn)
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
#define ii pair<ll,ll>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define pll pair<ll,ll>


using namespace std;

const int MOD = 1000000007;
const ll INF = 1000000000000000000;
const int MAXN = 501;

int main(){
	int n;
	cin >> n;
	int arr[n];
	FOR(i,n)cin >> arr[n-i-1];
	stack<ii> pq;
	pq.push({1000000000,1});	
	FOR(i,n){
		if(i == 0){
			pq.push({arr[i],1});
			continue;
		}else{

			if(pq.top().ff!=0){
				pq.push({0,1});
			}
			else{
				ii behind = pq.top();pq.pop();
				pq.push({0,behind.ss+1});
			}
		}
		/*
		vector<ii> all;
		while(!pq.empty()){
			ii ele = pq.top();pq.pop();
			cout << ele.ff << ":" << ele.ss << " <> ";
			all.pb(ele);
		}
		cout << endl;
		for(auto ele:all)pq.push(ele);
*/

		ii curr = pq.top();pq.pop();
		int left = arr[i];
		//cout << left << endl;
		//cout << pq.size() << endl;
		while(!pq.empty()){
			//cout << "1"<<endl;
			//cout << left << endl;
			//int z;cin >> z ;
			ii behind = pq.top();

			
			ll canAccomodateBeforeWithoutMerging = max((ll)0,(behind.ff - curr.ff-1)*curr.ss);
			ll canAccomodateBeforeWithMerging = max((ll)0,(behind.ff - curr.ff)*curr.ss);
			//cout << "BEHIND : " << behind.ff << ":" << behind.ss << endl;
			//cout << "STATUS : " << left << " " << canAccomodateBeforeWithMerging << " " << canAccomodateBeforeWithoutMerging << endl;
			if(canAccomodateBeforeWithoutMerging >= left){
				ll minIncreaseForAll = left/curr.ss;
				ll moreIncreaseForSome = left%curr.ss;
				if(moreIncreaseForSome != 0){
					pq.push({curr.ff + minIncreaseForAll + 1,moreIncreaseForSome});
				}
				pq.push({curr.ff + minIncreaseForAll,curr.ss - moreIncreaseForSome});
				
				
				break;
			}else if(canAccomodateBeforeWithMerging >= left){
				pq.pop();
				int leftOut = canAccomodateBeforeWithMerging - left;
				//cout << "LEFTOUT : " << leftOut << endl;
				pq.push({behind.ff,behind.ss + curr.ss - leftOut});
				if(leftOut > 0)pq.push({behind.ff-1,leftOut});
				break;
			}else{
				pq.pop();
				left -= canAccomodateBeforeWithMerging;
				curr = {behind.ff,behind.ss + curr.ss};
				//break;
			}
		}
		if(pq.empty())pq.push(curr);
	}
	/*
	vector<ii> all;
		while(!pq.empty()){
			ii ele = pq.top();pq.pop();
			cout << ele.ff << ":" << ele.ss << " <> ";
			all.pb(ele);
		}
		cout << endl;
		for(auto ele:all)pq.push(ele);
*/
	ll ans = 0;
	//cout<<pq.size()<<endl;
	int sz = pq.size();
	FOR(i,sz-1)
	{
		ii ele =pq.top(); pq.pop();	
	//	cout<<ele<<endl;
		//cout << ele.ff << " " << ele.ss << endl;

		ll val = ele.ff;
		ans += val*val*ele.ss;
	}	
	cout<<ans<<endl;
	
	return 0;
}
