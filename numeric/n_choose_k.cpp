#include <iostream>
using namespace std;

double choose(unsigned n, unsigned k){

    if(k > n-k)
    	k = n-k;

    double result = 1.0;

    for(long long int i=0; i<k; i++){
        result *= n-i;
        result /= i+1;
    }

    return result;
}


int main() {

	unsigned n = 200;
	unsigned k = 20;

	double result = choose(n, k);

	std::cout<<"N choose K is: "<<result<<std::endl;

	return 0;
}
