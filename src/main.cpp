#include "Randomizer.h"
#include "Grid.h"
#include "TheGame.h"

int main(int argc, char *argv[]) {

    int wallsNum = 10000;
    int bulletNum = 1000;

    if (argc > 1) {
        if (argc >= 2)
            wallsNum = atoi(argv[1]);
        if (argc == 3)
            bulletNum = atoi(argv[2]);
    }

    std::unique_ptr<TheGame> theGame = std::make_unique<TheGame>(wallsNum, bulletNum);
    theGame->RunTheGame();

    return 0;
}
