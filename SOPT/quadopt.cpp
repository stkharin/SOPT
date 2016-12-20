//
//  quadopt.cpp
//  SOPT
//
//  Created by Stepan Kharin on 19.12.16.
//  Copyright © 2016 Stepan Kharin. All rights reserved.
//

#include <cmath>
#include <iostream>
using namespace std;

double** makeA(int n, int k, double* x){

    //calculating all required sums of powers of x
    double sum[2*n+1];
    for (int i=0;i<2*n+1;i++){
        sum[i]=0.0;
        for (int j=0;j<k;j++){
            sum[i]+=pow(x[j],i);
        }
    }
    
    //filling up the matrix
    double** A = new double*[n+1];
    for(int i = 0; i < n+1; i++) {
        A[i] = new double[n+1];
        for(int j = 0; j < n+1; j++){
            A[i][j]=sum[i+j];
        }
    }
    return A;
}

double* makeB(int n, int k, double* x, double* y){
    
    double* B = new double[n+1];
    for (int i=0;i<n+1;i++){
        B[i]=0;
        for (int j=0;j<k;j++)
            B[i]+=y[j]*pow(x[j], i);
    }
    return B;
}

double product(int n, double* a, double* b){
    double p=0;
    for (int i=0;i<n;i++)
        p+=a[i]*b[i];
    return p;
}

double* product(int n, double** A, double* b){
    double* p = new double[n];
    for (int i=0;i<n;i++){
        p[i]=0;
        for (int j=0;j<n;j++)
            p[i]+=A[i][j]*b[j];
    }
    return p;
}

double* product(int n, double a, double* b){
    double* p = new double[n];
    for (int i=0;i<n;i++){
        p[i]=a*b[i];
    }
    return p;
}

double* subtract(int n, double* a, double* b){
    double* s=new double[n];
    for (int i=0;i<n;i++)
        s[i]=a[i]-b[i];
    return s;
}

double* add(int n, double* a, double* b){
    double* s=new double[n];
    for (int i=0;i<n;i++)
        s[i]=a[i]+b[i];
    return s;
}

double* linsolve(int n, double** A, double* b) {
    double* x = new double[n];
    double* r;
    double* d;
    
    fill(x,x+n,0.);
    r=b;
    d=r;
    
    double r0=product(n, r, r);
    double r1;
    double* Ap;
    double alpha;
    
    for (int i=0;i<n;i++){
        Ap=product(n, A, d);
        alpha=r0/(product(n, d, Ap));
        x=add(n, x, product(n, alpha, d));
        r=subtract(n, r, product(n, alpha, Ap));
        r1=product(n, r, r);
        if (sqrt(r1)<1e-10)
            break;
        d=add(n, r, product(n, r1/r0, d));
        r0=r1;
    }
    
    return x;
}

double* polyfit(int n, int k, double* x, double* y){
    return linsolve(n+1, makeA(n,k,x), makeB(n,k,x,y));
}

int main() {
    double x[9]={0.5, 1, 1.5, 2.5, 3, 3.5, 4, 4.5, 5};
    double y[9]={0.5, 1.5, 2, 3, 3, 2.5, 2, 1, 0};
    int n=2;
    int k=9;
    
    double* coeffs;
    coeffs=polyfit(n, k, x, y);
    for (int i=0;i<n+1;i++)
        cout<<coeffs[i]<<endl;
    return 0;
}

 
 
 


