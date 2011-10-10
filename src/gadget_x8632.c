/*
** RopGadget - Release v3.2
** Jonathan Salwan - http://twitter.com/JonathanSalwan
** http://shell-storm.org
** 2011-10-10
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
*/

#include "ropgadget.h"

#define NB_GADGET   (sizeof(tab_x8632) / sizeof(tab_x8632[0])) - 2

/*
** If you want, you can add your gadgets in tab_x8632[]
** {FLAG, ADDR, INSTRUCTION, HEX INSTRUCTION, SIZE OPCODE}
*/
t_asm tab_x8632[] =
{
  /* hard opcode */
  {0, 0, "int $0x80", "\xcd\x80", 2},
  {0, 0, "sysenter", "\x0f\x34", 2},
  {0, 0, "call *%eax", "\xff\xd0", 2},
  {0, 0, "call *%ebx", "\xff\xd3", 2},
  {0, 0, "call *%ecx", "\xff\xd1", 2},
  {0, 0, "call *%edx", "\xff\xd2", 2},
  {0, 0, "call *%esi", "\xff\xd6", 2},
  {0, 0, "call *%edi", "\xff\xd7", 2},
  {0, 0, "call *(%eax)", "\xff\x10", 2},
  {0, 0, "call *(%ebx)", "\xff\x13", 2},
  {0, 0, "call *(%ecx)", "\xff\x11", 2},
  {0, 0, "call *(%edx)", "\xff\x12", 2},
  {0, 0, "call *(%esi)", "\xff\x16", 2},
  {0, 0, "call *(%edi)", "\xff\x17", 2},
  {0, 0, "jmp *%eax", "\xff\xe0", 2},
  {0, 0, "jmp *%ebx", "\xff\xe3", 2},
  {0, 0, "jmp *%ecx", "\xff\xe1", 2},
  {0, 0, "jmp *%edx", "\xff\xe2", 2},
  {0, 0, "jmp *%esi", "\xff\xe6", 2},
  {0, 0, "jmp *%edi", "\xff\xe7", 2},
  {0, 0, "jmp *(%eax)", "\xff\x20", 2},
  {0, 0, "jmp *(%ebx)", "\xff\x23", 2},
  {0, 0, "jmp *(%ecx)", "\xff\x21", 2},
  {0, 0, "jmp *(%edx)", "\xff\x22", 2},
  {0, 0, "jmp *(%esi)", "\xff\x26", 2},
  {0, 0, "jmp *(%edi)", "\xff\x27", 2},
  {0, 0, "pusha | ret", "\x60\xc3", 2},
  {0, 0, "popa | ret", "\x61\xc3", 2},
  {0, 0, "push %eax | ret", "\x50\xc3", 2},
  {0, 0, "push %ebx | ret", "\x53\xc3", 2},
  {0, 0, "push %ecx | ret", "\x51\xc3", 2},
  {0, 0, "push %edx | ret", "\x52\xc3", 2},
  {0, 0, "push %esi | ret", "\x56\xc3", 2},
  {0, 0, "push %edi | ret", "\x57\xc3", 2},
  {0, 0, "push %ebp | ret", "\x55\xc3", 2},
  {0, 0, "push %esp | ret", "\x54\xc3", 2},
  {0, 0, "pop %esp | ret", "\x5c\xc3", 2},
  {0, 0, "pop %ebp | ret", "\x5d\xc3", 2},
  {0, 0, "pop %eax | ret", "\x58\xc3", 2},
  {0, 0, "pop %ebx | ret", "\x5b\xc3", 2},
  {0, 0, "pop %ecx | ret", "\x59\xc3", 2},
  {0, 0, "pop %edx | ret", "\x5a\xc3", 2},
  {0, 0, "pop %esi | ret", "\x5e\xc3", 2},
  {0, 0, "pop %edi | ret", "\x5f\xc3", 2},
  {0, 0, "pop %ebx | pop %ebp | ret", "\x5b\x5d\xc3", 3},
  {0, 0, "pop %eax | pop %ebx | pop %esi | pop %edi | ret", "\x58\x5b\x5e\x5f\xc3", 5},
  {0, 0, "pop %ebx | pop %esi | pop %ebp | ret", "\x5b\x5e\x5d\xc3", 4},
  {0, 0, "pop %ebx | pop %esi | pop %edi | pop %ebp | ret", "\x5b\x5e\x5f\x5d\xc3", 5},
  {0, 0, "pop %esi | pop %ebx | pop %edx | ret", "\x5e\x5b\x5a\xc3", 4},
  {0, 0, "pop %edx | pop %ecx | pop %ebx | ret", "\x5a\x59\x5b\xc3", 4},
  {0, 0, "xor %eax,%eax | ret", "\x31\xc0\xc3", 3},
  {0, 0, "xor %ebx,%ebx | ret", "\x31\xdb\xc3", 3},
  {0, 0, "xor %ecx,%ecx | ret", "\x31\xc9\xc3", 3},
  {0, 0, "xor %edx,%edx | ret", "\x31\xd2\xc3", 3},
  {0, 0, "xor %esi,%esi | ret", "\x31\xf6\xc3", 3},
  {0, 0, "xor %edi,%edi | ret", "\x31\xf7\xc3", 3},
  {0, 0, "xor %eax,%eax | pop %ebx | pop %ebp | ret", "\x31\xc0\x5b\x5d\xc3", 5},
  {0, 0, "xor %eax,%eax | pop %ebx | pop %esi | pop %edi | pop %ebp | ret", "\x31\xc0\x5b\x5e\x5f\x5d\xc3", 7},
  {0, 0, "xor %eax,%eax | pop %edi | ret", "\x31\xc0\x5f\xc3", 4},
  {0, 0, "xor %eax,%eax | pop %ebx | ret", "\x31\xc0\x5b\xc3", 4},
  {0, 0, "xor %eax,%eax | mov %esp, %ebp | pop %ebp | ret", "\x31\xc0\x89\xe5\x5d\xc3", 6},
  {0, 0, "inc %eax | ret", "\x40\xc3", 2},
  {0, 0, "inc %ebx | ret", "\x43\xc3", 2},
  {0, 0, "inc %ecx | ret", "\x41\xc3", 2},
  {0, 0, "inc %edx | ret", "\x42\xc3", 2},
  {0, 0, "inc %esi | ret", "\x46\xc3", 2},
  {0, 0, "inc %edi | ret", "\x47\xc3", 2},
  {0, 0, "dec %eax | ret", "\x48\xc3", 2},
  {0, 0, "dec %ebx | ret", "\x4b\xc3", 2},
  {0, 0, "dec %ecx | ret", "\x49\xc3", 2},
  {0, 0, "dec %edx | ret", "\x4a\xc3", 2},
  {0, 0, "dec %esi | ret", "\x4e\xc3", 2},
  {0, 0, "dec %edi | ret", "\x4f\xc3", 2},
  {0, 0, "inc %eax | pop %edi | pop %esi | ret", "\x40\x5f\x5e\xc3", 4},
  {0, 0, "inc %eax | pop %edi | ret", "\x40\x5f\xc3", 3},
  {0, 0, "inc %eax | inc %eax | inc %eax | ret", "\x40\x40\x40\xc3", 4},
  {0, 0, "inc %eax | inc %eax | ret", "\x40\x40\xc3", 3},
  {0, 0, "sub $0x01,%eax | pop %ebx | pop %esi | pop %ebp | ret", "\x83\xe8\x01\x5b\x5e\x5d\xc3", 7},
  {0, 0, "sub %ebx,%eax | pop %ebx | pop %esi | pop %edi | pop %ebp | ret", "\x29\xd8\x5b\x5e\x5f\x5d\xc3", 7},
  {0, 0, "sub $0x01,%eax | pop %ebp | ret", "\x89\xe8\x01\x5d\xc3", 5},
  {0, 0, "add %ebx,%eax | pop %ebx | pop %ebp | ret", "\x01\xd8\x5b\x5d\xc3", 5},
  {0, 0, "mul %eax | ret", "\xf7\xe0\xc3", 3},
  {0, 0, "mul %ebx | ret", "\xf7\xe3\xc3", 3},
  {0, 0, "mul %ecx | ret", "\xf7\xe1\xc3", 3},
  {0, 0, "mul %edx | ret", "\xf7\xe2\xc3", 3},
  {0, 0, "mul %esi | ret", "\xf7\xe6\xc3", 3},
  {0, 0, "mul %edi | ret", "\xf7\xe7\xc3", 3},
  {0, 0, "mul %eax | pop %ebp | ret", "\xf7\xe0\x5d\xc3", 3},
  {0, 0, "mul %ebx | pop %ebp | ret", "\xf7\xe3\x5d\xc3", 3},
  {0, 0, "mul %ecx | pop %ebp | ret", "\xf7\xe1\x5d\xc3", 3},
  {0, 0, "mul %edx | pop %ebp | ret", "\xf7\xe2\x5d\xc3", 3},
  {0, 0, "mul %esi | pop %ebp | ret", "\xf7\xe6\x5d\xc3", 3},
  {0, 0, "mul %edi | pop %ebp | ret", "\xf7\xe7\x5d\xc3", 3},
  {0, 0, "div %eax | ret", "\xf7\xf0\xc3", 3},
  {0, 0, "div %ebx | ret", "\xf7\xf3\xc3", 3},
  {0, 0, "div %ecx | ret", "\xf7\xf1\xc3", 3},
  {0, 0, "div %edx | ret", "\xf7\xf2\xc3", 3},
  {0, 0, "div %esi | ret", "\xf7\xf6\xc3", 3},
  {0, 0, "div %edi | ret", "\xf7\xf7\xc3", 3},
  {0, 0, "div %eax | pop %ebp | ret", "\xf7\xf0\x5d\xc3", 3},
  {0, 0, "div %ebx | pop %ebp | ret", "\xf7\xf3\x5d\xc3", 3},
  {0, 0, "div %ecx | pop %ebp | ret", "\xf7\xf1\x5d\xc3", 3},
  {0, 0, "div %edx | pop %ebp | ret", "\xf7\xf2\x5d\xc3", 3},
  {0, 0, "div %esi | pop %ebp | ret", "\xf7\xf6\x5d\xc3", 3},
  {0, 0, "div %edi | pop %ebp | ret", "\xf7\xf7\x5d\xc3", 3},
  {0, 0, "neg %eax | ret", "\xf7\xd8\xc3", 3},
  {0, 0, "neg %ebx | ret", "\xf7\xdb\xc3", 3},
  {0, 0, "neg %ecx | ret", "\xf7\xd9\xc3", 3},
  {0, 0, "neg %edx | ret", "\xf7\xda\xc3", 3},
  {0, 0, "neg %esi | ret", "\xf7\xde\xc3", 3},
  {0, 0, "neg %edi | ret", "\xf7\xdf\xc3", 3},
  {0, 0, "neg %eax | pop %ebp | ret", "\xf7\xd8\x5d\xc3", 3},
  {0, 0, "neg %ebx | pop %ebp | ret", "\xf7\xdb\x5d\xc3", 3},
  {0, 0, "neg %ecx | pop %ebp | ret", "\xf7\xd9\x5d\xc3", 3},
  {0, 0, "neg %edx | pop %ebp | ret", "\xf7\xda\x5d\xc3", 3},
  {0, 0, "neg %esi | pop %ebp | ret", "\xf7\xde\x5d\xc3", 3},
  {0, 0, "neg %edi | pop %ebp | ret", "\xf7\xdf\x5d\xc3", 3},
  {0, 0, "not %eax | ret", "\xf7\xd0\xc3", 3},
  {0, 0, "not %ebx | ret", "\xf7\xd3\xc3", 3},
  {0, 0, "not %ecx | ret", "\xf7\xd1\xc3", 3},
  {0, 0, "not %edx | ret", "\xf7\xd2\xc3", 3},
  {0, 0, "not %esi | ret", "\xf7\xd6\xc3", 3},
  {0, 0, "not %edi | ret", "\xf7\xd7\xc3", 3},
  {0, 0, "not %eax | pop %ebp | ret", "\xf7\xd0\x5d\xc3", 3},
  {0, 0, "not %ebx | pop %ebp | ret", "\xf7\xd3\x5d\xc3", 3},
  {0, 0, "not %ecx | pop %ebp | ret", "\xf7\xd1\x5d\xc3", 3},
  {0, 0, "not %edx | pop %ebp | ret", "\xf7\xd2\x5d\xc3", 3},
  {0, 0, "not %esi | pop %ebp | ret", "\xf7\xd6\x5d\xc3", 3},
  {0, 0, "not %edi | pop %ebp | ret", "\xf7\xd7\x5d\xc3", 3},
  {0, 0, "shr %eax | ret", "\xd1\xe8\xc3", 3},
  {0, 0, "shr %ebx | ret", "\xd1\xeb\xc3", 3},
  {0, 0, "shr %ecx | ret", "\xd1\xe9\xc3", 3},
  {0, 0, "shr %edx | ret", "\xd1\xea\xc3", 3},
  {0, 0, "shr %esi | ret", "\xd1\xee\xc3", 3},
  {0, 0, "shr %edi | ret", "\xd1\xef\xc3", 3},
  {0, 0, "shl %eax | ret", "\xd1\xe0\xc3", 3},
  {0, 0, "shl %ebx | ret", "\xd1\xe3\xc3", 3},
  {0, 0, "shl %ecx | ret", "\xd1\xe1\xc3", 3},
  {0, 0, "shl %edx | ret", "\xd1\xe2\xc3", 3},
  {0, 0, "shl %esi | ret", "\xd1\xe6\xc3", 3},
  {0, 0, "shl %edi | ret", "\xd1\xe7\xc3", 3},
  {0, 0, "ror %eax | ret", "\xd1\xc8\xc3", 3},
  {0, 0, "ror %ebx | ret", "\xd1\xcb\xc3", 3},
  {0, 0, "ror %ecx | ret", "\xd1\xc9\xc3", 3},
  {0, 0, "ror %edx | ret", "\xd1\xca\xc3", 3},
  {0, 0, "ror %esi | ret", "\xd1\xce\xc3", 3},
  {0, 0, "ror %edi | ret", "\xd1\xcf\xc3", 3},
  {0, 0, "rol %eax | ret", "\xd1\xc0\xc3", 3},
  {0, 0, "rol %ebx | ret", "\xd1\xc3\xc3", 3},
  {0, 0, "rol %ecx | ret", "\xd1\xc1\xc3", 3},
  {0, 0, "rol %edx | ret", "\xd1\xc2\xc3", 3},
  {0, 0, "rol %esi | ret", "\xd1\xc6\xc3", 3},
  {0, 0, "rol %edi | ret", "\xd1\xc7\xc3", 3},
  {0, 0, "xchg %eax,%esp | ret", "\x94\xc3", 2},
  {0, 0, "xchg %eax,%ebx | ret", "\x93\xc3", 2},
  {0, 0, "xchg %eax,%ecx | ret", "\x91\xc3", 2},
  {0, 0, "xchg %eax,%edx | ret", "\x92\xc3", 2},
  {0, 0, "xchg %eax,%esi | ret", "\x96\xc3", 2},
  {0, 0, "xchg %eax,%edi | ret", "\x97\xc3", 2},
  {0, 0, "xchg %eax,%ebp | ret", "\x95\xc3", 2},
  {0, 0, "xchg %eax,%esp | pop %ebp | ret", "\x94\x5d\xc3", 2},
  {0, 0, "xchg %eax,%ebx | pop %ebp | ret", "\x93\x5d\xc3", 2},
  {0, 0, "xchg %eax,%ecx | pop %ebp | ret", "\x91\x5d\xc3", 2},
  {0, 0, "xchg %eax,%edx | pop %ebp | ret", "\x92\x5d\xc3", 2},
  {0, 0, "xchg %eax,%esi | pop %ebp | ret", "\x96\x5d\xc3", 2},
  {0, 0, "xchg %eax,%edi | pop %ebp | ret", "\x97\x5d\xc3", 2},
  {0, 0, "xchg %eax,%ebp | pop %ebp | ret", "\x95\x5d\xc3", 2},
  {0, 0, "bswap %eax | ret", "\x0f\xc8\xc3", 3},
  {0, 0, "bswap %ebx | ret", "\x0f\xcb\xc3", 3},
  {0, 0, "bswap %ecx | ret", "\x0f\xc9\xc3", 3},
  {0, 0, "bswap %edx | ret", "\x0f\xca\xc3", 3},
  {0, 0, "bswap %esi | ret", "\x0f\xce\xc3", 3},
  {0, 0, "bswap %edi | ret", "\x0f\xcf\xc3", 3},
  {0, 0, "bswap %eax | pop %ebp | ret", "\x0f\xc8\x5d\xc3", 3},
  {0, 0, "bswap %ebx | pop %ebp | ret", "\x0f\xcb\x5d\xc3", 3},
  {0, 0, "bswap %ecx | pop %ebp | ret", "\x0f\xc9\x5d\xc3", 3},
  {0, 0, "bswap %edx | pop %ebp | ret", "\x0f\xca\x5d\xc3", 3},
  {0, 0, "bswap %esi | pop %ebp | ret", "\x0f\xce\x5d\xc3", 3},
  {0, 0, "bswap %edi | pop %ebp | ret", "\x0f\xcf\x5d\xc3", 3},
  {0, 0, "mov %ebx,%eax | pop %ebx | pop %ebp | ret", "\x89\xd8\x5b\x5d\xc3", 5},
  {0, 0, "mov %edx,%eax | pop %ebx | pop %esi | pop %edi | pop %ebp | ret", "\x89\xd0\x5b\x5e\x5f\x5d\xc3", 7},
  {0, 0, "mov %edi,%eax | pop %ebx | pop %esi | pop %edi | pop %ebp | ret", "\x89\xf8\x5b\x5e\x5f\x5d\xc3", 7},
  {0, 0, "mov %ebx,%eax | pop %ebx | pop %esi | pop %edi | pop %ebp | ret", "\x89\xd8\x5b\x5e\x5f\x5d\xc3", 7},
  {0, 0, "mov %esi,%eax | pop %ebx | pop %esi | pop %edi | pop %ebp | ret", "\x89\xf0\x5b\x5e\x5f\x5d\xc3", 7},
  {0, 0, "mov %ecx,%eax | pop %ebx | pop %esi | pop %edi | pop %ebp | ret", "\x89\xc8\x5b\x5e\x5f\x5d\xc3", 7},
  {0, 0, "mov %ebx,%eax | pop %ebx | pop %esi | pop %ebp | ret", "\x89\xd8\x5b\x5e\x5d\xc3", 6},
  {0, 0, "mov %ebp,%esp | pop %ebp | ret", "\x89\xec\x5d\xc3", 4},
  {0, 0, "mov %esp,%eax | ret", "\x89\xe0\xc3", 3},
  {0, 0, "mov %esp,%ebx | ret", "\x89\xe3\xc3", 3},
  {0, 0, "mov %esp,%ecx | ret", "\x89\xe1\xc3", 3},
  {0, 0, "mov %esp,%edx | ret", "\x89\xe2\xc3", 3},
  {0, 0, "mov %esp,%ebp | ret", "\x89\xe5\xc3", 3},
  {0, 0, "mov %eax,%ebx | ret", "\x89\xc3\xc3", 3},
  {0, 0, "mov %eax,%ecx | ret", "\x89\xc1\xc3", 3},
  {0, 0, "mov %eax,%edx | ret", "\x89\xc2\xc3", 3},
  {0, 0, "mov %eax,%esi | ret", "\x89\xc6\xc3", 3},
  {0, 0, "mov %eax,%edi | ret", "\x89\xc7\xc3", 3},
  {0, 0, "mov %ebx,%eax | ret", "\x89\xd8\xc3", 3},
  {0, 0, "mov %ebx,%ecx | ret", "\x89\xd9\xc3", 3},
  {0, 0, "mov %ebx,%edx | ret", "\x89\xda\xc3", 3},
  {0, 0, "mov %ebx,%esi | ret", "\x89\xde\xc3", 3},
  {0, 0, "mov %ebx,%edi | ret", "\x89\xdf\xc3", 3},
  {0, 0, "mov %ecx,%eax | ret", "\x89\xc8\xc3", 3},
  {0, 0, "mov %ecx,%ebx | ret", "\x89\xcb\xc3", 3},
  {0, 0, "mov %ecx,%edx | ret", "\x89\xca\xc3", 3},
  {0, 0, "mov %ecx,%esi | ret", "\x89\xce\xc3", 3},
  {0, 0, "mov %ecx,%edi | ret", "\x89\xcf\xc3", 3},
  {0, 0, "mov %edx,%eax | ret", "\x89\xd0\xc3", 3},
  {0, 0, "mov %edx,%ebx | ret", "\x89\xd3\xc3", 3},
  {0, 0, "mov %edx,%ecx | ret", "\x89\xd1\xc3", 3},
  {0, 0, "mov %edx,%esi | ret", "\x89\xd6\xc3", 3},
  {0, 0, "mov %edx,%edi | ret", "\x89\xd7\xc3", 3},
  {0, 0, "mov %esi,%eax | ret", "\x89\xf0\xc3", 3},
  {0, 0, "mov %esi,%ebx | ret", "\x89\xf3\xc3", 3},
  {0, 0, "mov %esi,%ecx | ret", "\x89\xf1\xc3", 3},
  {0, 0, "mov %esi,%edx | ret", "\x89\xf2\xc3", 3},
  {0, 0, "mov %esi,%edi | ret", "\x89\xf7\xc3", 3},
  {0, 0, "mov %edi,%eax | ret", "\x89\xf8\xc3", 3},
  {0, 0, "mov %edi,%ebx | ret", "\x89\xfb\xc3", 3},
  {0, 0, "mov %edi,%ecx | ret", "\x89\xf9\xc3", 3},
  {0, 0, "mov %edi,%edx | ret", "\x89\xfa\xc3", 3},
  {0, 0, "mov %edi,%esi | ret", "\x89\xfe\xc3", 3},
  {0, 0, "mov %esp,%eax | pop %ebp | ret", "\x89\xe0\x5d\xc3", 4},
  {0, 0, "mov %esp,%ebx | pop %ebp | ret", "\x89\xe3\x5d\xc3", 4},
  {0, 0, "mov %esp,%ecx | pop %ebp | ret", "\x89\xe1\x5d\xc3", 4},
  {0, 0, "mov %esp,%edx | pop %ebp | ret", "\x89\xe2\x5d\xc3", 4},
  {0, 0, "mov %eax,%ebx | pop %ebp | ret", "\x89\xc3\x5d\xc3", 4},
  {0, 0, "mov %eax,%ecx | pop %ebp | ret", "\x89\xc1\x5d\xc3", 4},
  {0, 0, "mov %eax,%edx | pop %ebp | ret", "\x89\xc2\x5d\xc3", 4},
  {0, 0, "mov %eax,%esi | pop %ebp | ret", "\x89\xc6\x5d\xc3", 4},
  {0, 0, "mov %eax,%edi | pop %ebp | ret", "\x89\xc7\x5d\xc3", 4},
  {0, 0, "mov %ebx,%eax | pop %ebp | ret", "\x89\xd8\x5d\xc3", 4},
  {0, 0, "mov %ebx,%ecx | pop %ebp | ret", "\x89\xd9\x5d\xc3", 4},
  {0, 0, "mov %ebx,%edx | pop %ebp | ret", "\x89\xda\x5d\xc3", 4},
  {0, 0, "mov %ebx,%esi | pop %ebp | ret", "\x89\xde\x5d\xc3", 4},
  {0, 0, "mov %ebx,%edi | pop %ebp | ret", "\x89\xdf\x5d\xc3", 4},
  {0, 0, "mov %ecx,%eax | pop %ebp | ret", "\x89\xc8\x5d\xc3", 4},
  {0, 0, "mov %ecx,%ebx | pop %ebp | ret", "\x89\xcb\x5d\xc3", 4},
  {0, 0, "mov %ecx,%edx | pop %ebp | ret", "\x89\xca\x5d\xc3", 4},
  {0, 0, "mov %ecx,%esi | pop %ebp | ret", "\x89\xce\x5d\xc3", 4},
  {0, 0, "mov %ecx,%edi | pop %ebp | ret", "\x89\xcf\x5d\xc3", 4},
  {0, 0, "mov %edx,%eax | pop %ebp | ret", "\x89\xd0\x5d\xc3", 4},
  {0, 0, "mov %edx,%ebx | pop %ebp | ret", "\x89\xd3\x5d\xc3", 4},
  {0, 0, "mov %edx,%ecx | pop %ebp | ret", "\x89\xd1\x5d\xc3", 4},
  {0, 0, "mov %edx,%esi | pop %ebp | ret", "\x89\xd6\x5d\xc3", 4},
  {0, 0, "mov %edx,%edi | pop %ebp | ret", "\x89\xd7\x5d\xc3", 4},
  {0, 0, "mov %esi,%eax | pop %ebp | ret", "\x89\xf0\x5d\xc3", 4},
  {0, 0, "mov %esi,%ebx | pop %ebp | ret", "\x89\xf3\x5d\xc3", 4},
  {0, 0, "mov %esi,%ecx | pop %ebp | ret", "\x89\xf1\x5d\xc3", 4},
  {0, 0, "mov %esi,%edx | pop %ebp | ret", "\x89\xf2\x5d\xc3", 4},
  {0, 0, "mov %esi,%edi | pop %ebp | ret", "\x89\xf7\x5d\xc3", 4},
  {0, 0, "mov %edi,%eax | pop %ebp | ret", "\x89\xf8\x5d\xc3", 4},
  {0, 0, "mov %edi,%ebx | pop %ebp | ret", "\x89\xfb\x5d\xc3", 4},
  {0, 0, "mov %edi,%ecx | pop %ebp | ret", "\x89\xf9\x5d\xc3", 4},
  {0, 0, "mov %edi,%edx | pop %ebp | ret", "\x89\xfa\x5d\xc3", 4},
  {0, 0, "mov %edi,%esi | pop %ebp | ret", "\x89\xfe\x5d\xc3", 4},
  {0, 0, "mov (%eax),%ebx | ret", "\x8b\x18\xc3", 3},
  {0, 0, "mov (%eax),%ecx | ret", "\x8b\x08\xc3", 3},
  {0, 0, "mov (%eax),%edx | ret", "\x8b\x10\xc3", 3},
  {0, 0, "mov (%eax),%esi | ret", "\x8b\x30\xc3", 3},
  {0, 0, "mov (%eax),%edi | ret", "\x8b\x38\xc3", 3},
  {0, 0, "mov (%ebx),%eax | ret", "\x8b\x03\xc3", 3},
  {0, 0, "mov (%ebx),%ebx | ret", "\x8b\x1b\xc3", 3},
  {0, 0, "mov (%ebx),%ecx | ret", "\x8b\x0b\xc3", 3},
  {0, 0, "mov (%ebx),%edx | ret", "\x8b\x13\xc3", 3},
  {0, 0, "mov (%ebx),%esi | ret", "\x8b\x33\xc3", 3},
  {0, 0, "mov (%ebx),%edi | ret", "\x8b\x3b\xc3", 3},
  {0, 0, "mov (%ecx),%eax | ret", "\x8b\x01\xc3", 3},
  {0, 0, "mov (%ecx),%ebx | ret", "\x8b\x19\xc3", 3},
  {0, 0, "mov (%ecx),%ecx | ret", "\x8b\x09\xc3", 3},
  {0, 0, "mov (%ecx),%edx | ret", "\x8b\x11\xc3", 3},
  {0, 0, "mov (%ecx),%esi | ret", "\x8b\x31\xc3", 3},
  {0, 0, "mov (%ecx),%edi | ret", "\x8b\x39\xc3", 3},
  {0, 0, "mov (%edx),%eax | ret", "\x8b\x02\xc3", 3},
  {0, 0, "mov (%edx),%ebx | ret", "\x8b\x1a\xc3", 3},
  {0, 0, "mov (%edx),%ecx | ret", "\x8b\x0a\xc3", 3},
  {0, 0, "mov (%edx),%edx | ret", "\x8b\x12\xc3", 3},
  {0, 0, "mov (%edx),%esi | ret", "\x8b\x32\xc3", 3},
  {0, 0, "mov (%edx),%edi | ret", "\x8b\x3a\xc3", 3},
  {0, 0, "mov (%esi),%eax | ret", "\x8b\x06\xc3", 3},
  {0, 0, "mov (%esi),%ebx | ret", "\x8b\x1e\xc3", 3},
  {0, 0, "mov (%esi),%ecx | ret", "\x8b\x0e\xc3", 3},
  {0, 0, "mov (%esi),%edx | ret", "\x8b\x16\xc3", 3},
  {0, 0, "mov (%esi),%esi | ret", "\x8b\x36\xc3", 3},
  {0, 0, "mov (%esi),%edi | ret", "\x8b\x3e\xc3", 3},
  {0, 0, "mov (%edi),%eax | ret", "\x8b\x07\xc3", 3},
  {0, 0, "mov (%edi),%ebx | ret", "\x8b\x1f\xc3", 3},
  {0, 0, "mov (%edi),%ecx | ret", "\x8b\x0f\xc3", 3},
  {0, 0, "mov (%edi),%edx | ret", "\x8b\x17\xc3", 3},
  {0, 0, "mov (%edi),%esi | ret", "\x8b\x37\xc3", 3},
  {0, 0, "mov (%edi),%edi | ret", "\x8b\x3f\xc3", 3},
  {0, 0, "mov (%eax),%ebx | pop %ebp | ret", "\x8b\x18\x5d\xc3", 4},
  {0, 0, "mov (%eax),%ecx | pop %ebp | ret", "\x8b\x08\x5d\xc3", 4},
  {0, 0, "mov (%eax),%edx | pop %ebp | ret", "\x8b\x10\x5d\xc3", 4},
  {0, 0, "mov (%eax),%esi | pop %ebp | ret", "\x8b\x30\x5d\xc3", 4},
  {0, 0, "mov (%eax),%edi | pop %ebp | ret", "\x8b\x38\x5d\xc3", 4},
  {0, 0, "mov (%ebx),%eax | pop %ebp | ret", "\x8b\x03\x5d\xc3", 4},
  {0, 0, "mov (%ebx),%ebx | pop %ebp | ret", "\x8b\x1b\x5d\xc3", 4},
  {0, 0, "mov (%ebx),%ecx | pop %ebp | ret", "\x8b\x0b\x5d\xc3", 4},
  {0, 0, "mov (%ebx),%edx | pop %ebp | ret", "\x8b\x13\x5d\xc3", 4},
  {0, 0, "mov (%ebx),%esi | pop %ebp | ret", "\x8b\x33\x5d\xc3", 4},
  {0, 0, "mov (%ebx),%edi | pop %ebp | ret", "\x8b\x3b\x5d\xc3", 4},
  {0, 0, "mov (%ecx),%eax | pop %ebp | ret", "\x8b\x01\x5d\xc3", 4},
  {0, 0, "mov (%ecx),%ebx | pop %ebp | ret", "\x8b\x19\x5d\xc3", 4},
  {0, 0, "mov (%ecx),%ecx | pop %ebp | ret", "\x8b\x09\x5d\xc3", 4},
  {0, 0, "mov (%ecx),%edx | pop %ebp | ret", "\x8b\x11\x5d\xc3", 4},
  {0, 0, "mov (%ecx),%esi | pop %ebp | ret", "\x8b\x31\x5d\xc3", 4},
  {0, 0, "mov (%ecx),%edi | pop %ebp | ret", "\x8b\x39\x5d\xc3", 4},
  {0, 0, "mov (%edx),%eax | pop %ebp | ret", "\x8b\x02\x5d\xc3", 4},
  {0, 0, "mov (%edx),%ebx | pop %ebp | ret", "\x8b\x1a\x5d\xc3", 4},
  {0, 0, "mov (%edx),%ecx | pop %ebp | ret", "\x8b\x0a\x5d\xc3", 4},
  {0, 0, "mov (%edx),%edx | pop %ebp | ret", "\x8b\x12\x5d\xc3", 4},
  {0, 0, "mov (%edx),%esi | pop %ebp | ret", "\x8b\x32\x5d\xc3", 4},
  {0, 0, "mov (%edx),%edi | pop %ebp | ret", "\x8b\x3a\x5d\xc3", 4},
  {0, 0, "mov (%esi),%eax | pop %ebp | ret", "\x8b\x06\x5d\xc3", 4},
  {0, 0, "mov (%esi),%ebx | pop %ebp | ret", "\x8b\x1e\x5d\xc3", 4},
  {0, 0, "mov (%esi),%ecx | pop %ebp | ret", "\x8b\x0e\x5d\xc3", 4},
  {0, 0, "mov (%esi),%edx | pop %ebp | ret", "\x8b\x16\x5d\xc3", 4},
  {0, 0, "mov (%esi),%esi | pop %ebp | ret", "\x8b\x36\x5d\xc3", 4},
  {0, 0, "mov (%esi),%edi | pop %ebp | ret", "\x8b\x3e\x5d\xc3", 4},
  {0, 0, "mov (%edi),%eax | pop %ebp | ret", "\x8b\x07\x5d\xc3", 4},
  {0, 0, "mov (%edi),%ebx | pop %ebp | ret", "\x8b\x1f\x5d\xc3", 4},
  {0, 0, "mov (%edi),%ecx | pop %ebp | ret", "\x8b\x0f\x5d\xc3", 4},
  {0, 0, "mov (%edi),%edx | pop %ebp | ret", "\x8b\x17\x5d\xc3", 4},
  {0, 0, "mov (%edi),%esi | pop %ebp | ret", "\x8b\x37\x5d\xc3", 4},
  {0, 0, "mov (%edi),%edi | pop %ebp | ret", "\x8b\x3f\x5d\xc3", 4},
  {0, 0, "mov %eax,(%edx) | ret", "\x89\x02\xc3", 3},
  {0, 0, "mov %eax,(%ebx) | ret", "\x89\x03\xc3", 3},
  {0, 0, "mov %eax,(%ecx) | ret", "\x89\x01\xc3", 3},
  {0, 0, "mov %eax,(%esi) | ret", "\x89\x06\xc3", 3},
  {0, 0, "mov %eax,(%edi) | ret", "\x89\x07\xc3", 3},
  {0, 0, "mov %ebx,(%eax) | ret", "\x89\x18\xc3", 3},
  {0, 0, "mov %ebx,(%ecx) | ret", "\x89\x19\xc3", 3},
  {0, 0, "mov %ebx,(%edx) | ret", "\x89\x1a\xc3", 3},
  {0, 0, "mov %ebx,(%esi) | ret", "\x89\x1e\xc3", 3},
  {0, 0, "mov %ebx,(%edi) | ret", "\x89\x1f\xc3", 3},
  {0, 0, "mov %ecx,(%eax) | ret", "\x89\x08\xc3", 3},
  {0, 0, "mov %ecx,(%ebx) | ret", "\x89\x0b\xc3", 3},
  {0, 0, "mov %ecx,(%edx) | ret", "\x89\x0a\xc3", 3},
  {0, 0, "mov %ecx,(%esi) | ret", "\x89\x0e\xc3", 3},
  {0, 0, "mov %ecx,(%edi) | ret", "\x89\x0f\xc3", 3},
  {0, 0, "mov %edx,(%eax) | ret", "\x89\x10\xc3", 3},
  {0, 0, "mov %edx,(%ebx) | ret", "\x89\x13\xc3", 3},
  {0, 0, "mov %edx,(%ecx) | ret", "\x89\x11\xc3", 3},
  {0, 0, "mov %edx,(%esi) | ret", "\x89\x16\xc3", 3},
  {0, 0, "mov %edx,(%edi) | ret", "\x89\x17\xc3", 3},

  {0, 0, "mov (%esp),%eax | ret", "\x8b\x04\x24\xc3", 4},
  {0, 0, "mov (%esp),%ebx | ret", "\x8b\x1c\x24\xc3", 4},
  {0, 0, "mov (%esp),%ecx | ret", "\x8b\x0c\x24\xc3", 4},
  {0, 0, "mov (%esp),%edx | ret", "\x8b\x14\x24\xc3", 4},
  {0, 0, "mov (%esp),%esi | ret", "\x8b\x34\x24\xc3", 4},
  {0, 0, "mov (%esp),%edi | ret", "\x8b\x3c\x24\xc3", 4},
  {0, 0, "mov (%esp),%ebp | ret", "\x8b\x2c\x24\xc3", 4},


  {0, 0, "mov %eax,(%edx) | pop %ebp | ret", "\x89\x02\x5d\xc3", 4},
  {0, 0, "mov %eax,(%ebx) | pop %ebp | ret", "\x89\x03\x5d\xc3", 4},
  {0, 0, "mov %eax,(%ecx) | pop %ebp | ret", "\x89\x01\x5d\xc3", 4},
  {0, 0, "mov %eax,(%esi) | pop %ebp | ret", "\x89\x06\x5d\xc3", 4},
  {0, 0, "mov %eax,(%edi) | pop %ebp | ret", "\x89\x07\x5d\xc3", 4},
  {0, 0, "mov %ebx,(%eax) | pop %ebp | ret", "\x89\x18\x5d\xc3", 4},
  {0, 0, "mov %ebx,(%ecx) | pop %ebp | ret", "\x89\x19\x5d\xc3", 4},
  {0, 0, "mov %ebx,(%edx) | pop %ebp | ret", "\x89\x1a\x5d\xc3", 4},
  {0, 0, "mov %ebx,(%esi) | pop %ebp | ret", "\x89\x1e\x5d\xc3", 4},
  {0, 0, "mov %ebx,(%edi) | pop %ebp | ret", "\x89\x1f\x5d\xc3", 4},
  {0, 0, "mov %ecx,(%eax) | pop %ebp | ret", "\x89\x08\x5d\xc3", 4},
  {0, 0, "mov %ecx,(%ebx) | pop %ebp | ret", "\x89\x0b\x5d\xc3", 4},
  {0, 0, "mov %ecx,(%edx) | pop %ebp | ret", "\x89\x0a\x5d\xc3", 4},
  {0, 0, "mov %ecx,(%esi) | pop %ebp | ret", "\x89\x0e\x5d\xc3", 4},
  {0, 0, "mov %ecx,(%edi) | pop %ebp | ret", "\x89\x0f\x5d\xc3", 4},
  {0, 0, "mov %edx,(%eax) | pop %ebp | ret", "\x89\x10\x5d\xc3", 4},
  {0, 0, "mov %edx,(%ebx) | pop %ebp | ret", "\x89\x13\x5d\xc3", 4},
  {0, 0, "mov %edx,(%ecx) | pop %ebp | ret", "\x89\x11\x5d\xc3", 4},
  {0, 0, "mov %edx,(%esi) | pop %ebp | ret", "\x89\x16\x5d\xc3", 4},
  {0, 0, "mov %edx,(%edi) | pop %ebp | ret", "\x89\x17\x5d\xc3", 4},
  {0, 0, "mov %edx,%eax | pop %ebx | pop %esi | pop %edi | pop %ebp | ret", "\x89\xd0\x5b\x5e\x5f\x5d\xc3", 7},
  {0, 0, "mov %eax,%edi | mov %edi,%eax | pop %edi | pop %ebp | ret", "\x89\xc7\x89\xf8\x5f\x5d\xc3", 7},
  {0, 0, "mov (%edx),%eax | mov (%esp),%ebx | mov %ebp,%esp | pop %ebp | ret", "\x03\x02\x8b\x1c\x24\x89\xec\x5d\xc3", 9},
  {0, 0, "mov %eax,(%edi) | pop %eax | pop %ebx | pop %esi | pop %edi | ret", "\x89\x07\x58\x5b\x5e\x5f\xc3", 7},
  {0, 0, "mov %ebx,(%edi) | pop %ebx | pop %esi | pop %edi | ret", "\x89\x1f\x5b\x5e\x5f\xc3", 6},
  {0, 0, "mov %eax,(%ecx) | mov %ebx,%eax | pop %ebx | pop %ebp | ret", "\x89\x01\x89\xd8\x5b\x5d\xc3", 7},
  {0, 0, "mov %ebp,%eax | pop %ebx | pop %esi | pop %edi | pop %ebp | ret", "\x89\xe8\x5b\x5e\x5f\x5d\xc3", 7},
  {0, 0, "mov %ebx,%eax | pop %ebx | pop %esi | pop %edi | ret", "\x89\xd8\x5b\x5e\x5f\xc3", 6},
  {0, 0, "mov %edi,%eax | pop %ebx | pop %esi | pop %edi | ret", "\x89\xf8\x5b\x5e\x5f\xc3", 6},
  {0, 0, "mov %ebx,%eax | pop %ebx | ret", "\x89\xd8\x5b\xc3", 4},
  /* EOF hard opcode */

  /*
  ** Variable opcode
  ** ---------------
  **
  ** '?' is for 1 any byte direct value
  ** '#' if for 4 any bytes direct value
  */
  {0, 0, "add $0x?,%al | ret", "\x04?\xc3", 3},
  {0, 0, "add $0x?,%bl | ret", "\x80\xc3?\xc3", 4},
  {0, 0, "add $0x?,%cl | ret", "\x80\xc1?\xc3", 4},
  {0, 0, "add $0x?,%dl | ret", "\x80\xc2?\xc3", 4},
  {0, 0, "add $0x?,%ax | ret", "\x66\x83\xc0?\xc3", 5},
  {0, 0, "add $0x?,%bx | ret", "\x66\x83\xc3?\xc3", 5},
  {0, 0, "add $0x?,%cx | ret", "\x66\x83\xc1?\xc3", 5},
  {0, 0, "add $0x?,%dx | ret", "\x66\x83\xc2?\xc3", 5},
  {0, 0, "add $0x?,%eax | ret", "\x83\xc0?\xc3", 4},
  {0, 0, "add $0x?,%ebx | ret", "\x83\xc3?\xc3", 4},
  {0, 0, "add $0x?,%ecx | ret", "\x83\xc1?\xc3", 4},
  {0, 0, "add $0x?,%edx | ret", "\x83\xc2?\xc3", 4},
  {0, 0, "add $0x?,%esi | ret", "\x83\xc6?\xc3", 4},
  {0, 0, "add $0x?,%edi | ret", "\x83\xc7?\xc3", 4},
  {0, 0, "add $0x?,%ebp | ret", "\x83\xc5?\xc3", 4},
  {0, 0, "add $0x?,%esp | ret", "\x83\xc4?\xc3", 4},
  {0, 0, "sub $0x?,%al | ret", "\x2c?\xc3", 3},
  {0, 0, "sub $0x?,%bl | ret", "\x80\xeb?\xc3", 4},
  {0, 0, "sub $0x?,%cl | ret", "\x80\xe9?\xc3", 4},
  {0, 0, "sub $0x?,%dl | ret", "\x80\xea?\xc3", 4},
  {0, 0, "sub $0x?,%ax | ret", "\x66\x83\xe8?\xc3", 5},
  {0, 0, "sub $0x?,%bx | ret", "\x66\x83\xeb?\xc3", 5},
  {0, 0, "sub $0x?,%cx | ret", "\x66\x83\xe9?\xc3", 5},
  {0, 0, "sub $0x?,%dx | ret", "\x66\x83\xea?\xc3", 5},
  {0, 0, "sub $0x?,%eax | ret", "\x83\xe8?\xc3", 4},
  {0, 0, "sub $0x?,%ebx | ret", "\x83\xeb?\xc3", 4},
  {0, 0, "sub $0x?,%ecx | ret", "\x83\xe9?\xc3", 4},
  {0, 0, "sub $0x?,%edx | ret", "\x83\xea?\xc3", 4},
  {0, 0, "sub $0x?,%esi | ret", "\x83\xee?\xc3", 4},
  {0, 0, "sub $0x?,%edi | ret", "\x83\xef?\xc3", 4},
  {0, 0, "sub $0x?,%ebp | ret", "\x83\xed?\xc3", 4},
  {0, 0, "sub $0x?,%esp | ret", "\x83\xec?\xc3", 4},
  {0, 0, "mov $0x?,%al | ret", "\xb0?\xc3", 3},
  {0, 0, "mov $0x?,%bl | ret", "\xb3?\xc3", 3},
  {0, 0, "mov $0x?,%cl | ret", "\xb2?\xc3", 3},
  {0, 0, "mov $0x?,%dl | ret", "\xb1?\xc3", 3},
  {0, 0, "xor $0x?,%eax | ret", "\x83\xf0?\xc3", 4},
  {0, 0, "xor $0x?,%ebx | ret", "\x83\xf3?\xc3", 4},
  {0, 0, "xor $0x?,%ecx | ret", "\x83\xf1?\xc3", 4},
  {0, 0, "xor $0x?,%edx | ret", "\x83\xf2?\xc3", 4},
  {0, 0, "xor $0x?,%esi | ret", "\x83\xf6?\xc3", 4},
  {0, 0, "xor $0x?,%edi | ret", "\x83\xf7?\xc3", 4},
  {0, 0, "xor $0x?,%eax | pop %ebp | ret", "\x83\xf0?\x5d\xc3", 4},
  {0, 0, "xor $0x?,%ebx | pop %ebp | ret", "\x83\xf3?\x5d\xc3", 4},
  {0, 0, "xor $0x?,%ecx | pop %ebp | ret", "\x83\xf1?\x5d\xc3", 4},
  {0, 0, "xor $0x?,%edx | pop %ebp | ret", "\x83\xf2?\x5d\xc3", 4},
  {0, 0, "xor $0x?,%esi | pop %ebp | ret", "\x83\xf6?\x5d\xc3", 4},
  {0, 0, "xor $0x?,%edi | pop %ebp | ret", "\x83\xf7?\x5d\xc3", 4},

  /* 4 any bytes */
  {0, 0, "mov $0x#,%eax | ret", "\xb8####\xc3", 6},
  {0, 0, "mov $0x#,%ebx | ret", "\xbb####\xc3", 6},
  {0, 0, "mov $0x#,%ecx | ret", "\xb9####\xc3", 6},
  {0, 0, "mov $0x#,%edx | ret", "\xba####\xc3", 6},
  {0, 0, "mov $0x#,%esi | ret", "\xbe####\xc3", 6},
  {0, 0, "mov $0x#,%edi | ret", "\xbf####\xc3", 6},
  {0, 0, "mov $0x#,%ebp | ret", "\xbd####\xc3", 6},
  {0, 0, "mov $0x#,%esp | ret", "\xbc####\xc3", 6},
  {0, 0, "mov $0x#,%eax | pop %ebp | ret", "\xb8####\x5d\xc3", 7},
  {0, 0, "mov $0x#,%ebx | pop %ebp | ret", "\xbb####\x5d\xc3", 7},
  {0, 0, "mov $0x#,%ecx | pop %ebp | ret", "\xb9####\x5d\xc3", 7},
  {0, 0, "mov $0x#,%edx | pop %ebp | ret", "\xba####\x5d\xc3", 7},
  {0, 0, "mov $0x#,%esi | pop %ebp | ret", "\xbe####\x5d\xc3", 7},
  {0, 0, "mov $0x#,%edi | pop %ebp | ret", "\xbf####\x5d\xc3", 7},
  {0, 0, "mov $0x#,%ebp | pop %ebp | ret", "\xbd####\x5d\xc3", 7},
  {0, 0, "mov $0x#,%esp | pop %ebp | ret", "\xbc####\x5d\xc3", 7},
  {0, 0, "xor $0x#,%eax | ret", "\x35####\xc3", 6},
  {0, 0, "xor $0x#,%ebx | ret", "\x81\xf3####\xc3", 7},
  {0, 0, "xor $0x#,%ecx | ret", "\x81\xf1####\xc3", 7},
  {0, 0, "xor $0x#,%edx | ret", "\x81\xf2####\xc3", 7},
  {0, 0, "xor $0x#,%esi | ret", "\x81\xf6####\xc3", 7},
  {0, 0, "xor $0x#,%edi | ret", "\x81\xf7####\xc3", 7},
  {0, 0, "xor $0x#,%eax | pop %ebp | ret", "\x35####\x5d\xc3", 7},
  {0, 0, "xor $0x#,%ebx | pop %ebp | ret", "\x81\xf3####\x5d\xc3", 8},
  {0, 0, "xor $0x#,%ecx | pop %ebp | ret", "\x81\xf1####\x5d\xc3", 8},
  {0, 0, "xor $0x#,%edx | pop %ebp | ret", "\x81\xf2####\x5d\xc3", 8},
  {0, 0, "xor $0x#,%esi | pop %ebp | ret", "\x81\xf6####\x5d\xc3", 8},
  {0, 0, "xor $0x#,%edi | pop %ebp | ret", "\x81\xf7####\x5d\xc3", 8},
  {0, 0, "add $0x#,%eax | ret", "\x05####\xc3", 6},
  {0, 0, "add $0x#,%ebx | ret", "\x81\xc3####\xc3", 7},
  {0, 0, "add $0x#,%ecx | ret", "\x81\xc1####\xc3", 7},
  {0, 0, "add $0x#,%edx | ret", "\x81\xc2####\xc3", 7},
  {0, 0, "add $0x#,%esi | ret", "\x81\xc6####\xc3", 7},
  {0, 0, "add $0x#,%edi | ret", "\x81\xc7####\xc3", 7},
  {0, 0, "add $0x#,%eax | pop %ebp | ret", "\x05####\x5d\xc3", 7},
  {0, 0, "add $0x#,%ebx | pop %ebp | ret", "\x81\xc3####\x5d\xc3", 8},
  {0, 0, "add $0x#,%ecx | pop %ebp | ret", "\x81\xc1####\x5d\xc3", 8},
  {0, 0, "add $0x#,%edx | pop %ebp | ret", "\x81\xc2####\x5d\xc3", 8},
  {0, 0, "add $0x#,%esi | pop %ebp | ret", "\x81\xc6####\x5d\xc3", 8},
  {0, 0, "add $0x#,%edi | pop %ebp | ret", "\x81\xc7####\x5d\xc3", 8},
  {0, 0, "sub $0x#,%eax | ret", "\x2d####\xc3", 6},
  {0, 0, "sub $0x#,%ebx | ret", "\x81\xeb####\xc3", 7},
  {0, 0, "sub $0x#,%ecx | ret", "\x81\xe9####\xc3", 7},
  {0, 0, "sub $0x#,%edx | ret", "\x81\xea####\xc3", 7},
  {0, 0, "sub $0x#,%esi | ret", "\x81\xee####\xc3", 7},
  {0, 0, "sub $0x#,%edi | ret", "\x81\xef####\xc3", 7},
  {0, 0, "sub $0x#,%eax | pop %ebp | ret", "\x2d####\x5d\xc3", 7},
  {0, 0, "sub $0x#,%ebx | pop %ebp | ret", "\x81\xeb####\x5d\xc3", 8},
  {0, 0, "sub $0x#,%ecx | pop %ebp | ret", "\x81\xe9####\x5d\xc3", 8},
  {0, 0, "sub $0x#,%edx | pop %ebp | ret", "\x81\xea####\x5d\xc3", 8},
  {0, 0, "sub $0x#,%esi | pop %ebp | ret", "\x81\xee####\x5d\xc3", 8},
  {0, 0, "sub $0x#,%edi | pop %ebp | ret", "\x81\xef####\x5d\xc3", 8},
  /* EOF variable opcode */

  {0, 0, NULL, NULL, 0}
};

