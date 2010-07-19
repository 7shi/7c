int printf(const char *, ...);
int fprintf(void *, const char *, ...);
int sprintf(char *, const char *, ...);
void *fopen(const char *, const char *);
int fclose(void *);
int fread(void *, int, int, void *);
int fwrite(const void *, int, int, void *);
int fseek(void *, int, int);
int strcmp(const char *, const char *);
char *strcpy(char *, const char *);
char *strcat(char *, const char *);

typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;

enum Format
{
	___, Pcd, Bra, Mem, Mfc, Mbr, Opr, F_P
};

enum Regs
{
	/* r00	 */ V0,
	/* r01-r08 */ T0, T1, T2, T3, T4, T5, T6, T7,
	/* r09-r14 */ S0, S1, S2, S3, S4, S5,
	/* r15	 */ FP,
	/* r16-r21 */ A0, A1, A2, A3, A4, A5,
	/* r22-r25 */ T8, T9, T10, T11,
	/* r26	 */ RA,
	/* r27	 */ T12,
	/* r28	 */ AT,
	/* r29	 */ GP,
	/* r30	 */ SP,
	/* r31	 */ Zero,
};

const char *regname[] =
{
	/* r00	 */ "v0",
	/* r01-r08 */ "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
	/* r09-r14 */ "s0", "s1", "s2", "s3", "s4", "s5",
	/* r15	 */ "fp",
	/* r16-r21 */ "a0", "a1", "a2", "a3", "a4", "a5",
	/* r22-r25 */ "t8", "t9", "t10", "t11",
	/* r26	 */ "ra",
	/* r27	 */ "t12",
	/* r28	 */ "at",
	/* r29	 */ "gp",
	/* r30	 */ "sp",
	/* r31	 */ "zero",
};

enum Format formats[] =
{
	/* 00-07 */ Pcd, ___, ___, ___, ___, ___, ___, ___,
	/* 08-0f */ Mem, Mem, Mem, Mem, Mem, Mem, Mem, Mem,
	/* 10-17 */ Opr, Opr, Opr, Opr, F_P, F_P, F_P, F_P,
	/* 18-1f */ Mfc, ___, Mbr, ___, Opr, ___, ___, ___,
	/* 20-27 */ Mem, Mem, Mem, Mem, Mem, Mem, Mem, Mem,
	/* 28-2f */ Mem, Mem, Mem, Mem, Mem, Mem, Mem, Mem,
	/* 30-37 */ Bra, Bra, Bra, Bra, Bra, Bra, Bra, Bra,
	/* 38-3f */ Bra, Bra, Bra, Bra, Bra, Bra, Bra, Bra,
};

