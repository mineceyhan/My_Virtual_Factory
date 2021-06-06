
 // Mine CEYHAN
 //Date : 28.05.2021
 // Development Enviorement : Visual Studio 2019

#include <iostream>
#include <fstream>
#include <string>
#include<vector>

using namespace std;

void setup_durations(string s, vector<int>  temp, vector<vector<int>>& gecisler, vector<int>& kurulum)
{
	string del = ";";
	int i = 0;
	int start = 0;
	int end = s.find(del);
	while (end != -1) {
		string tok1 = s.substr(start, end - start);
		temp.push_back(stoi(tok1));
		start = end + del.size();
		end = s.find(del, start);
		i++;
	}
	gecisler.push_back(temp);
	temp.clear();
	string tok = s.substr(start, end - start);
	kurulum.push_back(stoi(tok));
}

void orders(string s, vector<int> temp, vector<vector<int>>& order_temp, vector<int>& son_teslim)
{
	string del = ";";
	int i = 0;
	int start = 0;
	int end = s.find(del);
	while (end != -1) {
		string tok1 = s.substr(start, end - start);
		temp.push_back(stoi(tok1));
		start = end + del.size();
		end = s.find(del, start);
		i++;
	}
	order_temp.push_back(temp);
	temp.clear();
	string tok = s.substr(start, end - start);
	son_teslim.push_back(stoi(tok));
}

