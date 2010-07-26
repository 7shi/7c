/* libc declaration */

typedef short int16_t;
typedef int int32_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef void FILE;

#ifdef __alpha
typedef long int64_t;
typedef unsigned long uint64_t;

void (*exit)(int) = (void *)0x00ef0000;
int (*fputc)(int, FILE *) = (void *)0x00ef0004;
int (*fgetc)(FILE *) = (void *)0x00ef0008;
FILE *(*fopen)(const char *, const char *) = (void *)0x00ef000c;
int (*fclose)(FILE *) = (void *)0x00ef0010;
int (*fwrite)(const void *, int, int, FILE *) = (void *)0x00ef0014;
int (*fread)(void *, int, int, FILE *) = (void *)0x00ef0018;
int (*fseek)(FILE *, long, int) = (void *)0x00ef001c;

int printf(const char *, ...);
int fprintf(FILE *, const char *, ...);
int snprintf(char *, int, const char *, ...);
int strcmp(const char *, const char *);
char *strncpy(char *, const char *, int);
char *strncat(char *, const char *, int);
void *memset(void *, int, int);
#else
typedef long long int64_t;
typedef unsigned long long uint64_t;

#ifdef _MSC_VER
#define snprintf _snprintf
#endif

int printf(const char *, ...);
int snprintf(char *, int, const char *, ...);
int fprintf(FILE *, const char *, ...);
FILE *fopen(const char *, const char *);
int fclose(FILE *);
int fread(void *, int, int, FILE *);
int fwrite(const void *, int, int, FILE *);
int fseek(FILE *, int, int);
int fgetc(FILE *);
int strcmp(const char *, const char *);
char *strncpy(char *, const char *, int);
char *strncat(char *, const char *, int);
void *memset(void *, int, int);
#endif

/* Alpha declaration */

