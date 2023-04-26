#ifndef SOLVERFACTORY_HH
#define SOLVERFACTORY_HH
#include "SolverTraits.hpp"
#include "SolverBase.hpp"
#include <memory>
using SolverPtr = std::unique_ptr<SolverBase>;

class SolverFactory
{
private:
    Function m_f;
    SolverTraits m_traits;
public:
    //constructor for the factory, with possibility to edit parameters
    SolverFactory(Function f, double tolerance = 1e-4, size_t iters = 150):m_f(f){
        m_traits.add_iters(iters);
        m_traits.add_tol(tolerance);
    };
    //operator for the method
    SolverPtr operator() (std::string method){
        if (method == "QuasiNewton" || method == "quasinewton" || method == "qn" || method == "QN"){
            SolverQN res(m_f, m_traits);
            SolverPtr res_ptr = std::make_unique<SolverQN>(res);
            return res_ptr;
        }
        else if (method == "Secant" || method == "secant" || method == "Sec" || method == "sec"){
            SolverSecant res(m_f, m_traits);
            SolverPtr res_ptr = std::make_unique<SolverSecant>(res);
            return res_ptr;
        }
        else if (method == "Bisection" || method == "bisection" || method == "bisec" || method == "bs"){
            SolverBisection res(m_f, m_traits);
            SolverPtr res_ptr = std::make_unique<SolverBisection>(res);
            return res_ptr;
        }
        
    }
};



#endif //SOLVERFACTORY_HH