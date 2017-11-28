boot_seg       	      equ 0x07c0;31KB,   segment 0x7c00
ss_seg                equ 0x8000;512KB   segment 0x80000
kernel_bin_seg        equ 0x5000;320KB,  segment 0x50000
kernel_seg            equ 0x1000;64KB,   segment 0x10000

jmp start

start:
  mov ax,boot_seg
  mov	ds,ax
  mov	es,ax
  mov ax,ss_seg
  mov	ss,ax
  mov	sp,200h

  mov ax,0x0600
	mov cx,0x0000
	mov dx,0x174f
	mov bh,0x00
	int 0x10

  call read_kernel
  mov ax,disp_loader_sys
  mov cx,13
  mov bp,ax
  mov ax,0x1301
  mov bx,15
  mov dx,0x0101
  int 0x10

setA20.1:
  in      al, 0x64
  test    al, 0x2
  jnz     setA20.1
  mov     al, 0xd1
  out     byte 0x64, al
setA20.2:
  in      al, 0x64
  test    al, 0x2
  jnz     setA20.2
  mov     al, 0xdf
  out     byte 0x60, al
init_gdtr:
  cli;close all int
  lidt [idtr]
	lgdt [gdtr]
	mov	ax, 0x0001
	lmsw	ax ;switch on PE in cr0
	; jmp $ ;test
	jmp dword 0x08:0x0

read_kernel:; read 128KB kernel img to 0x50000
  push es
	mov ax,kernel_bin_seg
	mov es,ax
	mov ch,0
	mov cl,2
	mov dh,0
read_kernel_0:
	mov ax,0x0201
	mov bx,0x0000
	mov dl,0x00
	int 0x13
	jnc read_kernel_1
	jmp read_kernel_end
read_kernel_1:
	mov ax,es
	add ax,0x0020
	mov es,ax
	add cl,1
	cmp cl,18 ; <= 18
	jbe read_kernel_0
	add ch,1
	cmp ch,15 ; < 80
	jb  read_kernel_0
read_kernel_end:
  mov	dl, 0x00
  mov	ah, 0x00
  int 0x13
  pop es
ret

disp_loader_sys        db "laoding sys.."

gdt:
	dw 0, 0, 0, 0
kernel_code_desc:
	dw	0x07FF
	dw	0x0000
	dw	0x9A05
	dw	0x00C0
kernel_data_desc:
	dw	0x07FF
	dw	0x0000
	dw	0x9200
	dw	0x00C0
test_video_desc:;video addr:0B8000h
	dw	0x07FF
	dw	0x8000
	dw	0x920B
	dw	0x00C0
gdt_end:

idtr:
	dw	0			;// idt limit=0
	dw	0,0			;// idt base=0L
gdtr:
    dw  0x800
    dd  0x7c00 + gdt

times 510-($-$$)  db 0
dw 0xaa55