enum Format
{
    ___, Pcd, Bra, Mem, Mfc, Mbr, Opr, F_P
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

enum Regs
{
    /* r00     */ V0,
    /* r01-r08 */ T0, T1, T2, T3, T4, T5, T6, T7,
    /* r09-r14 */ S0, S1, S2, S3, S4, S5,
    /* r15     */ FP,
    /* r16-r21 */ A0, A1, A2, A3, A4, A5,
    /* r22-r25 */ T8, T9, T10, T11,
    /* r26     */ RA,
    /* r27     */ T12,
    /* r28     */ AT,
    /* r29     */ GP,
    /* r30     */ SP,
    /* r31     */ Zero,
};

const char *regname[] =
{
    /* r00     */ "v0",
    /* r01-r08 */ "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
    /* r09-r14 */ "s0", "s1", "s2", "s3", "s4", "s5",
    /* r15     */ "fp",
    /* r16-r21 */ "a0", "a1", "a2", "a3", "a4", "a5",
    /* r22-r25 */ "t8", "t9", "t10", "t11",
    /* r26     */ "ra",
    /* r27     */ "t12",
    /* r28     */ "at",
    /* r29     */ "gp",
    /* r30     */ "sp",
    /* r31     */ "zero",
};

const int reglen = sizeof(regname) / sizeof(const char *);

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
    Unop = 0x0b0001,
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

const char *opnames[] =
{
    "addf", "addf/c", "addf/s", "addf/sc", "addf/su", "addf/suc", "addf/u", "addf/uc",
    "addg", "addg/c", "addg/s", "addg/sc", "addg/su", "addg/suc", "addg/u", "addg/uc",
    "addl", "addl/v", "addq", "addq/v", "adds", "adds/c", "adds/d", "adds/m",
    "adds/su", "adds/suc", "adds/sud", "adds/sui", "adds/suic", "adds/suid", "adds/suim", "adds/sum",
    "adds/u", "adds/uc", "adds/ud", "adds/um", "addt", "addt/c", "addt/d", "addt/m",
    "addt/su", "addt/suc", "addt/sud", "addt/sui", "addt/suic", "addt/suid", "addt/suim", "addt/sum",
    "addt/u", "addt/uc", "addt/ud", "addt/um", "amask", "and", "beq", "bge",
    "bgt", "bic", "bis", "blbc", "blbs", "ble", "blt", "bne",
    "br", "bsr", "call_pal", "cmoveq", "cmovge", "cmovgt", "cmovlbc", "cmovlbs",
    "cmovle", "cmovlt", "cmovne", "cmpbge", "cmpeq", "cmpgeq", "cmpgeq/s", "cmpgle",
    "cmpgle/s", "cmpglt", "cmpglt/s", "cmple", "cmplt", "cmpteq", "cmpteq/su", "cmptle",
    "cmptle/su", "cmptlt", "cmptlt/su", "cmptun", "cmptun/su", "cmpule", "cmpult", "cpys",
    "cpyse", "cpysn", "ctlz", "ctpop", "cttz", "cvtdg", "cvtdg/c", "cvtdg/s",
    "cvtdg/sc", "cvtdg/su", "cvtdg/suc", "cvtdg/u", "cvtdg/uc", "cvtgd", "cvtgd/c", "cvtgd/s",
    "cvtgd/sc", "cvtgd/su", "cvtgd/suc", "cvtgd/u", "cvtgd/uc", "cvtgf", "cvtgf/c", "cvtgf/s",
    "cvtgf/sc", "cvtgf/su", "cvtgf/suc", "cvtgf/u", "cvtgf/uc", "cvtgq", "cvtgq/c", "cvtgq/s",
    "cvtgq/sc", "cvtgq/sv", "cvtgq/svc", "cvtgq/v", "cvtgq/vc", "cvtlq", "cvtqf", "cvtqf/c",
    "cvtqg", "cvtqg/c", "cvtql", "cvtql/sv", "cvtql/v", "cvtqs", "cvtqs/c", "cvtqs/d",
    "cvtqs/m", "cvtqs/sui", "cvtqs/suic", "cvtqs/suid", "cvtqs/suim", "cvtqt", "cvtqt/c", "cvtqt/d",
    "cvtqt/m", "cvtqt/sui", "cvtqt/suic", "cvtqt/suid", "cvtqt/suim", "cvtst", "cvtst/s", "cvttq",
    "cvttq/c", "cvttq/d", "cvttq/m", "cvttq/sv", "cvttq/svc", "cvttq/svd", "cvttq/svi", "cvttq/svic",
    "cvttq/svid", "cvttq/svim", "cvttq/svm", "cvttq/v", "cvttq/vc", "cvttq/vd", "cvttq/vm", "cvtts",
    "cvtts/c", "cvtts/d", "cvtts/m", "cvtts/su", "cvtts/suc", "cvtts/sud", "cvtts/sui", "cvtts/suic",
    "cvtts/suid", "cvtts/suim", "cvtts/sum", "cvtts/u", "cvtts/uc", "cvtts/ud", "cvtts/um", "divf",
    "divf/c", "divf/s", "divf/sc", "divf/su", "divf/suc", "divf/u", "divf/uc", "divg",
    "divg/c", "divg/s", "divg/sc", "divg/su", "divg/suc", "divg/u", "divg/uc", "divs",
    "divs/c", "divs/d", "divs/m", "divs/su", "divs/suc", "divs/sud", "divs/sui", "divs/suic",
    "divs/suid", "divs/suim", "divs/sum", "divs/u", "divs/uc", "divs/ud", "divs/um", "divt",
    "divt/c", "divt/d", "divt/m", "divt/su", "divt/suc", "divt/sud", "divt/sui", "divt/suic",
    "divt/suid", "divt/suim", "divt/sum", "divt/u", "divt/uc", "divt/ud", "divt/um", "ecb",
    "eqv", "excb", "extbl", "extlh", "extll", "extqh", "extql", "extwh",
    "extwl", "fbeq", "fbge", "fbgt", "fble", "fblt", "fbne", "fcmoveq",
    "fcmovge", "fcmovgt", "fcmovle", "fcmovlt", "fcmovne", "fetch", "fetch_m", "ftois",
    "ftoit", "implver", "insbl", "inslh", "insll", "insqh", "insql", "inswh",
    "inswl", "itoff", "itofs", "itoft", "jmp", "jsr", "jsr_coroutine", "lda",
    "ldah", "ldbu", "ldf", "ldg", "ldl", "ldl_l", "ldq", "ldq_l",
    "ldq_u", "lds", "ldt", "ldwu", "maxsb8", "maxsw4", "maxub8", "maxuw4",
    "mb", "mf_fpcr", "minsb8", "minsw4", "minub8", "minuw4", "mskbl", "msklh",
    "mskll", "mskqh", "mskql", "mskwh", "mskwl", "mt_fpcr", "mulf", "mulf/c",
    "mulf/s", "mulf/sc", "mulf/su", "mulf/suc", "mulf/u", "mulf/uc", "mulg", "mulg/c",
    "mulg/s", "mulg/sc", "mulg/su", "mulg/suc", "mulg/u", "mulg/uc", "mull", "mull/v",
    "mulq", "mulq/v", "muls", "muls/c", "muls/d", "muls/m", "muls/su", "muls/suc",
    "muls/sud", "muls/sui", "muls/suic", "muls/suid", "muls/suim", "muls/sum", "muls/u", "muls/uc",
    "muls/ud", "muls/um", "mult", "mult/c", "mult/d", "mult/m", "mult/su", "mult/suc",
    "mult/sud", "mult/sui", "mult/suic", "mult/suid", "mult/suim", "mult/sum", "mult/u", "mult/uc",
    "mult/ud", "mult/um", "opc01", "opc02", "opc03", "opc04", "opc05", "opc06",
    "opc07", "ornot", "pal19", "pal1b", "pal1d", "pal1e", "pal1f", "perr",
    "pklb", "pkwb", "prefetch", "prefetch_en", "prefetch_m", "prefetch_men", "rc", "ret",
    "rpcc", "rs", "s4addl", "s4addq", "s4subl", "s4subq", "s8addl", "s8addq",
    "s8subl", "s8subq", "sextb", "sextw", "sll", "sqrtf", "sqrtf/c", "sqrtf/s",
    "sqrtf/sc", "sqrtf/su", "sqrtf/suc", "sqrtf/u", "sqrtf/uc", "sqrtg", "sqrtg/c", "sqrtg/s",
    "sqrtg/sc", "sqrtg/su", "sqrtg/suc", "sqrtg/u", "sqrtg/uc", "sqrts", "sqrts/c", "sqrts/d",
    "sqrts/m", "sqrts/su", "sqrts/suc", "sqrts/sud", "sqrts/sui", "sqrts/suic", "sqrts/suid", "sqrts/suim",
    "sqrts/sum", "sqrts/u", "sqrts/uc", "sqrts/ud", "sqrts/um", "sqrtt", "sqrtt/c", "sqrtt/d",
    "sqrtt/m", "sqrtt/su", "sqrtt/suc", "sqrtt/sud", "sqrtt/sui", "sqrtt/suic", "sqrtt/suid", "sqrtt/suim",
    "sqrtt/sum", "sqrtt/u", "sqrtt/uc", "sqrtt/ud", "sqrtt/um", "sra", "srl", "stb",
    "stf", "stg", "stl", "stl_c", "stq", "stq_c", "stq_u", "sts",
    "stt", "stw", "subf", "subf/c", "subf/s", "subf/sc", "subf/su", "subf/suc",
    "subf/u", "subf/uc", "subg", "subg/c", "subg/s", "subg/sc", "subg/su", "subg/suc",
    "subg/u", "subg/uc", "subl", "subl/v", "subq", "subq/v", "subs", "subs/c",
    "subs/d", "subs/m", "subs/su", "subs/suc", "subs/sud", "subs/sui", "subs/suic", "subs/suid",
    "subs/suim", "subs/sum", "subs/u", "subs/uc", "subs/ud", "subs/um", "subt", "subt/c",
    "subt/d", "subt/m", "subt/su", "subt/suc", "subt/sud", "subt/sui", "subt/suic", "subt/suid",
    "subt/suim", "subt/sum", "subt/u", "subt/uc", "subt/ud", "subt/um", "trapb", "umulh",
    "unop", "unpkbl", "unpkbw", "wh64", "wh64en", "wmb", "xor", "zap",
    "zapnot",
};

enum Op opcodes[] =
{
    Addf, Addf__c, Addf__s, Addf__sc, Addf__su, Addf__suc, Addf__u, Addf__uc,
    Addg, Addg__c, Addg__s, Addg__sc, Addg__su, Addg__suc, Addg__u, Addg__uc,
    Addl, Addl__v, Addq, Addq__v, Adds, Adds__c, Adds__d, Adds__m,
    Adds__su, Adds__suc, Adds__sud, Adds__sui, Adds__suic, Adds__suid, Adds__suim, Adds__sum,
    Adds__u, Adds__uc, Adds__ud, Adds__um, Addt, Addt__c, Addt__d, Addt__m,
    Addt__su, Addt__suc, Addt__sud, Addt__sui, Addt__suic, Addt__suid, Addt__suim, Addt__sum,
    Addt__u, Addt__uc, Addt__ud, Addt__um, Amask, And, Beq, Bge,
    Bgt, Bic, Bis, Blbc, Blbs, Ble, Blt, Bne,
    Br, Bsr, Call_pal, Cmoveq, Cmovge, Cmovgt, Cmovlbc, Cmovlbs,
    Cmovle, Cmovlt, Cmovne, Cmpbge, Cmpeq, Cmpgeq, Cmpgeq__s, Cmpgle,
    Cmpgle__s, Cmpglt, Cmpglt__s, Cmple, Cmplt, Cmpteq, Cmpteq__su, Cmptle,
    Cmptle__su, Cmptlt, Cmptlt__su, Cmptun, Cmptun__su, Cmpule, Cmpult, Cpys,
    Cpyse, Cpysn, Ctlz, Ctpop, Cttz, Cvtdg, Cvtdg__c, Cvtdg__s,
    Cvtdg__sc, Cvtdg__su, Cvtdg__suc, Cvtdg__u, Cvtdg__uc, Cvtgd, Cvtgd__c, Cvtgd__s,
    Cvtgd__sc, Cvtgd__su, Cvtgd__suc, Cvtgd__u, Cvtgd__uc, Cvtgf, Cvtgf__c, Cvtgf__s,
    Cvtgf__sc, Cvtgf__su, Cvtgf__suc, Cvtgf__u, Cvtgf__uc, Cvtgq, Cvtgq__c, Cvtgq__s,
    Cvtgq__sc, Cvtgq__sv, Cvtgq__svc, Cvtgq__v, Cvtgq__vc, Cvtlq, Cvtqf, Cvtqf__c,
    Cvtqg, Cvtqg__c, Cvtql, Cvtql__sv, Cvtql__v, Cvtqs, Cvtqs__c, Cvtqs__d,
    Cvtqs__m, Cvtqs__sui, Cvtqs__suic, Cvtqs__suid, Cvtqs__suim, Cvtqt, Cvtqt__c, Cvtqt__d,
    Cvtqt__m, Cvtqt__sui, Cvtqt__suic, Cvtqt__suid, Cvtqt__suim, Cvtst, Cvtst__s, Cvttq,
    Cvttq__c, Cvttq__d, Cvttq__m, Cvttq__sv, Cvttq__svc, Cvttq__svd, Cvttq__svi, Cvttq__svic,
    Cvttq__svid, Cvttq__svim, Cvttq__svm, Cvttq__v, Cvttq__vc, Cvttq__vd, Cvttq__vm, Cvtts,
    Cvtts__c, Cvtts__d, Cvtts__m, Cvtts__su, Cvtts__suc, Cvtts__sud, Cvtts__sui, Cvtts__suic,
    Cvtts__suid, Cvtts__suim, Cvtts__sum, Cvtts__u, Cvtts__uc, Cvtts__ud, Cvtts__um, Divf,
    Divf__c, Divf__s, Divf__sc, Divf__su, Divf__suc, Divf__u, Divf__uc, Divg,
    Divg__c, Divg__s, Divg__sc, Divg__su, Divg__suc, Divg__u, Divg__uc, Divs,
    Divs__c, Divs__d, Divs__m, Divs__su, Divs__suc, Divs__sud, Divs__sui, Divs__suic,
    Divs__suid, Divs__suim, Divs__sum, Divs__u, Divs__uc, Divs__ud, Divs__um, Divt,
    Divt__c, Divt__d, Divt__m, Divt__su, Divt__suc, Divt__sud, Divt__sui, Divt__suic,
    Divt__suid, Divt__suim, Divt__sum, Divt__u, Divt__uc, Divt__ud, Divt__um, Ecb,
    Eqv, Excb, Extbl, Extlh, Extll, Extqh, Extql, Extwh,
    Extwl, Fbeq, Fbge, Fbgt, Fble, Fblt, Fbne, Fcmoveq,
    Fcmovge, Fcmovgt, Fcmovle, Fcmovlt, Fcmovne, Fetch, Fetch_m, Ftois,
    Ftoit, Implver, Insbl, Inslh, Insll, Insqh, Insql, Inswh,
    Inswl, Itoff, Itofs, Itoft, Jmp, Jsr, Jsr_coroutine, Lda,
    Ldah, Ldbu, Ldf, Ldg, Ldl, Ldl_l, Ldq, Ldq_l,
    Ldq_u, Lds, Ldt, Ldwu, Maxsb8, Maxsw4, Maxub8, Maxuw4,
    Mb, Mf_fpcr, Minsb8, Minsw4, Minub8, Minuw4, Mskbl, Msklh,
    Mskll, Mskqh, Mskql, Mskwh, Mskwl, Mt_fpcr, Mulf, Mulf__c,
    Mulf__s, Mulf__sc, Mulf__su, Mulf__suc, Mulf__u, Mulf__uc, Mulg, Mulg__c,
    Mulg__s, Mulg__sc, Mulg__su, Mulg__suc, Mulg__u, Mulg__uc, Mull, Mull__v,
    Mulq, Mulq__v, Muls, Muls__c, Muls__d, Muls__m, Muls__su, Muls__suc,
    Muls__sud, Muls__sui, Muls__suic, Muls__suid, Muls__suim, Muls__sum, Muls__u, Muls__uc,
    Muls__ud, Muls__um, Mult, Mult__c, Mult__d, Mult__m, Mult__su, Mult__suc,
    Mult__sud, Mult__sui, Mult__suic, Mult__suid, Mult__suim, Mult__sum, Mult__u, Mult__uc,
    Mult__ud, Mult__um, Opc01, Opc02, Opc03, Opc04, Opc05, Opc06,
    Opc07, Ornot, Pal19, Pal1b, Pal1d, Pal1e, Pal1f, Perr,
    Pklb, Pkwb, Prefetch, Prefetch_en, Prefetch_m, Prefetch_men, Rc, Ret,
    Rpcc, Rs, S4addl, S4addq, S4subl, S4subq, S8addl, S8addq,
    S8subl, S8subq, Sextb, Sextw, Sll, Sqrtf, Sqrtf__c, Sqrtf__s,
    Sqrtf__sc, Sqrtf__su, Sqrtf__suc, Sqrtf__u, Sqrtf__uc, Sqrtg, Sqrtg__c, Sqrtg__s,
    Sqrtg__sc, Sqrtg__su, Sqrtg__suc, Sqrtg__u, Sqrtg__uc, Sqrts, Sqrts__c, Sqrts__d,
    Sqrts__m, Sqrts__su, Sqrts__suc, Sqrts__sud, Sqrts__sui, Sqrts__suic, Sqrts__suid, Sqrts__suim,
    Sqrts__sum, Sqrts__u, Sqrts__uc, Sqrts__ud, Sqrts__um, Sqrtt, Sqrtt__c, Sqrtt__d,
    Sqrtt__m, Sqrtt__su, Sqrtt__suc, Sqrtt__sud, Sqrtt__sui, Sqrtt__suic, Sqrtt__suid, Sqrtt__suim,
    Sqrtt__sum, Sqrtt__u, Sqrtt__uc, Sqrtt__ud, Sqrtt__um, Sra, Srl, Stb,
    Stf, Stg, Stl, Stl_c, Stq, Stq_c, Stq_u, Sts,
    Stt, Stw, Subf, Subf__c, Subf__s, Subf__sc, Subf__su, Subf__suc,
    Subf__u, Subf__uc, Subg, Subg__c, Subg__s, Subg__sc, Subg__su, Subg__suc,
    Subg__u, Subg__uc, Subl, Subl__v, Subq, Subq__v, Subs, Subs__c,
    Subs__d, Subs__m, Subs__su, Subs__suc, Subs__sud, Subs__sui, Subs__suic, Subs__suid,
    Subs__suim, Subs__sum, Subs__u, Subs__uc, Subs__ud, Subs__um, Subt, Subt__c,
    Subt__d, Subt__m, Subt__su, Subt__suc, Subt__sud, Subt__sui, Subt__suic, Subt__suid,
    Subt__suim, Subt__sum, Subt__u, Subt__uc, Subt__ud, Subt__um, Trapb, Umulh,
    Unop, Unpkbl, Unpkbw, Wh64, Wh64en, Wmb, Xor, Zap,
    Zapnot,
};

const int oplen = sizeof(opnames) / sizeof(const char *);

const char *op00[1], *op01[1], *op02[1], *op03[1];
const char *op04[1], *op05[1], *op06[1], *op07[1];
const char *op08[1], *op09[1], *op0a[1], *op0b[2];
const char *op0c[1], *op0d[1], *op0e[1], *op0f[1];
const char *op10[0x80], *op11[0x80], *op12[0x80], *op13[0x80];
const char *op14[0x800], *op15[0x800], *op16[0x800], *op17[0x800];
const char *op18[] = { "pal18" }, *op19[1], *op1a[4], *op1b[1];
const char *op1c[0x80], *op1d[1], *op1e[1], *op1f[1];
const char *op20[1], *op21[1], *op22[2], *op23[2];
const char *op24[1], *op25[1], *op26[1], *op27[1];
const char *op28[2], *op29[2], *op2a[1], *op2b[1];
const char *op2c[1], *op2d[1], *op2e[1], *op2f[1];
const char *op30[1], *op31[1], *op32[1], *op33[1];
const char *op34[1], *op35[1], *op36[1], *op37[1];
const char *op38[1], *op39[1], *op3a[1], *op3b[1];
const char *op3c[1], *op3d[1], *op3e[1], *op3f[1];

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

enum POp
{
    Mov, Nop, Clr,
    Sextl, Not, Negl, Negl__v, Negq, Negq__v,
    Fnop, Fclr, Fabs, Fmov, Fneg,
    Negf, Negf__s, Negg, Negg__s,
    Negs, Negs__su, Negs__sui, Negt, Negt__su, Negt__sui
};

const char *popnames[] =
{
    "mov", "nop", "clr",
    "sextl", "not", "negl", "negl/v", "negq", "negq/v",
    "fnop", "fclr", "fabs", "fmov", "fneg",
    "negf", "negf/s", "negg", "negg/s",
    "negs", "negs/su", "negs/sui", "negt", "negt/su", "negt/sui"
};

enum Op popcodes[] =
{
    UNDEF, Bis, Bis,
    Addl, Ornot, Subl, Subl__v, Subq, Subq__v,
    Cpys, Cpys, Cpys, Cpys, Cpysn,
    Subf, Subf__s, Subg, Subg__s,
    Subs, Subs__su, Subs__sui, Subt, Subt__su, Subt__sui
};

const int poplen = sizeof(popnames) / sizeof(const char *);

/* disassembler implementation */

void init_table()
{
    int i;
    for (i = 0; i < oplen; i++)
    {
        int op = (int)opcodes[i], h = op >> 16;
        if (h != 0x18) subops[h][op & 0xffff] = opnames[i];
    }
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
        default: return UNDEF;
        }
        break;
    case 0x1a: subop = (code >> 14) & 3; break;
    case 0x1c: subop = (code >> 5) & 0x7f; break;
    }
    return subops[op][subop] ? (enum Op)((op << 16) | subop) : UNDEF;
}

