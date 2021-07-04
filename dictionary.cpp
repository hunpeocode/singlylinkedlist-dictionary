#include<iostream>
#include<fstream>
#include<conio.h>
#include<windows.h>
#include<iomanip>
#include<cstring>

using namespace std;
struct world
{
	string tu;
	string nghia;
	string vidu;

};
struct dic
{
	world myWorld;
	dic *next;
};
dic *first, *last, *cur;
dic *searchWorld(string line);
void sort();
void add(dic *tuthem);
void read();
void write();
void inds();
void* nhaptu();
void deleteWorld(dic *tucanxoa);
dic *searchWorld(string line);
void xoatu();
void detailWorld(dic *tucantim);
void suaTu(dic *tucansua);
dic *nhaptucantra();
void tratu();
void gotoxy(short x,short y);
void chucnang();
void hienthi();
int main()
{
	read();
	hienthi();
	write();
	return 0;
}
void sort()
{
	dic *p = new dic;
	dic *q = new dic;
	dic *pmin = new dic;
	world min;
	for(p = first;p!= NULL;p = p->next)
	{
		pmin = p;
		min = pmin->myWorld;
		for(q = p->next; q!=NULL;q = q->next )
		{
			if(min.tu > q->myWorld.tu)
			{
				min = q->myWorld;
				pmin = q;
			}
		}
		pmin->myWorld = p->myWorld;
		p->myWorld = min;
	}
}
void add(dic *tuthem)
{
	if(tuthem == NULL) return;
	if(tuthem->myWorld.tu == "") return;
	if(last == NULL)
	{
		first = last = tuthem;
		tuthem->next = NULL;
	}
	else
	{
		last->next = tuthem;
		last = tuthem;
		tuthem->next = NULL;
	}
}
void read()
{
	ifstream fileIn("data.txt");
	if(fileIn.is_open())
	while(!fileIn.eof())
	{
		dic *tudien = new dic;
		getline(fileIn,tudien->myWorld.tu,'@');
		getline(fileIn,tudien->myWorld.nghia,'@');
		getline(fileIn,tudien->myWorld.vidu);
		add(tudien);
	}
	fileIn.clear();
}
void write()
{
	sort();
	ofstream fileOut("data.txt");
	cur = first;
		while(cur != NULL)
		{
			fileOut << cur->myWorld.tu << '@' << cur->myWorld.nghia << '@'<< cur->myWorld.vidu << endl ;
			cur = cur->next;
		}
	fileOut.close();
}
void inds()
{
	cout << endl;
	cur = first;
	while(cur!=NULL)
	{
		cout << setw(20) << left << cur->myWorld.tu;
		cout << setw(20) <<cur->myWorld.nghia << setw(10);
		cout << "Vi du: ";
		cout << cur->myWorld.vidu << endl;
		cur = cur->next;
	}
}

