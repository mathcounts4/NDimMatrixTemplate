// g++ -std=c++14 TestMatrix.cpp -o testMatrix.out
// g++ -std=c++14 TestMatrix.cpp -o testMatrix.out -D DEBUG
// g++ -std=c++14 TestMatrix.cpp -o testMatrix.out -D DEBUG -g

#include <iostream>
#include "Matrix2D.hpp"

#ifdef DEBUG
#define QQ std::cout << "line " << __LINE__ << " in " << __FUNCTION__ << std::endl
#else
#define QQ 0
#endif

#ifdef Q
#undef Q
#endif

using namespace std;



void preamble()
{
#ifndef DEBUG
    cout << "Use g++ option -D DEBUG to view constructor and destructor calls, as well as periodic main() line numbers" << endl << endl;
#endif
}



void section1()
{
    cout << endl << endl << endl;
    cout << "*** Section 1: Declaring, setting, and printing ***" << endl;
    cout << endl;



    QQ;
    cout << "Declaring 3 matrices:" << endl;
    Matrix<int> X;
    Matrix<int,3> Y;
    Matrix<int,3,4> Z(3);
    cout << endl;



    QQ;
    cout << "Printing their dimensions:" << endl;
    cout << X.getDims() << endl;
    cout << Y.getDims() << endl;
    cout << Z.getDims() << endl;
    cout << endl;



    QQ;
    cout << "Setting and printing some values (17,5,1,17):" << endl;
    X() = 17;     // = 17
    Y(2) = 5;     // = 5
    Z(2,3) = 1;   // = 1
    Z(1,3) = X(); // = 17
    cout << X() << " " << Y(2) << " " << Z(2,3) << " " << Z(1,3) << endl;
    cout << endl;

    

    QQ;
    cout << "Using a reference of a Matrix<int,12> to change a Matrix<int,3,4> matrix value (thanks reinterpret_cast):" << endl;
    Matrix<int,12>& A = Z;
    cout << "Was " << Z(2,3) << endl;
    A(11) = 42;
    cout << "Now is " << Z(2,3) << endl;
    cout << endl;
}



void section2()
{
    cout << endl << endl << endl;
    cout << "*** Section 2: Error throwing (and catching) ***" << endl;
    cout << endl;



    QQ;
    cout << "Declaring 3 matrices:" << endl;
    Matrix<int> X;
    Matrix<int,3> Y;
    Matrix<int,3,4> Z(3);
    Matrix<int,12>& A = Z; // reference
    cout << endl;


    
    /*
     * NOW CHECKED AT COMPILE-TIME
     *

    try
    {
	QQ;
	cout << "Attempting to initialize a matrix of the wrong size" << endl;
	// Z has total size 12
	Matrix<int,10> Bad = Z;
    }
    catch (logic_error& err)
    {
	cout << "error: " << err.what() << endl;
    }
    */


    
    try
    {
	QQ;
	cout << "Attempting to access an index out-of bounds" << endl;
	// A has a size of 12
	A(42) = 54;
    }
    catch (logic_error& err)
    {
	cout << "error: " << err.what() << endl;
    }
    cout << endl;


    
    try
    {
	cout << "Attempting to index into a matrix using the wrong number of dimensions" << endl;
	// Z is 2-dimensional
	Z(1) = 2;
    }
    catch (logic_error& err)
    {
	cout << "error: " << err.what() << endl;
    }
    cout << endl;


    
    try
    {
	cout << "Attempting to divide a matrix by 0" << endl;
	// Divide by 0 (matrix / T)
	auto bad = A / 0;
    }
    catch (runtime_error& err)
    {
	cout << "error: " << err.what() << endl;
    }
    cout << endl;


    
    try
    {
	cout << "Attempting to divide a number by a matrix with a 0 element" << endl;
	// Divide by 0 (T / matrix)
	Matrix<double,3> bad = 5 / (Y - Y);
    }
    catch (runtime_error& err)
    {
	cout << "error: " << err.what() << endl;
    }
    cout << endl;
}



