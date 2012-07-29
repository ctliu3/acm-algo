// Euler function
// phi[i] is the amount of numbers which are smaller and coprime to n
// phi[i] = i * (1 - 1 / p1) * (1 - 1 / p2)  * ... * (1 - 1 / pn) 
// pi is the prime factor of i, and phi[i] = i - 1 if i is a primer.
int phi[MAXN];

void mkphi(int n) {
    fill(phi, phi + n, 0);
    phi[1] = 1; // * 
    for (int i = 2; i <= n; ++i) {
        if (!phi[i]) {
            for (int j = i; j <= n; j += i) {
                if (!phi[j]) {
                    phi[j] = j;
                }
                // in accrod with the formula above
                phi[j] -= phi[j] / i;
            }
        }
    }
}
