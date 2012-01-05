gcc -c -m32 -march=i386  printsome.c -o print.o
gcc -c -m32 -march=i386  gpf.c -o gpf.o
nasm -f elf main.asm -o main.o
nasm -f elf idt_ld.asm -o idt_ld.o
nasm -f elf gpfhandler.asm -o gpfhandler.o
ld --script scr.ld -o kernel print.o gpf.o main.o idt_ld.o gpfhandler.o
objcopy -O binary kernel s

rm print.o
rm gpf.o
rm main.o
rm idt_ld.o
rm gpfhandler.o
rm kernel