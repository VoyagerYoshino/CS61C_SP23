.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
#   a0 (int*) is the pointer to the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   None
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# ==============================================================================
relu:
    bge x0,a1,Exceptions
    mv t0,x0 
loop_start:
    bge t0,a1,loop_end
    slli t1,t0,2    #offset
    add a2,a0,t1
    addi t0,t0,1    #t0+1
    lw t2,0(a2)
    bge t2,x0,loop_start
    sw x0,0(a2)
    j loop_start
loop_end:
    jr ra
Exceptions:
    li a0 36
    j exit