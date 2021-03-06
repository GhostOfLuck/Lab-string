/*Задан текстовый файл input.txt. Требуется определить строки этого
 файла, содержащие максимальную по длине подстроку, состоящую только из
 цифр. Если таких строк несколько, найти первые 10. Результат вывести на
 консоль в форме, удобной для чтения. */

#include <iostream>
#include "pch.h"
#include <string>
#include <fstream>
#define _CRT_SECURE_NO_WARNINGS
	using namespace std;

	//ifstream fin("input.txt");

	//void chek_in() {
	//	if (!fin)
	//		throw "Входной файл не открыт";
	//}

	//void chek_empty() {
	//	string a;
	//	if (!(fin >> a))
	//		throw "Входной файл пуст";
	//	else {
	//		fin.clear();
	//		fin.seekg(0);
	//	}
	//}


	bool proverka(const string& s)
	{
		return(strspn(s.c_str(), "0123456789") == s.size());
	}

	bool chek(string a, const string s[], int c)
	{
		int k, n = 0;
		for (int i = 0; i < c; i++)
		{
			int k = a.find(s[i]);
			if (k != -1)
				return true;
		}
		return false;
	}

	int main()
	{
		FILE* f1 = fopen("input.txt", "r");
		FILE* f2 = fopen("output.txt", "w");
		const int size = 1000;
		string a,s=" ";
		char a1[size];
		int max = 0, count = 0;
		
		if (f1 == NULL)
		{
			cout << "No input file" << endl;
			return 0;
		}
		if (f2 == NULL)
		{
			cout << "You can't create a file" << endl;
			fclose(f1);
			system("pause");
			return 0;
		}
		fgets(a1, size, f1);
		a = string (a1);
		if (proverka(a))
		{
			if (a.length() == max)
			{
				s += a + " ";
				count++;
			}
			if (a.length() > max)
			{
				max = a.length();
				s.clear();
				s = a + " ";
				count = 1;
			}
		}

		while (!feof(f1))
		{
			fgets(a1, size, f1);
			a = string (a1);
			if (proverka(a))
			{
				if (a.length() == max)
				{
					s += a + " ";
					count++;
				}
				if (a.length() > max)
				{
					max = a.length();
					s.clear();
					s = a + " ";
					count = 1;
				}
			}
		}
		fclose(f1);
		f1 = fopen("input.txt", "r");
		string *stroka = new string[count];
		int k = 0, i = 0, nom;
		while ((k = s.find_first_not_of(" ", k)) != -1)
		{
			nom = s.find_first_of(" ", k);
			stroka[i] = s.substr(k, nom - k);
			i++;
			k = nom;
		}
		int c = count;
		count = 0;
		while (!feof(f1) && count < 10)
		{
			fgets(a1, size, f1);
			a = string (a1);
			if (chek(a, stroka, c))
			{
				cout << a << endl;
				count++;
			}
		}
		if (count == 0)
			cout << "Строк с цифрами нет" << endl;
		delete[] stroka;
		fclose(f1);
		system("pause");
	}