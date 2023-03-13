#ifndef CAUCHY_SOLVER_HH
#define CAUCHY_SOLVER_HH
#include <functional>
#include <array>
#include <vector>
#include "basicZeroFun.hpp"
#include<tuple>
class cauchy_solver
{
private:
    std::function<double (const double &, const double &)> m_fun;
    double m_x0;
    int m_t0;
    int m_T;
    int m_N;
    double m_h = m_T/m_N;
    std::array<std::vector<double>, 2> m_sol;
public:
    cauchy_solver(std::function<double (const double &, const double &)> fun, double  x0, int t0, int T, int N):m_fun(fun), m_x0(x0), m_t0(t0), m_T(T), m_N(N){};
    double crank_nicolson(std::function<double (const double &, const double &)> fun, double x0, double t0, double h){
        double fn = fun(x0, t0);
        auto fplus1 = [&](double x){
            return x - h * 0.5 * (fun(x, t0+h) + fn) + x0;
        };
        double x1 = x0 * h + fn;
        std::tuple<double, bool> zero = apsc::secant <std::function<double (const double &)>> (fplus1, x0, x1);
        return std::get<0>(zero);
    };
    std::array<std::vector<double>, 2> solve(void){
        m_sol[0].push_back(0);
        m_sol[1].push_back(m_x0);
        for (size_t n = 1; n < m_N; n++)
        {
            m_sol[0].push_back(n*m_h);
            double un = crank_nicolson(m_fun, m_sol[1].back(), m_sol[0].back(), m_h);
            m_sol[1].push_back(un);
        }
        return m_sol;
    }
};

#endif //CAUCHY_SOLVER_HH