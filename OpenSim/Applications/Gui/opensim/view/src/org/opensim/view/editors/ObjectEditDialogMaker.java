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

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JPanel;
import org.openide.DialogDescriptor;
import org.openide.DialogDisplayer;
import org.opensim.modeling.OpenSimObject;
import org.opensim.view.ModelWindowVTKTopComponent;
import org.opensim.view.pub.ViewDB;

/**
 *
 * @author Ayman Habib
 */
public class ObjectEditDialogMaker {
    ObjectPropertyViewerPanel propertiesEditorPanel=null;
    AbstractEditorPanel       typeSpecificEditorPanel=null;
    DialogDescriptor          topDialog;
    OpenSimObject             objectToEdit;
    JButton                   confirmButton = new JButton("OK");
    /**
     * Creates a new instance of ObjectEditDialogMaker
     */
    public ObjectEditDialogMaker(OpenSimObject object, ModelWindowVTKTopComponent owner, boolean allowEdit, String confirmButtonText) {
        // If allowEdit is true,aAssume we're editing properties from a file, so we'll call it "Save" instead of "OK"
        confirmButton.setText(confirmButtonText);

        objectToEdit = object;
        propertiesEditorPanel = new ObjectPropertyViewerPanel(object, allowEdit);
        JPanel topDialogPanel = new JPanel();
        topDialogPanel.setLayout(new BoxLayout(topDialogPanel, BoxLayout.Y_AXIS));

        if (object.getDisplayer()!=null &&
                ViewDB.getInstance().getVtkRepForObject(object)!=null){   // This should be made more general to account for other editing
            typeSpecificEditorPanel = new VisibilityEditorPanel(object, owner);
            typeSpecificEditorPanel.setAlignmentY(0);
            typeSpecificEditorPanel.setAlignmentX(0);
            topDialogPanel.add(typeSpecificEditorPanel);
        }

        propertiesEditorPanel.setAlignmentY(0);
        propertiesEditorPanel.setAlignmentX(0);
        topDialogPanel.add(propertiesEditorPanel);

        // @todo Check that the object is visible first to avoid crashing downstream
        String name = allowEdit ? "Property Editor" : "Property Viewer";
        topDialog = new DialogDescriptor(topDialogPanel, name);
        topDialog.setOptions(new Object[]{confirmButton, DialogDescriptor.CANCEL_OPTION});
        // Make undoredo
        DialogDisplayer.getDefault().createDialog(topDialog).setVisible(true);
    }
    /**
     * Just review, no edit
     *
     * @todo handle the case of null owner (if no ModelWindowVTKTopComponent is open)
     */
    public ObjectEditDialogMaker(OpenSimObject object, ModelWindowVTKTopComponent owner) {
        this(object, owner, false, "OK");
    }
    
    /**
     * Non visible objects
     */
     public ObjectEditDialogMaker(OpenSimObject object, boolean allowEdit, String confirmButtonText) {
        this(object, null, allowEdit, confirmButtonText);
     }

     public ObjectEditDialogMaker(OpenSimObject object, boolean allowEdit) {
        this(object, null, allowEdit, "OK");
     }
     
    /**
     * process handles the closing of the Editor dialog and calls corresponding AbstractEditor methods
     * It also return a boolean true for confirm, false otherwise
     */
    public boolean process() {
        Object userInput = topDialog.getValue();
        boolean confirm = (userInput==confirmButton);
        if(typeSpecificEditorPanel!=null) {
           if(confirm) typeSpecificEditorPanel.confirmEdit();
           else typeSpecificEditorPanel.cancelEdit();
        }
        return confirm;
    }
}
