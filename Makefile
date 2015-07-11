iscm: iscm.c lex.h lex.c strhlp.h strhlp.c types.h types.c
	gcc -g -o iscm iscm.c lex.c strhlp.c types.c
