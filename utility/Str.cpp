#include <utility/Str.h>
using namespace yazi::utility;

#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdarg.h>
#include <cctype>
#include <algorithm>
#include <iterator>
using namespace std;


string Str::to_lower(const string & input)
{
    string str = input;
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

string Str::to_upper(const string & input)
{
    string str = input;
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

char Str::to_char(const string & input)
{
    char c = 0;
    stringstream ss;
    ss << input;
    ss >> c;
    return c;
}

short Str::to_short(const string & input)
{
    short s = 0;
    stringstream ss;
    ss << input;
    ss >> s;
    return s;
}

int Str::to_int(const string & input)
{
    //return atoi(input.c_str());
    int i = 0;
    stringstream ss;
    ss << input;
    ss >> i;
    return i;
}

long Str::to_long(const string & input)
{
    //return atol(input.c_str());
    long l = 0;
    stringstream ss;
    ss << input;
    ss >> l;
    return l;
}

float Str::to_float(const string & input)
{
    float f = 0.0;
    stringstream ss;
    ss << input;
    ss >> f;
    return f;
}

double Str::to_double(const string & input)
{
    // return atof(input.c_str());
    double d = 0.0;
    stringstream ss;
    ss << input;
    ss >> d;
    return d;
}

string Str::to_string(char c)
{
    ostringstream os;
    os << c;
    return os.str();
}

string Str::to_string(short s)
{
    ostringstream os;
    os << s;
    return os.str();
}

string Str::to_string(int i)
{
    ostringstream os;
    os << i;
    return os.str();
}

string Str::to_string(long l)
{
    ostringstream os;
    os << l;
    return os.str();
}

string Str::to_string(float f)
{
    ostringstream os;
    os << f;
    return os.str();
}

string Str::to_string(double d)
{
    ostringstream os;
    os << d;
    return os.str();
}

string Str::trim_start(const string & input)
{
    return trim_start(input, " \r\n");
}

string Str::trim_start(const string & input, char trim)
{
    string str;
    str = trim;
    return trim_start(input, str.c_str());
}

string Str::trim_start(const string & input, const char * trims)
{
    string delimiter = trims;
    string str = input;
    size_t found;
    found = str.find_first_not_of(delimiter);
    if (found != string::npos)
        str.erase(0, found);
    else
        str.clear();
    return str;
}

string Str::trim_end(const string & input)
{
    return trim_end(input, " \r\n");
}

string Str::trim_end(const string & input, char delim)
{
    string str;
    str = delim;
    return trim_end(input, str.c_str());
}

string Str::trim_end(const string & input, const char * delims)
{
    string delimiter = delims;
    string str = input;
    size_t found;
    found = str.find_last_not_of(delimiter);
    if (found != string::npos)
        str.erase(found + 1);
    else
        str.clear();
    return str;
}

string Str::trim(const string & input)
{
    return trim(input, " \r\n");
}

string Str::trim(const string & input, char trim)
{
    string str;
    str = trim;
    return Str::trim(input, str.c_str());
}

string Str::trim(const string& input, const char * trims)
{
    string str = trim_start(input, trims);
    return trim_end(str, trims);
}

void Str::split(vector<string> & output, const string & input)
{
    output.clear();
    istringstream iss(input);
    copy(istream_iterator<string>(iss),
        istream_iterator<string>(),
        back_inserter(output));
}

void Str::split(vector<string> & output, const string & input, char separator)
{
    output.clear();
    stringstream ss(input);
    string item;
    while(getline(ss, item, separator))
    {
        output.push_back(item);
    }
}

void Str::split(vector<string> & output, const string & input, const string & separators)
{
    output.clear();
    size_t last = 0;
    size_t index = input.find_first_of(separators, last);
    while (index != string::npos)
    {
        string str = input.substr(last, index - last);
        output.push_back(str);
        last = index + 1;
        index = input.find_first_of(separators, last);
    }
    if (index - last > 0)
    {
        output.push_back(input.substr(last , index - last));
    }
}

string Str::join(vector<string> & input)
{
    return join(input, ' ');
}

string Str::join(vector<string> & input, char separator)
{
    ostringstream os;
    vector<string>::iterator it;
    for (it = input.begin(); it != input.end(); it++)
    {
        os << *it;
        os << separator;
    }
    return os.str();
}

string Str::join(vector<string> & input, const char * separators)
{
    ostringstream os;
    vector<string>::iterator it;
    for (it = input.begin(); it != input.end(); it++)
    {
        os << *it;
        os << separators;
    }
    return os.str();
}

string Str::capitalize(const string & input)
{
    ostringstream os;
    int size = input.size();
    for (int i = 0; i < size; i++)
    {
        if (i == 0)
        {
            if (input[i] >= 97 && input[i] <= 122)
            {
                os << (char)(input[i] - 32);
            }
        }
        else
        {
            os << input[i];
        }
    }
    return os.str();
}

int Str::compare(const string & strA, const string & strB, bool ignoreCase)
{
    if (ignoreCase)
    {
        return strcasecmp(strA.c_str(), strB.c_str());
    }
    else
    {
        return strA.compare(strB);
    }
}

string Str::format(const char* format, ...)
{
    char buf[1024];
    memset(buf, 0, sizeof(buf));
    va_list arg_ptr;
    va_start(arg_ptr, format);
    vsnprintf(buf, sizeof(buf), format, arg_ptr);
    va_end(arg_ptr);
    return string(buf);
}

bool Str::is_numeric(const string & input)
{
    if (input.find_first_not_of("0123456789.") != string::npos)
        return false;
    if (count(input.begin(), input.end(), '.') > 1)
        return false;
    return true;
}

