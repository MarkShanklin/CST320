#pragma once
//**************************************
// cAssignNode.h
//
// Defines AST node for assignment statments
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2016
//

#include "cAstNode.h"
#include "cStmtNode.h"
#include "cExprNode.h"
#include "cVarExprNode.h"

class cAssignNode : public cStmtNode
{
    public:
        // params are the lval and the expression
        cAssignNode(cVarExprNode *lval, cExprNode *expr)
            : cStmtNode()
        {
            bool allowed = true;
            cDeclNode* lvalType = lval->GetType();
            cDeclNode* exprType = expr->GetType();
            cDeclNode* charDecl = g_SymbolTable.Find("char")->GetDecl();
            
            if(lvalType == exprType)
            {
                allowed = true;
            }
            else
            {
                if(lvalType->isStruct() && exprType->isStruct())
                {
                    allowed = false;
                }
                else if(exprType->isFloat() && lvalType->isInt())
                {
                    allowed = false;
                }
                else if(lvalType == charDecl && exprType != charDecl)
                {
                    allowed = false;
                }
                else if(lvalType->isStruct() && exprType->isInt())
                {
                    allowed = false;
                }
                else if(lvalType->isInt() && exprType->isStruct())
                {
                    allowed = false;
                }
            }

            if(allowed == true)
            {
                AddChild(lval);
                AddChild(expr);
            }
            else
            {
                string err = "Cannot assign " + exprType->GetName() + " to " + lvalType->GetName();
                SemanticError("test");
            }
        }

        virtual string NodeType() { return string("assign"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
