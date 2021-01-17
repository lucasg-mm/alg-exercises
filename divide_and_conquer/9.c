#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// define the paremeters of the mathematical function
double p , q , r , s , t , u;

// The mathematical function
double func(double x){
    return p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * pow(x, 2) + u;
}

// Function to execute the bissection method and print the answer
void bissection(double low, double high, double tolerance){
    double center;

    if (func(low) * func(high) <= 0){  // we're assuming there's only one root in the [0, 1] interval
        while ((high - low) / 2 > tolerance){
            center = (high + low) / 2;
            if (func(center) <= 0){
                high = center;
            }    
            else{
                low = center;
            }    
        }        
        printf("%.4lf\n", ((low + high) / 2));  // print the answer
    }    
    else{
        printf("No solution\n");  // print this if there's no solution  
    }      
}

// The main function
int main(){
    // get user's input and solve the equation
    while(scanf("%lf%lf%lf%lf%lf%lf", &p, &q, &r, &s, &t, &u) != EOF){
        bissection(0, 1, 3e-9);
    }
    return 0; 
}