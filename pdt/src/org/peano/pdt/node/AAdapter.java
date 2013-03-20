/* This file was generated by SableCC (http://www.sablecc.org/). */

package org.peano.pdt.node;

import java.util.*;
import org.peano.pdt.analysis.*;

@SuppressWarnings("nls")
public final class AAdapter extends PAdapter
{
    private TIdentifier _name_;
    private final LinkedList<TIdentifier> _userDefined_ = new LinkedList<TIdentifier>();
    private final LinkedList<PPredefinedAdapter> _predefinedAdapter_ = new LinkedList<PPredefinedAdapter>();

    public AAdapter()
    {
        // Constructor
    }

    public AAdapter(
        @SuppressWarnings("hiding") TIdentifier _name_,
        @SuppressWarnings("hiding") List<TIdentifier> _userDefined_,
        @SuppressWarnings("hiding") List<PPredefinedAdapter> _predefinedAdapter_)
    {
        // Constructor
        setName(_name_);

        setUserDefined(_userDefined_);

        setPredefinedAdapter(_predefinedAdapter_);

    }

    @Override
    public Object clone()
    {
        return new AAdapter(
            cloneNode(this._name_),
            cloneList(this._userDefined_),
            cloneList(this._predefinedAdapter_));
    }

    public void apply(Switch sw)
    {
        ((Analysis) sw).caseAAdapter(this);
    }

    public TIdentifier getName()
    {
        return this._name_;
    }

    public void setName(TIdentifier node)
    {
        if(this._name_ != null)
        {
            this._name_.parent(null);
        }

        if(node != null)
        {
            if(node.parent() != null)
            {
                node.parent().removeChild(node);
            }

            node.parent(this);
        }

        this._name_ = node;
    }

    public LinkedList<TIdentifier> getUserDefined()
    {
        return this._userDefined_;
    }

    public void setUserDefined(List<TIdentifier> list)
    {
        this._userDefined_.clear();
        this._userDefined_.addAll(list);
        for(TIdentifier e : list)
        {
            if(e.parent() != null)
            {
                e.parent().removeChild(e);
            }

            e.parent(this);
        }
    }

    public LinkedList<PPredefinedAdapter> getPredefinedAdapter()
    {
        return this._predefinedAdapter_;
    }

    public void setPredefinedAdapter(List<PPredefinedAdapter> list)
    {
        this._predefinedAdapter_.clear();
        this._predefinedAdapter_.addAll(list);
        for(PPredefinedAdapter e : list)
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
            + toString(this._name_)
            + toString(this._userDefined_)
            + toString(this._predefinedAdapter_);
    }

    @Override
    void removeChild(@SuppressWarnings("unused") Node child)
    {
        // Remove child
        if(this._name_ == child)
        {
            this._name_ = null;
            return;
        }

        if(this._userDefined_.remove(child))
        {
            return;
        }

        if(this._predefinedAdapter_.remove(child))
        {
            return;
        }

        throw new RuntimeException("Not a child.");
    }

    @Override
    void replaceChild(@SuppressWarnings("unused") Node oldChild, @SuppressWarnings("unused") Node newChild)
    {
        // Replace child
        if(this._name_ == oldChild)
        {
            setName((TIdentifier) newChild);
            return;
        }

        for(ListIterator<TIdentifier> i = this._userDefined_.listIterator(); i.hasNext();)
        {
            if(i.next() == oldChild)
            {
                if(newChild != null)
                {
                    i.set((TIdentifier) newChild);
                    newChild.parent(this);
                    oldChild.parent(null);
                    return;
                }

                i.remove();
                oldChild.parent(null);
                return;
            }
        }

        for(ListIterator<PPredefinedAdapter> i = this._predefinedAdapter_.listIterator(); i.hasNext();)
        {
            if(i.next() == oldChild)
            {
                if(newChild != null)
                {
                    i.set((PPredefinedAdapter) newChild);
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
