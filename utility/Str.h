#pragma once

#include <sstream>
using std::istringstream;
using std::ostringstream;

#include <vector>
using std::vector;

#include <string>
using std::string;

namespace yazi {
namespace utility {

class Str
{
public:
    static string to_lower(const string & input);
    static string to_upper(const string & input);

    static char to_char(const string & input);
    static short to_short(const string & input);
    static int to_int(const string & input);
    static long to_long(const string & input);
    static float to_float(const string & input);
    static double to_double(const string & input);

    static string to_string(char c);
    static string to_string(short s);
    static string to_string(int i);
    static string to_string(long l);
    static string to_string(float f);
    static string to_string(double d);

    static string trim_start(const string & input);
    static string trim_start(const string & input, char trim);
    static string trim_start(const string & input, const char * trims);

    static string trim_end(const string & input);
    static string trim_end(const string & input, char trim);
    static string trim_end(const string & input, const char * trims);

    static string trim(const string & input);
    static string trim(const string & input, char trim);
    static string trim(const string & input, const char * trims);

    static void split(vector<string> & output, const string & input);
    static void split(vector<string> & output, const string & input, char separator);
    static void split(vector<string> & output, const string & input, const string & separators);

    static string join(vector<string> & input);
    static string join(vector<string> & input, char separator);
    static string join(vector<string> & input, const char * separators);

    static string capitalize(const string & input);

    static int compare(const string & strA, const string & strB, bool ignoreCase = false);
    static string format(const char * format, ...);

    static bool is_numeric(const string & input);
};

}}
