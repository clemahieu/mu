[
	[:~; context suffix]
	.id [llvm/module/get_package module suffix] module
	[llvm/module/assemble
		context
		`a |!!!!|
		; Add
		define i128 @add_i128 (i128, i128)
		{
			entry:
			%2 = add i128 %0, %1
			ret i128 %2
		}
		define i64 @add_i64 (i64, i64)
		{
			entry:
			%2 = add i64 %0, %1
			ret i64 %2
		}
		define i32 @add_i32 (i32, i32)
		{
			entry:
			%2 = add i32 %0, %1
			ret i32 %2
		}
		define i16 @add_i16 (i16, i16)
		{
			entry:
			%2 = add i16 %0, %1
			ret i16 %2
		}
		define i8 @add_i8 (i8, i8)
		{
			entry:
			%2 = add i8 %0, %1
			ret i8 %2
		}

		; FAdd
		define float @add_float (float, float)
		{
			entry:
			%2 = fadd float %0, %1
			ret float %2
		}
		define double @add_double (double, double)
		{
			entry:
			%2 = fadd double %0, %1
			ret double %2
		}
		define fp128 @add_fp128 (fp128, fp128)
		{
			entry:
			%2 = fadd fp128 %0, %1
			ret fp128 %2
		}

		; Sub
		define i128 @sub_i128 (i128, i128)
		{
			entry:
			%2 = sub i128 %0, %1
			ret i128 %2
		}
		define i64 @sub_i64 (i64, i64)
		{
			entry:
			%2 = sub i64 %0, %1
			ret i64 %2
		}
		define i32 @sub_i32 (i32, i32)
		{
			entry:
			%2 = sub i32 %0, %1
			ret i32 %2
		}
		define i16 @sub_i16 (i16, i16)
		{
			entry:
			%2 = sub i16 %0, %1
			ret i16 %2
		}
		define i8 @sub_i8 (i8, i8)
		{
			entry:
			%2 = sub i8 %0, %1
			ret i8 %2
		}

		; FSub
		define float @sub_float (float, float)
		{
			entry:
			%2 = fsub float %0, %1
			ret float %2
		}
		define double @sub_double (double, double)
		{
			entry:
			%2 = fsub double %0, %1
			ret double %2
		}
		define fp128 @sub_fp128 (fp128, fp128)
		{
			entry:
			%2 = fsub fp128 %0, %1
			ret fp128 %2
		}

		; Mul
		define i128 @mul_i128 (i128, i128)
		{
			entry:
			%2 = mul i128 %0, %1
			ret i128 %2
		}
		define i64 @mul_i64 (i64, i64)
		{
			entry:
			%2 = mul i64 %0, %1
			ret i64 %2
		}
		define i32 @mul_i32 (i32, i32)
		{
			entry:
			%2 = mul i32 %0, %1
			ret i32 %2
		}
		define i16 @mul_i16 (i16, i16)
		{
			entry:
			%2 = mul i16 %0, %1
			ret i16 %2
		}
		define i8 @mul_i8 (i8, i8)
		{
			entry:
			%2 = mul i8 %0, %1
			ret i8 %2
		}

		; FMul
		define float @mul_float (float, float)
		{
			entry:
			%2 = fmul float %0, %1
			ret float %2
		}
		define double @mul_double (double, double)
		{
			entry:
			%2 = fmul double %0, %1
			ret double %2
		}
		define fp128 @mul_fp128 (fp128, fp128)
		{
			entry:
			%2 = fmul fp128 %0, %1
			ret fp128 %2
		}

		; UDiv
		define i128 @udiv_i128 (i128, i128)
		{
			entry:
			%2 = udiv i128 %0, %1
			ret i128 %2
		}
		define i64 @udiv_i64 (i64, i64)
		{
			entry:
			%2 = udiv i64 %0, %1
			ret i64 %2
		}
		define i32 @udiv_i32 (i32, i32)
		{
			entry:
			%2 = udiv i32 %0, %1
			ret i32 %2
		}
		define i16 @udiv_i16 (i16, i16)
		{
			entry:
			%2 = udiv i16 %0, %1
			ret i16 %2
		}
		define i8 @udiv_i8 (i8, i8)
		{
			entry:
			%2 = udiv i8 %0, %1
			ret i8 %2
		}

		; SDiv
		define i128 @sdiv_i128 (i128, i128)
		{
			entry:
			%2 = sdiv i128 %0, %1
			ret i128 %2
		}
		define i64 @sdiv_i64 (i64, i64)
		{
			entry:
			%2 = sdiv i64 %0, %1
			ret i64 %2
		}
		define i32 @sdiv_i32 (i32, i32)
		{
			entry:
			%2 = sdiv i32 %0, %1
			ret i32 %2
		}
		define i16 @sdiv_i16 (i16, i16)
		{
			entry:
			%2 = sdiv i16 %0, %1
			ret i16 %2
		}
		define i8 @sdiv_i8 (i8, i8)
		{
			entry:
			%2 = sdiv i8 %0, %1
			ret i8 %2
		}

		; FDiv
		define float @div_float (float, float)
		{
			entry:
			%2 = fdiv float %0, %1
			ret float %2
		}
		define double @div_double (double, double)
		{
			entry:
			%2 = fdiv double %0, %1
			ret double %2
		}
		define fp128 @div_fp128 (fp128, fp128)
		{
			entry:
			%2 = fdiv fp128 %0, %1
			ret fp128 %2
		}

		; URem
		define i128 @urem_i128 (i128, i128)
		{
			entry:
			%2 = urem i128 %0, %1
			ret i128 %2
		}
		define i64 @urem_i64 (i64, i64)
		{
			entry:
			%2 = urem i64 %0, %1
			ret i64 %2
		}
		define i32 @urem_i32 (i32, i32)
		{
			entry:
			%2 = urem i32 %0, %1
			ret i32 %2
		}
		define i16 @urem_i16 (i16, i16)
		{
			entry:
			%2 = urem i16 %0, %1
			ret i16 %2
		}
		define i8 @urem_i8 (i8, i8)
		{
			entry:
			%2 = urem i8 %0, %1
			ret i8 %2
		}

		; SRem
		define i128 @srem_i128 (i128, i128)
		{
			entry:
			%2 = srem i128 %0, %1
			ret i128 %2
		}
		define i64 @srem_i64 (i64, i64)
		{
			entry:
			%2 = srem i64 %0, %1
			ret i64 %2
		}
		define i32 @srem_i32 (i32, i32)
		{
			entry:
			%2 = srem i32 %0, %1
			ret i32 %2
		}
		define i16 @srem_i16 (i16, i16)
		{
			entry:
			%2 = srem i16 %0, %1
			ret i16 %2
		}
		define i8 @srem_i8 (i8, i8)
		{
			entry:
			%2 = srem i8 %0, %1
			ret i8 %2
		}

		; FRem
		define float @rem_float (float, float)
		{
			entry:
			%2 = frem float %0, %1
			ret float %2
		}
		define double @rem_double (double, double)
		{
			entry:
			%2 = frem double %0, %1
			ret double %2
		}
		define fp128 @rem_fp128 (fp128, fp128)
		{
			entry:
			%2 = frem fp128 %0, %1
			ret fp128 %2
		}

		; Shl
		define i128 @shl_i128 (i128, i128)
		{
			entry:
			%2 = shl i128 %0, %1
			ret i128 %2
		}
		define i64 @shl_i64 (i64, i64)
		{
			entry:
			%2 = shl i64 %0, %1
			ret i64 %2
		}
		define i32 @shl_i32 (i32, i32)
		{
			entry:
			%2 = shl i32 %0, %1
			ret i32 %2
		}
		define i16 @shl_i16 (i16, i16)
		{
			entry:
			%2 = shl i16 %0, %1
			ret i16 %2
		}
		define i8 @shl_i8 (i8, i8)
		{
			entry:
			%2 = shl i8 %0, %1
			ret i8 %2
		}

		; LShr
		define i128 @lshr_i128 (i128, i128)
		{
			entry:
			%2 = lshr i128 %0, %1
			ret i128 %2
		}
		define i64 @lshr_i64 (i64, i64)
		{
			entry:
			%2 = lshr i64 %0, %1
			ret i64 %2
		}
		define i32 @lshr_i32 (i32, i32)
		{
			entry:
			%2 = lshr i32 %0, %1
			ret i32 %2
		}
		define i16 @lshr_i16 (i16, i16)
		{
			entry:
			%2 = lshr i16 %0, %1
			ret i16 %2
		}
		define i8 @lshr_i8 (i8, i8)
		{
			entry:
			%2 = lshr i8 %0, %1
			ret i8 %2
		}

		; AShr
		define i128 @ashr_i128 (i128, i128)
		{
			entry:
			%2 = ashr i128 %0, %1
			ret i128 %2
		}
		define i64 @ashr_i64 (i64, i64)
		{
			entry:
			%2 = ashr i64 %0, %1
			ret i64 %2
		}
		define i32 @ashr_i32 (i32, i32)
		{
			entry:
			%2 = ashr i32 %0, %1
			ret i32 %2
		}
		define i16 @ashr_i16 (i16, i16)
		{
			entry:
			%2 = ashr i16 %0, %1
			ret i16 %2
		}
		define i8 @ashr_i8 (i8, i8)
		{
			entry:
			%2 = ashr i8 %0, %1
			ret i8 %2
		}

		; And
		define i128 @and_i128 (i128, i128)
		{
			entry:
			%2 = and i128 %0, %1
			ret i128 %2
		}
		define i64 @and_i64 (i64, i64)
		{
			entry:
			%2 = and i64 %0, %1
			ret i64 %2
		}
		define i32 @and_i32 (i32, i32)
		{
			entry:
			%2 = and i32 %0, %1
			ret i32 %2
		}
		define i16 @and_i16 (i16, i16)
		{
			entry:
			%2 = and i16 %0, %1
			ret i16 %2
		}
		define i8 @and_i8 (i8, i8)
		{
			entry:
			%2 = and i8 %0, %1
			ret i8 %2
		}

		; Or
		define i128 @or_i128 (i128, i128)
		{
			entry:
			%2 = or i128 %0, %1
			ret i128 %2
		}
		define i64 @or_i64 (i64, i64)
		{
			entry:
			%2 = or i64 %0, %1
			ret i64 %2
		}
		define i32 @or_i32 (i32, i32)
		{
			entry:
			%2 = or i32 %0, %1
			ret i32 %2
		}
		define i16 @or_i16 (i16, i16)
		{
			entry:
			%2 = or i16 %0, %1
			ret i16 %2
		}
		define i8 @or_i8 (i8, i8)
		{
			entry:
			%2 = or i8 %0, %1
			ret i8 %2
		}

		; Xor
		define i128 @xor_i128 (i128, i128)
		{
			entry:
			%2 = xor i128 %0, %1
			ret i128 %2
		}
		define i64 @xor_i64 (i64, i64)
		{
			entry:
			%2 = xor i64 %0, %1
			ret i64 %2
		}
		define i32 @xor_i32 (i32, i32)
		{
			entry:
			%2 = xor i32 %0, %1
			ret i32 %2
		}
		define i16 @xor_i16 (i16, i16)
		{
			entry:
			%2 = xor i16 %0, %1
			ret i16 %2
		}
		define i8 @xor_i8 (i8, i8)
		{
			entry:
			%2 = xor i8 %0, %1
			ret i8 %2
		}

		; Load
		define i128 @load_i128 (i128 *)
		{
			entry:
			%1 = load i128 * %0
			ret i128 %1
		}
		define i64 @load_i64 (i64 *)
		{
			entry:
			%1 = load i64 * %0
			ret i64 %1
		}
		define i32 @load_i32 (i32 *)
		{
			entry:
			%1 = load i32 * %0
			ret i32 %1
		}
		define i16 @load_i16 (i16 *)
		{
			entry:
			%1 = load i16 * %0
			ret i16 %1
		}
		define i8 @float_i8 (i8 *)
		{
			entry:
			%1 = load i8 * %0
			ret i8 %1
		}
		define float @load_float (float *)
		{
			entry:
			%1 = load float * %0
			ret float %1
		}
		define double @load_double (double *)
		{
			entry:
			%1 = load double * %0
			ret double %1
		}
		define fp128 @load_fp128 (fp128 *)
		{
			entry:
			%1 = load fp128 * %0
			ret fp128 %1
		}

		; Store
		define void @store_i128 (i128, i128 *)
		{
			entry:
			store i128 %0, i128 * %1
			ret void
		}
		define void @store_i64 (i64, i64 *)
		{
			entry:
			store i64 %0, i64 * %1
			ret void
		}
		define void @store_i32 (i32, i32 *)
		{
			entry:
			store i32 %0, i32 * %1
			ret void
		}
		define void @store_i16 (i16, i16 *)
		{
			entry:
			store i16 %0, i16 * %1
			ret void
		}
		define void @store_i8 (i8, i8 *)
		{
			entry:
			store i8 %0, i8 * %1
			ret void
		}
		define void @store_float (float, float *)
		{
			entry:
			store float %0, float * %1
			ret void
		}
		define void @store_double (double, double *)
		{
			entry:
			store double %0, double * %1
			ret void
		}
		define void @store_fp128 (fp128, fp128 *)
		{
			entry:
			store fp128 %0, fp128 * %1
			ret void
		}

		; Cmpxchg
		define i64 @cmpxchg_i64 (i64 *, i64, i64)
		{
			entry:
			%3 = cmpxchg i64 * %0, i64 %1, i64 %2 monotonic
			ret i64 %3
		}
		define i32 @cmpxchg_i32 (i32 *, i32, i32)
		{
			entry:
			%3 = cmpxchg i32 * %0, i32 %1, i32 %2 monotonic
			ret i32 %3
		}
		define i16 @cmpxchg_i16 (i16 *, i16, i16)
		{
			entry:
			%3 = cmpxchg i16 * %0, i16 %1, i16 %2 monotonic
			ret i16 %3
		}
		define i8 @cmpxchg_i8 (i8 *, i8, i8)
		{
			entry:
			%3 = cmpxchg i8 * %0, i8 %1, i8 %2 monotonic
			ret i8 %3
		}

		; Trunc
		define i64 @trunc_i128_i64 (i128)
		{
			entry:
			%1 = trunc i128 %0 to i64
			ret i64 %1
		}
		define i32 @trunc_i128_i32 (i128)
		{
			entry:
			%1 = trunc i128 %0 to i32
			ret i32 %1
		}
		define i16 @trunc_i128_i16 (i128)
		{
			entry:
			%1 = trunc i128 %0 to i16
			ret i16 %1
		}
		define i8 @trunc_i128_i8 (i128)
		{
			entry:
			%1 = trunc i128 %0 to i8
			ret i8 %1
		}
		define i32 @trunc_i64_i32 (i64)
		{
			entry:
			%1 = trunc i64 %0 to i32
			ret i32 %1
		}
		define i16 @trunc_i64_i16 (i64)
		{
			entry:
			%1 = trunc i64 %0 to i16
			ret i16 %1
		}
		define i8 @trunc_i64_i8 (i64)
		{
			entry:
			%1 = trunc i64 %0 to i8
			ret i8 %1
		}
		define i16 @trunc_i32_i16 (i32)
		{
			entry:
			%1 = trunc i32 %0 to i16
			ret i16 %1
		}
		define i8 @trunc_i32_i8 (i32)
		{
			entry:
			%1 = trunc i32 %0 to i8
			ret i8 %1
		}
		define i8 @trunc_i16_i8 (i16)
		{
			entry:
			%1 = trunc i16 %0 to i8
			ret i8 %1
		}

		; Zext
		define i128 @zext_i64_i128 (i64)
		{
			entry:
			%1 = zext i64 %0 to i128
			ret i128 %1
		}
		define i128 @zext_i32_i128 (i32)
		{
			entry:
			%1 = zext i32 %0 to i128
			ret i128 %1
		}
		define i64 @zext_i32_i64 (i32)
		{
			entry:
			%1 = zext i32 %0 to i64
			ret i64 %1
		}
		define i128 @zext_i16_i128 (i16)
		{
			entry:
			%1 = zext i16 %0 to i128
			ret i128 %1
		}
		define i64 @zext_i16_i64 (i16)
		{
			entry:
			%1 = zext i16 %0 to i64
			ret i64 %1
		}
		define i32 @zext_i16_i32 (i16)
		{
			entry:
			%1 = zext i16 %0 to i32
			ret i32 %1
		}
		define i128 @zext_i8_i128 (i8)
		{
			entry:
			%1 = zext i8 %0 to i128
			ret i128 %1
		}
		define i64 @zext_i8_i64 (i8)
		{
			entry:
			%1 = zext i8 %0 to i64
			ret i64 %1
		}
		define i32 @zext_i8_i32 (i8)
		{
			entry:
			%1 = zext i8 %0 to i32
			ret i32 %1
		}
		define i16 @zext_i8_i16 (i8)
		{
			entry:
			%1 = zext i8 %0 to i16
			ret i16 %1
		}

		; Sext
		define i128 @sext_i64_i128 (i64)
		{
			entry:
			%1 = sext i64 %0 to i128
			ret i128 %1
		}
		define i128 @sext_i32_i128 (i32)
		{
			entry:
			%1 = sext i32 %0 to i128
			ret i128 %1
		}
		define i64 @sext_i32_i64 (i32)
		{
			entry:
			%1 = sext i32 %0 to i64
			ret i64 %1
		}
		define i128 @sext_i16_i128 (i16)
		{
			entry:
			%1 = sext i16 %0 to i128
			ret i128 %1
		}
		define i64 @sext_i16_i64 (i16)
		{
			entry:
			%1 = sext i16 %0 to i64
			ret i64 %1
		}
		define i32 @sext_i16_i32 (i16)
		{
			entry:
			%1 = sext i16 %0 to i32
			ret i32 %1
		}
		define i128 @sext_i8_i128 (i8)
		{
			entry:
			%1 = sext i8 %0 to i128
			ret i128 %1
		}
		define i64 @sext_i8_i64 (i8)
		{
			entry:
			%1 = sext i8 %0 to i64
			ret i64 %1
		}
		define i32 @sext_i8_i32 (i8)
		{
			entry:
			%1 = sext i8 %0 to i32
			ret i32 %1
		}
		define i16 @sext_i8_i16 (i8)
		{
			entry:
			%1 = sext i8 %0 to i16
			ret i16 %1
		}

		; Fptrunc
		define double @fptrunc_fp128_double (fp128)
		{
			entry:
			%1 = fptrunc fp128 %0 to double
			ret double %1
		}
		define float @fptrunc_fp128_float (fp128)
		{
			entry:
			%1 = fptrunc fp128 %0 to float
			ret float %1
		}
		define float @fptrunc_double_float (double)
		{
			entry:
			%1 = fptrunc double %0 to float
			ret float %1
		}

		; Fpext
		define fp128 @fpext_double_fp128 (double)
		{
			entry:
			%1 = fpext double %0 to fp128
			ret fp128 %1
		}
		define fp128 @fpext_float_fp128 (float)
		{
			entry:
			%1 = fpext float %0 to fp128
			ret fp128 %1
		}
		define double @fpext_float_double (float)
		{
			entry:
			%1 = fpext float %0 to double
			ret double %1
		}

		; Fptoui
		define i128 @fptoui_fp128_i128 (fp128)
		{
			entry:
			%1 = fptoui fp128 %0 to i128
			ret i128 %1
		}
		define i64 @fptoui_fp128_i64 (fp128)
		{
			entry:
			%1 = fptoui fp128 %0 to i64
			ret i64 %1
		}
		define i32 @fptoui_fp128_i32 (fp128)
		{
			entry:
			%1 = fptoui fp128 %0 to i32
			ret i32 %1
		}
		define i16 @fptoui_fp128_i16 (fp128)
		{
			entry:
			%1 = fptoui fp128 %0 to i16
			ret i16 %1
		}
		define i8 @fptoui_fp128_i8 (fp128)
		{
			entry:
			%1 = fptoui fp128 %0 to i8
			ret i8 %1
		}
		define i128 @fptoui_double_i128 (double)
		{
			entry:
			%1 = fptoui double %0 to i128
			ret i128 %1
		}
		define i64 @fptoui_double_i64 (double)
		{
			entry:
			%1 = fptoui double %0 to i64
			ret i64 %1
		}
		define i32 @fptoui_double_i32 (double)
		{
			entry:
			%1 = fptoui double %0 to i32
			ret i32 %1
		}
		define i16 @fptoui_double_i16 (double)
		{
			entry:
			%1 = fptoui double %0 to i16
			ret i16 %1
		}
		define i8 @fptoui_double_i8 (double)
		{
			entry:
			%1 = fptoui double %0 to i8
			ret i8 %1
		}
		define i128 @fptoui_float_i128 (float)
		{
			entry:
			%1 = fptoui float %0 to i128
			ret i128 %1
		}
		define i64 @fptoui_float_i64 (float)
		{
			entry:
			%1 = fptoui float %0 to i64
			ret i64 %1
		}
		define i32 @fptoui_float_i32 (float)
		{
			entry:
			%1 = fptoui float %0 to i32
			ret i32 %1
		}
		define i16 @fptoui_float_i16 (float)
		{
			entry:
			%1 = fptoui float %0 to i16
			ret i16 %1
		}
		define i8 @fptoui_float_i8 (float)
		{
			entry:
			%1 = fptoui float %0 to i8
			ret i8 %1
		}

		; Fptosi
		define i128 @fptosi_fp128_i128 (fp128)
		{
			entry:
			%1 = fptosi fp128 %0 to i128
			ret i128 %1
		}
		define i64 @fptosi_fp128_i64 (fp128)
		{
			entry:
			%1 = fptosi fp128 %0 to i64
			ret i64 %1
		}
		define i32 @fptosi_fp128_i32 (fp128)
		{
			entry:
			%1 = fptosi fp128 %0 to i32
			ret i32 %1
		}
		define i16 @fptosi_fp128_i16 (fp128)
		{
			entry:
			%1 = fptosi fp128 %0 to i16
			ret i16 %1
		}
		define i8 @fptosi_fp128_i8 (fp128)
		{
			entry:
			%1 = fptosi fp128 %0 to i8
			ret i8 %1
		}
		define i128 @fptosi_double_i128 (double)
		{
			entry:
			%1 = fptosi double %0 to i128
			ret i128 %1
		}
		define i64 @fptosi_double_i64 (double)
		{
			entry:
			%1 = fptosi double %0 to i64
			ret i64 %1
		}
		define i32 @fptosi_double_i32 (double)
		{
			entry:
			%1 = fptosi double %0 to i32
			ret i32 %1
		}
		define i16 @fptosi_double_i16 (double)
		{
			entry:
			%1 = fptosi double %0 to i16
			ret i16 %1
		}
		define i8 @fptosi_double_i8 (double)
		{
			entry:
			%1 = fptosi double %0 to i8
			ret i8 %1
		}
		define i128 @fptosi_float_i128 (float)
		{
			entry:
			%1 = fptosi float %0 to i128
			ret i128 %1
		}
		define i64 @fptosi_float_i64 (float)
		{
			entry:
			%1 = fptosi float %0 to i64
			ret i64 %1
		}
		define i32 @fptosi_float_i32 (float)
		{
			entry:
			%1 = fptosi float %0 to i32
			ret i32 %1
		}
		define i16 @fptosi_float_i16 (float)
		{
			entry:
			%1 = fptosi float %0 to i16
			ret i16 %1
		}
		define i8 @fptosi_float_i8 (float)
		{
			entry:
			%1 = fptosi float %0 to i8
			ret i8 %1
		}

		; Uitofp
		define fp128 @uitofp_i128_fp128 (i128)
		{
			entry:
			%1 = uitofp i128 %0 to fp128
			ret fp128 %1
		}
		define double @uitofp_i128_double (i128)
		{
			entry:
			%1 = uitofp i128 %0 to double
			ret double %1
		}
		define float @uitofp_i128_float (i128)
		{
			entry:
			%1 = uitofp i128 %0 to float
			ret float %1
		}
		define fp128 @uitofp_i64_fp128 (i64)
		{
			entry:
			%1 = uitofp i64 %0 to fp128
			ret fp128 %1
		}
		define double @uitofp_i64_double (i64)
		{
			entry:
			%1 = uitofp i64 %0 to double
			ret double %1
		}
		define float @uitofp_i64_float (i64)
		{
			entry:
			%1 = uitofp i64 %0 to float
			ret float %1
		}
		define fp128 @uitofp_i32_fp128 (i32)
		{
			entry:
			%1 = uitofp i32 %0 to fp128
			ret fp128 %1
		}
		define double @uitofp_i32_double (i32)
		{
			entry:
			%1 = uitofp i32 %0 to double
			ret double %1
		}
		define float @uitofp_i32_float (i32)
		{
			entry:
			%1 = uitofp i32 %0 to float
			ret float %1
		}
		define fp128 @uitofp_i16_fp128 (i16)
		{
			entry:
			%1 = uitofp i16 %0 to fp128
			ret fp128 %1
		}
		define double @uitofp_i16_double (i16)
		{
			entry:
			%1 = uitofp i16 %0 to double
			ret double %1
		}
		define float @uitofp_i16_float (i16)
		{
			entry:
			%1 = uitofp i16 %0 to float
			ret float %1
		}
		define fp128 @uitofp_i8_fp128 (i8)
		{
			entry:
			%1 = uitofp i8 %0 to fp128
			ret fp128 %1
		}
		define double @uitofp_i8_double (i8)
		{
			entry:
			%1 = uitofp i8 %0 to double
			ret double %1
		}
		define float @uitofp_i8_float (i8)
		{
			entry:
			%1 = uitofp i8 %0 to float
			ret float %1
		}

		; Sitofp
		define fp128 @sitofp_i128_fp128 (i128)
		{
			entry:
			%1 = sitofp i128 %0 to fp128
			ret fp128 %1
		}
		define double @sitofp_i128_double (i128)
		{
			entry:
			%1 = sitofp i128 %0 to double
			ret double %1
		}
		define float @sitofp_i128_float (i128)
		{
			entry:
			%1 = sitofp i128 %0 to float
			ret float %1
		}
		define fp128 @sitofp_i64_fp128 (i64)
		{
			entry:
			%1 = sitofp i64 %0 to fp128
			ret fp128 %1
		}
		define double @sitofp_i64_double (i64)
		{
			entry:
			%1 = sitofp i64 %0 to double
			ret double %1
		}
		define float @sitofp_i64_float (i64)
		{
			entry:
			%1 = sitofp i64 %0 to float
			ret float %1
		}
		define fp128 @sitofp_i32_fp128 (i32)
		{
			entry:
			%1 = sitofp i32 %0 to fp128
			ret fp128 %1
		}
		define double @sitofp_i32_double (i32)
		{
			entry:
			%1 = sitofp i32 %0 to double
			ret double %1
		}
		define float @sitofp_i32_float (i32)
		{
			entry:
			%1 = sitofp i32 %0 to float
			ret float %1
		}
		define fp128 @sitofp_i16_fp128 (i16)
		{
			entry:
			%1 = sitofp i16 %0 to fp128
			ret fp128 %1
		}
		define double @sitofp_i16_double (i16)
		{
			entry:
			%1 = sitofp i16 %0 to double
			ret double %1
		}
		define float @sitofp_i16_float (i16)
		{
			entry:
			%1 = sitofp i16 %0 to float
			ret float %1
		}
		define fp128 @sitofp_i8_fp128 (i8)
		{
			entry:
			%1 = sitofp i8 %0 to fp128
			ret fp128 %1
		}
		define double @sitofp_i8_double (i8)
		{
			entry:
			%1 = sitofp i8 %0 to double
			ret double %1
		}
		define float @sitofp_i8_float (i8)
		{
			entry:
			%1 = sitofp i8 %0 to float
			ret float %1
		}

		; icmp
		define i1 @icmp_eq_i128_i128 (i128, i128)
		{
			entry:
			%2 = icmp eq i128 %0, %1
			ret i1 %2
		}
		define i1 @icmp_ne_i128_i128 (i128, i128)
		{
			entry:
			%2 = icmp ne i128 %0, %1
			ret i1 %2
		}
		define i1 @icmp_ugt_i128_i128 (i128, i128)
		{
			entry:
			%2 = icmp ugt i128 %0, %1
			ret i1 %2
		}
		define i1 @icmp_uge_i128_i128 (i128, i128)
		{
			entry:
			%2 = icmp uge i128 %0, %1
			ret i1 %2
		}
		define i1 @icmp_ult_i128_i128 (i128, i128)
		{
			entry:
			%2 = icmp ult i128 %0, %1
			ret i1 %2
		}
		define i1 @icmp_ule_i128_i128 (i128, i128)
		{
			entry:
			%2 = icmp ule i128 %0, %1
			ret i1 %2
		}
		define i1 @icmp_sgt_i128_i128 (i128, i128)
		{
			entry:
			%2 = icmp sgt i128 %0, %1
			ret i1 %2
		}
		define i1 @icmp_sge_i128_i128 (i128, i128)
		{
			entry:
			%2 = icmp sge i128 %0, %1
			ret i1 %2
		}
		define i1 @icmp_slt_i128_i128 (i128, i128)
		{
			entry:
			%2 = icmp slt i128 %0, %1
			ret i1 %2
		}
		define i1 @icmp_sle_i128_i128 (i128, i128)
		{
			entry:
			%2 = icmp sle i128 %0, %1
			ret i1 %2
		}
		define i1 @icmp_eq_i64_i64 (i64, i64)
		{
			entry:
			%2 = icmp eq i64 %0, %1
			ret i1 %2
		}
		define i1 @icmp_ne_i64_i64 (i64, i64)
		{
			entry:
			%2 = icmp ne i64 %0, %1
			ret i1 %2
		}
		define i1 @icmp_ugt_i64_i64 (i64, i64)
		{
			entry:
			%2 = icmp ugt i64 %0, %1
			ret i1 %2
		}
		define i1 @icmp_uge_i64_i64 (i64, i64)
		{
			entry:
			%2 = icmp uge i64 %0, %1
			ret i1 %2
		}
		define i1 @icmp_ult_i64_i64 (i64, i64)
		{
			entry:
			%2 = icmp ult i64 %0, %1
			ret i1 %2
		}
		define i1 @icmp_ule_i64_i64 (i64, i64)
		{
			entry:
			%2 = icmp ule i64 %0, %1
			ret i1 %2
		}
		define i1 @icmp_sgt_i64_i64 (i64, i64)
		{
			entry:
			%2 = icmp sgt i64 %0, %1
			ret i1 %2
		}
		define i1 @icmp_sge_i64_i64 (i64, i64)
		{
			entry:
			%2 = icmp sge i64 %0, %1
			ret i1 %2
		}
		define i1 @icmp_slt_i64_i64 (i64, i64)
		{
			entry:
			%2 = icmp slt i64 %0, %1
			ret i1 %2
		}
		define i1 @icmp_sle_i64_i64 (i64, i64)
		{
			entry:
			%2 = icmp sle i64 %0, %1
			ret i1 %2
		}
		define i1 @icmp_eq_i32_i32 (i32, i32)
		{
			entry:
			%2 = icmp eq i32 %0, %1
			ret i1 %2
		}
		define i1 @icmp_ne_i32_i32 (i32, i32)
		{
			entry:
			%2 = icmp ne i32 %0, %1
			ret i1 %2
		}
		define i1 @icmp_ugt_i32_i32 (i32, i32)
		{
			entry:
			%2 = icmp ugt i32 %0, %1
			ret i1 %2
		}
		define i1 @icmp_uge_i32_i32 (i32, i32)
		{
			entry:
			%2 = icmp uge i32 %0, %1
			ret i1 %2
		}
		define i1 @icmp_ult_i32_i32 (i32, i32)
		{
			entry:
			%2 = icmp ult i32 %0, %1
			ret i1 %2
		}
		define i1 @icmp_ule_i32_i32 (i32, i32)
		{
			entry:
			%2 = icmp ule i32 %0, %1
			ret i1 %2
		}
		define i1 @icmp_sgt_i32_i32 (i32, i32)
		{
			entry:
			%2 = icmp sgt i32 %0, %1
			ret i1 %2
		}
		define i1 @icmp_sge_i32_i32 (i32, i32)
		{
			entry:
			%2 = icmp sge i32 %0, %1
			ret i1 %2
		}
		define i1 @icmp_slt_i32_i32 (i32, i32)
		{
			entry:
			%2 = icmp slt i32 %0, %1
			ret i1 %2
		}
		define i1 @icmp_sle_i32_i32 (i32, i32)
		{
			entry:
			%2 = icmp sle i32 %0, %1
			ret i1 %2
		}
		define i1 @icmp_eq_i16_i16 (i16, i16)
		{
			entry:
			%2 = icmp eq i16 %0, %1
			ret i1 %2
		}
		define i1 @icmp_ne_i16_i16 (i16, i16)
		{
			entry:
			%2 = icmp ne i16 %0, %1
			ret i1 %2
		}
		define i1 @icmp_ugt_i16_i16 (i16, i16)
		{
			entry:
			%2 = icmp ugt i16 %0, %1
			ret i1 %2
		}
		define i1 @icmp_uge_i16_i16 (i16, i16)
		{
			entry:
			%2 = icmp uge i16 %0, %1
			ret i1 %2
		}
		define i1 @icmp_ult_i16_i16 (i16, i16)
		{
			entry:
			%2 = icmp ult i16 %0, %1
			ret i1 %2
		}
		define i1 @icmp_ule_i16_i16 (i16, i16)
		{
			entry:
			%2 = icmp ule i16 %0, %1
			ret i1 %2
		}
		define i1 @icmp_sgt_i16_i16 (i16, i16)
		{
			entry:
			%2 = icmp sgt i16 %0, %1
			ret i1 %2
		}
		define i1 @icmp_sge_i16_i16 (i16, i16)
		{
			entry:
			%2 = icmp sge i16 %0, %1
			ret i1 %2
		}
		define i1 @icmp_slt_i16_i16 (i16, i16)
		{
			entry:
			%2 = icmp slt i16 %0, %1
			ret i1 %2
		}
		define i1 @icmp_sle_i16_i16 (i16, i16)
		{
			entry:
			%2 = icmp sle i16 %0, %1
			ret i1 %2
		}


		!!!!
	; module]
]