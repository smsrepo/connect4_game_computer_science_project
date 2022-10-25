#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/*
* CONNECT 4 GAME - C PROGRAMMING CODE
* 
* SYED MUHAMMAD SAIM - GROUP A10
* ELECTRONIC ENGINEERING - HAMM-LIPPSTADT UNIVERSITY OF APPLIED SCIENCES
* COMPUTER SCIENCE 2 - PROJECT
*/

#define C 7                                                             // Marcro to specify coloumns
#define R 6                                                             // Marcro to specify rows

typedef struct node {
    struct node** fills;
    int n_fills;
    int board[R][C];
    double value;
    int depth;
}Node;

void Initial_Display();                                                 // Shows a display to tell user how to proceed
void Board_Display(Node* access);                                        // Displays board without any position
void Initialize_Board(Node* access);                                    // Set up Board
void Print_Board(int board[R][C]);                                      // Displays Board
int Validate_UserInput();
void Apply_Shot(int board[R][C], int position, int player);             // Places User's Mark
int Board_Full(int board[R][C]);                                        // Checks whether the board is full or not
int Verify_Shot(int board[R][C], int position);                         // Checks a valid shot
void Copy_Board(int destination[R][C], int origin[R][C]);               // 
int Determine_Fills(int board[R][C]);                                   // Identifies places that has been filled
int verify(int board[R][C], int player);
int Shot_Real(int board[R][C], int shotFalse);
int Board_Won(int board[R][C]);                                         // 
int Board_Lost(int board[R][C]);
int Connect_Vertical3(int board[R][C], int i, int j, int player);
int Connect_Horitzontal3(int board[R][C], int i, int j, int player);
int Connect_Diagonals3(int board[R][C], int i, int j, int player);
int Connect_Vertical2(int board[R][C], int i, int j, int player);
int Connect_Horitzontal2(int board[R][C], int i, int j, int player);
int Connect_Diagonals2(int board[R][C], int i, int j, int player);
int Connection2(int board[R][C], int player);
int Connection3(int board[R][C], int player);
double Heuristic(int board[R][C]);
Node* Create_Node(Node* pair, int numFill, int prof);
void Create1Level(Node* pair, int prof);
void Create_Map(Node* access, int prof);
void Mini_Max(Node* pair);
double ferMini_Max(Node* pair);
void Display_Winner(int end);                                            // Display the Winner 

int main() {

    int position, option = 0, end = 0;
    bool input = false;
    Node* access = (Node*)malloc(sizeof(Node));                         // As name suggests, access is an object that have an access inside struct node
    Initial_Display();

    start:
    switch (option) {

    case 1:
        Board_Display(access);
        while (end == 0) {
            position = Validate_UserInput();
            system("cls");
            Apply_Shot(access->board, position, 2);
            Print_Board(access->board);
            if (verify(access->board, 2) != 0) {
                end = 2;
                break;
            }
            if (Board_Full(access->board) == 1) {
                end = 4;
                break;
            }
            Create_Map(access, 0);
            Mini_Max(access);
            Apply_Shot(access->board, ferMini_Max(access), 1);
            system("cls");
            Print_Board(access->board);
            end = verify(access->board, 1);
        }
        Display_Winner(end);
        break;

    case 2:
        Board_Display(access);
        while (end == 0) {
            position = Validate_UserInput();
            system("cls");
            Apply_Shot(access->board, position, 2);
            Print_Board(access->board);
            if (verify(access->board, 2) != 0) {
                end = 2;
                break;
            }
            if (Board_Full(access->board) == 1) {
                end = 4;
                break;
            }
            Apply_Shot(access->board, 1 + rand() % C, 1);
            system("cls");
            Print_Board(access->board);
            end = verify(access->board, 1);
        }
        Display_Winner(end);
        break;

    case 3:
        Board_Display(access);
        while (end == 0) {
            position = Validate_UserInput();
            system("cls");
            Apply_Shot(access->board, position, 2);
            system("cls");
            Print_Board(access->board);
            if (verify(access->board, 2) != 0) {
                end = 2;
                break;
            }
            if (Board_Full(access->board) == 1) {
                end = 4;
                break;
            }

            jump1:
            printf("\nWhich coloumn would you like to mark 2nd Player X? ");
            scanf("%i", &position);
            if (position > 1 && position <= 7 && (sizeof(position) / (sizeof(int))) == 1) {
                goto jump2;
            }
            else {
                printf("Please enter a valid coloumn nunmber between 1 to 7\n");
                goto jump1;
            }
            jump2:
            
            system("cls");
            Apply_Shot(access->board, position, 1);
            system("cls");
            Print_Board(access->board);
            end = verify(access->board, 1);
        }
        if (end == 1) {
            printf("\n\nHA Won Player X\n");
        }
        else if (end == 4) {
            printf("Board Full! DRAW\n");
        }
        else {
            printf("\n\nHA Won Player O\n");
        }
        break;

    default:
        do {
            printf("Please enter a number from 1 to 3 to selesct Mode:\n");
            scanf("%d", &option);
            if (option >= 1 && option <= 3 && (sizeof(option) / (sizeof(int))) == 1) {
                input = true;
                break;
            }
        } while (input == false);
        if (input == true) {
            goto start;
        }
        
    }
    return 0;
}

