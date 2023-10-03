#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
 * Complete the 'timeConversion' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

string timeConversion(string s) {
    int hours, minutes, seconds;
    char am_pm[3];
    
    sscanf(s.c_str(), "%d:%d:%d%2s", &hours, &minutes, &seconds, am_pm);

    if (strcmp(am_pm, "PM") == 0 && hours != 12) {
        hours += 12;
    }
    if (strcmp(am_pm, "AM") == 0 && hours == 12) {
        hours = 0;
    }

    char formattedTime[9];
    snprintf(formattedTime, sizeof(formattedTime), "%02d:%02d:%02d", hours, minutes, seconds);

    return formattedTime;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = timeConversion(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