int main() {
	vector<int>  temp;
	vector<int>  temp2;
	vector<int>  kurulum;
	vector<vector<int>> gecisler;
	vector<vector<int>>  order_temp;
	vector<int> siparis_kodu;
	vector<int> is_uzunlugu;
	vector<int> islem_kodu;
	vector<int> son_teslim;

	vector<int> siparis_kodubasarili;
	vector<int> is_uzunlugubasarili;
	vector<int> islem_kodubasarili;
	vector<int> son_teslimbasarili;

	vector<int> siparis_kodubasarisiz;
	vector<int> is_uzunlugubasarisiz;
	vector<int> islem_kodubasarisiz;
	vector<int> son_teslimbasarisiz;


	vector<int> order_kurulum;
	order_kurulum.push_back(0); // BAÞLANGIÇ DA KURULUM SÜRESÝ YOKTUR.
	vector<int>  islemhizi;
	vector<int>  islemkodu;
	int toplamdak = 0;
	int toplamdak1 = 0;

	ifstream  operations("Operations.txt");
	string textline;
	islemhizi.push_back(0);    //0. ÝNDÝSLERÝNE  HERHANGÝ BÝR DEÐER ATIYORUM. ÝÞLEM KODU  VE VECTOR ÝNDÝSÝNÝN AYNI SAYIYI TUTMASI ÝÇÝN
	islemkodu.push_back(0);
	while (getline(operations, textline)) {

		string kod = textline.substr(0, textline.find(";"));
		string hiz = textline.substr(textline.find(";") + 1, textline.length());
		islemkodu.push_back(stoi(kod));
		islemhizi.push_back(stoi(hiz));
	}

	operations.close();
	ifstream  setup_duration("SetupDuration.txt");
	string textline1;
	while (getline(setup_duration, textline1)) {
		setup_durations(textline1, temp, gecisler, kurulum);
	}
	setup_duration.close();
	ifstream  order("Orders.txt");
	string textline2;
	while (getline(order, textline2)) {
		orders(textline2, temp, order_temp, son_teslim);
	}
	order.close();
	for (unsigned int k = 0; k < order_temp.size(); k++) {
		siparis_kodu.push_back(order_temp[k][0]);
		is_uzunlugu.push_back(order_temp[k][1]);
		islem_kodu.push_back(order_temp[k][2]);
	}

	for (unsigned int i = 0; i < islem_kodu.size(); i++)
	{
		for (unsigned int j = 0; j < islem_kodu.size(); j++)
		{
			if (islem_kodu[i] < islem_kodu[j]) {
				int tmp, temp, temp2, temp3, temp4;
				temp = son_teslim[j];
				temp2 = siparis_kodu[j];
				temp3 = is_uzunlugu[j];
				temp4 = islem_kodu[j];
				son_teslim[j] = son_teslim[i];
				siparis_kodu[j] = siparis_kodu[i];
				is_uzunlugu[j] = is_uzunlugu[i];
				islem_kodu[j] = islem_kodu[i];
				son_teslim[i] = temp;
				siparis_kodu[i] = temp2;
				is_uzunlugu[i] = temp3;
				islem_kodu[i] = temp4;
			}
		}
	}
	for (unsigned int i = 0; i < siparis_kodu.size(); i++)
	{
		for (unsigned int k = i + 1; k < siparis_kodu.size(); k++)
		{
			if (k == i + 1) {
				for (unsigned int b = 0; b < gecisler.size(); b++)
				{
					if (islem_kodu[i] == gecisler[b][0] && islem_kodu[k] == gecisler[b][1])
						order_kurulum.push_back(kurulum[b]);
					else if (islem_kodu[i] == gecisler[b][1] && islem_kodu[k] == gecisler[b][0])
						order_kurulum.push_back(kurulum[b]);
				}
				if (islem_kodu[i] == islem_kodu[k])
					order_kurulum.push_back(0);
			}
		}
	}
	order_kurulum.push_back(0);

	int h2 = 0;
	int basarisiz = 0;

	for (int xx = 0;xx < 100 ;xx++) 
	{
		siparis_kodubasarili.clear();
		islem_kodubasarili.clear();
		is_uzunlugubasarili.clear();
		son_teslimbasarili.clear();
		siparis_kodubasarisiz.clear();
		islem_kodubasarisiz.clear();
		is_uzunlugubasarisiz.clear();
		son_teslimbasarisiz.clear();

		toplamdak = 0;
		h2 = 0;
		basarisiz = 0;
		for (unsigned int v = 0; v < siparis_kodu.size(); v++)
		{
			for (unsigned int j = 1; j < islemhizi.size(); j++)
			{
				if (islem_kodu[h2] == islemkodu[j]) {
					if ((son_teslim[h2] - toplamdak + is_uzunlugu[h2]) / islemhizi[j] < 0)
					{
						basarisiz++;
						siparis_kodubasarisiz.push_back(siparis_kodu[h2]);
						is_uzunlugubasarisiz.push_back(is_uzunlugu[h2]);
						islem_kodubasarisiz.push_back(islem_kodu[h2]);
						son_teslimbasarisiz.push_back(son_teslim[h2]);
					}
					else {
						toplamdak = toplamdak + order_kurulum[h2 + 1] + is_uzunlugu[h2] / islemhizi[j];

						siparis_kodubasarili.push_back(siparis_kodu[h2]);
						is_uzunlugubasarili.push_back(is_uzunlugu[h2]);
						islem_kodubasarili.push_back(islem_kodu[h2]);
						son_teslimbasarili.push_back(son_teslim[h2]);
					}
				}
			}
			h2++;
		}
		siparis_kodu.clear();
		islem_kodu.clear();
		is_uzunlugu.clear();
		son_teslim.clear();
		for (int x = 0;x < siparis_kodubasarisiz.size();x++)
		{
			siparis_kodu.push_back(siparis_kodubasarisiz[x]);
			islem_kodu.push_back(islem_kodubasarisiz[x]);
			is_uzunlugu.push_back(is_uzunlugubasarisiz[x]);
			son_teslim.push_back(son_teslimbasarisiz[x]);
		}
		for (int x = 0;x < siparis_kodubasarili.size();x++)
		{
			siparis_kodu.push_back(siparis_kodubasarili[x]);
			islem_kodu.push_back(islem_kodubasarili[x]);
			is_uzunlugu.push_back(is_uzunlugubasarili[x]);
			son_teslim.push_back(son_teslimbasarili[x]);
		}
	}

	h2 = 0;
	toplamdak = 0;

	ofstream fout("schedule.txt");

	for (unsigned int v = 0; v < siparis_kodu.size(); v++)
	{
		for (unsigned int j = 1; j < islemhizi.size(); j++)
		{
			if (islem_kodu[h2] == islemkodu[j]) {
				fout << toplamdak << ";" << islemkodu[j] << ";" << siparis_kodu[h2] << ";" << is_uzunlugu[h2];
				fout << ";" << order_kurulum[h2];
				if (son_teslim[h2] - toplamdak + is_uzunlugu[h2] / islemhizi[j] < 0)
				{
					siparis_kodubasarisiz.push_back(siparis_kodu[h2]);
					is_uzunlugubasarisiz.push_back(is_uzunlugu[h2]);
					islem_kodubasarisiz.push_back(islem_kodu[h2]);
					son_teslimbasarisiz.push_back(son_teslim[h2]);
				}
				else {
					toplamdak = toplamdak + order_kurulum[h2 + 1] + is_uzunlugu[h2] / islemhizi[j];

					siparis_kodubasarili.push_back(siparis_kodu[h2]);
					is_uzunlugubasarili.push_back(is_uzunlugu[h2]);
					islem_kodubasarili.push_back(islem_kodu[h2]);
					son_teslimbasarili.push_back(son_teslim[h2]);
				}
			}
		}
		h2++;
		fout << endl;
	}
	fout.close();

	return 0;
}
