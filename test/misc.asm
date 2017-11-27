;%define STACK_PARAM_1 [ebp + 4]
;%define STACK_PARAM_2 [ebp + 8]
;%define STACK_PARAM_3 [ebp + 12]
;%define STACK_PARAM_4 [ebp + 16]
;%define STACK_PARAM_5 [ebp + 20]
;%define STACK_PARAM_6 [ebp + 24]
;%define STACK_PARAM_7 [ebp + 28]
;%define STACK_PARAM_8 [ebp + 32]
;%define STACK_PARAM_9 [ebp + 36]
%define STACK_PARAM_1 [ebp + 8];0 return addr, 4 ebp adder
%define STACK_PARAM_2 [ebp + 12]
%define STACK_PARAM_3 [ebp + 16]
%define STACK_PARAM_4 [ebp + 20]
%define STACK_PARAM_5 [ebp + 24]
%define STACK_PARAM_6 [ebp + 28]
%define STACK_PARAM_7 [ebp + 32]
%define STACK_PARAM_8 [ebp + 36]
%define STACK_PARAM_9 [ebp + 40]

[section .text]         ;代码段开始
global trace,trace_by_c


trace:;(char*, int)
        push ebp
        mov ebp, esp
        mov edx, STACK_PARAM_2; 参数三：字符串长度
        mov ecx, STACK_PARAM_1; 参数二：要显示的字符串
        mov ebx, 1       ; 参数一：文件描述符(stdout)
        mov eax, 4       ; 系统调用号(sys_write)
        int 80h          ; 调用内核功能
        pop ebp
        ret 8            ;pop 2 param bytes

trace_by_c:;(char*, int)
        mov edx, [esp+8]; 参数三：字符串长度
        mov ecx, [esp+4]; 参数二：要显示的字符串
        mov ebx, 1       ; 参数一：文件描述符(stdout)
        mov eax, 4       ; 系统调用号(sys_write)
        int 80h          ; 调用内核功能
        ret
