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
#include <map>//hash like functionality.
#include <list>//stack like functionality.
#include <string>//used for storing yytext.
#include "cSymbol.h"//used for symbols.

using std::string;//needed for holding yytext.
using std::map;//needed for Hash like functionality.
using std::pair;//needed to add to the map as a single command.
using std::list;//used for the stack like functionality.

class cSymbolTable
{
    public:
        /*******************************************
         * Increase the Scope.
         ******************************************/
        void IncreaseScope()
        {
            m_cSymbolTable.push_front(map<string, cSymbol*>());//adding a new symbol table to the stack of tables.
            m_scope++;//Increase the variable that tracks the current scope.
        }
        /*******************************************
         * Decrease the Scope.
         ******************************************/
        void DecreaseScope()
        {
            if(m_scope != 0)
            {
            m_cSymbolTable.pop_front();// remove top default table from the stack
            m_scope--;// change the scope to match default table scope number.
            }
            else  
                //error can't pop off of a empty list.
                std::cout << "Error: can't Decrease Scope when in out most scope" << std::endl;
        }
        /*******************************************
         * Insert a symbol into the current Scope.
         ******************************************/
        cSymbol* Insert(char* yytext)
        {
            cSymbol* temp; //pointer to a cSymbol
            if (!(temp = Lookup(yytext)))//if the symbol doen't exist do below.
            {
                temp = new cSymbol(yytext);//create a new cSymbol with yytext.
                m_cSymbolTable.front().insert(pair<string,cSymbol*>(yytext,temp));//goto default table front() and insert the new symbol into this table.
            }
            return temp;//return the cSymbol*
        }
        /*******************************************
         * Used to Lookup a symbol for current Scope.
         ******************************************/
        cSymbol* Lookup(char* yytext)
        {
            map<string,cSymbol*>::iterator it;//create an iterator for my map.
            it = m_cSymbolTable.front().find(yytext);//set that iterator equal to the default scope front() at the desired symbol yytext.
            if (it != m_cSymbolTable.front().end())//make sure the scope is greater than zero.
            {
                return it->second;//return the second element in the pair of elements which is the cSymbol pointer.
            }

            return nullptr;//return nullptr if it doesn't exist in the table.
        }
        /*******************************************
         * Used to Lookup a symbol for all Scopes.
         ******************************************/
        cSymbol* g_Lookup(char* yytext)
        {
            for(auto& i : m_cSymbolTable)//range based for loop
            {
                map<string,cSymbol*>::iterator it;//an iterator for my map.
                it = i.find(yytext);//set it equal. 
                if (it != i.end())//check that scope is greater than zero.
                {
                    return it->second;//return the second element in the pair of elements which is the cSymbol pointer.
                }
            }
            return nullptr;//return nullptr if it doesn't exist throught the scopes of tables.
        }
        /*******************************************
         * Class members
         ******************************************/
        list<map<string, cSymbol*>> m_cSymbolTable;// A list of maps of pairs containing a string and a cSymbol pointers
        int m_scope = 0;//a integer used to keep track of the current scope.    
};

#endif
