#include <iostream>
#include <vector>


class Nqueens
{
  private:
    const int &NumOfQueens;
    std::vector<std::vector<int>> ChessBoard;
  public:
    Nqueens(const int &numOfQueens);
    ~Nqueens();

    bool IsValidPosition(int rowIdx, int colIdx);
    bool SetNewQueenPosition(int col);
    bool Solve();
    void PrintPosition();
};

Nqueens::Nqueens(const int &numOfQueens): NumOfQueens(numOfQueens)
{
  ChessBoard.resize(NumOfQueens);
  for (auto &rows: ChessBoard) {
    rows.resize(NumOfQueens);
  }
}

Nqueens::~Nqueens()
{
  // Empty.
}

bool Nqueens::IsValidPosition(int rowIndex, int colIndex)
{

  // Example: 4X4 chess board.
  // (0,0) (0,1) (0,2) (0,3)
  // (1,0) (1,1) (1,2) (1,3)
  // (2,0) (2,1) (2,2) (2,3)
  // (3,0) (3,1) (3,2) (3,3)
  //
  // Say Queen is present in (0,0). Now in second iteration we cannot place the
  // Queen on (0,1).For Loop(1) will evaluate the condition to false.

  // For Loop --> 1
  for(int i=0; i< colIndex; i++) {
    if (ChessBoard[rowIndex][i] == 1) {
      return false;
    }
  }

  // Now suppose we want to check if we can place the Queen in (2,1). In this scinario we need to
  // eavaluate the diagonal element associated with(2,1).
  // ( Q ) (0,1) (0,2) (0,3)
  // (1,0) (1,1) (1,2) (1,3)
  // (2,0) (?Q?) (2,2) (2,3)
  // (3,0) (3,1) (3,2) (3,3)
  //
  // Now we just need to worry only about the diagonal corners (1,0) and (3,0) and check if there are any
  // Queen's already placed or Queen's are sitting in the same diagonal.
  // The check for diagonal element (1,0) happens in For Loop (2).

  // ( Q ) (   ) (   ) (   )
  // (1,0) (   ) (   ) (   )
  // (   ) (?Q?) (   ) (   )
  // (   ) (   ) (   ) (   )

  // From the above illustration, we consider (?Q?) as the bottom right corner and (1,0) as the top left corner
  // of the square. The other elements on the column ex (2,x) or (3,x) doesn't matter for now as we have not placed
  // any Queens in those columns.
  // This is curicial to understand this logic.

  // +-----------+
  // |(1,0)|(   )|
  // +-----+-----+
  // |(   )|(?Q?)|
  // +-----------+

  // For Loop --> 2
  for(int row = rowIndex, col = colIndex; row >=0 && col >= 0; row--, col-- ) {
    if (ChessBoard[row][col] == 1) {
      return false;
    }
  }

  // The check for diagonal element (3,0) happens in For Loop (3).
  // ( Q ) (   ) (   ) (   )
  // (   ) (   ) (   ) (   )
  // (   ) (?Q?) (   ) (   )
  // (3,0) (   ) (   ) (   )
  //
  // From the above illustration, we consider (?Q?) as the top right corner and (3,0) as the bottom left corner
  // of the square. The other elements on the column ex (2,x) or (3,x) doesn't matter for now as we have not placed
  // any Queens in those columns.
  // This is curicial to understand this logic.

  // +-----------+
  // |(   )|(?Q?)|
  // +-----+-----+
  // |(3,0)|(   )|
  // +-----------+

  // For Loop -->3
  for(int row = rowIndex, col = colIndex; row < NumOfQueens && col >= 0; row++, col--) {
    if (ChessBoard[row][col] == 1) {
      return false;
    }
  }

  // Just to solidfy the understanding. if we are evaluating position (2,3), then
  // our For Loop (2) evaluation square looks as follows.

  // +-----+-----+-----+
  // |(0,1)|(   )|(   )|
  // +-----+-----+-----+
  // |(   )|(1,2)|(   )|
  // +-----+-----+-----+
  // |(   )|(   )|(?Q?)| <---(2,3)
  // +-----+-----+-----+

  // For Loop (3) evaluation square looks as follows.
  // +-----------+
  // |(   )|(?Q?)| <--(2,3)
  // +-----+-----+
  // |(3,2)|(   )|
  // +-----------+

  return true;
}


bool Nqueens::SetNewQueenPosition(int colIdx)
{
  if (colIdx == NumOfQueens) {
    return true;
  }

  for (int i = 0; i < NumOfQueens; i++) {
    if (IsValidPosition(i, colIdx)) {
      ChessBoard[i][colIdx] = 1;
      if (SetNewQueenPosition(colIdx + 1)) {
        return true;
      }
      ChessBoard[i][colIdx] = 0;
    }
  }
  return false;
}

bool Nqueens::Solve()
{
  int col = 0;
  if (SetNewQueenPosition(col)) {
    PrintPosition();
  }
  else {
    std::cout << "It is not possible to solve " << NumOfQueens << " poblem\n";
  }
}

void Nqueens::PrintPosition()
{
  for(int i = 0; i < NumOfQueens; i++) {
    for (int j = 0; j < NumOfQueens; j++) {
      if (ChessBoard[i][j] == 1) {
        std::cout << " Q ";
      }
      else {
        std::cout << " - ";
      }
    }
    std::cout << "\n";
  }
}

int main(int argc, char** argv)
{
  if (argc < 2) {
    std::cout << "USAGE: Nqueens <num_of_queens>\n";
    return 0;
  }
  int num = std::stoi(argv[1]);
  Nqueens queens(num);
  //queens.PrintPosition();
  std::cout << "\n";
  queens.Solve();
}