void Initial_Display() {

    printf("\n\n");
    printf("                                                                      \n");
    printf("            CONNECT 4 - GAME                                         \n");
    printf("    Please choose a valid option below to proceed.                    \n");
    printf("                                                                      \n");
    printf("          !   !   !   !   !   !                                       \n");
    printf("          !   !   !   !   !   !                                       \n");
    printf("          !   !   !   !   !   !                                       \n");
    printf("          !   !   !   ! O !   !                                       \n");
    printf("          !   ! X !   ! X ! O !                                       \n");
    printf("          ! O ! O ! O ! X ! X !                                       \n");
    printf("          *********************                                       \n");
    printf("                                                                      \n");
    printf("                                                                      \n");
    printf("                                                                      \n");
    printf("    Press key 1 tp play VS Artificial Intelligence (MODE DIFICIL)     \n");
    printf("    Press key 2 to play VS Artificial Intelligence (MODE FACIL)       \n");
    printf("    Press key 3 to play Player1 VS Player2                           \n");
    printf("                                                                      \n");
}

void Board_Display(Node* access) {

    system("cls");
    srand(time(0));
    Initialize_Board(access);
    Print_Board(access->board);
}

int Validate_UserInput() {

    int position;
    jump1:
    printf("\nWhich coloumn would you like to mark 1st Player O? \n");
    scanf("%i", &position);
    if (position >= 1 && position <= 7 && (sizeof(position) / (sizeof(int))) == 1) {
        goto jump2;
    }
    else {
        printf("Please enter a valid coloumn nunmber between 1 to 7\n");
        goto jump1;
    }
    jump2:
    return position;
}

int Board_Full(int board[R][C]) {

    int i, j, check = 0;
    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            if (board[i][j] != 0) {
                check++;
            }
        }
    }
    if (check == (R * C)) {
        return 1; //board Full
    }
    else {
        return 0;
    }
}

int Verify_Shot(int board[R][C], int position) {

    if (0 < position && position < C + 1 && board[0][position - 1] == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

void Copy_Board(int destination[R][C], int origin[R][C]) {

    int i, j;
    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            destination[i][j] = origin[i][j];
        }
    }
}

int Determine_Fills(int board[R][C]) {

    int fills = 0, i;
    for (i = 0; i < C; i++) {
        if (board[0][i] == 0) {
            fills++;
        }
    }
    return fills;
}

int verify(int board[R][C], int player) {

    int i, j;
    for (j = 0; j < C; j++) {
        for (i = 0; i < (R - 3); i++) {
            if (board[i][j] == player && board[i + 1][j] == player && board[i + 2][j] == player && board[i + 3][j] == player) {
                return player;
            }
        }
    }

    for (j = 0; j < (C - 3); j++) {
        for (i = 0; i < R; i++) {
            if (board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == player && board[i][j + 3] == player) {
                return player;
            }
        }
    }

    for (i = 0; i < (R - 3); i++) {
        for (j = (C - 1); j > 2; j--) {
            if (board[i][j] == player && board[i + 1][j - 1] == player && board[i + 2][j - 2] == player && board[i + 3][j - 3] == player) {
                return player;
            }
        }
    }


    for (j = 0; j < (C - 3); j++) {
        for (i = 0; i < (R - 3); i++) {
            if (board[i][j] == player && board[i + 1][j + 1] == player && board[i + 2][j + 2] == player && board[i + 3][j + 3] == player) {
                return player;
            }
        }
    }

    return 0;
}

int Shot_Real(int board[R][C], int shotFalse) {

    int i, check = 0;
    for (i = 0; i < C; i++) {
        check = check + Verify_Shot(board, i + 1);
        if (check == shotFalse) {
            break;
        }
    }
    return i + 1;
}

void Print_Board(int board[R][C]) {

    int i, j;
    printf("\n  ");
    for (i = 0; i < C; i++) {
        printf("%i   ", i + 1);
    }
    printf("\n\n");
    for (i = 0; i < R; i++) {
        printf("! ");
        for (j = 0; j < C; j++) {
            if (board[i][j] == 1) {
                printf("X ! ");
            }
            else if (board[i][j] == 2) {
                printf("O ! ");
            }
            else {
                printf("  ! ");
            }
        }
        printf("\n");
    }
}

void Apply_Shot(int board[R][C], int position, int player) {

    int i;
    for (i = R - 1; i >= 0; i--) {
        if (board[i][position - 1] == 0) {
            board[i][position - 1] = player;
            break;
        }
    }
}

int Board_Won(int board[R][C]) {

    if (verify(board, 1) == 1) return 0;
    return 47;
}

int Board_Lost(int board[R][C]) {

    if (verify(board, 2) == 2) return 0;
    return 47;
}

int Connect_Vertical3(int board[R][C], int i, int j, int player) {

    if (board[i][j] == player && board[i + 1][j] == player && board[i + 2][j] == player) {
        return 1;
    }
    else {
        return 0;
    }
}

