#include <bits/stdc++.h>

using namespace std;

const string Saturday = "## Saturday";
const string Sunday = "## Sunday";
const string Monday = "## Monday";
const string Tuesday = "## Tuesday";
const string Wednesday = "## Wednesday";
const string Thursday = "## Thursday";
const string Friday = "## Friday";

const string saturday = "SAT";
const string sunday = "SUN";
const string monday = "MON";
const string tuesday = "TUE";
const string wednesday = "WED";
const string thursday = "THU";
const string friday = "FRI";

const int NUMBER_OF_DAYS = 7;
const int NUMBER_OF_TIMES = 27;
const int SIZE_OF_CODE = 7;
const int SIZE_OF_GROUP = 2;
const int SIZE_OF_DAYS = 3;
const int SIZE_OF_TIME = 5;
const int FIRST_TIME = 7;
const int LAST_TIME = 20;
const int DAY_POS = 11;
const int SIZE_SPACE = 10;

typedef struct Course{
	string name;
	string code;
	int group;
}Course;

typedef vector<Course> course;

typedef struct CSV{
	string name;
	string code;
}CSV;

typedef vector<CSV> csv;

typedef vector<string> str;
typedef vector<int> integer; 

str open_file(char* file);
csv id_alias(str line);
string search_name(string code, csv courses);
void get_input(str& lines);
int day_of_week(string day);
int hour_min(string _time, int& min);
int pos_of_begin(string begin);
int length_of_time(string begin, string end);
void initialize(integer day_time[NUMBER_OF_DAYS][NUMBER_OF_TIMES], int day, int begin, int length, int row, int value);
bool overlap(integer day_time[NUMBER_OF_DAYS][NUMBER_OF_TIMES], int day, int begin, int length, int row);
void str_to_time(integer day_time[NUMBER_OF_DAYS][NUMBER_OF_TIMES], string day_and_time, int i);
course line_to_word(str line, csv file, integer day_time[NUMBER_OF_DAYS][NUMBER_OF_TIMES]);
void initial(integer day_time[NUMBER_OF_DAYS][NUMBER_OF_TIMES]);
void init_days(str& days);
void print_title(char* title);
void print_hours();
void print_dash();
int length_of_value(integer day_time[NUMBER_OF_DAYS][NUMBER_OF_TIMES], int begin, int day, int row);
bool empty(integer day_time[NUMBER_OF_DAYS][NUMBER_OF_TIMES], int day, int row, int begin = 0);
bool print_1_row(integer day_time[NUMBER_OF_DAYS][NUMBER_OF_TIMES], int day, int row);
void print_2_row(integer day_time[NUMBER_OF_DAYS][NUMBER_OF_TIMES], int day, int row, course courses);
void print_course(integer day_time[NUMBER_OF_DAYS][NUMBER_OF_TIMES], int day, course courses);
void print_days(str days, integer day_time[NUMBER_OF_DAYS][NUMBER_OF_TIMES], course courses);
void output(char* title, course courses, integer day_time[NUMBER_OF_DAYS][NUMBER_OF_TIMES]);

int main(int argc, char *argv[])
{
	csv file = id_alias(open_file(argv[1]));
	integer day_time[NUMBER_OF_DAYS][NUMBER_OF_TIMES];
	initial(day_time);
	str lines;
	get_input(lines);
	course courses = line_to_word(lines, file, day_time);
	output(argv[2], courses, day_time);
	return 0;
}

str open_file(char* file)
{
	str lines;
    string line;
    ifstream myfile;
    myfile.open(file);
	myfile >> line;
    while(myfile >> line)
		lines.push_back(line);
	return lines;
}

csv id_alias(str line)
{
	csv courses;
	for(int i = 0; i < line.size(); i++)
	{
		CSV curr;
		curr.code = line[i].substr(0, SIZE_OF_CODE);
		curr.name = line[i].substr(SIZE_OF_CODE + 1);
		courses.push_back(curr);
	}
	return courses;
}

string search_name(string code, csv courses)
{
	for(int i = 0; i < courses.size(); i++)
		if(code == courses[i].code)
			return courses[i].name;
	return "";
}

void get_input(str& lines)
{
	string s;
	while(getline(cin, s))
		lines.push_back(s);
}

int day_of_week(string day)
{
	if(day == saturday)
		return 0;
	if(day == sunday)
		return 1;
	if(day == monday)
		return 2;
	if(day == tuesday)
		return 3;
	if(day == wednesday)
		return 4;
	if(day == thursday)
		return 5;
	if(day == friday)
		return 6;
	return -1;
}

int hour_min(string _time, int& min)
{
	int hour = stoi(_time.substr(0, 2));
	min = stoi(_time.substr(3, 2));
	return hour;
}

