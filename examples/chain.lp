[
	[script/chain/operation =>
		[
			[:~; value]
			[script/integer/subtract value # d1; result]
			[script/integer/equal result # d0; continue]
			.id result continue
		]
		# d10
	]
]