#include <iostream>

double calculate_catelian(unsigned n){

	unsigned two_n = 2 * n;
	unsigned k = n;

    if(k > two_n - k)
    	k = two_n - k;

    double result = 1.0;

    for(long long int i=0; i<k; i++){
        result *= two_n - i;
        result /= i + 1;
    }

    return result/(n + 1);
}


int main() {

	unsigned n = 6;

	double result = calculate_catelian(n);

	std::cout<<"The "<<n<<"th Catelian number is: "<<result<<std::endl;

	return 0;
}
