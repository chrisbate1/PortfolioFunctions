// C++ functions on asset price or returns data

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
double semiv(double[], int);
double valatrisk(double[], int);
double cvar(double[], int);
//double maxDD(double[], int);

int main(){
    AssetFunctions data;
    data.prices[0] = 1;
    data.rets[0] = 0;
    for(int i = 1; i < (sizeof(data.prices) / sizeof(*data.prices)); i++){
        double acc = 1e6;
        data.prices[i] = data.prices[i - 1] * exp((sqrt(-2 * log(double((rand() % long(acc)) / acc))) * cos(2 * M_PI * double(rand() % long(acc)) / acc))/10);
        data.rets[i] = log(data.prices[i] / data.prices[i-1]);
    }

    double myPrices[10];
    for(int i = 0;i<10; i++){
        myPrices[i] = pow(i+1, 2);
        //data.prices[i] = myPrices[i];
    }

    // Array size flexible filling data.prices 

    // for (int i = 0; i < (sizeof(data.prices) / sizeof(*data.prices)); i++)
    //     data.prices[i] = myPrices[i % (sizeof(myPrices) / sizeof(*myPrices))];

    printArray(data.prices, sizeof(data.prices) / sizeof(*data.prices));
    cout << endl;
    printArray(data.rets, sizeof(data.rets) / sizeof(*data.rets));

    cout << endl;
    cout << "Mean: " << mean(data.rets, sizeof(data.rets) / sizeof(*data.rets)) << endl;
    cout << "Var: " << var(data.rets, sizeof(data.rets) / sizeof(*data.rets)) << endl;
    cout << "SD: " << sd(data.rets, sizeof(data.rets) / sizeof(*data.rets)) << endl;
    cout << "Semivariance: " << semiv(data.rets, sizeof(data.rets) / sizeof(*data.rets)) << endl;

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
    long s = 0;
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
    for(int i = 0; i < sze; i++){
        if(arr[i] <= m){
            ssBelow += (arr[i] - meanBelow)*(arr[i] - meanBelow);
        }
    }

    return ssBelow / (numBelow-1);
}

double valatrisk(double arr[], int sze){
    

    return 0;
}
