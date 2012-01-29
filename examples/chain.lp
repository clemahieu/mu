[script/chain/operation 
	routine
	# d10
	[cluster
		# d0
	; routine]
	[.synthesize
		lambda
	; cluster]
	[.id =>
		[
			[.id 
				[id result]
				continue
				[:~; value]
				[script/integer/subtract value # d1; result]
				[script/integer/equal result # d5; continue]						 
			]
			[:~;; id]
		]
	; lambda]
]