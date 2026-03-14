#include "all.h"

I386Op i386_op[NOp] = {
#define O(op, t, x) [O##op] =
#define X(nm, zf, lf) { nm, zf, lf, },
	#include "../ops.h"
};

static int
i386_memargs(int op)
{
	return i386_op[op].nmem;
}

#define I386_COMMON \
	.ptrsz = 4, \
	.gpr0 = EAX, \
	.ngpr = NGPR, \
	.fpr0 = XMM0, \
	.nfpr = NFPR, \
	.rglob = BIT(EBP) | BIT(ESP), \
	.nrglob = 2, \
	.memargs = i386_memargs, \
	.abi0 = elimsb, \
	.isel = i386_isel, \
	.cansel = 1, /* use CMOVcc to make if branchless */

Target T_i386_sysv = {
	.name = "i386_sysv",
	.emitfin = elf_emitfin,
	.asloc = ".L",
	.abi1 = i386_sysv_abi,
	.rsave = i386_sysv_rsave,
	.nrsave = {NGPS, NFPS},
	.retregs = i386_sysv_retregs,
	.argregs = i386_sysv_argregs,
	.emitfn = i386_sysv_emitfn,
	I386_COMMON
};
