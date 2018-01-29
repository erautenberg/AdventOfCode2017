CC			=	gcc

CFLAGS		=	

OBJFILES	=	adventofcode.o 		\
				days/day01.o 		\
				days/day02.o 		\
				days/day03.o 		\
				days/day04.o 		\
				days/day05.o 		\

TARGET		=	advent

RM 			=	rm -f


default: all

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

clean:
	$(RM) $(OBJFILES) $(TARGET) *~

