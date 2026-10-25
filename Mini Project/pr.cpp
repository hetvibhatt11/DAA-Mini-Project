#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    int budget, n;

    cout << "====================================\n";
    cout << " SMART BUDGET OPTIMIZATION SYSTEM\n";
    cout << "====================================\n";

    cout << "Enter your total budget (Rs.): ";
    cin >> budget;

    cout << "Enter number of expenses: ";
    cin >> n;

    vector<string> name(n);
    vector<int> cost(n), priority(n);

    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter expense name: ";
        cin >> name[i];

        cout << "Enter expense cost: ";
        cin >> cost[i];

        cout << "Enter priority value (1-10): ";
        cin >> priority[i];

        if (cost[i] < 0 || priority[i] < 1 ||
            priority[i] > 10)
        {
            cout << "Invalid cost or priority!\n";
            return 0;
        }
    }

    // Dynamic Programming table
    vector<vector<int>> dp(
        n + 1, vector<int>(budget + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w <= budget; w++)
        {
            dp[i][w] = dp[i - 1][w];

            if (cost[i - 1] <= w)
            {
                int include = priority[i - 1]
                    + dp[i - 1][w - cost[i - 1]];

                if (include > dp[i][w])
                    dp[i][w] = include;
            }
        }
    }

    cout << "\n========== OPTIMIZED BUDGET ==========\n";

    cout << "Maximum Priority Value: "
         << dp[n][budget] << endl;

    cout << "\nSelected Expenses:\n";

    int w = budget;
    int totalCost = 0;

    for (int i = n; i > 0; i--)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            cout << name[i - 1]
                 << " - Rs. " << cost[i - 1]
                 << " (Priority: " << priority[i - 1]
                 << ")\n";

            totalCost += cost[i - 1];
            w -= cost[i - 1];
        }
    }

    cout << "\nTotal Selected Cost: Rs. "
         << totalCost << endl;

    cout << "Remaining Budget: Rs. "
         << budget - totalCost << endl;

    cout << "======================================\n";

    return 0;
}
