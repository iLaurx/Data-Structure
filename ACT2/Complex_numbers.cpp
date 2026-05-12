#include <iostream>

struct Complexf
{
    float r,i;
    
    Complexf()
    {
        i=r=0;
    }
    
    Complexf(float rv, float iv)
    {
        r = rv;
        i = iv;
    }
    
    Complexf operator+(const Complexf &other)
    {
        Complexf res;
        
        res.r = r + other.r;
        res.i = i + other.i;
        
        return res;
    }
    
    Complexf operator-(const Complexf &other)
    {
        Complexf resta;

        resta.r = r - other.r;
        resta.i = i - other.i;

        return resta;
    }

    Complexf operator*(const Complexf &other)
    {
        Complexf multi;

        multi.r = r * other.r;
        multi.i = i * other.i;

        return multi;
    }

    Complexf operator/(const Complexf &other)
    {
        Complexf div;
        float divisor = (other.r * other.r) + (other.i * other.i);

        if (divisor == 0) {
            std::cout << "Error: Division por cero" << std::endl;
            return Complexf(0,0); // O manejar error
        }

        div.r = ((r * other.r) + (i * other.i)) / divisor;
        div.i = ((i * other.r) - (r * other.i)) / divisor;

        return div;
    }

    // copy assignment
    Complexf& operator=(const Complexf& other)
    {
        // Guard self assignment
        if (this == &other)
            return *this;
            
        r = other.r;
        i = other.i;

        return *this;
    }
};

void mostrar(Complexf c) {

    if(c.i > 0){
        std::cout << c.r << "+" << c.i << "i\n"; 
    }
    else{
        std::cout << c.r << "-" << std::abs(c.i) << "i\n"; //std::abs para evitar signos dobles 
    }
        
}

int main()
{
    printf("Resultados\n");
    Complexf c1(1,2),c2,c3,c4,c5,c6;
    
    c2.i = -3;
    
    c3 = c1 + c2;
    c4 = c1 - c2;
    c5 = c1 * c2;
    c6 = c1 / c2;

    std::cout << "suma: "; mostrar(c3);
    std::cout << "resta: "; mostrar(c4);
    std::cout << "multiplicacion: "; mostrar(c5);
    std::cout << "division: "; mostrar(c6);
    return 0;
}
