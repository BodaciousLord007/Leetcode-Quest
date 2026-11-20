/*
Problem statement: Simple Bank System

You have been tasked with writing a program for a popular bank that will
automate all its operations. The bank has n accounts numbered from 1 to n.
The initial balance of each account is stored in a 0-indexed integer array
balance of size n, where the (i + 1)th account has an initial balance of balance[i].

Execute all the valid transactions. A transaction is valid if:
- The given account number(s) are between 1 and n, and
- The amount of money withdrawn or transferred from is less than or equal to
  the balance of the account.

Implement the Bank class:
- Bank(vector<long long>& balance): Initializes the object with the 0-indexed
  integer array balance.
- bool transfer(int account1, int account2, long long money): Transfers money dollars
  from the account numbered account1 to account2. Returns true if successful, false otherwise.
- bool deposit(int account, long long money): Deposits money dollars into the account
  numbered account. Returns true if successful, false otherwise.
- bool withdraw(int account, long long money): Withdraws money dollars from the account
  numbered account. Returns true if successful, false otherwise.

Example:
vector<long long> balance = {10, 100, 20, 50, 30};
Bank bank(balance);
bank.withdraw(3, 10);    // return true
bank.transfer(5, 1, 20); // return true
bank.deposit(5, 20);     // return true
bank.transfer(3, 4, 15); // return false
bank.withdraw(10, 50);   // return false
*/

#include <iostream>
#include <vector>

using namespace std;

class Bank {
public:
  int n;
  vector<long long> balance;

  Bank(vector<long long> &balance) {
    n = balance.size();
    this->balance = balance;
  }

  bool transfer(int account1, int account2, long long money) {
    account1 -= 1;
    account2 -= 1;

    if (account1 < 0 || account2 < 0)
      return false;
    if (account1 >= n || account2 >= n)
      return false;
    if (balance[account1] < money)
      return false;

    balance[account1] -= money;
    balance[account2] += money;
    return true;
  }

  bool deposit(int account, long long money) {
    account -= 1;

    if (account < 0 || account >= n)
      return false;

    balance[account] += money;
    return true;
  }

  bool withdraw(int account, long long money) {
    account -= 1;

    if (account < 0 || account >= n)
      return false;
    if (balance[account] < money)
      return false;

    balance[account] -= money;
    return true;
  }
};

int main() {
  vector<long long> balance = {10, 100, 20, 50, 30};
  Bank bank(balance);

  cout << boolalpha;
  cout << bank.withdraw(3, 10) << endl;    // true (account 3: 20 -> 10)
  cout << bank.transfer(5, 1, 20) << endl; // true (account 5: 30 -> 10, account 1: 10 -> 30)
  cout << bank.deposit(5, 20) << endl;     // true (account 5: 10 -> 30)
  cout << bank.transfer(3, 4, 15) << endl; // false (account 3 only has 10)
  cout << bank.withdraw(10, 50) << endl;   // false (account 10 does not exist)

  return 0;
}

/**
 * Your Bank object will be instantiated and called as such:
 * Bank* obj = new Bank(balance);
 * bool param_1 = obj->transfer(account1,account2,money);
 * bool param_2 = obj->deposit(account,money);
 * bool param_3 = obj->withdraw(account,money);
 */
