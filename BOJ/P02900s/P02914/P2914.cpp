#define onlycc ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

typedef long long ll;

int a, i;

int main()
{
    onlycc;
    cin >> a >> i;
    cout << a*(i-1) + 1;

    return 0;
}
