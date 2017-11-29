incbin "bin/boot.bin"
incbin "bin/kernel.bin"
; fill 1MBytes
times 1048576 - ($ - $$) db 0
