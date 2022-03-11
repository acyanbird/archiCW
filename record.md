#### original

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

#### with waxpby avx

===== Final Statistics =====
Executable name:      /dcs/20/u2061245/kudo/ACACGS/./acacgs
Dimensions:           20 20 20
Number of iterations: 149
Final residual:       1.353069e-50

=== Time ==
Total:           8.965800e-02 seconds
ddot Kernel:     3.227000e-03 seconds
waxpby Kernel:   6.026000e-03 seconds
sparsemv Kernel: 7.990400e-02 seconds

=== FLOP ==
Total:           7.628800e+07 floating point operations
ddot Kernel:     4.768000e+06 floating point operations
waxpby Kernel:   7.152000e+06 floating point operations
sparsemv Kernel: 6.436800e+07 floating point operations

=== MFLOP/s ==
Total:           8.508778e+02 MFLOP/s
ddot Kernel:     1.477533e+03 MFLOP/s
waxpby Kernel:   1.186857e+03 MFLOP/s
sparsemv Kernel: 8.055667e+02 MFLOP/s

Difference between computed and exact = 1.776357e-15 

#### ddot, waxpby avx, sparsemv openmp
===== Final Statistics =====
Executable name:      /dcs/20/u2061245/kudo/archiCW/./acacgs
Dimensions:           20 20 20
Number of iterations: 149
Final residual:       8.396848e-51

=== Time ==
Total:           8.485819e+00 seconds
ddot Kernel:     2.307400e-02 seconds
waxpby Kernel:   2.605700e-02 seconds
sparsemv Kernel: 8.431142e+00 seconds

=== FLOP ==
Total:           7.628800e+07 floating point operations
ddot Kernel:     4.768000e+06 floating point operations
waxpby Kernel:   7.152000e+06 floating point operations
sparsemv Kernel: 6.436800e+07 floating point operations

=== MFLOP/s ==
Total:           8.990057e+00 MFLOP/s
ddot Kernel:     2.066395e+02 MFLOP/s
waxpby Kernel:   2.744752e+02 MFLOP/s
sparsemv Kernel: 7.634553e+00 MFLOP/s

Difference between computed and exact = 1.110223e-15

#### ddot, waxpby avx, sparsemv, waxpby openmp

===== Final Statistics =====
Executable name:      /dcs/20/u2061245/kudo/archiCW/./acacgs
Dimensions:           20 20 20
Number of iterations: 149
Final residual:       1.629319e-51

=== Time ==
Total:           8.864465e+00 seconds
ddot Kernel:     2.819500e-02 seconds
waxpby Kernel:   2.426100e-02 seconds
sparsemv Kernel: 8.811509e+00 seconds

=== FLOP ==
Total:           7.628800e+07 floating point operations
ddot Kernel:     4.768000e+06 floating point operations
waxpby Kernel:   7.152000e+06 floating point operations
sparsemv Kernel: 6.436800e+07 floating point operations

=== MFLOP/s ==
Total:           8.606047e+00 MFLOP/s
ddot Kernel:     1.691080e+02 MFLOP/s
waxpby Kernel:   2.947941e+02 MFLOP/s
sparsemv Kernel: 7.304992e+00 MFLOP/s

Difference between computed and exact = 1.332268e-15 

#### i dont know
===== Final Statistics =====
Executable name:      /dcs/20/u2061245/kudo/archiCW/./acacgs
Dimensions:           20 20 20
Number of iterations: 149
Final residual:       2.114218e-51

=== Time ==
Total:           8.729053e+00 seconds
ddot Kernel:     2.562100e-02 seconds
waxpby Kernel:   3.840800e-02 seconds
sparsemv Kernel: 8.664529e+00 seconds

=== FLOP ==
Total:           7.628800e+07 floating point operations
ddot Kernel:     4.768000e+06 floating point operations
waxpby Kernel:   7.152000e+06 floating point operations
sparsemv Kernel: 6.436800e+07 floating point operations

=== MFLOP/s ==
Total:           8.739551e+00 MFLOP/s
ddot Kernel:     1.860973e+02 MFLOP/s
waxpby Kernel:   1.862112e+02 MFLOP/s
sparsemv Kernel: 7.428909e+00 MFLOP/s

Difference between computed and exact = 1.221245e-15 


