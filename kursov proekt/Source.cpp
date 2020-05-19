#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<list>
#include<algorithm>
#include<ctime>
#include<stdlib.h>
#pragma warning(disable: 4996);

using namespace std;

fstream fp;

time_t t = time(NULL);
tm* timePtr = localtime(&t);


// klas edno
class CFilms {
private:
	string fname;
	string producer;
	int tiraj;
	int year;
	string genre;

public:

	// Ustanovqvane na chlen promenlivite 1.
	void setFilmName(const string s) { fname = s; }
	void setProducer(const string s) { producer = s; }
	void setGenre(const string s) { genre = s; }
	void setTiraj(const int i) { tiraj = i; }
	void setYear(const int i) { year = i; }

	string getFilmName() const { return fname; }
	string getProducer() const { return producer; }
	string getGenre() const { return genre; }
	int getTiraj() const { return tiraj; }
	int getYear() const { return year; }

	istream& input(istream& in) {
		in >> fname;
		in >> producer;
		in >> genre;
		in >> tiraj;
		in >> year;
		return in;
	}
	friend istream& operator>>(istream& in, CFilms& fil) { return fil.input(in); }

	// funkciq za izvejdane v izhoden potok konzola 2.
	ostream& outputConsole(ostream& out) {
		out << fname << endl;
		out << producer << endl;
		out << genre << endl;
		out << tiraj << endl;
		out << year << endl;
		return out;
	}
	friend ostream& operator<<(ostream& out, CFilms& fil) { return fil.outputConsole(out); }

	// funkciq za izvejdane v izhoden potok fail 2.
	void outputFile() {
		fp.open("film.txt", ios::in);
		if (!fp) {
			cout << endl << "******* ERROR *******";
			exit(1);
		}
		string line;
		int count = 0;

		if (fp.is_open())
		{
			int inside_count = 0;
			while (getline(fp, line))
			{
				inside_count++;
				if (inside_count == 5) {
					count++;
					inside_count = 0;
				}
			}
			fp.close();
		}

		fp.open("film.txt", ios::in);
		if (!fp) {
			cout << endl << "******* ERROR *******";
			exit(1);
		}
		string fs1, fs2, fs3;
		int fi1, fi2;

		if (fp.is_open()) {
			int inside_count = 0;
			while (count != inside_count) {
				getline(fp, fs1);
				getline(fp, fs2);
				getline(fp, fs3);
				getline(fp, line);
				fi1 = stoi(line);
				getline(fp, line);
				fi2 = stoi(line);
				CFilms fil(fs1, fs2, fs3, fi1, fi2);
				cout << fil;
				inside_count++;
			}
			fp.close();
		}
	}

	// podrazbirasht se konstruktor 1.
	CFilms() {
		fname = " ";
		producer = " ";
		genre = " ";
		tiraj = 0;
		year = 0;
	}

	// kopirasht konstruktor 2.
	CFilms(const CFilms& fil) {
		fname = fil.getFilmName();
		producer = fil.getProducer();
		genre = fil.getGenre();
		tiraj = fil.getTiraj();
		year = fil.getYear();
	}

	// ekspliciten konstruktor 3.
	CFilms(string nam, string pro, string gen, int tir, int yer) {
		fname = nam;
		producer = pro;
		genre = gen;
		tiraj = tir;
		year = yer;
	}

	// funkciq za validizirane na janra 1. 
	bool validateGenre(string s) {
		return (genre == s) ? true : false;
	}

	// funkciq za izchislqvane na vyzrastta na filma 2.
	int calculateAge() {
		return timePtr->tm_year - year;
	}

	// izvejdane na dannite za filma na printer 3.
	void sendToPrint() {
		ofstream print;
		print.open("LPT1");
		print << fname;
		print << producer;
		print << genre;
		print << tiraj;
		print << year;
		print.close();
	}


	// operator za prizvoqvane = 4.
	CFilms operator=(const CFilms& fil) {
		fname = fil.fname;
		producer = fil.producer;
		genre = fil.genre;
		tiraj = fil.tiraj;
		year = fil.year;
		return *this;
	}

	// logicheski operator, koito proverqva dali filma e ot tazi godina 5.
	bool operator!() { return (timePtr->tm_year != year) ? true : false; }

	// operator za sravnenie > (po tiraj) 6.
	bool operator>(const CFilms& fil) { return (tiraj > fil.getTiraj()) ? true : false; }

	// operator za syvpadenie == (po producenti) 7.
	bool operator==(const CFilms& fil) { return (producer == fil.getProducer()) ? true : false; }

};


// klas dve
class CRazprostranitel {
private:
	vector<CFilms> vfilm;
	string rname;
	double revenue;

public:

