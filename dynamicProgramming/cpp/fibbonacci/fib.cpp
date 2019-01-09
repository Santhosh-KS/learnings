#include <iostream>



uint64_t FibHeadRecursion(int n)
{
  if (n <= 0) {
    return 0;
  }

  return n + FibHeadRecursion(n-1);
}

//0,1,1,2,3,5,8,13,....
uint64_t FibTailRecursion(int n, int a, int b)
{
  if (n == 0) {
    return a;
  }
  if (n == 1) {
    return b;
  }
  return FibTailRecursion(n-1,b,a+b);
}

int main()
{
  std::cout << FibHeadRecursion(10) << "\n";
  std::cout << FibTailRecursion(10, 0, 1) << "\n";
  return 0;
}