t_char_importsc *add_char_importsc(t_char_importsc *old_element, char octet, Elf32_Addr addr)
{
  t_char_importsc *new_element;

  new_element = malloc(sizeof(t_char_importsc));
  if (new_element == NULL)
    exit(EXIT_FAILURE);
  new_element->addr        = addr;
  new_element->octet       = octet;
  new_element->next        = old_element;
  if (old_element != NULL)
    old_element->back = new_element;

  return (new_element);
}

void save_octet(unsigned char *data, Elf32_Addr offset)
{
  static int cpt = 0;

  if (*data == importsc_mode.opcode[cpt] && cpt != importsc_mode.size)
    {
      importsc_mode.poctet = add_char_importsc(importsc_mode.poctet, *data, offset);
      cpt++;
    }
}

void gadget_x8632(unsigned char *data, unsigned int cpt, Elf32_Addr offset, int i, t_maps_exec *maps_exec)
{
  char *varopins;

  if (importsc_mode.flag == 1 && !check_exec_maps(maps_exec, (Elf32_Addr)(cpt + offset)))
    save_octet(data, (Elf32_Addr)(cpt + offset));

  if(!match((const char *)data, tab_x8632[i].value, tab_x8632[i].size)
     && !check_exec_maps(maps_exec, (Elf32_Addr)(cpt + offset)))
    {
      /* no '?' & no '#' */
      if (!check_interrogation(tab_x8632[i].instruction))
        fprintf(stdout, "%s0x%.8x%s: %s%s%s\n", RED, (cpt + offset), ENDC, GREEN, tab_x8632[i].instruction, ENDC);
      /* if '?' */
      else if (interrogation_or_diese(tab_x8632[i].instruction) == 1)
        {
          varopins = ret_instruction_interrogation(((Elf32_Addr)pMapElf + cpt), tab_x8632[i].instruction, tab_x8632[i].value);
          if (!check_if_varop_was_printed(varopins))
            {
              fprintf(stdout, "%s0x%.8x%s: %s%s%s\n", RED, (cpt + offset), ENDC, GREEN, varopins, ENDC);
              pVarop = add_element_varop(pVarop, varopins, (cpt + offset));
            }
          else
            {
              free(varopins);
              NbGadFound--;
            }
        }
      /* if '#' */
      else if (interrogation_or_diese(tab_x8632[i].instruction) == 2)
        {
          varopins = ret_instruction_diese(((Elf32_Addr)pMapElf + cpt), tab_x8632[i].instruction, tab_x8632[i].value);
          if (!check_if_varop_was_printed(varopins))
            {
              fprintf(stdout, "%s0x%.8x%s: %s%s%s\n", RED, (cpt + offset), ENDC, GREEN, varopins, ENDC);
              pVarop = add_element_varop(pVarop, varopins, (cpt + offset));
            }
          else
            {
              free(varopins);
              NbGadFound--;
            }
        }

      if (!check_interrogation(tab_x8632[i].instruction))
        tab_x8632[i].flag = 1;
      tab_x8632[i].addr = (Elf32_Addr)(cpt + offset);
      NbGadFound++;
      NbTotalGadFound++;
    }
}

