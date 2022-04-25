#Musab Fiqi

#change the last dependency for each new lab
all:  tags headers lab4

#Builds the main lab4 executable from lab4.o, output.o, code.o, motion.o, functions.o, memory.o, linkedlist.o, unreliable.o
lab4: lab4.o output.o code.o motion.o memory.o functions.o linkedlist.o reliable.o
	gcc -g -o $@ $^ -lncurses -L. -linvaders -lm

#Builds the main lab4u executable from lab4.o, output.o, code.o, motion.o, functions.o, memory.o, linkedlist.o, unreliable.o
lab4u: lab4.o output.o code.o motion.o memory.o functions.o linkedlist.o unreliable.o
	gcc -g -o $@ $^ -lncurses -L. -linvaders -lm

#BUILDS PROTOTYPE EXECUTABLES
#I wrote all prototypes

#Prototype that shows inserting strings into linkedlist
p1: p1.o linkedlist.o reliable.o
	gcc -g -o $@ $^ -lncurses -L. -linvaders 

#Prototype that shows iterating over linkedlist works
p2: p2.o linkedlist.o reliable.o
	gcc -g -o $@ $^ -lncurses -L. -linvaders 

#Prototype that deletes all nodes from linkedlist
p3: p3.o linkedlist.o reliable.o
	gcc -g -o $@ $^ -lncurses -L. -linvaders  

#Prototype that shows the any function in linkedlist.h works
p4: p4.o linkedlist.o reliable.o
	gcc -g -o $@ $^ -lncurses -L. -linvaders 


#Builds lab4.zip
#zips every .c, .h, .a, .sh, and .sa files.
#also include the makefile and readme_lab4

lab4.zip:	makefile *.o *.c *.h README_LAB4 *.a *.sa *.sh *.awk reliable.o unreliable.o
	zip $@ $^
	rm -rf install
	mkdir install
	unzip lab4.zip -d install
	make -C install lab4


#this entry stays for C code labs
tags: *.c
	ctags -R .

# this entry stays for C code labs
headers: *.c tags
	headers.sh

# this entry takes care of C files depending on header files
# It has the flags for compiling the c code
# It you don't like makefiles, consider typing the following line a few
# thousand times this semester and reconsider.
# Be sure that this one doesn't get an inserted line break anywhere
%.o:%.c *.h
	gcc -ansi -pedantic -Wimplicit-function-declaration -Wreturn-type -g -c $< -o $@
