Simple object oriented solver for root finding. Based on three methods:
- Bisection
- QuasiNewton
- Secant
Each method can be accessed by the ```()``` operator, simply by writing the method name (case-insensitive) inside the operator to access the ```solve``` method offered by each solver. 
Inside the solve method you need to pass the interval for the Bisection and Secant method, while for QuasiNewton a starting point and a derivative step.

To quickly check the code, just launch the ```compile_and_run.sh``` script, otherwise using ```make all``` you can build it and then launch it normally.
