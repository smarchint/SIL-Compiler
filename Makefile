all:
	flex 62.l
	bison -d -y 62.y
	gcc -g lex.yy.c y.tab.c -o 6