#define onlycc ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<int, long double> pid;

ll b, p;

int main()
{
    onlycc;
    cin >> b;
    p = 5*b - 400;

    cout << p << '\n';
    if(p < 100) cout << 1;
    else if(p > 100) cout << -1;
    else cout << 0;

    return 0;
}
