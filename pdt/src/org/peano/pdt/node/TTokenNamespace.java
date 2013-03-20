/* This file was generated by SableCC (http://www.sablecc.org/). */

package org.peano.pdt.node;

import org.peano.pdt.analysis.*;

@SuppressWarnings("nls")
public final class TTokenNamespace extends Token
{
    public TTokenNamespace()
    {
        super.setText("namespace:");
    }

    public TTokenNamespace(int line, int pos)
    {
        super.setText("namespace:");
        setLine(line);
        setPos(pos);
    }

    @Override
    public Object clone()
    {
      return new TTokenNamespace(getLine(), getPos());
    }

    public void apply(Switch sw)
    {
        ((Analysis) sw).caseTTokenNamespace(this);
    }

    @Override
    public void setText(@SuppressWarnings("unused") String text)
    {
        throw new RuntimeException("Cannot change TTokenNamespace text.");
    }
}
