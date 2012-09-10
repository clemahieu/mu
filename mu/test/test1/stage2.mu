[hash
[input_file output_file]
[	
]]

[fmix
[value]
[	integer/xor
	[	integer/shr
		[	integer/mul
			[	integer/xor
				[	integer/shr
					[	integer/mul	
						[	integer/xor
							[	integer/shr
								value
								#16]
							value]
						#85ebca6bh
					;	value1]
					#13]
				value1]
			#c2b2ae35h
		;	value2]
		#16]
	value2]
]]

[fmix2
[value]
[
	[	nil
		[* #85ebca6bh [^ h [>> h #16]]; h1]
		[* #c2b2ae35h [^ h1 [>> h1 #13]; h2]]
	^ h2 [>> h2 #16]
]]

[fmix3
[value]
[	
	[	integer/mul	
		[	integer/xor
			[	integer/shr
				value
				#16]
			value]
		#85ebca6bh
	;	value1]
	[	integer/shr
		value1
		[	integer/mul
			[	integer/xor
					#13]
				value1]
			#c2b2ae35h
		]
	;	value2]
	[	integer/xor
		value2
		[	integer/shr
			#16
			value2]
	;	value3]
]
[value3]
]

[fmix4
[value]
[
	[* #85ebca6bh [^ h [>> h #16]]; h1]
	[* #c2b2ae35h [^ h1 [>> h1 #13]]; h2]
	[^ h2 [>> h2 #16]; h3]
]
[h3]
]

[murmurhash-x86-32
[key len seed out]
[	
]]
