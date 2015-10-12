driver: driver.o statemodel.o hardware.o state.o accepting.o manufacturing.o processing.o shipping.o
	gcc driver.o statemodel.o hardware.o state.o accepting.o manufacturing.o processing.o shipping.o -o driver

driver.o: driver.c hardware.h statemodel.h
	gcc -c driver.c

hardware.o: hardware.c hardware.h
	gcc -c hardware.c -o hardware.o

statemodel.o: hardware.h statemodel.h statemodel.c
	gcc -c statemodel.c

state.o: state.h state.c
	gcc -c state.c -o state.o

closed.o: state.h accepting.h accepting.c
	gcc -c accepting.c

closing.o: state.h processing.h processing.c
	gcc -c processing.c

opened.o: state.h manufacturing.h manufacturing.c
	gcc -c manufacturing.c

opening.o: state.h shipping.h shipping.c
	gcc -c shipping.c

clean:
	rm *.o ; rm driver
