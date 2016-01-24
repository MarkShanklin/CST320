/*******************************************
 * Author:          Mark Shanklin
 *                  mark.shanklin@oit.edu
 *
 * Date Created:    Jan. 20, 2016
 * Last Mod. Date:  Jan. 23, 2016
 * Lab Number:      3
 * File Name:       cSymbolTable.h
 *
 ******************************************/
#ifndef CSYMBOLTABLE_H
#define CSYMBOLTABLE_H

#include <iostream>
#include <map>
#include <list>
#include <string> 
#include "cSymbol.h"

using std::string;
using std::map;
using std::pair;
using std::list;
using std::cout;
using std::endl;

class cSymbolTable
{
    public:
        void IncreaseScope()
        {
            m_cSymbolTable.push_front(map<string, cSymbol*>());
            m_scope++;
        }
        void DecreaseScope()
        {
            m_cSymbolTable.pop_front();// remove top default table from the stack
            m_scope--;// change the scope to match default table scope number.
        }
        cSymbol* Insert(char* yytext)
        {
            cSymbol* temp;
            if (!(temp = Lookup(yytext)))
            {
                temp = new cSymbol(yytext);
                m_cSymbolTable.front().insert(pair<string,cSymbol*>(yytext,temp));
            }
            return temp;
        }
        cSymbol* Lookup(char* yytext)
        {
            map<string,cSymbol*>::iterator it;
            it = m_cSymbolTable.front().find(yytext);
            if (it != m_cSymbolTable.front().end())
            {
                return it->second;
            }
            return nullptr;
        }
        cSymbol* g_Lookup(char* yytext)
        {
            for(auto& i : m_cSymbolTable)
            {
                map<string,cSymbol*>::iterator it;
                it = i.find(yytext);
                if (it != i.end())
                {
                    return it->second;
                }
            }
            return nullptr;
        }
        
        list<map<string, cSymbol*>> m_cSymbolTable;
        int m_scope = 0;    
};

#endif
