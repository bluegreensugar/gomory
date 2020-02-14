// gomory.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <math.h> 
#include <vector>
using namespace std;

void print(double** mass, string** massx, int n, int m)
{
	cout << endl;
	cout << "mass: " << endl;
	cout << massx[0][0] << "\t";
	for (int i = 1; i < m + 1; i++)
	{
		cout << massx[0][i] << "\t";
	}
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		cout << massx[i + 1][0] << "\t ";

		for (int j = 0; j < m; j++)
		{
			cout << (round(float(mass[i][j]) * 100)) / 100 << "\t ";
		}
		cout << endl;
	}
}
bool proverka(double** mass, bool& w, int n, int m)
{
	w = false;
	for (int i = 0; i < m; i++)
	{

		if (mass[n - 1][i] < 0)
		{
			w = true;
		}
	}
	return w;
}
int RazreshStolbec(double** mass, int n, int m, double& min, int razresh_stl)
{
	min = mass[n - 1][0];
	for (int i = 1; i < m; i++)
	{
		if (mass[n - 1][i] < min)
		{
			min = mass[n - 1][i];
			razresh_stl = i;
		}
	}
	return razresh_stl;
}
int RazreshStroka(double** mass, int n, int m, double& min, int razresh_str, int razresh_stl, bool& poloz)
{
	min = mass[0][0] / mass[0][razresh_stl];
	razresh_str = 0;
	poloz = false;
	for (int i = 1; i < n - 1; i++)
	{

		if (mass[i][razresh_stl] > 0)
		{
			poloz = true;
			if (mass[i][0] / mass[i][razresh_stl] <= min)
			{
				min = mass[i][0] / mass[i][razresh_stl];
				razresh_str = i;
			}

		}

	}
	return razresh_str;
}
void Zamena_massx(string** massx, int razresh_str, int razresh_stl)
{
	string temp;
	temp = massx[0][razresh_stl + 1];
	//massx[0][razresh_stl + 1] = massx[razresh_str + 1][0];
	massx[razresh_str + 1][0] = temp;
}
void Izmenenie_tabl(double** mass, int razresh_str, int razresh_stl, double razresh_elem, int n, int m)
{
	double temp;
	for (int i = 0; i < m; i++)
	{
		mass[razresh_str][i] = mass[razresh_str][i] / razresh_elem;

	}
	for (int j = 0; j < n; j++)
	{
		if (j != razresh_str)
		{
			double umnoz = (-1 * mass[j][razresh_stl]);
			for (int i = 0; i < m; i++)
			{
				temp = mass[razresh_str][i];
				temp = temp * umnoz;
				mass[j][i] = mass[j][i] + temp;
			}
		}
	}
}
int gomori(double** mass,string** massx, int n,int  m, vector <string>& nebaz)
{
	
		for (int j = 0; j < m; j++)
		{
			
			mass[n - 2][j] = 0;
		
		}
	
	
	for (int i = 0; i < n; i++)
	{
		mass[n - 1][i] = -mass[n - 1][i];
	}

	int count;

	
	string str;
	int stroka=-1;
	double max_drob=0, celoe;
	/*for (int i = 0; i < count; i++)
	{
		cin >> str;
		nebaz.push_back(str);
	}*/
	count = nebaz.size();
	for (int i = 1; i < n-1; i++)
	{
		for (int q = 0; q < count; q++)
		{
			if (massx[i][0] == nebaz[q])
			{
				
				 if((max_drob!= (mass[i-1][0] - floor(mass[i-1][0])))&& (max_drob < ( mass[i-1][0]-floor (mass[i-1][0]))) )
				{
					max_drob = mass[i-1][0] - floor(mass[i-1][0]);
					stroka = i-1;
				}

			}

		}
		
	}
	cout << "maaaz " << max_drob<< " " <<stroka;
	for (int i = 0; i <m; i++)
	{
		if (mass[stroka][i] >= 0)
		{
			if (mass[stroka][i] - floor(mass[stroka][i]) == 0)
			{
				mass[stroka][i]=0;
			}
			else mass[n - 2][i] = -(mass[stroka][i] - floor(mass[stroka][i]));
		}
		else
		{
			for (int j = n-1 ; j >= stroka ; j--)
			{   
				for (int k = m-1; k >= 0; k--)
				{
					
					if (mass[j][k] < 0)
					{
						if  ((floor(mass[j][k]) == mass[j][k]) || ((mass[j][k] - ceil(mass[j][k])) < -0.99909))
						{
							mass[n - 2][i] = -(mass[stroka][i] - mass[j][k]);
						}

					}
					

				}
			}
		}
	}
	mass[n - 2][m - 1] = 1;
	

	return stroka;

}
//void copia()
void zapolnenie_newmass(double** mass, double** mass1,  string** massx,string** massx1, int& n, int& m)
{
	
	for (int i = 0; i < n - 2; i++)
	{
		for (int j = 0; j < m - 1; j++)
		{
			mass[i][j] = mass1[i][j];

		}
		
	}
	for (int i = 0; i < m-1; i++)
	{
		mass[n - 1][i] = mass1[n - 1][i];
	}
	for (int i = 0; i < n; i++)
	{
		if (i == n - 2) mass[i][m - 1] = 1;
		else mass[i][m - 1] = 0;
	}

	
	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < m + 1; j++)
		{
			if ((i == 0) || (j == 0))
			{
				massx[i][j] = massx1[i][j];
			}
		}
	}
	for (int j = 0; j < m; j++)
	{

		mass[n - 2][j] = 0;

	}
	cout << "enter new baziz: " << endl;
	cin >> massx[n - 1][0];
	massx[0][m] = massx[n - 1][0];

}
void newmass(double** mass,double**mass1, string** massx, string**massx1 , int n, int m) 
{
	
	
	
	for (int i = 0; i < n + 1-2; i++)
	{
		for (int j = 0; j < m + 1-1; j++)
		{
			if ((i == 0) || (j == 0))
			{

				massx1[i][j] = massx[i][j];
			}
			else mass1[i][j] = 0;
		}
	}
	massx1[n][0] = massx[n-1][0];
	
	for (int i = 0; i < n-2; i++)
	{
		for (int j = 0; j < m-1; j++)
		{
			mass1[i][j] = mass[i][j];

		}
		
	}
	for (int i = 0; i < m-1; i++)
	{
		mass1[n - 1][i] = mass[n - 2][i];
	}
}
bool proverka_gomori(double** mass, string** massx, int n, int  m, vector <string> & nebaz)
{
	setlocale(LC_ALL, "ru");
	cout << "Введите колличество и сами не базисные перемнные: ";
	int count;
	cin >> count;
	bool flag = false;
	string str;
	int stroka = -1;
	double max_drob = 0, celoe;
	for (int i = 0; i < count; i++)
	{
		cin >> str;
		nebaz.push_back(str);
	}
	while (count)
	{
		for (int i = 0; i < count; i++)
		{
			for (int j = 1; j < n; j++)
			{
				if (nebaz[i] == massx[j][0])
				{
					if (mass[j - 1][0] - floor(mass[j - 1][0]) != 0)
					{
						flag = true;
					}
				}

			}
			count--;
			
		}
	}
	return flag;
}
int razresh_stolb_gomori(double** mass,  int n, int  m)
{
	int  stolb =0;
	double min = mass[n - 1][1] / mass[n - 2][1];
	for (int i = 2; i <m-1; i++)
	{
		if (min > mass[n-1][i] / mass[n-2][i])
		{
			min = mass[n - 1][i] / mass[n - 2][i];
			stolb = i;
		}
	}
	return stolb;
}