const char *get_mnemonic(enum Op op)
{
    return op == UNDEF ? "UNDEF" : subops[((int)op) >>16][((int)op) & 0xffff];
}

enum Op disassemble(void *f, uint64_t addr, uint32_t code)
{
    enum Op op = get_op(code);
    int opc = (int)(code >> 26);
    const char *mne = get_mnemonic(op);
    switch (formats[opc])
    {
    default:
        if (op == UNDEF)
            fprintf(f, "opc%02x %08x", opc, code & 0x03ffffff);
        else
            fprintf(f, "%s %08x", mne, code & 0x03ffffff);
        return op;
    case Bra:
        {
            int ra = (int)((code >> 21) & 31);
            int disp = code & 0x001fffff;
            char sdisp[32];
            if (disp < 0x00100000)
                snprintf(sdisp, sizeof(sdisp), "%08x", addr + disp * 4 + 4);
            else
                snprintf(sdisp, sizeof(sdisp), "%08x", addr - (0x00200000 - disp) * 4 + 4);
            if (ra == 31 && op == Br)
                fprintf(f, "br 0x%s", sdisp);
            else
                fprintf(f, "%s %s,0x%s", mne, regname[ra], sdisp);
            return op;
        }
    case Mem:
        {
            int ra = (int)((code >> 21) & 31);
            int rb = (int)((code >> 16) & 31);
            int disp = (int)(code & 0xffff);
            char args[32];
            if (disp < 10)
                snprintf(args, sizeof(args), "%d", disp);
            else if (disp < 0x8000)
                snprintf(args, sizeof(args), "0x%x", disp);
            else
            {
                int disp2 = 0x10000 - disp;
                if (disp2 < 10)
                    snprintf(args, sizeof(args), "-%d", disp2);
                else
                    snprintf(args, sizeof(args), "-0x%x", disp2);
            }
            if (rb != 31)
            {
                strncat(args, "(", sizeof(args));
                strncat(args, regname[rb], sizeof(args));
                strncat(args, ")", sizeof(args));
            }
            if (op == Ldt || op == Stt)
            {
                fprintf(f, "%s f%d,%s", mne, ra, args);
                return op;
            }
            else if (ra == 31)
            {
                if (disp == 0 && op == Ldq_u)
                {
                    fprintf(f, "unop");
                    return op;
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
                        return op;
                    }
                }
            }
            fprintf(f, "%s %s,%s", mne, regname[ra], args);
            return op;
        }
    case Mfc:
        {
            int ra = (int)((code >> 21) & 31);
            int rb = (int)((code >> 16) & 31);
            fprintf(f, "%s %s,%s", mne, regname[ra], regname[rb]);
            return op;
        }
    case Mbr:
        {
            int ra = (int)((code >> 21) & 31);
            int rb = (int)((code >> 16) & 31);
            int hint = (int)(code & 0x3fff);
            if (op == Ret && ra == Zero && rb == RA && hint == 1)
                fprintf(f, "%s", mne);
            else
                fprintf(f, "%s %s,(%s),0x%04x", mne, regname[ra], regname[rb], hint);
            return op;
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
                strncpy(arg2, regname[rb], sizeof(arg2));
            }
            else
               snprintf(arg2, sizeof(arg2), "0x%02x", (code >> 13) & 0xff);
            if (ra == 31)
            {
                const char *pse = 0;
                switch (op)
                {
                case Bis:
                    if (rb == 31 && rc == 31)
                    {
                        fprintf(f, "nop");
                        return op;
                    }
                    else if (rb == 31)
                    {
                        fprintf(f, "clr %s", regname[rc]);
                        return op;
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
                    return op;
                }
            }
            fprintf(f, "%s %s,%s,%s", mne, regname[ra], arg2, regname[rc]);
            return op;
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
                    return op;
                case 1:
                    fprintf(f, "%s f%d", pse, fc);
                    return op;
                case 2:
                    fprintf(f, "%s f%d,f%d", pse, fb, fc);
                    return op;
            }
            fprintf(f, "%s f%d,f%d,f%d", mne, fa, fb, fc);
            return op;
        }
    }
    return UNDEF;
}

