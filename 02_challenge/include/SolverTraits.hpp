#ifndef SOLVERTRAITS_HH
#define SOLVERTRAITS_HH

#include <vector>
#include<map>
#include<string>
/*
here i store the various types and the settings of the solver
*/
struct OptionsType
    {
        double tolerance;
        size_t iterations;
    };

typedef double ResultType;
class SolverTraits
{
private:
    OptionsType options;
public:
    SolverTraits() = default;
    SolverTraits(double tol, size_t iters){
        options.tolerance = tol;
        options.iterations = iters;
    };
    void add_tol(double tol){
        options.tolerance = tol;
    }
    void add_iters(size_t iters){
        options.iterations = iters;
    }
    double get_tol(void){
        return options.tolerance;
    }
    size_t get_iters(void){
        return options.iterations;
    }
    SolverTraits(const SolverTraits &rhs):options(rhs.options){};
};

#endif //SOLVERTRAITS_HH