#pragma once
/*******************************************
 * Author: Mark Shanklin
 * mark.shanklin@oit.edu
 *
 * Date: Feb. 20, 2016
 ******************************************/
#include <string>
#include "cDeclNode.h"
class cBaseTypeNode : public cDeclNode
{
    public:
        cBaseTypeNode(string name, int size, bool is_float)
        {
            m_name = name;
            m_size = size;
            m_is_float = is_float;
        }
        virtual bool isVar(){ return false; }
        virtual bool isStruct(){ return false; }
        virtual bool isFloat(){ return m_is_float; }
        virtual bool isInt(){ return !m_is_float; }
        virtual int GetSize(){ return m_size; }
        virtual string GetName(){ return m_name; }
        virtual cDeclNode* GetType(){ return this; }    
        virtual string NodeType() { return string("type"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        string m_name;
        int m_size;
        bool m_is_float;
};
