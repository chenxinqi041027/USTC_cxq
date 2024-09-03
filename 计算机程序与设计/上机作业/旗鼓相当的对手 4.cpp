#include<bits/stdc++.h>
using namespace std;
struct eee {
	int yuwen,shuxue,yingyu,zf;
	string s;
};
int n;
eee a[1001];
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) {
		cin>>a[i].s>>a[i].yuwen>>a[i].shuxue>>a[i].yingyu;
		a[i].zf=a[i].yuwen+a[i].shuxue+a[i].yingyu;
	}
	for(int i=1; i<n; ++i)
		for(int j=i+1; j<=n; ++j) {
			if(a[i].s>a[j].s) {
				swap(a[i].s,a[j].s);
				swap(a[i].yuwen,a[j].yuwen);
				swap(a[i].shuxue,a[j].shuxue);
				swap(a[i].yingyu,a[j].yingyu);
			}
		}
	for(int i=1; i<n; ++i)
		for(int j=i+1; j<=n; ++j) {
			if(abs(a[i].yuwen-a[j].yuwen)<=5&&abs(a[i].shuxue-a[j].shuxue)<=5&&abs(a[i].yingyu-a[j].yingyu)<=5&&abs(a[i].zf-a[j].zf)<=10) {
				cout<<a[i].s<<" "<<a[j].s<<endl;
			}
		}
	return 0;
}

