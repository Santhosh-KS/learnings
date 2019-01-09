#include <iostream>

void Solve(int n, char fromRod, char midRod, char toRod)
{
  if (n == 1) {
    std::cout << "Moved " << n << " from " << fromRod << " to " << toRod << "\n";
    return;
  }

  Solve(n-1, fromRod, toRod, midRod); // Stage 1 where Bigger disk is freed up and an empty peg in the
  // End is available.
  std::cout << "Moved " << n << " from " << fromRod << " to " << toRod << "\n";
  Solve(n-1, midRod, toRod, fromRod);
}

int main(int argc, char** argv)
{
  if (argc < 2) {
    std::cout << "USAGE: ./TowerOfHanoi <num_of_disks>\n";
    return 0;
  }
  int val = std::stoi(argv[1]);
  Solve(val,'A','B','C');
}
