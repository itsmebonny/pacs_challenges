#ifndef SOLVERBASE_HH
#define SOLVERBASE_HH
#include <iostream>
#include "SolverTraits.hpp"
#include <cmath>
#include<functional>
#include <limits>
using Function = std::function<double(double)>;
/*
class of root finders based on different methods
*/


class SolverBase
{
protected:
    Function m_f;
    SolverTraits traits;
    
public:
    SolverBase(Function f, double tolerance = 1e-8, size_t iterations = 150):m_f(f){
        traits.add_tol(tolerance);
        traits.add_iters(iterations);
    };
    SolverBase(Function f, SolverTraits traits):m_f(f), traits(traits){};
    virtual ResultType solve(double start, double end) = 0;
};


double derivative (Function f, double x, double h){
    // evaluates FD derivative
    return (f(x+h) - f(x))/h;
}
class SolverQN : public SolverBase
{
public:
    SolverQN(Function f):
        SolverBase(f){};
    SolverQN(Function f, SolverTraits traits):SolverBase(f, traits){};
    ResultType solve(double start, double step) override {
        double x0 = start, h = step;
        size_t iter = 0, max_it = traits.get_iters();
        double tol = traits.get_tol();
        double residual = std::abs(m_f(x0)), check = residual * tol;
        size_t count = 0;
        
        while (check < residual && iter < max_it)
        {
            iter++;
            double temp = x0-m_f(x0)/derivative(m_f, x0, h);
            double ytemp = m_f(temp);
            residual = std::abs(m_f(temp));
            x0 = temp;
        }
        ResultType res = x0;
        return res;
    }
};



class SolverSecant : public SolverBase
{
public:
    SolverSecant(Function f):
        SolverBase(f){};
    SolverSecant(Function f, SolverTraits traits):SolverBase(f, traits){};
    ResultType solve(double start, double end) override {
        double x0 = start, x1 = end;
        size_t iter = 0, max_it = traits.get_iters();
        double tol = traits.get_tol();
        double residual = std::abs(m_f(x0)), check = residual * tol;
        size_t count = 0;
        while (check < residual && iter < max_it)
        {
            iter++;
            double y0 = m_f(x0), y1 = m_f(x1);
            double temp = x0-y0*(x1-x0)/(y1 - y0);
            double ytemp = m_f(temp);
            residual = std::abs(m_f(temp));
            x0 = x1;
            x1 = temp;
        }
        ResultType res = x1;
        return res;
    }
};

class SolverBisection : public SolverBase
{    
public:
    SolverBisection(Function f):SolverBase(f){};
    SolverBisection(Function f, SolverTraits traits):SolverBase(f, traits){};
    ResultType solve (double start, double end) override {
        double x0 = start, x1 = end, y0 = m_f(start), y1 = m_f(end);
        if(y0 * y1 < 0){
                double delta = x1-x0, xn = x0, yn = y0;
                while (std::abs(delta) > 2*traits.get_tol())
                {
                    xn = (x0 + x1) / 2;
                    yn = m_f(xn);
                    if (yn * y0 < 0){
                        y1 = yn;
                        x1 = xn;
                    }
                    else {
                        y0 = yn;
                        x0 = xn;
                    }
                    delta = delta = x1-x0;
                }
            return (x0+x1)/2;
        }
        else{
            std::cerr << "invalid interval" << std::endl;
            return std::numeric_limits<ResultType>::quiet_NaN();
        }
    }
};


#endif //SOLVERBASE_HH