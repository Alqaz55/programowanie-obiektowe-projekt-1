g++ -g -fsanitize=address,undefined -fno-omit-frame-pointer -O0 -Wall -Wextra -Iheaders -lncurses Guarana.cpp Turtle.cpp Antelope.cpp Fox.cpp main.cpp World.cpp Organism.cpp Wolf.cpp Human.cpp Animal.cpp Plant.cpp Grass.cpp -o main.exe >gppLOG.log 2>&1
 2 wyjscie bledow
 ./main.exe 2 > err.log