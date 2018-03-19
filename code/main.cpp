#include "HashMap.h"
#include <iostream>
#include <string>
#include <time.h>
using namespace std;
const int N = 2500;
const int K = 3;
void menu(HashMap<string> &HMap) {
  cout << endl
       << "1 - Print\n"
       << "2 - Add element\n"
       << "3 - Delete elem\n"
       << "4 - Export\n"
       << "5 - Exit\n"
       << "Select the menu item: ";
  int choice;
  cin >> choice;
  cin.clear();
  cin.ignore(cin.rdbuf()->in_avail());
  switch (choice) {
  case 1: {
    HMap.print();
    menu(HMap);
    break;
  }
  case 2: {
    string key;
    string val;
    cout << "Key: ";
    getline(cin, key);
    if (key.length() == 6 && isupper(key[0]) && isupper(key[5]) &&
        isdigit(key[1]) && isdigit(key[2]) && isdigit(key[3]) &&
        isdigit(key[4])) {
      cout << "Value: ";
      getline(cin, val);
      HMap.put(key, val);
    }
    menu(HMap);
    break;
  }
  case 3: {
    string key;
    cout << "Key: ";
    getline(cin, key);
    if (key.length() == 6 && isupper(key[0]) && isupper(key[5]) &&
        isdigit(key[1]) && isdigit(key[2]) && isdigit(key[3]) &&
        isdigit(key[4])) {
      cout << "Elements with collisions: " << HMap.del(key).size() << endl;
    }
    menu(HMap);
    break;
  }
  case 4: {
    HMap.excel(string("excel.txt"));
    cout << "OK" << endl;
    menu(HMap);
    break;
  }
  case 5: {
    break;
  }
  default:
    cout << "Incorrect choice." << endl;
    menu(HMap);
  }
}
int main() {
  srand(time(0));
  HashMap<string> HMap(N);
  for (int i = 0; i < K; i++) {
    string strKey(6, '0');
    string strVal(10 + rand() % 70, '\0');
    strKey[0] = 'A' + rand() % 26;
    strKey[1] = '0' + rand() % 9;
    strKey[2] = '0' + rand() % 9;
    strKey[3] = '0' + rand() % 9;
    strKey[4] = '0' + rand() % 9;
    strKey[5] = 'A' + rand() % 26;
    for (int i = 0; i < strVal.length(); i++)
      strVal[i] = (char)'A' + rand() % 26;
    HMap.put(strKey, strVal);
  }
  menu(HMap);
  return 0;
}
