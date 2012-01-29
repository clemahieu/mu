[
	.id
	[script/chain/operation 
		[
			[.synthesize
				=>
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
			]
			# d0
		]
		# d10
	]
]