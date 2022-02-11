#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

constexpr double alpha = 0.384615;
constexpr double initial_x = 1.0;
constexpr double initial_y = 1.0;
constexpr double threshold = 0.00001;

struct grad{
    double x_grad;
    double y_grad;
};

auto func(double x, double y){
    return x * x + y * y + x * y - 2 * x;
}

auto calc_grad(double x, double y)-> grad {
    return {2 * x + y - 2, 2 * y + x};
}

int main(int ac, char* av[]){
    double x = initial_x;
    double y = initial_y;
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
        x = x - alpha * grad.x_grad;
        y = y - alpha * grad.y_grad;
        if((-threshold < grad.x_grad && grad.x_grad < threshold) && (-threshold < grad.y_grad && grad.y_grad < threshold)) loop_flag = false;
        fout << "x = " << x << " y = " << y << " f(x, y) = " << func(x, y) <<endl;
    }
    cout << "x = " << x << " y = " << y << " Extream value f(x, y) = " << func(x, y) <<endl;

    fout.close();
    return 0;
}
