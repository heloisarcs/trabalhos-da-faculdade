#include <stdio.h>
#include <stdlib.h>

char board[9];
int movesX[3] = {-1, -1, -1};
int movesO[3] = {-1, -1, -1};
int countX = 0, countO = 0;
int turn = 0;

// ---------------- CHECK VITÓRIA ----------------
char checkWinner() {
    int wins[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8},
        {0,3,6}, {1,4,7}, {2,5,8},
        {0,4,8}, {2,4,6}
    };

    int i, a, b, c;

    for (i = 0; i < 8; i++) {
        a = wins[i][0];
        b = wins[i][1];
        c = wins[i][2];

        if (board[a] != ' ' && board[a] == board[b] && board[b] == board[c])
            return board[a];
    }

    return 0;
}

// ---------------- IMPRIME TABULEIRO ----------------
void printBoard() {
    printf("\n %c | %c | %c\n", board[0], board[1], board[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", board[3], board[4], board[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n\n", board[6], board[7], board[8]);
}

// ---------------- MOVE DO JOGADOR ----------------
void addMove(int pos, char player, int moves[], int *count) {
    int i;

    if (*count < 3) {
        moves[*count] = pos;
        (*count)++;
    } else {
        for (i = 0; i < 2; i++)
            moves[i] = moves[i + 1];

        moves[2] = pos;
    }

    for (i = 0; i < 9; i++)
        if (board[i] == player)
            board[i] = ' ';

    for (i = 0; i < *count; i++)
        if (moves[i] != -1)
            board[moves[i]] = player;
}

// ---------------- PROGRAMA PRINCIPAL ----------------
int main() {
    int i, pos;

    for (i = 0; i < 9; i++)
        board[i] = ' ';

    while (1) {
        printBoard();

        char player = (turn == 0) ? 'X' : 'O';
        int *moves = (turn == 0) ? movesX : movesO;
        int *count = (turn == 0) ? &countX : &countO;

        printf("Vez do jogador %c. Escolha uma posicao (1 a 9): ", player);
        scanf("%d", &pos);
        pos--;

        if (pos < 0 || pos > 8) {
            printf("Posicao invalida!\n");
            continue;
        }

        addMove(pos, player, moves, count);

        if (checkWinner()) {
            printBoard();
            printf("Jogador %c venceu!\n", checkWinner());
            break;
        }

        turn = 1 - turn;
    }

    return 0;
}

