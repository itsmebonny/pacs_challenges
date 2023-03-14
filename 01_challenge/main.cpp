#include "cauchy_solver.hpp"
#include <iostream>
#include <fstream>
#include "gnuplot-iostream.hpp"

double function (const double &t, const double &y){
    return -t*std::exp(-y);
}
int main(){
    std::ofstream solution("solution.csv");
    std::function<double (const double &, const double &)> fun = function;
    double x0 = 0;
    cauchy_solver test(fun, x0, 0, 1, 100);
    auto sol = test.solve();
    bool flag = true;
    for (auto i : sol)
    {
        if (flag){
            std::cout << "tn: ";
            solution << "tn: ";
        }
        else{
            std::cout << "un: ";
            solution << "un: ";
        }
        for (auto j : i)
        {
            std::cout << j << ", ";
            solution << j << ", ";
        }
        std::cout << std::endl;
        solution << std::endl;
        flag = false;
    }
    Gnuplot gp; 
    gp << "plot" << gp.file1d(std::tie(sol[0], sol[1])) << "title 'uh'" << std::endl;
}