#include <iostream>
using namespace std;

int last(string p, char c){
    int last = p.length()-1;
    for (int i = p.length()-1; i>=0; i--){
        if (p[i] == c) {
            if (i<last){
                last = i;
            }
        }
    }
    if (last == p.length()-1){
        return -1;
    }
    return last;
}

void BM (string text, string pat){
    int n = text.length(); int m = pat.length();
    int i = m - 1;
    int j = m - 1;

    int index = 0;

    while (true){
        if (text[i] == pat[j]){
            if (j == 0){
                cout<<"foound a match! "<<endl;
                return i;
            }
            i--;
            j--;
        }
        else if (i<0){
            break;
        }
        else {
            i = i + m - min(j, last(text, pat[j]));
            j = m - 1;
        }
    }
    return -1;
}
