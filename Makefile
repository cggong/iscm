iscm: iscm.c lex.h lex.c strhlp.h strhlp.c types.h types.c eval.h eval.c
	gcc -g -o iscm iscm.c lex.c strhlp.c types.c eval.c
