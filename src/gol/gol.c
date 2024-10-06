#include <gol/gol.h>

#include <string.h>
#include <time.h>

Cell* golCells         = NULL;
Cell* golPrevCells     = NULL;
unsigned int golWidth  = 0;
unsigned int golHeight = 0;

Cell* golFetch(unsigned int x, unsigned int y) { return &golCells[y * golWidth + x]; }

Cell* golFetchPrev(unsigned int x, unsigned int y) { return &golPrevCells[y * golWidth + x]; }

void renderCharacter(unsigned int x, unsigned int y, char c, unsigned int species) {
    switch (c) {
    case '0':
        *golFetchPrev(x, y)         = species;
        *golFetchPrev(x + 1, y)     = species;
        *golFetchPrev(x + 2, y)     = species;
        *golFetchPrev(x, y + 1)     = species;
        *golFetchPrev(x + 2, y + 1) = species;
        *golFetchPrev(x, y + 2)     = species;
        *golFetchPrev(x + 2, y + 2) = species;
        *golFetchPrev(x, y + 3)     = species;
        *golFetchPrev(x + 2, y + 3) = species;
        *golFetchPrev(x, y + 4)     = species;
        *golFetchPrev(x + 1, y + 4) = species;
        *golFetchPrev(x + 2, y + 4) = species;
        break;
    case '1':
        *golFetchPrev(x + 1, y)     = species;
        *golFetchPrev(x + 1, y + 1) = species;
        *golFetchPrev(x + 1, y + 2) = species;
        *golFetchPrev(x + 1, y + 3) = species;
        *golFetchPrev(x + 1, y + 4) = species;
        break;
    case '2':
        *golFetchPrev(x, y)         = species;
        *golFetchPrev(x + 1, y)     = species;
        *golFetchPrev(x + 2, y)     = species;
        *golFetchPrev(x + 2, y + 1) = species;
        *golFetchPrev(x, y + 2)     = species;
        *golFetchPrev(x + 1, y + 2) = species;
        *golFetchPrev(x + 2, y + 2) = species;
        *golFetchPrev(x, y + 3)     = species;
        *golFetchPrev(x, y + 4)     = species;
        *golFetchPrev(x + 1, y + 4) = species;
        *golFetchPrev(x + 2, y + 4) = species;
        break;
    case '3':
        *golFetchPrev(x, y)         = species;
        *golFetchPrev(x + 1, y)     = species;
        *golFetchPrev(x + 2, y)     = species;
        *golFetchPrev(x + 2, y + 1) = species;
        *golFetchPrev(x + 1, y + 2) = species;
        *golFetchPrev(x + 2, y + 2) = species;
        *golFetchPrev(x + 2, y + 3) = species;
        *golFetchPrev(x, y + 4)     = species;
        *golFetchPrev(x + 1, y + 4) = species;
        *golFetchPrev(x + 2, y + 4) = species;
        break;
    case '4':
        *golFetchPrev(x, y)         = species;
        *golFetchPrev(x + 2, y)     = species;
        *golFetchPrev(x, y + 1)     = species;
        *golFetchPrev(x + 2, y + 1) = species;
        *golFetchPrev(x, y + 2)     = species;
        *golFetchPrev(x + 1, y + 2) = species;
        *golFetchPrev(x + 2, y + 2) = species;
        *golFetchPrev(x + 2, y + 3) = species;
        *golFetchPrev(x + 2, y + 4) = species;
        break;
    case '5':
        *golFetchPrev(x, y)         = species;
        *golFetchPrev(x + 1, y)     = species;
        *golFetchPrev(x + 2, y)     = species;
        *golFetchPrev(x, y + 1)     = species;
        *golFetchPrev(x, y + 2)     = species;
        *golFetchPrev(x + 1, y + 2) = species;
        *golFetchPrev(x + 2, y + 2) = species;
        *golFetchPrev(x + 2, y + 3) = species;
        *golFetchPrev(x, y + 4)     = species;
        *golFetchPrev(x + 1, y + 4) = species;
        *golFetchPrev(x + 2, y + 4) = species;
        break;
    case '6':
        *golFetchPrev(x, y)         = species;
        *golFetchPrev(x + 1, y)     = species;
        *golFetchPrev(x + 2, y)     = species;
        *golFetchPrev(x, y + 1)     = species;
        *golFetchPrev(x, y + 2)     = species;
        *golFetchPrev(x + 1, y + 2) = species;
        *golFetchPrev(x + 2, y + 2) = species;
        *golFetchPrev(x, y + 3)     = species;
        *golFetchPrev(x + 2, y + 3) = species;
        *golFetchPrev(x, y + 4)     = species;
        *golFetchPrev(x + 1, y + 4) = species;
        *golFetchPrev(x + 2, y + 4) = species;
        break;
    case '7':
        *golFetchPrev(x, y)         = species;
        *golFetchPrev(x + 1, y)     = species;
        *golFetchPrev(x + 2, y)     = species;
        *golFetchPrev(x + 2, y + 1) = species;
        *golFetchPrev(x + 2, y + 2) = species;
        *golFetchPrev(x + 2, y + 3) = species;
        *golFetchPrev(x + 2, y + 4) = species;
        break;
    case '8':
        *golFetchPrev(x, y)         = species;
        *golFetchPrev(x + 1, y)     = species;
        *golFetchPrev(x + 2, y)     = species;
        *golFetchPrev(x, y + 1)     = species;
        *golFetchPrev(x + 2, y + 1) = species;
        *golFetchPrev(x, y + 2)     = species;
        *golFetchPrev(x + 1, y + 2) = species;
        *golFetchPrev(x + 2, y + 2) = species;
        *golFetchPrev(x, y + 3)     = species;
        *golFetchPrev(x + 2, y + 3) = species;
        *golFetchPrev(x, y + 4)     = species;
        *golFetchPrev(x + 1, y + 4) = species;
        *golFetchPrev(x + 2, y + 4) = species;
        break;
    case '9':
        *golFetchPrev(x, y)         = species;
        *golFetchPrev(x + 1, y)     = species;
        *golFetchPrev(x + 2, y)     = species;
        *golFetchPrev(x, y + 1)     = species;
        *golFetchPrev(x + 2, y + 1) = species;
        *golFetchPrev(x, y + 2)     = species;
        *golFetchPrev(x + 1, y + 2) = species;
        *golFetchPrev(x + 2, y + 2) = species;
        *golFetchPrev(x + 2, y + 3) = species;
        *golFetchPrev(x + 2, y + 4) = species;
        break;
    }
}

