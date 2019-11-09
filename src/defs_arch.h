#ifndef __DEFS_ARCH_H__
#define __DEFS_ARCH_H__

// AMD64
#ifdef __amd64__
#define PROGRAM_ARCH "AMD64"
#endif
#ifdef __amd64
#define PROGRAM_ARCH "AMD64"
#endif
#ifdef __x86_64__
#define PROGRAM_ARCH "AMD64"
#endif
#ifdef __x86_64
#define PROGRAM_ARCH "AMD64"
#endif
#ifdef _M_X64
#define PROGRAM_ARCH "AMD64"
#endif
#ifdef _M_AMD64
#define PROGRAM_ARCH "AMD64"
#endif

// ARM
#ifdef __arm__
#define PROGRAM_ARCH "ARM"
#endif
#ifdef __thumb__
#define PROGRAM_ARCH "ARM"
#endif
#ifdef __TARGET_ARCH_ARM
#define PROGRAM_ARCH "ARM"
#endif
#ifdef __TARGET_ARCH_THUMB
#define PROGRAM_ARCH "ARM"
#endif
#ifdef _ARM
#define PROGRAM_ARCH "ARM"
#endif
#ifdef _M_ARM
#define PROGRAM_ARCH "ARM"
#endif
#ifdef _M_ARMT
#define PROGRAM_ARCH "ARM"
#endif
#ifdef __arm
#define PROGRAM_ARCH "ARM"
#endif

// ARM64
#ifdef __aarch64__
#define PROGRAM_ARCH "ARM64"
#endif

// Intel x86
#ifdef i386
#define PROGRAM_ARCH "Intel x86"
#endif
#ifdef __i386
#define PROGRAM_ARCH "Intel x86"
#endif
#ifdef __i386__
#define PROGRAM_ARCH "Intel x86"
#endif
#ifdef __IA32__
#define PROGRAM_ARCH "Intel x86"
#endif
#ifdef _M_I86
#define PROGRAM_ARCH "Intel x86"
#endif
#ifdef _M_IX86
#define PROGRAM_ARCH "Intel x86"
#endif
#ifdef __X86__
#define PROGRAM_ARCH "Intel x86"
#endif
#ifdef _X86_
#define PROGRAM_ARCH "Intel x86"
#endif
#ifdef __THW_INTEL__
#define PROGRAM_ARCH "Intel x86"
#endif
#ifdef __I86__
#define PROGRAM_ARCH "Intel x86"
#endif
#ifdef __INTEL__
#define PROGRAM_ARCH "Intel x86"
#endif
#ifdef __386
#define PROGRAM_ARCH "Intel x86"
#endif

// IA-64 (Intel Itanium)
#ifdef __ia64__
#define PROGRAM_ARCH "IA-64"
#endif
#ifdef _IA64
#define PROGRAM_ARCH "IA-64"
#endif
#ifdef __IA64__
#define PROGRAM_ARCH "IA-64"
#endif
#ifdef __ia64
#define PROGRAM_ARCH "IA-64"
#endif
#ifdef _M_IA64
#define PROGRAM_ARCH "IA-64"
#endif
#ifdef __itanium__
#define PROGRAM_ARCH "IA-64"
#endif

// MIPS
#ifdef __mips__
#define PROGRAM_ARCH "MIPS"
#endif
#ifdef mips
#define PROGRAM_ARCH "MIPS"
#endif
#ifdef __mips
#define PROGRAM_ARCH "MIPS"
#endif
#ifdef __MIPS__
#define PROGRAM_ARCH "MIPS"
#endif

// PowerPC
#ifdef __powerpc
#define PROGRAM_ARCH "PowerPC"
#endif
#ifdef __powerpc__
#define PROGRAM_ARCH "PowerPC"
#endif
#ifdef __powerpc64__
#define PROGRAM_ARCH "PowerPC"
#endif
#ifdef __POWERPC__
#define PROGRAM_ARCH "PowerPC"
#endif
#ifdef __ppc__
#define PROGRAM_ARCH "PowerPC"
#endif
#ifdef __ppc64__
#define PROGRAM_ARCH "PowerPC"
#endif
#ifdef __PPC__
#define PROGRAM_ARCH "PowerPC"
#endif
#ifdef __PPC64__
#define PROGRAM_ARCH "PowerPC"
#endif
#ifdef _ARCH_PPC
#define PROGRAM_ARCH "PowerPC"
#endif
#ifdef _ARCH_PPC64
#define PROGRAM_ARCH "PowerPC"
#endif
#ifdef _M_PPC
#define PROGRAM_ARCH "PowerPC"
#endif
#ifdef _ARCH_PPC
#define PROGRAM_ARCH "PowerPC"
#endif
#ifdef _ARCH_PPC64
#define PROGRAM_ARCH "PowerPC"
#endif
#ifdef __ppc
#define PROGRAM_ARCH "PowerPC"
#endif

#endif // __DEFS_ARCH_H__
