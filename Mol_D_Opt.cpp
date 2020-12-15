/*  AEP 4380 Final Project
    Monte Carlo Molecular Dynamics in 3D with optimized algorithm
    Run on a core i9 with g++ 9.1.0 64 bit
    Vineet Kamat 19-sep-2020 
*/

#include <cstdlib>  // plain C
#include <cmath>
#include <vector>

#include <iostream>  //  stream IO
#include <fstream>   // stream file IO
#include <iomanip>   // to format the output
#define Na 100
#define max_s .15
#define L 4.
#define KbT .15
#define mindist 1e-10
#define sig 3.4e-10
#define eps 1.65e-21
using namespace std;



typedef double Doub;
typedef int Int;
typedef unsigned int Uint;
typedef unsigned long long Ullong;



// Code from Numerical Recipes Press et. al. //
struct Ranq1 {
    Ullong v;
    Ranq1(Ullong j) : v(4101842887655102017LL) {
        v ^= j;
        v = int64(); 
    }
    inline Ullong int64() {
        v ^= v >> 21; v ^= v << 35; v ^= v >> 4;
        return v * 2685821657736338717LL;
    }
    inline Doub doub() { return 5.42101086242752217E-20 * int64(); }
    inline Uint int32() { return (Uint)int64(); }
};
//-------------------------------------------//


double get_r_sqrd(double x1,double x2,double y1,double y2,double z1,double z2){
  return (x1-x2)*(x1-x2)
          + (y1-y2)*(y1-y2)
          + (z1-z2)*(z1-z2);
}
double get_E(double r_sqrd){
  return 4*(1/(r_sqrd*r_sqrd*r_sqrd)*((1/(r_sqrd*r_sqrd*r_sqrd))-1));
}

void update_energy(Ranq1 rng, vector< vector<double> >* E, int atom,
                    double* x, double* xnew, double* y, double* ynew,
                    double* z, double* znew){
                      
    double r_sqrd, difference = 0;
    for(int i=0;i<Na;i++){
      r_sqrd = get_r_sqrd(xnew[i],xnew[atom],ynew[i],ynew[atom],znew[i],znew[atom]);
      if(i<atom){
        if(r_sqrd < mindist){
          difference += E->at(atom)[i] - 1e20;
        }else{
          difference += E->at(atom)[i] - get_E(r_sqrd);
        }
      }else if(i>atom){
        if(r_sqrd < mindist){
          difference += E->at(i)[atom] - 1e20;
        }else{
          difference += E->at(i)[atom] - get_E(r_sqrd);
        }
      }
    }


    double rand = rng.doub();
    if(difference>=0 || rand < exp(difference/KbT)){
      

      // update the Energies and vectors
      for(int i=0;i<Na;i++){

        r_sqrd = (xnew[i]-xnew[atom])*(xnew[i]-xnew[atom]) + (ynew[i]-ynew[atom])*(ynew[i]-ynew[atom]) +
                  (znew[i]-znew[atom])*(znew[i]-znew[atom]);
        if(i<atom){
          if(r_sqrd < mindist){
            E->at(atom)[i] = 1e20;
          }else{
            E->at(atom)[i] = 4*(1/(r_sqrd*r_sqrd*r_sqrd)*((1/(r_sqrd*r_sqrd*r_sqrd))-1));
          }
        }else if(i>atom){
          if(r_sqrd < mindist){
            E->at(i)[atom] = 1e20;
          }else{
            E->at(i)[atom] = 4*(1/(r_sqrd*r_sqrd*r_sqrd)*((1/(r_sqrd*r_sqrd*r_sqrd))-1));
          }
        }
      }
      x[atom] = xnew[atom];
      y[atom] = ynew[atom];
      z[atom] = znew[atom];
    }else{
      xnew[atom] = x[atom];
      ynew[atom] = y[atom];
      znew[atom] = z[atom];
    }
}

double get_energy(vector< vector<double> > E){
  double to_return = 0;
  for(int i=0;i<Na;i++){
    for(int j=0;j<i;j++){
      to_return += E[i][j];
    }
  }
  return to_return;
}


