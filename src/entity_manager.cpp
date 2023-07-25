// Local headers
#include <entity.hpp>
#include <entity_manager.hpp>

#define PIECE_SIZE 4
#define STARTY 0
#define STARTX 10

#define LAST_INDEX(_Size) (_Size - 1)

typedef enum {
    I_PIECE,
    J_PIECE,
    L_PIECE,
    O_PIECE,
    S_PIECE,
    T_PIECE,
    Z_PIECE,
    UNIQUE_PIECES
} PieceType;

// Constructor/Destructor
EntityManager::EntityManager(void) {
    uint16_t size;
    char body;
    Coord *offSets = nullptr;

    random_piece(size, body, &offSets);
    this->currentEnt = make_entity(size, body, &offSets);
    random_piece(size, body, &offSets);
    this->currentEnt->nextEnt = make_entity(size, body, &offSets);
    this->currentEnt->nextEnt->nextEnt = nullptr;
}

// Instance methods
void EntityManager::random_piece(uint16_t &size, char &body, Coord **offSets) {
    size = PIECE_SIZE;
    body = '#';
    *offSets = new Coord[size];

    std::uniform_int_distribution<uint16_t> uniqueDist(0, UNIQUE_PIECES - 1);
    switch(uniqueDist(this->randGen)) {
        case I_PIECE:
            for(uint16_t i = 0; i < size; i++) (*offSets)[i] = { 1, i };
            break;
        case J_PIECE:
            (*offSets)[0] = { 0, 0 };
            for(uint16_t i = 0; i < LAST_INDEX(size); i++) (*offSets)[i + 1] = { 1, i };
            break;
        case L_PIECE:
            for(uint16_t i = 0; i < LAST_INDEX(size); i++) (*offSets)[i] = { 1, i };
            (*offSets)[LAST_INDEX(size)].y = 0;
            (*offSets)[LAST_INDEX(size)].x = LAST_INDEX(size) - 1;
            break;
        case O_PIECE:
            for(uint16_t i = 0, index = 0; i < 2; i++) {
                for(uint16_t j = 0; j < (size/2); j++) {
                    (*offSets)[index].y = i;
                    (*offSets)[index++].x = j;
                }
            }
            break;
        case S_PIECE:
            for(uint16_t i = 0, index = 0; i < 2; i++) { // TODO: Fix this piece
                for(uint16_t j = 0; j < (size/2); j++) {
                    (*offSets)[index].y = i;
                    (*offSets)[index++].x = j;
                }
            }
            break;
        case T_PIECE:
            for(uint16_t i = 0; i < size; i++) (*offSets)[i] = { 1, i }; // TODO: Fix this piece
            break;
        case Z_PIECE:
            for(uint16_t i = 0, index = 0; i < 2; i++) { // TODO: Fix this piece
                for(uint16_t j = 0; j < (size/2); j++) {
                    (*offSets)[index].y = i;
                    (*offSets)[index++].x = j;
                }
            }
            break;
    }
}

Entity *EntityManager::make_entity(uint16_t size, char body, Coord **offSets) {
    Entity *freshEnt = new Entity;
    freshEnt->size = size;
    freshEnt->body = body;
    freshEnt->pieces = *offSets;
    for(uint16_t i = 0; i < size; i++) {
        freshEnt->pieces[i].y += STARTY;
        freshEnt->pieces[i].x += STARTX;
    }
    *offSets = nullptr;
    return freshEnt;
}

// Getters
Entity *EntityManager::get_current_entity(void) {
    return this->currentEnt;
}