/*

Compute n modulo d without division(/) 
and modulo(%) operators, where d is a power of 2 number.

*/


unsigned int getModulo(unsigned int n, unsigned int d)
{
  return ( n & (d-1) );
}     

