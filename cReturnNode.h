#pragma once
/*******************************************
 * cReturnNode.h
 *
 * Defines AST node for return statements
 *
 * Inherits from cStmtNode so return statements can go in statement lists, and be
 * used anywhere a statement is legal.
 *
 * Author: Mark Shanklin
 * mark.shanklin@oit.edu
 *
 * Date: Feb. 02, 2016
 ******************************************/

#include "cStmtNode.h"
#include "cAstNode.h"
#include "cExprNode.h"

class cReturnNode : public cStmtNode
{
    public:
        cReturnNode(cExprNode *expr) : cStmtNode()
        {
            AddChild(expr);
        }

        virtual string NodeType() { return string("return"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
