////////////////////////////////////////////////////////////////////////////////
// File: subtract_vectors.c                                                   //
// Routine(s):                                                                //
//    Subtract_Vectors                                                        //
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  void Subtract_Vectors(double *w, double *u, double *v, int n)             //
//                                                                            //
//  Description:                                                              //
//     Subtract the vector v from the vector u to form the vector w, i.e.     //
//     w[i] = u[i] - v[i].  All vectors should be declared as "double [n]"    //
//     in the calling routine.                                                //
//                                                                            //
//  Arguments:                                                                //
//     double w[]   Resultant vector w = u - v.                               //
//     double u[]   The minuend.                                              //
//     double v[]   The subtrahend.                                           //
//     int    n     The number of components of u, v, and w.                  //
//                                                                            //
//  Return Values:                                                            //
//     void                                                                   //
//                                                                            //
//  Example:                                                                  //
//     #define N                                                              //
//     double u[N],  v[N], w[N];                                              //
//                                                                            //
//     (your code to initialize the vector u and v)                           //
//                                                                            //
//     Subtract_Vectors(w, u, v, N);                                          //
//     printf("The vector w = u - v is \n"); ...                              //
////////////////////////////////////////////////////////////////////////////////
void Subtract_Vectors(double w[], double u[], double v[], int n) 
{
   register int i;

   for (i = 0; i < n; i++) w[i] = u[i] - v[i];
}
