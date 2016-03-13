#pragma once

//Author: Mark Shanklin
//mark.shanklin@oit.edu
//Date: Mar. 03, 2016

#include "cVisitor.h"
#include "emit.h"

const int INT = 4;
const int FLOAT = 8;

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
        
        virtual void Visit(cProgramNode *node)
        {
            EmitString("Stack_Pointer += ");
            EmitInt(node->GetBlock()->GetSize());
            EmitString(";\n");
            VisitAllChildren(node);
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
        
        virtual void Visit(cVarExprNode *node)
        { 
            if(node->GetType()->IsFloat())
            {
                EmitString("*(double *)&Memory[Frame_Pointer+");
                EmitInt(node->GetOffset());
                EmitString("]");
            }
            else if(node->GetSize() == 1)
            {
                EmitString("Memory[Frame_Pointer+");
                EmitInt(node->GetOffset());
                EmitString("]");
            }
            else
            {
                EmitString("*(int *)&Memory[Frame_Pointer+");
                EmitInt(node->GetOffset());
                EmitString("]");
            }
        }

        virtual void Visit(cAssignNode *node)
        {
            if(node->GetExpr()->GetDecl() != nullptr && node->GetExpr()->GetDecl()->IsFunc())
            {
                node->GetExpr()->Visit(this);
                node->GetLval()->Visit(this);

                if(node->GetExpr()->GetType()->IsFloat())
                {
                    EmitString(" = Temp_F;\n");
                }
                else
                {    
                    EmitString(" = Temp;\n");
                }
            }
            else
            {
                node->GetLval()->Visit(this);
                EmitString("=");
                node->GetExpr()->Visit(this);
                EmitString(";\n");
            }
        }
        virtual void Visit(cBinaryExprNode *node)
        {   
            node->GetLeft()->Visit(this);
            EmitString(node->GetOp()->GetOpAsString());
            node->GetRight()->Visit(this);
        }
        virtual void Visit(cIfNode *node)
        {
            std::string End = GenerateLabel();
            if(node->GetElseStmt() != nullptr)
            {
                std::string Else = GenerateLabel();
                EmitString("if((");
                node->GetCond()->Visit(this);
                EmitString(") == 0) goto " + Else + ";\n");
                node->GetIfStmt()->Visit(this);
                EmitString(" goto " + End + ";\n");
                EmitString( Else + ":\n");
                node->GetElseStmt()->Visit(this);
                EmitString( End + ":\n");
            }
            else
            {
                EmitString("if((");
                node->GetCond()->Visit(this);
                EmitString(") == 0) goto " + End + ";\n");
                node->GetIfStmt()->Visit(this);
                EmitString( End + ":\n");
            }      
        }
        virtual void Visit(cWhileNode *node)
        {
            std::string End = GenerateLabel();
            std::string Start = GenerateLabel();
            EmitString( Start + ":\n");
            EmitString("if((");
            node->GetCond()->Visit(this);
            EmitString(") == 0) goto " + End + ";\n");
            node->GetStmt()->Visit(this);
            EmitString(" goto " + Start + ";\n");
            EmitString( End + ":\n");
        }
        virtual void Visit(cFuncExprNode *node)
        {
            EmitString("*(int *)&Memory[Stack_Pointer]= Frame_Pointer;\n");
            EmitString("Stack_Pointer +=");
            EmitInt(INT);
            EmitString(";\n");
            if(node->GetParams() != nullptr)
            {
                int j = node->GetParams()->NumChildren();
                for(int i = 0; i < j; i++)
                {
                    cExprNode* temp = node->GetParams()->GetParam(i);
                    if(temp->GetType()->IsFloat())
                    {
                        EmitString("*(double *)&Memory[Stack_Pointer] = ");
                        temp->Visit(this);
                        EmitString(";\n");
                        EmitString("Stack_Pointer +=");
                        EmitInt(FLOAT); 
                        EmitString(";\n");
                    }
                    else
                    {
                        EmitString("*(int *)&Memory[Stack_Pointer] = ");
                        temp->Visit(this);
                        EmitString(";\n");
                        EmitString("Stack_Pointer +=");
                        EmitInt(INT);
                        EmitString(";\n");
                    }
                }
                EmitString("Frame_Pointer = Stack_Pointer;\n");
                EmitString("Frame_Pointer -= ");
                EmitInt(node->GetFuncDecl()->GetParams()->GetSize());
                EmitString(";\n");                
            }
            else
            {
                EmitString("Frame_Pointer = Stack_Pointer;\n");
            }
            
            EmitString(node->GetName() + "();\n");

            if(node->GetParams() != nullptr)
            {
                EmitString("Stack_Pointer -=");
                EmitInt(node->GetFuncDecl()->GetParams()->GetSize());
                EmitString(";\n");
            }
                EmitString("Stack_Pointer -=");
                EmitInt(INT);
                EmitString(";\n");
                EmitString("Frame_Pointer = *(int *)&Memory[Stack_Pointer];\n");
        }
        virtual void Visit(cFuncDeclNode *node)
        {
            if(node->GetLocals() || node->GetStmts())
            {
                returnPoint = GenerateLabel();
                StartFunctionOutput(node->GetName());
                if(node->GetLocals())
                {
                    EmitString("Stack_Pointer += ");
                    EmitInt(node->GetLocals()->GetSize());
                    EmitString(";\n");
                    node->GetLocals()->Visit(this);
                }
                if(node->GetStmts())
                {
                    node->GetStmts()->Visit(this);
                }
                EmitString(returnPoint + ":\n");
                if(node->GetLocals())
                {
                    EmitString("Stack_Pointer -=");
                    EmitInt(node->GetLocals()->GetSize());
                    EmitString(";\n");
                }
                EndFunctionOutput();
            }    
        }
        virtual void Visit(cReturnNode *node)
        {
            if(node->GetExpr()->GetType()->IsFloat())
            {
                EmitString("Temp_F= ");
            }
            else
            {
                EmitString("Temp= ");
            }
            node->GetExpr()->Visit(this);
            EmitString(";\n");
            EmitString("goto " + returnPoint + ";\n");
        }
        

    protected:
        std::string returnPoint;
};
