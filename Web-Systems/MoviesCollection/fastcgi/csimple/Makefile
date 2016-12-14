all:
	g++ SimpleClass.cpp -fPIC -lfastcgi-daemon2 -shared -o libcsimple.so
	g++ HelloFastCGI.cpp -O2 -fPIC -lfastcgi-daemon2 -shared -o libHelloFastCGI.so