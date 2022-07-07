/**
 * @file main.cpp
 * @author Shane Gervais
 * @brief From a wavefunction we want to calculate how much of
 * the wave is transmitted and reflected by finding its 
 * coefficients for each effect.
 * @version 0.1
 * @date 2022-06-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <cstdlib>
//must install eigen3 use: sudo apt-get install libeigen3-dev libeigen3-doc for linux
//This was made on Ubuntu linux
#include <eigen3/Eigen/Dense> 
#include <complex>
#include <string>
#include <sstream>


//Namespaces for short hand
using namespace std;
using namespace Eigen;

//Define type complex for complex numbers
typedef complex<double> Complex;

int main(int argc, char ** argv)
{

    //Default values
    double v = 0.5; //Potential Energy
    double k = 0.2; //Wavenumber

    //Complex number i: (-1)^1/2
    Complex I(0, 1.0);

    //Complex value for wavenumber
    Complex nk = k*sqrt(Complex(1-v));

    //Define vector Y
    VectorXcd Y(4);

    //Initialize vector Y
    Y(0) = -exp(-I*k);
    Y(1) = 0;
    Y(2) = -I*k*exp(-I*k);
    Y(3) = 0;

    //Define matrix A
    MatrixXcd A(4,4);
    
    //Initialize matrix A
    //first row
    A(0,0) = exp(I*k);
    A(0,1) = -exp(-I*nk);
    A(0,2) = -exp(I*nk);
    A(0,3) = 0;

    //second
    A(1,0) = 0;
    A(1,1) = exp(I*nk);
    A(1,2) = exp(-I*nk);
    A(1,3) = -exp(I*k);

    //third
    A(2,0) = -I*k*exp(I*k);
    A(2,1) = -I*nk*exp(-I*nk);
    A(2,2) = I*nk*exp(I*nk);
    A(2,3) = 0;

    //fourth
    A(3,0) = 0;
    A(3,1) = I*nk*exp(I*nk);
    A(3,2) = -I*nk*exp(-I*nk);
    A(3,3) = -I*k*exp(I*k);

    //inverse A
    MatrixXcd Ainv = A.inverse();
    
    //Product of invA and vector Y
    VectorXcd BCDF = Ainv*Y;

    Complex B = BCDF(0), F = BCDF(3);

    //Display BCDF matrix
    cout << "Complex coefficient" << endl;
    cout << BCDF << endl;


    cout << endl;

    //Display results
    //Reflection coefficient describing how much is the wave reflected
    cout << "Reflection coefficient: " << norm(B) << endl;
    //Transmission coefficient describing the amout of the transmitted wave compared to the incident wave
    cout << "Transmission coefficient: " << norm(F) << endl;
    //Should be equal to 1
    cout << "Sum: " << norm(B)+norm(F) << endl;

    return EXIT_SUCCESS;

}//end main function