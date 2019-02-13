/* -----------------------------------------------------------------------
 * Random test - smithy card in dominion.c
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

int checkSmithyCard(int p, struct gameState *post) {
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0, handpos = rand() % post->handCount[p];
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));

    cardEffect(smithy, choice1, choice2, choice3, post, handpos, &bonus);

    if (post->handCount[p] != pre.handCount[p] + 2) {
        printf("Fail: drew less than three cards\n");
        return 1;
    }
    if (pre.playedCardCount != post->playedCardCount - 1) {
        printf("Fail: Card is not discarded to played pile\n");
        return 1;
    }
    if (post->playedCards[post->playedCardCount - 1] != pre.hand[p][handpos]) {
        printf("Fail: Wrong card discarded\n");
        return 1;
    }
    if (post->handCount[p] + post->deckCount[p] + post->discardCount[p] + post->playedCardCount !=
        pre.handCount[p] + pre.discardCount[p] + pre.deckCount[p] + pre.playedCardCount) {
        printf("Fail: total cards in hand, deck, discard and played changed\n");
        return 1;
    }

    // test if other player's status has changed
    int statusOfOtherPlayerChanged = 0;
    for (int n = 0; n < 4; n++) {
        if (n != p) {
            if (pre.handCount[n] != post->handCount[n]) {
                statusOfOtherPlayerChanged = 1;
            }
            for (int i = 0; i < pre.handCount[n]; i++) {
                if(pre.hand[n][i] != post->hand[n][i]) {
                    statusOfOtherPlayerChanged = 1;
                }
            }
            if (pre.deckCount[n] != post->deckCount[n]) {
                statusOfOtherPlayerChanged = 1;
            }
            for (int i = 0; i < pre.deckCount[n]; i++) {
                if(pre.deck[n][i] != post->deck[n][i]) {
                    statusOfOtherPlayerChanged = 1;
                }
            }
            if (pre.discardCount[n] != post->discardCount[n]) {
                statusOfOtherPlayerChanged = 1;
            }
            for (int i = 0; i < pre.discardCount[n]; i++) {
                if(pre.discard[n][i] != post->discard[n][i]) {
                    statusOfOtherPlayerChanged = 1;
                }
            }
            if (statusOfOtherPlayerChanged == 1) {
                printf("Fail: the status of the other player has changed\n");
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

    printf("randomtestcard1.c -- result of random test for smithy:\n");
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

        if (G.handCount[p] >= MAX_HAND - 3) G.handCount[p] = MAX_HAND - 3;
        checkSmithyCard(p, &G);
    }
    return 0;
}
