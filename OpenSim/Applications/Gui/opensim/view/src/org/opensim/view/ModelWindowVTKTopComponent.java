package org.opensim.view;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.prefs.Preferences;
import javax.swing.Action;
import javax.swing.JFileChooser;
import javax.swing.JToggleButton;
import org.openide.util.NbBundle;
import org.openide.windows.TopComponent;
import org.opensim.utils.FileUtils;
import org.opensim.utils.TheApp;
import org.opensim.view.pub.ViewDB;
import vtk.vtkFileOutputWindow;

/**
 * Top component which displays something.
 */
public class ModelWindowVTKTopComponent extends TopComponent
{
    
    private static final long serialVersionUID = 1L;
    private static int ct = 0; //A counter used to provide names for new models
    private String tabDisplayName;
    Preferences prefs;
    /** path to the icon used by the component and its open action */
//    static final String ICON_PATH = "SET/PATH/TO/ICON/HERE";
    public ModelWindowVTKTopComponent() {
        initComponents();
        setTabDisplayName(NbBundle.getMessage(
                        ModelWindowVTKTopComponent.class,
                        "UnsavedModelNameFormat",
                        new Object[] { new Integer(ct++) }
                ));
//        SwingUtilities.invokeLater(new Runnable(){
 //           public void run() {
                 setName(tabDisplayName);
//            }});
        
        // Set preferred directory for the TopComponent (to be used for all saving, loading, ...
        prefs = Preferences.userNodeForPackage(TheApp.class);
        vtkFileOutputWindow fow = new vtkFileOutputWindow();
        fow.SetFileName("vtklog.log");
        if (fow != null)
           fow.SetInstance(fow);   
    }
    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
    private void initComponents() {
        jRefitModelButton = new javax.swing.JButton();
        jModelWiondowToolBar = new javax.swing.JToolBar();
        jFrontViewButton = new javax.swing.JButton();
        jTopViewButton = new javax.swing.JButton();
        jSideViewButton = new javax.swing.JButton();
        jTakeSnapshotButton = new javax.swing.JButton();
        jStartStopMovieToggleButton = new javax.swing.JToggleButton();
        openSimCanvas1 = new org.opensim.view.OpenSimCanvas();

        org.openide.awt.Mnemonics.setLocalizedText(jRefitModelButton, "Refit");
        jRefitModelButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jRefitModelButtonActionPerformed(evt);
            }
        });

        setLayout(new java.awt.BorderLayout());

        jFrontViewButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/front.gif")));
        jFrontViewButton.setToolTipText("View model from front (look along -X)");
        jFrontViewButton.setMaximumSize(new java.awt.Dimension(32, 21));
        jFrontViewButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jFrontViewButtonActionPerformed(evt);
            }
        });

        jModelWiondowToolBar.add(jFrontViewButton);

        jTopViewButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/top.gif")));
        jTopViewButton.setToolTipText("View model from above (look along -Y)");
        jTopViewButton.setMaximumSize(new java.awt.Dimension(32, 21));
        jTopViewButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jTopViewButtonActionPerformed(evt);
            }
        });

        jModelWiondowToolBar.add(jTopViewButton);

        jSideViewButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/side.gif")));
        jSideViewButton.setToolTipText("View model from the side (look along -Z)");
        jSideViewButton.setMaximumSize(new java.awt.Dimension(32, 21));
        jSideViewButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jSideViewButtonActionPerformed(evt);
            }
        });

        jModelWiondowToolBar.add(jSideViewButton);

        jTakeSnapshotButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/camera.gif")));
        jTakeSnapshotButton.setToolTipText("Take a snapshot image");
        jTakeSnapshotButton.setMaximumSize(new java.awt.Dimension(32, 21));
        jTakeSnapshotButton.setPreferredSize(new java.awt.Dimension(32, 21));
        jTakeSnapshotButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jTakeSnapshotButtonActionPerformed(evt);
            }
        });

        jModelWiondowToolBar.add(jTakeSnapshotButton);

        jStartStopMovieToggleButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/movie_camera.gif")));
        jStartStopMovieToggleButton.setToolTipText("Press to start recording, press again to finish.");
        jStartStopMovieToggleButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jStartStopMovieToggleButtonActionPerformed(evt);
                jToggleButton1ActionPerformed(evt);
            }
        });

        jModelWiondowToolBar.add(jStartStopMovieToggleButton);

        add(jModelWiondowToolBar, java.awt.BorderLayout.NORTH);

        openSimCanvas1.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mousePressed(java.awt.event.MouseEvent evt) {
                openSimCanvas1MousePressed(evt);
            }
        });

        add(openSimCanvas1, java.awt.BorderLayout.CENTER);

    }// </editor-fold>//GEN-END:initComponents

    private void jToggleButton1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jToggleButton1ActionPerformed
// TODO add your handling code here:
    }//GEN-LAST:event_jToggleButton1ActionPerformed

    private void jStartStopMovieToggleButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jStartStopMovieToggleButtonActionPerformed
