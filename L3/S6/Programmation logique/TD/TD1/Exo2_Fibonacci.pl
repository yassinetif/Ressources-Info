f(0,1).
f(1,1).
f(N,R) :- N_moins1 is N-1, N_moins2 is N-2, f(N_moins1, R1), f(N_moins2, R2), R is R1+R2.