uint64_t text_addr, text_size;
char text_buf[65536];

int read_text_file(void *f)
{
    int i;
    char buf[64], shstrtab[256];
    uint16_t e_machine, e_shstrndx, e_shentsize, e_shnum;
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

    e_machine = *(uint16_t *)&buf[18];
    e_shoff = *(uint64_t *)&buf[40];
    e_shentsize = *(uint16_t *)&buf[58];
    e_shnum = *(uint16_t *)&buf[60];
    e_shstrndx = *(uint16_t *)&buf[62];

    if (e_machine != 0x9026)
    {
        printf("e_machine != EM_ALPHA_EXP\n");
        return 0;
    }
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
    FILE *f = fopen(fn, "rb");
    if (f)
    {
        ret = read_text_file(f);
        fclose(f);
    }
    return ret;
}

#ifdef _MSC_VER
#define CURDIR "../Test/"
#else
#define CURDIR
#endif

const char *tests[] =
{
    "1", "2", "3", "4", "5", "6", "7t", "7d", "7a", 0
};

int main()
{
    const char **t;
    init_table();
    for (t = tests; *t; t++)
    {
        char src[32], dst[32];
        snprintf(src, sizeof(src), CURDIR"%s", *t);
        snprintf(dst, sizeof(dst), CURDIR"%s.asm", *t);
        printf("%s -> %s\n", src, dst);
        if (read_text(src))
        {
            FILE *f;
            printf("text_addr: 0x%08x\n", text_addr);
            printf("text_size: 0x%08x\n", text_size);
            f = fopen(dst, "w");
            if (f)
            {
                int j;
                for (j = 0; j < text_size; j += 4)
                {
                    enum Op op;
                    fprintf(f, "0x%08x: ", (long)(text_addr + j));
                    op = disassemble(f, text_addr + j, *(uint32_t *)&text_buf[j]);
                    fprintf(f, "\n");
                    if (op == Ret) fprintf(f, "\n");
                }
                fclose(f);
            }
        }
    }
    return 0;
}

