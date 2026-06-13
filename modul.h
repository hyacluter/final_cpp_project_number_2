#ifndef UNTITLED_BBB_H
#define UNTITLED_BBB_H

#include <string>
#include <algorithm>
#include <cctype>
#include <fstream>

class NumericRing {
private:
    std::string ring;
    bool hasLeadingZero(const std::string& s) const {
        return s.length()>1 && s[0]=='0';
    }
    std::string addStrings(const std::string& a, const std::string& b) const {
        std::string result;
        int carry=0;
        int i=a.length()-1;
        int j=b.length()-1;
        while (i>=0 || j>=0 || carry) {
            int sum=carry;
            if (i>=0)sum+=a[i--]-'0';
            if (j>=0)sum+=b[j--]-'0';
            carry=sum/10;
            result+=(sum%10)+'0';
        }
        reverse(result.begin(), result.end());
        return result;
    }

    bool quickCheck(const std::string& a, const std::string& b, const std::string& c) const {
        if (c.length()<std::max(a.length(), b.length())) return false;
        if (c.length()>std::max(a.length(), b.length())+1) return false;
        return true;
    }

    bool checkEquation(const std::string& a, const std::string& b, const std::string& c) const {
        if (hasLeadingZero(a) || hasLeadingZero(b) || hasLeadingZero(c)) return false;
        if (!quickCheck(a,b,c)) return false;
        std::string sum=addStrings(a, b);
        return sum==c;
    }

public:
    int load(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) return 1;
        getline(file, ring);
        file.close();
        ring.erase(remove(ring.begin(), ring.end(), ' '), ring.end());
        ring.erase(remove(ring.begin(), ring.end(), '\n'), ring.end());
        ring.erase(remove(ring.begin(), ring.end(), '\r'), ring.end());
        if (ring.empty()) return 2;
        for (char c : ring)
            if (!isdigit(c)) return 3;
        if (ring.length()>1000) return 4;
        return 0;
    }

    bool find(std::string& result) const {
        int n=ring.length();
        if (n<3) return false;
        for (int lenA=1; lenA<=n-2; lenA++) {
            int minLenC=std::max(lenA, 1);
            int maxLenC=std::min(n-lenA-1,lenA+1);
            for (int lenB=1; lenB<=n-lenA-1; lenB++) {
                int lenC=n-lenA-lenB;
                if (lenC<lenA || lenC<lenB) continue;
                if (lenC>lenA+1 && lenC>lenB+1) continue;
                for (int start=0; start<n; start++) {
                    std::string a,b,c;
                    for (int i=0; i<lenA; i++)
                        a+=ring[(start+i)%n];
                    if (hasLeadingZero(a)) continue;
                    int bStart=(start+lenA)%n;
                    for (int i=0; i<lenB; i++)
                        b+=ring[(bStart+i)%n];
                    if (hasLeadingZero(b)) continue;
                    int cStart=(bStart+lenB)%n;
                    for (int i=0; i<lenC; i++)
                        c+=ring[(cStart+i)%n];
                    if (checkEquation(a,b,c)) {
                        result=a+"+"+b+"="+c;
                        return true;
                    }
                }
            }
        }
        return false;
    }
    bool isEmpty() const { return ring.empty(); }
};
void Menu();

#endif 