enum Op
{
	UNDEF = -1,
	Call_pal = 0x000000,
	Opc01 = 0x010000,
	Opc02 = 0x020000,
	Opc03 = 0x030000,
	Opc04 = 0x040000,
	Opc05 = 0x050000,
	Opc06 = 0x060000,
	Opc07 = 0x070000,
	Lda = 0x080000,
	Ldah = 0x090000,
	Ldbu = 0x0a0000,
	Ldq_u = 0x0b0000,
	Ldwu = 0x0c0000,
	Stw = 0x0d0000,
	Stb = 0x0e0000,
	Stq_u = 0x0f0000,
	Addl = 0x100000,
	S4addl = 0x100002,
	Subl = 0x100009,
	S4subl = 0x10000b,
	Cmpbge = 0x10000f,
	S8addl = 0x100012,
	S8subl = 0x10001b,
	Cmpult = 0x10001d,
	Addq = 0x100020,
	S4addq = 0x100022,
	Subq = 0x100029,
	S4subq = 0x10002b,
	Cmpeq = 0x10002d,
	S8addq = 0x100032,
	S8subq = 0x10003b,
	Cmpule = 0x10003d,
	Addl__v = 0x100040,
	Subl__v = 0x100049,
	Cmplt = 0x10004d,
	Addq__v = 0x100060,
	Subq__v = 0x100069,
	Cmple = 0x10006d,
	And = 0x110000,
	Bic = 0x110008,
	Cmovlbs = 0x110014,
	Cmovlbc = 0x110016,
	Bis = 0x110020,
	Cmoveq = 0x110024,
	Cmovne = 0x110026,
	Ornot = 0x110028,
	Xor = 0x110040,
	Cmovlt = 0x110044,
	Cmovge = 0x110046,
	Eqv = 0x110048,
	Amask = 0x110061,
	Cmovle = 0x110064,
	Cmovgt = 0x110066,
	Implver = 0x11006c,
	Mskbl = 0x120002,
	Extbl = 0x120006,
	Insbl = 0x12000b,
	Mskwl = 0x120012,
	Extwl = 0x120016,
	Inswl = 0x12001b,
	Mskll = 0x120022,
	Extll = 0x120026,
	Insll = 0x12002b,
	Zap = 0x120030,
	Zapnot = 0x120031,
	Mskql = 0x120032,
	Srl = 0x120034,
	Extql = 0x120036,
	Sll = 0x120039,
	Insql = 0x12003b,
	Sra = 0x12003c,
	Mskwh = 0x120052,
	Inswh = 0x120057,
	Extwh = 0x12005a,
	Msklh = 0x120062,
	Inslh = 0x120067,
	Extlh = 0x12006a,
	Mskqh = 0x120072,
	Insqh = 0x120077,
	Extqh = 0x12007a,
	Mull = 0x130000,
	Mulq = 0x130020,
	Umulh = 0x130030,
	Mull__v = 0x130040,
	Mulq__v = 0x130060,
	Itofs = 0x140004,
	Sqrtf__c = 0x14000a,
	Sqrts__c = 0x14000b,
	Itoff = 0x140014,
	Itoft = 0x140024,
	Sqrtg__c = 0x14002a,
	Sqrtt__c = 0x14002b,
	Sqrts__m = 0x14004b,
	Sqrtt__m = 0x14006b,
	Sqrtf = 0x14008a,
	Sqrts = 0x14008b,
	Sqrtg = 0x1400aa,
	Sqrtt = 0x1400ab,
	Sqrts__d = 0x1400cb,
	Sqrtt__d = 0x1400eb,
	Sqrtf__uc = 0x14010a,
	Sqrts__uc = 0x14010b,
	Sqrtg__uc = 0x14012a,
	Sqrtt__uc = 0x14012b,
	Sqrts__um = 0x14014b,
	Sqrtt__um = 0x14016b,
	Sqrtf__u = 0x14018a,
	Sqrts__u = 0x14018b,
	Sqrtg__u = 0x1401aa,
	Sqrtt__u = 0x1401ab,
	Sqrts__ud = 0x1401cb,
	Sqrtt__ud = 0x1401eb,
	Sqrtf__sc = 0x14040a,
	Sqrtg__sc = 0x14042a,
	Sqrtf__s = 0x14048a,
	Sqrtg__s = 0x1404aa,
	Sqrtf__suc = 0x14050a,
	Sqrts__suc = 0x14050b,
	Sqrtg__suc = 0x14052a,
	Sqrtt__suc = 0x14052b,
	Sqrts__sum = 0x14054b,
	Sqrtt__sum = 0x14056b,
	Sqrtf__su = 0x14058a,
	Sqrts__su = 0x14058b,
	Sqrtg__su = 0x1405aa,
	Sqrtt__su = 0x1405ab,
	Sqrts__sud = 0x1405cb,
	Sqrtt__sud = 0x1405eb,
	Sqrts__suic = 0x14070b,
	Sqrtt__suic = 0x14072b,
	Sqrts__suim = 0x14074b,
	Sqrtt__suim = 0x14076b,
	Sqrts__sui = 0x14078b,
	Sqrtt__sui = 0x1407ab,
	Sqrts__suid = 0x1407cb,
	Sqrtt__suid = 0x1407eb,
	Addf__c = 0x150000,
	Subf__c = 0x150001,
	Mulf__c = 0x150002,
	Divf__c = 0x150003,
	Cvtdg__c = 0x15001e,
	Addg__c = 0x150020,
	Subg__c = 0x150021,
	Mulg__c = 0x150022,
	Divg__c = 0x150023,
	Cvtgf__c = 0x15002c,
	Cvtgd__c = 0x15002d,
	Cvtgq__c = 0x15002f,
	Cvtqf__c = 0x15003c,
	Cvtqg__c = 0x15003e,
	Addf = 0x150080,
	Subf = 0x150081,
	Mulf = 0x150082,
	Divf = 0x150083,
	Cvtdg = 0x15009e,
	Addg = 0x1500a0,
	Subg = 0x1500a1,
	Mulg = 0x1500a2,
	Divg = 0x1500a3,
	Cmpgeq = 0x1500a5,
	Cmpglt = 0x1500a6,
	Cmpgle = 0x1500a7,
	Cvtgf = 0x1500ac,
	Cvtgd = 0x1500ad,
	Cvtgq = 0x1500af,
	Cvtqf = 0x1500bc,
	Cvtqg = 0x1500be,
	Addf__uc = 0x150100,
	Subf__uc = 0x150101,
	Mulf__uc = 0x150102,
	Divf__uc = 0x150103,
	Cvtdg__uc = 0x15011e,
	Addg__uc = 0x150120,
	Subg__uc = 0x150121,
	Mulg__uc = 0x150122,
	Divg__uc = 0x150123,
	Cvtgf__uc = 0x15012c,
	Cvtgd__uc = 0x15012d,
	Cvtgq__vc = 0x15012f,
	Addf__u = 0x150180,
	Subf__u = 0x150181,
	Mulf__u = 0x150182,
	Divf__u = 0x150183,
	Cvtdg__u = 0x15019e,
	Addg__u = 0x1501a0,
	Subg__u = 0x1501a1,
	Mulg__u = 0x1501a2,
	Divg__u = 0x1501a3,
	Cvtgf__u = 0x1501ac,
	Cvtgd__u = 0x1501ad,
	Cvtgq__v = 0x1501af,
	Addf__sc = 0x150400,
	Subf__sc = 0x150401,
	Mulf__sc = 0x150402,
	Divf__sc = 0x150403,
	Cvtdg__sc = 0x15041e,
	Addg__sc = 0x150420,
	Subg__sc = 0x150421,
	Mulg__sc = 0x150422,
	Divg__sc = 0x150423,
	Cvtgf__sc = 0x15042c,
	Cvtgd__sc = 0x15042d,
	Cvtgq__sc = 0x15042f,
	Addf__s = 0x150480,
	Subf__s = 0x150481,
	Mulf__s = 0x150482,
	Divf__s = 0x150483,
	Cvtdg__s = 0x15049e,
	Addg__s = 0x1504a0,
	Subg__s = 0x1504a1,
	Mulg__s = 0x1504a2,
	Divg__s = 0x1504a3,
	Cmpgeq__s = 0x1504a5,
	Cmpglt__s = 0x1504a6,
	Cmpgle__s = 0x1504a7,
	Cvtgf__s = 0x1504ac,
	Cvtgd__s = 0x1504ad,
	Cvtgq__s = 0x1504af,
	Addf__suc = 0x150500,
	Subf__suc = 0x150501,
	Mulf__suc = 0x150502,
	Divf__suc = 0x150503,
	Cvtdg__suc = 0x15051e,
	Addg__suc = 0x150520,
	Subg__suc = 0x150521,
	Mulg__suc = 0x150522,
	Divg__suc = 0x150523,
	Cvtgf__suc = 0x15052c,
	Cvtgd__suc = 0x15052d,
	Cvtgq__svc = 0x15052f,
	Addf__su = 0x150580,
	Subf__su = 0x150581,
	Mulf__su = 0x150582,
	Divf__su = 0x150583,
	Cvtdg__su = 0x15059e,
	Addg__su = 0x1505a0,
	Subg__su = 0x1505a1,
	Mulg__su = 0x1505a2,
	Divg__su = 0x1505a3,
	Cvtgf__su = 0x1505ac,
	Cvtgd__su = 0x1505ad,
	Cvtgq__sv = 0x1505af,
	Adds__c = 0x160000,
	Subs__c = 0x160001,
	Muls__c = 0x160002,
	Divs__c = 0x160003,
	Addt__c = 0x160020,
	Subt__c = 0x160021,
	Mult__c = 0x160022,
	Divt__c = 0x160023,
	Cvtts__c = 0x16002c,
	Cvttq__c = 0x16002f,
	Cvtqs__c = 0x16003c,
	Cvtqt__c = 0x16003e,
	Adds__m = 0x160040,
	Subs__m = 0x160041,
	Muls__m = 0x160042,
	Divs__m = 0x160043,
	Addt__m = 0x160060,
	Subt__m = 0x160061,
	Mult__m = 0x160062,
	Divt__m = 0x160063,
	Cvtts__m = 0x16006c,
	Cvttq__m = 0x16006f,
	Cvtqs__m = 0x16007c,
	Cvtqt__m = 0x16007e,
	Adds = 0x160080,
	Subs = 0x160081,
	Muls = 0x160082,
	Divs = 0x160083,
	Addt = 0x1600a0,
	Subt = 0x1600a1,
	Mult = 0x1600a2,
	Divt = 0x1600a3,
	Cmptun = 0x1600a4,
	Cmpteq = 0x1600a5,
	Cmptlt = 0x1600a6,
	Cmptle = 0x1600a7,
	Cvtts = 0x1600ac,
	Cvttq = 0x1600af,
	Cvtqs = 0x1600bc,
	Cvtqt = 0x1600be,
	Adds__d = 0x1600c0,
	Subs__d = 0x1600c1,
	Muls__d = 0x1600c2,
	Divs__d = 0x1600c3,
	Addt__d = 0x1600e0,
	Subt__d = 0x1600e1,
	Mult__d = 0x1600e2,
	Divt__d = 0x1600e3,
	Cvtts__d = 0x1600ec,
	Cvttq__d = 0x1600ef,
	Cvtqs__d = 0x1600fc,
	Cvtqt__d = 0x1600fe,
	Adds__uc = 0x160100,
	Subs__uc = 0x160101,
	Muls__uc = 0x160102,
	Divs__uc = 0x160103,
	Addt__uc = 0x160120,
	Subt__uc = 0x160121,
	Mult__uc = 0x160122,
	Divt__uc = 0x160123,
	Cvtts__uc = 0x16012c,
	Cvttq__vc = 0x16012f,
	Adds__um = 0x160140,
	Subs__um = 0x160141,
	Muls__um = 0x160142,
	Divs__um = 0x160143,
	Addt__um = 0x160160,
	Subt__um = 0x160161,
	Mult__um = 0x160162,
	Divt__um = 0x160163,
	Cvtts__um = 0x16016c,
	Cvttq__vm = 0x16016f,
	Adds__u = 0x160180,
	Subs__u = 0x160181,
	Muls__u = 0x160182,
	Divs__u = 0x160183,
	Addt__u = 0x1601a0,
	Subt__u = 0x1601a1,
	Mult__u = 0x1601a2,
	Divt__u = 0x1601a3,
	Cvtts__u = 0x1601ac,
	Cvttq__v = 0x1601af,
	Adds__ud = 0x1601c0,
	Subs__ud = 0x1601c1,
	Muls__ud = 0x1601c2,
	Divs__ud = 0x1601c3,
	Addt__ud = 0x1601e0,
	Subt__ud = 0x1601e1,
	Mult__ud = 0x1601e2,
	Divt__ud = 0x1601e3,
	Cvtts__ud = 0x1601ec,
	Cvttq__vd = 0x1601ef,
	Cvtst = 0x1602ac,
	Adds__suc = 0x160500,
	Subs__suc = 0x160501,
	Muls__suc = 0x160502,
	Divs__suc = 0x160503,
	Addt__suc = 0x160520,
	Subt__suc = 0x160521,
	Mult__suc = 0x160522,
	Divt__suc = 0x160523,
	Cvtts__suc = 0x16052c,
	Cvttq__svc = 0x16052f,
	Adds__sum = 0x160540,
	Subs__sum = 0x160541,
	Muls__sum = 0x160542,
	Divs__sum = 0x160543,
	Addt__sum = 0x160560,
	Subt__sum = 0x160561,
	Mult__sum = 0x160562,
	Divt__sum = 0x160563,
	Cvtts__sum = 0x16056c,
	Cvttq__svm = 0x16056f,
	Adds__su = 0x160580,
	Subs__su = 0x160581,
	Muls__su = 0x160582,
	Divs__su = 0x160583,
	Addt__su = 0x1605a0,
	Subt__su = 0x1605a1,
	Mult__su = 0x1605a2,
	Divt__su = 0x1605a3,
	Cmptun__su = 0x1605a4,
	Cmpteq__su = 0x1605a5,
	Cmptlt__su = 0x1605a6,
	Cmptle__su = 0x1605a7,
	Cvtts__su = 0x1605ac,
	Cvttq__sv = 0x1605af,
	Adds__sud = 0x1605c0,
	Subs__sud = 0x1605c1,
	Muls__sud = 0x1605c2,
	Divs__sud = 0x1605c3,
	Addt__sud = 0x1605e0,
	Subt__sud = 0x1605e1,
	Mult__sud = 0x1605e2,
	Divt__sud = 0x1605e3,
	Cvtts__sud = 0x1605ec,
	Cvttq__svd = 0x1605ef,
	Cvtst__s = 0x1606ac,
	Adds__suic = 0x160700,
	Subs__suic = 0x160701,
	Muls__suic = 0x160702,
	Divs__suic = 0x160703,
	Addt__suic = 0x160720,
	Subt__suic = 0x160721,
	Mult__suic = 0x160722,
	Divt__suic = 0x160723,
	Cvtts__suic = 0x16072c,
	Cvttq__svic = 0x16072f,
	Cvtqs__suic = 0x16073c,
	Cvtqt__suic = 0x16073e,
	Adds__suim = 0x160740,
	Subs__suim = 0x160741,
	Muls__suim = 0x160742,
	Divs__suim = 0x160743,
	Addt__suim = 0x160760,
	Subt__suim = 0x160761,
	Mult__suim = 0x160762,
	Divt__suim = 0x160763,
	Cvtts__suim = 0x16076c,
	Cvttq__svim = 0x16076f,
	Cvtqs__suim = 0x16077c,
	Cvtqt__suim = 0x16077e,
	Adds__sui = 0x160780,
	Subs__sui = 0x160781,
	Muls__sui = 0x160782,
	Divs__sui = 0x160783,
	Addt__sui = 0x1607a0,
	Subt__sui = 0x1607a1,
	Mult__sui = 0x1607a2,
	Divt__sui = 0x1607a3,
	Cvtts__sui = 0x1607ac,
	Cvttq__svi = 0x1607af,
	Cvtqs__sui = 0x1607bc,
	Cvtqt__sui = 0x1607be,
	Adds__suid = 0x1607c0,
	Subs__suid = 0x1607c1,
	Muls__suid = 0x1607c2,
	Divs__suid = 0x1607c3,
	Addt__suid = 0x1607e0,
	Subt__suid = 0x1607e1,
	Mult__suid = 0x1607e2,
	Divt__suid = 0x1607e3,
	Cvtts__suid = 0x1607ec,
	Cvttq__svid = 0x1607ef,
	Cvtqs__suid = 0x1607fc,
	Cvtqt__suid = 0x1607fe,
	Cvtlq = 0x170010,
	Cpys = 0x170020,
	Cpysn = 0x170021,
	Cpyse = 0x170022,
	Mt_fpcr = 0x170024,
	Mf_fpcr = 0x170025,
	Fcmoveq = 0x17002a,
	Fcmovne = 0x17002b,
	Fcmovlt = 0x17002c,
	Fcmovge = 0x17002d,
	Fcmovle = 0x17002e,
	Fcmovgt = 0x17002f,
	Cvtql = 0x170030,
	Cvtql__v = 0x170130,
	Cvtql__sv = 0x170530,
	Trapb = 0x180000,
	Excb = 0x180400,
	Mb = 0x184000,
	Wmb = 0x184400,
	Fetch = 0x188000,
	Fetch_m = 0x18a000,
	Rpcc = 0x18c000,
	Rc = 0x18e000,
	Ecb = 0x18e800,
	Rs = 0x18f000,
	Wh64 = 0x18f800,
	Wh64en = 0x18fc00,
	Pal19 = 0x190000,
	Jmp = 0x1a0000,
	Jsr = 0x1a0001,
	Ret = 0x1a0002,
	Jsr_coroutine = 0x1a0003,
	Pal1b = 0x1b0000,
	Sextb = 0x1c0000,
	Sextw = 0x1c0001,
	Ctpop = 0x1c0030,
	Perr = 0x1c0031,
	Ctlz = 0x1c0032,
	Cttz = 0x1c0033,
	Unpkbw = 0x1c0034,
	Unpkbl = 0x1c0035,
	Pkwb = 0x1c0036,
	Pklb = 0x1c0037,
	Minsb8 = 0x1c0038,
	Minsw4 = 0x1c0039,
	Minub8 = 0x1c003a,
	Minuw4 = 0x1c003b,
	Maxub8 = 0x1c003c,
	Maxuw4 = 0x1c003d,
	Maxsb8 = 0x1c003e,
	Maxsw4 = 0x1c003f,
	Ftoit = 0x1c0070,
	Ftois = 0x1c0078,
	Pal1d = 0x1d0000,
	Pal1e = 0x1e0000,
	Pal1f = 0x1f0000,
	Ldf = 0x200000,
	Ldg = 0x210000,
	Lds = 0x220000,
	Prefetch_m = 0x220001,
	Ldt = 0x230000,
	Prefetch_men = 0x230001,
	Stf = 0x240000,
	Stg = 0x250000,
	Sts = 0x260000,
	Stt = 0x270000,
	Ldl = 0x280000,
	Prefetch = 0x280001,
	Ldq = 0x290000,
	Prefetch_en = 0x290001,
	Ldl_l = 0x2a0000,
	Ldq_l = 0x2b0000,
	Stl = 0x2c0000,
	Stq = 0x2d0000,
	Stl_c = 0x2e0000,
	Stq_c = 0x2f0000,
	Br = 0x300000,
	Fbeq = 0x310000,
	Fblt = 0x320000,
	Fble = 0x330000,
	Bsr = 0x340000,
	Fbne = 0x350000,
	Fbge = 0x360000,
	Fbgt = 0x370000,
	Blbc = 0x380000,
	Beq = 0x390000,
	Blt = 0x3a0000,
	Ble = 0x3b0000,
	Blbs = 0x3c0000,
	Bne = 0x3d0000,
	Bge = 0x3e0000,
	Bgt = 0x3f0000,
};

