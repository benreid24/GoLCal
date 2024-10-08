#include <gol/gol.h>

#include <string.h>
#include <time.h>

Cell* golCells     = NULL;
Cell* golPrevCells = NULL;
int golWidth       = 0;
int golHeight      = 0;

const Cell golDead              = {0, 0.f, 0.f, 0.f};
const Cell golSpeciesSources[3] = {{1, 66.f / 255.f, 135.f / 255.f, 245.f / 255.f},
                                   {1, 41.f / 255.f, 230.f / 255.f, 66.f / 255.f},
                                   {1, 214.f / 255.f, 36.f / 255.f, 36.f / 255.f}};

Cell* golFetchNext(int x, int y) {
    x = x >= 0 ? x % golWidth : golWidth + x;
    y = y >= 0 ? y % golHeight : golHeight + y;
    return &golCells[y * golWidth + x];
}

Cell* golFetchCur(int x, int y) {
    x = x >= 0 ? x % golWidth : golWidth + x;
    y = y >= 0 ? y % golHeight : golHeight + y;
    return &golPrevCells[y * golWidth + x];
}

void renderCharacter(unsigned int x, unsigned int y, char c, Cell src) {
    switch (c) {
    case '0':
        *golFetchCur(x, y)         = src;
        *golFetchCur(x + 1, y)     = src;
        *golFetchCur(x + 2, y)     = src;
        *golFetchCur(x, y + 1)     = src;
        *golFetchCur(x + 2, y + 1) = src;
        *golFetchCur(x, y + 2)     = src;
        *golFetchCur(x + 2, y + 2) = src;
        *golFetchCur(x, y + 3)     = src;
        *golFetchCur(x + 2, y + 3) = src;
        *golFetchCur(x, y + 4)     = src;
        *golFetchCur(x + 1, y + 4) = src;
        *golFetchCur(x + 2, y + 4) = src;
        break;
    case '1':
        *golFetchCur(x + 1, y)     = src;
        *golFetchCur(x + 1, y + 1) = src;
        *golFetchCur(x + 1, y + 2) = src;
        *golFetchCur(x + 1, y + 3) = src;
        *golFetchCur(x + 1, y + 4) = src;
        break;
    case '2':
        *golFetchCur(x, y)         = src;
        *golFetchCur(x + 1, y)     = src;
        *golFetchCur(x + 2, y)     = src;
        *golFetchCur(x + 2, y + 1) = src;
        *golFetchCur(x, y + 2)     = src;
        *golFetchCur(x + 1, y + 2) = src;
        *golFetchCur(x + 2, y + 2) = src;
        *golFetchCur(x, y + 3)     = src;
        *golFetchCur(x, y + 4)     = src;
        *golFetchCur(x + 1, y + 4) = src;
        *golFetchCur(x + 2, y + 4) = src;
        break;
    case '3':
        *golFetchCur(x, y)         = src;
        *golFetchCur(x + 1, y)     = src;
        *golFetchCur(x + 2, y)     = src;
        *golFetchCur(x + 2, y + 1) = src;
        *golFetchCur(x + 1, y + 2) = src;
        *golFetchCur(x + 2, y + 2) = src;
        *golFetchCur(x + 2, y + 3) = src;
        *golFetchCur(x, y + 4)     = src;
        *golFetchCur(x + 1, y + 4) = src;
        *golFetchCur(x + 2, y + 4) = src;
        break;
    case '4':
        *golFetchCur(x, y)         = src;
        *golFetchCur(x + 2, y)     = src;
        *golFetchCur(x, y + 1)     = src;
        *golFetchCur(x + 2, y + 1) = src;
        *golFetchCur(x, y + 2)     = src;
        *golFetchCur(x + 1, y + 2) = src;
        *golFetchCur(x + 2, y + 2) = src;
        *golFetchCur(x + 2, y + 3) = src;
        *golFetchCur(x + 2, y + 4) = src;
        break;
    case '5':
        *golFetchCur(x, y)         = src;
        *golFetchCur(x + 1, y)     = src;
        *golFetchCur(x + 2, y)     = src;
        *golFetchCur(x, y + 1)     = src;
        *golFetchCur(x, y + 2)     = src;
        *golFetchCur(x + 1, y + 2) = src;
        *golFetchCur(x + 2, y + 2) = src;
        *golFetchCur(x + 2, y + 3) = src;
        *golFetchCur(x, y + 4)     = src;
        *golFetchCur(x + 1, y + 4) = src;
        *golFetchCur(x + 2, y + 4) = src;
        break;
    case '6':
        *golFetchCur(x, y)         = src;
        *golFetchCur(x + 1, y)     = src;
        *golFetchCur(x + 2, y)     = src;
        *golFetchCur(x, y + 1)     = src;
        *golFetchCur(x, y + 2)     = src;
        *golFetchCur(x + 1, y + 2) = src;
        *golFetchCur(x + 2, y + 2) = src;
        *golFetchCur(x, y + 3)     = src;
        *golFetchCur(x + 2, y + 3) = src;
        *golFetchCur(x, y + 4)     = src;
        *golFetchCur(x + 1, y + 4) = src;
        *golFetchCur(x + 2, y + 4) = src;
        break;
    case '7':
        *golFetchCur(x, y)         = src;
        *golFetchCur(x + 1, y)     = src;
        *golFetchCur(x + 2, y)     = src;
        *golFetchCur(x + 2, y + 1) = src;
        *golFetchCur(x + 2, y + 2) = src;
        *golFetchCur(x + 2, y + 3) = src;
        *golFetchCur(x + 2, y + 4) = src;
        break;
    case '8':
        *golFetchCur(x, y)         = src;
        *golFetchCur(x + 1, y)     = src;
        *golFetchCur(x + 2, y)     = src;
        *golFetchCur(x, y + 1)     = src;
        *golFetchCur(x + 2, y + 1) = src;
        *golFetchCur(x, y + 2)     = src;
        *golFetchCur(x + 1, y + 2) = src;
        *golFetchCur(x + 2, y + 2) = src;
        *golFetchCur(x, y + 3)     = src;
        *golFetchCur(x + 2, y + 3) = src;
        *golFetchCur(x, y + 4)     = src;
        *golFetchCur(x + 1, y + 4) = src;
        *golFetchCur(x + 2, y + 4) = src;
        break;
    case '9':
        *golFetchCur(x, y)         = src;
        *golFetchCur(x + 1, y)     = src;
        *golFetchCur(x + 2, y)     = src;
        *golFetchCur(x, y + 1)     = src;
        *golFetchCur(x + 2, y + 1) = src;
        *golFetchCur(x, y + 2)     = src;
        *golFetchCur(x + 1, y + 2) = src;
        *golFetchCur(x + 2, y + 2) = src;
        *golFetchCur(x + 2, y + 3) = src;
        *golFetchCur(x + 2, y + 4) = src;
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
        renderCharacter(x_char_pos, y_char_pos, message[i], golSpeciesSources[i % 3]);
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

struct CellGroup {
    Cell info;
    unsigned int size;
};

typedef struct CellGroup CellGroup;

unsigned int addCellToGroups(CellGroup* groups, unsigned int groupCount, Cell* cell) {
    // find group of same species and add if found
    for (unsigned int i = 0; i < groupCount; ++i) {
        if (groups[i].info.species == cell->species) {
            // compute new average color, increment size, and return
            const float c    = (float)groups[i].size;
            const float nc   = c + 1.f;
            groups[i].info.r = (groups[i].info.r * c + cell->r) / nc;
            groups[i].info.g = (groups[i].info.g * c + cell->g) / nc;
            groups[i].info.b = (groups[i].info.b * c + cell->b) / nc;
            groups[i].size += 1;
            return groupCount;
        }
    }

    // no matching group, create it
    groups[groupCount].info = *cell;
    groups[groupCount].size = 1;
    return groupCount + 1;
}

unsigned int countNeighbors(int x, int y, CellGroup* neighborGroups) {
    unsigned nc = 0;
    for (int x_dir = -1; x_dir < 2; ++x_dir) {
        for (int y_dir = -1; y_dir < 2; ++y_dir) {
            if (!(x_dir == 0 && y_dir == 0)) {
                Cell* cell = golFetchCur(x + x_dir, y + y_dir);
                if (cell->species != 0) { nc = addCellToGroups(neighborGroups, nc, cell); }
            }
        }
    }
    return nc;
}

void golTick() {
    CellGroup neighborGroups[8];
    unsigned int neighborCount = 0;

    Cell* spawners[2];
    unsigned int spawnerCount = 0;

    for (int x = 0; x < golWidth; ++x) {
        for (int y = 0; y < golHeight; ++y) {
            neighborCount = countNeighbors(x, y, &neighborGroups);
            Cell* cell    = golFetchCur(x, y);

            if (cell->species != 0) {
                unsigned int sameNeighbors = 0;
                for (unsigned int i = 0; i < neighborCount; ++i) {
                    if (neighborGroups[i].info.species == cell->species) {
                        sameNeighbors = neighborGroups[i].size;
                        break;
                    }
                }
                if (sameNeighbors == 2 || sameNeighbors == 3) { *golFetchNext(x, y) = *cell; }
                else { *golFetchNext(x, y) = golDead; }
            }
            else {
                spawnerCount = 0;
                for (unsigned int i = 0; i < neighborCount; ++i) {
                    if (neighborGroups[i].size == 3) {
                        spawners[spawnerCount] = &neighborGroups[i].info;
                        ++spawnerCount;
                    }
                }
                if (spawnerCount > 0) { *golFetchNext(x, y) = *spawners[rand() % spawnerCount]; }
                else { *golFetchNext(x, y) = golDead; }
            }
        }
    }
    // swap cells
    Cell* tmp    = golCells;
    golCells     = golPrevCells;
    golPrevCells = tmp;
}