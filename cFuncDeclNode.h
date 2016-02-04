#pragma once
/*******************************************
 * cFuncDeclNode.h
 *
 * Author:Mark Shanklin
 * mark.shanklin@oit.edu
 *
 * Date:Feb. 03, 2016
 ******************************************/

#include "cAstNode.h"
#include "cStmtsNode.h"
#include "cParamsNode.h"
#include "cDeclNode.h"

class cFuncDeclNode : public cDeclNode
{
    public:
        cFuncDeclNode(cSymbol *type, cSymbol *name)
        {
            if(g_SymbolTable.Find(name->GetName()) != nullptr)
            {
                name = new cSymbol(name->GetName());
            }
            g_SymbolTable.Insert(name);

            AddChild(type);
            AddChild(name);
        }
        void AddDeclsNode(cDeclsNode *locals)
        {
            AddChild(locals);
        }
        void AddStmtsNode(cStmtsNode *stmts)
        {
            AddChild(stmts);
        }
        void AddParamsNode(cParamsNode *params)
        {
            AddChild(params);
        }
        virtual string NodeType() { return string("func"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
