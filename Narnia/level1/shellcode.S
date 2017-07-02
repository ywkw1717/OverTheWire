      .section .text
      .global main
      .type main, @function
main:
      xor    eax, eax
      push   eax
      push   0x68732f2f
      push   0x6e69622f
      mov    eax, 0xb
      mov    ebx, esp
      mov    ecx, eax
      mov    edx, eax
      int    0x80
      ret
