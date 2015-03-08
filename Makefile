all:
	flex 6.l
	bison -d -y 6.y
	gcc -g lex.yy.c y.tab.c -o 6