// TODO add your handling code here:
        javax.swing.JToggleButton btn = (javax.swing.JToggleButton)(evt.getSource());
        if (btn.getModel().isSelected()){
            String fileName = FileUtils.getInstance().browseForFilename(".avi", "Movie file to create", false);
            //System.out.println("Create movie to file"+fileName);
            if (fileName!=null){
                // Append .avi to the end if not done by user
                if (!fileName.endsWith(".avi"))
                    fileName = fileName+".avi";
                getCanvas().createMovie(fileName);
            }
            else
                btn.getModel().setSelected(false);
         }
        else{
            getCanvas().finishMovie();
            //System.out.println("Finish movie");
        }
    }//GEN-LAST:event_jStartStopMovieToggleButtonActionPerformed

   private void openSimCanvas1MousePressed(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_openSimCanvas1MousePressed
// TODO add your handling code here:
      processMousePressed(evt);
   }//GEN-LAST:event_openSimCanvas1MousePressed

   private void jFrontViewButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jFrontViewButtonActionPerformed
// TODO add your handling code here:
      openSimCanvas1.applyCameraX();
   }//GEN-LAST:event_jFrontViewButtonActionPerformed

   private void jSideViewButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jSideViewButtonActionPerformed
// TODO add your handling code here:
      openSimCanvas1.applyCameraZ();
   }//GEN-LAST:event_jSideViewButtonActionPerformed

   private void jTopViewButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jTopViewButtonActionPerformed
// TODO add your handling code here:
      openSimCanvas1.applyCameraY();
   }//GEN-LAST:event_jTopViewButtonActionPerformed

    private void jTakeSnapshotButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jTakeSnapshotButtonActionPerformed
// TODO add your handling code here:
       String defaultDir="";
       defaultDir = Preferences.userNodeForPackage(TheApp.class).get("WorkDirectory", defaultDir);
        final JFileChooser dlog = new JFileChooser(defaultDir);
        
        if (dlog.showSaveDialog(null) == JFileChooser.APPROVE_OPTION) {
            String fullPath = dlog.getSelectedFile().getAbsolutePath();
            if (! fullPath.toLowerCase().endsWith(".tiff")){
                fullPath = dlog.getSelectedFile().getAbsolutePath()+".tiff";
            }
            getCanvas().HardCopy(fullPath, 1);
        }
    }//GEN-LAST:event_jTakeSnapshotButtonActionPerformed

    private void jRefitModelButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jRefitModelButtonActionPerformed
// TODO add your handling code here:
        getCanvas().resetCamera();
        getCanvas().Render();
    }//GEN-LAST:event_jRefitModelButtonActionPerformed

    private void processMousePressed(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_processMousePressed
// TODO add your handling code here:
        if(evt.getClickCount()==1 && ViewDB.getInstance().isPicking()){
            getCanvas().selectObject(evt);
        }
        if(evt.getClickCount()==2){
            getCanvas().handleDoubleClick(evt);
        }
        super.processEvent(evt);
    }//GEN-LAST:event_processMousePressed
    
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton jFrontViewButton;
    private javax.swing.JToolBar jModelWiondowToolBar;
    private javax.swing.JButton jRefitModelButton;
    private javax.swing.JButton jSideViewButton;
    private javax.swing.JToggleButton jStartStopMovieToggleButton;
    private javax.swing.JButton jTakeSnapshotButton;
    private javax.swing.JButton jTopViewButton;
    private org.opensim.view.OpenSimCanvas openSimCanvas1;
    // End of variables declaration//GEN-END:variables
    
    public int getPersistenceType() {
        return TopComponent.PERSISTENCE_NEVER;
    }
        
    public String preferredID() {
        return "Model";
    }     
    
    public String getDisplayName()
    {
        return tabDisplayName;
    }
    
    /**
     * Potentially there could be multiple canvases inserted into this top component,
     * Use an accessor method just incase 
     */
    public org.opensim.view.OpenSimCanvas getCanvas() {
        return openSimCanvas1;
    }
    
    public Action[] getActions(){
        ViewReplicateAction act1 = new ViewReplicateAction();   // New...
        ViewEditAction act2 = new ViewEditAction(); //Edit...
                         
        return (new Action[]{act1,act2});
    };

    protected void componentActivated() {
        super.componentActivated();
        ViewDB.getInstance().setCurrentModelWindow(this);
    }

    /**
     * update the view to reflect changes in whole model visibility. 
     */
    void updateDisplayedModels() {
        ArrayList<SingleModelVisuals> modelsToDisplay = ViewDB.getInstance().getModelVisuals();
        Iterator<SingleModelVisuals> modelVisualIter = modelsToDisplay.iterator();
        while(modelVisualIter.hasNext()){
            SingleModelVisuals nextModelVis = modelVisualIter.next();
            getCanvas().setModelVisibility(nextModelVis, nextModelVis.isVisible());
        }
        repaint();
    }
    /**
     * Window closing, remove self from ViewDB
     **/
    protected void componentClosed() {
        super.componentClosed();
        ViewDB.getInstance().removeWindow(this);
    }

    public void setTabDisplayName(String tabDisplayName) {
        this.tabDisplayName = tabDisplayName;
    }

}