const char *op00[] = { "call_pal" };
const char *op01[] = { "opc01" };
const char *op02[] = { "opc02" };
const char *op03[] = { "opc03" };
const char *op04[] = { "opc04" };
const char *op05[] = { "opc05" };
const char *op06[] = { "opc06" };
const char *op07[] = { "opc07" };
const char *op08[] = { "lda" };
const char *op09[] = { "ldah" };
const char *op0a[] = { "ldbu" };
const char *op0b[] = { "ldq_u" };
const char *op0c[] = { "ldwu" };
const char *op0d[] = { "stw" };
const char *op0e[] = { "stb" };
const char *op0f[] = { "stq_u" };
const char *op10[0x80];
const char *op11[0x80];
const char *op12[0x80];
const char *op13[0x80];
const char *op14[0x800];
const char *op15[0x800];
const char *op16[0x800];
const char *op17[0x800];
const char *op18[] = { "pal18" };
const char *op19[] = { "pal19" };
const char *op1a[0x4];
const char *op1b[] = { "pal1b" };
const char *op1c[0x80];
const char *op1d[] = { "pal1d" };
const char *op1e[] = { "pal1e" };
const char *op1f[] = { "pal1f" };
const char *op20[] = { "ldf" };
const char *op21[] = { "ldg" };
const char *op22[] = { "lds", "prefetch_m" };
const char *op23[] = { "ldt", "prefetch_men" };
const char *op24[] = { "stf" };
const char *op25[] = { "stg" };
const char *op26[] = { "sts" };
const char *op27[] = { "stt" };
const char *op28[] = { "ldl", "prefetch" };
const char *op29[] = { "ldq", "prefetch_en" };
const char *op2a[] = { "ldl_l" };
const char *op2b[] = { "ldq_l" };
const char *op2c[] = { "stl" };
const char *op2d[] = { "stq" };
const char *op2e[] = { "stl_c" };
const char *op2f[] = { "stq_c" };
const char *op30[] = { "br" };
const char *op31[] = { "fbeq" };
const char *op32[] = { "fblt" };
const char *op33[] = { "fble" };
const char *op34[] = { "bsr" };
const char *op35[] = { "fbne" };
const char *op36[] = { "fbge" };
const char *op37[] = { "fbgt" };
const char *op38[] = { "blbc" };
const char *op39[] = { "beq" };
const char *op3a[] = { "blt" };
const char *op3b[] = { "ble" };
const char *op3c[] = { "blbs" };
const char *op3d[] = { "bne" };
const char *op3e[] = { "bge" };
const char *op3f[] = { "bgt" };

