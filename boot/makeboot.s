incbin "bin/boot.bin"
incbin "bin/enter.bin"
; fill 1.44MBytes
times 1474560 - ($ - $$) db 0
