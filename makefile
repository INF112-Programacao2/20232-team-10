all: main

main:
	g++ ./*.cpp -o main -ltgui -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

clean:
	rm main
