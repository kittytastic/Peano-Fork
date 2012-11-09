/* This file was generated by SableCC (http://www.sablecc.org/). */

package org.peano.pdt.node;

import java.util.*;
import org.peano.pdt.analysis.*;

@SuppressWarnings("nls")
public final class AVertex extends PVertex
{
    private TFilename _filename_;
    private final LinkedList<POperation> _operation_ = new LinkedList<POperation>();

    public AVertex()
    {
        // Constructor
    }

    public AVertex(
        @SuppressWarnings("hiding") TFilename _filename_,
        @SuppressWarnings("hiding") List<POperation> _operation_)
    {
        // Constructor
        setFilename(_filename_);

        setOperation(_operation_);

    }

    @Override
    public Object clone()
    {
        return new AVertex(
            cloneNode(this._filename_),
            cloneList(this._operation_));
    }

    public void apply(Switch sw)
    {
        ((Analysis) sw).caseAVertex(this);
    }

    public TFilename getFilename()
    {
        return this._filename_;
    }

    public void setFilename(TFilename node)
    {
        if(this._filename_ != null)
        {
            this._filename_.parent(null);
        }

        if(node != null)
        {
            if(node.parent() != null)
            {
                node.parent().removeChild(node);
            }

            node.parent(this);
        }

        this._filename_ = node;
    }

    public LinkedList<POperation> getOperation()
    {
        return this._operation_;
    }

    public void setOperation(List<POperation> list)
    {
        this._operation_.clear();
        this._operation_.addAll(list);
        for(POperation e : list)
        {
            if(e.parent() != null)
            {
                e.parent().removeChild(e);
            }

            e.parent(this);
        }
    }

    @Override
    public String toString()
    {
        return ""
            + toString(this._filename_)
            + toString(this._operation_);
    }

    @Override
    void removeChild(@SuppressWarnings("unused") Node child)
    {
        // Remove child
        if(this._filename_ == child)
        {
            this._filename_ = null;
            return;
        }

        if(this._operation_.remove(child))
        {
            return;
        }

        throw new RuntimeException("Not a child.");
    }

    @Override
    void replaceChild(@SuppressWarnings("unused") Node oldChild, @SuppressWarnings("unused") Node newChild)
    {
        // Replace child
        if(this._filename_ == oldChild)
        {
            setFilename((TFilename) newChild);
            return;
        }

        for(ListIterator<POperation> i = this._operation_.listIterator(); i.hasNext();)
        {
            if(i.next() == oldChild)
            {
                if(newChild != null)
                {
                    i.set((POperation) newChild);
                    newChild.parent(this);
                    oldChild.parent(null);
                    return;
                }

                i.remove();
                oldChild.parent(null);
                return;
            }
        }

        throw new RuntimeException("Not a child.");
    }
}