/* libc implementation */

#ifdef __alpha
void fsnputc(int ch, FILE *f, char **sb, int *len)
{
    if (sb)
    {
        if ((*len)-- > 0) *((*sb)++) = *len ? ch : 0;
    }
    else
        fputc(ch, f);
}

int fsnprintstr(const char *s, FILE *f, char **sb, int *len)
{
    int ret = 0;
    for (; *s; s++, ret++) fsnputc(*s, f, sb, len);
    return ret;
}

int fsnprintlong(long v, int w, char pad, FILE *f, char **sb, int *len)
{
    char buf[32];
    char *p, *start;
    unsigned long uv = (unsigned long)v;
    int ret = 0;
    if (v < 0)
    {
        fsnputc('-', f, sb, len);
        ret++;
        uv = 0 - uv;
    }
    p = buf + sizeof(buf) - 1;
    *p = '\0';
    if (v == 0)
        *(--p) = '0';
    else
        for (; uv; uv /= 10)
            *(--p) = '0' + (uv % 10);
    if (w < 0) w = 0;
    if (w > sizeof(buf) - 1) w = sizeof(buf) - 1;
    start = buf + sizeof(buf) - 1 - w;
    while (p > start) *(--p) = pad;
    return ret + fsnprintstr(p, f, sb, len);
}

