#include <bits/stdc++.h>
using namespace std;

class game{
    private:
    int board[9][9];
    int solution[9][9];

    public:
    game(){
        memset(board, 0, sizeof(board));
        memset(solution, 0, sizeof(solution));
    } 
    ~game(){} //destructor

    void createGame(){
        string gameData;
        fstream dataFile("testcaseonepuzzle.txt");
        if(dataFile.is_open()){
            getline(dataFile, gameData);

            dataFile.close();
        }
        if(gameData.length() != 81){
            cerr << "game data is not 81 integers long";
            return;
        }
          
        for(int i = 0; i < 9; ++i){
            for(int j = 0; j < 9; ++j){
                board[i][j] = gameData[i * 9 + j] - '0';
                solution[i][j] = gameData[i * 9 + j] - '0';
            }
        }
        
    displayBoard();
    }
    void displayBoard(){
        int rowCounter;
        cout << "1 2 3   4 5 6   7 8 9\n---------------------\n";
        
        for (int i = 0; i < 9; ++i) {
            rowCounter++;
            if (i % 3 == 0 && i != 0) {
                cout << "---------------------\n";
            }
            for (int j = 0; j < 9; ++j) {
                if (j % 3 == 0 && j != 0) {
                    cout <<  "| ";
                }
                cout <<board[i][j] << ' ';
            }
            cout << "| " << i + 1 << "\n";
        }
    }


    void changeValue(){
    int getRow;
    int getCol;
    int val;

    while(true){ 
        cout << "Enter the Row (1-9): ";
        cin >> getRow;
        while(cin.fail() || getRow <= 0 || getRow > 9){\
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "No row exists, please try again: ";
            cin >> getRow;
        }

        cout << "Enter the Column (1-9): ";
        cin >> getCol;
        while(cin.fail() || getCol <= 0 || getCol > 9){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "No Column exists, please try again: ";
            cin >> getCol;
        }
        if(board[getRow - 1][getCol - 1] != 0) {
            cout << "A number is already set at this position. Please choose another position.\n";
            continue;
        }
        cout << "Enter Number: ";
        cin >> val;

        if(cin.fail()){
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid input, please enter numerical values only.\n";
            continue; 
        }

        board[getRow - 1][getCol - 1] = val; 
        solution[getRow - 1][getCol - 1] = val; 
        displayBoard(); 
    }
}
    bool isValid(int row, int col, int num){
       for(int x = 0; x < 9; x++){
        if(solution[row][x] == num || solution[x][col] == num){
            return false;
        }
        if(solution[3 * (row / 3) + x / 3][(col / 3) + x % 3] == num){
            return false;
        }
       }
       return true;

        
    }
    bool solve(){      
         int row = -1, col = -1;
         bool isEmpty = false;

        for (int i = 0; i < 9 && !isEmpty; i++) {
            for (int j = 0; j < 9; j++) {
                if (solution[i][j] == 0) {
                    row = i;
                    col = j;
                    isEmpty = true;
                    break;
                }
            }
        }
        if (!isEmpty) {
            return true; 
        }

        for (int num = 1; num <= 9; num++) {
            if (isValid(row, col, num)) {
                solution[row][col] = num; 

                if (solve()) { 
                    return true;
            }
            
                solution[row][col] = 0; 
        }
    }
    return false;
        
    }
    void displaySolution() {
        if (solve()) {
            cout << "Solution:\n";
            memcpy(board, solution, sizeof(board)); 
            displayBoard();
        } else {
            cout << "No solution exists.\n";
        }
    }

};
int main()
{
   game mygame;
   int decision;
   while (true){
    cout << "(1) Play \n(2) Solve\n";
    cin >> decision;
    if(decision == 1){
        mygame.createGame();
        mygame.changeValue();
    }
    else if(decision == 2){
        mygame.displaySolution();
    }else{cout << "Invalid Input, try again.\n";}

   }
   
   
   return 0;
    
}

