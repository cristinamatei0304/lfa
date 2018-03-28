#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
using namespace std;


class element
{
private:
	int nr;
	vector<string> vect;
public:
	friend istream& operator>>(istream&, element&);
	friend ostream& operator<<(ostream&, element&);

	int get_nr(){ return nr; }
	int pozitie(string);
	bool parcurgere( vector<string>, int, string, vector< vector<string> >, element, element );
	string elem_vect(int poz){ return vect[poz]; }
};


istream& operator>>( istream &x, element &p )
{
	x >> p.nr;
	string s;
	for ( int i = 0; i < p.nr; i++ )
	{
		x >> s;
		p.vect.push_back(s);
	}
	return x;
}

ostream& operator<<( ostream &x, element &p )
{
	vector <string> :: iterator i;
	for ( i = p.vect.begin(); i != p.vect.end(); i++ )
		x << *i<<' ';
	return x;
}

int element::pozitie( string s )
{
	vector <string> :: iterator i;
	int nr = 0;
	for ( i = vect.begin(); i != vect.end(); i++ )
	{
		if ( (*i) == s )
			return nr;
		nr++;
	}
	return -1;

}

bool element::parcurgere( vector<string> test, int poz, string stare_curenta, vector< vector<string> > mat_stare, element stari, element final )
{
	int pozi = stari.pozitie(stare_curenta);
	int cuvant = (*this).pozitie( test[poz] );
	if ( poz <= test.size()-1 && cuvant == -1 )
		return false;
	if ( mat_stare[pozi][cuvant] == "!" )
		return false;
	if ( poz <= test.size() - 1 )
		return (*this).parcurgere(test, poz+1, mat_stare[pozi][cuvant], mat_stare, stari, final );
	if ( final.pozitie(stare_curenta) == -1 )
		return false;
	return true;
}



int main()
{
	ifstream in("automat.in");
	element stari, final, alfabet;
	string stare_init;
	in >> stari;
	in >> stare_init;
	in >> final;
	in >> alfabet;

	int nr_functii;
	in >> nr_functii;
	vector< vector<string> > matrice_functii(nr_functii,vector<string>(alfabet.get_nr()+1));
	for ( int i = 0; i < nr_functii; i++ )
		for ( int j = 0; j <= 2; j++ )
			in >> matrice_functii[i][j];

	vector< vector<string> > mat_stare(stari.get_nr()+1,vector<string>(alfabet.get_nr()+1));
	
	for ( int i = 0; i < stari.get_nr(); i++ )
		for ( int j = 0; j < alfabet.get_nr(); j++ )
			mat_stare[i][j] = "!";

	/*for( int i = 0; i < nr_functii; i++ )
	{
		for ( int j = 0; j < alfabet.get_nr()+1; j++ )
			cout << matrice_functii[i][j]<<' ';
		cout <<'\n';
	}*/

	for ( int i = 0; i < nr_functii; i++ )
	{
		int poz_start = stari.pozitie(matrice_functii[i][0]);
		int cost = alfabet.pozitie(matrice_functii[i][2]);
		//cout << poz_start<<' '<<cost<<'\n';
		mat_stare[poz_start][cost] = matrice_functii[i][1];
	}


	int nr_teste, nr_curent = 0, nr_cuvinte;
	in >> nr_teste;
	vector<string> test;
	string s;
	while( in >> nr_cuvinte )
	{
		nr_curent++;
		for ( int i = 0; i < nr_cuvinte; i++ )
		{
			in >> s;
			test.push_back(s);
		}
		cout << "Test: ";
		vector <string> :: iterator i;
		for ( i = test.begin(); i != test.end(); i++ )
			cout << *i<<' ';
		bool raspuns = alfabet.parcurgere(test,0, stare_init, mat_stare, stari, final );
		if ( raspuns == true )
			cout <<"True\n";
		else cout <<"False\n";
		for ( int i = 0; i < nr_cuvinte; i++ )
			test.pop_back();
	}

	if ( nr_curent < nr_teste )
	{
		if ( final.pozitie(stare_init) == -1 )
			cout <<"Cuvant: λ\nFalse\n";
		else cout <<"Cuvant: λ\nTrue\n";

	}


	return 0;
}