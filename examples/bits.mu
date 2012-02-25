[~ [i32]]
[~ [i32]]
[xor
	value
	[sext
		#i 1 d1
		[i32]
	]
	[:~; value]
;; not]

[~ [i32][i32]]
[~ [i32]]
[or
	[lshr value count]
	[shl value [sub #i 32 d32 count]]
	[:~; value count]
;; rotr]