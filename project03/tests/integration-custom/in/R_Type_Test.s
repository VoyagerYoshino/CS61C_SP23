addi t0,x0,3    #t0=3
add t1,t0,t0    #t1=6
mul t1,t1,t0    #t1=18
sub t1,t1,t0    #t1=15
sll t2,t1,t0    #t2=120
addi t2,x0,256
mul t2,t2,t2
mulhu t1,t2,t2
mulh  t1,t2,t2
xor t1,t1,t0
srl t1,t1,t0
sra t1,t1,t0
or t1,t2,t0
and t1,t2,t0
slt t1,t1,t0