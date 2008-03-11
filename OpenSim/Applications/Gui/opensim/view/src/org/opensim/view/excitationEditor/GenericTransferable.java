package org.opensim.view.excitationEditor;

/*****************************************************************************************************
 * GenericTransferable.java
 * author: Ulrich Hilger
 * http://articles.lightdev.com/tree/tree_article.pdf
 *
 * This class is very general and may contain an Array
 * of selected Tree Paths in the object "data".
 * The object is given to the constructor and returned by the method "getTransferData".
 * Here we use "DataFlavor.stringFlavor", however this is ignored in the implementation.
 ****************************************************************************************************/

import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.io.IOException;

public class GenericTransferable implements Transferable {

    public GenericTransferable(Object data) {
        super();
        this.data = data;
    }

    public DataFlavor[] getTransferDataFlavors() {
        return flavors;
    }

    public boolean isDataFlavorSupported(DataFlavor flavor) {
        return true;
    }

    public Object getTransferData(DataFlavor flavor) throws UnsupportedFlavorException, IOException {
        return data;
    }
    private Object data;
    private static final DataFlavor[] flavors = new DataFlavor[1];
    static {
        flavors[0] = DataFlavor.stringFlavor;
    }
}