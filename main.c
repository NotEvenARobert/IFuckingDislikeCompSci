/* COP 3502C PA1
This program is written by: ANH NHAT LE (ROBERT) */

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
        
    char *playerName;
    int totalScore;
        
} Player;
    
typedef struct {
        
    char *puzzleType;
    int puzzleNo;
    int *scores;
    int playerCount;
    Player** players;
        
} Puzzle;
    
typedef struct {
        
    int puzzleCount;
    Puzzle* puzzles;
        
} Archive;
    
Player* createPlayer(char* name) {
        
    Player* newPlayer = (Player*)malloc(sizeof(Player));
    newPlayer->playerName = (char*)malloc(strlen(name) + 1);
    strcpy(newPlayer->playerName, name);
    newPlayer->totalScore = 0;
    return newPlayer;
        
}

Player** readPlayerPool(int* playerCount) {
    
    scanf("%d", playerCount);
    Player** playerPool = (Player**)malloc(*playerCount * sizeof(Player*));
    char temporaryName[21];
    
    for(int a = 0; a < *playerCount; a++) {
        
        scanf("%s", temporaryName);
        playerPool[a] = createPlayer(temporaryName);
        
    }
    return playerPool;
}

char** readPuzzleTypes(int* countPtr) {
    
    scanf("%d", countPtr);
    
    char** puzzleTypes = (char**)malloc(*countPtr * sizeof(char*));
    char temporaryType[21];
    
    for(int b = 0; b < *countPtr; b++) {
        
        scanf("%s", temporaryType);
        puzzleTypes[b] =  (char*)malloc(strlen(temporaryType) + 1);
        strcpy(puzzleTypes[b], temporaryType);
        
    }
    return puzzleTypes;
    
}

Archive* createArchive(int puzzleCount) {
    
    Archive* newArchive = (Archive*)malloc(sizeof(Archive));
    newArchive->puzzleCount = puzzleCount;
    newArchive->puzzles = (Puzzle*)malloc(puzzleCount * sizeof(Puzzle));

    for (int i = 0; i < puzzleCount; i++) {
        newArchive->puzzles[i].puzzleType = NULL;
        newArchive->puzzles[i].puzzleNo = 0;
        newArchive->puzzles[i].scores = NULL;
        newArchive->puzzles[i].playerCount = 0;
        newArchive->puzzles[i].players = NULL;
    }    
    return newArchive;
    
}

char* getPuzzleTypePtr(char** puzzleTypes, int count, char* type) {
    
    for(int g = 0; g < count; g++) {
        
        if(strcmp(puzzleTypes[g], type) == 0) {
            
            return puzzleTypes[g];
            
        }
        
    }
    
    return NULL;
    
}

Player* getPlayerPtrByName(Player** playerPool, int playerCount, char* playerName) {
    
    for(int h = 0; h < playerCount; h++) {
        
        if(strcmp(playerPool[h]->playerName, playerName) == 0) {
            
            return playerPool[h];
            
        }
        
    }
    
    return NULL;
    
}

void printMaxTotalScorer(Player** playerPool, int playerCount) {
    
    if(playerCount == 0) {
        
        printf("No players in the system\n");
        return;
        
    }

    Player* topPlayer = playerPool[0];
    int maxScore = playerPool[0]->totalScore;

    for(int j = 1; j < playerCount; j++) {
        if(playerPool[j]->totalScore > maxScore) {
            maxScore = playerPool[j]->totalScore;
            topPlayer = playerPool[j];
        }
    }

    printf("Top player: %s with total score %d\n", topPlayer->playerName, topPlayer->totalScore);
        
}

