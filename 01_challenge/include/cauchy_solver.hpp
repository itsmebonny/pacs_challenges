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
#include <set>

class cauchy_solver
{
private:
    std::function<double (const double &, const double &)> m_fun;
    double m_x0;
    double m_t0;
    double m_T;
    double m_N;
    std::array<std::vector<double>, 2> m_sol;

    double step(std::function<double (const double &, const double &)> fun, double x0, double t0, double h, double theta){
        double fn = fun(t0, x0);
        auto fn1 = [&](double x){
            return x - h * theta * fun(t0+h, x) - h * (1 - theta) *  fn - x0;
        };
        double x1 = x0 + h * fn;
        if (x0 == x1){ //because i'm stupid
            x1 = x0 + h*fun(t0+h, x0);
        }
        std::tuple<double, bool> zero = apsc::secant <std::function<double (const double &)>> (fn1, x0, x1);

        return std::get<0>(zero);
    };

public:
    cauchy_solver(std::function<double (const double &, const double &)> fun, double  x0, double t0, double T, double N)
     : m_fun(fun), m_x0(x0), m_t0(t0), m_T(T), m_N(N) {};
    
    std::array<std::vector<double>, 2> solve(double theta = 0.5){
        if (theta > 1 && theta < 0){
            std::cerr << "theta must be inside [0,1]!" << std::endl;
            std::cout << "Using theta = 0.5" << std::endl;;
            theta = 0.5;
        }
        std::cout << "theta = " << theta << std::endl;
        auto h = (m_T-m_t0)/m_N;
        m_sol[0].push_back(m_t0);
        m_sol[1].push_back(m_x0);
        std::cout << 0 << " un: " << m_x0 << std::endl;

        for (size_t n = 1; n < m_N; n++)
        {
            double un = step(m_fun, m_sol[1].back(), m_sol[0].back(), h, theta);
            std::cout <<n << " un: " << un << std::endl;
            m_sol[0].push_back(n*h);
            m_sol[1].push_back(un);
        }
        
        return m_sol;
    }
    void print_solution(void){
        if(m_sol[0].empty() || m_sol[1].empty()){
            std::cerr << "You need to run the solve method first!" << std::endl;
        }
        else{
            bool flag = true;
            for (auto i : m_sol){
                if (flag){
                    std::cout << "tn: ";
                }
                else{
                    std::cout << "un: ";
                }
                for (auto j : i)
                {
                    std::cout << j << ", ";
                    if (i.back() == j){
                        std::cout << j;
                    }
                }
                std::cout << std::endl;
                flag = false;
            }
        }
    }
    void save_solution(std::string filename){
        if(m_sol[0].empty() || m_sol[1].empty()){
            std::cerr << "You need to run the solve method first!" << std::endl;
        }
        else{
            std::ofstream solution(filename);
            bool flag = true;
            for (auto i : m_sol){
                if (flag){
                    solution << "tn: ";
                }
                else{
                    solution << "un: ";
                }
                for (auto j : i)
                {
                    solution << j << ", ";
                    if (i.back() == j){
                        solution << j;
                    }
                }
                solution << std::endl;
                flag = false;
            }
        }
    }
    void plot(void){
        if(!(m_sol[0].empty() || m_sol[1].empty())){
        Gnuplot gp; 
        gp << "plot" << gp.file1d(std::tie(m_sol[0], m_sol[1])) << "title 'uh'" << std::endl;
        }
        else{
            std::cerr << "The solution is empty! Run the solve method before" << std::endl;
        }
    }
};

#endif //CAUCHY_SOLVER_HH
