#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

const int  n = 2;
const double eps = 0.0000000005;

double func (double x, double y) {
   //return (4*x*x - 6*x*y - 34*x + 5*y*y + 42*y + 7);
   return (x*x*x + 3*x * y*y - 15*x - 12*y + 1);
}

//Via wiki Метод Нелдера — Мида (9 steps)
int main () {

   double x[n + 5], y[n + 5];
   double conv = 1000;
   long int num_iter = 0;

   //step 1
   //(Note from Wiki) Метод находит локальный экстремум и может «застрять» в одном из них. 
   //                 Если всё же требуется найти глобальный экстремум, 
   //                 можно пробовать выбирать другой начальный симплекс. 
   x[0] = 5;  y[0] = 5;
   x[1] = 2; y[1] = 2;
   x[2] = 3; y[2] = 3;

   double alpha = 1, betta = 0.5, gamma = 2;
   int h, l, g, 
      c = n + 1, 
      r = n + 2, 
      e = n + 3, 
      s = n + 4;

   while (conv > eps) {
      
      num_iter++;

      //step 2
      h = 0;
      l = 0;
      g = 0;
      double max = func(x[0], y[0]);
      double min = func(x[0], y[0]);

      for (int k = 1; k <= n; k ++) {
         
         if (func(x[k], y[k]) < min) {
            min = func(x[k], y[k]);
            l = k;
         }
         if (func(x[k], y[k]) > max) {
            max = func(x[k], y[k]);
            h = k;
         }
      }

      max = func(x[0], y[0]);
      for (int k = 1; k <= n; k ++) {
         if ((func(x[k], y[k]) > max) && (k != h)) {
            max = func(x[k], y[k]);
            g = k;
         }
      }

      //step 3
      x[c] = (x[0] + x[1] + x[2] - x[h]) / n;
      y[c] = (y[0] + y[1] + y[2] - y[h]) / n;

      //step 4
      x[r] = (1 + alpha) * x[n + 1] - alpha * x[h];
      y[r] = (1 + alpha) * y[n + 1] - alpha * y[h];

      //step 5
      if (func(x[r], y[r]) < func(x[l], y[l])) {
         
         x[e] = (1 - gamma)*x[c] + gamma * x[r];
         y[e] = (1 - gamma)*y[c] + gamma * y[r];

         if (func(x[e], y[e]) < func(x[r], y[r])) {
            x[h] = x[e];
            y[h] = y[e];
         }
         else {
            x[h] = x[r];
            y[h] = y[r];
         }
      }
      else {
   
         if ( func(x[g], y[g]) < func(x[r], y[r]) ) {
            
            if ( func(x[r], y[r]) < func(x[h], y[h]) ) {
               x[h] = x[r];
               y[h] = y[r];
            }

            //step 6
            x[s] = betta * x[h] + (1 - betta) * x[c];
            y[s] = betta * y[c] + (1 - betta) * y[c];
         
            //step 7
            if ( func(x[s], y[s]) < func(x[h], y[h]) ) {
               x[h] = x[s];
               y[h] = y[s];
            }
            else { //step 8
               for (int k = 0; k < n; k++) {
                  x[k] = x[l] + 0.5 * (x[k] - x[l]);
                  y[k] = y[l] + 0.5 * (y[k] - y[l]);
               }
            }
         }
         else {
            x[h] = x[r];
            y[h] = y[r];
         }
      }

      //step 9
      float conv1 = 0, conv2 = 0;
      for (int k = 0; k < n + 1; k++) {
         conv1 += func(x[k], y[k]);
         conv2 += func(x[k], y[k]) * func(x[k], y[k]);
      }
      conv = conv2 - conv1 * conv1 / (n + 1);
      conv /= (n + 1);
   
   }

   cout << "x = " << x[0] << endl;
   cout << "y = " << y[0] << endl;
   cout << "Extrem. = " << func(x[0], y[0]) << endl;
   cout << "Iter. count = " << num_iter << endl;

}
