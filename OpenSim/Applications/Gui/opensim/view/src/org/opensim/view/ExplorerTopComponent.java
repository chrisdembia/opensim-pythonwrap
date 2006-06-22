package org.opensim.view;

import java.awt.BorderLayout;
import java.io.IOException;
import java.io.Serializable;
import java.util.HashMap;
import java.util.Observable;
import java.util.Observer;
import org.openide.ErrorManager;
import org.openide.util.NbBundle;
import org.openide.windows.TopComponent;
import org.openide.windows.WindowManager;
import org.opensim.common.OpenSimDB;
import org.opensim.common.ModelEvent;
import org.openide.explorer.ExplorerManager;
import org.openide.explorer.view.BeanTreeView;
import org.openide.nodes.Node;
import org.opensim.modeling.SimmModel;
import org.opensim.view.ModelNode.ConcreteModelNode;
import org.opensim.common.ModelEvent.Operation;
/**
 * Top component which displays something.
 */
final class ExplorerTopComponent extends TopComponent implements Observer, ExplorerManager.Provider  {
    
    private static final long serialVersionUID = 1L;
    
    private static ExplorerTopComponent instance;
    /** path to the icon used by the component and its open action */
//    static final String ICON_PATH = "SET/PATH/TO/ICON/HERE";
    
    private static final String PREFERRED_ID = "ExplorerTopComponent";
    
   private final ExplorerManager manager = new ExplorerManager();
   private final BeanTreeView modelTree = new BeanTreeView();
   private static HashMap<SimmModel, ConcreteModelNode> mapModelsToNodes = new HashMap<SimmModel, ConcreteModelNode>(4);
   
   private ExplorerTopComponent() {
        initComponents();
        setName(NbBundle.getMessage(ExplorerTopComponent.class, "CTL_ExplorerTopComponent"));
        setToolTipText(NbBundle.getMessage(ExplorerTopComponent.class, "HINT_ExplorerTopComponent"));
        // Add explorer as observer of the database
        OpenSimDB.getInstance().addObserver(this);
//        setIcon(Utilities.loadImage(ICON_PATH, true));
        setLayout(new BorderLayout());
        add(modelTree, BorderLayout.CENTER);
        modelTree.setRootVisible(false);
        manager.setRootContext(new ModelNode.RootNode());
    }
   
     BeanTreeView getTree() {
        return modelTree;
    }
   
    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
    private void initComponents() {

        org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(0, 400, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(0, 300, Short.MAX_VALUE)
        );
    }// </editor-fold>//GEN-END:initComponents
    
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    // End of variables declaration//GEN-END:variables
    
    /**
     * Gets default instance. Do not use directly: reserved for *.settings files only,
     * i.e. deserialization routines; otherwise you could get a non-deserialized instance.
     * To obtain the singleton instance, use {@link findInstance}.
     */
    public static synchronized ExplorerTopComponent getDefault() {
        if (instance == null) {
            instance = new ExplorerTopComponent();
        }
        return instance;
    }
    
    /**
     * Obtain the ExplorerTopComponent instance. Never call {@link #getDefault} directly!
     */
    public static synchronized ExplorerTopComponent findInstance() {
        TopComponent win = WindowManager.getDefault().findTopComponent(PREFERRED_ID);
        if (win == null) {
            ErrorManager.getDefault().log(ErrorManager.WARNING, "Cannot find Explorer component. It will not be located properly in the window system.");
            return getDefault();
        }
        if (win instanceof ExplorerTopComponent) {
            return (ExplorerTopComponent)win;
        }
        ErrorManager.getDefault().log(ErrorManager.WARNING, "There seem to be multiple components with the '" + PREFERRED_ID + "' ID. That is a potential source of errors and unexpected behavior.");
        return getDefault();
    }
    
    public int getPersistenceType() {
        return TopComponent.PERSISTENCE_ALWAYS;
    }
    
    public void componentOpened() {
        // TODO add custom code on component opening
        redisplay();
    }
    
    public void componentClosed() {
        // TODO add custom code on component closing
    }
    
    /** replaces this in object stream */
    public Object writeReplace() {
        return new ResolvableHelper();
    }
    
    protected String preferredID() {
        return PREFERRED_ID;
    }

    public void update(Observable o, Object arg) {
        // Observable is OpenSimDB
        if (arg instanceof ModelEvent){
            final ModelEvent evnt = (ModelEvent)arg;
             // Add the model to the Tree window.
            ExplorerTopComponent tree = ExplorerTopComponent.findInstance();

            Node rootNode = tree.getExplorerManager().getRootContext();
            switch(evnt.getOperation()){
                case Open :
                {
                    SimmModel newModel = evnt.getModel();
                    ConcreteModelNode newModelNode = new ModelNode.ConcreteModelNode(newModel);
                    rootNode.getChildren().add(new Node[] { newModelNode});
                    mapModelsToNodes.put(newModel, newModelNode);
                    break;
                }
                case Close:
                {
                    SimmModel closingModel = evnt.getModel();
                    ConcreteModelNode modelNode = mapModelsToNodes.get(closingModel);
                    try {
                        modelNode.destroy();
                    } catch (IOException ex) {
                        ex.printStackTrace();
                    }
                }
                  
            }
 
        }        
    }

    public ExplorerManager getExplorerManager() {
        return manager;
    }
    
    final static class ResolvableHelper implements Serializable {
        private static final long serialVersionUID = 1L;
        public Object readResolve() {
            return ExplorerTopComponent.getDefault();
        }
    }
    
    public void redisplay()
    {
        // Sync. up the tree with the OpenSimDB
        OpenSimDB db = OpenSimDB.getInstance();
        

        Node rootNode = getExplorerManager().getRootContext();

        Object[] models = db.getAllModels();
        for(int i=0; i < models.length; i++)
            rootNode.getChildren().add(new Node[] { new ModelNode.ConcreteModelNode((SimmModel)models[i]) });

    }
}
