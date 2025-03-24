#include <stdio.h>
#include <stdarg.h>
#define MAX 8
#define MIN 1e-6

int Printf( const char* sFormat, ...  ); //<zdeklarowac parametry>
int PrintfV( const char* sFormat, va_list args );
//zadeklarowac PrintfV()

void outDec( int );       // znakowo wypisuje liczbe calk
void outChar( char );     // wypisuje znak  // putchar()
void outStr( char* );     // wypisuje zanakowo string
void outDouble( double ); // wypisuje znakowow liczbe double    0.  (do 8 po kropce)
void outNum( int x );     // wypisuje znakowo liczbe int >0     rekurencyjnie

//----------------------------------
int main( int argc, char* argv[] )
{
  int n  = -0;
  char c = '$';
  double x = 12000000.34500000012;   // nie wiecej jak 8 po pkropce  // .0000012 <=1e-6
  double y = -.12;
  double z = -1.5;
  char*  str = (char*)"to jest string";

  n = Printf( "%s\n%f%c  n=%%d \\ \% /\ny=%f ` ` z=%%f\n%", str, x, c, n, y, z );  //  -> '
  Printf( "\nilosc formatow=%d\n", n );
  return 0;
}
// implementacja uproszczonej funkcji "Printf": %c %d %f %s oraz 
// zamienia (klawisz ~) na '( klawisz ")
// do wypisywania mozna uzyc JEDYNIE putchar() (raz) (poprzez outChar())


//-----------------------------------------------
int Printf( const char* sFormat, ...)
{
  va_list args; // Initialize variable arguments 
  va_start( args, sFormat );// set the pointer at the beggining of the arg list and get the first argument from the args list

  int res = PrintfV( sFormat, args ); // PrintfV

  // Reset variable arguments
  va_end( args );
  return res;
}
//-----------------------------------------------
int PrintfV( const char* sFormat, va_list args )
{
  int liczFormat = 0;
  char c;

  while( ( c=*sFormat++ ) /*c = znak_z_we_stringu*/ )
  {
    switch( c )
    {
    case '%': 
      switch( c = *sFormat++ )
      {
      case 'd': outDec( va_arg(args, int ) ); liczFormat++; break;
      case 'f': outDouble( va_arg(args, double ) ); liczFormat++; break; 
      case 's': outStr( va_arg(args, char* ) ); liczFormat++; break;
      case 'c': outChar( va_arg(args, char ) ); liczFormat++; break;
      default:  outChar( '%' ); 
                if( c != '\0' && c != '%' ) outChar( c ); 
                else *sFormat--; 
                break;
      }		   
      break;

    case '`': c = '\''; // to bez break-a
    default: outChar( c );
    }
  }
  return liczFormat;
}

//-----------------------------------------------
void outChar( char c )    
{
  putchar( c );
}
//-----------------------------------------------
void outStr( char* pStr )     
{
  while( *pStr )
    outChar( *pStr++ );
}
//-----------------------------------------------
void outDec( int x )       
{
  if( x<0 )
  {
    outChar( '-' );
    x = -x;
  }
  else if( !x )  //if (x == 0)
  {
    outChar( '0' ); return;//bo outnum nie wypisze
  }
  outNum( x );
  // wypisac znak jesli trzeba i wykorzystac outNum()
}

//-----------------------------------------------
void outDouble( double x ) 
{
 
  if( x<0 )
    {
      outChar( '-' );
      x = -x;
    }
  
  outDec((int)x);
  outChar('.');
  x = x - (int)x;
  for(int i = 0; i < MAX && x-(int)x>MIN; i++)
  {
    outDec((int)(x *= 10) % 10);

  // wykorzystac outDec()
  // przerwac drukowanie jesli reszta <=1e-6  ewentualnie do  8-miu cyfr po kropce
  }
  }
//-----------------------------------------------
void outNum( int x ) //rekurencyjny  //x>0
{
  if( x > 0 ) {
  outNum( x/10 );
  outChar( x%10 + '0' );
  }
}