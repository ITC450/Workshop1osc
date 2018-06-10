#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <atomic>
#include <unistd.h>

using namespace std;
#define NUM_THREADS    2000
mutex lager_mutex;
std::atomic <bool> ready(false);


struct lager
{
   vector <int> database = { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20 };
   vector <int>::iterator it;
} _lager;



void koeb(int item, int amount, struct lager *k_lager)
{
   int loaded_amount = k_lager->database[item];

   if (loaded_amount == 0 || loaded_amount < amount)
   {
      cout << "Køb fejl\n";
      return;
   }
   else
   {
      {
         lock_guard <mutex> guard(lager_mutex);
         k_lager->database[item] = loaded_amount - amount;
      }
      cout << "Køb\n";
      for (auto i = _lager.database.begin(); i != _lager.database.end(); ++i)
      {
         std::cout << *i << ' ';
      }
   }
}

void salg(int item, int amount, struct lager *s_lager)
{
   int loaded_amount = s_lager->database[item];

   {
      lock_guard <mutex> guard(lager_mutex);
      s_lager->database[item] = loaded_amount + amount;
   }
   cout << "Salg\n";
   for (auto i = _lager.database.begin(); i != _lager.database.end(); ++i)
   {
      std::cout << *i << ' ';
   }
}

void users()
{
   while (!ready)
   {
      std::this_thread::yield();
   }
   bool intention = rand() % 2;
   int  item      = rand() % 10;
   int  amount    = rand() % 6;
   if (intention)
   {
      koeb(item, amount, &_lager);
   }
   else
   {
      salg(item, amount, &_lager);
   }
}

int main()
{
   //std::cout << sizeof(int) << '\n';
   auto start = std::chrono::high_resolution_clock::now();

   thread threads[NUM_THREADS];

   srand(time(NULL));

   for (int i = 0; i < 1; i++)
   {
      for (int i = 0; i < NUM_THREADS; i++)
      {
         threads[i] = thread(users);
      }
      ready = true;
      for (auto& th : threads)
      {
         th.join();
      }
   }

   auto end    = std::chrono::high_resolution_clock::now();
   auto result = std::chrono::duration_cast <std::chrono::microseconds>(end - start);
   std::cout << "Microseconds = " << result.count() << std::endl;
}
