#include <gtest/gtest.h>
#include "cuda_ops.hpp"

TEST(CudaOpsTest, ChecksDataFlow) {
    constexpr int N = 16;
    constexpr int MULTIPLIER = 7;

    int host_input[N];
    int host_output[N];

    for (int i = 0; i < N; i++) {
        host_input[i] = i;
    }

    ASSERT_TRUE(multiplyValues(host_input, host_output, N, MULTIPLIER));
    
    for(int i=0; i<N; i++){
        EXPECT_EQ(host_output[i], host_input[i] * MULTIPLIER);
    }
}