#include <bits/stdc++.h>
using namespace std;

int board[9][9];
int solutionCount = 0;

// Kiểm tra số val có hợp lệ khi đặt vào (r, c)
bool isValid(int r, int c, int val) 
{
    // kiểm tra hàng
    for (int j = 0; j < 9; j++) {
        if (board[r][j] == val) 
            return false;
    }
    // kiểm tra cột
    for (int i = 0; i < 9; i++) {
        if (board[i][c] == val) 
            return false;
    }
    // kiểm tra ô 3x3
    int startRow = (r / 3) * 3;
    int startCol = (c / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[startRow + i][startCol + j] == val) 
                return false;
        }
    }
    return true;
}

// Hàm backtracking
void solveSudoku(int cell) 
{
    if (cell == 81) { // đi hết 81 ô
        solutionCount++;
        return;
    }
    int r = cell / 9;
    int c = cell % 9;

    if (board[r][c] != 0) {
        // ô đã có sẵn → bỏ qua
        solveSudoku(cell + 1);
    } else {
        // thử điền 1..9
        for (int val = 1; val <= 9; val++) {
            if (isValid(r, c, val)) {
                board[r][c] = val;         // điền thử
                solveSudoku(cell + 1);     // đi tiếp
                board[r][c] = 0;           // quay lui
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Đọc input 9x9
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> board[i][j];
        }
    }

    solveSudoku(0); // bắt đầu từ ô 0

    cout << solutionCount << "\n";
    return 0;
}





// Write a program to compute the number of sudoku solutions (fill the zero elements of a given partial sudoku table)
// Fill numbers from 1, 2, 3, .., 9 to 9 x 9 table so that:
// Numbers of each row are distinct
// Numbers of each column are distinct
// Numbers on each sub-square 3 x 3 are distinct
// Input
// Each line i (i = 1, 2, ..., 9) contains elements of the i
// th
//  row of the Sudoku table: elements are numbers from 0 to 9 (value 0 means the empty cell of the table)
// Output
// Write the number of solutions found

// Example
// Input
// 0 0 3 4 0 0 0 8 9
// 0 0 6 7 8 9 0 2 3
// 0 8 0 0 2 3 4 5 6
// 0 0 4 0 6 5 0 9 7
// 0 6 0 0 9 0 0 1 4
// 0 0 7 2 0 4 3 6 5
// 0 3 0 6 0 2 0 7 8
// 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0
// Output
// 64