const char **subops[] =
{
	op00, op01, op02, op03, op04, op05, op06, op07,
	op08, op09, op0a, op0b, op0c, op0d, op0e, op0f,
	op10, op11, op12, op13, op14, op15, op16, op17,
	op18, op19, op1a, op1b, op1c, op1d, op1e, op1f,
	op20, op21, op22, op23, op24, op25, op26, op27,
	op28, op29, op2a, op2b, op2c, op2d, op2e, op2f,
	op30, op31, op32, op33, op34, op35, op36, op37,
	op38, op39, op3a, op3b, op3c, op3d, op3e, op3f,
};

void init_table()
{
	subops[0x10][0x00] = "addl";
	subops[0x10][0x02] = "s4addl";
	subops[0x10][0x09] = "subl";
	subops[0x10][0x0b] = "s4subl";
	subops[0x10][0x0f] = "cmpbge";
	subops[0x10][0x12] = "s8addl";
	subops[0x10][0x1b] = "s8subl";
	subops[0x10][0x1d] = "cmpult";
	subops[0x10][0x20] = "addq";
	subops[0x10][0x22] = "s4addq";
	subops[0x10][0x29] = "subq";
	subops[0x10][0x2b] = "s4subq";
	subops[0x10][0x2d] = "cmpeq";
	subops[0x10][0x32] = "s8addq";
	subops[0x10][0x3b] = "s8subq";
	subops[0x10][0x3d] = "cmpule";
	subops[0x10][0x40] = "addl/v";
	subops[0x10][0x49] = "subl/v";
	subops[0x10][0x4d] = "cmplt";
	subops[0x10][0x60] = "addq/v";
	subops[0x10][0x69] = "subq/v";
	subops[0x10][0x6d] = "cmple";

	subops[0x11][0x00] = "and";
	subops[0x11][0x08] = "bic";
	subops[0x11][0x14] = "cmovlbs";
	subops[0x11][0x16] = "cmovlbc";
	subops[0x11][0x20] = "bis";
	subops[0x11][0x24] = "cmoveq";
	subops[0x11][0x26] = "cmovne";
	subops[0x11][0x28] = "ornot";
	subops[0x11][0x40] = "xor";
	subops[0x11][0x44] = "cmovlt";
	subops[0x11][0x46] = "cmovge";
	subops[0x11][0x48] = "eqv";
	subops[0x11][0x61] = "amask";
	subops[0x11][0x64] = "cmovle";
	subops[0x11][0x66] = "cmovgt";
	subops[0x11][0x6c] = "implver";

	subops[0x12][0x02] = "mskbl";
	subops[0x12][0x06] = "extbl";
	subops[0x12][0x0b] = "insbl";
	subops[0x12][0x12] = "mskwl";
	subops[0x12][0x16] = "extwl";
	subops[0x12][0x1b] = "inswl";
	subops[0x12][0x22] = "mskll";
	subops[0x12][0x26] = "extll";
	subops[0x12][0x2b] = "insll";
	subops[0x12][0x30] = "zap";
	subops[0x12][0x31] = "zapnot";
	subops[0x12][0x32] = "mskql";
	subops[0x12][0x34] = "srl";
	subops[0x12][0x36] = "extql";
	subops[0x12][0x39] = "sll";
	subops[0x12][0x3b] = "insql";
	subops[0x12][0x3c] = "sra";
	subops[0x12][0x52] = "mskwh";
	subops[0x12][0x57] = "inswh";
	subops[0x12][0x5a] = "extwh";
	subops[0x12][0x62] = "msklh";
	subops[0x12][0x67] = "inslh";
	subops[0x12][0x6a] = "extlh";
	subops[0x12][0x72] = "mskqh";
	subops[0x12][0x77] = "insqh";
	subops[0x12][0x7a] = "extqh";

	subops[0x13][0x00] = "mull";
	subops[0x13][0x20] = "mulq";
	subops[0x13][0x30] = "umulh";
	subops[0x13][0x40] = "mull/v";
	subops[0x13][0x60] = "mulq/v";

	subops[0x14][0x004] = "itofs";
	subops[0x14][0x00a] = "sqrtf/c";
	subops[0x14][0x00b] = "sqrts/c";
	subops[0x14][0x014] = "itoff";
	subops[0x14][0x024] = "itoft";
	subops[0x14][0x02a] = "sqrtg/c";
	subops[0x14][0x02b] = "sqrtt/c";
	subops[0x14][0x04b] = "sqrts/m";
	subops[0x14][0x06b] = "sqrtt/m";
	subops[0x14][0x08a] = "sqrtf";
	subops[0x14][0x08b] = "sqrts";
	subops[0x14][0x0aa] = "sqrtg";
	subops[0x14][0x0ab] = "sqrtt";
	subops[0x14][0x0cb] = "sqrts/d";
	subops[0x14][0x0eb] = "sqrtt/d";
	subops[0x14][0x10a] = "sqrtf/uc";
	subops[0x14][0x10b] = "sqrts/uc";
	subops[0x14][0x12a] = "sqrtg/uc";
	subops[0x14][0x12b] = "sqrtt/uc";
	subops[0x14][0x14b] = "sqrts/um";
	subops[0x14][0x16b] = "sqrtt/um";
	subops[0x14][0x18a] = "sqrtf/u";
	subops[0x14][0x18b] = "sqrts/u";
	subops[0x14][0x1aa] = "sqrtg/u";
	subops[0x14][0x1ab] = "sqrtt/u";
	subops[0x14][0x1cb] = "sqrts/ud";
	subops[0x14][0x1eb] = "sqrtt/ud";
	subops[0x14][0x40a] = "sqrtf/sc";
	subops[0x14][0x42a] = "sqrtg/sc";
	subops[0x14][0x48a] = "sqrtf/s";
	subops[0x14][0x4aa] = "sqrtg/s";
	subops[0x14][0x50a] = "sqrtf/suc";
	subops[0x14][0x50b] = "sqrts/suc";
	subops[0x14][0x52a] = "sqrtg/suc";
	subops[0x14][0x52b] = "sqrtt/suc";
	subops[0x14][0x54b] = "sqrts/sum";
	subops[0x14][0x56b] = "sqrtt/sum";
	subops[0x14][0x58a] = "sqrtf/su";
	subops[0x14][0x58b] = "sqrts/su";
	subops[0x14][0x5aa] = "sqrtg/su";
	subops[0x14][0x5ab] = "sqrtt/su";
	subops[0x14][0x5cb] = "sqrts/sud";
	subops[0x14][0x5eb] = "sqrtt/sud";
	subops[0x14][0x70b] = "sqrts/suic";
	subops[0x14][0x72b] = "sqrtt/suic";
	subops[0x14][0x74b] = "sqrts/suim";
	subops[0x14][0x76b] = "sqrtt/suim";
	subops[0x14][0x78b] = "sqrts/sui";
	subops[0x14][0x7ab] = "sqrtt/sui";
	subops[0x14][0x7cb] = "sqrts/suid";
	subops[0x14][0x7eb] = "sqrtt/suid";

	subops[0x15][0x000] = "addf/c";
	subops[0x15][0x001] = "subf/c";
	subops[0x15][0x002] = "mulf/c";
	subops[0x15][0x003] = "divf/c";
	subops[0x15][0x01e] = "cvtdg/c";
	subops[0x15][0x020] = "addg/c";
	subops[0x15][0x021] = "subg/c";
	subops[0x15][0x022] = "mulg/c";
	subops[0x15][0x023] = "divg/c";
	subops[0x15][0x02c] = "cvtgf/c";
	subops[0x15][0x02d] = "cvtgd/c";
	subops[0x15][0x02f] = "cvtgq/c";
	subops[0x15][0x03c] = "cvtqf/c";
	subops[0x15][0x03e] = "cvtqg/c";
	subops[0x15][0x080] = "addf";
	subops[0x15][0x081] = "subf";
	subops[0x15][0x082] = "mulf";
	subops[0x15][0x083] = "divf";
	subops[0x15][0x09e] = "cvtdg";
	subops[0x15][0x0a0] = "addg";
	subops[0x15][0x0a1] = "subg";
	subops[0x15][0x0a2] = "mulg";
	subops[0x15][0x0a3] = "divg";
	subops[0x15][0x0a5] = "cmpgeq";
	subops[0x15][0x0a6] = "cmpglt";
	subops[0x15][0x0a7] = "cmpgle";
	subops[0x15][0x0ac] = "cvtgf";
	subops[0x15][0x0ad] = "cvtgd";
	subops[0x15][0x0af] = "cvtgq";
	subops[0x15][0x0bc] = "cvtqf";
	subops[0x15][0x0be] = "cvtqg";
	subops[0x15][0x100] = "addf/uc";
	subops[0x15][0x101] = "subf/uc";
	subops[0x15][0x102] = "mulf/uc";
	subops[0x15][0x103] = "divf/uc";
	subops[0x15][0x11e] = "cvtdg/uc";
	subops[0x15][0x120] = "addg/uc";
	subops[0x15][0x121] = "subg/uc";
	subops[0x15][0x122] = "mulg/uc";
	subops[0x15][0x123] = "divg/uc";
	subops[0x15][0x12c] = "cvtgf/uc";
	subops[0x15][0x12d] = "cvtgd/uc";
	subops[0x15][0x12f] = "cvtgq/vc";
	subops[0x15][0x180] = "addf/u";
	subops[0x15][0x181] = "subf/u";
	subops[0x15][0x182] = "mulf/u";
	subops[0x15][0x183] = "divf/u";
	subops[0x15][0x19e] = "cvtdg/u";
	subops[0x15][0x1a0] = "addg/u";
	subops[0x15][0x1a1] = "subg/u";
	subops[0x15][0x1a2] = "mulg/u";
	subops[0x15][0x1a3] = "divg/u";
	subops[0x15][0x1ac] = "cvtgf/u";
	subops[0x15][0x1ad] = "cvtgd/u";
	subops[0x15][0x1af] = "cvtgq/v";
	subops[0x15][0x400] = "addf/sc";
	subops[0x15][0x401] = "subf/sc";
	subops[0x15][0x402] = "mulf/sc";
	subops[0x15][0x403] = "divf/sc";
	subops[0x15][0x41e] = "cvtdg/sc";
	subops[0x15][0x420] = "addg/sc";
	subops[0x15][0x421] = "subg/sc";
	subops[0x15][0x422] = "mulg/sc";
	subops[0x15][0x423] = "divg/sc";
	subops[0x15][0x42c] = "cvtgf/sc";
	subops[0x15][0x42d] = "cvtgd/sc";
	subops[0x15][0x42f] = "cvtgq/sc";
	subops[0x15][0x480] = "addf/s";
	subops[0x15][0x481] = "subf/s";
	subops[0x15][0x482] = "mulf/s";
	subops[0x15][0x483] = "divf/s";
	subops[0x15][0x49e] = "cvtdg/s";
	subops[0x15][0x4a0] = "addg/s";
	subops[0x15][0x4a1] = "subg/s";
	subops[0x15][0x4a2] = "mulg/s";
	subops[0x15][0x4a3] = "divg/s";
	subops[0x15][0x4a5] = "cmpgeq/s";
	subops[0x15][0x4a6] = "cmpglt/s";
	subops[0x15][0x4a7] = "cmpgle/s";
	subops[0x15][0x4ac] = "cvtgf/s";
	subops[0x15][0x4ad] = "cvtgd/s";
	subops[0x15][0x4af] = "cvtgq/s";
	subops[0x15][0x500] = "addf/suc";
	subops[0x15][0x501] = "subf/suc";
	subops[0x15][0x502] = "mulf/suc";
	subops[0x15][0x503] = "divf/suc";
	subops[0x15][0x51e] = "cvtdg/suc";
	subops[0x15][0x520] = "addg/suc";
	subops[0x15][0x521] = "subg/suc";
	subops[0x15][0x522] = "mulg/suc";
	subops[0x15][0x523] = "divg/suc";
	subops[0x15][0x52c] = "cvtgf/suc";
	subops[0x15][0x52d] = "cvtgd/suc";
	subops[0x15][0x52f] = "cvtgq/svc";
	subops[0x15][0x580] = "addf/su";
	subops[0x15][0x581] = "subf/su";
	subops[0x15][0x582] = "mulf/su";
	subops[0x15][0x583] = "divf/su";
	subops[0x15][0x59e] = "cvtdg/su";
	subops[0x15][0x5a0] = "addg/su";
	subops[0x15][0x5a1] = "subg/su";
	subops[0x15][0x5a2] = "mulg/su";
	subops[0x15][0x5a3] = "divg/su";
	subops[0x15][0x5ac] = "cvtgf/su";
	subops[0x15][0x5ad] = "cvtgd/su";
	subops[0x15][0x5af] = "cvtgq/sv";

	subops[0x16][0x000] = "adds/c";
	subops[0x16][0x001] = "subs/c";
	subops[0x16][0x002] = "muls/c";
	subops[0x16][0x003] = "divs/c";
	subops[0x16][0x020] = "addt/c";
	subops[0x16][0x021] = "subt/c";
	subops[0x16][0x022] = "mult/c";
	subops[0x16][0x023] = "divt/c";
	subops[0x16][0x02c] = "cvtts/c";
	subops[0x16][0x02f] = "cvttq/c";
	subops[0x16][0x03c] = "cvtqs/c";
	subops[0x16][0x03e] = "cvtqt/c";
	subops[0x16][0x040] = "adds/m";
	subops[0x16][0x041] = "subs/m";
	subops[0x16][0x042] = "muls/m";
	subops[0x16][0x043] = "divs/m";
	subops[0x16][0x060] = "addt/m";
	subops[0x16][0x061] = "subt/m";
	subops[0x16][0x062] = "mult/m";
	subops[0x16][0x063] = "divt/m";
	subops[0x16][0x06c] = "cvtts/m";
	subops[0x16][0x06f] = "cvttq/m";
	subops[0x16][0x07c] = "cvtqs/m";
	subops[0x16][0x07e] = "cvtqt/m";
	subops[0x16][0x080] = "adds";
	subops[0x16][0x081] = "subs";
	subops[0x16][0x082] = "muls";
	subops[0x16][0x083] = "divs";
	subops[0x16][0x0a0] = "addt";
	subops[0x16][0x0a1] = "subt";
	subops[0x16][0x0a2] = "mult";
	subops[0x16][0x0a3] = "divt";
	subops[0x16][0x0a4] = "cmptun";
	subops[0x16][0x0a5] = "cmpteq";
	subops[0x16][0x0a6] = "cmptlt";
	subops[0x16][0x0a7] = "cmptle";
	subops[0x16][0x0ac] = "cvtts";
	subops[0x16][0x0af] = "cvttq";
	subops[0x16][0x0bc] = "cvtqs";
	subops[0x16][0x0be] = "cvtqt";
	subops[0x16][0x0c0] = "adds/d";
	subops[0x16][0x0c1] = "subs/d";
	subops[0x16][0x0c2] = "muls/d";
	subops[0x16][0x0c3] = "divs/d";
	subops[0x16][0x0e0] = "addt/d";
	subops[0x16][0x0e1] = "subt/d";
	subops[0x16][0x0e2] = "mult/d";
	subops[0x16][0x0e3] = "divt/d";
	subops[0x16][0x0ec] = "cvtts/d";
	subops[0x16][0x0ef] = "cvttq/d";
	subops[0x16][0x0fc] = "cvtqs/d";
	subops[0x16][0x0fe] = "cvtqt/d";
	subops[0x16][0x100] = "adds/uc";
	subops[0x16][0x101] = "subs/uc";
	subops[0x16][0x102] = "muls/uc";
	subops[0x16][0x103] = "divs/uc";
	subops[0x16][0x120] = "addt/uc";
	subops[0x16][0x121] = "subt/uc";
	subops[0x16][0x122] = "mult/uc";
	subops[0x16][0x123] = "divt/uc";
	subops[0x16][0x12c] = "cvtts/uc";
	subops[0x16][0x12f] = "cvttq/vc";
	subops[0x16][0x140] = "adds/um";
	subops[0x16][0x141] = "subs/um";
	subops[0x16][0x142] = "muls/um";
	subops[0x16][0x143] = "divs/um";
	subops[0x16][0x160] = "addt/um";
	subops[0x16][0x161] = "subt/um";
	subops[0x16][0x162] = "mult/um";
	subops[0x16][0x163] = "divt/um";
	subops[0x16][0x16c] = "cvtts/um";
	subops[0x16][0x16f] = "cvttq/vm";
	subops[0x16][0x180] = "adds/u";
	subops[0x16][0x181] = "subs/u";
	subops[0x16][0x182] = "muls/u";
	subops[0x16][0x183] = "divs/u";
	subops[0x16][0x1a0] = "addt/u";
	subops[0x16][0x1a1] = "subt/u";
	subops[0x16][0x1a2] = "mult/u";
	subops[0x16][0x1a3] = "divt/u";
	subops[0x16][0x1ac] = "cvtts/u";
	subops[0x16][0x1af] = "cvttq/v";
	subops[0x16][0x1c0] = "adds/ud";
	subops[0x16][0x1c1] = "subs/ud";
	subops[0x16][0x1c2] = "muls/ud";
	subops[0x16][0x1c3] = "divs/ud";
	subops[0x16][0x1e0] = "addt/ud";
	subops[0x16][0x1e1] = "subt/ud";
	subops[0x16][0x1e2] = "mult/ud";
	subops[0x16][0x1e3] = "divt/ud";
	subops[0x16][0x1ec] = "cvtts/ud";
	subops[0x16][0x1ef] = "cvttq/vd";
	subops[0x16][0x2ac] = "cvtst";
	subops[0x16][0x500] = "adds/suc";
	subops[0x16][0x501] = "subs/suc";
	subops[0x16][0x502] = "muls/suc";
	subops[0x16][0x503] = "divs/suc";
	subops[0x16][0x520] = "addt/suc";
	subops[0x16][0x521] = "subt/suc";
	subops[0x16][0x522] = "mult/suc";
	subops[0x16][0x523] = "divt/suc";
	subops[0x16][0x52c] = "cvtts/suc";
	subops[0x16][0x52f] = "cvttq/svc";
	subops[0x16][0x540] = "adds/sum";
	subops[0x16][0x541] = "subs/sum";
	subops[0x16][0x542] = "muls/sum";
	subops[0x16][0x543] = "divs/sum";
	subops[0x16][0x560] = "addt/sum";
	subops[0x16][0x561] = "subt/sum";
	subops[0x16][0x562] = "mult/sum";
	subops[0x16][0x563] = "divt/sum";
	subops[0x16][0x56c] = "cvtts/sum";
	subops[0x16][0x56f] = "cvttq/svm";
	subops[0x16][0x580] = "adds/su";
	subops[0x16][0x581] = "subs/su";
	subops[0x16][0x582] = "muls/su";
	subops[0x16][0x583] = "divs/su";
	subops[0x16][0x5a0] = "addt/su";
	subops[0x16][0x5a1] = "subt/su";
	subops[0x16][0x5a2] = "mult/su";
	subops[0x16][0x5a3] = "divt/su";
	subops[0x16][0x5a4] = "cmptun/su";
	subops[0x16][0x5a5] = "cmpteq/su";
	subops[0x16][0x5a6] = "cmptlt/su";
	subops[0x16][0x5a7] = "cmptle/su";
	subops[0x16][0x5ac] = "cvtts/su";
	subops[0x16][0x5af] = "cvttq/sv";
	subops[0x16][0x5c0] = "adds/sud";
	subops[0x16][0x5c1] = "subs/sud";
	subops[0x16][0x5c2] = "muls/sud";
	subops[0x16][0x5c3] = "divs/sud";
	subops[0x16][0x5e0] = "addt/sud";
	subops[0x16][0x5e1] = "subt/sud";
	subops[0x16][0x5e2] = "mult/sud";
	subops[0x16][0x5e3] = "divt/sud";
	subops[0x16][0x5ec] = "cvtts/sud";
	subops[0x16][0x5ef] = "cvttq/svd";
	subops[0x16][0x6ac] = "cvtst/s";
	subops[0x16][0x700] = "adds/suic";
	subops[0x16][0x701] = "subs/suic";
	subops[0x16][0x702] = "muls/suic";
	subops[0x16][0x703] = "divs/suic";
	subops[0x16][0x720] = "addt/suic";
	subops[0x16][0x721] = "subt/suic";
	subops[0x16][0x722] = "mult/suic";
	subops[0x16][0x723] = "divt/suic";
	subops[0x16][0x72c] = "cvtts/suic";
	subops[0x16][0x72f] = "cvttq/svic";
	subops[0x16][0x73c] = "cvtqs/suic";
	subops[0x16][0x73e] = "cvtqt/suic";
	subops[0x16][0x740] = "adds/suim";
	subops[0x16][0x741] = "subs/suim";
	subops[0x16][0x742] = "muls/suim";
	subops[0x16][0x743] = "divs/suim";
	subops[0x16][0x760] = "addt/suim";
	subops[0x16][0x761] = "subt/suim";
	subops[0x16][0x762] = "mult/suim";
	subops[0x16][0x763] = "divt/suim";
	subops[0x16][0x76c] = "cvtts/suim";
	subops[0x16][0x76f] = "cvttq/svim";
	subops[0x16][0x77c] = "cvtqs/suim";
	subops[0x16][0x77e] = "cvtqt/suim";
	subops[0x16][0x780] = "adds/sui";
	subops[0x16][0x781] = "subs/sui";
	subops[0x16][0x782] = "muls/sui";
	subops[0x16][0x783] = "divs/sui";
	subops[0x16][0x7a0] = "addt/sui";
	subops[0x16][0x7a1] = "subt/sui";
	subops[0x16][0x7a2] = "mult/sui";
	subops[0x16][0x7a3] = "divt/sui";
	subops[0x16][0x7ac] = "cvtts/sui";
	subops[0x16][0x7af] = "cvttq/svi";
	subops[0x16][0x7bc] = "cvtqs/sui";
	subops[0x16][0x7be] = "cvtqt/sui";
	subops[0x16][0x7c0] = "adds/suid";
	subops[0x16][0x7c1] = "subs/suid";
	subops[0x16][0x7c2] = "muls/suid";
	subops[0x16][0x7c3] = "divs/suid";
	subops[0x16][0x7e0] = "addt/suid";
	subops[0x16][0x7e1] = "subt/suid";
	subops[0x16][0x7e2] = "mult/suid";
	subops[0x16][0x7e3] = "divt/suid";
	subops[0x16][0x7ec] = "cvtts/suid";
	subops[0x16][0x7ef] = "cvttq/svid";
	subops[0x16][0x7fc] = "cvtqs/suid";
	subops[0x16][0x7fe] = "cvtqt/suid";

	subops[0x17][0x010] = "cvtlq";
	subops[0x17][0x020] = "cpys";
	subops[0x17][0x021] = "cpysn";
	subops[0x17][0x022] = "cpyse";
	subops[0x17][0x024] = "mt_fpcr";
	subops[0x17][0x025] = "mf_fpcr";
	subops[0x17][0x02a] = "fcmoveq";
	subops[0x17][0x02b] = "fcmovne";
	subops[0x17][0x02c] = "fcmovlt";
	subops[0x17][0x02d] = "fcmovge";
	subops[0x17][0x02e] = "fcmovle";
	subops[0x17][0x02f] = "fcmovgt";
	subops[0x17][0x030] = "cvtql";
	subops[0x17][0x130] = "cvtql/v";
	subops[0x17][0x530] = "cvtql/sv";

	//subops[0x18][0x0000] = "trapb";
	//subops[0x18][0x0400] = "excb";
	//subops[0x18][0x4000] = "mb";
	//subops[0x18][0x4400] = "wmb";
	//subops[0x18][0x8000] = "fetch";
	//subops[0x18][0xa000] = "fetch_m";
	//subops[0x18][0xc000] = "rpcc";
	//subops[0x18][0xe000] = "rc";
	//subops[0x18][0xe800] = "ecb";
	//subops[0x18][0xf000] = "rs";
	//subops[0x18][0xf800] = "wh64";
	//subops[0x18][0xfc00] = "wh64en";

	subops[0x1a][0x0] = "jmp";
	subops[0x1a][0x1] = "jsr";
	subops[0x1a][0x2] = "ret";
	subops[0x1a][0x3] = "jsr_coroutine";

	subops[0x1c][0x00] = "sextb";
	subops[0x1c][0x01] = "sextw";
	subops[0x1c][0x30] = "ctpop";
	subops[0x1c][0x31] = "perr";
	subops[0x1c][0x32] = "ctlz";
	subops[0x1c][0x33] = "cttz";
	subops[0x1c][0x34] = "unpkbw";
	subops[0x1c][0x35] = "unpkbl";
	subops[0x1c][0x36] = "pkwb";
	subops[0x1c][0x37] = "pklb";
	subops[0x1c][0x38] = "minsb8";
	subops[0x1c][0x39] = "minsw4";
	subops[0x1c][0x3a] = "minub8";
	subops[0x1c][0x3b] = "minuw4";
	subops[0x1c][0x3c] = "maxub8";
	subops[0x1c][0x3d] = "maxuw4";
	subops[0x1c][0x3e] = "maxsb8";
	subops[0x1c][0x3f] = "maxsw4";
	subops[0x1c][0x70] = "ftoit";
	subops[0x1c][0x78] = "ftois";
}

