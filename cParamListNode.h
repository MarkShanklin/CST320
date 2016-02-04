#pragma once
/*******************************************
 * cParamListNode.h
 *
 * Author: Mark Shanklin
 * mark.shanklin@oit.edu
 *
 * Date: Feb. 03, 2016
 ******************************************/

#include "cAstNode.h"
#include "cExprNode.h"

class cParamListNode : public cExprNode
{
    public:
        cParamListNode(cExprNode *params)
        {
            AddChild(params);
        }
        void Insert(cExprNode *params)
        {
            AddChild(params);
        }
        virtual string NodeType() { return string("params"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
