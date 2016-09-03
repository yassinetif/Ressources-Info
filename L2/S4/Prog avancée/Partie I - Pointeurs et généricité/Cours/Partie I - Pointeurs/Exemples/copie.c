extern
char  * copie( char * cible , char * source , int n ) 
{
  char * d = source ;
  while( n-- ) *cible++ = *source++ ;
  return d ;
}
