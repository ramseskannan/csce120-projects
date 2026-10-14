//forgot the include statements
#include "functions.h"
#include <stdexcept>
#include <limits>
#include <cstdint>


int largest(int a, int b, int c) {
  int d = a; //assuming a is the largest
  if (b > d) //comparing b to largest
    d = b; 
  if(c > d) //comparing c to largest
    d = c;
  return d;
} //forgot the bracket

bool sum_is_even(int a, int b) {
  return ((a + b) % 2 == 0); //checking if sum is even
} //forgot this bracket

int boxes_needed(int apples) {
  if (apples <= 0) 
    return 0; //apples cant be 0 or less because no boxes are need for them
  
    //add 19 to simulate roudning up
  long long total = (long long)apples + 19;
  return (int)(total / 20); //rounding up
}

bool smarter_section(int A_correct, int A_total, int B_correct, int B_total) { //fixed the variable name
  //we have to validate all the inputs first
  if (A_total <= 0 || B_total <= 0 ||
      A_correct < 0 || B_correct < 0 ||
      A_correct > A_total || B_correct > B_total){
    throw std::invalid_argument("invalid input");
  }
  //used long long to prevent overflow
  long long left = (long long)A_correct * B_total;
  long long right = (long long)B_correct * A_total;

  return left > right; //true only if A performed better
}


bool good_dinner(int pizzas, bool is_weekend) {
  //weekends, needs atleast 10 pizzas
  if (is_weekend) {
    return pizzas >= 10;
  } else { 
    //weekdays: need between 10 and 20 inclusive 
    return pizzas >= 10 && pizzas <=20;
  }
}

int sum_between(int low, int high) {
  if (low > high) 
    throw std::invalid_argument("low > high"); //invalid order

  //using 64 bit like said in the document for safe calculations
  if (low == high)
    return low;
  //safely calculating them using long long
  long long n = (long long)high - low + 1;
  long long  total = n * ((long long)low + high);

  //to get the final sum
  long long sum = total / 2;

  //this checks for overflow relative to 32-bit integer
  if (sum > std::numeric_limits<int>::max() || sum < std::numeric_limits<int>::min()) {
    throw std::overflow_error("overflow");
  }
  return (int)sum;
}

int64_t product(int64_t a, int64_t b) {
  // return a x b this is the wrong notation
  if (a == 0 || b == 0) {
    return 0;
  }
    //4 cases
    //boht positive, check for max limit
    if ((a > 0 && b > 0 && a > std::numeric_limits<int64_t>::max() / b) ||
      // both negative, results in a pos value
        (a < 0 && b < 0 && a < std::numeric_limits<int64_t>::max() / b) ||
      //a pos and b neg, results is negative
        (a > 0 && b < 0 && b < std::numeric_limits<int64_t>::min() / a) ||
      //a neg and b pos, resutls is negative
        (a < 0 && b > 0 && a < std::numeric_limits<int64_t>::min() / b)) {
      throw std::overflow_error("overflow");
    }
    //safe to multiply now
    return a * b;  

}