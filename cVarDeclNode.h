#pragma once
/*******************************************
 * cVarDeclNode
 *
 * Defines class for variable declarations.
 *
 * Author: Mark Shanklin
 * mark.shanklin@oit.edu
 *
 * Date: Feb. 02, 2016
 ******************************************/

#include "cSymbol.h"
#include "cAstNode.h"

class cVarDeclNode : public cDeclNode
{
    public: 
        cVarDeclNode(cSymbol *type, cSymbol *name)
        {
            if (g_SymbolTable.Find(name->GetName()) != nullptr)
            {
                name = new cSymbol(name->GetName());
            }
            
            g_SymbolTable.Insert(name);

            AddChild(type);
            AddChild(name);
        }
        virtual string NodeType() { return string("var_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
