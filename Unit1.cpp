//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <fstream>
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include "ElectronicsStore.h"
TForm1 *Form1;
Store _es;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        ComboBox1->ItemIndex =0;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button5Click(TObject *Sender)  //searchButton
{
        if(Button5->Caption=="Поиск" && CheckData(true))
        {
                vector<bool> vect;
                int id ;
                string name, category, color;
                double price, weight;
                bool available = CheckBox1->Checked;
                if(CheckBox2->Checked==true&&Edit1->Text!=""){vect.push_back(true); id = StrToInt(Edit1->Text);}else vect.push_back(false);
                if(CheckBox3->Checked){ vect.push_back(true); name = Edit2->Text.c_str(); } else vect.push_back(false);
                if(CheckBox4->Checked){ vect.push_back(true); category = Edit3->Text.c_str(); } else vect.push_back(false);
                if(CheckBox5->Checked&&Edit4->Text!=""){ vect.push_back(true); price = StrToFloat(Edit4->Text);  } else vect.push_back(false);
                if(CheckBox6->Checked&&Edit5->Text!=""){ vect.push_back(true); weight = StrToFloat(Edit5->Text); } else vect.push_back(false);
                if(CheckBox7->Checked){ vect.push_back(true); color = ComboBox1->Text.c_str();} else vect.push_back(false);
                if(CheckBox8->Checked){ vect.push_back(true); } else vect.push_back(false);
                if(_es.getCount()>0)
                {
                        Button5->Caption="ОК";
                        vector<int> founded = _es.Found(id,name,category,price,weight,color,available,vect);
                        ListBox1->Items->Clear();
                        if(founded.size()!=0)
                        {
                                ListBox1->Items->Add("Найденные товары(для возврата ко всему списку нажмите 'ОК'):");
                                for(int i=0;i<founded.size();i++)
                                        ListBox1->Items->Add(_es.GetShortInfo(founded[i]).c_str());
                        }
                        else ListBox1->Items->Add("Не было найдено ни одного товара(для возврата ко всему списку нажмите 'ОК')");
                }
                else ShowMessage("Элементов нет. Где искать-то?");
        }
        else if (Button5->Caption=="ОК")
        {
                Button5->Caption="Поиск";
                PrintList();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender) //addButton
{
        if(CheckData(false))
        {
                _es.AddNewElement(false, _es.getCount(),StrToInt(Edit1->Text),Edit2->Text.c_str(),Edit3->Text.c_str(),StrToFloat(Edit4->Text),StrToFloat(Edit5->Text),
                            ComboBox1->Text.c_str(),CheckBox1->Checked);
                PrintList();
                Clear();
                ShowMessage("Товар добавлен");
                Button8->Enabled = True;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender) //removeButton
{
        int i = ListBox1->ItemIndex;
        if(i>=0)
        {
                _es.Remove(i);
                ListBox1->Items->Clear();
                for(int i=0;i<_es.getCount();i++)
                        ListBox1->Items->Add(_es.GetShortInfo(i).c_str());
                Edit1->Clear();
                Edit2->Clear();
                Edit3->Clear();
                Edit4->Clear();
                Edit5->Clear();
                ComboBox1->ItemIndex =0;
                CheckBox1->Checked = true;
                ListBox1->ItemIndex = -1;
                ShowMessage("Товар удалён");
                Button8->Enabled = True;
        }
        else ShowMessage("Выберите элемент");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender) //correctButton
{
        int i = ListBox1->ItemIndex;
        if(i>=0 && CheckData(false))
        {
                _es.Correct(i,StrToInt(Edit1->Text),Edit2->Text.c_str(),Edit3->Text.c_str(),StrToFloat(Edit4->Text),StrToFloat(Edit5->Text),
                            ComboBox1->Text.c_str(),CheckBox1->Checked);
                ListBox1->Items->Clear();
                for(int i=0;i<_es.getCount();i++)
                        ListBox1->Items->Add(_es.GetShortInfo(i).c_str());
                Edit1->Clear();
                Edit2->Clear();
                Edit3->Clear();
                Edit4->Clear();
                Edit5->Clear();
                ComboBox1->ItemIndex =0;
                CheckBox1->Checked = true;
                ListBox1->ItemIndex = -1;
                ShowMessage("Информация о товаре отредактирована");
                Button8->Enabled = True;
        }
        else ShowMessage("Выберите элемент");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ListBox1Click(TObject *Sender)//clickOnListBox
{
        int i = ListBox1->ItemIndex;
        if(i>=0)
        {
                Edit1->Text = _es.getID(i);
                Edit2->Text = _es.getName(i).c_str();
                Edit3->Text = _es.getCategory(i).c_str();
                Edit4->Text = _es.getPrice(i);
                Edit5->Text = _es.getWeight(i);
                ComboBox1->Text = _es.getColor(i).c_str();
                CheckBox1->Checked = _es.getAvailable(i);
        }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender) //clearButton
{
        Clear();
}

void TForm1::Clear()
{
        Edit1->Clear();
        Edit2->Clear();
        Edit3->Clear();
        Edit4->Clear();
        Edit5->Clear();
        ComboBox1->ItemIndex =0;
        CheckBox1->Checked = true;
        ListBox1->ItemIndex = -1;
}

bool TForm1::CheckData(bool search)
{
        bool checked = false;
        if(!search || (search && CheckBox2->Checked))
        {
                checked=true;
                if(Edit1->Text == "")
                {
                        ShowMessage("Ошибка. Введите идентификатор");
                        return false;
                }
                try
                {
                       int id = StrToInt(Edit1->Text);
                }
                catch(int err_code)
                {
                        ShowMessage("Ошибка. Неправильный идентификатор. Ожидалось целое число.");
                        return false;
                }
        }
        if(!search || (search && CheckBox3->Checked))
        {
                if(Edit2->Text == "")
                {
                        ShowMessage("Ошибка. Введите название");
                        return false;
                }
        }
        if(!search || (search && CheckBox4->Checked))
        {
                if(Edit3->Text == "")
                {
                        ShowMessage("Ошибка. Введите категорию");
                        return false;
                }
        }

        if(!search || (search && CheckBox5->Checked))
        {
                if(Edit4->Text == "")
                {
                       ShowMessage("Ошибка. Введите цену");
                       return false;
                }
                try
                {
                        double price = StrToFloat(Edit4->Text);
                        if(price<0)
                        {
                                ShowMessage("Ошибка. Цена не может быть отрицательной");
                                return false;
                        }
                }
                catch(int err_code)
                {
                        ShowMessage("Ошибка. Неправильная цена. Ожидалось число с плавающей точкой. Попробуйте заменить точку на запятую или наоборот.");
                        return false;
                }
        }
        if(!search || (search && CheckBox6->Checked))
        {
                if(Edit5->Text == "")
                {
                        ShowMessage("Ошибка. Введите вес");
                        return false;
                }
                try
                {
                        double weight = StrToFloat(Edit5->Text);
                        if(weight<0)
                        {
                                ShowMessage("Ошибка. Вес не может быть отрицательным");
                                return false;
                        }
                }
                catch(int err_code)
                {
                        ShowMessage("Ошибка. Неправильный вес. Ожидалось число с плавающей точкой. Попробуйте заменить точку на запятую или наоборот.");
                        return false;
                }
        }
        if(!search || (search && CheckBox7->Checked))
        {
                if(ComboBox1->Text == "")
                {
                        ShowMessage("Ошибка. Введите цвет");
                        return false;
                }
        }
        if(search && !checked)
        {
                ShowMessage("Выберите хотя бы один параметр для поиска или проверьте поля для поиска");
                return false;
        }
        return true;
}

void TForm1::PrintList()
{
        ListBox1->Items->Clear();
        for(int i=0;i<_es.getCount();i++)
                ListBox1->Items->Add(_es.GetShortInfo(i).c_str());
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ListBox1DblClick(TObject *Sender)  //doubleClickOnListBox
{
        int i = ListBox1->ItemIndex;
        if(i>=0) ShowMessage(_es.GetFullInfo(i).c_str());
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button2Click(TObject *Sender)//readFromFile
{
        string line;
        std::ifstream in(Edit6->Text.c_str());
        if (in.is_open())
        {
                _es.Clear();
                int counter = 0;
                int id ;
                string name, category, color;
                double price, weight;
                bool available = false;
                while (getline(in, line))
                {
                        Edit7->Text = line.c_str();
                        switch(counter)
                        {
                                case 0 : { id=StrToInt(line.c_str()); break;}
                                case 1 : { name=line.c_str();break;}
                                case 2 : { category=line.c_str();break;}
                                case 3 : { price=StrToFloat(line.c_str());break;}
                                case 4 : { weight=StrToFloat(line.c_str());break;}
                                case 5 : { color=line.c_str();break;}
                                case 6 : { if(line=="1") available=true; else available=false; break;}
                        }
                        counter++;
                        if(counter==8)
                        {
                                counter=0;
                                _es.AddNewElement(true, _es.getCount(),id,name,category,price,weight,color,available);
                        }
                }
                PrintList();
                Button8->Enabled = True;
                ShowMessage("Товары прочитаны из файла!");
        }
        in.close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender) //writeToFile
{
        if(_es.getCount()>0)
        {
                std::ofstream out;
                out.open(Edit6->Text.c_str());
                if (out.is_open())
                {
                        for(int i=0;i<_es.getCount();i++)
                        {
                                out << _es.getID(i) << std::endl;
                                out << _es.getName(i) << std::endl;
                                out << _es.getCategory(i) << std::endl;
                                out << _es.getPrice(i) << std::endl;
                                out << _es.getWeight(i) << std::endl;
                                out << _es.getColor(i) << std::endl;
                                out << _es.getAvailable(i) << std::endl;
                                out << "-------";
                                if(i!=_es.getCount()-1) out << std::endl ;
                        }
                        ShowMessage("Товары записаны в файл!");
                }
        }
        else ShowMessage("Нет ни одного элемента. Сохранять нечего");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)//cancelButton
{
        _es.Cancel();
        PrintList();
        Button8->Enabled = False;
}
//---------------------------------------------------------------------------

