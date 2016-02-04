#pragma once
/*******************************************
 * cFuncExprNode.h
 *
 * Author:Mark Shanklin
 * mark.shanklin@oit.edu
 *
 * Date: Feb. 03, 2016
 ******************************************/

#include "cAstNode.h"
#include "cExprNode.h"
#include "cSymbol.h"
#include "cParamListNode.h"

class cFuncExprNode : public cExprNode
{
    public:
        cFuncExprNode(cSymbol *name, cParamListNode *params)
        {
            AddChild(name);
            AddChild(params);
        }
        virtual string NodeType() { return string("funcCall"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
