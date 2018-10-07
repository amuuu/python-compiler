#include <stdio.h>
#include <conio.h>

enum Symbols {
	s_id, s_no, s_dot, s_floordiv, s_diveq, s_muleq, s_mul, s_pow,
	s_sum, su_seqsum, s_lambda, s_sub, s_eqsub, s_valeq, s_eq, s_noteq, s_not,
	s_lseq, s_lt, s_gteq, s_gt, s_lo, s_colon, s_comma, s_openpran, s_closepran, s_opencurly,
	s_closecurly, s_openbrace, s_closebrace
} Symbols;


typedef struct Token {
	int ROW, COL, BLKNO, BLKRD;
	enum Symbols type;
	char name[80];
} Token;



 struct Token Lexer(FILE *sourceFile){
 	enum Symbols LexiconType;
 	char nextChar, nextWord[80];
 	int state=0, length=0;
 	static char lastChar='\0';
 	static int rowNo=0, colNo=0;

 	while(!feof(sourceFile)){
 		if(lastChar) {
 			nextChar = lastChar;
 			lastChar = '\0';
 		}
 		else {
 			nextChar = fgetc(sourceFile);
 			nextWord[length++] = nextChar;
 			switch (state) {
 				case 0:
 					printf("helllllo\n");
 			}
 		}
 	}
 }



int main(int argc, char const *argv[])
{
	FILE *sourceFile;
	if(argc < 2) {
		printf("NO SOURCE CODE IN INPUT.\n");
		if (!getch())
			getch();
	}
//	sourceFile = fopen(argv[1], "R");
	sourceFile = fopen("testSource.py", "R");
	while(!feof(sourceFile)){
		Token token;
		token = Lexer(sourceFile);
	}
	return 0;
}


