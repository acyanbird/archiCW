#### original

original

===== Final Statistics =====
Executable name:      /dcs/20/u2061245/tryKudo/ACACGS/./acacgs
Dimensions:           20 20 20
Number of iterations: 149
Final residual:       1.902160e-50

=== Time ==
Total:           8.441600e-02 seconds
ddot Kernel:     5.613000e-03 seconds
waxpby Kernel:   8.065000e-03 seconds
sparsemv Kernel: 7.026600e-02 seconds

=== FLOP ==
Total:           7.628800e+07 floating point operations
ddot Kernel:     4.768000e+06 floating point operations
waxpby Kernel:   7.152000e+06 floating point operations
sparsemv Kernel: 6.436800e+07 floating point operations

=== MFLOP/s ==
Total:           9.037149e+02 MFLOP/s
ddot Kernel:     8.494566e+02 MFLOP/s
waxpby Kernel:   8.867948e+02 MFLOP/s
sparsemv Kernel: 9.160618e+02 MFLOP/s

Difference between computed and exact = 1.887379e-15 

#### with ddot avx

===== Final Statistics =====
Executable name:      ./acacgs
Dimensions:           20 20 20
Number of iterations: 149
Final residual:       1.902160e-50

=== Time ==
Total:           1.472690e-01 seconds
ddot Kernel:     9.381000e-03 seconds
waxpby Kernel:   1.489000e-02 seconds
sparsemv Kernel: 1.225930e-01 seconds

=== FLOP ==
Total:           7.628800e+07 floating point operations
ddot Kernel:     4.768000e+06 floating point operations
waxpby Kernel:   7.152000e+06 floating point operations
sparsemv Kernel: 6.436800e+07 floating point operations

=== MFLOP/s ==
Total:           5.180180e+02 MFLOP/s
ddot Kernel:     5.082614e+02 MFLOP/s
waxpby Kernel:   4.803224e+02 MFLOP/s
sparsemv Kernel: 5.250544e+02 MFLOP/s

Difference between computed and exact = 1.887379e-15 


