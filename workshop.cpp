#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

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
    k_lager->database[item] = loaded_amount-amount;
    cout << "Køb\n";
  }
}

void salg(int item, int amount, struct lager *s_lager){
  int loaded_amount = s_lager->database[item];
  s_lager->database[item] = loaded_amount + amount;
  cout << "Salg\n";
}

void users(){
  bool intention = rand() % 2;
  //bool intention = 1;
  int item = rand() % 10;
  int amount = rand() % 6;
  if(intention){
    koeb(item, amount, &_lager);
  }
  else{
    salg(item, amount, &_lager);
  }
}

//vector<string> name = {"Sne", "Briller", "Vand", "Bold", "Elektrisk lyssværd", "Ged", "Hundevalp", "Selvlysende kondom"};

int main(){
  srand (time(NULL));
  for (int i = 0; i < 50; i++) {
    for (auto i = _lager.database.begin(); i != _lager.database.end(); ++i)
          std::cout << *i << ' ';

    users();
  }
}
