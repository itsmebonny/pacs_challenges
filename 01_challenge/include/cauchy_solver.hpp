#ifndef CAUCHY_SOLVER_HH
#define CAUCHY_SOLVER_HH
#include <functional>
#include <array>
#include <vector>
#include "basicZeroFun.hpp"
#include<tuple>
#include <string>
#include <iostream>
#include <fstream>
#include "gnuplot-iostream.hpp"

class cauchy_solver
{
private:
    std::function<double (const double &, const double &)> m_fun;
    double m_x0;
    double m_t0;
    double m_T;
    double m_N;
    std::array<std::vector<double>, 2> m_sol;

    double crank_nicolson(std::function<double (const double &, const double &)> fun, double x0, double t0, double h){
        double fn = fun(t0, x0);
        std::cout << fn << std::endl;
        auto fn1 = [&](double x){
            return x - h * 0.5 * (fun(t0+h, x) + fn) - x0;
        };
        double x1 = x0 + h * fn;
        if (x0 == x1){ //because i'm stupid
            x1 = x0 + h*fun(t0+h, x0);
        }
        std::tuple<double, bool> zero = apsc::secant <std::function<double (const double &)>> (fn1, x0, x1);

        std::cout << "zero at : " << std::get<1>(zero) << std::endl;
        return std::get<0>(zero);
    };

public:
    cauchy_solver(std::function<double (const double &, const double &)> fun, double  x0, double t0, double T, double N)
     : m_fun(fun), m_x0(x0), m_t0(t0), m_T(T), m_N(N) {};
    
    std::array<std::vector<double>, 2> solve(void){
        auto h = (m_T-m_t0)/m_N;
        m_sol[0].push_back(m_t0);
        m_sol[1].push_back(m_x0);

        for (size_t n = 1; n < m_N; n++)
        {
            double un = crank_nicolson(m_fun, m_sol[1].back(), m_sol[0].back(), h);
            std::cout << "un: " << un << std::endl;
            m_sol[0].push_back(n*h);
            m_sol[1].push_back(un);
        }
        return m_sol;
    }
    void save_solution(std::string filename){
        if(m_sol.empty()){
            std::cerr << "You need to run the solve method first!" << std::endl;
        }
        std::ofstream solution(filename);
        bool flag = true;
        for (auto i : m_sol)
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
    }
};

#endif //CAUCHY_SOLVER_HH
