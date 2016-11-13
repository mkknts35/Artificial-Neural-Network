/*
    These are utility functions that I commonly use in my software.

    Copyright(C) 2016  Michael Brett Koonts

    This program is free software : you can redistribute it and / or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
#include "util.h"
//========================================================================
#if WINDOWSSYSTEM
void PrintTimeDifference(const FILETIME &start, const FILETIME &end)
{
    ULARGE_INTEGER st, et;
    __int64 etime, sTimeInt, eTimeInt;
    __int64 days, hours, minutes, seconds, milliseconds, tenths, hundredths;

    st.LowPart = start.dwLowDateTime;
    st.HighPart = start.dwHighDateTime;
    sTimeInt = st.QuadPart;

    et.LowPart = end.dwLowDateTime;
    et.HighPart = end.dwHighDateTime;
    eTimeInt = et.QuadPart;

    etime = (eTimeInt - sTimeInt) / 10000;
    
    seconds = etime / 1000;
    milliseconds = etime % 1000;
    tenths = milliseconds / 100;
    milliseconds = milliseconds % 100;
    hundredths = milliseconds / 10;
    milliseconds = milliseconds % 10;
    minutes = seconds / 60;
    seconds = seconds % 60;
    hours = minutes / 60;
    minutes = minutes % 60;
    days = hours / 24;
    hours = hours % 24;

    std::cout << "(Time: " << etime << " ms)" << std::endl;
    std::cout << "(" << days << ":" << hours << ":" << minutes 
        << ":" << seconds << "." << tenths << hundredths 
        << milliseconds << ")" << std::endl;
}
#else
void PrintTimeDifference(const timeval &start, const timeval &end)
{
    long mtime, seconds, useconds;
    seconds = end.tv_sec - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    mtime = ((seconds)* 1000 + useconds / 1000.0) + 0.5;
    long day, hour, minute, second, tenth, hundredth, millisecond;

    second = mtime / 1000;
    millisecond = mtime % 1000;
    tenth = millisecond / 100;
    millisecond = millisecond % 100;
    hundredth = millisecond / 10;
    millisecond = millisecond % 10;
    minute = second / 60;
    second = second % 60;
    hour = minute / 60;
    minute = minute % 60;
    day = hour / 24;
    hour = hour % 24;
    std::cout << "(Time: " << mtime << " ms)" << std::endl;
    std::cout << "(" << day << ":" << hour << ":" << minute 
        << ":" << second << "." << tenth << hundredth 
        << millisecond << ")" << std::endl;
}
#endif
//========================================================================
int calcPercentageComplete(int position, int end)
{
    double d_position = position, d_end = end;
    return (d_position / d_end) * 100;
}
//========================================================================
int updateOutputPercentage(int percent, bool finished)
{
    int p = percent;
    if (p > 99) p = 99;
    if (finished){
        std::cout << "\b\b\bDone." << std::endl;
    } else {
        std::cout << "\b\b\b" << std::setw(2) << p << "%" << std::flush;
    }
    return percent;
}
//========================================================================
void outputStatusMessage(std::string message)
{
    std::cout << message << "...   ";
}