	vector<CFilms> getCFilmVector() const { return vfilm; }
	string getRazName() const { return rname; }
	double getRevenue() const { return revenue; }

	// syzdavane na obekt ot drug obekt 1.
	CRazprostranitel(const CRazprostranitel& raz) {
		vector<CFilms> vf = raz.getCFilmVector();
		copy(vf.begin(), vf.end(), back_inserter(vfilm));
		rname = raz.getRazName();
		revenue = raz.getRevenue();
	}

	// syzdavane na obekt chrez eksplicitno zadadeni parametri 2.
	CRazprostranitel(vector<CFilms>& fil, string rnm, double rev) {
		copy(fil.begin(), fil.end(), back_inserter(vfilm));
		rname = rnm;
		revenue = rev;
	}

	CRazprostranitel() {
		rname = " ";
		revenue = 0.0;
	}

	// funkciq opredelqshta dali filma e predlagan poveche ot 1 pyt 3.
	bool sheckIfMoreThenOne(CFilms& fil) { return (fil.getTiraj() > 1) ? true : false; }

	istream& RInput(istream& in) {
		in >> rname;
		in >> revenue;
		int siz = 0;
		in >> siz;
		for (int i = 0; i < siz; i++) {
			CFilms fil;
			in >> fil;
			vfilm.push_back(fil);
		}
		return in;
	}
	friend istream& operator>>(istream& in, CRazprostranitel& raz) { return raz.RInput(in); }

	ostream& ROutput(ostream& out) {
		out << rname << endl;
		out << revenue << endl;
		out << vfilm.size() << endl;
		for (auto it = vfilm.begin(); it != vfilm.end(); it++) {
			out << (*it);
		}
		return out;
	}
	friend ostream& operator<<(ostream& out, CRazprostranitel& raz) { return raz.ROutput(out); }

};


// CASE 1
void makeCFilm(string& nm, string& pro, int& tir, int& yer, string& gen) {
	system("cls");
	fp.open("film.txt", ios::app);
	if (!fp) {
		cout << endl << "******* ERROR *******";
		exit(1);
	}
	CFilms fil(nm, pro, gen, tir, yer);
	fp << fil;
	fp.close();
}


// CASE 2
void makeCRazprostranitel(vector<CRazprostranitel>& vr, string& rnm, double& rv, string vs[]) {
	system("cls");
	fp.open("film.txt", ios::in);
	if (!fp) {
		cout << endl << "******* ERROR *******";
		exit(1);
	}
	string line;
	int count = 0;

	if (fp.is_open()){
		int inside_count = 0;
		while (getline(fp, line)){
			inside_count++;
			if (inside_count == 5) {
				count++;
				inside_count = 0;
			}
		}
		fp.close();
	}
	vector<CFilms> filmvector;
	string fs1, fs2, fs3;
	int fi1, fi2;

	for (int i = 0; i < sizeof(vs); i++) {
		string fnm = vs[i];
		fp.open("film.txt", ios::in);
		if (!fp) {
			cout << endl << "******* ERROR *******";
			exit(1);
		}
		if (fp.is_open()) {
			int inside_count = 0;
			while (count != inside_count) {
				getline(fp, fs1);
				getline(fp, fs2);
				getline(fp, fs3);
				getline(fp, line);
				fi1 = stoi(line);
				getline(fp, line);
				fi2 = stoi(line);
				CFilms fil(fs1, fs2, fs3, fi1, fi2);
				if (fil.getFilmName() == fnm) {
					filmvector.push_back(fil);
					break;
				}
				inside_count++;
			}
			fp.close();
		}
	}

	CRazprostranitel raz(filmvector, rnm, rv);
	cout << raz;
	vr.push_back(raz);

	system("pause");
}


// CASE 3
void listKomediq50k(list<CFilms>& k50k, string& kom) {
	system("cls");
	fp.open("film.txt", ios::in);
	if (!fp) {
		cout << endl << "******* ERROR *******";
		exit(1);
	}
	string line;
	int count = 0;

	if (fp.is_open()){
		int inside_count = 0;
		while (getline(fp, line)){
			inside_count++;
			if (inside_count == 5) {
				count++;
				inside_count = 0;
			}
		}
		fp.close();
	}

	cout << "Filmi s tiraj nad 50 000 ot janr komediq: " << endl << endl;

	fp.open("film.txt", ios::in);
	if (!fp) {
		cout << endl << "******* ERROR *******";
		exit(1);
	}

	string fs1, fs2, fs3;
	int fi1, fi2;

	if (fp.is_open()) {
		int inside_count = 0;
		while (count != inside_count) {
			getline(fp, fs1);
			getline(fp, fs2);
			getline(fp, fs3);
			getline(fp, line);
			fi1 = stoi(line);
			getline(fp, line);
			fi2 = stoi(line);
			CFilms fil(fs1, fs2, fs3, fi1, fi2);
			if (fil.getTiraj() > 50000 && fil.getGenre() == kom) {
				cout << fil;
				k50k.push_back(fil);
			}
			inside_count++;
		}
		fp.close();
	}
	system("pause");
}


