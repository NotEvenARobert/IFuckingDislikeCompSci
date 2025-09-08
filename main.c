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

int main(void) {
    
    int playerCount = 0; 
    int puzzleTypeCount = 0;
    Player** playerPool = readPlayerPool(&playerCount);
    char** puzzleTypes = readPuzzleTypes(&puzzleTypeCount);
    
    int puzzleCount = 0;
    scanf("%d", &puzzleCount);
    Archive* archive = createArchive(puzzleCount);
    printf("Archive for %d puzzles successfully created\n\n", archive->puzzleCount);
    
    printf("Loading data of %d puzzle types:\n", puzzleTypeCount);
    for(int c = 0; c < puzzleTypeCount; c++) {
        
        printf("  - %s\n", puzzleTypes[c]);
        
    }
    
    printf("Loading data of %d players:\n", playerCount);
    for(int d = 0; d < playerCount; d++) {
        
        printf("  - %s (Total Score: %d)\n", playerPool[d]->playerName, playerPool[d]->totalScore);
        
    }
    
    printf("\n----- Reading & Storing Puzzle Data -----");
    for(int e = 0; e < archive->puzzleCount; e++) {
        
        char temporaryType[21];
        int puzzleID;
        int numPlayersPuzzle;
        
        scanf("%s %d %d", temporaryType, &puzzleID, &numPlayersPuzzle);
        
        char* typePtr = getPuzzleTypePtr(puzzleTypes, puzzleTypeCount, temporaryType);
        archive->puzzles[e].puzzleType = typePtr;
        archive->puzzles[e].puzzleNo = puzzleID;
        archive->puzzles[e].playerCount = numPlayersPuzzle;
        
        if(numPlayersPuzzle > 0) {
            
            archive->puzzles[e].players = (Player**)malloc(numPlayersPuzzle * sizeof(Player*));
            archive->puzzles[e].scores = (int*)malloc(numPlayersPuzzle * sizeof(int));
            
        } else {
            
            archive->puzzles[e].players = NULL;
            archive->puzzles[e].scores = NULL;
            
        }
        
        printf("Stored Puzzle: Type = %s, ID = %d\n", archive->puzzles[e].puzzleType, archive->puzzles[e].puzzleNo);
        
        for(int f = 0; f < numPlayersPuzzle; f++) {
            
            char temporaryName[21];
            int score;
            scanf("%s %d", temporaryName, &score);
            
            Player* playerPtr = getPlayerPtrByName(playerPool, playerCount, temporaryName);
            archive->puzzles[e].players[f] = playerPtr;
            archive->puzzles[e].scores[f] = score;
            playerPtr->totalScore += score;
            
        }
        
    }
    
    printf("\n----- Player Total Scores -----\n");
    for(int i = 0; i < playerCount; i++) {
        printf("- %s has a total score of %d\n", playerPool[i]->playerName, playerPool[i]->totalScore);
    }
    
    return 0;
}
