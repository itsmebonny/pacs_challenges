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
    size_t m_N;
    bool m_print = false;
    bool m_plot = false;
    bool m_save = true;
    std::array<std::vector<double>, 2> m_sol;

    double step(std::function<double (const double &, const double &)> fun, double x0, double t0, double h, double theta){
        /*
        the step of the numeric method, depends on the paramether theta
        */
        double fn = fun(t0, x0);
        auto fn1 = [&](double x){
            return x - h * theta * fun(t0+h, x) - h * (1 - theta) *  fn - x0;
        };
        double x1 = x0 + h * fn;
        if (x0 == x1){ //because i'm stupid and my interval has a problem with fn = 0
            x1 = x0 + h*fun(t0+h, x0);
        }
        std::tuple<double, bool> zero = apsc::secant <std::function<double (const double &)>> (fn1, x0, x1);

        return std::get<0>(zero);
    };
    void print_solution(void){
        /*
        a simple method to print the solution on the screen
        */
        if(m_sol[0].empty() || m_sol[1].empty()){
            std::cerr << "You need to run the solve method first!" << std::endl;
        }
        else{
            for (size_t i = 0; i < m_sol[0].size(); i++)
            {
                std::cout << m_sol[0][i] << "\t" << m_sol[1][i] << std::endl;
            }
        }
    }
    void save_solution(std::string filename = "solution.csv"){
        /*
        this one stores the solution in a file, if the name changes, must be changed also in plot.p, otherwise make plot won't work
        */
        if ((m_sol[0].empty() || m_sol[1].empty()) || (m_sol[1].size() != m_sol[0].size())){
            std::cerr << "You need to run the solve method first!" << std::endl;
        }
        else{
            std::ofstream solution(filename);
            for (size_t i = 0; i < m_sol[0].size(); i++)
            {
                solution << m_sol[0][i] << "," << m_sol[1][i] << ";" << std::endl;
            }
        }
    }
    
    void plot_solution(void){
        /*
        this method plots the solution, i used it to get familiar with gnuplot
        */
        if(!(m_sol[0].empty() || m_sol[1].empty())){
        Gnuplot gp; 
        gp << "plot" << gp.file1d(std::tie(m_sol[0], m_sol[1])) << "title 'uh'" << std::endl;
        }
        else{
            std::cerr << "The solution is empty! Run the solve method before" << std::endl;
        }
    }
public:
    cauchy_solver(std::function<double (const double &, const double &)> fun, double  x0, double t0, double T, size_t N, bool print = false, bool plot = false, bool save = true)
     : m_fun(fun), m_x0(x0), m_t0(t0), m_T(T), m_N(N), m_print(print), m_save(save), m_plot(plot) {};
    
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

        for (size_t n = 1; n < m_N; n++)
        {
            double un = step(m_fun, m_sol[1].back(), m_sol[0].back(), h, theta);
            m_sol[0].push_back(n*h);
            m_sol[1].push_back(un);
        }
        if(m_save){
            save_solution();
        }
        if(m_plot){
            plot_solution();
        }
        if(m_print){
            print_solution();
        }
        return m_sol;
    }
    
};

#endif //CAUCHY_SOLVER_HH