//funkciq za CASE 4, za proverka na povtarqshti se imena na producenti
//s cel predotvratqvane na dublirashti s danni vyv faila
bool check(vector<string>& vs, string& s) {
	bool flag = false;
	for (auto i = vs.begin(); i != vs.end(); i++) {
		if ((*i) == s) {
			return false;
		}
		flag = true;
	}
	return flag;
}


// CASE 4
void separateFilesByProducer(vector<CRazprostranitel>& vr) {
	system("cls");

	vector<string> vProd;
	vProd.push_back("empty");
	string filename;

	for (auto it = vr.begin(); it != vr.end(); it++) {
		vector<CFilms> filmVector = (*it).getCFilmVector();

		for (auto itf = filmVector.begin(); itf != filmVector.end(); itf++) {
			string comp = (*itf).getProducer();
			filename = comp + ".txt";

			fp.open(filename, ios::out | ios::app);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				CRazprostranitel raz((*it));
				string sPr = (*itf).getProducer();
				if (check(vProd, sPr) == true) {
					fp << raz;
					vProd.push_back(sPr);
				}
				fp.close();
			}
		}
		vProd.clear();
		vProd.push_back("Empty");
	}

	cout << "Failovete sa gotovi" << endl;
	system("pause");
}


// CASE 5
void showFilmNames20(vector<CRazprostranitel>& vr, string& prod) {
	system("cls");

	cout << "Filmite s nad 20 broiki: " << endl;
	for (auto it = vr.begin(); it != vr.end(); it++) {
		vector<CFilms> filmVector = (*it).getCFilmVector();

		for (auto itf = filmVector.begin(); itf != filmVector.end(); itf++) {
			if (prod == (*itf).getProducer() && (*itf).getTiraj() > 20) {
				cout << "Film: " << (*itf).getFilmName() << endl;
				cout << "Razprostranitel: " << (*it).getRazName() << endl << endl;
			}
		}
	}
	system("pause");
}


// CASE 6
void showRevFromFileName(string& filename) {
	system("cls");

	fp.open(filename, ios::in);
	if (!fp) {
		cout << endl << "******* ERROR *******";
		exit(1);
	}
	string line;
	int rCount = 0;

	if (fp.is_open()){
		int inside_count = 0;
		int vSize = 0;
		while (getline(fp, line)){
			inside_count++;
			if (inside_count == 3) {
				vSize = stoi(line); 
				inside_count = 0;
				rCount++;
				for (int i = 0; i < vSize * 5; i++) {
					getline(fp, line);
				}
			}
		}
		fp.close();
	}

	fp.open(filename, ios::in);
	if (!fp) {
		cout << endl << "******* ERROR *******";
		exit(1);
	}

	if (fp.is_open()) {
		int inside_count = 0;
		while (rCount != inside_count) {
			int vSize = 0;

			getline(fp, line);
			cout << "Razprostranitel: " << line << endl;

			getline(fp, line);
			cout << "Pechalba: " << line << endl;
			
			getline(fp, line);
			cout << "Broi filmi: " << line << endl << endl;
			vSize = stoi(line);
			
			for (int i = 0; i < vSize * 5; i++) {
				getline(fp, line);
			}
			
			inside_count++;
		}
		fp.close();
	}
	system("pause");
}


// CASE 7
void showRazprosNaEkshanDrama(vector<CRazprostranitel>& vr, int& yearch, string& ek, string& dr) {
	system("cls");
	bool flag = false;
	cout << "Razprostranitelite s filmi za godina " << yearch << " ot janr ekshan ili drama sa: " << endl << endl;
	for (auto it = vr.begin(); it != vr.end(); it++) {
		vector<CFilms> filmVector = (*it).getCFilmVector();
		for (auto itf = filmVector.begin(); itf != filmVector.end(); itf++) {
			if (yearch == (*itf).getYear()) {
				if (ek == (*itf).getGenre()) {
					cout << endl << "Razprostranitel:" << (*it).getRazName() << endl;
					cout << "Film: " << (*itf).getFilmName() << endl;
					cout << "Janr: " << (*itf).getGenre() << endl << endl;
					flag = true;
				}
			}
		}
	}

	for (auto it = vr.begin(); it != vr.end(); it++) {
		vector<CFilms> filmVector = (*it).getCFilmVector();
		for (auto itf = filmVector.begin(); itf != filmVector.end(); itf++) {
			if (yearch == (*itf).getYear()) {
				if (dr == (*itf).getGenre()) {
					cout << endl << "Razprostranitel:" << (*it).getRazName() << endl;
					cout << "Film: " << (*itf).getFilmName() << endl;
					cout << "Janr: " << (*itf).getGenre() << endl << endl;
					flag = true;
				}
			}
		}
	}

	if (flag == false) {
		cout << "Nqma filmi za tazi godina" << endl;
	}

	system("pause");
}


