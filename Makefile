CC = g++
CFLAG = -O4 -Wall

all: gradient_descent_method

gradient_descent_method: Gradient_descent_method.cpp
						$(CC) $(CFLAG) Gradient_descent_method.cpp -o gradient_descent_method

clean:
		rm -f gradient_descent_method *.o*~