int Connect_Horitzontal3(int board[R][C], int i, int j, int player) {

    if (board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == player) {
        return 1;
    }
    else {
        return 0;
    }
}

int Connect_Diagonals3(int board[R][C], int i, int j, int player) {

    int check = 0;
    if (board[i][j] == player && board[i + 1][j + 1] == player && board[i + 2][j + 2] == player) {
        check++;
    }
    if (board[i][j] == player && board[i - 1][j + 1] == player && board[i - 2][j + 2] == player) {
        check++;
    }
    return check;
}

int Connect_Vertical2(int board[R][C], int i, int j, int player) {

    if (board[i][j] == player && board[i + 1][j] == player) {
        return 1;
    }
    else {
        return 0;
    }
}

int Connect_Horitzontal2(int board[R][C], int i, int j, int player) {

    if (board[i][j] == player && board[i][j + 1] == player) {
        return 1;
    }
    else {
        return 0;
    }
}

int Connect_Diagonals2(int board[R][C], int i, int j, int player) {

    int check = 0;
    if (board[i][j] == player && board[i + 1][j + 1] == player) {
        check++;
    }
    if (board[i][j] == player && board[i - 1][j + 1] == player) {
        check++;
    }
    return check;
}

int Connection2(int board[R][C], int player) {

    int i, j, sum = 0;
    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            sum = sum + Connect_Vertical2(board, i, j, player) + Connect_Horitzontal2(board, i, j, player) + Connect_Diagonals2(board, i, j, player);
        }
    }
    return sum;
}

int Connection3(int board[R][C], int player) {

    int i, j, sum = 0;
    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            sum = sum + Connect_Vertical3(board, i, j, player) + Connect_Horitzontal3(board, i, j, player) + Connect_Diagonals3(board, i, j, player);
        }
    }
    return sum;
}

double Heuristic(int board[R][C]) {

    int tres = 0, dos = 0, tres_oposats = 0, dos_oposats = 0;
    tres = Connection3(board, 1);
    dos = Connection2(board, 1) - 2 * tres;
    tres_oposats = Connection3(board, 2);
    dos_oposats = Connection2(board, 2) - 2 * tres_oposats;
    if (Board_Won(board) == 0) {
        return 100000;
    }
    else if (Board_Lost(board) == 0) {
        return -100000;
    }
    else {
        return (tres * 100 + dos * 10) - (tres_oposats * 100 + dos_oposats * 10);
    }
}

void Initialize_Board(Node* access) {

    int i, j;
    access->n_fills = C;
    access->fills = malloc(access->n_fills * sizeof(Node*));
    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            access->board[i][j] = 0;
        }
    }
}

Node* Create_Node(Node* pair, int numFill, int prof) {

    int level;
    if (prof % 2 == 0) {
        level = 2;
    }
    else {
        level = 1;
    }

    Node* p = (Node*)malloc(sizeof(Node));
    Copy_Board(p->board /* destination */, pair->board);
    Apply_Shot(p->board, Shot_Real(p->board, numFill + 1), level);
    p->depth = prof;

    if (verify(p->board, 1) || verify(p->board, 2)) {
        p->n_fills = 0;
        p->fills = NULL;
        p->value = Heuristic(p->board);
    }
    else if (prof < R) {
        p->n_fills = Determine_Fills(p->board);
        p->fills = malloc(p->n_fills * sizeof(Node*));
        if (prof % 2 == 0) {
            p->value = -10000000;
        }
        else {
            p->value = 10000000;
        }
    }
    else {
        p->n_fills = 0;
        p->fills = NULL;
        p->value = Heuristic(p->board);
    }
    return p;
}

void Create1Level(Node* pair, int prof) {

    int i;
    for (i = 0; i < pair->n_fills; i++) {
        pair->fills[i] = Create_Node(pair, i, prof);
    }
}

void Create_Map(Node* access, int prof) {

    int i;
    prof++;
    Create1Level(access, prof);
    if (prof < R) {
        for (i = 0; i < access->n_fills; i++) {
            Create_Map(access->fills[i], prof);
        }
    }
}

void Mini_Max(Node* pair) {

    int i;
    for (i = 0; i < pair->n_fills; i++) {
        Mini_Max(pair->fills[i]);
        if (pair->fills[i]->depth % 2 == 0) {
            if (pair->fills[i]->value < pair->value) {
                pair->value = pair->fills[i]->value;
            }
        }
        else {
            if (pair->fills[i]->value > pair->value) {
                pair->value = pair->fills[i]->value;
            }
        }
    }
}

double ferMini_Max(Node* pair) {

    double max = -10000000;
    int shot_no;
    Mini_Max(pair);
    for (int i = 0; i < pair->n_fills; i++) {
        if (pair->fills[i]->value > max) {
            max = pair->fills[i]->value;
            shot_no = i;
        }
    }
    return Shot_Real(pair->board, shot_no + 1);
}

void Display_Winner(int end) {

    if (end == 1) {
        printf("\n\nHA Won COMPUTER\n");
    }
    else if (end == 4) {
        printf("Board Full! DRAW\n");
    }
    else {
        printf("\n\nHA Won Player HUMAN\n");
    }
}