#pragma once
//**************************************
// cVarExprNode.h
//
// Defines AST node for a variable reference
//
// Inherits from cExprNode so variable refs can be used in expressions`
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2016
//
// Modified By: Mark Shanklin
// mark.shanklin@oit.edu
//
// Mod Date: Feb. 21, 2016
//

#include "cSymbol.h"
#include "cAstNode.h"
#include "cExprNode.h"

class cVarExprNode : public cExprNode
{
    public:
        // param is the symbol for the variable
        cVarExprNode(cSymbol *name)
            : cExprNode()
        {
            if (!g_SymbolTable.Find(name->GetName()))
            {
                SemanticError("Symbol " + name->GetName() + " not defined");
            }
            else
            {
                AddChild(name);
            }   
        }

        // called for the fields in struct refs
        void AddElement(cSymbol *name)
        { 
            cSymbol* lastChild = dynamic_cast<cSymbol*>(m_children.back());

            if(!lastChild->GetDecl()->GetType()->isStruct())
            {
                SemanticError(GetName() + " is not a struct");
            }
            else
            {
                cStructDeclNode* structdecl = dynamic_cast<cStructDeclNode*>(lastChild->GetDecl()->GetType());
                cSymbol* element = structdecl->GetElement(name->GetName()); 
                    if(element == nullptr)
                    {
                        SemanticError(name->GetName() + " is not a field of " + GetName());
                    }
                    else
                    {
                        AddChild(element);
                    }
            }
           // AddChild(name);
        }

        cDeclNode* GetDecl()
        {
            cSymbol* type = dynamic_cast<cSymbol*>(m_children.back());
            return type->GetDecl();
        }
        virtual cDeclNode* GetType()
        {
            cSymbol* type = dynamic_cast<cSymbol*>(m_children.front());
            return type->GetDecl();
        }
        string GetName()
        {
            string name = "";
            for(int i = 0; i < NumChildren(); i++)
            {
                cSymbol* temp = dynamic_cast<cSymbol*>(m_children[i]);
                name += temp->GetName();
                if(i < (NumChildren() - 1))
                {
                    name += ".";
                }
            }
            return name;
        }

        virtual string NodeType() { return string("varref"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
