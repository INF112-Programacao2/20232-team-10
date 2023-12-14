all: main

main:
	g++ src/* -o main -ltgui -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

clean:
	rm main
