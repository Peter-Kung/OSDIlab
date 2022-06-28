.section ".text.boot"

.global _start

_start:
	/* because  4 cores will run same code, 
	 * so we need read cpu id and core 0 run, 
	 * other cores wait for event 
 	 */
	// read cpu id, stop slave cores,
	
	/* Move to ARM register from system coprocessor register. */
	mrs x1, mpidr_el1      /* read process id from Multiprocessor Affinity Register */
	and x1, x1, #3         /*  and with 3, if > 0, continue to tag 1 */
	cbz x1, 2f	       /* CMP x1 # 0, BEQ 2f: if x1 == 0, jmp 2f */
	// cpu id > 0 stop

1:  	
	/* cpu id > 0 */
	wfe
	b   1b

2: 	/* cpu id == 0 */
	/* set stack pointer to top if stack*/
	ldr x1, =_start        /* load top of stack address into x1 */
	mov sp, x1	       /* sp = top of stack address */

	/* clear bss */
	ldr  x1, =__bss_start   /* x1 = __bss_start */	
	ldr  w2, =__bss_size    /* w2 = record of bss size */
3: 	cbz  w2, 4f		/* CMP w2 # 0, BEQ 4f: if w2 == 0, jmp 4f */

	/* when bss isn't all load into OS, w2 will not be zero. 
	 
	 * str xzr, [x1], #8: 
	 * puts value inside xzr(0 represented by 8 bytes) into 
	 * address inside x1's contents, 
	 * and x1 = x1 + 8 
	 * 
	 * ```c=
	 *        *x1 = xzr;
	 *	   x1 += 8 ;
	 * ```
         */
	str  xzr, [x1], #8      
	sub  w2, w2, #1		/* w2 -= 1 */
	cbnz w2, 3b		/* if w2 != 0, jmp 3b*/

	// jump to C code should not return
4: 	bl   main
	// for failsage, halt this core too
	b    1b
	
