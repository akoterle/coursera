#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <cstdlib>

using std::vector;
using std::cin;
using std::cout;
using std::cerr;

class Timer
{
public:
  Timer() : beg_(clock_::now()) {}
  void reset() { beg_ = clock_::now(); }
  double elapsed() const
  {
    return std::chrono::duration_cast<second_>(clock_::now() - beg_).count();
  }

private:
  typedef std::chrono::high_resolution_clock clock_;
  typedef std::chrono::duration<double, std::ratio<1>> second_;
  std::chrono::time_point<clock_> beg_;
};

long long MaxPairwiseProduct(const vector<int> &numbers)
{
  int first_index = -1;
  int second_index = -1;
  long long result = 0;
  int n = numbers.size();

  for (int i = 0, j = i + 1; i < n - 1; i++, j++)
  {
    if ((first_index == -1) || (numbers[i] > numbers[first_index]))
      first_index = i;
      else if ((second_index == -1) || (numbers[i] > numbers[second_index]))
      second_index = j;
    if (numbers[j] > numbers[first_index])
    {
      if ((second_index == -1) || (numbers[first_index] > numbers[second_index]))
        second_index = first_index;
      first_index = j;
    }
    i++; j++;

  }
  result = (long long)numbers[first_index] * numbers[second_index];
  return result;
}

long long MaxPairwiseProductFast(const vector<int> &numbers)
{
  int n = numbers.size();

  int max_index1 = -1;
  for (int i = 0; i < n; ++i)
    if ((max_index1 == -1) || (numbers[i] > numbers[max_index1]))
      max_index1 = i;

  int max_index2 = -1;
  for (int j = 0; j < n; ++j)
    //    if ((numbers[j] != numbers[max_index1]) && ((max_index2 == -1) || (numbers[j] > numbers[max_index2])))
    if ((j != max_index1) && ((max_index2 == -1) || (numbers[j] > numbers[max_index2])))
      max_index2 = j;
  cout << max_index1 << ' ' << max_index2 << "\n";
  return ((long long)(numbers[max_index1])) * numbers[max_index2];
}

int main()
{
  while (true)
  {
    int n = rand() % 10 + 2;
    cerr << n << "\n";
    vector<int> a;
    for (int i = 0; i < n; ++i)
    {
      a.push_back(rand() % 100000);
    }
    for (int i = 0; i < n; ++i)
    {
      cerr << a[i] << ' ';
    }
    cerr << "\n";
    long long res1 = MaxPairwiseProduct(a);
    long long res2 = MaxPairwiseProductFast(a);
    if (res1 != res2)
    {
      cerr << "Wrong answer: " << res1 << ' ' << res2 << "\n";
      break;
    }
    else
    {
      cerr << "OK\n";
    }
  }
}
