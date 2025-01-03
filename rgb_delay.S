.syntax unified

.global cycle_delay_t0h
.global cycle_delay_t0l
.global cycle_delay_t1h
.global cycle_delay_t1l

@(Assuming 125MHz CPU clock)

@(Remember that C side has some delays due to arithmetic and register logic in between delays so we must be under the required timings)

@(Each instruction cycle is 8ns => 1/100MHz*1000)
@(Formula for actual ns delay in the functions below is (3N+2)*8ns where N is the number fed into R0)

@(These functions are just used to waste cycles)

cycle_delay_t0h:			@[400ns needed] [376ns actual]
	MOVS R0, #15			@1 cycle (change this up or down if timings don't work)
1:	SUBS R0, R0, #1			@1 cycle (subtract from R0 and check below if 0 yet)
	BNE 1b					@2 cycles on entry, 1 on exit (if no zero, branch back to local label)
	BX LR					@2 cycles (bounce back to C)
							 

cycle_delay_t0l:			@[850ns needed] [832ns actual]
	MOVS R0, #34			@(change this up or down if timings don't work)
2:	SUBS R0, R0, #1
	BNE 2b
	BX LR					

cycle_delay_t1h:			@[800ns needed] [784ns actual]
	MOVS R0, #32			@(change this up or down if timings don't work)
3:	SUBS R0, R0, #1
	BNE 3b
	BX LR					

cycle_delay_t1l:			@[450ns needed] [424ns actual]
	MOVS R0, #17			@(change this up or down if timings don't work)
4:	SUBS R0, R0, #1
	BNE 4b
	BX LR