int main()
{
	cout << " enter n and m" << endl;
	int n, m;
	cin >> n >> m;
	double** mass = new double* [n];
	for (int i = 0; i < n; i++)
	{
		mass[i] = new double[m];
	}
	cout << "enter mass (Svobodnie chleni, ,bazisnie, x1..." << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << "elem [" << i << "][" << j << "]";
			cin >> mass[i][j];
		}
	}
	string** massx = new string * [n + 1];
	for (int i = 0; i < n + 1; i++)
	{
		massx[i] = new string[m + 1];
	}
	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < m + 1; j++)
		{
			if ((i == 0) || (j == 0))
			{
				cout << "elem x [" << i << "][" << j << "] :";
				cin >> massx[i][j];
			}
		}
	}

	print(mass, massx, n, m);
	bool w = true;
	w = proverka(mass, w, n, m);
	if (!w)
	{
		cout << "net otric elem" << endl;
	}
	double min = 0;
		int razresh_stl = 0, razresh_str = 0;
	double razresh_elem = 0;
	while (w == true)
	{
		razresh_stl = RazreshStolbec(mass, n, m, min, razresh_stl);

		bool poloz = false;
		razresh_str = RazreshStroka(mass, n, m, min, razresh_str, razresh_stl, poloz);
		if (poloz == false)
		{
			cout << "reshenii net!!" << endl;
			break;
		}
		razresh_elem = mass[razresh_str][razresh_stl];
		cout << endl;
		cout << "razreshaushii element: " << razresh_elem << endl;
		cout << "razresh str i stl: " << razresh_str << " " << razresh_stl << endl;
		Zamena_massx(massx, razresh_str, razresh_stl);
		Izmenenie_tabl(mass, razresh_str, razresh_stl, razresh_elem, n, m);
		print(mass, massx, n, m);
	
		w = proverka(mass, w, n, m);
		if (!w)
		{
			cout << "net otric elem" << endl;
		}
		

	}
	vector <string> nebaz;
	w = proverka_gomori(mass, massx, n, m, nebaz);
	while (w)
	{
		cout << "---------------------------" << endl;
		n++;
		m++;
		string** massx1 = new string * [n + 1];
		for (int i = 0; i < n + 1; i++)
		{
			massx1[i] = new string[m + 1];
		}
		double** mass1 = new double* [n];
		for (int i = 0; i < n; i++)
		{
			mass1[i] = new double[m];
		}
		newmass(mass, mass1, massx, massx1, n, m);

		mass = new double* [n];
		for (int i = 0; i < n; i++)
		{
			mass[i] = new double[m];
		}
		massx = new string * [n + 1];
		for (int i = 0; i < n + 1; i++)
		{
			massx[i] = new string[m + 1];
		}
		zapolnenie_newmass(mass, mass1, massx, massx1, n, m);
		gomori(mass, massx, n, m, nebaz);
		print(mass, massx, n, m);
		cout << endl;
		cout << " F = " << mass[n - 1][0];
		razresh_stl = razresh_stolb_gomori(mass, n, m);
		razresh_str = n - 2;
		cout << endl;
		razresh_elem = mass[razresh_str][razresh_stl];
		cout << razresh_stl << " " << razresh_str << endl;
		Zamena_massx(massx, razresh_str, razresh_stl);
		Izmenenie_tabl(mass, razresh_str, razresh_stl, razresh_elem, n, m);
		print(mass, massx, n, m);

		w = proverka_gomori(mass, massx, n, m, nebaz);
		if (!w)
		{
			cout << "net otric elem" << endl;
		}
	}
	cout << "end";
	

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
