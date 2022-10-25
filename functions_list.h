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
int Comptar2(int board[R][C], int player);
int Comptar3(int board[R][C], int player);
double Heuristic(int board[R][C]);
Node* Create_Node(Node* pair, int numFill, int prof);
void Create1Level(Node* pair, int prof);
void Create_Map(Node* access, int prof);
void Mini_Max(Node* pair);
double ferMini_Max(Node* pair);
void Display_Winner(int end);