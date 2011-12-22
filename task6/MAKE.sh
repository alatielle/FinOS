gcc -c printc.c
ld --script scr.ld -o 1 printc.o
objcopy -O binary 1 2
nasm a.asm
cat a 2 > res
rm printc.o
rm 1
rm 2
rm a