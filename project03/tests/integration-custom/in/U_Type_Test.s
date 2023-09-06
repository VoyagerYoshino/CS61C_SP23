addi t0, x0, 89
addi t1, x0, 17
mul t0, t0, t1

auipc s0, 5545
addi s0, s0, 801
auipc s1, 7456
addi s1, s1, 1656
mul t0, s0, s0
mul t1, s1, s1
mul t2, s0, s1
mul t2, s1, s0