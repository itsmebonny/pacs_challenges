#include "include/cauchy_solver.hpp"
#include <iostream>
#include <fstream>
#include "gnuplot-iostream.hpp"

double function (const double &t, const double &y){
    return -t*std::exp(-y);
}
int main(int argc, char* argv[]){
    
    std::function<double (const double &, const double &)> fun = function;
    double x0 = 0;
    cauchy_solver test(fun, x0, 0, 1, 100);
    auto sol1 = test.solve(1);
    test.save_solution();
    test.print_solution();
    }