extern void printc() {
        *(char *)0xb8000 = 'A'; 
}

