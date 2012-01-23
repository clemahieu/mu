[
	[
		.id
		[.synthesize
			=>												:[Build lambda routine that will be used in times operation:] 
			[
				[:~; op value amount]						:[Expecting 3 arguments, an operation, a value and an amount:]
				op value amount							:[Apply value and amount to operation:]
			]
		]												:[Function is the results of the operation:]
	; routine]											:[Name lambda `routine':]
	[.create routine # d3; closure]					:[Create a closure out of routine taking 3 arguments:]
	[closure script/integer/subtract ? # d5; op]		:[Apply the subtract function to argument 1 and the integer 5 to argument 3, name as `op':]
	script/times/operation # d7 op # d50				:[Connect `op' to itself 7 times, pass in the argument the integer 50:]
]														:[Function is the result of the times operation:]