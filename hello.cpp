#include <cstdio>
#include <cuda_ops.hpp>


int main(){
    constexpr int N = 100;
   
    int host_input[N];
    int host_output[N];
    
    for(int i=0; i<N; i++){
        host_input[i] = i;
    }    

    bool success = multiplyValues(host_input, host_output, N, 10);

    if(!success){
        fprintf(stderr, "Multiply failed\n");
        return 1;
    }

    for(int i=0; i<N; i++){
        if(host_output[i] != host_input[i] * 10){
            fprintf(stderr,
                "Incorrect value at index %d: expected %d, got %d\n",
                i, host_input[i] * 10, host_output[i]);
            return 1;
        }
    }

    printf("All values are correct\n");
    return 0;
}