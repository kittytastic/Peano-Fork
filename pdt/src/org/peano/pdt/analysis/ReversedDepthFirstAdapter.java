/* This file was generated by SableCC (http://www.sablecc.org/). */

package org.peano.pdt.analysis;

import java.util.*;
import org.peano.pdt.node.*;

public class ReversedDepthFirstAdapter extends AnalysisAdapter
{
    public void inStart(Start node)
    {
        defaultIn(node);
    }

    public void outStart(Start node)
    {
        defaultOut(node);
    }

    public void defaultIn(@SuppressWarnings("unused") Node node)
    {
        // Do nothing
    }

    public void defaultOut(@SuppressWarnings("unused") Node node)
    {
        // Do nothing
    }

    @Override
    public void caseStart(Start node)
    {
        inStart(node);
        node.getEOF().apply(this);
        node.getPDescription().apply(this);
        outStart(node);
    }

    public void inADescription(ADescription node)
    {
        defaultIn(node);
    }

    public void outADescription(ADescription node)
    {
        defaultOut(node);
    }

    @Override
    public void caseADescription(ADescription node)
    {
        inADescription(node);
        {
            List<PAdapter> copy = new ArrayList<PAdapter>(node.getAdapter());
            Collections.reverse(copy);
            for(PAdapter e : copy)
            {
                e.apply(this);
            }
        }
        {
            List<PEventMapping> copy = new ArrayList<PEventMapping>(node.getEventMapping());
            Collections.reverse(copy);
            for(PEventMapping e : copy)
            {
                e.apply(this);
            }
        }
        if(node.getState() != null)
        {
            node.getState().apply(this);
        }
        if(node.getCell() != null)
        {
            node.getCell().apply(this);
        }
        if(node.getVertex() != null)
        {
            node.getVertex().apply(this);
        }
        {
            List<PHeapDastgenFile> copy = new ArrayList<PHeapDastgenFile>(node.getHeapDastgenFile());
            Collections.reverse(copy);
            for(PHeapDastgenFile e : copy)
            {
                e.apply(this);
            }
        }
        if(node.getNamespace() != null)
        {
            node.getNamespace().apply(this);
        }
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outADescription(node);
    }

    public void inARepository(ARepository node)
    {
        defaultIn(node);
    }

    public void outARepository(ARepository node)
    {
        defaultOut(node);
    }

