edit : src/main.o src/cenario.o src/figuras.o \
	src/iluminacao.o src/logica.o src/texturas.o
	cc -o bin/medieval src/main.o src/cenario.o \
		src/figuras.o src/iluminacao.o src/logica.o src/texturas.o \
		-lGL -lGLU -lglut -lm -Wall

main.o : main.c macros.h
	 cc -c main.c
cenario.o : cenario.c cenario.h macros.h texturas.h
	cc -c cenario.c
figuras.o : figuras.c figuras.h macros.h texturas.h logica.h
	cc -c figuras.c
iluminacao.o : iluminacao.c iluminacao.h
	cc -c iluminacao.c
logica.o : logica.c logica.h macros.h
	cc -c logica.c
texturas.o : texturas.c texturas.h
	cc -c texturas.c
clean : 
	rm bin/medieval src/*.o
