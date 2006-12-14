/*
 *
 * ObjectEditDialogMaker
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
package org.opensim.view.editors;

import java.awt.BorderLayout;
import javax.swing.JPanel;
import org.openide.DialogDescriptor;
import org.openide.DialogDisplayer;
import org.opensim.modeling.OpenSimObject;
import org.opensim.view.ModelWindowVTKTopComponent;
import org.opensim.view.ViewDB;

/**
 *
 * @author Ayman Habib
 */
public class ObjectEditDialogMaker {
    ObjectPropertyViewerPanel propertiesEditorPanel=null;
    AbstractEditorPanel       typeSpecificEditorPanel=null;
    DialogDescriptor          topDialog;
    OpenSimObject             objectToEdit;
    /**
     * Creates a new instance of ObjectEditDialogMaker
     */
    public ObjectEditDialogMaker(OpenSimObject object, ModelWindowVTKTopComponent owner, boolean allowEdit) {
        objectToEdit = object;
        propertiesEditorPanel = new ObjectPropertyViewerPanel(object, allowEdit);
        JPanel topDialogPanel = new JPanel();
        topDialogPanel.setLayout(new BorderLayout());
        topDialogPanel.add(propertiesEditorPanel, BorderLayout.SOUTH);
        // @todo Check that the object is visible first to avoid crashing downstream
        if (object.getDisplayer()!=null &&
                ViewDB.getInstance().getActorForObject(object)!=null){   // This should be made more general to account for other editing
            typeSpecificEditorPanel = new VisibilityEditorPanel(object, owner);
            topDialogPanel.add(typeSpecificEditorPanel, BorderLayout.NORTH);
        }
        topDialog = new DialogDescriptor(topDialogPanel, "Object Editor");
        // Make undoredo
        DialogDisplayer.getDefault().createDialog(topDialog).setVisible(true);
    }
    /**
     * Just review, no edit
     *
     * @todo handle the case of null owner (if no ModelWindowVTKTopComponent is open)
     */
    public ObjectEditDialogMaker(OpenSimObject object, ModelWindowVTKTopComponent owner) {
        this(object, owner, false);
    }
    
    /**
     * Non visible objects
     */
     public ObjectEditDialogMaker(OpenSimObject object, boolean allowEdit) {
        this(object, null, allowEdit);
    }
     
    /**
     * process handles the closing of the Editor dialog and calls corresponding AbstractEditor methods
     * It also return a boolean true for confirm, false otherwise
     */
    public boolean process() {
        Object userInput = topDialog.getValue();
        if (userInput instanceof Integer){
            Integer ret = (Integer)userInput;
            if (ret!=DialogDescriptor.OK_OPTION){
                if (typeSpecificEditorPanel!= null)
                    typeSpecificEditorPanel.cancelEdit();
                    
            }
            else{
                if (typeSpecificEditorPanel!= null)
                    typeSpecificEditorPanel.confirmEdit();
            }
        }
        return (((Integer)userInput).compareTo((Integer)DialogDescriptor.OK_OPTION)==0);

    }
}