void x8632(unsigned char *data, unsigned int size_data, t_maps_exec *maps_exec)
{
  int i              = 0;
  unsigned int cpt   = 0;
  Elf32_Addr  offset;

  pGadgets = tab_x8632;
  NbTotalGadFound = 0;
  NbGadFound = 0;
  pVarop = NULL;
  importsc_mode.poctet = NULL;
  while(cpt < size_data)
    {
      i = 0;
      if (opcode_mode.flag != 1)
        {
          while (i <= (int)NB_GADGET)
            {
              if (pGadgets[i].flag != 1 && !no_filtered(pGadgets[i].instruction) && onlymode(pGadgets[i].instruction))
                gadget_x8632(data, cpt, (pElf32_Phdr->p_vaddr - pElf32_Phdr->p_offset), i, maps_exec);
              i++;
            }
        }
      else
        {
          offset = (pElf32_Phdr->p_vaddr - pElf32_Phdr->p_offset);
          if(!search_opcode((const char *)data, (char *)opcode_mode.opcode, opcode_mode.size)
            && !check_exec_maps(maps_exec, (Elf32_Addr)(cpt + offset)))
            {
              fprintf(stdout, "%s0x%.8x%s: \"%s", RED, (cpt + offset), ENDC, GREEN);
              print_opcode();
              fprintf(stdout, "%s\"\n", ENDC);
              NbTotalGadFound++;
            }
        }
      cpt++;
      data++;
    }
  how_many_found();
}