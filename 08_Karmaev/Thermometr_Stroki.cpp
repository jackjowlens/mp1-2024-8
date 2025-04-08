#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

class Monitoring {
private:
	int day;
	int month;
	int year;
	string time;
	double temperature;
	string comment;
public:
	Monitoring() : day(1), month(1), year(2025), time("00:00"), temperature(0.0), comment("  ") {}

	Monitoring(int day, int month, int year, string time, double temperature,string comment) : day(day), month(month), year(year), time(time), temperature(temperature), comment(comment) {} 
	
	int getDay() const { return day; }
	int getMonth() const { return month; }
	int getYear() const { return year; }
	int getHour() const { 
		size_t r = time.find(":");
		return stoi(time.substr(0,r)) ; }
	string getTime() {
		return time;
	}
	double getTemperature() const { return temperature; }
	int setDay(int d) { day=d; }
	int setMonth(int m) { month=m; }
	int setYear(int y) { year = y; }
	string setHour(int h) { time=h; }
	double setTemperature(double t) { temperature = t; }

	void printMon() const {
		cout << "Дата: " << day << "." << month << "." << year << "  " << time << "  "<< temperature << " C " << comment << " " << endl;
	}
	
};

class Thermometr {
private:
	vector <Monitoring> monitor = { {1,1,2025,"00:00",-15.2,"  "}};
	int size = 1;

public:
	void setBaseDateTime(int day, int month, int year, string time, double t,string comment) {
		Monitoring a(day, month, year, time, t,comment);
		monitor[0] = (a);
	}

	void const getBaseDateTime() const {
		monitor[0].printMon();
	}

	void newMonit(const string& str) {
		int day, month, year;
		double temperature=-10000;
		string time;
		string comment;
		vector <string> date;
		string token;
		size_t slash1, slash2;
		stringstream ss(str);
		while (ss >> token) {
			date.push_back(token);
		}
		for (int i = 0; i < date.size(); i++) {
			if (date[i].find("/") != -1) {
				slash1 = date[i].find("/");
				slash2 = date[i].rfind("/");
				day = stoi(date[i].substr(0, slash1));
				month = stoi(date[i].substr(slash1+1,slash2-slash1-1));
				year = stoi(date[i].substr(slash2+1));
				date.erase(date.cbegin() + i);
				break;
			}
		}
		size_t double_point;
		for (int i = 0; i < date.size(); i++) {
			if (date[i].find(":") != -1) {
				double_point = date[i].find(":");
				time = date[i];
				date.erase(date.cbegin() + i);
				break;
			}
			
		}
		
		for (int i = 0; i < date.size(); i++) {
			if (date[i].find(".") != -1) {
				temperature = stod(date[i]);
				date.erase(date.cbegin() + i);
			}
			
		}

		comment = date[0];
		
		
		
		monitor.push_back(Monitoring(day, month, year, time, temperature, comment));


	}

	

	void getTemper(int d, int m, int y, int h)const {
		int k = 0;
		for (int i = 0; i < monitor.size(); i++) {
			if (d == monitor[i].getDay() && m == monitor[i].getMonth() && y == monitor[i].getYear() && h == monitor[i].getHour()) {
				cout << "Температура -   " << monitor[i].getTemperature() << " C" << endl;
				k = 1;
			}
		}
		if (k != 1) {
			cout << "Такого замера не было (((";
		}
	}

	void addMonitoringSeries(int k) {
		
		/*for (int i = 0; i < k; i++) {
			t[i] = -1;
		}
		int c = 0;
		while (k != 0) {
			int h;

			cout << "Введите время" << endl;
			cin >> h;
			while (h < 0 || h > 24) {

				cout << "Ошибка введите заново" << endl;
				cin >> h;

			}
			for (int i = 0; i < k; i++) {
				if (t[i] == h) {
					cout << "Ошибка введите заново" << endl;
					cin >> h;

					i = 0;
				}
			}
			t[c] = h;
			double temper;
			cout << "Введите температуру ";
			cin >> temper;*/
		int day, month, year;
		double temperature;
		string time, comment;
		for (int i = 0; i < k; i++) {
			cout << "Введите день, месяц и год через пробел" << "\n";
			cin >> day;
			cin >> month;
			cin >> year;
			cout << "Введите температуру" << "\n";
			cin >> temperature;
			cout << "Введите время в формате 21:00" << "\n";
			cin >> time;
			cout << "Введите комментарий" << "\n";
			cin >> comment;
			pushnewmonit(day, month, year, time, temperature,comment);
			k--;
		}	

	
	}
	void pushnewmonit(int day, int month, int year, string time, double temperature, string comment) {
		monitor.push_back(Monitoring(day, month, year, time, temperature, comment));
	}

	void findAvgTempForDay(int d, int m, int y) {
		int counter = 0;
		double c_temp = 0.0;
		for (int i = 0; i < monitor.size(); i++) {
			if (monitor[i].getDay() == d && monitor[i].getMonth() == m && monitor[i].getYear() == y) {
				c_temp += monitor[i].getTemperature();
				counter += 1;
			}
		}
		cout << "Средняя температура за " << d<<"."<<m<<"."<<y<<"  "<<(c_temp / counter);
	}

	void findAvgTempForMonth(int m, int y) {
		int counter = 0;
		double c_temp = 0.0;
		for (int i = 0; i < monitor.size(); i++) {
			if (monitor[i].getMonth() == m && monitor[i].getYear() == y) {
				c_temp += monitor[i].getTemperature();
				counter += 1;
			}
		}
		cout << "Средняя температура за месяц = " << (c_temp / counter);
	}
	
	void findAvgTempForYear(int m, int y) {
		int counter = 0;
		double c_temp = 0.0;
		for (int i = 0; i < monitor.size(); i++) {
			if (monitor[i].getYear() == y) {
				c_temp += monitor[i].getTemperature();
				counter += 1;
			}
		}
		cout << "Средняя температура за год = " << (c_temp / counter);
	}
	
	void avgdaytempformonth(int m, int y) {
		int counter = 0;
		double c_temp = 0.0;
		for (int i = 0; i < monitor.size(); i++) {
			if (monitor[i].getYear() == y && monitor[i].getMonth() == m && (12 <= monitor[i].getHour() <= 18)) {
				c_temp += monitor[i].getTemperature();
				counter += 1;
			}
		}
		cout << "Средняя дневная температура за месяц = " << (c_temp / counter);
	}
	
	void avgnighttempformonth(int m, int y) {
		int counter = 0;
		double c_temp = 0.0;
		for (int i = 0; i < monitor.size(); i++) {
			if (monitor[i].getYear() == y && monitor[i].getMonth() == m && ((22 <= monitor[i].getHour() <= 23)) || ((0 <= monitor[i].getHour() <= 5))) {
				c_temp += monitor[i].getTemperature();
				counter += 1;
			}
		}
		cout << "Средняя ночная температура за месяц = " << (c_temp / counter);
	}

};



int main() {
	setlocale(LC_ALL, "Russian");
	Thermometr t;

	t.setBaseDateTime(1, 1, 2025, "00:00", -15.2,"Было холодно конечно да");
	t.getBaseDateTime();  

	string s;

	cout << "Введите наблюдение в формате: \n 12/11/2025 12:00 -23.3 Комментарий\n";
	getline(cin, s);
	stringstream ss(s);
	t.newMonit(s);
	t.getTemper(12, 11, 2025, 12);  

	t.addMonitoringSeries(2);  
	t.getTemper(2, 1, 2025, 14);  
	t.getTemper(2, 1, 2025, 18);  



	t.findAvgTempForDay(1, 1, 2025);  


}