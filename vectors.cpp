#include <cstdlib>  // plain C
#include <cmath>
#include <vector>

#include <iostream>  //  stream IO
#include <fstream>   // stream file IO
#include <iomanip>   // to format the output
using namespace std;


#define Na 250
#define max_s .25
#define L 18.
#define KbT .15
#define e 2.7182818284590452353602874713527
#define mindist 1e-10
#define sig 3.4e-10
#define eps 1.65e-21
using namespace std;



typedef double Doub;
typedef int Int;
typedef unsigned int Uint;
typedef unsigned long long Ullong;






//----------some simple code to test-----------//
void change_element(vector< vector<float> >* a){
  a->at(2)[0] = 1;
  return;
}
//-------------------------------------------//

int main(){

  vector<float> tmp(1);
  vector< vector<float> > p( 3, tmp);
  p[0][0] = 0;
  cout << p[0][0] << endl;
  change_element(&p);
  cout << p[2][0] << endl;
  cout << p[1][0] << endl;
  return( EXIT_SUCCESS );


  
}