int pos_of_begin(string begin)
{
	int time_begin_pos;
	int begin_hour, begin_min;
	begin_hour = hour_min(begin, begin_min);
	time_begin_pos = (begin_hour - FIRST_TIME) * 2 + begin_min / 30;
	return time_begin_pos;
}

int length_of_time(string begin, string end)
{
	int begin_hour, begin_min;
	begin_hour = hour_min(begin, begin_min);
	int end_hour, end_min;
	end_hour = hour_min(end, end_min);
	int diff_min = end_min - begin_min;
	int diff_hour = end_hour - begin_hour;
	switch(diff_min)
	{
		case 0:
			return diff_hour * 2;
		case 30:
			return diff_hour * 2 + 1;
		case -30:
			return diff_hour * 2 - 1;
	}
	return -1;
}

bool overlap(integer day_time[NUMBER_OF_DAYS][NUMBER_OF_TIMES], int day, int begin, int length, int row)
{
	for(int i = begin; i < begin + length; i++)
	{
		if(day_time[day][i][row] != -1)
			return true;
	}
	return false;
}

void initialize(integer day_time[NUMBER_OF_DAYS][NUMBER_OF_TIMES], int day, int begin, int length, int row, int value)
{
	for(int i = begin; i < begin + length; i++)
		day_time[day][i][row] = value;
}

void str_to_time(integer day_time[NUMBER_OF_DAYS][NUMBER_OF_TIMES], string day_and_time, int i)
{
	bool is_init = false;
	string day = day_and_time.substr(0, SIZE_OF_DAYS);
	int _day = day_of_week(day);
	if(_day == -1)
		abort();
	string time_begin = day_and_time.substr(SIZE_OF_DAYS + 1, SIZE_OF_TIME);
	string time_end = day_and_time.substr(SIZE_OF_DAYS + SIZE_OF_TIME + 2, SIZE_OF_TIME);
	int time_begin_pos = pos_of_begin(time_begin);
	int time_length = length_of_time(time_begin, time_end);
	if(time_length == -1)
		abort();	
	int row = day_time[_day][time_begin_pos].size() - 1;
	if(overlap(day_time, _day, time_begin_pos, time_length, row))
	{
		for(int j = 0; j < NUMBER_OF_TIMES; j++)
			day_time[_day][j].push_back(-1);
		row++;
		initialize(day_time, _day, time_begin_pos, time_length, row, i);
		is_init = true;
	} 
	else
	{
		for(row = day_time[_day][time_begin_pos].size() - 2; row >= 0; row--)
		{
			if(overlap(day_time, _day, time_begin_pos, time_length, row))
			{
				initialize(day_time, _day, time_begin_pos, time_length, row + 1, i);
				is_init = true;
				break;
			}
		}
	}
	if(!is_init)
	{
		initialize(day_time, _day, time_begin_pos, time_length, 0, i);
	}
	
	if((SIZE_OF_TIME * 3 + 1) > day_and_time.size())
		return;
	str_to_time(day_time, day_and_time.substr(SIZE_OF_TIME * 3 + 1), i);
}

course line_to_word(str line, csv file, integer day_time[NUMBER_OF_DAYS][NUMBER_OF_TIMES])
{
	course courses;
	for(int i = 0; i < line.size(); i++)
	{
		Course curr;
		curr.code = line[i].substr(0, SIZE_OF_CODE);
		curr.group = stoi(line[i].substr(SIZE_OF_CODE + 1, SIZE_OF_GROUP));
		curr.name = search_name(curr.code, file);
		if(curr.name == "")
			abort();
		courses.push_back(curr);
		string day_and_time = line[i].substr(DAY_POS);
		str_to_time(day_time, day_and_time, i);
	}
	return courses;
}

void initial(integer day_time[NUMBER_OF_DAYS][NUMBER_OF_TIMES])
{
	for(int i = 0; i < NUMBER_OF_DAYS; i++)
		for(int j = 0; j < NUMBER_OF_TIMES; j++)
			day_time[i][j].push_back(-1);
}

void init_days(str& days)
{
	days.push_back(Saturday);
	days.push_back(Sunday);
	days.push_back(Monday);
	days.push_back(Tuesday);
	days.push_back(Wednesday);
	days.push_back(Thursday);
	days.push_back(Friday);
}
	
