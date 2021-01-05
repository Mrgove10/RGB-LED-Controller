#include "c_utils.h"

/*
 * This allows you to check a string, it start at the begining and will 
 * compare the two trings to one another
 * if the start is identical i will return true, overwise it will return false
 */
bool c_utils::RegEx(String regExTemplate, String stringToCheck)
{
    int length = regExTemplate.length();
    int tmp = 0;
    for (size_t i = 0; i < length; i++)
    {
        if (regExTemplate[i] == stringToCheck[i])
        {
            tmp++;
        }
    }
    if (tmp == length)
        return true;
    else
        return false;
}