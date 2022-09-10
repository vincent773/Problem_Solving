#define onlycc ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

const int Segtree_SIZE = 1<<18;
class Segtree{
public:

    ll Size, leaf;
    vector<ll> arr, lazy;

    Segtree(int number) : Size(number)
    {
        leaf = 1;
        arr.resize(1<<22);
        lazy.resize(1<<22);
        fill(arr.begin(), arr.end(), 0);
        fill(lazy.begin(), lazy.end(), 0);
        //while(leaf < Size) leaf *= 2; //[leaf, 2leaf): leaf nodes
        leaf = (1<<22)/2;
    }

    void propagate(int nodeNum, int nodeL, int nodeR) //propagate [LL, RR)
    {
        if(lazy[nodeNum] != 0)
        {
            if(nodeNum < leaf)
            {
                lazy[nodeNum*2] += lazy[nodeNum];
                lazy[nodeNum*2+1] += lazy[nodeNum];
            }

            arr[nodeNum] += (nodeR-nodeL)*lazy[nodeNum];
            lazy[nodeNum] = 0;
        }
    }

    void update(int L, int R, ll k) { return update(L, R, k, 1, 0, leaf); } //add [L, R)
    void update(int L, int R, ll k, int nodeNum, int nodeL, int nodeR)
    {
        propagate(nodeNum, nodeL, nodeR);
        if(R <= nodeL || nodeR <= L) return;
        if(L <= nodeL && nodeR <= R)
        {
            lazy[nodeNum] += k;
            propagate(nodeNum, nodeL, nodeR);
            return;
        }

        ll mid = (nodeL + nodeR) / 2;
        update(L, R, k, nodeNum*2, nodeL, mid);
        update(L, R, k, nodeNum*2+1, mid, nodeR);

        arr[nodeNum] = arr[nodeNum*2] + arr[nodeNum*2+1];
    }

    ll sum(int L, int R) { return sum(L, R, 1, 0, leaf); } //get sum of [L, R)
    ll sum(int L, int R, int nodeNum, int nodeL, int nodeR)
    {
        propagate(nodeNum, nodeL, nodeR);
        if(R <= nodeL || nodeR <= L) return 0;
        if(L <= nodeL && nodeR <= R) return arr[nodeNum];
        ll mid = (nodeL + nodeR) / 2;
        return sum(L, R, nodeNum*2, nodeL, mid) + sum(L, R, nodeNum*2+1, mid, nodeR);
    }

    void construct()
    {
        for(ll i = leaf-1; i > 0; i--)
            arr[i] = arr[i*2] + arr[i*2+1];
    }
};

ll n, m, p[100000], o, a, b, cnt[100000], idx, MAX[100000];
vector<int> Edge[100000];
bool visited[100000];

void dfs(int now)
{
    visited[now] = true;
    cnt[now] = idx++;
    for(auto next : Edge[now])
    {
        if(visited[next]) continue;
        dfs(next);
    }
}

ll find_max(int now)
{
    visited[now] = true;

    MAX[now] = cnt[now];
    for(auto next : Edge[now])
    {
        if(visited[next]) continue;
        MAX[now] = max(MAX[now], find_max(next));
    }

    return MAX[now];
}

int main()
{
    onlycc;
    cin >> n >> m;
    Segtree stree(n+1);
    for(int i = 0; i < n; i++) stree.arr[stree.leaf+i] = 0;
    stree.construct();

    for(int i = 0; i < n; i++)
    {
        cin >> p[i];
        if(i > 0) Edge[p[i]-1].push_back(i);
    }
    for(int i = 0; i < n; i++) if(!visited[i]) dfs(i);

    memset(visited, 0, sizeof(visited));
    for(int i = 0; i < n; i++) if(!visited[i]) find_max(i);

    for(int i = 0; i < m; i++)
    {
        cin >> o >> a;
        if(o == 1)
        {
            cin >> b;
            stree.update(cnt[a-1], MAX[a-1]+1, b);
        }
        else cout << stree.sum(cnt[a-1], cnt[a-1]+1) << '\n';
    }

    return 0;
}