void section3()
{
    cout << endl << endl << endl;
    cout << "*** Section 3: Operators ***" << endl;
    cout << endl;



    QQ;
    cout << "Declaring a matrix:" << endl;
    Matrix<int,12> A(3);
    cout << endl;



    QQ;
    cout << "Using operators +, - and - (negative) to construct 3 new matrices, in addition to +, -, *, and / for matrix/scalar operations:" << endl;
    cout << endl;
    Matrix<double,12> D = 2 + 7 * A + A / 6 - 4;
    cout << endl;
    double three = 3;
    Matrix<int,2,2,3> E = three - three / D + A * 3 - D + three;
    cout << endl;
    auto F = -D - A; // creates a MatrixDif<ME,double,int,12>&
    Matrix<int,4,3> G = F;
    cout << endl;



    QQ;
    cout << "Printing the dims of the created matrices:" << endl;
    cout << D.getDims() << endl;
    cout << E.getDims() << endl;
    cout << G.getDims() << endl;
    cout << endl;



    QQ;
    cout << "Attempting to multiply A<int,12> by D<double,12>" << endl;
    Matrix<int> H = A * D;
    cout << "( ";
    for (size_t i = 0; i < 12; i++)
    {
	cout << A(i) << " ";
    }
    cout << ") * ( ";
    for (size_t i = 0; i < 12; i++)
    {
	cout << D(i) << " ";
    }
    cout << ") = " << H() << endl;
    cout << endl;



    QQ;
    cout << "Creating I<int,2,2,1>" << endl;
    Matrix<int,2,2,1> I(1);
    cout << "I is " << I.getDims() << ":" << endl;
    for (size_t i = 0; i < 2; i++)
    {
	for (size_t j = 0; j < 2; j++)
	{
	    cout << I(i,j,0) << endl;
	}
	cout << endl;
    }
    cout << "E is " << E.getDims() << ":" << endl;
    for (size_t i = 0; i < 2; i++)
    {
	for (size_t j = 0; j < 2; j++)
	{
	    for (size_t k = 0; k < 3; k++)
	    {
		cout << E(i,j,k) << " ";
	    }
	    cout << endl;
	}
	cout << endl;
    }
    cout << "Multiplying E by I" << endl;
    Matrix<int,3> J = E * I;
    cout << "Result:" << endl;
    for (size_t i = 0; i < 3; i++)
    {
	cout << J(i) << " ";
    }
    cout << endl << endl;



    QQ;
    cout << "Multiplying E by (I + 1)" << endl;
    Matrix<int,3> K = E * (I + 1);
    cout << "Result:" << endl;
    for (size_t i = 0; i < 3; i++)
    {
	cout << K(i) << " ";
    }
    cout << endl << endl;



    QQ;
    cout << "Multiplying (E + 4) by I" << endl;
    Matrix<int,3> L = (E + 4) * I;
    cout << "Result:" << endl;
    for (size_t i = 0; i < 3; i++)
    {
	cout << L(i) << " ";
    }
    cout << endl << endl;



    QQ;
    cout << "Multiplying (E + 4) by (2 * I)" << endl;
    Matrix<int,3> M = (E + 4) * (2 * I);
    cout << "Result:" << endl;
    for (size_t i = 0; i < 3; i++)
    {
	cout << M(i) << " ";
    }
    cout << endl << endl;



    QQ;
    cout << "Making Matrix<int,2,2,1> N(1) and Matrix<int,1,2,2> O(1)" << endl;
    Matrix<int,2,2,1> N(1);
    Matrix<int,1,2,2> O(1);
    cout << "Assigning N = N * O. Checks dependence since we use lazy evaluation - we should be creating a temporary and then copying that to N. All of N should now be 2" << endl;
    N = N * O;
    for (size_t i = 0; i < 2; i++)
    {
	for (size_t j = 0; j < 2; j++)
	{
	    cout << N(i,j,0) << " ";
	}
	cout << endl;
    }
    cout << endl;



    QQ;
    cout << "Making Matrix<int,2,1,2> P(0)" << endl;
    Matrix<int,2,1,2> P(0);
    cout << "Assigning P = P + N * O. Checks dependence and should NOT create a temporary. All of P should now be 4" << endl;
    P = P + N * O;
    for (size_t i = 0; i < 2; i++)
    {
	for (size_t j = 0; j < 2; j++)
	{
	    cout << P(i,0,j) << " ";
	}
	cout << endl;
    }
    cout << endl;
}



void section4()
{
    cout << endl << endl << endl;
    cout << "*** Section 4: 2D Operators ***" << endl;
    cout << endl;



    QQ;
    cout << "Making Matrix<int,2,3> Q(2) and Matrix<double,3,4> R(1)" << endl;
    Matrix<int,2,3> Q(2);
    Matrix<double,3,4> R(1);
    cout << endl;



    QQ;
    cout << "Multiplying Q * R. Should be all 6:" << endl;
    Matrix<double,2,4> S = Q * R;
    for (size_t i = 0; i < 2; i++)
    {
	for (size_t j = 0; j < 4; j++)
	{
	    cout << S(i,j) << " ";
	}
	cout << endl;
    }
    cout << endl;



    QQ;
    cout << "Multiplying (Q+1) * R. Should be all 9." << endl;
    Matrix<double,2,4> T = (Q+1) * R;
    for (size_t i = 0; i < 2; i++)
    {
	for (size_t j = 0; j < 4; j++)
	{
	    cout << T(i,j) << " ";
	}
	cout << endl;
    }
    cout << endl;



    QQ;
    cout << "Multiplying Q * (R+1.0). Should be all 12." << endl;
    Matrix<double,2,4> U = Q * (R+1.0);
    for (size_t i = 0; i < 2; i++)
    {
	for (size_t j = 0; j < 4; j++)
	{
	    cout << U(i,j) << " ";
	}
	cout << endl;
    }
    cout << endl;



    QQ;
    cout << "Multiplying (Q+1) * (R+1.0). Should be all 18." << endl;
    Matrix<double,2,4> V = (Q+1) * (R+1.0);
    for (size_t i = 0; i < 2; i++)
    {
	for (size_t j = 0; j < 4; j++)
	{
	    cout << V(i,j) << " ";
	}
	cout << endl;
    }
    cout << endl;



    QQ;
    cout << "Multiplying Matrix<double,2>(4) by Matrix<int,2,3>(3)" << endl;
    Matrix<int,3> W = Matrix<double,2>(4) * Matrix<int,2,3>(3);
    for (size_t i = 0; i < 3; i++)
    {
	cout << W(i) << " ";
    }
    cout << endl << endl;
}



int main()
{
    cout << endl;
    
    preamble();

    section1();
    section2();
    section3();
    section4();

    cout << endl << endl << endl <<
	"*** END OF MAIN ***" <<
	endl << endl << endl << endl;;

    return 0;
}
