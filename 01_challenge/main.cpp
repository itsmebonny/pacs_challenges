#include "include/cauchy_solver.hpp"
#include "GetPot"

double function (const double &t, const double &y){
    return -t*std::exp(-y);
}
int main(int argc, char* argv[]){
    

    GetPot ifl("parameters.pot");
    size_t N = ifl("N", 150);
    std::function<double (const double &, const double &)> fun = function;
    double x0 = ifl("x0", 0);
    double theta = ifl("theta", 0.5);
    cauchy_solver test(fun, x0, 0, 1, N);
    auto sol1 = test.solve(theta);
    test.save_solution();
    test.print_solution();
    }