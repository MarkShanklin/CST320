#pragma once
//**************************************
// cStructDeclNode.h
//
// Defines AST node for a struct declaration
//
// Inherits from cDeclNode because this is a type of declaration
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2016
// 
// Modified By: Mark Shanklin
// mark.shanklin@oit.edu
//
// Mod Date: Feb. 20, 2016
//

#include "cAstNode.h"
#include "cDeclNode.h"
#include "cDeclsNode.h"
#include "cSymbol.h"
#include "cSymbolTable.h"

class cStructDeclNode : public cDeclNode
{
    public:
        // params are: 
        //     the symbol table for the declarations that make up this struct
        //     the declarations that make up this struct
        //     the cSymbol for the name of the struct
        cStructDeclNode(cSymbolTable::symbolTable_t *symTbl, 
                        cDeclsNode *decls, 
                        cSymbol *struct_id)
            : cDeclNode()
        {
            cSymbol *name;
            AddChild(decls);
            m_symTbl = symTbl;

            // Figure out if the ID we were passed already exists in the 
            // local symbol table. 
            name = g_SymbolTable.FindLocal(struct_id->GetName());
            if (name == nullptr)
            {
                // No: this is good. A later lab will cause an error if it does
                name = struct_id;

                // If the symbol exists in an outer scope, we need to create
                // a new one instead of re-using the symbol from the outer scope
                if (g_SymbolTable.Find(struct_id->GetName()) != nullptr)
                {
                    name = new cSymbol(struct_id->GetName());
                }
                // insert the name of the struct into the global symbol table
                g_SymbolTable.Insert(name);
            }
            AddChild(name);
            name->SetDecl(this);
        }
        virtual bool isStruct()
        {
            return true;
        }
        virtual int  GetSize()
        {
            return 0;
        }
        virtual cDeclNode* GetType()
        {
            return this;
        }
        cSymbol* GetElement(string name)
        {
            return g_SymbolTable.FindInTable(m_symTbl, name);
        }
        virtual string GetName()
        {
            cSymbol* symbol = dynamic_cast<cSymbol*>(m_children.back());
            return symbol->GetName();
        }
        virtual string NodeType() { return string("struct_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        cSymbolTable::symbolTable_t *m_symTbl; 

};
