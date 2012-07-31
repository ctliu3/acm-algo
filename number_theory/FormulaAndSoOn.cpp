// The greatest common divisor between two numbers
// allow negative numbers in the args
int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        int c = b;
        b = a % b; // 8 % 12 = 8 
        a = c;
    }
    return a;
}
