[.id
	[llvm_io/synthesize
		.llvm
			[sext
				[integerc # d1 # d1]
				[integer # d32]
			]
		module
	]
	[llvm_io/synthesize
		.llvm
			[xor
				value
				[:~; value]
			]
		module
		word
	]
	[llvm_io/synthesize
		.llvm
			[xor
				[and x y]
				[and
					[not x]
					z
				]
				[:~ ; x y z not]
			]
		module
		word
		word
		word
	]
	[llvm_io/synthesize
		.llvm
			[xor
				[xor
					[and x y]
					[and x z]
				]
				[and y z]
				[:~ ; x y z]
			]
		module
		word
		word
		word
	]
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