void golRenderString(const char* message) {
    // TODO - Compute offsets to center the message
    unsigned int x_offset = (golWidth - 15) / 2;
    unsigned int y_offset = (golHeight - 13) / 2;

    for (unsigned int i = 0; i < strlen(message); ++i) {
        int x_char_pos = x_offset + 4 * (i % 4);
        int y_char_pos = y_offset + 7 * (i / 4);
        renderCharacter(x_char_pos, y_char_pos, message[i], (i % 3) + 1);
    }
}

void golInit(unsigned int width, unsigned int height) {
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
}

unsigned int countNeighbors(unsigned int x, unsigned int y, unsigned int species) {
    unsigned nc = 0;
    for (int x_dir = -1; x_dir < 2; ++x_dir) {
        if ((x + x_dir) >= 0 && x + x_dir < golWidth) {
            for (int y_dir = -1; y_dir < 2; ++y_dir) {
                if ((y + y_dir) >= 0 && y + y_dir < golHeight) {
                    if (!(x_dir == 0 && y_dir == 0)) {
                        if (*golFetchPrev(x + x_dir, y + y_dir) == species) { ++nc; }
                    }
                }
            }
        }
    }
    return nc;
}

void golTick() {
    for (unsigned int x = 0; x < golWidth; ++x) {
        for (unsigned int y = 0; y < golHeight; ++y) {
            if (*golFetchPrev(x, y) != 0) {
                const unsigned int species = *golFetchPrev(x, y);
                const unsigned int nc      = countNeighbors(x, y, species);
                if (nc == 2 || nc == 3) { *golFetch(x, y) = species; }
                else { *golFetch(x, y) = 0; }
            }
            else {
                unsigned int sc[3] = {
                    countNeighbors(x, y, 1), countNeighbors(x, y, 2), countNeighbors(x, y, 3)};
                int alive[3]    = {0, 0, 0};
                unsigned int ac = 0;
                for (unsigned int i = 0; i < 3; ++i) {
                    if (sc[i] == 3) {
                        alive[ac] = i + 1;
                        ++ac;
                    }
                }
                if (ac > 0) { *golFetch(x, y) = alive[rand() % ac]; }
                else { *golFetch(x, y) = 0; }
            }
        }
    }
    // swap cells
    Cell* tmp    = golCells;
    golCells     = golPrevCells;
    golPrevCells = tmp;
}