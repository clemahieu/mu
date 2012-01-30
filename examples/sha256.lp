[.id
	cluster
	[llvm_io/synthesize
		.llvm
		[
			[xor
				value
				[sext
					[constants/integer
						# d1
						# d1
					]
					[value/get_type
						value
					]
				]
				[:~; value]
			;; not]
			[xor
				[and x y]
				[and
					[not x]
					z
				]
				[:~ ; x y z]
			;; ch]
			[xor
				[xor
					[and x y]
					[and x z]
				]
				[and y z]
				[:~ ; x y z]
			;; maj]
		]
		module
	;; cluster]
	[llvm/integer_type/create
		context
		# d32
	; word]
	[llvm/module/create
		[llvm/context/create
		; context]
		context
	; module]
]