addi t0,x0,1
addi t1,x0,2
addi s0,x0,3
addi s1,x0,4
addi sp,sp,-4
sb t0,0(sp)
sb t1,1(sp)
sb s0,2(sp)
sb s1,3(sp)
lb t0,3(sp)
lb t1,2(sp)
lb s0,1(sp)
lb s1,0(sp)
addi sp,sp,4
addi s0,x0,0
addi s1,x0,0

addi t0,x0,31
addi t1,x0,32
addi sp,sp,-4
sh t0,0(sp)
sh t1,2(sp)
lh t0,2(sp)
lh t1,0(sp)
addi sp,sp,4

addi t0,x0,2042
addi sp,sp,-4
sw t0,0(sp)
lw t1,0(sp)
lh t0,2(sp)
lh t0,1(sp)
lh t0,0(sp)
lb t0,0(sp)
lb t0,1(sp)
lb t0,2(sp)
lb t0,3(sp)
addi sp,sp,4



