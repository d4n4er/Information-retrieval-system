#include "ElectronicsStore.h"
#include <string>
#include <sstream>

Store::Store()
{
}

int Store::getCount()
{
        return _ID.size();
}


int Store::getID(int i)
{
        return _ID[i];
}

double Store::getPrice(int i)
{
        return _Price[i];
}

double Store::getWeight(int i)
{
        return _Weight[i];
}

string Store::getName(int i)
{
        return _Name[i];
}

string Store::getCategory(int i)
{
        return _Category[i];
}

string Store::getColor(int i)
{
        return _Color[i];
}

bool Store::getAvailable(int i)
{
        return _Available[i];
}

void Store::Clear()
{
        _ID.clear();
        _ID.clear();
        _Price.clear();
        _Weight.clear();
        _Name.clear();
        _Category.clear();
        _Color.clear();
        _Available.clear();
}

void Store::SaveData(int i, int lastAction)
{
        _lastAction = lastAction;
        _lastIndex = i;
        _lastID = _ID[i];
        _lastName = _Name[i];
        _lastCategory = _Category[i];
        _lastPrice = _Price[i];
        _lastWeight = _Weight[i];
        _lastColor = _Color[i];
        _lastAvailable = _Available[i];
}

void Store::Cancel()
{
        switch(_lastAction)
        {
                case 0: {
                //0 - cancel Adding
                Remove(_lastIndex);
                break;}
                case 1: {
                //1 - cancel Removing
                AddNewElement(false, _lastIndex, _lastID, _lastName, _lastCategory, _lastPrice, _lastWeight, _lastColor, _lastAvailable);
                break;}
                case 2: {
               //2 - cancel Correcting
                Correct(_lastIndex, _lastID, _lastName, _lastCategory, _lastPrice, _lastWeight, _lastColor, _lastAvailable);
                break;}
                 case 3: {
               //3 - cancel ReadingFromFile
                for(int i=getCount()-1;i>=0;i--)
                        Remove(i);
                break;}
        }
}

void Store::Correct(int i, int id, string name, string category, double price, double weight, string color, bool available)
{
        SaveData(i,2);
        _ID[i] = id;
        _Price[i] = price;
        _Weight[i] = weight;
        _Name[i] = name;
        _Category[i] = category;
        _Color[i] = color;
        _Available[i] = available;
}

void Store::AddNewElement(bool readFromFile, int index, int id, string name, string category, double price, double weight, string color, bool available)
{
        _ID.insert(_ID.begin()+index,id);
        _Price.insert(_Price.begin()+index,price);
        _Weight.insert(_Weight.begin()+index,weight);
        _Name.insert(_Name.begin()+index,name);
        _Category.insert(_Category.begin()+index,category);
        _Color.insert(_Color.begin()+index,color);
        _Available.insert(_Available.begin()+index,available);
        if(readFromFile) SaveData(getCount()-1, 3);
        else SaveData(getCount()-1, 0);
}

void Store::Remove(int index)
{
        SaveData(index,1);
        _ID.erase(_ID.begin() + index);
        _Price.erase(_Price.begin() + index);
        _Weight.erase(_Weight.begin() + index);
        _Name.erase(_Name.begin() + index);
        _Category.erase(_Category.begin() + index);
        _Color.erase(_Color.begin() + index);
        _Available.erase(_Available.begin() + index);
}

string Store::GetFullInfo(int i)
{
        string s = "����� �";
        ostringstream index;
        index << (i+1);
        string str = index.str();
        s += str +":\n";

        ostringstream id;
        id << _ID[i];
        str = id.str();
        s +=  "  ID: " + str + "\n";
        s += "  ��������: " + _Name[i] + "\n";
        s +=  "  ���������: " + _Category[i] + "\n";

        ostringstream price;
        price << _Price[i];
        str = price.str();
        s +=  "  ����: " + str + " ���.\n";

        if(_Available[i])
          s+="  �������: � �������\n";
        else s+="  �������:  ��� � �������\n";
        s +=  "  ����: " + _Color[i] + "\n";

        ostringstream weight;
        weight << _Weight[i];
        str = weight.str();
        s +=  "  ���: " + str + " ��.";

        return s;
}

string Store::GetShortInfo(int i)
{

        string s = "";
        ostringstream index;
        index << (i+1);
        string str = index.str();
        s += str;

        ostringstream id;
        id << _ID[i];
        str = id.str();
        s +=  ". ID: " + str;
        s += "; ��������: " + _Name[i];
        s +=  "; ���������: " + _Category[i];

        ostringstream price;
        price << _Price[i];
        str = price.str();
        s +=  "; ����: " + str + " ���.";

        if(_Available[i])
          s+="; � �������";
        else s+="; ��� � �������";
        s +=  "; " + _Color[i];

        ostringstream weight;
        weight << _Weight[i];
        str = weight.str();
        s +=  "; ���: " + str + " ��.";

        return s;
}


vector<int> Store::Found(int id, string name, string category, double price, double weight, string color, bool available, vector<bool> seachBy)
{
        /*searchById - 0
          searchByName - 1
          searchByCategory - 2
          searchByPrice -   3
          searchByWeight - 4
          searchByColor - 5
          searchByAvailable - 6 */
        vector<int> founded;
        for(int i=0;i<_ID.size();i++)
        {
                bool correct = true;
                if(seachBy[0] && correct)
                   if(id!=_ID[i]) correct = false;
                if(seachBy[1] && correct)
                   if(name!=_Name[i]) correct = false;
                if(seachBy[2] && correct)
                   if(category!=_Category[i]) correct = false;
                if(seachBy[3] && correct)
                   if(price!=_Price[i]) correct = false;
                if(seachBy[4] && correct)
                   if(weight!=_Weight[i]) correct = false;
                if(seachBy[5] && correct)
                   if(color!=_Color[i]) correct = false;
                if(seachBy[6] && correct)
                   if(available!=_Available[i]) correct = false;
                if(correct) founded.push_back(i);
        }
        return founded;
}
