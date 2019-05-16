#include <string.h>
#include <iostream>
#include <vector>

using namespace std;

class Store
{
private:
   vector<int> _ID;
   vector<double> _Price, _Weight;
   vector<string> _Name, _Category, _Color;
   vector<bool> _Available;
   int _lastAction, _lastIndex, _lastID;
   double _lastPrice, _lastWeight;
   string _lastName, _lastCategory, _lastColor;
   bool _lastAvailable;
   void SaveData(int index, int lastAction);
public:
   Store();
   int getCount();
   int getID(int);
   double getPrice(int);
   double getWeight(int);
   string getName(int);
   string getCategory(int);
   string getColor(int);
   bool getAvailable(int);
   void Clear();
   void Cancel();
   void Correct(int i, int id, string name, string category, double price, double weight, string color, bool available);
   void AddNewElement(bool readFromFile, int index, int id, string name, string category, double price, double weight, string color, bool available);
   void Remove(int i);
   string GetShortInfo(int i);
   string GetFullInfo(int i);
   vector<int> Found(int id, string name, string category, double price, double weight, string color, bool available, vector<bool> seachBy);
};
