#include "../all.h"

typedef struct I386Op I386Op;

enum I386Reg {
	EAX = RXX+1, /* caller-save */
	ECX,  /* caller-save */
	EDX,  /* caller-save */

    EBX, /* callee-save */
	ESI,  /* callee-save */
	EDI,  /* callee-save */

	EBP, /* globally live */
	ESP,

	XMM0, /* sse */
	XMM1,
	XMM2,
	XMM3,
	XMM4,
	XMM5,
	XMM6,
	XMM7,

    // floating point registers
	NFPR = XMM6 - XMM0 + 1, /* reserve XMM7 (for tmp) */
    // general purpose registers
    NGPR = ESP - EAX + 1,
    // general purpose scratch (caller-saved) registers
    NGPS = EDX - EAX + 1,
    // callee-saved registers
    NCLR = EDI - EBX + 1,
    // floating point scratch (caller-saved) registers
    NFPS = NFPR,
};
MAKESURE(reg_not_tmp, XMM7 < (int)Tmp0);

struct I386Op {
	char nmem;
	char zflag;
	char lflag;
};

/* targ.c */
extern I386Op i386_op[];

/* sysv.c (abi) */
extern int i386_sysv_rsave[];
extern int i386_sysv_rclob[];
bits i386_sysv_retregs(Ref, int[2]);
bits i386_sysv_argregs(Ref, int[2]);
void i386_sysv_abi(Fn *);

/* isel.c */
void i386_isel(Fn *);

/* emit.c */
void i386_sysv_emitfn(Fn *, FILE *);
