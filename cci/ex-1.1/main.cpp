#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

/**
 * Function returns number of repeated characters - it's case sensitive.
 * Uses map to store characters already occured.
 * The complexity of this approach is O(n), since map access is O(n) and we iterate over the string only once.
 */
int checkForDuplicates(string &s) {
    int repeatedNo = 0;
    map<char, int> h;
    map<char, int>::iterator mapIt = h.end();
    //iterate over every character in a string
    //check if it was not registered with h map
    //if so, increment repeatitions value (not used yet, but could be to depict which characters repeat)
    //otherwise register in  the h map
    for (string::iterator it = s.begin(); it != s.end(); ++it) {
        char ch = *it;
        mapIt = h.find(ch);
        if (h.end() == mapIt) {//doesn't exist
            h.insert(make_pair(ch, 1));
        }
        else {//it was alredy there
            mapIt->second += 1;
            repeatedNo++;
        }
    }

    return repeatedNo;

    /*
    //populate vector with repeated characters - maybe some day will be needed
    vector<char> repeatChars;
    for (mapIt = h.begin(); mapIt != h.end(); ++mapIt) {
        repeatChars.push_back(*mapIt);
    }
    //return somehow repeatChars;
    */
}

/**
 *Returns number of repeated characters - case sensitive.
 *Doesn't use any additional structure - only array.
 *The complexity is O(n^2), since for every i-th character we have to iterate over the range [(i+1), length)
 */
int checkForDuplicates2(string &s) {
    int repeatsNo = 0;
    for (string::iterator it = s.begin(); it != s.end(); ++it) {
        for (string::iterator it2 = it + 1; it2 != s.end(); ++it2) {
            if (*it == *it2) {
                repeatsNo++;
                //cout << "Repeated: " << *it << ", total: " << repeatsNo << endl;
                //we need to break here, since otherwise if there are more repeatitions, they would be included
                //to repeatsNo in this round and the next one.
                break;
            }
        }
    }

    return repeatsNo;
}

/**
 * Same as above, but with operations on array.
 */
int checkForDuplicates3(const char *s) {
    int repeatsNo = 0;

    for (int outIdx = 0; '\0' != s[outIdx]; ++outIdx) {
        for (int inIdx = outIdx + 1; '\0' != s[inIdx]; ++inIdx) {
            if (s[inIdx] == s[outIdx]) {
                repeatsNo++;
                break;
            }
        }
    }

    return repeatsNo;
}

/**
 * Improved last implementation, since we get rid of the second iteration.
 * For this purpose, additional array is created, where we denote, which variable was used how many times.
 * Assumed ASCII set, however if we could limit ourselves to alphanumeric characters [a-z,A-Z, 0-9] with ' ', this
 * array could have size of 'z'-'a'+1 + 'Z'-'A'+1 + 1 //last one is for space character
 */
#include <cstring>//needed by memset
int checkForDuplicates4(const char *s) {
    int repeatsNo = 0;
    int charsCnt[256];
    memset(charsCnt, 0, sizeof(charsCnt));

    for (int i = 0; '\0' != s[i]; ++i) {
        if (s[i] >= 255) {
            cout << "Out of range character!" << endl;
        }
        else {
            if (0 != charsCnt[s[i]]) {
                repeatsNo++;
            }
            charsCnt[s[i]] += 1;
        }
    }

    return repeatsNo;
}

int main(int argc, char** argv) {
    string input;
    cout << "Input string" << endl;
    getline(cin, input);

    int ret = checkForDuplicates(input);
    cout << "Answer " << (0 == ret);
    cout << "Duplicated values number: " << ret << endl;

    ret = checkForDuplicates2(input);
    cout << "Answer " << (0 == ret);
    cout << "No structs approach (1): " << ret << endl;

    ret = checkForDuplicates3(input.c_str());
    cout << "Answer " << (0 == ret);
    cout << "No structs approach (2): " << ret << endl;

    ret = checkForDuplicates4(input.c_str());
    cout << "Answer " << (0 == ret);
    cout << "No structs approach (3): " << ret << endl;

    return 0;
}