enum Op get_op(uint32_t code)
{
	int op = (int)(code >> 26), subop = 0;
	switch (op)
	{
		case 0x10:
		case 0x11:
		case 0x12:
		case 0x13: subop = (code >> 5) & 0x7f; break;
		case 0x14:
		case 0x15:
		case 0x16:
		case 0x17: subop = (code >> 5) & 0x7ff; break;
		case 0x18:
			switch (code & 0xffff)
			{
				case 0x0000: return Trapb;
				case 0x0400: return Excb;
				case 0x4000: return Mb;
				case 0x4400: return Wmb;
				case 0x8000: return Fetch;
				case 0xa000: return Fetch_m;
				case 0xc000: return Rpcc;
				case 0xe000: return Rc;
				case 0xf000: return Rs;
				case 0xe800: return Ecb;
				case 0xf800: return Wh64;
				case 0xfc00: return Wh64en;
			}
			break;
		case 0x1a: subop = (code >> 14) & 3; break;
		case 0x1c: subop = (code >> 5) & 0x7f; break;
	}
	return subops[op][subop] ? (enum Op)((op << 16) | subop) : UNDEF;
}

const char *get_mnemonic(enum Op op)
{
	return subops[((int)op) >>16][((int)op) & 0xffff];
}

void disassemble(void *f, uint64_t addr, uint32_t code)
{
	enum Op op = get_op(code);
	int opc = (int)(code >> 26);
	const char *mne = get_mnemonic(op);
	switch (formats[opc])
	{
		default:
			fprintf(f, "%s %08x", mne, code & 0x03ffffff);
			return;
		case Bra:
			{
				int ra = (int)((code >> 21) & 31);
				int disp = code & 0x001fffff;
				char sdisp[32];
				if (disp < 0x00100000)
					sprintf(sdisp, "%08x", addr + disp * 4 + 4);
				else
					sprintf(sdisp, "%08x", addr - (0x00200000 - disp) * 4 + 4);
				if (ra == 31 && op == Br)
					fprintf(f, "br %s", sdisp);
				else
					fprintf(f, "%s %s,%s", mne, regname[ra], sdisp);
				return;
			}
		case Mem:
			{
				int ra = (int)((code >> 21) & 31);
				int rb = (int)((code >> 16) & 31);
				int disp = (int)(code & 0xffff);
				char args[32];
				if (disp < 0x8000)
					sprintf(args, "0x%x(%s)", disp, regname[rb]);
				else
					sprintf(args, "-0x%x(%s)", 0x10000 - disp, regname[rb]);
				if (rb == 31 && op == Lda)
				{
					fprintf(f, "mov 0x%04x,%s", disp, regname[ra]);
					return;
				}
				else if (rb == 31 && op == Ldah)
				{
					fprintf(f, "mov 0x%04x0000,%s", disp, regname[ra]);
					return;
				}
				else if (ra == 31)
				{
					if (disp == 0 && op == Ldq_u)
					{
						fprintf(f, "unop");
						return;
					}
					else
					{
						const char *pse = 0;
						switch (op)
						{
							case Ldl: pse = "prefetch"; break;
							case Ldq: pse = "prefetch_en"; break;
							case Lds: pse = "prefetch_m"; break;
							case Ldt: pse = "prefetch_men"; break;
						}
						if (pse)
						{
							fprintf(f, "%s %s", pse, args);
							return;
						}
					}
				}
				fprintf(f, "%s %s,%s", mne, regname[ra], args);
				return;
			}
		case Mfc:
			{
				int ra = (int)((code >> 21) & 31);
				int rb = (int)((code >> 16) & 31);
				fprintf(f, "%s %s,%s", mne, regname[ra], regname[rb]);
				return;
			}
		case Mbr:
			{
				int ra = (int)((code >> 21) & 31);
				int rb = (int)((code >> 16) & 31);
				int disp = (int)(code & 0x3fff);
				fprintf(f, "%s %s,(%s),0x%04x", mne, regname[ra], regname[rb], disp);
				return;
			}
		case Opr:
			{
				int ra = (int)((code >> 21) & 31);
				int rb = -1;
				int rc = (int)(code & 31);
				char arg2[32];
				if ((code & 0x1000) == 0)
				{
					rb = (int)((code >> 16) & 31);
					strcpy(arg2, regname[rb]);
				}
				else
					sprintf(arg2, "0x%02x", (code >> 13) & 0xff);
				if (ra == 31)
				{
					const char *pse = 0;
					switch (op)
					{
						case Bis:
							if (rb == 31 && rc == 31)
							{
								fprintf(f, "nop");
								return;
							}
							else if (rb == 31)
							{
								fprintf(f, "clr %s", regname[rc]);
								return;
							}
							else
								pse = "mov";
							break;
						case Addl: pse = "sextl"; break;
						case Ornot: pse = "not"; break;
						case Subl: pse = "negl"; break;
						case Subl__v: pse = "negl/v"; break;
						case Subq: pse = "negq"; break;
						case Subq__v: pse = "negq/v"; break;
					}
					if (pse)
					{
						fprintf(f, "%s %s,%s", pse, arg2, regname[rc]);
						return;
					}
				}
				fprintf(f, "%s %s,%s,%s", mne, regname[ra], arg2, regname[rc]);
				return;
			}
		case F_P:
			{
				int fa = (int)((code >> 21) & 31);
				int fb = (int)((code >> 16) & 31);
				int fc = (int)(code & 31);
				int pst = 2;
				const char *pse = 0;
				if (fa == 31)
					switch (op)
					{
						case Cpys:
							if (fb == 31 && fc == 31)
							{
								pst = 0;
								pse = "fnop";
							}
							else if (fb == 31)
							{
								pst = 1;
								pse = "fclr";
							}
							else
								pse = "fabs";
							break;
						case Subf: pse = "negf"; break;
						case Subf__s: pse = "negf/s"; break;
						case Subg: pse = "negg"; break;
						case Subg__s: pse = "negg/s"; break;
						case Subs: pse = "negs"; break;
						case Subs__su: pse = "negs/su"; break;
						case Subs__sui: pse = "negs/sui"; break;
						case Subt: pse = "negt"; break;
						case Subt__su: pse = "negt/su"; break;
						case Subt__sui: pse = "negt/sui"; break;
					};
				if (pse == 0 && fa == fb)
					switch (op)
					{
						case Cpys: pse = "fmov"; break;
						case Cpysn: pse = "fneg"; break;
					}
				if (pse == 0 && fa == fb && fb == fc)
					switch (op)
					{
						case Mf_fpcr:
						case Mt_fpcr:
							pst = 1;
							pse = mne;
							break;
					}
				if (pse)
					switch (pst)
					{
						case 0:
							fprintf(f, "%s", pse);
							return;
						case 1:
							fprintf(f, "%s f%d", pse, fc);
							return;
						case 2:
							fprintf(f, "%s f%d,f%d", pse, fb, fc);
							return;
					}
				fprintf(f, "%s f%d,f%d,f%d", mne, fa, fb, fc);
				return;
			}
	}
}

