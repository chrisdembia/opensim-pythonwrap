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

import java.util.HashMap;
import java.util.Observable;
import java.util.Observer;
import org.opensim.common.OpenSimDB;
import org.opensim.modeling.SimmModel;

/**
 *
 * @author Ayman
 *
 * A class to represent the top level view of the database/Model. 
 * ViewDB maintains the list of open model windows.
 */
final public class ViewDB implements Observer {
    
    static ViewDB instance=null;

    static HashMap<String, SimmModel> mapNamesToModels = new HashMap<String, SimmModel>(4);
    
    /** Creates a new instance of ViewDB */
    private ViewDB() {
    }
    
    public static synchronized ViewDB getInstance() {
        if (instance == null) {
            instance = new ViewDB();
            OpenSimDB db = OpenSimDB.getInstance();
            db.addObserver(instance);
        }
        return instance;
    }
    /**
     * Implement method of Observer interface. We'll be notified whenevr a change happens in the database 
     * that requires view update.
     */
    public void update(Observable o, Object arg) {
        int i=0; // View informed
    }
    
    
}
