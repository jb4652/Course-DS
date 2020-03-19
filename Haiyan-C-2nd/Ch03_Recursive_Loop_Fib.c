// Added by Bo
#include <stdio.h>

// Program 3.5, p.45
long Fib(int n)
{
    if(n == 0 || n == 1)
        return n;
    
    return Fib(n-2) + Fib(n-1);
}

// MOOCs Slides 3.4.2, p.7
long FibLoop(int n)
{
    int a = 0, b = 1, temp, i;
    
    if(n == 0 || n == 1) return n;
    
    for(i = 2; i <= n; i++)
    {
        temp = a + b;
        a = b;
        b = temp;
    }
    
    return temp;
}

// Added by Bo
int main(int argc, char **argv)
{
    // You can try larger n
    // Loop version will still work on larger n
    // But recursive version will stop working...
    int n = 40;
    
    long fib = FibLoop(n);
    printf("Fib(%d) = %ld\n", n, fib);
    
    fib = Fib(n);
    printf("Fib(%d) = %ld\n", n, fib);
	
	return 0;
}
