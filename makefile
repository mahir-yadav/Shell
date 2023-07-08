default:
	gcc cat.c -o cat
	gcc rm.c -o rm
	gcc date.c -o date
	gcc ls.c -o ls
	gcc mkdir.c -o mkdir
	gcc shell.c && ./a.out
clear:
	rm -rf ./a.out cat rm date ls mkdir