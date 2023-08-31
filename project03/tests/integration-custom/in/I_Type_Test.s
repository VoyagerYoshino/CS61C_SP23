addi t0,x0,2
slli t1,t0,3
slti t2,t1,15
slti s0,t1,17
xori t2,t2,255
srai s1,s0,3
srli t2,t2,3
andi s1,s1,-1