int main(){


  //declare functions
  double get_r_sqrd(double x1,double x2,double y1,double y2,double z1,double z2);
  double get_E(double r_sqrd);
  void update_energy(Ranq1 rng, vector< vector<double> >* E, int atom,
                    double* x, double* xnew, double* y, double* ynew,
                    double* z, double* znew);

  // Files to write
  ofstream RNG, RNG_pairs, start, at_e3, at_e4, at_e5, at_e6, Evals;       // output of random numbers
  RNG.precision(9); RNG_pairs.precision(9); start.precision(9); Evals.precision(9);
  at_e3.precision(9); at_e4.precision(9); at_e5.precision(9); at_e6.precision(9);
  start.open("start.txt");
  at_e3.open("at_e3.txt"); at_e4.open("at_e4.txt");
  at_e5.open("at_e5.txt"); at_e6.open("at_e6.txt");
  Evals.open("Evals.txt");

  
  Ranq1 rng(17);    // Init RNG


  double* x = new double[Na];
  double* xnew = new double[Na];
  double* y = new double[Na];
  double* ynew = new double[Na];
  double* z = new double[Na];
  double* znew = new double[Na];
  vector<double> tmp(Na);
  vector< vector<double> > E(Na,tmp);    //non-dimensionalized E





  // Initialize positions
  for(int i=0;i<Na;i++){
    x[i] = L*rng.doub();
    xnew[i] = x[i];
    y[i] = L*rng.doub();
    ynew[i] = y[i];
    z[i] = L*rng.doub();
    znew[i] = z[i];
    start << x[i] << setw(20) << y[i] << setw(20) << z[i] <<endl;
  }



  // Initialize energies
  double r_sqrd;
  for(int i=0;i<Na;i++){
    for(int j=0;j<i;j++){
      r_sqrd = get_r_sqrd(x[i],x[j],y[i],y[j],z[i],z[j]);
      if(r_sqrd < mindist){
        E[i][j] = 1e20;
      } else{
        E[i][j] = get_E(r_sqrd);
      }
    }
  }

  int atom; // which atom to move
  double dir; // up or down
  double cardinal; // x, y, z
  double amount; // distance by which to move


  for(int i=0;i<10000000;i++){

    // select and update position of random atom
    atom = rng.int32()%Na;
    cardinal = rng.doub();
    dir = rng.doub();
    amount = rng.doub();
    if(dir<.5){          // Move up
      if(cardinal<.3333333){
        xnew[atom] = min((xnew[atom] + max_s*amount),L);
      }else if(cardinal<.666666){
        ynew[atom] = min((ynew[atom] + max_s*amount),L);
      }else{
        znew[atom] = min((znew[atom] + max_s*amount),L);
      }
    }else{               // Move down
      if(cardinal<.3333333){
        xnew[atom] = max((xnew[atom] - max_s*amount),0.);
      }else if(cardinal<.666666){
        ynew[atom] = max((ynew[atom] - max_s*amount),0.);
      }else{
        znew[atom] = max((znew[atom] - max_s*amount),0.);
      }
    }

    

    // write file for 1000 iterations
    if(i == 1000){
      for(int i=0;i<Na;i++){
        at_e3 << x[i] << setw(20) << y[i] << setw(20) << z[i] << endl;
      }
    }

    // write file for 10000 iterations
    if(i == 10000){
      cout<< "10000"<< endl;
      for(int i=0;i<Na;i++){
        at_e4 << x[i] << setw(20) << y[i] << setw(20) << z[i] << endl;
      }
    }

    // write file for 100000 iterations
    if(i == 100000){
      cout<< "100000"<< endl;
      for(int i=0;i<Na;i++){
        at_e5 << x[i] << setw(20) << y[i] << setw(20) << z[i] << endl;
      }
    }


    if(i%2000==0 && i!= 0){
      Evals << i << setw(20) << get_energy(E) << endl;
    }
    
    
    update_energy(rng, &E, atom, x, xnew, y, ynew, z, znew);


    
  }

  cout << get_energy(E) << endl;

  // write file for 1000000 iterations
  for(int i=0;i<Na;i++){
    at_e6 << x[i] << setw(20) << y[i] << setw(20) << z[i] << endl;
  }

  

  return( EXIT_SUCCESS ); 
} // end main()
