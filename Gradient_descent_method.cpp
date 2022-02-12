#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

constexpr double initial_x = 1.0;
constexpr double initial_y = 1.0;
constexpr double threshold = 0.00001;
constexpr double raito = 0.40;//raito:係数の減衰比率
constexpr double coeff = 0.001;

struct grad{
    double x_grad;
    double y_grad;
};

auto func(double x, double y){
    return x * x + y * y + x * y - 2 * x;
}

inline auto calc_grad(double x, double y)-> grad {
    return {2 * x + y - 2, 2 * y + x};
}

inline auto Armijo_line_serch(double x, double y, grad grad, double alpha, double coeff, double raito){
    for(int i = 0; i< 10; i++){
        if(func(x - grad.x_grad * alpha, y - grad.y_grad * alpha) <= func(x, y) + alpha * coeff * (grad.x_grad * grad.x_grad + grad.y_grad * grad.y_grad) ) break;
        else alpha = raito * alpha;
    }
    return alpha;
}

int main(int ac, char* av[]){
    double x = initial_x;
    double y = initial_y;
    double alpha_initial = 1.0;
    double alpha;
    bool loop_flag = true;
    grad grad;

    ofstream fout (av[1]);
    if(!fout){
        cout << "Can't open the file !" << endl;
        exit(8);
    }
    fout << "initial x = " << x << " initila y = " << y << " f(x, y) = " << func(x, y) <<endl;

    while(loop_flag){
        grad = calc_grad(x, y);
        alpha = Armijo_line_serch(x, y, grad, alpha_initial, coeff, raito);
        if((-threshold < grad.x_grad && grad.x_grad < threshold) && (-threshold < grad.y_grad && grad.y_grad < threshold)) loop_flag = false;
        fout << "x = " << x << " y = " << y << " f(x, y) = " << func(x, y) <<endl;
        x = x - alpha * grad.x_grad;
        y = y - alpha * grad.y_grad;
    }
    cout << "x = " << x << " y = " << y << " Extream value f(x, y) = " << func(x, y) <<endl;

    fout.close();
    return 0;
}
