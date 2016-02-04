#pragma once
/*******************************************
 * cStructDeclNode.h
 *
 * Author:Mark Shanklin
 * mark.shanklin@oit.edu
 *
 * Date: Feb. 02, 2016
 ******************************************/

#include "cAstNode.h"
#include "cDeclNode.h"
class cStructDeclNode : public cDeclNode
{
    public:
        cStructDeclNode(cDeclsNode *decls, cSymbol *name)
        {
            if(g_SymbolTable.Find(name->GetName()) != nullptr)
            {
                name = new cSymbol(name->GetName());
            }

            g_SymbolTable.Insert(name);

            AddChild(decls);
            AddChild(name);
        }
    virtual string NodeType() {return string("struct_decl"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
