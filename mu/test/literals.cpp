extern char const * const generate_empty_expected = R"%%%(
define void @0() {
  unreachable, !dbg !9
}

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_empty", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_empty] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void ()* @0, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_empty", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{null}
!9 = metadata !{i32 0, i32 0, metadata !5, null}
)%%%";

extern char const * const generate_parameter_expected = R"%%%(
define void @0(i1) {
  call void @llvm.dbg.declare(metadata !{i1 %0}, metadata !10)
  unreachable, !dbg !11
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_parameter", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_parameter] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void (i1)* @0, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_parameter", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{null, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786689, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [parameter1] [line 0]
!11 = metadata !{i32 0, i32 0, metadata !5, null}
)%%%";

extern char const * const generate_parameter_return_expected = R"%%%(
define i1 @0(i1) {
  call void @llvm.dbg.declare(metadata !{i1 %0}, metadata !10)
  ret i1 %0, !dbg !11
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_parameter_return", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_parameter_return] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i1 (i1)* @0, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_parameter_return", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786689, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [parameter1] [line 0]
!11 = metadata !{i32 0, i32 0, metadata !5, null}
)%%%";

extern char const * const generate_add_expected = R"%%%(
define i1 @0(i1) {
  call void @llvm.dbg.declare(metadata !{i1 %0}, metadata !10)
  %2 = and i1 true, true
  %3 = add i1 %0, %0, !dbg !11
  call void @llvm.dbg.declare(metadata !{i1 %3}, metadata !12)
  ret i1 %3, !dbg !11
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_add", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_add] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i1 (i1)* @0, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_add", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786689, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [parameter1] [line 0]
!11 = metadata !{i32 0, i32 0, metadata !5, null}
!12 = metadata !{i32 786688, metadata !5, metadata !"instruction1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [instruction1] [line 0]
)%%%";

extern char const * const generate_sub_expected = R"%%%(
define i1 @0(i1) {
  call void @llvm.dbg.declare(metadata !{i1 %0}, metadata !10)
  %2 = and i1 true, true
  %3 = sub i1 %0, %0, !dbg !11
  call void @llvm.dbg.declare(metadata !{i1 %3}, metadata !13)
  ret i1 %3, !dbg !14
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_sub", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_sub] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i1 (i1)* @0, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_sub", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786689, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [parameter1] [line 0]
!11 = metadata !{i32 0, i32 0, metadata !12, null}
!12 = metadata !{i32 786443, metadata !5, i32 0, i32 0, metadata !6, i32 5} ; [ DW_TAG_lexical_block ] [/generate_sub]
!13 = metadata !{i32 786688, metadata !5, metadata !"instruction1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [instruction1] [line 0]
!14 = metadata !{i32 0, i32 0, metadata !5, null}
)%%%";

extern char const * const generate_store_expected = R"%%%(
define void @0(i1, i1*) {
  call void @llvm.dbg.declare(metadata !{i1 %0}, metadata !11)
  call void @llvm.dbg.declare(metadata !{i1* %1}, metadata !12)
  %3 = and i1 true, true
  br i1 %3, label %4, label %5

; <label>:4                                       ; preds = %2
  store i1 %0, i1* %1, !dbg !13
  br label %5

; <label>:5                                       ; preds = %4, %2
  ret void, !dbg !15
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_store", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_store] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void (i1, i1*)* @0, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_store", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{null, metadata !9, metadata !10}
!9 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786447, null, metadata !"ptr", null, i32 0, i64 8, i64 0, i64 0, i32 0, metadata !9} ; [ DW_TAG_pointer_type ] [ptr] [line 0, size 8, align 0, offset 0] [from int1]
!11 = metadata !{i32 786689, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [parameter1] [line 0]
!12 = metadata !{i32 786689, metadata !5, metadata !"parameter2", metadata !6, i32 0, metadata !10, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [parameter2] [line 0]
!13 = metadata !{i32 0, i32 0, metadata !14, null}
!14 = metadata !{i32 786443, metadata !5, i32 0, i32 0, metadata !6, i32 6} ; [ DW_TAG_lexical_block ] [/generate_store]
!15 = metadata !{i32 0, i32 0, metadata !5, null}
)%%%";

extern char const * const generate_load_expected = R"%%%(
define i1 @0(i1*) {
  call void @llvm.dbg.declare(metadata !{i1* %0}, metadata !11)
  br i1 true, label %2, label %4

; <label>:2                                       ; preds = %1
  %3 = load i1* %0, !dbg !12
  br label %4

; <label>:4                                       ; preds = %2, %1
  %5 = phi i1 [ %3, %2 ], [ undef, %1 ]
  call void @llvm.dbg.declare(metadata !{i1 %5}, metadata !14)
  ret i1 %5, !dbg !15
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_load", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_load] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i1 (i1*)* @0, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_load", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !10}
!9 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786447, null, metadata !"ptr", null, i32 0, i64 8, i64 0, i64 0, i32 0, metadata !9} ; [ DW_TAG_pointer_type ] [ptr] [line 0, size 8, align 0, offset 0] [from int1]
!11 = metadata !{i32 786689, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !10, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [parameter1] [line 0]
!12 = metadata !{i32 0, i32 0, metadata !13, null}
!13 = metadata !{i32 786443, metadata !5, i32 0, i32 0, metadata !6, i32 7} ; [ DW_TAG_lexical_block ] [/generate_load]
!14 = metadata !{i32 786688, metadata !5, metadata !"instruction1", metadata !6, i32 0, metadata !10, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [instruction1] [line 0]
!15 = metadata !{i32 0, i32 0, metadata !5, null}
)%%%";

extern char const * const generate_icmp1_expected = R"%%%(
define i1 @0(i1, i1) {
  call void @llvm.dbg.declare(metadata !{i1 %0}, metadata !10)
  call void @llvm.dbg.declare(metadata !{i1 %1}, metadata !11)
  %3 = and i1 true, true
  %4 = icmp eq i1 %0, %1, !dbg !12
  call void @llvm.dbg.declare(metadata !{i1 %4}, metadata !14)
  ret i1 %4, !dbg !15
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_icmp1", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_icmp1] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i1 (i1, i1)* @0, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_icmp1", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !9, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786689, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [parameter1] [line 0]
!11 = metadata !{i32 786689, metadata !5, metadata !"parameter2", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [parameter2] [line 0]
!12 = metadata !{i32 0, i32 0, metadata !13, null}
!13 = metadata !{i32 786443, metadata !5, i32 0, i32 0, metadata !6, i32 8} ; [ DW_TAG_lexical_block ] [/generate_icmp1]
!14 = metadata !{i32 786688, metadata !5, metadata !"instruction1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [instruction1] [line 0]
!15 = metadata !{i32 0, i32 0, metadata !5, null}
)%%%";

extern char const * const generate_two_return_expected = R"%%%(
%0 = type { i1, i1 }

define %0 @0(i1) {
  call void @llvm.dbg.declare(metadata !{i1 %0}, metadata !14)
  %2 = insertvalue %0 undef, i1 %0, 0
  %3 = insertvalue %0 %2, i1 %0, 1
  ret %0 %3, !dbg !15
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_two_return", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_two_return] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, %0 (i1)* @0, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_two_return", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !12}
!9 = metadata !{i32 786451, metadata !6, metadata !"", metadata !6, i32 0, i64 2, i64 0, i32 0, i32 0, null, metadata !10, i32 0, i32 0, i32 0} ; [ DW_TAG_structure_type ] [line 0, size 2, align 0, offset 0] [from ]
!10 = metadata !{metadata !11, metadata !13}
!11 = metadata !{i32 786445, metadata !6, metadata !"", metadata !6, i32 0, i64 1, i64 0, i64 0, i32 0, metadata !12} ; [ DW_TAG_member ] [line 0, size 1, align 0, offset 0] [from int1]
!12 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!13 = metadata !{i32 786445, metadata !6, metadata !"", metadata !6, i32 0, i64 1, i64 0, i64 1, i32 0, metadata !12} ; [ DW_TAG_member ] [line 0, size 1, align 0, offset 1] [from int1]
!14 = metadata !{i32 786689, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [parameter1] [line 0]
!15 = metadata !{i32 0, i32 0, metadata !5, null}
)%%%";

extern char const * const generate_if_expected = R"%%%(
define i8 @0(i1) {
  call void @llvm.dbg.declare(metadata !{i1 %0}, metadata !10)
  %2 = and i1 true, true
  %3 = icmp eq i1 %0, false
  %4 = and i1 %2, %3
  %5 = icmp eq i1 %0, true
  %6 = and i1 %2, %5
  %7 = and i1 true, %4
  %8 = select i1 %7, i8 0, i8 undef
  %9 = and i1 true, %6
  %10 = select i1 %9, i8 1, i8 %8
  ret i8 %10, !dbg !11
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_if", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_if] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i8 (i1)* @0, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_if", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{null, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786689, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [parameter1] [line 0]
!11 = metadata !{i32 0, i32 0, metadata !5, null}
)%%%";

extern char const * const generate_if_value_expected = R"%%%(
%0 = type { i32, i32, i8 }

define %0 @0(i1) {
  call void @llvm.dbg.declare(metadata !{i1 %0}, metadata !16)
  %2 = and i1 true, true
  %3 = icmp eq i1 %0, false
  %4 = and i1 %2, %3
  %5 = icmp eq i1 %0, true
  %6 = and i1 %2, %5
  %7 = and i1 true, %4
  %8 = and i1 %7, true
  %9 = select i1 %8, i8 0, i8 undef
  %10 = and i1 true, %6
  %11 = and i1 %10, true
  %12 = select i1 %11, i8 1, i8 %9
  %13 = insertvalue %0 undef, i32 4, 0
  %14 = insertvalue %0 %13, i32 5, 1
  %15 = insertvalue %0 %14, i8 %12, 2
  ret %0 %15, !dbg !17
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_if_value", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_if_value] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, %0 (i1)* @0, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_if_value", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !15}
!9 = metadata !{i32 786451, metadata !6, metadata !"", metadata !6, i32 0, i64 64, i64 0, i32 0, i32 0, null, metadata !10, i32 0, i32 0, i32 0} ; [ DW_TAG_structure_type ] [line 0, size 64, align 0, offset 0] [from ]
!10 = metadata !{metadata !11, metadata !13, metadata !14}
!11 = metadata !{i32 786445, metadata !6, metadata !"", metadata !6, i32 0, i64 32, i64 0, i64 0, i32 0, metadata !12} ; [ DW_TAG_member ] [line 0, size 32, align 0, offset 0] [from int32]
!12 = metadata !{i32 786468, null, metadata !"int32", null, i32 0, i64 32, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int32] [line 0, size 32, align 0, offset 0, enc DW_ATE_unsigned]
!13 = metadata !{i32 786445, metadata !6, metadata !"", metadata !6, i32 0, i64 32, i64 0, i64 32, i32 0, metadata !12} ; [ DW_TAG_member ] [line 0, size 32, align 0, offset 32] [from int32]
!14 = metadata !{i32 786468, null, metadata !"int8", null, i32 0, i64 8, i64 0, i64 0, i32 0, i32 8} ; [ DW_TAG_base_type ] [int8] [line 0, size 8, align 0, offset 0, enc DW_ATE_unsigned_char]
!15 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!16 = metadata !{i32 786689, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !15, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [parameter1] [line 0]
!17 = metadata !{i32 0, i32 0, metadata !5, null}
)%%%";

extern char const * const generate_if_join_expected = R"%%%(
define void @0(i1) {
  call void @llvm.dbg.declare(metadata !{i1 %0}, metadata !10)
  %2 = and i1 true, true
  %3 = icmp eq i1 %0, false
  %4 = and i1 %2, %3
  %5 = icmp eq i1 %0, true
  %6 = and i1 %2, %5
  %7 = or i1 false, %4
  %8 = or i1 %7, %6
  ret void, !dbg !11
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_if_join", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_if_join] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void (i1)* @0, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_if_join", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{null, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786689, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [parameter1] [line 0]
!11 = metadata !{i32 0, i32 0, metadata !5, null}
)%%%";

extern char const * const generate_if_join_value_expected = R"%%%(
define i1 @0(i1) {
  call void @llvm.dbg.declare(metadata !{i1 %0}, metadata !10)
  %2 = and i1 true, true
  %3 = and i1 true, true
  %4 = icmp eq i1 %0, false
  %5 = and i1 %3, %4
  %6 = icmp eq i1 %0, true
  %7 = and i1 %3, %6
  %8 = and i1 %2, %7
  %9 = add i1 %0, %0, !dbg !11
  call void @llvm.dbg.declare(metadata !{i1 %9}, metadata !12)
  %10 = or i1 false, %8
  %11 = select i1 %8, i1 %9, i1 undef
  %12 = and i1 true, true
  %13 = and i1 %12, %7
  %14 = add i1 %0, %0, !dbg !11
  call void @llvm.dbg.declare(metadata !{i1 %14}, metadata !13)
  %15 = or i1 %10, %13
  %16 = select i1 %13, i1 %14, i1 %11
  call void @llvm.dbg.declare(metadata !{i1 %16}, metadata !14)
  ret i1 %16, !dbg !11
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_if_join_value", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_if_join_value] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i1 (i1)* @0, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_if_join_value", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786689, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [parameter1] [line 0]
!11 = metadata !{i32 0, i32 0, metadata !5, null}
!12 = metadata !{i32 786688, metadata !5, metadata !"add1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [add1] [line 0]
!13 = metadata !{i32 786688, metadata !5, metadata !"add2", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [add2] [line 0]
!14 = metadata !{i32 786688, metadata !5, metadata !"join1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [join1] [line 0]
)%%%";

extern char const * const generate_if_join_2value_expected = R"%%%(
%0 = type { i1, i1, i8 }

define %0 @0(i1) {
  call void @llvm.dbg.declare(metadata !{i1 %0}, metadata !15)
  %2 = and i1 true, true
  %3 = and i1 true, true
  %4 = icmp eq i1 %0, false
  %5 = and i1 %3, %4
  %6 = icmp eq i1 %0, true
  %7 = and i1 %3, %6
  %8 = and i1 %2, %5
  %9 = add i1 %0, %0, !dbg !16
  call void @llvm.dbg.declare(metadata !{i1 %9}, metadata !17)
  %10 = or i1 false, %8
  %11 = select i1 %8, i1 %9, i1 undef
  %12 = and i1 true, true
  %13 = and i1 %12, %7
  %14 = add i1 %0, %0, !dbg !16
  call void @llvm.dbg.declare(metadata !{i1 %14}, metadata !18)
  %15 = or i1 %10, %13
  %16 = select i1 %13, i1 %14, i1 %11
  call void @llvm.dbg.declare(metadata !{i1 %16}, metadata !19)
  %17 = and i1 true, %15
  %18 = select i1 %17, i8 0, i8 undef
  %19 = and i1 true, true
  %20 = and i1 %19, %5
  %21 = add i1 %0, %0, !dbg !16
  call void @llvm.dbg.declare(metadata !{i1 %21}, metadata !20)
  %22 = or i1 false, %20
  %23 = select i1 %20, i1 %21, i1 undef
  %24 = and i1 true, true
  %25 = and i1 %24, %7
  %26 = add i1 %0, %0, !dbg !16
  call void @llvm.dbg.declare(metadata !{i1 %26}, metadata !21)
  %27 = or i1 %22, %25
  %28 = select i1 %25, i1 %26, i1 %23
  call void @llvm.dbg.declare(metadata !{i1 %28}, metadata !22)
  %29 = and i1 true, %27
  %30 = select i1 %29, i8 1, i8 %18
  %31 = insertvalue %0 undef, i1 %16, 0
  %32 = insertvalue %0 %31, i1 %28, 1
  %33 = insertvalue %0 %32, i8 %30, 2
  ret %0 %33, !dbg !16
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_if_join_2value", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_if_join_2value] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, %0 (i1)* @0, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_if_join_2value", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !12}
!9 = metadata !{i32 786451, metadata !6, metadata !"", metadata !6, i32 0, i64 2, i64 0, i32 0, i32 0, null, metadata !10, i32 0, i32 0, i32 0} ; [ DW_TAG_structure_type ] [line 0, size 2, align 0, offset 0] [from ]
!10 = metadata !{metadata !11, metadata !13, metadata !14}
!11 = metadata !{i32 786445, metadata !6, metadata !"", metadata !6, i32 0, i64 1, i64 0, i64 0, i32 0, metadata !12} ; [ DW_TAG_member ] [line 0, size 1, align 0, offset 0] [from int1]
!12 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!13 = metadata !{i32 786445, metadata !6, metadata !"", metadata !6, i32 0, i64 1, i64 0, i64 1, i32 0, metadata !12} ; [ DW_TAG_member ] [line 0, size 1, align 0, offset 1] [from int1]
!14 = metadata !{i32 786468, null, metadata !"int8", null, i32 0, i64 8, i64 0, i64 0, i32 0, i32 8} ; [ DW_TAG_base_type ] [int8] [line 0, size 8, align 0, offset 0, enc DW_ATE_unsigned_char]
!15 = metadata !{i32 786689, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [parameter1] [line 0]
!16 = metadata !{i32 0, i32 0, metadata !5, null}
!17 = metadata !{i32 786688, metadata !5, metadata !"add1", metadata !6, i32 0, metadata !12, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [add1] [line 0]
!18 = metadata !{i32 786688, metadata !5, metadata !"add2", metadata !6, i32 0, metadata !12, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [add2] [line 0]
!19 = metadata !{i32 786688, metadata !5, metadata !"join1", metadata !6, i32 0, metadata !12, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [join1] [line 0]
!20 = metadata !{i32 786688, metadata !5, metadata !"add3", metadata !6, i32 0, metadata !12, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [add3] [line 0]
!21 = metadata !{i32 786688, metadata !5, metadata !"add4", metadata !6, i32 0, metadata !12, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [add4] [line 0]
!22 = metadata !{i32 786688, metadata !5, metadata !"join2", metadata !6, i32 0, metadata !12, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [join2] [line 0]
)%%%";

extern char const * const generate_if_join_load_expected = R"%%%(
define i1 @0(i1) {
  call void @llvm.dbg.declare(metadata !{i1 %0}, metadata !10)
  %2 = and i1 true, true
  %3 = icmp eq i1 %0, false
  %4 = and i1 %2, %3
  %5 = icmp eq i1 %0, true
  %6 = and i1 %2, %5
  %7 = and i1 true, %4
  br i1 %7, label %8, label %10

; <label>:8                                       ; preds = %1
  %9 = load i1* null, !dbg !11
  br label %10

; <label>:10                                      ; preds = %8, %1
  %11 = phi i1 [ %9, %8 ], [ undef, %1 ]
  call void @llvm.dbg.declare(metadata !{i1 %11}, metadata !13)
  %12 = or i1 false, %7
  %13 = select i1 %7, i1 %11, i1 undef
  %14 = and i1 true, %6
  br i1 %14, label %15, label %17

; <label>:15                                      ; preds = %10
  %16 = load i1* null, !dbg !11
  br label %17

; <label>:17                                      ; preds = %15, %10
  %18 = phi i1 [ %16, %15 ], [ undef, %10 ]
  call void @llvm.dbg.declare(metadata !{i1 %18}, metadata !15)
  %19 = or i1 %12, %14
  %20 = select i1 %14, i1 %18, i1 %13
  call void @llvm.dbg.declare(metadata !{i1 %20}, metadata !16)
  ret i1 %20, !dbg !17
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_if_join_load", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_if_join_load] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i1 (i1)* @0, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_if_join_load", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786689, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [parameter1] [line 0]
!11 = metadata !{i32 0, i32 0, metadata !12, null}
!12 = metadata !{i32 786443, metadata !5, i32 0, i32 0, metadata !6, i32 15} ; [ DW_TAG_lexical_block ] [/generate_if_join_load]
!13 = metadata !{i32 786688, metadata !5, metadata !"load1", metadata !6, i32 0, metadata !14, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [load1] [line 0]
!14 = metadata !{i32 786447, null, metadata !"ptr", null, i32 0, i64 8, i64 0, i64 0, i32 0, metadata !9} ; [ DW_TAG_pointer_type ] [ptr] [line 0, size 8, align 0, offset 0] [from int1]
!15 = metadata !{i32 786688, metadata !5, metadata !"load2", metadata !6, i32 0, metadata !14, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [load2] [line 0]
!16 = metadata !{i32 786688, metadata !5, metadata !"join1", metadata !6, i32 0, metadata !14, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [join1] [line 0]
!17 = metadata !{i32 0, i32 0, metadata !5, null}
)%%%";

extern char const * const generate_call_0_expected = R"%%%(
define void @0() {
  ret void, !dbg !10
}

define void @1() {
  br i1 true, label %1, label %2

; <label>:1                                       ; preds = %0
  call void @0(), !dbg !11
  br label %2

; <label>:2                                       ; preds = %0, %1
  ret void, !dbg !13
}

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_call_0", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_call_0] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !9}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void ()* @0, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_call_0", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{null}
!9 = metadata !{i32 786478, i32 0, metadata !6, metadata !"1", metadata !"1", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void ()* @1, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [1]
!10 = metadata !{i32 0, i32 0, metadata !5, null}
!11 = metadata !{i32 0, i32 0, metadata !12, null}
!12 = metadata !{i32 786443, metadata !9, i32 0, i32 0, metadata !6, i32 17} ; [ DW_TAG_lexical_block ] [/generate_call_0]
!13 = metadata !{i32 0, i32 0, metadata !9, null}
)%%%";

extern char const * const generate_call_1_expected = R"%%%(
define i1 @0(i1) {
  call void @llvm.dbg.declare(metadata !{i1 %0}, metadata !11)
  ret i1 %0, !dbg !12
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

define i1 @1(i1) {
  call void @llvm.dbg.declare(metadata !{i1 %0}, metadata !13)
  %2 = and i1 true, true
  br i1 %2, label %3, label %5

; <label>:3                                       ; preds = %1
  %4 = call i1 @0(i1 %0), !dbg !14
  br label %5

; <label>:5                                       ; preds = %1, %3
  %6 = phi i1 [ %4, %3 ], [ undef, %1 ]
  ret i1 %6, !dbg !16
}

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_call_1", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_call_1] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !10}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i1 (i1)* @0, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_call_1", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786478, i32 0, metadata !6, metadata !"1", metadata !"1", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i1 (i1)* @1, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [1]
!11 = metadata !{i32 786689, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [parameter1] [line 0]
!12 = metadata !{i32 0, i32 0, metadata !5, null}
!13 = metadata !{i32 786689, metadata !10, metadata !"parameter2", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [parameter2] [line 0]
!14 = metadata !{i32 0, i32 0, metadata !15, null}
!15 = metadata !{i32 786443, metadata !10, i32 0, i32 0, metadata !6, i32 19} ; [ DW_TAG_lexical_block ] [/generate_call_1]
!16 = metadata !{i32 0, i32 0, metadata !10, null}
)%%%";

extern char const * const generate_call_2_expected = R"%%%(
define i8 @0(i1) {
  call void @llvm.dbg.declare(metadata !{i1 %0}, metadata !11)
  %2 = and i1 true, true
  %3 = icmp eq i1 %0, false
  %4 = and i1 %2, %3
  %5 = icmp eq i1 %0, true
  %6 = and i1 %2, %5
  %7 = and i1 true, %4
  %8 = select i1 %7, i8 0, i8 undef
  %9 = and i1 true, %6
  %10 = select i1 %9, i8 1, i8 %8
  ret i8 %10, !dbg !12
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

define i8 @1(i1) {
  call void @llvm.dbg.declare(metadata !{i1 %0}, metadata !13)
  %2 = and i1 true, true
  br i1 %2, label %3, label %5

; <label>:3                                       ; preds = %1
  %4 = call i8 @0(i1 %0), !dbg !14
  br label %5

; <label>:5                                       ; preds = %1, %3
  %6 = phi i8 [ %4, %3 ], [ undef, %1 ]
  %7 = icmp eq i8 %6, 0
  %8 = and i1 %2, %7
  %9 = icmp eq i8 %6, 1
  %10 = and i1 %2, %9
  %11 = and i1 true, %8
  %12 = select i1 %11, i8 0, i8 undef
  %13 = and i1 true, %10
  %14 = select i1 %13, i8 1, i8 %12
  ret i8 %14, !dbg !16
}

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_call_2", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_call_2] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !10}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i8 (i1)* @0, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_call_2", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{null, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786478, i32 0, metadata !6, metadata !"1", metadata !"1", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i8 (i1)* @1, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [1]
!11 = metadata !{i32 786689, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [parameter1] [line 0]
!12 = metadata !{i32 0, i32 0, metadata !5, null}
!13 = metadata !{i32 786689, metadata !10, metadata !"parameter2", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [parameter2] [line 0]
!14 = metadata !{i32 0, i32 0, metadata !15, null}
!15 = metadata !{i32 786443, metadata !10, i32 0, i32 0, metadata !6, i32 21} ; [ DW_TAG_lexical_block ] [/generate_call_2]
!16 = metadata !{i32 0, i32 0, metadata !10, null}
)%%%";

extern char const * const generate_call_3_expected = R"%%%(
%0 = type { i32, i32, i8 }

define %0 @0(i1) {
  call void @llvm.dbg.declare(metadata !{i1 %0}, metadata !19)
  %2 = and i1 true, true
  %3 = icmp eq i1 %0, false
  %4 = and i1 %2, %3
  %5 = icmp eq i1 %0, true
  %6 = and i1 %2, %5
  %7 = and i1 true, %4
  %8 = and i1 %7, true
  %9 = select i1 %8, i8 0, i8 undef
  %10 = and i1 true, %6
  %11 = and i1 %10, true
  %12 = select i1 %11, i8 1, i8 %9
  %13 = insertvalue %0 undef, i32 1, 0
  %14 = insertvalue %0 %13, i32 2, 1
  %15 = insertvalue %0 %14, i8 %12, 2
  ret %0 %15, !dbg !20
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

define i8 @1(i1) {
  call void @llvm.dbg.declare(metadata !{i1 %0}, metadata !21)
  %2 = and i1 true, true
  br i1 %2, label %3, label %5

; <label>:3                                       ; preds = %1
  %4 = call %0 @0(i1 %0), !dbg !22
  br label %5

; <label>:5                                       ; preds = %1, %3
  %6 = phi %0 [ %4, %3 ], [ undef, %1 ]
  %7 = extractvalue %0 %6, 2
  %8 = icmp eq i8 %7, 0
  %9 = and i1 %2, %8
  %10 = extractvalue %0 %6, 0
  %11 = icmp eq i8 %7, 1
  %12 = and i1 %2, %11
  %13 = extractvalue %0 %6, 1
  %14 = icmp eq i8 %7, 2
  %15 = and i1 %2, %14
  %16 = and i1 true, %9
  %17 = select i1 %16, i8 0, i8 undef
  %18 = and i1 true, %12
  %19 = select i1 %18, i8 1, i8 %17
  ret i8 %19, !dbg !24
}

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_call_3", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_call_3] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !16}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, %0 (i1)* @0, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_call_3", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !15}
!9 = metadata !{i32 786451, metadata !6, metadata !"", metadata !6, i32 0, i64 64, i64 0, i32 0, i32 0, null, metadata !10, i32 0, i32 0, i32 0} ; [ DW_TAG_structure_type ] [line 0, size 64, align 0, offset 0] [from ]
!10 = metadata !{metadata !11, metadata !13, metadata !14}
!11 = metadata !{i32 786445, metadata !6, metadata !"", metadata !6, i32 0, i64 32, i64 0, i64 0, i32 0, metadata !12} ; [ DW_TAG_member ] [line 0, size 32, align 0, offset 0] [from int32]
!12 = metadata !{i32 786468, null, metadata !"int32", null, i32 0, i64 32, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int32] [line 0, size 32, align 0, offset 0, enc DW_ATE_unsigned]
!13 = metadata !{i32 786445, metadata !6, metadata !"", metadata !6, i32 0, i64 32, i64 0, i64 32, i32 0, metadata !12} ; [ DW_TAG_member ] [line 0, size 32, align 0, offset 32] [from int32]
!14 = metadata !{i32 786468, null, metadata !"int8", null, i32 0, i64 8, i64 0, i64 0, i32 0, i32 8} ; [ DW_TAG_base_type ] [int8] [line 0, size 8, align 0, offset 0, enc DW_ATE_unsigned_char]
!15 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!16 = metadata !{i32 786478, i32 0, metadata !6, metadata !"1", metadata !"1", metadata !"", metadata !6, i32 0, metadata !17, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i8 (i1)* @1, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [1]
!17 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !18, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!18 = metadata !{null, metadata !15}
!19 = metadata !{i32 786689, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !15, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [parameter1] [line 0]
!20 = metadata !{i32 0, i32 0, metadata !5, null}
!21 = metadata !{i32 786689, metadata !16, metadata !"parameter2", metadata !6, i32 0, metadata !15, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [parameter2] [line 0]
!22 = metadata !{i32 0, i32 0, metadata !23, null}
!23 = metadata !{i32 786443, metadata !16, i32 0, i32 0, metadata !6, i32 23} ; [ DW_TAG_lexical_block ] [/generate_call_3]
!24 = metadata !{i32 0, i32 0, metadata !16, null}
)%%%";

extern char const * const generate_call_predicate_b1v0_expected = R"%%%(
define void @0() {
  ret void, !dbg !10
}

define void @1() {
  br i1 true, label %1, label %2

; <label>:1                                       ; preds = %0
  call void @0(), !dbg !11
  br label %2

; <label>:2                                       ; preds = %0, %1
  ret void, !dbg !13
}

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_call_predicate_b1v0", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_call_predicate_b1v0] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !9}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void ()* @0, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_call_predicate_b1v0", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{null}
!9 = metadata !{i32 786478, i32 0, metadata !6, metadata !"1", metadata !"1", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void ()* @1, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [1]
!10 = metadata !{i32 0, i32 0, metadata !5, null}
!11 = metadata !{i32 0, i32 0, metadata !12, null}
!12 = metadata !{i32 786443, metadata !9, i32 0, i32 0, metadata !6, i32 25} ; [ DW_TAG_lexical_block ] [/generate_call_predicate_b1v0]
!13 = metadata !{i32 0, i32 0, metadata !9, null}
)%%%";

extern char const * const generate_call_predicate_b1v1_expected = R"%%%(
define void @0() {
  ret void, !dbg !13
}

define i1 @1() {
  br i1 true, label %1, label %2

; <label>:1                                       ; preds = %0
  call void @0(), !dbg !14
  br label %2

; <label>:2                                       ; preds = %0, %1
  ret i1 false, !dbg !16
}

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_call_predicate_b1v1", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_call_predicate_b1v1] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !9}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void ()* @0, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_call_predicate_b1v1", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{null}
!9 = metadata !{i32 786478, i32 0, metadata !6, metadata !"1", metadata !"1", metadata !"", metadata !6, i32 0, metadata !10, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i1 ()* @1, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [1]
!10 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !11, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!11 = metadata !{metadata !12}
!12 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!13 = metadata !{i32 0, i32 0, metadata !5, null}
!14 = metadata !{i32 0, i32 0, metadata !15, null}
!15 = metadata !{i32 786443, metadata !9, i32 0, i32 0, metadata !6, i32 27} ; [ DW_TAG_lexical_block ] [/generate_call_predicate_b1v1]
!16 = metadata !{i32 0, i32 0, metadata !9, null}
)%%%";

extern char const * const generate_loop1_expected = R"%%%(
define void @0(i1) {
  call void @llvm.dbg.declare(metadata !{i1 %0}, metadata !10)
  %2 = and i1 true, true
  br i1 %2, label %3, label %21

; <label>:3                                       ; preds = %3, %1
  %4 = phi i1 [ %0, %1 ], [ %6, %3 ]
  %5 = and i1 %2, true
  %6 = add i1 %4, true, !dbg !11
  %7 = and i1 %2, %5
  %8 = and i1 %2, true
  %9 = icmp eq i1 %4, false, !dbg !12
  %10 = and i1 true, %8
  %11 = icmp eq i1 %9, false
  %12 = and i1 %10, %11
  %13 = icmp eq i1 %9, false
  %14 = and i1 %10, %13
  %15 = icmp eq i1 %9, true
  %16 = and i1 %10, %15
  %17 = icmp eq i1 %9, true
  %18 = and i1 %10, %17
  %19 = and i1 %7, %14
  %20 = and i1 %2, %14
  br i1 %19, label %3, label %21

; <label>:21                                      ; preds = %3, %1
  %22 = phi i1 [ undef, %1 ], [ %20, %3 ]
  ret void, !dbg !11
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_loop1", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_loop1] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void (i1)* @0, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_loop1", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{null, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786689, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [parameter1] [line 0]
!11 = metadata !{i32 0, i32 0, metadata !5, null}
!12 = metadata !{i32 0, i32 0, metadata !13, null}
!13 = metadata !{i32 786443, metadata !5, i32 0, i32 0, metadata !6, i32 28} ; [ DW_TAG_lexical_block ] [/generate_loop1]
)%%%";

extern char const * const generate_loop_count_expected = R"%%%(
define i32 @0(i32) {
  call void @llvm.dbg.declare(metadata !{i32 %0}, metadata !10)
  %2 = and i1 true, true
  %3 = and i1 %2, true
  br i1 %3, label %4, label %25

; <label>:4                                       ; preds = %4, %1
  %5 = phi i32 [ %0, %1 ], [ %8, %4 ]
  %6 = phi i32 [ 0, %1 ], [ %11, %4 ]
  %7 = and i1 true, %2
  %8 = add i32 1, %5, !dbg !11
  %9 = and i1 %3, %7
  %10 = and i1 true, %3
  %11 = add i32 1, %6, !dbg !11
  %12 = and i1 %9, %10
  %13 = and i1 %2, true
  %14 = icmp eq i32 %5, 0, !dbg !12
  %15 = and i1 true, %13
  %16 = icmp eq i1 %14, false
  %17 = and i1 %15, %16
  %18 = icmp eq i1 %14, true
  %19 = and i1 %15, %18
  %20 = and i1 %15, true
  %21 = and i1 %20, true
  %22 = and i1 %12, %17
  %23 = and i1 %3, %3
  %24 = and i1 %23, %19
  br i1 %22, label %4, label %25

; <label>:25                                      ; preds = %4, %1
  %26 = phi i32 [ undef, %1 ], [ %6, %4 ]
  %27 = phi i1 [ undef, %1 ], [ %3, %4 ]
  ret i32 %26, !dbg !11
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_loop_count", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_loop_count] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i32 (i32)* @0, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_loop_count", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int32", null, i32 0, i64 32, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int32] [line 0, size 32, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786689, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [parameter1] [line 0]
!11 = metadata !{i32 0, i32 0, metadata !5, null}
!12 = metadata !{i32 0, i32 0, metadata !13, null}
!13 = metadata !{i32 786443, metadata !5, i32 0, i32 0, metadata !6, i32 29} ; [ DW_TAG_lexical_block ] [/generate_loop_count]
)%%%";

extern char const * const generate_asm_expected = R"%%%(
define void @0() {
  br i1 true, label %1, label %2

; <label>:1                                       ; preds = %0
  call void asm sideeffect "text", ""()
  br label %2

; <label>:2                                       ; preds = %1, %0
  ret void, !dbg !9
}

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_asm", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_asm] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void ()* @0, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_asm", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{null}
!9 = metadata !{i32 0, i32 0, metadata !5, null}
)%%%";