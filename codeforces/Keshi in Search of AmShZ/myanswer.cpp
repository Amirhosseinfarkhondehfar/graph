#include<bits/stdc++.h>
using namespace std;
//in_the_name_of_god;
long long n,m;
set<pair<long long,long long>>st;
vector<long long>khor;
vector<vector<long long>>vor;
vector<bool>visited;
vector<long long>result;

void solve(){
	while(st.size()>0){
		auto x=*st.begin();
		if(visited[x.second]==1){
			st.erase(x);
			continue;
		}
		visited[x.second]=1;
		result[x.second]=x.first;
		for(auto y:vor[x.second]){
			khor[y]--;
			st.insert({x.first+khor[y]+1,y});
		}
	}
}

int main(){
    ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	khor.resize(n+2);
	vor.resize(n+2);
	result.resize(n+2);
	visited.resize(n+2);
	for(long long i=0;i<m;i++){
		long long u,v;
		cin>>u>>v;
		vor[v].push_back(u);
		khor[u]++;
	}
	result[n]=0;
	st.insert({0,n});
	solve();
	cout<<result[1]<<endl;
}