uint64_t text_addr, text_size;
char text_buf[65536];

int read_text_file(void *f)
{
	int i;
	char buf[64], shstrtab[256];
	uint16_t e_shstrndx, e_shentsize, e_shnum;
	uint64_t e_shoff, stroff, strsize, textoff = 0;

	if (fread(buf, 64, 1, f) == 0)
	{
		printf("can not read ELF header.\n");
		return 0;
	}
	if (buf[0] != 0x7f || buf[1] != 'E' || buf[2] != 'L' || buf[3] != 'F')
	{
		printf("EI_MAG != { 0x7f, 'E', 'L', 'F' }\n");
		return 0;
	}
	if (buf[4] != 2)
	{
		printf("EI_CLASS != ELFCLASS64\n");
		return 0;
	}
	if (buf[5] != 1)
	{
		printf("EI_DATA != ELFDATA2LSB\n");
		return 0;
	}

	e_shoff = *(uint64_t *)&buf[40];
	e_shentsize = *(uint16_t *)&buf[58];
	e_shnum = *(uint16_t *)&buf[60];
	e_shstrndx = *(uint16_t *)&buf[62];

	if (e_shoff == 0)
	{
		printf("e_shoff == 0\n");
		return 0;
	}
	if (e_shstrndx == 0)
	{
		printf("e_shstrndx == 0\n");
		return 0;
	}
	if (fseek(f, (int)(e_shoff + e_shstrndx * e_shentsize + 24), 0) != 0 ||
		fread(&stroff, sizeof(stroff), 1, f) == 0 ||
		fread(&strsize, sizeof(strsize), 1, f) == 0 ||
		strsize > sizeof(shstrtab) ||
		fseek(f, (int)stroff, 0) != 0 ||
		fread(shstrtab, (int)strsize, 1, f) == 0)
	{
		printf("can not read shstrtab\n");
		return 0;
	}

	if (fseek(f, (int)e_shoff, 0) != 0)
	{
		printf("can not read section headers\n");
		return 0;
	}
	for (i = 0; i < e_shnum; i++)
	{
		const char *name;
		if (fread(buf, 64, 1, f) == 0) break;
		name = shstrtab + *(uint32_t *)buf;
		if (strcmp(name, ".text") == 0)
		{
			text_addr = *(uint64_t *)&buf[16];
			textoff = *(uint64_t *)&buf[24];
			text_size = *(uint64_t *)&buf[32];
			break;
		}
	}
	if (textoff == 0 ||
		text_size > sizeof(text_buf) ||
		fseek(f, (int)textoff, 0) != 0 ||
		fread(text_buf, (int)text_size, 1, f) == 0)
	{
		printf("can not read .text section\n");
		return 0;
	}

	return 1;
}

int read_text(const char *fn)
{
	int ret = 0;
	void *f = fopen(fn, "rb");
	if (f)
	{
		ret = read_text_file(f);
		fclose(f);
	}
	return ret;
}

int main()
{
	int i;
	init_table();
	for (i = 1; i <= 6; i++)
	{
		char src[32] = "../Test/", dst[32];
		char num[8] = "x";
		num[0] = '0' + i;
		strcat(src, num);
		strcpy(dst, src);
		strcat(dst, ".asm");
		printf("%s -> %s\n", src, dst);
		if (read_text(src))
		{
			void *f;
			printf("text_addr: 0x%08x\n", text_addr);
			printf("text_size: 0x%08x\n", text_size);
			f = fopen(dst, "w");
			if (f)
			{
				int j;
				for (j = 0; j < text_size; j += 4)
				{
					fprintf(f, "%08x: ", (long)(text_addr + j));
					disassemble(f, text_addr + j, *(uint32_t *)&text_buf[j]);
					fprintf(f, "\n");
				}
				fclose(f);
			}
		}
	}
	return 0;
}
