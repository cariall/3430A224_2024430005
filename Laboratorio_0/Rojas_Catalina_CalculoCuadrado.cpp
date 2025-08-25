#include <iostream>
double square(double x) //double: 64 bits, más precisión que float (32)
{
return x*x;
}

void print_square(double x)
{
std::cout<<"El cuadrado de " << x << " es " << square(x) << "\n";
}

int main()
{
print_square(1.234);
print_square(5.555);
} 
