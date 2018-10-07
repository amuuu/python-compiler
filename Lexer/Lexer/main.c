#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>

bool isDigit(char character);
bool isLetter(char character);

enum Symbols {
	s_id, s_no, s_dot, s_floordiv, s_diveq, s_muleq, s_mul, s_pow,
	s_sum, su_seqsum, s_lambdasign, s_sub, s_eqsub, s_valeq, s_eq, s_noteq, s_notsign,
	s_lseq, s_lt, s_gteq, s_gt, s_lo, s_colon, s_comma, s_openpran, s_closepran, s_opencurly,
	s_closecurly, s_openbrace, s_closebrace,
	
	s_if, s_else, s_elif, s_while, s_for, s_in, s_not, s_from,
	s_import, s_false, s_true, s_class, s_finally, s_is, s_return, s_none,
	s_continue, s_lambda, s_try, s_def, s_nonlocal,
	s_and, s_del, s_global, s_with, s_as, s_or, s_yield, s_assert, s_pass,
	s_break, s_except, s_raise
	
} Symbols;


typedef struct Token {
	int ROW, COL, BLKNO, BLKRD;
	enum Symbols type;
	char name[80];
} Token;


enum Symbols isKeyword(char* word){
		struct keyType {
			char *keyword;
			enum Symbols type_;
		} keywordTable[] = {
			"if", s_if,
			"else", s_else,
			"elif", s_elif,
			"while", s_while,
			"for", s_for,
			"in", s_in,
			"not", s_not,
			"from", s_from,
			"import", s_import,
			"False", s_false,
			"True", s_true,
			"class", s_class,
			"finally", s_finally,
			"is", s_is,
			"return", s_return,
			"None", s_none,
			"continue", s_continue,
			"lambda", s_lambda,
			"try", s_try,
			"def", s_def,
			"from", s_from,
			"nonlocal", s_nonlocal,
			"and", s_and,
			"del", s_del,
			"global", s_global,
			"with", s_with,
			"as", s_as,
			"or", s_or,
			"yield", s_yield,
			"assert", s_assert,
			"pass", s_pass,
			"break", s_break,
			"except", s_except,
			"raise", s_raise
		};
		for (int i=0; keywordTable[i].keyword; i++){
			if(strncmp(keywordTable[i].keyword, word, sizeof(word)/sizeof(word[0]))== 0){
				return keywordTable[i].type_;
			}
		}
		return s_id;
		
};

typedef struct Token makeToken(enum Symbols type, int ROW, int COL){
		typedef struct Token token;
		token.ROW = ROW;
		token.COL = COL;
		token.type = type;

		return token;
}

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
					
					if(nextChar=='\n') { rowNo++; colNo=0; } else { colNo++; }
					
					if(nextChar==' ' || nextChar=='\n') { length=0; }
					
					else if ((nextChar<='z' && nextChar>='a') ||
							 (nextChar<='Z' && nextChar>='A'))
						state=1;
					
					else if (nextChar<='9' && nextChar>='0')
						state=2;
					
					else if (nextChar=='#')
						state=5;
					
					else if (nextChar=='"')
						state=6;
						
					else {
						printf("INVALID CHARACTER AT THE BEGINNING.\n");
						// return;
					}
						
					break;
				
				case 1:
				
					if(isLetter(nextChar) || isDigit(nextChar) || (nextChar=='_'))
						state = 1;
					else {
						lastChar = nextChar;
						nextWord[length-1]='\0';
						return makeToken(isKeyword(nextWord), rowNo, colNo);
					}
				
					break;

				default:
				
					printf("Not expected.");
					break;
 			}
 		}
 	}
 }



int main(int argc, char const *argv[])
{
	FILE *sourceFile;
	if(argc < 2) {
		printf("No source code in running arguments, using the sample python source file.\n");
		sourceFile = fopen("testSource.py", "r");
	}
	else {
		sourceFile = fopen(argv[1], "r");
	}
	while(!feof(sourceFile)){
		Token token;
		token = Lexer(sourceFile);
		printf("HEREEEEE");
	}
	return 0;
}




bool isLetter(char character) {
	if ((character>='a' && character<='z') ||
	    (character>='A' && character<='Z'))
		return true;
	else
		return false;
}

bool isDigit(char character) {
	if (character>='0' && character<='9')
		return true;
	else 
		return false;
	
}