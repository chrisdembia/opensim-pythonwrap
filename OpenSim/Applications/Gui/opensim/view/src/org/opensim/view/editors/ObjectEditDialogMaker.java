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
import org.openide.NotifyDescriptor;
import org.opensim.modeling.OpenSimObject;
import org.opensim.view.OpenSimCanvas;

/**
 *
 * @author Ayman
 */
public class ObjectEditDialogMaker {
    ObjectPropertyViewerPanel propertiesPanel;
    AbstractEditorPanel       editorPanel;
    DialogDescriptor          topDialog;
    /**
     * Creates a new instance of ObjectEditDialogMaker
     */
    public ObjectEditDialogMaker(OpenSimObject object, OpenSimCanvas canvas) {
        propertiesPanel = new ObjectPropertyViewerPanel(object, false);
        editorPanel = new VisibilityEditorPanel(object, canvas);
        JPanel topDialogPanel = new JPanel();
        topDialogPanel.setLayout(new BorderLayout());
        topDialogPanel.add(editorPanel, BorderLayout.NORTH);
        topDialogPanel.add(propertiesPanel, BorderLayout.SOUTH);
        topDialog = new DialogDescriptor(topDialogPanel, "Object Editor");
        DialogDisplayer.getDefault().createDialog(topDialog).setVisible(true);
    }

    public void process() {
        Object userInput = topDialog.getValue();
        if (userInput instanceof Integer){
            Integer ret = (Integer)userInput;
            if (ret!=DialogDescriptor.OK_OPTION){
                editorPanel.cancelEdit();
            }
            else
                editorPanel.confirmEdit();
        }
    }
}