void* nhaptu()
{
	char key[1];
	int kt;
	do
	{
		cin.clear();
		dic *tunhap = new dic;
		cin.ignore();
		cout << "\nNhap tu: ";
		getline(cin,tunhap->myWorld.tu);
		if(tunhap->myWorld.tu == "")
		{
			cout << "Ban chua nhap tu";
			return NULL;
		}
		if(searchWorld(tunhap->myWorld.tu) != NULL)
			{
				cout << "Tu da ton tai";
			return NULL;
			}
		cout << "Nhap nghia: ";
		getline(cin,tunhap->myWorld.nghia);
		if(tunhap->myWorld.nghia == "")
		{
			cout << "Ban chua nhap nghia";
		}
		cout << "Nhap vi du: ";
		getline(cin,tunhap->myWorld.vidu);
		if(tunhap->myWorld.vidu == "")
		{
			cout << "Ban chua nhap vi du";
		}
		add(tunhap);
		cout << "Enter de tiep tuc?/Nhan phim bat ki de chon chuc nang khac ";
		cin.get(key,1);
		kt =(int)key[1];
	}while( kt == 13);
}
void deleteWorld(dic *tucanxoa)
{
	if(tucanxoa == first)
	{
		first = tucanxoa->next;
		delete tucanxoa;
		return;
	}
	else
	{
		cur = first;
		while(cur != NULL)
		{
			dic *p;
			if(cur->next == tucanxoa)
			{
				p = cur->next;
				if(p->next == NULL)
				{
					cur->next = NULL;
					delete p;
					last = cur;
					return;
				}
				else
				{
					cur->next = p->next;
					delete p;
					return;
				}
			}
			cur = cur->next;
		}

	}
	cout << "Khong xoa duoc tu";
	return;
}
dic *searchWorld(string line)
{
	cur = first;
	while(cur!= NULL)
	{
		if(cur->myWorld.tu == line)
			return cur;
		cur = cur->next;
	}
	return NULL;
}
void xoatu()
{
	string line;
	cout <<"Nhap tu can xoa: ";
	cin >> line;
	if(searchWorld(line) == NULL)
	{
		cout << "Khong thay tu";
		return;
	}
	cout <<"Ban muon xoa tu: "<<line <<" ?  (Enter de xoa)";
	int hitkey = getch();
	if(hitkey == 13)
		{
			deleteWorld(searchWorld(line));
			cout << "\nDa xoa tu: " << line << endl;
		}
	else cout << "Ban chua xoa tu.";
}
void detailWorld(dic *tucantim)
{
	if(tucantim == NULL)
		return;
	cout << tucantim->myWorld.tu << ":  " << tucantim->myWorld.nghia <<"\n";
	cout << tucantim->myWorld.vidu;
}
void suaTu(dic *tucansua)
{
	cin.ignore() ;
	cur = first;
	while(cur != NULL)
	{
		if(cur->myWorld.tu == tucansua->myWorld.tu)
		{
			cout << "Nhap lai tu: ";
			getline(cin,cur->myWorld.tu);
			cout << "Nhap lai nghia: ";
			getline(cin,cur->myWorld.nghia);
			cout << "Nhap vi du: ";
			getline(cin,cur->myWorld.vidu);
			return;
		}
		cur = cur->next;
	}
	cout << "Khong tim thay tu can xoa";
}
dic *nhaptucantra()
{
	string st;
	cout << "\nNhap tu can tra:";
	cin >> st;
	if (searchWorld(st)==NULL)
		{
			cout << "\nKhong tim duoc tu";
			return NULL;
		}
	else return searchWorld(st);
}
void tratu()
{
	detailWorld(nhaptucantra());
}
void gotoxy(short x,short y) 
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = {x, y};
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
void chucnang()
{
	gotoxy(99,2);
	cout << " 1: Xoa tu";
	gotoxy(100,3);
	cout << "2: Them tu";
	gotoxy(100,4);
	cout << "3: Sua tu";
	gotoxy(100,5);
	cout << "4: Tra tu";
	gotoxy(100,6);
	cout << "9: In danh sach";
	gotoxy(100,7);
	cout << "0: Thoat";
}
void hienthi()
{
	int key = 0;
	chucnang();
	gotoxy(1,1);
	do
	{
		cout << "\nChon chuc nang: ";
		cin >> key;
		switch(key)
		{
				case 1:						//1 xoa tu
					{
						system("cls");
						chucnang();
						gotoxy(1,1);
						xoatu();
						break;
					}
				case 2:						 // 2 them tu
					{
						system("cls");
						chucnang();
						gotoxy(1,1);
						nhaptu();
						break;
					}
				case 3: 						// 3 sua tu
					{
						system("cls");
						chucnang();
						gotoxy(1,1);
						string st;
						cout << "\nnhap tu can sua: ";
						cin >> st;
						suaTu(searchWorld(st));
						break;
					}
				case 4:						//4
					{
						system("cls");
						chucnang();
						gotoxy(1,1);
						detailWorld(nhaptucantra());
						cout << endl;
						break;
					}
				case 5:
					{
						sort();
						break;
					}
				case 9:						//9
					{
						system("cls");
						chucnang();
						gotoxy(1,1);
						inds();
						break;
					}
				default:
					{
						if(key!= 0)
							cout << "\nSai chuc nang";
						break;
					}
		}

	}while(key != 0);
}