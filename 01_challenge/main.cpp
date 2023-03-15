#include "include/cauchy_solver.hpp"
#include <iostream>
#include <fstream>
#include "gnuplot-iostream.hpp"

double function (const double &t, const double &y){
    return -t*std::exp(-y);
}
int main(){
    
    std::function<double (const double &, const double &)> fun = function;
    double x0 = 0;
    cauchy_solver test(fun, x0, 0, 1, 100);
    auto sol = test.solve();
    test.save_solution("test.txt");
    
    Gnuplot gp; 
    gp << "plot" << gp.file1d(std::tie(sol[0], sol[1])) << "title 'uh'" << std::endl;
}