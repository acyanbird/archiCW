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

#### waxpby sparsemv 取消 openmp

===== Final Statistics =====
Executable name:      /dcs/20/u2061245/kudo/archiCW/./acacgs
Dimensions:           20 20 20
Number of iterations: 149
Final residual:       1.353069e-50

=== Time ==
Total:           2.331901e-02 seconds
ddot Kernel:     6.778240e-04 seconds
waxpby Kernel:   1.080751e-03 seconds
sparsemv Kernel: 2.153134e-02 seconds

=== FLOP ==
Total:           7.628800e+07 floating point operations
ddot Kernel:     4.768000e+06 floating point operations
waxpby Kernel:   7.152000e+06 floating point operations
sparsemv Kernel: 6.436800e+07 floating point operations

=== MFLOP/s ==
Total:           3.271495e+03 MFLOP/s
ddot Kernel:     7.034274e+03 MFLOP/s
waxpby Kernel:   6.617618e+03 MFLOP/s
sparsemv Kernel: 2.989502e+03 MFLOP/s

Difference between computed and exact = 1.776357e-15 

#### simd
===== Final Statistics =====
Executable name:      ./acacgs
Dimensions:           20 20 20
Number of iterations: 149
Final residual:       6.506193e-51

=== Time ==
Total:           2.913229e+00 seconds
ddot Kernel:     1.604080e-03 seconds
waxpby Kernel:   3.211498e-03 seconds
sparsemv Kernel: 2.908347e+00 seconds

=== FLOP ==
Total:           7.628800e+07 floating point operations
ddot Kernel:     4.768000e+06 floating point operations
waxpby Kernel:   7.152000e+06 floating point operations
sparsemv Kernel: 6.436800e+07 floating point operations

=== MFLOP/s ==
Total:           2.618675e+01 MFLOP/s
ddot Kernel:     2.972420e+03 MFLOP/s
waxpby Kernel:   2.226998e+03 MFLOP/s
sparsemv Kernel: 2.213216e+01 MFLOP/s

Difference between computed and exact = 1.332268e-15 

#### del openmp del g
===== Final Statistics =====
Executable name:      /dcs/20/u2061245/kudo/archiCW/./acacgs
Dimensions:           20 20 20
Number of iterations: 149
Final residual:       1.353069e-50

=== Time ==
Total:           2.342248e-02 seconds
ddot Kernel:     6.940365e-04 seconds
waxpby Kernel:   1.070499e-03 seconds
sparsemv Kernel: 2.162910e-02 seconds

=== FLOP ==
Total:           7.628800e+07 floating point operations
ddot Kernel:     4.768000e+06 floating point operations
waxpby Kernel:   7.152000e+06 floating point operations
sparsemv Kernel: 6.436800e+07 floating point operations

=== MFLOP/s ==
Total:           3.257042e+03 MFLOP/s
ddot Kernel:     6.869956e+03 MFLOP/s
waxpby Kernel:   6.680994e+03 MFLOP/s
sparsemv Kernel: 2.975991e+03 MFLOP/s

Difference between computed and exact = 1.776357e-15 