int fsnprinthex(unsigned long v, int w, char pad, FILE *f, char **sb, int *len)
{
    char buf[32];
    char *p, *start;
    int ret = 0;
    p = buf + sizeof(buf) - 1;
    *p = '\0';
    if (v == 0)
        *(--p) = '0';
    else
        for (; v; v >>= 4)
            *(--p) = "0123456789abcdef"[v & 15];
    if (w < 0) w = 0;
    if (w > sizeof(buf) - 1) w = sizeof(buf) - 1;
    start = buf + sizeof(buf) - 1 - w;
    while (p > start) *(--p) = pad;
    return ret + fsnprintstr(p, f, sb, len);
}

int parseint(const char **p)
{
    int ret = 0;
    for (; **p; (*p)++)
    {
        char ch = **p;
        if ('0' <= ch && ch <= '9')
        {
            ret *= 10;
            ret += ch - '0';
        }
        else
            break;
    }
    return ret;
}

int vfsnprintf(FILE *f, char **sb, int *len, const char *format, void **args)
{
    const char *p = format, *pp;
    int ret = 0, n, pad;
    for (; *p; p++)
    {
        if (*p == '%')
        {
            pp = p;
            switch (*(++p))
            {
            case '\0':
                fsnputc('%', f, sb, len);
                ret++;
                p--;
                break;
            case 'd':
                ret += fsnprintlong(*(int *)(args++), 0, '0', f, sb, len);
                break;
            case 'x':
                ret += fsnprinthex(*(int *)(args++), 0, '0', f, sb, len);
                break;
            case 'p':
                fsnprintstr("0x", f, sb, len);
                ret += fsnprinthex(*(int *)(args++), 16, '0', f, sb, len) + 2;
                break;
            case 'c':
                fsnputc(*(char *)(args++), f, sb, len);
                ret++;
                break;
            case 's':
                ret += fsnprintstr(*(const char **)(args++), f, sb, len);
                break;
            case '%':
                fsnputc('%', f, sb, len);
                ret++;
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                pad = *p == '0' ? '0' : ' ';
                n = parseint(&p);
                switch (*p)
                {
                case 'd':
                    ret += fsnprintlong(*(int *)(args++), n, pad, f, sb, len);
                    break;
                case 'x':
                    ret += fsnprinthex(*(int *)(args++), n, pad, f, sb, len);
                    break;
                default:
                    for (; pp <= p; pp++, ret++) fsnputc(*pp, f, sb, len);
                    break;
                }
                break;
            default:
                for (; pp <= p; pp++, ret++) fsnputc(*pp, f, sb, len);
                break;
            }
        }
        else
        {
            fsnputc(*p, f, sb, len);
            ret++;
        }
    }
    return ret;
}

int printf(const char * format, ...)
{
    return vfsnprintf(0, 0, 0, format, ((void **)&format) + 9);
}

int fprintf(FILE *f, const char *format, ...)
{
    return vfsnprintf(f, 0, 0, format, ((void **)&format) + 9);
}

int snprintf(char *sb, int len, const char *format, ...)
{
    return vfsnprintf(0, &sb, &len, format, ((void **)&format) + 11);
}

int strcmp(const char *a, const char *b)
{
    for (; *a || *b; a++, b++)
    {
        if (*a < *b) return -1; else if (*a > *b) return 1;
    }
    return 0;
}

char *strncpy(char *dst, const char *src, int size)
{
    for (; size > 0; size--, dst++, src++)
    {
        *dst = *src;
        if (!*src) break;
    }
    return dst;
}

char *strncat(char *dst, const char *src, int size)
{
    for (; size > 0 && *dst; size--, dst++);
    strncpy(dst, src, size);
    return dst;
}

void *memset(void *dst, int c, int len)
{
    char *d = (char *)dst;
    int i;
    for (i = 0; i < len; i++, d++) *d = (char)c;
    return dst;
}
#endif
