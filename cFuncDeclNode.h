#pragma once
//**************************************
// cFuncDeclNode.h
//
// Defines AST node for a function declaration
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2016
//

#include "cAstNode.h"
#include "cStmtsNode.h"
#include "cDeclsNode.h"
#include "cDeclNode.h"

class cFuncDeclNode : public cDeclNode
{
    public:
        // params are the return type and name of function
        cFuncDeclNode(cSymbol *type, cSymbol *name)
            : cDeclNode()
        {
            AddChild(type);
            AddChild(name);
            m_isDefinition = false;
            name->SetDecl(this);
            g_SymbolTable.Insert(name);
        }

        // Add formal params to the declaration
        void AddParams(cDeclsNode *params)
        {
            AddChild(params);
        }

        // Add declarations to the declaration.
        // Doing so means this is a definition, not just a declaration
        // BUT, we will wait for AddStmts to mark it as a definition
        // because our grammar requires all functions to have statements.
        void AddDecls(cDeclsNode *decls)
        {
            AddChild(decls);
        }

        // Add statements to the declaration.
        // Doing so means that this is a definition, not just a declaration
        // We will set the flag marking this as a definition.
        void AddStmts(cStmtsNode *stmts)
        {
            AddChild(stmts);
            m_isDefinition = true;
        }
        int GetSize()
        {
            //cSymbol* size = dynamic_cast
            //return size->GetDecl()->GetSize();
            return 0;
        }
        cDeclNode* GetType()
        {
            return this;
        }

        virtual string NodeType() { return string("func"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        bool        m_isDefinition;     // flag indicating this is a definition,
                                        // not just a declaration
};
