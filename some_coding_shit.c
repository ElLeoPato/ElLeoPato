#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#define BUFFER_SIZE 4096

typedef int (*FunctionType)();

int main() {
    void *EXEC_MEM = mmap(NULL, BUFFER_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (EXEC_MEM == MAP_FAILED) {
        perror("mmap");
        return 1;
    }
  
    unsigned char SHELLCODE[] = {
        0x48, 0xC7, 0xC0, 0x45, 0x00, 0x00, 0x00, 0xC3 // mov rax, 0x2a + ret
    };

    memcpy(EXEC_MEM, SHELLCODE, sizeof(SHELLCODE));
    FunctionType FUNC = (FunctionType)EXEC_MEM;
    int RESULT = FUNC();
    munmap(EXEC_MEM, BUFFER_SIZE);
    printf("%d\n", RESULT);
    return 0;
}
