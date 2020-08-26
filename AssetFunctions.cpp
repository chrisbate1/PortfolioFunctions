// C++ functions on asset price or returns data

#include <ctime>
#include <iostream>
#include <cmath>
using namespace std;

class AssetFunctions{
    public:
        double prices[100];
        double rets[100];
};

void printArray(double[], int);
double mean(double[], int);
double var(double[], int);
double sd(double[], int);
double sharpe(double[], int, double);
double sortino(double[], int, double);
double semiv(double[], int);
double valatrisk(double[], int, double);
double cvar(double[], int, double);
double maxDD(double[], int);

int main(){
    clock_t start = clock();

    AssetFunctions data;
    data.prices[0] = 1;
    data.rets[0] = 0;
    for(int i = 1; i < (sizeof(data.prices) / sizeof(*data.prices)); i++){
        double acc = 1e6;
        // Random walk with 2% drift
        data.prices[i] = data.prices[i - 1] * exp(0.02+(sqrt(-2 * log(double((rand() % long(acc)) / acc))) * cos(2 * M_PI * double(rand() % long(acc)) / acc))/10);
        data.rets[i] = log(data.prices[i] / data.prices[i-1]);
    }

    printArray(data.prices, sizeof(data.prices) / sizeof(*data.prices));
    cout << endl;
    printArray(data.rets, sizeof(data.rets) / sizeof(*data.rets));

    cout << endl;
    cout << "Mean: " << mean(data.rets, sizeof(data.rets) / sizeof(*data.rets)) << endl;
    cout << "Var: " << var(data.rets, sizeof(data.rets) / sizeof(*data.rets)) << endl;
    cout << "SD: " << sd(data.rets, sizeof(data.rets) / sizeof(*data.rets)) << endl;
    cout << "Sharpe: " << sharpe(data.rets, sizeof(data.rets) / sizeof(*data.rets), 0.01) << endl;
    cout << "Semivariance: " << semiv(data.rets, sizeof(data.rets) / sizeof(*data.rets)) << endl;
    cout << "Sortino: " << sortino(data.rets, sizeof(data.rets) / sizeof(*data.rets), 0.01) << endl;
    cout << "VaR: " << valatrisk(data.rets, sizeof(data.rets) / sizeof(*data.rets), 0.01) << endl;
    cout << "CVaR: " << cvar(data.rets, sizeof(data.rets) / sizeof(*data.rets), 0.01) << endl;
    cout << "Max DD: " << maxDD(data.rets, sizeof(data.rets) / sizeof(*data.rets)) << endl;

    cout << "\nTime elapsed: " << (clock() - start) / (double)CLOCKS_PER_SEC << endl;

    return 0;
}

void printArray(double arr[], int sze){
    for(int i = 0; i < sze; i++){
        cout << arr[i] << " ";
        if(i % 20 == 19)
            cout << endl;
    }
}

double mean(double arr[], int sze){
    double s = 0;
    for(int i = 0; i < sze; i++)
        s += arr[i];
    
    return s / sze;
}

double var(double arr[], int sze){
    double m = mean(arr, sze);
    double ss = 0;
    for(int i = 0; i < sze; i++)
        ss += (arr[i] - m)*(arr[i] - m);
    
    return ss / (sze-1);
}

double sd(double arr[], int sze){
    return sqrt(var(arr, sze));
}

double sharpe(double arr[], int sze, double r){
    double m;
    double s = 0;
    for (int i = 0; i < sze; i++)
        s += arr[i];
    m = s / sze;

    return (m - r) / sd(arr, sze);
}

double sortino(double arr[], int sze, double r){
    double m;
    double s = 0;
    for (int i = 0; i < sze; i++)
        s += arr[i];
    m = s / sze;

    return (m - r) / sqrt(semiv(arr, sze));
}

double semiv(double arr[], int sze){
    double m = mean(arr, sze);
    int numBelow = 0;
    double sumBelow = 0;
    double ssBelow = 0;
    for(int i = 0; i < sze; i++)
        if(arr[i] <= m){
            numBelow++;
            sumBelow += arr[i];
        }
    
    double meanBelow = sumBelow / double(numBelow);
    for(int i = 0; i < sze; i++)
        if(arr[i] <= m)
            ssBelow += (arr[i] - meanBelow)*(arr[i] - meanBelow);

    return ssBelow / (numBelow-1);
}

double valatrisk(double arr[], int sze, double p){
    sort(arr, arr+sze);
    
    return -arr[int(sze*p)];
}

double cvar(double arr[], int sze, double p){
    sort(arr, arr + sze);
    double s = 0;
    for (int i = 0; i < sze * p; i++)
        s += arr[i];

    return -s / int(sze*p);
}

double maxDD(double arr[], int sze){
    double ind[sze];
    ind[0] = 1;
    for(int i = 1; i < sze; i++)
        ind[i] = ind[i-1] * exp(arr[i]);
    double mdd = 0;
    // Not computationally efficient 
    for(int i = 0; i < sze; i++)
        for (int j = i; j < sze; j++)
            mdd = max(mdd, log(ind[i] / ind[j]));
    
    return mdd;
}
