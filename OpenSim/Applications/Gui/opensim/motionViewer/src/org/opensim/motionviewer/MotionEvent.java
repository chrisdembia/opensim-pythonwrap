/*
 *
 * MotionEvent
 * Author(s): Ayman Habib
 * Copyright (c) 2005-2006, Stanford University, Ayman Habib
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
package org.opensim.motionviewer;

import java.util.EventObject;
import org.opensim.modeling.SimmMotionData;

/**
 *
 * @author Ayman
 */
   /** Creates a new instance of MotionEvent */
public class MotionEvent extends EventObject {
    
    public enum Operation{Open, Close, Save, SetCurrent};
    
    Operation op= Operation.Open;
    /**
     * Creates a new instance of MotionEvent
     */
    public MotionEvent(SimmMotionData source, Operation op) {
        super(source);
        this.op = op;
    }
    
    public SimmMotionData getMotion()
    {
        return (SimmMotionData) source;
    }
    
    public MotionEvent.Operation getOperation()
    {
        return op;
    }
}

