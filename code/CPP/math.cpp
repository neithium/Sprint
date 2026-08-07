#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <string>

using namespace std;

// ==========================================
// 1. Check if a number is prime
// Time Complexity: O(sqrt(n))
// Sample Input: n = 29
// Sample Output: true (1)
// ==========================================
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    // Loop up to the square root of n
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// ==========================================
// 2. Sieve of Eratosthenes
// Time Complexity: O(N log(log N))
// Sample Input: n = 10
// Sample Output: [2, 3, 5, 7]
// ==========================================
vector<int> sieveOfEratosthenes(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p * p <= n; p++) {
        if (is_prime[p]) {
            for (int i = p * p; i <= n; i += p)
                is_prime[i] = false;
        }
    }
    vector<int> primes;
    for (int p = 2; p <= n; p++) {
        if (is_prime[p]) primes.push_back(p);
    }
    return primes;
}

// ==========================================
// 3. Prime Factors
// Time Complexity: O(sqrt(n))
// Sample Input: n = 315
// Sample Output: [3, 3, 5, 7]
// ==========================================
vector<int> primeFactors(int n) {
    vector<int> factors;
    // Divide out the 2s
    while (n % 2 == 0) {
        factors.push_back(2);
        n /= 2;
    }
    // n must be odd now, so skip even numbers
    for (int i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    // If n is a prime greater than 2
    if (n > 2) factors.push_back(n);

    return factors;
}

// ==========================================
// 4. GCD (Greatest Common Divisor)
// Time Complexity: O(log(min(a, b)))
// Sample Input: a = 48, b = 18
// Sample Output: 6
// ==========================================
int gcd(int a, int b) {
    // Loop until the remainder becomes 0
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    // When b is 0, a contains the greatest common divisor
    return a;
}

// ==========================================
// 5. LCM (Least Common Multiple)
// Time Complexity: O(log(min(a, b)))
// Sample Input: a = 4, b = 6
// Sample Output: 12
// ==========================================
int lcm(int a, int b) {
    if (a == 0 || b == 0) return 0;
    return (a / gcd(a, b)) * b;
}

// ==========================================
// 6. Integer Reverse
// Time Complexity: O(log10(n))
// Sample Input: x = 123
// Sample Output: 321
// ==========================================
int reverse(int x) {
    int rev = 0;
    while (x != 0) {
        int pop = x % 10;
        x /= 10;
        // Check for positive and negative overflow
        if (rev > INT_MAX / 10 || (rev == INT_MAX / 10 && pop > 7)) return 0;
        if (rev < INT_MIN / 10 || (rev == INT_MIN / 10 && pop < -8)) return 0;

        rev = rev * 10 + pop;
    }
    return rev;
}

// ==========================================
// 7. Palindrome (Easy version)
// Time Complexity: O(log10(n))
// Sample Input: x = 121
// Sample Output: true (1)
// ==========================================
bool isPalindrome(int x) {
    // Negative numbers cannot be palindromes (e.g., -121 becomes 121-)
    if (x < 0) return false;

    long long original = x;
    long long reversed = 0;

    // Reverse the entire number
    while (x > 0) {
        reversed = reversed * 10 + x % 10;
        x /= 10;
    }

    // Check if the reversed number matches the original
    return original == reversed;
}

// ==========================================
// 8. Armstrong Number
// Time Complexity: O(log10(n))
// Sample Input: n = 153
// Sample Output: true (1)
// ==========================================
bool isArmstrong(int n) {
    int original = n;
    int sum = 0;
    int digits = to_string(n).length();

    while (n > 0) {
        int digit = n % 10;
        sum += pow(digit, digits);
        n /= 10;
    }
    return sum == original;
}

// ==========================================
// 9. Trailing Zeroes
// Time Complexity: O(log5(n))
// Sample Input: n = 25
// Sample Output: 6
// ==========================================
int trailingZeroes(int n) {
    int count = 0;
    while (n > 0) {
        n /= 5;
        count += n;
    }
    return count;
}

// ==========================================
// 10. Square Root of an Integer
// Time Complexity: O(log(n))
// Sample Input: x = 8
// Sample Output: 2
// ==========================================
int mySqrt(int x) {
    if (x == 0 || x == 1) return x;

    int left = 1, right = x, ans = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Use division to prevent overflow from mid * mid
        if (mid <= x / mid) {
            ans = mid;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return ans;
}

// ==========================================
// 11. Robot Return to Origin
// Time Complexity: O(N) where N is the length of the string.
// Sample Input: moves = "UD"
// Sample Output: true (1)
// ==========================================
bool judgeCircle(string moves) {
    int x = 0, y = 0;
    for (char move : moves) {
        if (move == 'U') y++;
        else if (move == 'D') y--;
        else if (move == 'R') x++;
        else if (move == 'L') x--;
    }
    return x == 0 && y == 0;
}

// ==========================================
// 12. Pow (x, n)
// Time Complexity: O(log(n))
// Sample Input: x = 2.0, n = 3
// Sample Output: 8.0
// ==========================================
double myPow(double x, int n) {
    // Base case: anything to the power of 0 is 1
    if (n == 0) return 1.0;

    // Calculate the power of half the exponent
    double half = myPow(x, n / 2);

    // If the exponent is even
    if (n % 2 == 0) return half * half;

    // If the exponent is odd and positive
    if (n > 0) return half * half * x;

    // If the exponent is odd and negative
    return half * half / x;
}

// ==========================================
// Main function for testing
// ==========================================
int main() {
    cout << "1. isPrime(29): " << isPrime(29) << endl;

    cout << "2. Sieve of Eratosthenes(10): ";
    vector<int> primes = sieveOfEratosthenes(10);
    for (int p : primes) cout << p << " ";
    cout << endl;

    cout << "3. Prime Factors(315): ";
    vector<int> factors = primeFactors(315);
    for (int f : factors) cout << f << " ";
    cout << endl;

    cout << "4. GCD(48, 18): " << gcd(48, 18) << endl;
    cout << "5. LCM(4, 6): " << lcm(4, 6) << endl;
    cout << "6. Reverse(123): " << reverse(123) << endl;
    cout << "7. isPalindrome(121): " << isPalindrome(121) << endl;
    cout << "8. isArmstrong(153): " << isArmstrong(153) << endl;
    cout << "9. Trailing Zeroes(25): " << trailingZeroes(25) << endl;
    cout << "10. Square Root(8): " << mySqrt(8) << endl;
    cout << "11. Judge Circle(\"UD\"): " << judgeCircle("UD") << endl;
    cout << "12. Pow(2.0, 3): " << myPow(2.0, 3) << endl;

    return 0;
}