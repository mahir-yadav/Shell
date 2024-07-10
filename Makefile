default:
	clang cat.c -o cat
	clang rm.c -o rm
	clang date.c -o date
	clang ls.c -o ls
	clang mkdir.c -o mkdir
	clang Shell.c && ./a.out
clear:
	rm -rf ./a.out history.txt cat rm date ls mkdir