LAB = 1
OBJS = main.c
OUT = lab
FLAGS = -std=c99 -pthread -Wall
lab: $(OBJS)
ifeq ($(LAB),1)
	gcc $(OBJS) -o $(OUT) $(FLAGS)
endif
