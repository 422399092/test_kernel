extern trace;(char*, int)
extern test_c;(int loop)
extern wait_c
section .data            ; 数据段声明
        msg db "调用内核功能test.", 0xA     ; 要输出的字符串
        len equ $ - msg                 ; 字串长度
        num dd 10
        idx dd 0
section .text            ; 代码段声明
global _start            ; 指定入口函数
_start:                  ; 在屏幕上显示一个字符串
        mov eax,len
        push eax
        mov eax,msg
        push eax
        call trace

        mov eax, [num]
        push eax
        call test_c
        add esp, 4
loop:
        mov eax, [num]
        mov ebx, [idx]
        cmp ebx, eax
        jnb loop_end
        mov eax, len
        push eax
        mov eax, msg
        push eax
        call trace
        mov ebx, [idx]
        inc ebx
        mov [idx], ebx
        jmp loop
loop_end:
        nop              ; 退出程序
        mov ebx, 0       ; 参数一：退出代码
        mov eax, 1       ; 系统调用号(sys_exit)
        int 0x80         ; 调用内核功能