// MAIN
void menu();
int main() {
	menu();
	return 0;
}

// MENU
void menu() {
	vector<CRazprostranitel> vraz;
	list<CFilms> komediq50k;
	// CASE 1
	string nm, pro, gen;
	int tir, yer;

	// CASE 2
	string fnm, rnm;
	double rv;
	int broi;
	string vs[100];

	// CASE 3
	string kom;

	// CASE 4
	// bez >>

	// CASE 5
	string prod;

	// CASE 6
	string filename;

	// CASE 7
	int yearch;
	string ek, dr;

	int ch;
	do {
		do {
			system("cls");
			cout << "==========MENU==========" << endl;
			cout << "1. Suzdai Film" << endl;
			cout << "2. Suzdai Razprostranitel" << endl;
			cout << "3. Izvejdane v otdelen spisyk na filmite s tiraj nad 50 000 kopiq, ot janr komediq" << endl;
			cout << "4. Da se izvedat v otdelni failove vsichki razprostraniteli, koito razprostranqvat filmi na edin i sysht producent" << endl;
			cout << "5. Da se izvedat zaglaviqta na filmite, koito sa nad 20 za producent, po ime" << endl;
			cout << "6. Da se izvedat vsichki danni za razprostranitelite s broi prihodi, kato parametyr, ot tekstov fail" << endl;
			cout << "7. Pri daden kato parametyr godina da se izveat razprostranitelite na takiva filmi, ot janr ekshan ili drama" << endl;
			cout << "8. Exit" << endl;
			cout << endl << "Vyvedete izbora si: ";
			cin >> ch;
		} while (ch < 1 || ch>8);
		switch (ch) {
		case 1: system("cls");
			cout << "Ime na filma: ";
			cin.ignore(1, '\n');
			getline(cin, nm);

			cout << endl << "Producent: ";
			getline(cin, pro);

			cout << endl << "Tiraj: ";
			cin >> tir;

			cout << endl << "Godina: ";
			cin >> yer;

			cout << endl << "Janr: ";
			cin.ignore(1, '\n');
			getline(cin, gen);
			makeCFilm(nm, pro, tir, yer, gen); break;

		case 2: system("cls");
			cout << "Ime na razprostranitelq: ";
			cin.ignore(1, '\n');
			getline(cin, rnm);

			cout << endl << "Pechalba za godinata: ";
			cin >> rv;

			cout << endl << "Kolko filma iskate: ";
			cin >> broi;

			for (int i = 0; i < broi; i++) {
				cout << endl << "Ime na film " << i + 1 << " koito shte vzeme: ";
				cin >> fnm;
				vs[i] = fnm;
			}
			makeCRazprostranitel(vraz, rnm, rv, vs);
			for (int i = 0; i < broi; i++) {
				vs[i] = "";
			}
			break;

		case 3: system("cls");
			cout << "Napishete kak ste vyveli janra komediq: ";
			cin.ignore(1, '\n');
			getline(cin, kom);
			listKomediq50k(komediq50k, kom); break;

		case 4: system("cls");
			separateFilesByProducer(vraz); break;

		case 5: system("cls");
			cout << "Napishete imeto na producenta za proverka: ";
			cin.ignore(1, '\n');
			getline(cin, prod);
			showFilmNames20(vraz, prod); break;

		case 6: system("cls");
			cout << "Napishete imeto na faila koito iskate da otvorite: ";
			cin.ignore(1, '\n');
			getline(cin, filename);
			showRevFromFileName(filename); break;

		case 7: system("cls");
			cout << "Vyvedete godina na film: ";
			cin >> yearch;
			cout << "Napishete kak ste vyveli janra ekshan: ";
			cin.ignore(1, '\n');
			getline(cin, ek);
			cout << "Napishete kak ste vyveli janra drama: ";
			getline(cin, dr);
			showRazprosNaEkshanDrama(vraz, yearch, ek, dr); break;
		default: system("cls"); cout << "==== END ====";
		}
	} while (ch != 8);
}