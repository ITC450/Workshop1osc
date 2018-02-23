#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
//#include <string>
//#include <cstdio>
//#include <cstdlib>
//#include <ctime>
#include <chrono>

using namespace std;
#define NUM_THREADS 1000000
mutex lager_mutex;

struct lager{
  vector<int> database = {2, 4, 6, 8, 10, 12, 14 , 16, 18, 20};
  vector<int>::iterator it;
}_lager;



void koeb(int item, int amount, struct lager *k_lager){
  int loaded_amount = k_lager->database[item];
  if(loaded_amount == 0 || loaded_amount < amount){
    cout << "Køb fejl\n";
    return;
  }
  else{
    lock_guard<mutex> guard(lager_mutex);

    k_lager->database[item] = loaded_amount-amount;

    cout << "Køb\n";
  }
}

void salg(int item, int amount, struct lager *s_lager){
  int loaded_amount = s_lager->database[item];
  lock_guard<mutex> guard(lager_mutex);

  s_lager->database[item] = loaded_amount + amount;

  cout << "Salg\n";
}



void users(){
  bool intention = rand() % 2;
  int item = rand() % 10;
  int amount = rand() % 6;
  if(intention){

    koeb(item, amount, &_lager);
  }
  else{

    salg(item, amount, &_lager);
  }
}

int main(){

  auto start = std::chrono::high_resolution_clock::now();

  thread threads[NUM_THREADS];
  srand (time(NULL));
  //thread t1 (users);

  for (int i = 0; i < NUM_THREADS; i++) {
    //bool intention = 1;

    threads[i] = thread(users);
    threads[i].join();
    //threads[i].detach();
    for (auto i = _lager.database.begin(); i != _lager.database.end(); ++i)

          std::cout << *i << ' ';
  }
  auto end = std::chrono::high_resolution_clock::now();
  auto result = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
  std::cout << "Microseconds = " << result.count() << std::endl;
}
