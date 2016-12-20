//
//  points.cpp
//  test_generator
//
//  Created by Stepan Kharin on 19.12.16.
//  Copyright © 2016 Stepan Kharin. All rights reserved.
//

#include <iomanip>
#include <cmath>
#include <fstream>
#include <iostream>
using namespace std;

//defining constants for coefficients values range
const int lowc=-10;
const int highc=10;
const int rangec=highc-lowc;

//defining constants for x values range
const int lowx=-10;
const int highx=10;
const int rangex=highx-lowx;

//value of maximal difference between real and generated y value
//disty=0 for exact y values
const double dist=0.2;

int main(int argc, const char * argv[]) {
    if (argc==4)
    {
        string filename = argv[1];      //name of the file to create
        int n = atoi(argv[2]);          //polynomial degree
        int k = atoi(argv[3]);          //number of points to generate
        
        if (n<1){
            cout<<"Polynonial degree must be greater then 0"<<endl;
            return 1;
        }
        
        if (k<n+1){
            cout<<"Number of points to generate must be greater than degree of the polynomial"<<endl;
            return 1;
        }
        
        ofstream outfile;
        outfile.open(filename);
        outfile<<k<<endl;
        srand(time(NULL));
        
        double coeffs[n+1];
        for (int i=0;i<n+1;i++){
            coeffs[i]=(lowc+(rand()%(rangec*100))/100.)/pow(i+1,2);  //randomizing polynomial coefficients within the given range with 2 digits after comma precision; the greater the power the less the value
        }
        
        double step = (double)rangex/k; //calclulating step for randomizing x values, so they are more or less evenly distributed within the given range
        for (int i=0;i<k;i++){
            double x=lowx+step*i+(rand()%(int)(step*100))/100.; //calculating x value somewhere within step range
            double y=0;
            double fakex=x-step*dist+step*(rand()%(int)(dist*200))/100.; //calculating fake x somewhere within step*distortion range
            for (int j=0;j<n+1;j++){
                y+=coeffs[j]*pow(fakex,j);   //calculating y value
            }
        outfile<<fixed<<setprecision(2)<<x<<" "<<y<<endl;
        }
        outfile.close();
    }
    else
        cout<<"Wrong number of arguments!"<<endl;
    return 0;
}
