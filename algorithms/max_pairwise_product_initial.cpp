#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>

using std::vector;
using std::cin;
using std::cout;

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
  int max, first_index = 0;
  int second_index = 0;
  long long result = 0;
  int n = numbers.size();

  for (int i = 0, j = i + 1; i < n - 1; i++, j++)
  {
    if (numbers[i] > first_index)
      first_index = i;
    if (numbers[j] > numbers[first_index])
    {
      if (numbers[first_index] > numbers[second_index])
        second_index = first_index;
      first_index = j;
    }
    i = j * 2;
    j = i + 1;

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
    if ((numbers[j] != numbers[max_index1]) && ((max_index2 == -1) || (numbers[j] > numbers[max_index2])))
      max_index2 = j;

  return ((long long)(numbers[max_index1])) * numbers[max_index2];
}

int main()
{
  int n;
  cin >> n;
  vector<int> numbers(n);
  for (int i = 0; i < n; ++i)
  {
    cin >> numbers[i];
  }

  long long result = MaxPairwiseProduct(numbers);

  cout << result << "\n";
  return 0;
}
