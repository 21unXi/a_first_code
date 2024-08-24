#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define INF 0x3f3f3f3f
const int maxn = 1e6 + 10;
ll n, q, m;
ll a[maxn];
struct edge
{
	ll sum, add, mul;
}e[maxn];
void build(ll l, ll r, ll p)
{
	e[p].mul = 1;
	if(l == r) 
	{
		e[p].sum = a[l] % m;
		return;
	}
	ll mid = (l + r) >> 1; 
	build(l, mid, p * 2);
	build(mid + 1, r, p * 2 + 1);
	e[p].sum = (e[p * 2].sum + e[p * 2 + 1].sum) % m; 
}

void del(ll s, ll t, ll p)//将延时标记传递 
{
	ll mid = (s + t) >> 1;
	e[p * 2].sum = (e[p].mul * e[p * 2].sum + ((mid - s + 1) * e[p].add) % m) % m;
	e[p * 2 + 1].sum = (e[p].mul * e[p * 2 + 1].sum + ((t - mid) * e[p].add) % m) % m;
	
	e[p * 2].mul = (e[p * 2].mul * e[p].mul) % m;
	e[p * 2 + 1].mul = (e[p * 2 + 1].mul * e[p].mul) % m;
	
	e[p * 2].add = (e[p * 2].add * e[p].mul + e[p].add) % m;
	e[p * 2 + 1].add = (e[p * 2 + 1].add * e[p].mul + e[p].add) % m;
	
	e[p].mul = 1, e[p].add = 0;
}

void update1(ll l, ll r, ll s, ll t, ll c, ll p)//加法更新 
{
	if(l <= s && t <= r)
	{
		e[p].add = (e[p].add + c) % m;
		e[p].sum = (e[p].sum + c * (t - s + 1)) % m;
		return;
	}
	del(s, t, p);
	ll mid = (s + t) >> 1;
	e[p].sum = (e[p * 2].sum + e[p * 2 + 1].sum) % m;
	if(l <= mid) update1(l, r, s, mid, c, p * 2);
	if(r > mid) update1(l, r, mid + 1, t, c, p * 2 + 1);
	e[p].sum = (e[p * 2].sum + e[p * 2 + 1].sum) % m;
}

void update2(ll l, ll r, ll s, ll t, ll c, ll p)//乘法更新 
{
	if(l <= s && t <= r)
	{
		e[p].add = (e[p].add * c) % m;
		e[p].mul = (e[p].mul * c) % m;
		e[p].sum = (e[p].sum * c) % m;
		return ;
	}
	del(s, t, p);
	e[p].sum = (e[p * 2].sum + e[p * 2 + 1].sum) % m;
	ll mid = (s + t) >> 1;
	if(l <= mid) update2(l, r, s, mid, c, p * 2);
	if(r > mid) update2(l, r, mid + 1, t, c, p * 2 + 1);
	e[p].sum = (e[p * 2].sum + e[p * 2 + 1].sum) % m;  
}

ll getsum(ll l, ll r, ll s, ll t, ll p)
{
	if(l <= s && t <= r) return e[p].sum;
	ll mid = (s + t) >> 1, ans = 0;
	del(s, t, p);
	if(l <= mid) ans = getsum(l, r, s, mid, p * 2) % m;
	if(r > mid) ans = (ans + getsum(l, r, mid + 1, t, p * 2 + 1) % m) % m;
	return ans;
}
void solve()
{
	cin >> n >> q >> m;	
	for(int i = 1; i <= n; i++) cin >> a[i];
	build(1, n, 1);
	for(int i = 1; i <= q; i++)
	{
		ll op, x, y, k;
		cin >> op;
		if(op == 1) 
		{
			cin >> x >> y >> k;
			update2(x, y, 1, n, k, 1);
		}
		else if(op == 2)
		{
			cin >> x >> y >> k;
			update1(x, y, 1, n, k, 1);
		}
		else
		{
			cin >> x >> y;
			cout << getsum(x, y, 1, n, 1) % m << endl;
		}
	}
} 
signed main()
{
    //ios::sync_with_stdio(false);cin.tie(0);
	

//	int t;
//	cin >> t;
//	while(t--) 
//	
	solve();
	return 0; 
}


