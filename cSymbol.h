/*******************************************
 * Author: Phil Howard
 *
 * ModifiedBy: Mark Shanklin
 * Date: Jan. 23, 2016
 ******************************************/
#pragma once
#include <string>

using std::string;

class cSymbol
{
    public:
        cSymbol(string name)
        {
            m_id = ++nextId;
            m_name = name;
        }

        virtual string ToString()
        {
            string result("<sym id=\"");
            result += std::to_string(m_id);
            result += "\" name=\"" + m_name + "\" />";

            return result;
        }

        string GetName()
        {
            return m_name;
        }
    protected:
        static long long nextId; //symbolCount
        long long m_id; //mSequence
        string m_name;
};
