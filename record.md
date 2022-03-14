#### original O0

===== Final Statistics =====
Executable name:      /dcs/20/u2061245/kudo/ACACGS/./acacgs
Dimensions:           20 20 20
Number of iterations: 149
Final residual:       1.353069e-50

=== Time ==
Total:           8.952700e-02 seconds
ddot Kernel:     3.226000e-03 seconds
waxpby Kernel:   6.014000e-03 seconds
sparsemv Kernel: 7.979200e-02 seconds

=== FLOP ==
Total:           7.628800e+07 floating point operations
ddot Kernel:     4.768000e+06 floating point operations
waxpby Kernel:   7.152000e+06 floating point operations
sparsemv Kernel: 6.436800e+07 floating point operations

=== MFLOP/s ==
Total:           8.521228e+02 MFLOP/s
ddot Kernel:     1.477991e+03 MFLOP/s
waxpby Kernel:   1.189225e+03 MFLOP/s
sparsemv Kernel: 8.066974e+02 MFLOP/s

Difference between computed and exact = 1.776357e-15


### original O3
===== Final Statistics =====
Executable name:      /dcs/20/u2061245/kudo/archiCW/./acacgs
Dimensions:           20 20 20
Number of iterations: 149
Final residual:       1.902160e-50

=== Time ==
Total:           2.649300e-02 seconds
ddot Kernel:     2.583000e-03 seconds
waxpby Kernel:   2.028000e-03 seconds
sparsemv Kernel: 2.138500e-02 seconds

=== FLOP ==
Total:           7.628800e+07 floating point operations
ddot Kernel:     4.768000e+06 floating point operations
waxpby Kernel:   7.152000e+06 floating point operations
sparsemv Kernel: 6.436800e+07 floating point operations

=== MFLOP/s ==
Total:           2.879553e+03 MFLOP/s
ddot Kernel:     1.845916e+03 MFLOP/s
waxpby Kernel:   3.526627e+03 MFLOP/s
sparsemv Kernel: 3.009960e+03 MFLOP/s

Difference between computed and exact = 1.887379e-15


#### O0 simd unroll
===== Final Statistics =====
Executable name:      /dcs/20/u2061245/kudo/archiCW/./acacgs
Dimensions:           20 20 20
Number of iterations: 149
Final residual:       9.318571e-51

=== Time ==
Total:           1.547771e+00 seconds
ddot Kernel:     2.978086e-03 seconds
waxpby Kernel:   1.915932e-03 seconds
sparsemv Kernel: 1.542845e+00 seconds

=== FLOP ==
Total:           7.628800e+07 floating point operations
ddot Kernel:     4.768000e+06 floating point operations
waxpby Kernel:   7.152000e+06 floating point operations
sparsemv Kernel: 6.436800e+07 floating point operations

=== MFLOP/s ==
Total:           4.928895e+01 MFLOP/s
ddot Kernel:     1.601028e+03 MFLOP/s
waxpby Kernel:   3.732910e+03 MFLOP/s
sparsemv Kernel: 4.172032e+01 MFLOP/s

Difference between computed and exact = 1.332268e-15 

#### 03 final
===== Final Statistics =====
Executable name:      /dcs/20/u2061245/kudo/archiCW/./acacgs
Dimensions:           20 20 20
Number of iterations: 149
Final residual:       1.902160e-50

=== Time ==
Total:           2.564600e-02 seconds
ddot Kernel:     2.517000e-03 seconds
waxpby Kernel:   1.987000e-03 seconds
sparsemv Kernel: 2.066000e-02 seconds

=== FLOP ==
Total:           7.628800e+07 floating point operations
ddot Kernel:     4.768000e+06 floating point operations
waxpby Kernel:   7.152000e+06 floating point operations
sparsemv Kernel: 6.436800e+07 floating point operations

=== MFLOP/s ==
Total:           2.974655e+03 MFLOP/s
ddot Kernel:     1.894319e+03 MFLOP/s
waxpby Kernel:   3.599396e+03 MFLOP/s
sparsemv Kernel: 3.115586e+03 MFLOP/s

Difference between computed and exact = 1.887379e-15 



