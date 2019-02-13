CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o adventureCardEffect.o smithyCardEffect.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe randomtestadventurer randomtestcard1 randomtestcard2

adventureCardEffect.o: adventureCardEffect.h adventureCardEffect.c
	gcc -c adventureCardEffect.c -g  $(CFLAGS)

smithyCardEffect.o: smithyCardEffect.h smithyCardEffect.c
	gcc -c smithyCardEffect.c -g  $(CFLAGS)
    
councilRoomCardEffect.o: councilRoomCardEffect.h councilRoomCardEffect.c
	gcc -c councilRoomCardEffect.c -g  $(CFLAGS)

randomtestadventurer: randomtestadventurer.c  councilRoomCardEffect.o adventureCardEffect.o smithyCardEffect.o dominion.o rngs.o
	gcc -o randomtestadventurer -g  councilRoomCardEffect.o randomtestadventurer.c adventureCardEffect.o smithyCardEffect.o dominion.o rngs.o $(CFLAGS)
	./randomtestadventurer
	gcov -b adventureCardEffect.c > randomtestadventurer.out

randomtestcard1: randomtestcard1.c councilRoomCardEffect.o adventureCardEffect.o smithyCardEffect.o dominion.o rngs.o
	gcc -o randomtestcard1 -g  councilRoomCardEffect.o randomtestcard1.c smithyCardEffect.o adventureCardEffect.o dominion.o rngs.o $(CFLAGS)
	./randomtestcard1
	gcov -b smithyCardEffect.c > randomtestcard1.out

randomtestcard2: randomtestcard2.c councilRoomCardEffect.o adventureCardEffect.o smithyCardEffect.o dominion.o rngs.o
	gcc -o randomtestcard2 -g  randomtestcard2.c councilRoomCardEffect.o smithyCardEffect.o adventureCardEffect.o dominion.o rngs.o $(CFLAGS)
	./randomtestcard2
	gcov -b councilRoomCardEffect.c > randomtestcard2.out

unittestadventurer: unittestadventurer.c councilRoomCardEffect.o adventureCardEffect.o smithyCardEffect.o dominion.o rngs.o
	gcc -o unittestadventurer -g  unittestadventurer.c councilRoomCardEffect.o smithyCardEffect.o adventureCardEffect.o dominion.o rngs.o $(CFLAGS)
	./unittestadventurer
	gcov -b adventureCardEffect.c > unittestadventurer.out

unittest1: unittest1.c councilRoomCardEffect.o adventureCardEffect.o smithyCardEffect.o dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c councilRoomCardEffect.o smithyCardEffect.o adventureCardEffect.o dominion.o rngs.o $(CFLAGS)
	./unittest1
	gcov -b smithyCardEffect.c > unittest1.out

unittest2: unittest2.c councilRoomCardEffect.o adventureCardEffect.o smithyCardEffect.o dominion.o rngs.o
	gcc -o unittest2 -g  unittest2.c councilRoomCardEffect.o smithyCardEffect.o adventureCardEffect.o dominion.o rngs.o $(CFLAGS)
	./unittest2
	gcov -b councilRoomCardEffect.c > unittest2.out