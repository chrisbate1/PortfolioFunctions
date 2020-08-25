//
//  main.cpp
//  OptIn
//
//  Created by Chris Bate  on 3/6/20.
//  Copyright © 2020 Chris Bate . All rights reserved.
//

#include <iostream>
#include <math.h>
using namespace std;

void printEq(double a, double b, double c){
    if(b >= 0 and c >= 0){
        cout << " of: " << a << "x^2 + " << b << "x + " << c << endl;
    }
    else if(b < 0 and c >= 0){
        cout << " of: " << a << "x^2 - " << -b << "x + " << c << endl;
    }
    else if(b >= 0 and c < 0){
        cout << " of: " << a << "x^2 + " << b << "x - " << -c << endl;
    }
    else if(b < 0 and c < 0){
        cout << " of: " << a << "x^2 - " << -b << "x - " << -c << endl;
    }
}

double solvQuad(double a, double b, double c, double start){
    cout << "Root ";
    printEq(a, b, c);
    int i = 0;
    double x0 = start - (a*start*start + b*start + c) / (2*a*start + b);
    while(fabs(x0-start) > 0.000001){
        i ++;
        start = x0;
        x0 = start - (a*start*start + b*start + c) / (2*a*start + b);
        if (isinf(abs(x0))){
            cout << "Divergent" << endl;
            break;
        }
    }
    cout << "Iterations: " << i << endl;
    return x0;
}

double turnPoint(double a, double b, double c, double start){
    cout << "Turning point";
    printEq(a, b, c);
    int i = 0;
    double x0 = start - (2*a*start + b) / (2*a);
    while(fabs(x0-start) > 0.0000001){
        i ++;
        start = x0;
        x0 = start - (2*start + b) / (2*a);
        if(isinf(abs(x0))){
            cout << "Divergent" << endl;
            break;
        }
    }
    cout << "Iterations: " << i << endl;
    return x0;
}

int main(int argc, const char * argv[]) {
    cout << "Hello, World! \n";
    srand((unsigned)time(NULL));
    
    double a = 2*(rand() %100 +1)-100;
    double b = 2*(rand() %100 +1)-100;
    double c = 2*(rand() %100 +1)-100;
    cout << a << ", " << b << ", " << c << endl;
    cout << b*b - 4*a*c << endl;
    if(b*b - 4*a*c < 0){
        cout << "No real roots" << endl;
        cout << turnPoint(a, b, c, 0) << endl;
    }
    else{
        cout << solvQuad(a,b,c,-100) << endl;
        cout << turnPoint(a, b, c, -1000) << endl;
        cout << turnPoint(a, b, c, 1000) << endl;
    }
    
    return 0;
}
