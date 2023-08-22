.globl argmax

.text
# =================================================================
# FUNCTION: Given a int array, return the index of the largest
#   element. If there are multiple, return the one
#   with the smallest index.
# Arguments:
#   a0 (int*) is the pointer to the start of the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   a0 (int)  is the first index of the largest element
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# =================================================================
argmax:
    bge x0,a1,Exceptions
    mv t0,x0
    mv,t4,x0           #argmax
    lw t3,0(a0)     #t3 maxvalue
loop_start:
    bge t0,a1,loop_end
    slli t1,t0,2    #offset
    add t1,t1,a0    #t1 adress
    lw t2,0(t1)     #t2 value
    blt t3,t2,Max
loop_continue:
    addi t0,t0,1    #t0+1
    j loop_start
Max:
    mv t3,t2
    mv t4,t0
    j loop_continue
loop_end:
    mv a0,t4
    jr ra
Exceptions:
    addi a0,x0,36
    j exit
