#include <string>
#include <iostream>
#include <limits>
#include <fstream>
#include <vector>

using namespace std;

int len;
int n;
string reply;
string segment;
string mark = " -- tried ";
vector <string> db_buffer;
bool last_file_exists = false;
string last_file;

bool fileExists(const std::string& filename)
{
    ifstream infile(filename);
    return infile.good();
}

string init_lst_files()
{
	string filename = "combo";
	for(int i=0; fileExists(filename+".lst")==true; i++)
	{
		if(i>=1)
		{
			filename.pop_back();
		}
		filename = filename + to_string(i);
	}
	filename.append(".lst");
	ofstream outfile (filename);
	return filename;
}

// The main recursive method to print all possible strings of length "length"
void print_str(const char str[], string prefix, const int n, const int len, fstream& obj)
{
	if (len == 1)
	{
		for (int j = 0; j < n; j++)
		{
			cout << prefix + str[j] <<endl;
			obj<<prefix+str[j]<<endl;
		}
	}//Base case: len = 1, print the string "len" times + the remaining letter
	else
	{
		// One by one add all characters from "str" and recursively call for "len" equals to "len"-1
		for (int i = 0; i < n; i++)
		// Next character of input added
		print_str(str, prefix + str[i], n, len - 1, obj);
		// "len" is decreased, because we have added a new character
	}
}

void start()
{
	cout<<"How many numbers are used? \n";
	cin>>len;
	cout<<"How many different numbers or symbols are possible? \n";
	cin>>n;
	char str[n];
	cout<<"Enter all numbers or symbols possible. Note: only one symbol supported at a time. \n";
	for (int z = 0; z < sizeof(str); z++) 
	{
		cout<<"Enter value #"<<z<<" out of #"<<sizeof(str)<<endl;
		cin >> str[z];
	}
	
	fstream obj(init_lst_files(), fstream::out | fstream::app | fstream::ate);
	print_str(str, "", n, len, obj);  //Note: this function works on all cases and not just the case above
	
	cin.get();	
}

string rem_extension(string str)
{
	size_t pos = str.find_last_of(".");
	if (pos!=string::npos)
	{
		string ext = str.substr(pos);
		str.erase( str.size() - ext.length());
		return str;
	}
	else
	{
		cout<<"No extension in passed string"<<str<<endl;
		return str;
	}
}

void write_mark(string filename)
{
	filename = rem_extension(filename);
	filename.append(".mark");
	ofstream outfile (filename);
	for(int i=0; i<db_buffer.size(); i++)
	{
		outfile<<db_buffer[i]<<endl;
	}	
	outfile.close();
	db_buffer.clear();
}

void mark_comb(string filename, string segment)
{
	string line;
	size_t pos;
	fstream obj(filename, fstream::in);
	if(obj.is_open())
	{
		while(getline(obj,line))
		{
			pos = line.find(segment);
			if(pos!=string::npos)
			{
				db_buffer.push_back(line+mark);
				continue;
			}
			else
			{
				db_buffer.push_back(line);
			}
		}
	}
	else
	{
		cout<<"Cant open "<<filename<<endl;
	}
	write_mark(filename);
}

void list_db(string filename)
{
	string line;
	fstream obj(filename, fstream::in);
	if(obj.is_open())
	{
		while(getline(obj,line))
		{
			cout<<line<<endl;
		}
	}
	else
	{
		cout<<"Cant open "<<filename<<endl;
	}	
}

int main()
{
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
	
	start:
	cout<<"Type `s` to start a new combination. Else press any key. \n";
	cout<<"Type `c` to mark a combination as `checked` in database. \n";
	cout<<"Type `l` to list a database file. \n";
	cin>>reply;
	if(reply.compare("s")==0)
	{
		start();
	}
	else if(reply.compare("c")==0)
	{
		cin.clear();
		cout<<"Type the name of database to load: [Or any key to default = last file opened .] \n";
		cin>>reply;
		if(!fileExists(reply))
		{
			if(!last_file_exists)
			{
				reply = "combo.lst";
				last_file_exists = true;
			}
			else
			{
				reply = last_file;
			}
		}
		last_file = reply;
		cout<<"What segment to search for in the database? \n";
		cin>>segment;
		mark_comb(reply, segment);
		goto start;
	}
	else if(reply.compare("l")==0)
	{
		cin.clear();
		cout<<"Type the name of database to load: [Or any key to default = last file opened .] \n";
		cin>>reply;
		if(!fileExists(reply))
		{
			if(!last_file_exists)
			{
				reply = "combo.mark";
				last_file_exists = true;
			}
			else
			{
				reply = last_file;
			}			
		}
		last_file = reply;
		list_db(reply);
		goto start;
	}
	else
	{
		goto start;
	}
	
	return 0;
}