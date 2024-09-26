#include <iostream>
#include <map>
#include <cmath>
#include <vector>
using namespace std;

// Function to convert value from given base to decimal
int decodeValue(string value, int base) {
    int result = 0;
    int power = 0;
    for (int i = value.length() - 1; i >= 0; i--) {
        result += (value[i] - '0') * pow(base, power);
        power++;
    }
    return result;
}

// Lagrange interpolation to find the constant term (c) of the polynomial
double lagrangeInterpolation(const vector<pair<int, int>>& points, int k) {
    double secret = 0;
    
    for (int i = 0; i < k; i++) {
        double term = points[i].second;
        for (int j = 0; j < k; j++) {
            if (i != j) {
                term *= (0 - points[j].first) * 1.0 / (points[i].first - points[j].first);
            }
        }
        secret += term;
    }
    
    return secret;
}

int main() {
    // Input data parsed from JSON (for simplicity, directly in code here)
    map<int, pair<int, string>> data = {
        {1, {10, "4"}},
        {2, {2, "111"}},
        {3, {10, "12"}},
        {6, {4, "213"}}
    };

    // Number of points provided (n) and minimum points needed (k)
    int n = 4;
    int k = 3;

    // Step 1: Decode the values from their respective bases
    vector<pair<int, int>> points;
    for (auto &entry : data) {
        int x = entry.first;
        int base = entry.second.first;
        string encodedValue = entry.second.second;
        int y = decodeValue(encodedValue, base);  // Decode y value
        points.push_back({x, y});
    }

    // Step 2: Find the constant term 'c' using Lagrange interpolation
    double secret = lagrangeInterpolation(points, k);

    // Output the secret (constant term 'c')
    cout << "The constant term (secret 'c') is: " << secret << endl;

    return 0;
}