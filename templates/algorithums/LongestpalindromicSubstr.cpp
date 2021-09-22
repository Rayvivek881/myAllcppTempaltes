string LongestPalindromicString(string & text)
{
    int N = 2 * text.size() + 1;
    int L[N], C = 1, R = 2, i = 0, iMirror, diff = -1;
    L[0] = 0, L[1] = 1;
    int expand = -1, maxLPSLength = 0, maxLPSCenterPosition = 0;
    for (i = 2; i < N; i++) {
        iMirror = 2*C-i;
        expand = 0;
        diff = R - i;
        if(diff >= 0) {
            if(L[iMirror] < diff) L[i] = L[iMirror];
            else if(L[iMirror] == diff && R == N-1)  L[i] = L[iMirror];
            else if(L[iMirror] == diff && R < N-1) L[i] = L[iMirror], expand = 1;
            else if(L[iMirror] > diff) L[i] = diff, expand = 1;
        }
        else L[i] = 0, expand = 1;
        if (expand == 1) {
            while (((i + L[i]) < N && (i - L[i]) > 0) &&(((i + L[i] + 1) % 2 == 0) ||
                (text[(i + L[i] + 1)/2] == text[(i-L[i]-1)/2] ))) L[i]++;
        }
        if(L[i] > maxLPSLength) {
            maxLPSLength = L[i];
            maxLPSCenterPosition = i;
        }
        if (i + L[i] > R) C = i, R = i + L[i];
    }
    int start = (maxLPSCenterPosition - maxLPSLength) / 2;
    int end = start + maxLPSLength - 1;
    return text.substr(start, end - start + 1);
}
