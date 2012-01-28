[
	.id
	[script/chain/operation 
		[.synthesize
			->
				[
					[:~; value]
					[script/integer/subtract value # d1; result]
					[script/integer/equal result # d5; continue]
					.id result continue
				]
		]
		# d10
	]
]