#include <bits/stdc++.h>

using namespace std;

struct MinQueue{
    deque<pair<int,int>>q;
    void push(int x){
        int k=1;
        while(!q.empty() && x<=q.back().first){
			k+=q.back().second;
			q.pop_back();
		}
		q.emplace_back(x,k);
    }
    int min(){ 
		return q.front().first;
	}
    void pop(){ 
		if(!--q.front().second) q.pop_front(); 
	}
};
class SuffixArray{
private:
	int n;
	string str;
	vector<int>SA,LCP,idx;
public:
	SuffixArray(int& N, string& STR){
		n=N,str=STR;
		idx.assign(n,0);
		SA.resize(n),LCP.resize(n);
		build();
	}
	SuffixArray(int& N, string& STR, vector<int>&IDX){
		n=N,str=STR,idx=IDX;
		SA.resize(n),LCP.resize(n);
		build();
	}
    void build(){
		vector<int>rank(n),cnt(max(256,n),0);
		for(int i=0; i<n; i++) cnt[str[i]]++;
		for(int i=1; i<256; i++) cnt[i]+=cnt[i-1];
		for(int i=0; i<n; i++) SA[--cnt[str[i]]]=i;
		rank[SA[0]]=0;
		int classes=1;
		for(int i=1; i<n; i++){
			if(str[SA[i]]!=str[SA[i-1]]) classes++;
			rank[SA[i]]=classes-1;
		}
		vector<int>tempSA(n),tempR(n);
		int x,y,p=1,h=0;
		while(p<n){
			for(int i=0; i<n; i++){
				tempSA[i]=SA[i]-p;
				if(tempSA[i]<0) tempSA[i]+=n;
			}
			for(int i=0; i<classes; i++) cnt[i]=0;
			for(int i=0; i<n; i++) cnt[rank[tempSA[i]]]++;
			for(int i=1; i<classes; i++) cnt[i]+=cnt[i-1];
			for(int i=n-1; i>=0; i--) SA[--cnt[rank[tempSA[i]]]]=tempSA[i];
			tempR[SA[0]]=0;
			classes=1;
			for(int i=1; i<n; i++){
				x=SA[i]+p;
				while(x>=n) x-=n;
				y=SA[i-1]+p;
				while(y>=n) y-=n;
				if(rank[SA[i]]!=rank[SA[i-1]] || rank[x]!=rank[y]) classes++;
				tempR[SA[i]]=classes-1;
			}
			for(int i=0; i<n; i++) rank[i]=tempR[i];
			p=pow(2,++h);
		}
	}
    void lcp(){
		vector<int>match(n),recover(n,0);
		match[SA[0]]=-1;
		for(int i=1; i<n; i++) match[SA[i]]=SA[i-1];
		for(int i=0,l=0; i<n; i++){
			if(match[i]==-1){
				recover[i]=0;
				continue;
			}
			while(i+l<n && match[i]+l<n && str[i+l]==str[match[i]+l]) l++;
			recover[i]=l;
			l=max(l-1,0);
		}
		for(int i=0; i<n; i++) LCP[i]=recover[SA[i]];
	}
    int lcs(int t){
		int maxLCP=-1,x=0,y=1;
		vector<int>vec(t,0);
		MinQueue q;
		vec[idx[SA[x]]]++;
		vec[idx[SA[y]]]++;
		q.push(LCP[y]);
		while(y<n){
			int i;
			for(i=0; i<t && vec[i]!=0; i++);
			if(i<t){
				y++;
				if(y>=n) break;
				vec[idx[SA[y]]]++;
				q.push(LCP[y]);
			}
			else{
				maxLCP=max(maxLCP,q.min());
				vec[idx[SA[x]]]--;
				q.pop();
				x++;
			}
		}
		return maxLCP;
	}
    int lrs(string& ans){
		int id,maior=0,cont=0;
		for(int i=0; i<n; i++){
			if(maior<LCP[i]){
				cont=2;
				id=i;
				maior=LCP[i];
			}
			else if(maior>0 && maior==LCP[i] && maior==LCP[i-1]) cont++;
		}
		ans="";
		for(int i=0; i<maior; i++) ans+=str[i+SA[id]];
		return cont;
	}
    void printSA(){
		cout<<n<<endl;
		for(int i=0; i<n; i++){
			cout<<'['<<i<<']'<<SA[i]<<": "<<LCP[i]<<" -> ";
			for(int j=SA[i]; j<n; j++) cout<< str[j];
			cout<<endl;
		}
	}
};
int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    
}
