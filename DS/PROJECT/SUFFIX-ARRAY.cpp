#include<bits/stdc++.h>
using namespace std;

bool suffixCompare(const string& a, const string& b) {
    return a < b;
}

vector<int> constructSuffixArray(const string& str) {
    int n = str.length();
    vector<string> suffixes(n);

    // Generate all suffixes
    for (int i = 0; i < n; ++i) {
        suffixes[i] = str.substr(i);
    }

    // Sort the suffixes using the custom comparator
    sort(suffixes.begin(), suffixes.end(), suffixCompare);

    // Construct the suffix array
    vector<int> suffixArray(n);
    for (int i = 0; i < n; ++i) {
        suffixArray[i] = n - suffixes[i].length();
    }

    return suffixArray;
}

int main() {
    string str;
    cout << "Enter a string: ";
    getline(cin, str);

    vector<int> suffixArray = constructSuffixArray(str);

    cout << "Suffix Array: ";
    for (int suffixIdx : suffixArray) {
        cout << suffixIdx << " ";
    }
    cout << endl;

    return 0;
}

