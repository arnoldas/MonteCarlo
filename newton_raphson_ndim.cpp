////////////////////////////////////////////////////////////////////////////////
// File: newton_raphson_ndim.c                                                //
// Routines:                                                                  //
//    Newton_Raphson_ndim.c                                                   //
////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>                // required for malloc(), free(), and NULL

//                        Externally Defined Routines

void    Copy_Vector(double *d, double *s, int n);
int     Gaussian_Elimination(double *A, int n, double *B);
double* Subtract_Vectors(double w[], double u[], double v[], int n);

////////////////////////////////////////////////////////////////////////////////
//  int Newton_Raphson_ndim( void (*f)(double*, double*),                     //
//                   void (*df)(double*, double*, double*),                   //
//                              int (*Stopping_Rule)(double*, double*, int),  //
//                                             double *a, double *fa, int n)  //
//                                                                            //
//  Description:                                                              //
//     Given a function f:R^n -> R^n, and an initial estimate a in R^n, the   //
//     Newton-Raphson method attempts to find a point x in R^n such that      //
//     f(x) = 0.                                                              //
//                                                                            //
//  Arguments:                                                                //
//     void (*f)(double*, double*)                                            //
//        Pointer to a user-defined function of a real n-dimensional vector,  //
//        the first argument, returning a real n-dimensional vector, in the   //
//        second argument.                                                    //
//     void (*df)(double*, double*, double*)                                  //
//        Pointer to a user-defined function which returns the Jacobian of the//
//        function f above, evaluated the first argument, the second argument //
//        is f evaluated at the same point, and the third argument is the     //
//        Jacobian, i.e. the matrix with the i,j component being the partial  //
//        derivative of the i-th component of f with respect to j-th component//
//        of the vector x evaluated at the first argument.  The second        //
//        argument, the value of f at the first argument, in case the first   //
//        derivatives contain terms which include that value.                 //
//     int (*stopping_rule)(double*, double*, int, int),                      //
//        Pointer to a user-defined function which controls the iteration of  //
//        the Newton-Raphson method.  If the stopping rule is non-zero the    //
//        process is halted and if zero then the process continues iterating. //
//        The arguments are: the vector x - x0, f(x), the total number of     //
//        iterations performed, and n the dimension of x.                     //
//     double *a                                                              //
//        On input, a is the initial point to start the iteraction. On output,//
//        a is the final point before the iteration is halted.                //
//     double *fa                                                             //
//        On output, *fa is the vector f(a[]).                                //
//     int    n                                                               //
//        The dimension of a.                                                 //
//                                                                            //
//  Return Values:                                                            //
//    -1    Not enough memory.                                                //
//    -2    Jacobian is singular or ill-formed.                               //
//    Other The return value of the user-supplied Stopping_Rule.              //
//                                                                            //
//  Example:                                                                  //
//     extern void f(double*, double*);                                       //
//     extern void df(double*, double*, double*);                             //
//     extern int Stopping_Rule(double*, double*, int, int);                  //
//     #define N                                                              //
//     double a[N], double fa[N];                                             //
//                                                                            //
//     (your code to initialize the vector a)                                 //
//                                                                            //
//     err = Newton_Raphson_ndim(f, df, Stopping_Rule, a, fa, N);             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

int Newton_Raphson_ndim( void (*f)(double*, double*),
                            void (*df)(double*, double*, double*),
                            int (*Stopping_Rule)(double*, double*, int, int),
                                                 double *a, double *fa, int n)
{
   double* x;
   double *dfa;
   int iteration = 0;
   int err;

   x = (double *) malloc( n * sizeof(double) );
   dfa = (double *) malloc( n * n * sizeof(double) );

   if (dfa == NULL) { free(x); return -1; }

   f(a, fa);
   do {
      df(a, fa, dfa);
      Copy_Vector(x, fa, n);
      if ( Gaussian_Elimination(dfa, n, x) < 0 ) { err = -2; break; }
      Subtract_Vectors(a,a,x,n);
      iteration++;
      f(a,fa);
      err = Stopping_Rule(x, fa, iteration, n);
   } while ( !err );

   free(dfa);
   free(x);
   return err;
}
