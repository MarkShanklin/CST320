#pragma once
/*******************************************
 * cIfNode.h
 *
 * Defines AST node for if and else statments.
 *
 * Author: Mark Shanklin
 * mark.shanklin@oit.edu
 *
 * Date: Feb. 02, 2016
 ******************************************/

#include "cAstNode.h"
#include "cStmtNode.h"

class cIfNode : public cStmtNode
{
    public:
        cIfNode(cExprNode *expr, cStmtsNode *ifStmts, cStmtsNode *elseStmts ) : cStmtNode()
        {   
            AddChild(expr);
            AddChild(ifStmts);
            AddChild(elseStmts);
        }
    virtual string NodeType() { return string("if"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