    @Override
    public void caseARepository(ARepository node)
    {
        inARepository(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outARepository(node);
    }

    public void inAVertex(AVertex node)
    {
        defaultIn(node);
    }

    public void outAVertex(AVertex node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAVertex(AVertex node)
    {
        inAVertex(node);
        {
            List<POperation> copy = new ArrayList<POperation>(node.getOperation());
            Collections.reverse(copy);
            for(POperation e : copy)
            {
                e.apply(this);
            }
        }
        if(node.getFilename() != null)
        {
            node.getFilename().apply(this);
        }
        outAVertex(node);
    }

    public void inAReadScalarDoubleOperation(AReadScalarDoubleOperation node)
    {
        defaultIn(node);
    }

    public void outAReadScalarDoubleOperation(AReadScalarDoubleOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAReadScalarDoubleOperation(AReadScalarDoubleOperation node)
    {
        inAReadScalarDoubleOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAReadScalarDoubleOperation(node);
    }

    public void inAReadVectorDoubleOperation(AReadVectorDoubleOperation node)
    {
        defaultIn(node);
    }

    public void outAReadVectorDoubleOperation(AReadVectorDoubleOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAReadVectorDoubleOperation(AReadVectorDoubleOperation node)
    {
        inAReadVectorDoubleOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAReadVectorDoubleOperation(node);
    }

    public void inAReadVectorTwoPowDDoubleOperation(AReadVectorTwoPowDDoubleOperation node)
    {
        defaultIn(node);
    }

    public void outAReadVectorTwoPowDDoubleOperation(AReadVectorTwoPowDDoubleOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAReadVectorTwoPowDDoubleOperation(AReadVectorTwoPowDDoubleOperation node)
    {
        inAReadVectorTwoPowDDoubleOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAReadVectorTwoPowDDoubleOperation(node);
    }

    public void inAReadStencilDoubleOperation(AReadStencilDoubleOperation node)
    {
        defaultIn(node);
    }

    public void outAReadStencilDoubleOperation(AReadStencilDoubleOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAReadStencilDoubleOperation(AReadStencilDoubleOperation node)
    {
        inAReadStencilDoubleOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAReadStencilDoubleOperation(node);
    }

    public void inAReadIntergridOperatorDoubleOperation(AReadIntergridOperatorDoubleOperation node)
    {
        defaultIn(node);
    }

    public void outAReadIntergridOperatorDoubleOperation(AReadIntergridOperatorDoubleOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAReadIntergridOperatorDoubleOperation(AReadIntergridOperatorDoubleOperation node)
    {
        inAReadIntergridOperatorDoubleOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAReadIntergridOperatorDoubleOperation(node);
    }

    public void inAWriteScalarDoubleOperation(AWriteScalarDoubleOperation node)
    {
        defaultIn(node);
    }

    public void outAWriteScalarDoubleOperation(AWriteScalarDoubleOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAWriteScalarDoubleOperation(AWriteScalarDoubleOperation node)
    {
        inAWriteScalarDoubleOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAWriteScalarDoubleOperation(node);
    }

    public void inAWriteVectorDoubleOperation(AWriteVectorDoubleOperation node)
    {
        defaultIn(node);
    }

    public void outAWriteVectorDoubleOperation(AWriteVectorDoubleOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAWriteVectorDoubleOperation(AWriteVectorDoubleOperation node)
    {
        inAWriteVectorDoubleOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAWriteVectorDoubleOperation(node);
    }

    public void inAWriteVectorTwoPowDDoubleOperation(AWriteVectorTwoPowDDoubleOperation node)
    {
        defaultIn(node);
    }

    public void outAWriteVectorTwoPowDDoubleOperation(AWriteVectorTwoPowDDoubleOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAWriteVectorTwoPowDDoubleOperation(AWriteVectorTwoPowDDoubleOperation node)
    {
        inAWriteVectorTwoPowDDoubleOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAWriteVectorTwoPowDDoubleOperation(node);
    }

    public void inAWriteStencilDoubleOperation(AWriteStencilDoubleOperation node)
    {
        defaultIn(node);
    }

    public void outAWriteStencilDoubleOperation(AWriteStencilDoubleOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAWriteStencilDoubleOperation(AWriteStencilDoubleOperation node)
    {
        inAWriteStencilDoubleOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAWriteStencilDoubleOperation(node);
    }

    public void inAWriteIntergridOperatorDoubleOperation(AWriteIntergridOperatorDoubleOperation node)
    {
        defaultIn(node);
    }

    public void outAWriteIntergridOperatorDoubleOperation(AWriteIntergridOperatorDoubleOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAWriteIntergridOperatorDoubleOperation(AWriteIntergridOperatorDoubleOperation node)
    {
        inAWriteIntergridOperatorDoubleOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAWriteIntergridOperatorDoubleOperation(node);
    }

    public void inAReadScalarIntOperation(AReadScalarIntOperation node)
    {
        defaultIn(node);
    }

    public void outAReadScalarIntOperation(AReadScalarIntOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAReadScalarIntOperation(AReadScalarIntOperation node)
    {
        inAReadScalarIntOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAReadScalarIntOperation(node);
    }

    public void inAReadVectorIntOperation(AReadVectorIntOperation node)
    {
        defaultIn(node);
    }

    public void outAReadVectorIntOperation(AReadVectorIntOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAReadVectorIntOperation(AReadVectorIntOperation node)
    {
        inAReadVectorIntOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAReadVectorIntOperation(node);
    }

    public void inAReadVectorTwoPowDIntOperation(AReadVectorTwoPowDIntOperation node)
    {
        defaultIn(node);
    }

    public void outAReadVectorTwoPowDIntOperation(AReadVectorTwoPowDIntOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAReadVectorTwoPowDIntOperation(AReadVectorTwoPowDIntOperation node)
    {
        inAReadVectorTwoPowDIntOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAReadVectorTwoPowDIntOperation(node);
    }

    public void inAReadStencilIntOperation(AReadStencilIntOperation node)
    {
        defaultIn(node);
    }

    public void outAReadStencilIntOperation(AReadStencilIntOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAReadStencilIntOperation(AReadStencilIntOperation node)
    {
        inAReadStencilIntOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAReadStencilIntOperation(node);
    }

    public void inAReadIntergridOperatorIntOperation(AReadIntergridOperatorIntOperation node)
    {
        defaultIn(node);
    }

    public void outAReadIntergridOperatorIntOperation(AReadIntergridOperatorIntOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAReadIntergridOperatorIntOperation(AReadIntergridOperatorIntOperation node)
    {
        inAReadIntergridOperatorIntOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAReadIntergridOperatorIntOperation(node);
    }

    public void inAWriteScalarIntOperation(AWriteScalarIntOperation node)
    {
        defaultIn(node);
    }

    public void outAWriteScalarIntOperation(AWriteScalarIntOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAWriteScalarIntOperation(AWriteScalarIntOperation node)
    {
        inAWriteScalarIntOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAWriteScalarIntOperation(node);
    }

    public void inAWriteVectorIntOperation(AWriteVectorIntOperation node)
    {
        defaultIn(node);
    }

    public void outAWriteVectorIntOperation(AWriteVectorIntOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAWriteVectorIntOperation(AWriteVectorIntOperation node)
    {
        inAWriteVectorIntOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAWriteVectorIntOperation(node);
    }

    public void inAWriteVectorTwoPowDIntOperation(AWriteVectorTwoPowDIntOperation node)
    {
        defaultIn(node);
    }

    public void outAWriteVectorTwoPowDIntOperation(AWriteVectorTwoPowDIntOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAWriteVectorTwoPowDIntOperation(AWriteVectorTwoPowDIntOperation node)
    {
        inAWriteVectorTwoPowDIntOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAWriteVectorTwoPowDIntOperation(node);
    }

    public void inAWriteStencilIntOperation(AWriteStencilIntOperation node)
    {
        defaultIn(node);
    }

    public void outAWriteStencilIntOperation(AWriteStencilIntOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAWriteStencilIntOperation(AWriteStencilIntOperation node)
    {
        inAWriteStencilIntOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAWriteStencilIntOperation(node);
    }

    public void inAWriteIntergridOperatorIntOperation(AWriteIntergridOperatorIntOperation node)
    {
        defaultIn(node);
    }

    public void outAWriteIntergridOperatorIntOperation(AWriteIntergridOperatorIntOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAWriteIntergridOperatorIntOperation(AWriteIntergridOperatorIntOperation node)
    {
        inAWriteIntergridOperatorIntOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAWriteIntergridOperatorIntOperation(node);
    }

    public void inAReadScalarComplexOperation(AReadScalarComplexOperation node)
    {
        defaultIn(node);
    }

    public void outAReadScalarComplexOperation(AReadScalarComplexOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAReadScalarComplexOperation(AReadScalarComplexOperation node)
    {
        inAReadScalarComplexOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAReadScalarComplexOperation(node);
    }

    public void inAReadVectorComplexOperation(AReadVectorComplexOperation node)
    {
        defaultIn(node);
    }

    public void outAReadVectorComplexOperation(AReadVectorComplexOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAReadVectorComplexOperation(AReadVectorComplexOperation node)
    {
        inAReadVectorComplexOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAReadVectorComplexOperation(node);
    }

    public void inAReadVectorTwoPowDComplexOperation(AReadVectorTwoPowDComplexOperation node)
    {
        defaultIn(node);
    }

    public void outAReadVectorTwoPowDComplexOperation(AReadVectorTwoPowDComplexOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAReadVectorTwoPowDComplexOperation(AReadVectorTwoPowDComplexOperation node)
    {
        inAReadVectorTwoPowDComplexOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAReadVectorTwoPowDComplexOperation(node);
    }

    public void inAReadStencilComplexOperation(AReadStencilComplexOperation node)
    {
        defaultIn(node);
    }

    public void outAReadStencilComplexOperation(AReadStencilComplexOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAReadStencilComplexOperation(AReadStencilComplexOperation node)
    {
        inAReadStencilComplexOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAReadStencilComplexOperation(node);
    }

    public void inAReadIntergridOperatorComplexOperation(AReadIntergridOperatorComplexOperation node)
    {
        defaultIn(node);
    }

    public void outAReadIntergridOperatorComplexOperation(AReadIntergridOperatorComplexOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAReadIntergridOperatorComplexOperation(AReadIntergridOperatorComplexOperation node)
    {
        inAReadIntergridOperatorComplexOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAReadIntergridOperatorComplexOperation(node);
    }

    public void inAWriteScalarComplexOperation(AWriteScalarComplexOperation node)
    {
        defaultIn(node);
    }

    public void outAWriteScalarComplexOperation(AWriteScalarComplexOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAWriteScalarComplexOperation(AWriteScalarComplexOperation node)
    {
        inAWriteScalarComplexOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAWriteScalarComplexOperation(node);
    }

    public void inAWriteVectorComplexOperation(AWriteVectorComplexOperation node)
    {
        defaultIn(node);
    }

    public void outAWriteVectorComplexOperation(AWriteVectorComplexOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAWriteVectorComplexOperation(AWriteVectorComplexOperation node)
    {
        inAWriteVectorComplexOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAWriteVectorComplexOperation(node);
    }

    public void inAWriteVectorTwoPowDComplexOperation(AWriteVectorTwoPowDComplexOperation node)
    {
        defaultIn(node);
    }

    public void outAWriteVectorTwoPowDComplexOperation(AWriteVectorTwoPowDComplexOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAWriteVectorTwoPowDComplexOperation(AWriteVectorTwoPowDComplexOperation node)
    {
        inAWriteVectorTwoPowDComplexOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAWriteVectorTwoPowDComplexOperation(node);
    }

    public void inAWriteStencilComplexOperation(AWriteStencilComplexOperation node)
    {
        defaultIn(node);
    }

    public void outAWriteStencilComplexOperation(AWriteStencilComplexOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAWriteStencilComplexOperation(AWriteStencilComplexOperation node)
    {
        inAWriteStencilComplexOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAWriteStencilComplexOperation(node);
    }

    public void inAWriteIntergridOperatorComplexOperation(AWriteIntergridOperatorComplexOperation node)
    {
        defaultIn(node);
    }

    public void outAWriteIntergridOperatorComplexOperation(AWriteIntergridOperatorComplexOperation node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAWriteIntergridOperatorComplexOperation(AWriteIntergridOperatorComplexOperation node)
    {
        inAWriteIntergridOperatorComplexOperation(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAWriteIntergridOperatorComplexOperation(node);
    }

    public void inACell(ACell node)
    {
        defaultIn(node);
    }

    public void outACell(ACell node)
    {
        defaultOut(node);
    }

    @Override
    public void caseACell(ACell node)
    {
        inACell(node);
        if(node.getFilename() != null)
        {
            node.getFilename().apply(this);
        }
        outACell(node);
    }

    public void inAState(AState node)
    {
        defaultIn(node);
    }

    public void outAState(AState node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAState(AState node)
    {
        inAState(node);
        if(node.getFilename() != null)
        {
            node.getFilename().apply(this);
        }
        outAState(node);
    }

    public void inAHeapDastgenFile(AHeapDastgenFile node)
    {
        defaultIn(node);
    }

    public void outAHeapDastgenFile(AHeapDastgenFile node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAHeapDastgenFile(AHeapDastgenFile node)
    {
        inAHeapDastgenFile(node);
        if(node.getFilename() != null)
        {
            node.getFilename().apply(this);
        }
        outAHeapDastgenFile(node);
    }

    public void inAEventMapping(AEventMapping node)
    {
        defaultIn(node);
    }

    public void outAEventMapping(AEventMapping node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAEventMapping(AEventMapping node)
    {
        inAEventMapping(node);
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAEventMapping(node);
    }

    public void inAAdapter(AAdapter node)
    {
        defaultIn(node);
    }

    public void outAAdapter(AAdapter node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAAdapter(AAdapter node)
    {
        inAAdapter(node);
        {
            List<PPredefinedAdapter> copy = new ArrayList<PPredefinedAdapter>(node.getPredefinedAdapter());
            Collections.reverse(copy);
            for(PPredefinedAdapter e : copy)
            {
                e.apply(this);
            }
        }
        {
            List<TIdentifier> copy = new ArrayList<TIdentifier>(node.getUserDefined());
            Collections.reverse(copy);
            for(TIdentifier e : copy)
            {
                e.apply(this);
            }
        }
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAAdapter(node);
    }

    public void inAPredefinedAdapter(APredefinedAdapter node)
    {
        defaultIn(node);
    }

    public void outAPredefinedAdapter(APredefinedAdapter node)
    {
        defaultOut(node);
    }

    @Override
    public void caseAPredefinedAdapter(APredefinedAdapter node)
    {
        inAPredefinedAdapter(node);
        {
            List<TIdentifier> copy = new ArrayList<TIdentifier>(node.getParameters());
            Collections.reverse(copy);
            for(TIdentifier e : copy)
            {
                e.apply(this);
            }
        }
        if(node.getName() != null)
        {
            node.getName().apply(this);
        }
        outAPredefinedAdapter(node);
    }
}
