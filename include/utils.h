#ifndef UTILS_H
#define UTILS_H

#include <string>

std::string format_time(int time)
{
	int seconds = time/CLOCKS_PER_SEC;
	int minute = 60;
    int hour = 60*minute;
    int day = 24*hour;
    int month = 30*day;
    int year = 12*month;
    int y = (seconds / year);
    int mo = (seconds - y*year) / month;
    int d = (seconds - y*year - mo*month) / day;
    int h = (seconds - y*year - mo*month - d*day) / hour;
    int mi = (seconds - y*year - mo*month - d*day - h*hour) / minute;
    int s = (seconds - y*year - mo*month - d*day - h*hour - mi*minute);
    char str[30];
    sprintf(str, "%dy %dm %dd %dh %dm %ds", y, mo, d, h, mi, s);
    return std::string(str);
}

#endif
