#include <iostream>
#include <vector>
#include <utility>
#include <iomanip>

double f(double x, double y) {
  return x/(y - x*x); //RHS of ODE y'=f(x,y)
}

//Coefficients as defined in classical RKE4 method
double k1(double x, double y, double h) {
  return f(x, y);
}

double k2(double x, double y, double h) {
  return f(x + h/2, y + h/2*k1(x,y, h));
}

double k3(double x, double y, double h) {
  return f(x + h/2, y + h/2*k2(x, y, h));
}

double k4(double x, double y, double h) {
  return f(x + h, y + h*k3(x, y, h));
}
///////////////////////////////////////////////////

std::vector<std::pair<double,double>> RKE4_eval(double x0, double y0, int n, double x_in, double x_fin);

std::ostream& operator<<(std::ostream& stream, std::vector<std::pair<double,double>> v) {
	int count = 1;
	for(auto &item : v)
	{
		stream<<"x_"<<count<<": "<<item.first<<std::setprecision(4)<<std::endl;
		stream<<"y_"<<count<<": "<<item.second<<std::setprecision(4)<<std::endl;
		count++;
	}
	return stream;
} 

int main() {
	//Initial conditions y_(x0)=y0
	double x0 = 1.0;
	double y0 = 1.5;
	//Grid size
	int n = 10;
	//Interval of solution
	double x_in = 1.0;
	double x_fin = 2.0;

	std::cout << RKE4_eval(x0, y0, n, x_in, x_fin);
}

std::vector<std::pair<double,double>> RKE4_eval(double x0, double y0, int n, double x_in, double x_fin) {
  	std::vector<std::pair<double,double>> result;
  	double x = x0;                         
  	double y = y0;
  	double h = (x_fin - x_in)/n;

  	result.push_back(std::make_pair(x,y));

  	for(int i = 1; i <= n; ++i) {
      		x += h;
    		y += h/6*(k1(x-h, y, h) + 2*k2(x-h, y, h) + 2*k3(x-h, y, h) + k4(x-h, y, h));
    		result.push_back(std::make_pair(x,y));
  	}
  	return result;
}
