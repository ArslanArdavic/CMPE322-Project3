#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <mutex>

int g_num = 0;  // protected by g_num_mutex
std::mutex g_num_mutex;

void slow_increment(int id) 
{
    for (int i = 0; i < 3; ++i) {
        g_num_mutex.lock(); 
        ++g_num;
        // note, that the mutex also syncronizes the output
        std::cout << "id: " << id << ", g_num: " << g_num << '\n';
        g_num_mutex.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(234));
    }
}

void print(int n, const std::string &str)  {
  std::string msg = std::to_string(n) + " : " + str;
  std::cout << msg  << std::endl;
}
 
int main() {
   /* 
  std::vector<std::string> s = {
      "Educative.blog",
      "Educative",
      "courses",
      "are great"
  };
  std::vector<std::thread> threads;
 
  for (int i = 0; i < s.size(); i++) {
    threads.push_back(std::thread(print, i, s[i]));
  }
 
  for (auto &th : threads) {
    th.join();
  }
  std::cout << threads[0];
    */

    std::thread t1(slow_increment, 0);
    std::thread t2(slow_increment, 1);
    t1.join();
    t2.join();

    return 0;
}