void print_title(char* title)
{
	cout << "# " << title << endl << endl;
}
void print_hours()
{
	string s1, s2, s3, s4;
	for(int i = FIRST_TIME; i < LAST_TIME; i++)
	{
		cout.fill(' ');
		s1 = "0" + to_string(i) + ":" + "00";
		s2 = to_string(i) + ":" + "00";
		s3 = "0" + to_string(i) + ":" + "30";
		s4 = to_string(i) + ":" + "30";
		if(i < 10)
			cout << setw(SIZE_SPACE) << left << s1;
		else
			cout << setw(SIZE_SPACE) << left << s2;
		cout.fill(' ');
		if(i < 10)
			cout << setw(SIZE_SPACE) << left << s3;
		else
			cout << setw(SIZE_SPACE) << left << s4;
	}
	s1 = to_string(LAST_TIME) + ":" + "00";
	s2 = to_string(LAST_TIME) + ":" + "30";
	cout << setw(SIZE_SPACE) << left << s1;
	cout << s2;
	cout << endl;
}

void print_dash()
{
	cout.fill('_');
	cout << setw((LAST_TIME - FIRST_TIME + 1) * SIZE_SPACE * 2 - (SIZE_SPACE - SIZE_OF_TIME)) << '_' << endl;
}

int length_of_value(integer day_time[NUMBER_OF_DAYS][NUMBER_OF_TIMES], int begin, int day, int row)
{
	int l = 1;
	for(int i = begin; i < NUMBER_OF_TIMES - 1; i++)
	{
		if(day_time[day][i][row] == day_time[day][i + 1][row])
			l++;
		else
			return l;
	}
	return l;
}

bool empty(integer day_time[NUMBER_OF_DAYS][NUMBER_OF_TIMES], int day, int row, int begin)
{
	for(int i = begin; i < NUMBER_OF_TIMES; i++)
		if(day_time[day][i][row] != -1)
			return false;
	return true;
}

bool print_1_row(integer day_time[NUMBER_OF_DAYS][NUMBER_OF_TIMES], int day, int row)
{
	if(empty(day_time, day, row))
	{
		cout << endl;
		return false;
	}
	cout << "  ";
	for(int i = 0; i < NUMBER_OF_TIMES; i+= length_of_value(day_time, i, day, row))
	{
		if(empty(day_time, day, row, i))
		{
			cout << endl;
			return true;
		}
		switch(day_time[day][i][row])
		{
			case -1:
				cout.fill(' ');
				cout << setw(length_of_value(day_time, i, day, row) * SIZE_SPACE) << ' ';
				break;
			default:
				cout << '+';
				cout.fill('-');
				cout << setw(length_of_value(day_time, i, day, row) * SIZE_SPACE - 2) << '-';
				cout << '+';
				break;
		}
	}
	cout << endl;
	return true;
}

void print_2_row(integer day_time[NUMBER_OF_DAYS][NUMBER_OF_TIMES], int day, int row, course courses)
{
	int l;
	cout << "  ";
	for(int i = 0; i < NUMBER_OF_TIMES; i+= length_of_value(day_time, i, day, row))
	{
		if(empty(day_time, day, row, i))
		{
			cout << endl;
			return;
		}
		switch(day_time[day][i][row])
		{
			case -1:
				cout.fill(' ');
				cout << setw(length_of_value(day_time, i, day, row) * SIZE_SPACE) << ' ';
				break;
			default:
				cout << '|';
				cout.fill(' ');
				l = length_of_value(day_time, i, day, row) * SIZE_SPACE - 2;
				string s = courses[day_time[day][i][row]].name + " " + "(" + to_string(courses[day_time[day][i][row]].group) + ")";
				cout << setw((l - s.size()) / 2 + ((l - s.size()) % 2)) << right << ' ';
				cout << s;
				cout.fill(' ');
				cout << setw((l - s.size()) / 2) << ' ';
				cout << '|';
				break;
		}
	}
	cout << endl;
}

void print_course(integer day_time[NUMBER_OF_DAYS][NUMBER_OF_TIMES], int day, course courses)
{
	bool is_row = false;
	for(int row = 0; row < day_time[day][0].size(); row++)
	{
		if(print_1_row(day_time, day, row))
		{
			is_row = true;
			print_2_row(day_time, day, row, courses);
			print_1_row(day_time, day, row);
		}
	}
	if(is_row)
		cout << endl;
}

void print_days(str days, integer day_time[NUMBER_OF_DAYS][NUMBER_OF_TIMES], course courses)
{
	for(int i = 0; i < NUMBER_OF_DAYS; i++)
	{
		cout << days[i] << endl << endl;
		print_hours();
		print_dash();
		print_course(day_time, i, courses);
	}
}

void output(char* title, course courses, integer day_time[NUMBER_OF_DAYS][NUMBER_OF_TIMES])
{
	str days;
	init_days(days);
	print_title(title);
	print_days(days, day_time, courses);
}











