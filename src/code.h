// hello
#ifndef CODE_INCLUDE
#define CODE_INCLUDE

#define JUMP_BITS 3
#define DEST_BITS 3
#define COMP_BITS 6

typedef unsigned _BitInt(JUMP_BITS) int3;
typedef unsigned _BitInt(COMP_BITS) int6;

int uses_memory(char *m);
int3 dest(char *mne);
int3 jump(char *mne);
int6 comp(char *mne);

#endif
