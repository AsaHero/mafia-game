compile:
	gcc -o app  main.c util/socketutil.c util/json_parser.c -ljansson -luuid

run: 
	./app

compile-run:
	gcc -o app  main.c util/socketutil.c && ./app

