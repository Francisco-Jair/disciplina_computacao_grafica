CPP    = g++
WINDRES= windres
RM     = rm -f
OBJS   = main.o \
         AppResource.res

LIBS   = -static -lglut32 -lglu32 -lopengl32 -lwinmm -lgdi32
CFLAGS = -DGLUT_STATIC

.PHONY: Braco_ROBOTICO.exe clean clean-after

all: Braco_ROBOTICO.exe

clean:
	$(RM) $(OBJS) Braco_ROBOTICO.exe

clean-after:
	$(RM) $(OBJS)

Braco_ROBOTICO.exe: $(OBJS)
	$(CPP) -Wall -s -O2 -o $@ $(OBJS) $(LIBS)

main.o: main.cpp
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

AppResource.res: AppResource.rc
	$(WINDRES) -i AppResource.rc -J rc -o AppResource.res -O coff

