#include"include/SolverFactory.hpp"
#include<iostream>
#include<functional>

constexpr double pi = 3.14159265359;
double function(double x){
        return 0.5 - std::exp(pi*x);
    }
int main() {
    std::function<double(double)> fun = function;
    SolverFactory factory(fun);
    ResultType res = factory("sec")->solve(-1, 0.5);
    std::cout << "result " << res << std::endl;
    return 0;
}