void printBestScorer(Puzzle* puzzle) {
    
        const char *ptype = puzzle->puzzleType ? puzzle->puzzleType : "Unknown";
        
        if(puzzle->playerCount == 0) {
            printf("%s#%d No player yet for this puzzle\n", ptype, puzzle->puzzleNo);
            return;
        }
        
        int firstValid = -1;
        for (int i = 0; i < puzzle->playerCount; i++) {
            if (puzzle->players && puzzle->players[i] != NULL) {
                firstValid = i;
                break;
            }
        }
        
        if (firstValid == -1) {
            printf("%s#%d No player yet for this puzzle\n", ptype, puzzle->puzzleNo);
            return;
        }
        
        printf("%s#%d\n", ptype, puzzle->puzzleNo);
        
        int bestScore = puzzle->scores[firstValid];
        int bestPlayerIndex = firstValid;
        
        for(int k = firstValid + 1; k < puzzle->playerCount; k++) {
            if (puzzle->players[k] == NULL) continue;
            if(puzzle->scores[k] > bestScore) {
                bestScore = puzzle->scores[k];
                bestPlayerIndex = k;
            }
        }
        
        Player* topPlayer = puzzle->players[bestPlayerIndex];
        printf("%s %d\n", topPlayer->playerName, bestScore);

        
}

void freePlayerPool(Player** pool, int count) {

    for(int n = 0; n < count; n++) {
        
        free(pool[n]->playerName);
        free(pool[n]);
            
    }

    free(pool);
        
}

void freeArchive(Archive* archive) {

    for(int o = 0; o < archive->puzzleCount; o++) {

        if(archive->puzzles[o].players != NULL) {
                
            free(archive->puzzles[o].players);
                
        }
            
        if(archive->puzzles[o].scores != NULL) {
                
            free(archive->puzzles[o].scores);
                
        }
            
    }

    free(archive->puzzles);
    free(archive);
        
}


int main(void) {
    
    int playerCount = 0; 
    int puzzleTypeCount = 0;
    Player** playerPool = readPlayerPool(&playerCount);
    char** puzzleTypes = readPuzzleTypes(&puzzleTypeCount);
    
    int puzzleCount = 0;
    scanf("%d", &puzzleCount);
    Archive* archive = createArchive(puzzleCount);

    for(int e = 0; e < archive->puzzleCount; e++) {
        
        char temporaryType[21];
        int puzzleID;
        int numPlayersPuzzle;
        
        scanf("%s %d %d", temporaryType, &puzzleID, &numPlayersPuzzle);
        
        char* typePtr = getPuzzleTypePtr(puzzleTypes, puzzleTypeCount, temporaryType);
        archive->puzzles[e].puzzleType = typePtr;
        archive->puzzles[e].puzzleNo = puzzleID;
        
        if(numPlayersPuzzle > 0) {
            
            archive->puzzles[e].players = (Player**)malloc(numPlayersPuzzle * sizeof(Player*));
            archive->puzzles[e].scores = (int*)malloc(numPlayersPuzzle * sizeof(int));
            
        } else {
            
            archive->puzzles[e].players = NULL;
            archive->puzzles[e].scores = NULL;
            
        }
            
        int actualPlayersCount = 0;
        for(int f = 0; f < numPlayersPuzzle; f++) {
            
            char temporaryName[21];
            int score;
            scanf("%s %d", temporaryName, &score);
            
            Player* playerPtr = getPlayerPtrByName(playerPool, playerCount, temporaryName);
            if(playerPtr != NULL) {

                    archive->puzzles[e].players[f] = playerPtr;
                    archive->puzzles[e].scores[f] = score;        
                    playerPtr->totalScore += score;
                    actualPlayersCount++; 
                    
            } else {
                    
                    archive->puzzles[e].players[f] = NULL;
                    archive->puzzles[e].scores[f] = 0;
            }        
            
        }

        archive->puzzles[e].playerCount = actualPlayersCount;    
        
    }
    
    int numQuery;
    scanf("%d", &numQuery);
        
    for(int l = 0; l < numQuery; l++) {
        
        int queryType;
        scanf("%d", &queryType);

        if(queryType == 1) {

            printMaxTotalScorer(playerPool, playerCount);
                
        } else if(queryType == 2) {

            printf("Top scorer per puzzle:\n");
                
            for(int m = 0; m < archive->puzzleCount; m++) {

                printBestScorer(&archive->puzzles[m]);
                    
            }
                
        }
            
    }

    freePlayerPool(playerPool, playerCount);
    freeArchive(archive);    
    for(int p = 0; p < puzzleTypeCount; p++) {
            
        free(puzzleTypes[p]);
            
    }

    free(puzzleTypes);
        
    return 0;
}
