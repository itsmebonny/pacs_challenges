#include "include/cauchy_solver.hpp"
#include "GetPot"

double function (const double &t, const double &y){
    /*
    the function of the problem
    */
    return -t*std::exp(-y);
}
int main(){
    GetPot ifl("parameters.pot"); //parameters stored here, head to the file to see what those variables are
    size_t N = ifl("N", 150);
    std::function<double (const double &, const double &)> fun = function;
    double x0 = ifl("x0", 0);
    double theta = ifl("theta", 0.5);
    bool print = ifl("print_solution", false), plot = ifl("plot_solution", false), save = ifl("save_solution", true);
    cauchy_solver obj(fun, x0, 0, 1, N, print, plot, save);
    obj.solve(theta);
    return 0;
    }