driver: driver.o statemodel.o hardware.o state.o accepting.o manufacturing.o processing.o shipping.o
	gcc driver.o statemodel.o hardware.o state.o accepting.o manufacturing.o processing.o shipping.o -w -lpthread -o driver
	gcc server.c mySock.c -w -o server
	gcc client.c mySock.c -w -o client

driver.o: driver.c hardware.h statemodel.h
	gcc -c driver.c -w

hardware.o: hardware.c hardware.h
	gcc -c hardware.c -o hardware.o -w

statemodel.o: hardware.h statemodel.h statemodel.c
	gcc -c statemodel.c -w

state.o: state.h state.c
	gcc -c state.c -o state.o -w

closed.o: state.h accepting.h accepting.c
	gcc -c accepting.c -w

closing.o: state.h processing.h processing.c
	gcc -c processing.c -w

opened.o: state.h manufacturing.h manufacturing.c
	gcc -c manufacturing.c -w

opening.o: state.h shipping.h shipping.c
	gcc -c shipping.c -w

clean:
	rm driver
	rm server
	rm client
