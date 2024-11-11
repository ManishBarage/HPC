#include <stdio.h>

int main() {
    
    double clock_speed_ghz = 3.2;  
    int num_cores = 6;             
    int ipc = 4;                   
    int flop_per_instruction = 2; 

    
    double clock_speed_hz = clock_speed_ghz * 1e9;

    
    double flops = clock_speed_hz * num_cores * ipc * flop_per_instruction;

    
    printf("Theoretical FLOPS: %f n", flops);

    return 0;
}
