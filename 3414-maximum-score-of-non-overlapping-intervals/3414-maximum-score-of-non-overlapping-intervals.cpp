class Solution {
public:

    vector<int> maximumWeight(vector<vector<int>>& intervals) {

        int n = intervals.size();


        vector<array<long long, 4>> a;

        for (int i = 0; i < n; i++) {
            a.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        sort(a.begin(), a.end());


        vector<int> nxt(n);

        for (int i = 0; i < n; i++) {

            int left = i + 1;
            int right = n;

            while (left < right) {

                int mid = left + (right - left) / 2;


                if (a[mid][0] > a[i][1])
                    right = mid;
                else
                    left = mid + 1;
            }

            nxt[i] = left;
        }


        vector<vector<pair<long long, vector<int>>>> dp(
            n + 1,
            vector<pair<long long, vector<int>>>(5)
        );


        for (int i = n - 1; i >= 0; i--) {

            for (int k = 1; k <= 4; k++) {


                auto skip = dp[i + 1][k];


                auto take = dp[nxt[i]][k - 1];

                take.first += a[i][2];

                take.second.push_back((int)a[i][3]);


                sort(take.second.begin(), take.second.end());


                if (take.first > skip.first) {
                    dp[i][k] = take;
                }
                else if (take.first < skip.first) {
                    dp[i][k] = skip;
                }
                else {

                    if (take.second < skip.second)
                        dp[i][k] = take;
                    else
                        dp[i][k] = skip;
                }
            }
        }

        return dp[0][4].second;
    }
};