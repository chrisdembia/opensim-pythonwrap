/*
 *
 * ViewDB
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
package org.opensim.view;

import java.util.Hashtable;
import org.opensim.modeling.SimmModel;

/**
 *
 * @author Ayman Habib
 *
 * A Database of Displayed models, maps models to corresponding ModelWindowVTKTopComponents
 * Also keeps track of currently activated ModelWindowVTKTopComponent
 */
public final class ViewDB{
    
    static Hashtable<SimmModel, ModelWindowVTKTopComponent> mapModels2Tc = new Hashtable<SimmModel, ModelWindowVTKTopComponent>(4);
    static ViewDB instance=null;
    private static ModelWindowVTKTopComponent currentModelWindow=null;
    
    
    /** Creates a new instance of ViewDB */
    protected ViewDB() {
    }
    
    /**
     * Enforce a singleton pattern 
     */
    public static ViewDB getInstance()
    {
        if (instance==null){
            instance = new ViewDB();
        }
        return instance;
    }
    /**
     * Add a new model and topcomponent to the map
     */
    public void addModelWindowMap(SimmModel model, ModelWindowVTKTopComponent modelWindow)
    {
        mapModels2Tc.put(model, modelWindow);
    }
    /**
     * Retrieve the Topcomponent for the passed in model.
     */
    public static ModelWindowVTKTopComponent getVTKTopComponentForModel(SimmModel model)
    {
        return mapModels2Tc.get(model);
    }
    /**
     * Remove the passed in model from the map
     */
    public static void removeModel(SimmModel model)
    {
        mapModels2Tc.remove(model);
    }

    public static ModelWindowVTKTopComponent getCurrentModelWindow() {
        return currentModelWindow;
    }

    public static void setCurrentModelWindow(ModelWindowVTKTopComponent aCurrentModelWindow) {
        currentModelWindow = aCurrentModelWindow;
    }

}
