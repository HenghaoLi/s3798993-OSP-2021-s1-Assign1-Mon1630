PCP:
	gcc -Wall pc.c -o simulation -lpthread
CSP:
	gcc -Wall smoke.c -o simulation -lpthread

clean:
	rm simulation