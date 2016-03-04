#pragma once

//Author: Mark Shanklin
//mark.shanklin@oit.edu
//Date: Mar. 03, 2016

#include "cVisitor.h"
#include "emit.h"

class cCodeGen : public cVisitor
{
    public:
        cCodeGen(std::string filename) : cVisitor()
        {
            InitOutput(filename.c_str());
        }
        ~cCodeGen()
        {
            FinalizeOutput();
        }
        
        virtual void VisitAllNodes(cAstNode *node)
        {
            node->Visit(this);
        }
        
        virtual void Visit(cIntExprNode *node)
        {
            EmitInt(node->GetValue());
        }
        
        virtual void Visit(cFloatExprNode *node)
        {
            EmitFloat(node->GetValue());
        }
        
        virtual void Visit(cPrintNode *node)
        {
            if(node->GetExpr()->GetType()->IsFloat())
            {
                EmitString("Temp_F = ");
                node->GetExpr()->Visit(this);
                EmitString(";\n");
                EmitPrintTemp_F();
            }
            else 
            {
                EmitString("Temp = ");
                node->GetExpr()->Visit(this);
                EmitString(";\n");
                EmitPrintTemp();
            }
        }
};