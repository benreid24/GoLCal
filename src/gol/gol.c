#include <gol/gol.h>

#include <string.h>
#include <time.h>

Cell* golCells         = NULL;
Cell* golPrevCells     = NULL;
unsigned int golWidth  = 0;
unsigned int golHeight = 0;

Cell* golFetch(unsigned int x, unsigned int y) { return &golCells[y * golWidth + x]; }

Cell* golFetchPrev(unsigned int x, unsigned int y) { return &golPrevCells[y * golWidth + x]; }

void renderCharacter(unsigned int x, unsigned int y, char c, Cell* dest) {
    switch (c) {
    case '0':

        break;
    case '1':

        break;
    case '2':

        break;
    case '3':

        break;
    case '4':

        break;
    case '5':

        break;
    case '6':

        break;
    case '7':

        break;
    case '8':

        break;
    case '9':

        break;
    }
}

void golInit(unsigned int width, unsigned int height, char* message) {
    srand(time(NULL));
    if (golCells) {
        free(golCells);
        free(golPrevCells);
    }

    const unsigned int len = width * height * sizeof(Cell);
    golCells               = malloc(len);
    golPrevCells           = malloc(len);
    memset(golCells, 0, len);
    memset(golPrevCells, 0, len);
    golWidth  = width;
    golHeight = height;

    // TODO - Compute offsets to center the message
    unsigned int x_offset = 0;
    unsigned int y_offset = 0;

    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) { *golFetchPrev(x, y) = rand() % 2; }
    }
}

void golTick() {
    // TODO - run one iteration step of GoL on golCells
    for (unsigned int x = 0; x < golWidth; ++x) {
        for (unsigned int y = 0; y < golHeight; ++y) {
            int active_neighbors = 0;
            if (y + 1 < golHeight) { active_neighbors += *golFetchPrev(x, y + 1); }
            if (y > 0) { active_neighbors += *golFetchPrev(x, y - 1); }
            if (x + 1 < golWidth) { active_neighbors += *golFetchPrev(x + 1, y); }
            if (x > 0) { active_neighbors += *golFetchPrev(x - 1, y); }
            if (active_neighbors == 2 || active_neighbors == 3) { *golFetch(x, y) = 1; }
            else { *golFetch(x, y) = 0; }
        }
    }
    // swap cells
    Cell* tmp    = golCells;
    golCells     = golPrevCells;
    golPrevCells = tmp;
}