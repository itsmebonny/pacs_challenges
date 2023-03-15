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
    cauchy_solver test1(fun, x0, 0, 1, 100);
    cauchy_solver test2(fun, x0, 0, 1, 100);
    cauchy_solver test3(fun, x0, 0, 1, 100);
    auto sol1 = test1.solve(1);
    std::cout << sol1[0].size() << std::endl;
    auto sol2 = test2.solve(0);
    std::cout << sol2[0].size() << std::endl;
    auto sol3 = test3.solve(0.5);
    std::cout << sol3[0].size() << std::endl;
    test1.save_solution("final.csv");
    //test.print_solution();
    Gnuplot gp; 
    gp << "plot" 
    << gp.file1d(std::tie(sol1[0], sol1[1])) << "w lp pt 1 title 'bw eu',"
    << gp.file1d(std::tie(sol2[0], sol2[1])) << "w lp pt 2 title 'fw eu',"
    << gp.file1d(std::tie(sol3[0], sol3[1])) << "w lp pt 3 title 'cn'" 
    << std::endl;
    }