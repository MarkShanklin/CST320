#pragma once
/*******************************************
 * Author: Mark Shanklin
 * mark.shanklin@oit.edu
 *
 *
 * Date: Feb. 23, 2016
 ******************************************/
#include "cVisitor.h"
class cComputeSize : public cVisitor
{
    public:
        cComputeSize() : cVisitor()
        {
            m_varAlign = false;
            m_offset = 0;
            m_highWater = m_offset;
        }

        virtual void VisitAllNodes(cAstNode* node) { node->Visit(this); }

        int GetHighWater() { return m_highWater; }

        virtual void Visit(cBlockNode* node)
        {
            int startPoint = m_offset;
            int highWater = m_highWater;
            m_highWater = m_offset;
            
            VisitAllChildren(node);

            node->SetSize(m_highWater - startPoint);
            m_highWater = std::max(highWater, m_highWater);
            m_offset = startPoint;
            UpdateMoffset(m_offset);
        }

        virtual void Visit(cDeclsNode* node)
        {
            int startPoint = m_offset;
            VisitAllChildren(node);
            node->SetSize(m_offset - startPoint);
        }

        virtual void Visit(cVarDeclNode* node)
        {
            int size;
            size = node->GetType()->GetSize();
            node->SetSize(size);
            if(size > 1 || m_varAlign){UpdateMoffset(WordAlign(m_offset));}
            node->SetOffset(m_offset);
            m_offset += size;
            UpdateMoffset(m_offset); 
        }

        virtual void Visit(cStructDeclNode* node)
        {
            int startPoint = m_offset;
            m_offset = 0;
            VisitAllChildren(node);
            node->SetSize(m_offset);
            m_offset = startPoint;
        }
        
        virtual void Visit(cFuncDeclNode* node)
        {
            int startPoint = m_offset;
            int highWater = m_highWater;
            m_offset = 0;
            VisitAllChildren(node);
            UpdateMoffset(WordAlign(m_offset));
            node->SetSize(m_highWater);
            
            m_offset = startPoint;
            m_highWater = highWater;
        }
        
        virtual void Visit(cParamsNode* node)
        {  
            m_varAlign = true;
            int startPoint = m_offset;
            UpdateMoffset(WordAlign(m_offset));
            VisitAllChildren(node);
            UpdateMoffset(WordAlign(m_offset));
            node->SetSize(m_offset - startPoint);
            m_varAlign = false;
        }
        
        virtual void Visit(cVarExprNode* node)
        {
            m_varAlign = true;
            int startPoint = m_offset;
            m_offset = 0; 
            VisitAllChildren(node);
            int size = node->GetType()->Sizeof();
            node->SetSize(size);
            if(size == 1)
            {}
            else
            m_offset += size;
            if(size > 1){UpdateMoffset(WordAlign(m_offset));}
            WordAlign(m_offset);
            node->SetOffset(m_offset);
            m_offset = startPoint;
            m_varAlign = false;
        }

    protected:
        int m_offset;
        int m_highWater;
        bool m_varAlign;

        int WordAlign (int value)
        {  
           if(value%4 != 0) 
            value += 4 - value%4;

            return value;
        }
        void UpdateMoffset(int value)
        {
            if (value > m_highWater)
            {
                m_highWater = value;
            }
            m_offset = value;
        }
};
