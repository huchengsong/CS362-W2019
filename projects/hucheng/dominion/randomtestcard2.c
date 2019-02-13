/* -----------------------------------------------------------------------
 * Random test - council_room card in dominion.c
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int checkCouncilRoomCard(int p, struct gameState *post) {
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0, handpos = rand() % post->handCount[p];
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));

    cardEffect(council_room, choice1, choice2, choice3, post, handpos, &bonus);

    if (post->handCount[p] != pre.handCount[p] + 3) {
        printf("Fail: drew less than four cards\n");
        return 1;
    }
    if (post->handCount[p] + post->deckCount[p] + post->discardCount[p] + post->playedCardCount !=
        pre.handCount[p] + pre.discardCount[p] + pre.deckCount[p] + pre.playedCardCount) {
        printf("Fail: total cards in hand, deck, discard and played changed\n");
        return 1;
    }
    if (post->numBuys != pre.numBuys + 1) {
        printf("Fail: number of buys did not increase by one\n");
        return 1;
    }

    // test if other player drew a card
    // test if other player's card change correctly
    for (int i = 0; i < 4; i++) {
        if (i != p) {
            if (pre.handCount[i] != post->handCount[i] - 1) {
                printf("Fail: other player did not draw a card\n");
                return 1;
            }
            if (post->deckCount[i] + post->discardCount[i] + post->handCount[i]!= pre.deckCount[i] + pre.discardCount[i] + pre.handCount[i]) {
                printf("Fail: other player's total card number changed\n");
                return 1;
            }
        }
    }

    int gameStatusChanged = 0;
    for (int i = 0; i < 27; i++) {
        if (pre.supplyCount[i] != post->supplyCount[i]) {
            gameStatusChanged = 1;
        }
    }
    if (gameStatusChanged == 1) {
        printf("Fail: game status has changed\n");
        return 1;
    }
    printf ("ALL TESTS OK\n");
    return 0;
}

int main() {
    // random seed
    srand(time(NULL));

    printf("randomtestcard2.c -- result of random test for council_room:\n");
    //int deckCount, discardCount, handCount;
    //int k[10] = {adventurer, council_room, feast, gardens, mine,
    //remodel, smithy, village, baron, great_hall};
    struct gameState G;

    for (int n = 0; n < 2000; n++) {
        for (int i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = rand() % 256;
        }
        // initialize players
        for (int p = 0; p < 4; p++) {
            G.deckCount[p] = rand() % (MAX_DECK + 1);
            //G.discardCount[p] = MAX_DECK - G.deckCount[p];
            G.discardCount[p] = rand() % (MAX_DECK + 1);
            G.handCount[p] = rand() % (MAX_HAND + 1);
            for (int j = 0; j < G.deckCount[p]; j++) {
                G.deck[p][j] = rand() % 27;
            }
            for (int j = 0; j < G.discardCount[p]; j++) {
                G.discard[p][j] = rand() % 27;
            }
            for (int j = 0; j < G.handCount[p]; j++) {
                G.hand[p][j] = rand() % 27;
            }
        }

        // set playedCardCount
        G.playedCardCount = rand() % MAX_DECK;

        // pick current player
        int p = rand() % 4;
        G.whoseTurn = p;

        // player's handcount must larger than 0
        if (G.handCount[p] == 0) {
            G.handCount[p] = 1;
        }

        // must specify number of players
        G.numPlayers = 4;

        if (G.handCount[p] >= MAX_HAND - 4) G.handCount[p] = MAX_HAND - 4;
        checkCouncilRoomCard(p, &G);
    }
    return 0;
}
