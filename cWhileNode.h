#pragma once
/*******************************************
 * cWhileNode.h
 *
 * Defines AST node for while statements
 *
 * Inherits from cStmtNode so return statements can go in statement lists, and be
 * used anywhere a statement is legal.
 *
 * Author: Mark Shanklin
 * mark.shanklin@oit.edu
 *
 * Date: Feb. 02, 2016
 ******************************************/

#include "cAstNode.h"
#include "cStmtNode.h"
#include "cExprNode.h"

class cWhileNode : public cStmtNode
{
    public:
        cWhileNode(cExprNode *expr, cStmtNode *stmt) : cStmtNode()
        {
            AddChild(expr);
            AddChild(stmt);
        }
        virtual string NodeType() {return string("while"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
