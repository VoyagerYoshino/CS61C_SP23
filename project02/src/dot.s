.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int arrays
# Arguments:
#   a0 (int*) is the pointer to the start of arr0
#   a1 (int*) is the pointer to the start of arr1
#   a2 (int)  is the number of elements to use
#   a3 (int)  is the stride of arr0
#   a4 (int)  is the stride of arr1
# Returns:
#   a0 (int)  is the dot product of arr0 and arr1
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
#   - If the stride of either array is less than 1,
#     this function terminates the program with error code 37
# =======================================================
dot:
    bge x0,a2,Exception1
    bge x0,a3,Exception2
    bge x0,a4,Exception2
    addi sp,sp,-12
    sw s0,0(sp)
    sw s1,4(sp)
    sw s2,8(sp)
    mv t0,x0    #t0 is index
    mv t3,x0    #result
loop_start:
    bge t0,a2,loop_end
    slli t1,t0,2
    mul t1,t1,a3
    mul t2,t1,a4
    add t1,a0,t1    #address for array1
    add t2,a1,t2    #address for array2
    lw t1,0(t1)
    lw t2,0(t2)
    mul t1,t1,t2
    add t3,t3,t1    #t3+=mul
    addi t0,t0,1    #t0+1
    j loop_start
loop_end:
    lw s0,0(sp)
    lw s1,4(sp)
    lw s2,8(sp)
    addi sp,sp,12
    mv a0,t3
    jr ra
Exception1:
    addi a0,x0,36
    j exit
Exception2:
    addi a0,x0,37
    j exit