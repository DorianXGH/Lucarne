#include "cpuid.h"

void print_cpuid(struct def_vga_screen * s)
{
    uint32_t ecx, edx;

    cpuid_get_features(&ecx, &edx);

    uint32_t ecx2, edx2;

    cpuid_get_features(&ecx2, &edx2);

    if (ecx != ecx2 || edx != edx2) {
        putstring(s, "!!!");
    }

    putstring(s, "EDX : ");

    if (edx & CPUID_FEAT_EDX_ACPI) {
        putstring(s, "ACPI, ");
    }
    if (edx & CPUID_FEAT_EDX_APIC) {
        putstring(s, "APIC, ");
    }
    if (edx & CPUID_FEAT_EDX_CLF) {
        putstring(s, "CLF, ");
    }
    if (edx & CPUID_FEAT_EDX_CMOV) {
        putstring(s, "CMOV, ");
    }
    if (edx & CPUID_FEAT_EDX_CX8) {
        putstring(s, "CX8, ");
    }
    if (edx & CPUID_FEAT_EDX_DE) {
        putstring(s, "DE, ");
    }
    if (edx & CPUID_FEAT_EDX_DTES) {
        putstring(s, "DTES, ");
    }
    if (edx & CPUID_FEAT_EDX_FPU) {
        putstring(s, "FPU, ");
    }
    if (edx & CPUID_FEAT_EDX_FXSR) {
        putstring(s, "FXSR, ");
    }
    if (edx & CPUID_FEAT_EDX_HTT) {
        putstring(s, "HTT, ");
    }
    if (edx & CPUID_FEAT_EDX_IA64) {
        putstring(s, "IA64, ");
    }
    if (edx & CPUID_FEAT_EDX_MCA) {
        putstring(s, "MCA, ");
    }
    if (edx & CPUID_FEAT_EDX_MCE) {
        putstring(s, "MCE, ");
    }
    if (edx & CPUID_FEAT_EDX_MMX) {
        putstring(s, "MMX, ");
    }
    if (edx & CPUID_FEAT_EDX_MSR) {
        putstring(s, "MSR, ");
    }
    if (edx & CPUID_FEAT_EDX_MTRR) {
        putstring(s, "MTRR, ");
    }
    if (edx & CPUID_FEAT_EDX_PAE) {
        putstring(s, "PAE, ");
    }
    if (edx & CPUID_FEAT_EDX_PAT) {
        putstring(s, "PAT, ");
    }
    if (edx & CPUID_FEAT_EDX_PBE) {
        putstring(s, "PBE, ");
    }
    if (edx & CPUID_FEAT_EDX_PGE) {
        putstring(s, "PGE, ");
    }
    if (edx & CPUID_FEAT_EDX_PSE36) {
        putstring(s, "PSE36, ");
    }
    if (edx & CPUID_FEAT_EDX_PSE) {
        putstring(s, "PSE, ");
    }
    if (edx & CPUID_FEAT_EDX_PSN) {
        putstring(s, "PSN, ");
    }
    if (edx & CPUID_FEAT_EDX_SEP) {
        putstring(s, "SEP, ");
    }
    if (edx & CPUID_FEAT_EDX_SS) {
        putstring(s, "SS, ");
    }
    if (edx & CPUID_FEAT_EDX_SSE2) {
        putstring(s, "SSE2, ");
    }
    if (edx & CPUID_FEAT_EDX_SSE) {
        putstring(s, "SSE, ");
    }
    if (edx & CPUID_FEAT_EDX_TM1) {
        putstring(s, "TM1, ");
    }
    if (edx & CPUID_FEAT_EDX_TSC) {
        putstring(s, "TSC, ");
    }
    if (edx & CPUID_FEAT_EDX_VME) {
        putstring(s, "VME, ");
    }
    putstring(s, "\nECX : ");

    if (ecx & CPUID_FEAT_ECX_MONITOR) {
        putstring(s, "MONITOR, ");
    }
    if (ecx & CPUID_FEAT_ECX_MOVBE) {
        putstring(s, "MOVBE, ");
    }
    if (ecx & CPUID_FEAT_ECX_OSXSAVE) {
        putstring(s, "OSXSAVE, ");
    }
    if (ecx & CPUID_FEAT_ECX_PCIDE) {
        putstring(s, "PCIDE, ");
    }
    if (ecx & CPUID_FEAT_ECX_PCLMUL) {
        putstring(s, "PCLMUL, ");
    }
    if (ecx & CPUID_FEAT_ECX_PDCM) {
        putstring(s, "PDCM, ");
    }
    if (ecx & CPUID_FEAT_ECX_POPCNT) {
        putstring(s, "POPCNT, ");
    }
    if (ecx & CPUID_FEAT_ECX_SMX) {
        putstring(s, "SMX, ");
    }
    if (ecx & CPUID_FEAT_ECX_SSE3) {
        putstring(s, "MONITOR, ");
    }
    if (ecx & CPUID_FEAT_ECX_SSE4_1) {
        putstring(s, "SSE4.1, ");
    }
    if (ecx & CPUID_FEAT_ECX_SSE4_2) {
        putstring(s, "SSE4.2, ");
    }
    if (ecx & CPUID_FEAT_ECX_SSSE3) {
        putstring(s, "SSSE3, ");
    }
    if (ecx & CPUID_FEAT_ECX_TM2) {
        putstring(s, "TM2, ");
    }
    if (ecx & CPUID_FEAT_ECX_VMX) {
        putstring(s, "VMX, ");
    }
    if (ecx & CPUID_FEAT_ECX_x2APIC) {
        putstring(s, "x2APIC, ");
    }
    if (ecx & CPUID_FEAT_ECX_XSAVE) {
        putstring(s, "XSAVE, ");
    }
} /* print_cpuid */
