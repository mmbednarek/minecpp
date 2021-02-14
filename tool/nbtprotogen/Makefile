lexer: scanner.l
	flex++ scanner.l
	sed -i '/int yyFlexLexer::yywrap() { return 1; }/d' ./lex.yy.h