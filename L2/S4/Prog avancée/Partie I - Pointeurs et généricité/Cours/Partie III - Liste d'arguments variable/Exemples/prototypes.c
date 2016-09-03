void f1( int x, int y , ... )   /* OK */
{ 
}

void f2( char * format , ... )   /* OK */
{
} 

/* error: syntax error before ',' token */
void f3( , ... ) /* KO */
{

}
