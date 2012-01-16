/*
 * Copyright (c)  2005-2008, Stanford University
 * Use of the OpenSim software in source form is permitted provided that the following
 * conditions are met:
 * 	1. The software is used only for non-commercial research and education. It may not
 *     be used in relation to any commercial activity.
 * 	2. The software is not distributed or redistributed.  Software distribution is allowed 
 *     only through https://simtk.org/home/opensim.
 * 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
 *      presentations, or documents describing work in which OpenSim or derivatives are used.
 * 	4. Credits to developers may not be removed from executables
 *     created from modifications of the source.
 * 	5. Modifications of source code must retain the above copyright notice, this list of
 *     conditions and the following disclaimer. 
 * 
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 *  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 *  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 *  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 *  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 *  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
package org.opensim.view;

import java.awt.Color;
import java.awt.Dialog;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.InputEvent;
import java.util.prefs.Preferences;
import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.JColorChooser;
import javax.swing.JFileChooser;
import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;
import javax.swing.JRadioButtonMenuItem;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import org.openide.DialogDescriptor;
import org.openide.DialogDisplayer;
import org.openide.awt.UndoRedo;
import org.openide.util.NbBundle;
import org.openide.util.SharedClassObject;
import org.openide.windows.TopComponent;
import org.openide.windows.WindowManager;
import org.opensim.utils.FileUtils;
import org.opensim.utils.Prefs;
import org.opensim.utils.TheApp;
import org.opensim.view.pub.ViewDB;
import vtk.vtkCamera;
import vtk.vtkFileOutputWindow;
import vtk.vtkMatrix4x4;

/**
 * Top component which displays something.
 */
public class ModelWindowVTKTopComponent extends TopComponent 
        implements ChangeListener {  // For sliders
    
   class SetCameraAction extends AbstractAction {
      private Camera camera;
      public SetCameraAction(Camera camera) {
         super((camera!=null) ? camera.getName() : "none");
         this.camera = camera;
      }
      public void actionPerformed(ActionEvent evt) {
         getCanvas().setCamera(camera);
      }
   }

   class CameraEditorAction extends AbstractAction {
      public CameraEditorAction() {
         super("Edit Cameras...");
      }
      public void actionPerformed(ActionEvent evt) {
         CameraEditorPanel panel = new CameraEditorPanel();
         DialogDescriptor dlg = new DialogDescriptor(panel, "Camera Editor");
         dlg.setModal(false);
         dlg.setOptions(new Object[]{DialogDescriptor.OK_OPTION});
         Dialog dialog = DialogDisplayer.getDefault().createDialog(dlg);
         dialog.setVisible(true);
      }
   }
   
    private boolean internalTrigger=false;
    private static final long serialVersionUID = 1L;
    private static int ct = 0; //A counter used to provide names for new models
    private String tabDisplayName;
    Preferences prefs;
    /** path to the icon used by the component and its open action */
//    static final String ICON_PATH = "SET/PATH/TO/ICON/HERE";
    public ModelWindowVTKTopComponent() {
        initComponents();
        setComponentZOrder(toolBarPanel1, 0);
        setComponentZOrder(openSimCanvas1, 1);
        
        openSimCanvas1.addChangeListener(this);
        
        setTabDisplayName(NbBundle.getMessage(
                        ModelWindowVTKTopComponent.class,
                        "UnsavedModelNameFormat",
                        new Object[] { new Integer(ct++) }
                ));
        
        WindowManager.getDefault().invokeWhenUIReady(new Runnable(){
            public void run() {
                 setName(tabDisplayName);
            }});
        
        // Set preferred directory for the TopComponent (to be used for all saving, loading, ...
        prefs = Preferences.userNodeForPackage(TheApp.class);
        
        synchronizeBackgroundColor();
                
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
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {
        java.awt.GridBagConstraints gridBagConstraints;

        jRefitModelButton = new javax.swing.JButton();
        openSimCanvas1 = new org.opensim.view.OpenSimCanvas();
        toolBarPanel1 = new java.awt.Panel();
        jModelWindowToolBar = new javax.swing.JToolBar();
        jBackgroundColorButton = new javax.swing.JButton();
        jAxesToggleButton = new javax.swing.JToggleButton();
        jMinusXViewButton = new javax.swing.JButton();
        jPlusXViewButton = new javax.swing.JButton();
        jMinusYViewButton = new javax.swing.JButton();
        jPlusYViewButton = new javax.swing.JButton();
        jMinusZViewButton = new javax.swing.JButton();
        jPlusZViewButton = new javax.swing.JButton();
        jTakeSnapshotButton = new javax.swing.JButton();
        jStartStopMovieToggleButton = new javax.swing.JToggleButton();
        cameraEditorButton = new javax.swing.JButton();
        jAnnotateToggleButton = new javax.swing.JToggleButton();

        org.openide.awt.Mnemonics.setLocalizedText(jRefitModelButton, "Refit");
        jRefitModelButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jRefitModelButtonActionPerformed(evt);
            }
        });

        setDebugGraphicsOptions(javax.swing.DebugGraphics.BUFFERED_OPTION);
        setDoubleBuffered(true);
        setMinimumSize(new java.awt.Dimension(20, 20));
        setLayout(new java.awt.GridBagLayout());

        openSimCanvas1.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mousePressed(java.awt.event.MouseEvent evt) {
                openSimCanvas1MousePressed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.gridheight = 2;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
        gridBagConstraints.weightx = 1.0;
        gridBagConstraints.weighty = 1.0;
        add(openSimCanvas1, gridBagConstraints);

        toolBarPanel1.setBackground(new java.awt.Color(224, 223, 227));

        jModelWindowToolBar.setBorder(null);
        jModelWindowToolBar.setFloatable(false);
        jModelWindowToolBar.setOrientation(javax.swing.SwingConstants.VERTICAL);
        jModelWindowToolBar.setToolTipText("Drag to Preferred Edge or Float");
        jModelWindowToolBar.setMaximumSize(new java.awt.Dimension(20, 20));
        jModelWindowToolBar.setMinimumSize(new java.awt.Dimension(20, 20));
        jModelWindowToolBar.setOpaque(false);
        jModelWindowToolBar.setPreferredSize(new java.awt.Dimension(20, 220));

        jBackgroundColorButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/backgroundColor.png"))); // NOI18N
        jBackgroundColorButton.setToolTipText("Set view background color");
        jBackgroundColorButton.setAlignmentX(0.5F);
        jBackgroundColorButton.setBorderPainted(false);
        jBackgroundColorButton.setContentAreaFilled(false);
        jBackgroundColorButton.setFocusPainted(false);
        jBackgroundColorButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        jBackgroundColorButton.setMaximumSize(new java.awt.Dimension(20, 20));
        jBackgroundColorButton.setMinimumSize(new java.awt.Dimension(20, 20));
        jBackgroundColorButton.setPreferredSize(new java.awt.Dimension(20, 20));
        jBackgroundColorButton.setPressedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/backgroundColor_selected.png"))); // NOI18N
        jBackgroundColorButton.setRolloverIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/backgroundColor_rollover.png"))); // NOI18N
        jBackgroundColorButton.setRolloverSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/backgroundColor_rollover_selected.png"))); // NOI18N
        jBackgroundColorButton.setSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/backgroundColor_selected.png"))); // NOI18N
        jBackgroundColorButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jBackgroundColorButtonActionPerformed(evt);
            }
        });
        jModelWindowToolBar.add(jBackgroundColorButton);

        jAxesToggleButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/axes.png"))); // NOI18N
        jAxesToggleButton.setToolTipText("Show/Hide view axes");
        jAxesToggleButton.setAlignmentX(0.5F);
        jAxesToggleButton.setBorderPainted(false);
        jAxesToggleButton.setContentAreaFilled(false);
        jAxesToggleButton.setFocusPainted(false);
        jAxesToggleButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        jAxesToggleButton.setMaximumSize(new java.awt.Dimension(20, 20));
        jAxesToggleButton.setMinimumSize(new java.awt.Dimension(20, 20));
        jAxesToggleButton.setPreferredSize(new java.awt.Dimension(20, 20));
        jAxesToggleButton.setPressedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/axes_selected.png"))); // NOI18N
        jAxesToggleButton.setRolloverIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/axes_rollover.png"))); // NOI18N
        jAxesToggleButton.setRolloverSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/axes_rollover_selected.png"))); // NOI18N
        jAxesToggleButton.setSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/axes_selected.png"))); // NOI18N
        jAxesToggleButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jAxesToggleButtonActionPerformed(evt);
            }
        });
        jModelWindowToolBar.add(jAxesToggleButton);

        jMinusXViewButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/frontView_axes.png"))); // NOI18N
        jMinusXViewButton.setToolTipText("-X view");
        jMinusXViewButton.setAlignmentX(0.5F);
        jMinusXViewButton.setBorderPainted(false);
        jMinusXViewButton.setContentAreaFilled(false);
        jMinusXViewButton.setFocusPainted(false);
        jMinusXViewButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        jMinusXViewButton.setMaximumSize(new java.awt.Dimension(20, 20));
        jMinusXViewButton.setMinimumSize(new java.awt.Dimension(20, 20));
        jMinusXViewButton.setPreferredSize(new java.awt.Dimension(20, 20));
        jMinusXViewButton.setPressedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/frontView_axes_selected.png"))); // NOI18N
        jMinusXViewButton.setRolloverIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/frontView_axes_rollover.png"))); // NOI18N
        jMinusXViewButton.setRolloverSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/frontView_axes_rollover_selected.png"))); // NOI18N
        jMinusXViewButton.setSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/frontView_axes_selected.png"))); // NOI18N
        jMinusXViewButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMinusXViewButtonActionPerformed(evt);
            }
        });
        jModelWindowToolBar.add(jMinusXViewButton);

        jPlusXViewButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/backView_axes.png"))); // NOI18N
        jPlusXViewButton.setToolTipText("+X view");
        jPlusXViewButton.setAlignmentX(0.5F);
        jPlusXViewButton.setBorderPainted(false);
        jPlusXViewButton.setContentAreaFilled(false);
        jPlusXViewButton.setFocusPainted(false);
        jPlusXViewButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        jPlusXViewButton.setMaximumSize(new java.awt.Dimension(20, 20));
        jPlusXViewButton.setMinimumSize(new java.awt.Dimension(20, 20));
        jPlusXViewButton.setPreferredSize(new java.awt.Dimension(20, 20));
        jPlusXViewButton.setPressedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/backView_axes_selected.png"))); // NOI18N
        jPlusXViewButton.setRolloverIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/backView_axes_rollover.png"))); // NOI18N
        jPlusXViewButton.setRolloverSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/backView_axes_rollover_selected.png"))); // NOI18N
        jPlusXViewButton.setSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/backView_axes_selected.png"))); // NOI18N
        jPlusXViewButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jPlusXViewButtonActionPerformed(evt);
            }
        });
        jModelWindowToolBar.add(jPlusXViewButton);

        jMinusYViewButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/topView_axes.png"))); // NOI18N
        jMinusYViewButton.setToolTipText("-Y view");
        jMinusYViewButton.setAlignmentX(0.5F);
        jMinusYViewButton.setBorderPainted(false);
        jMinusYViewButton.setContentAreaFilled(false);
        jMinusYViewButton.setFocusPainted(false);
        jMinusYViewButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        jMinusYViewButton.setMaximumSize(new java.awt.Dimension(20, 20));
        jMinusYViewButton.setMinimumSize(new java.awt.Dimension(20, 20));
        jMinusYViewButton.setPreferredSize(new java.awt.Dimension(20, 20));
        jMinusYViewButton.setPressedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/topView_axes_selected.png"))); // NOI18N
        jMinusYViewButton.setRolloverIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/topView_axes_rollover.png"))); // NOI18N
        jMinusYViewButton.setRolloverSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/topView_axes_rollover_selected.png"))); // NOI18N
        jMinusYViewButton.setSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/topView_axes_selected.png"))); // NOI18N
        jMinusYViewButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMinusYViewButtonActionPerformed(evt);
            }
        });
        jModelWindowToolBar.add(jMinusYViewButton);

        jPlusYViewButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/bottomView_axes.png"))); // NOI18N
        jPlusYViewButton.setToolTipText("+Y view");
        jPlusYViewButton.setAlignmentX(0.5F);
        jPlusYViewButton.setBorderPainted(false);
        jPlusYViewButton.setContentAreaFilled(false);
        jPlusYViewButton.setFocusPainted(false);
        jPlusYViewButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        jPlusYViewButton.setMaximumSize(new java.awt.Dimension(20, 20));
        jPlusYViewButton.setMinimumSize(new java.awt.Dimension(20, 20));
        jPlusYViewButton.setPreferredSize(new java.awt.Dimension(20, 20));
        jPlusYViewButton.setPressedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/bottomView_axes_selected.png"))); // NOI18N
        jPlusYViewButton.setRolloverIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/bottomView_axes_rollover.png"))); // NOI18N
        jPlusYViewButton.setRolloverSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/bottomView_axes_rollover_selected.png"))); // NOI18N
        jPlusYViewButton.setSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/bottomView_axes_selected.png"))); // NOI18N
        jPlusYViewButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jPlusYViewButtonActionPerformed(evt);
            }
        });
        jModelWindowToolBar.add(jPlusYViewButton);

        jMinusZViewButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/rightView_axes.png"))); // NOI18N
        jMinusZViewButton.setToolTipText("-Z view");
        jMinusZViewButton.setAlignmentX(0.5F);
        jMinusZViewButton.setBorderPainted(false);
        jMinusZViewButton.setContentAreaFilled(false);
        jMinusZViewButton.setFocusPainted(false);
        jMinusZViewButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        jMinusZViewButton.setMaximumSize(new java.awt.Dimension(20, 20));
        jMinusZViewButton.setMinimumSize(new java.awt.Dimension(20, 20));
        jMinusZViewButton.setPreferredSize(new java.awt.Dimension(20, 20));
        jMinusZViewButton.setPressedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/rightView_axes_selected.png"))); // NOI18N
        jMinusZViewButton.setRolloverIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/rightView_axes_rollover.png"))); // NOI18N
        jMinusZViewButton.setRolloverSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/rightView_axes_rollover_selected.png"))); // NOI18N
        jMinusZViewButton.setSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/rightView_axes_selected.png"))); // NOI18N
        jMinusZViewButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMinusZViewButtonActionPerformed(evt);
            }
        });
        jModelWindowToolBar.add(jMinusZViewButton);

        jPlusZViewButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/leftView_axes.png"))); // NOI18N
        jPlusZViewButton.setToolTipText("+Z view");
        jPlusZViewButton.setAlignmentX(0.5F);
        jPlusZViewButton.setBorderPainted(false);
        jPlusZViewButton.setContentAreaFilled(false);
        jPlusZViewButton.setFocusPainted(false);
        jPlusZViewButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        jPlusZViewButton.setMaximumSize(new java.awt.Dimension(20, 20));
        jPlusZViewButton.setMinimumSize(new java.awt.Dimension(20, 20));
        jPlusZViewButton.setPreferredSize(new java.awt.Dimension(20, 20));
        jPlusZViewButton.setPressedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/leftView_axes_selected.png"))); // NOI18N
        jPlusZViewButton.setRolloverIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/leftView_axes_rollover.png"))); // NOI18N
        jPlusZViewButton.setRolloverSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/leftView_axes_rollover_selected.png"))); // NOI18N
        jPlusZViewButton.setSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/leftView_axes_selected.png"))); // NOI18N
        jPlusZViewButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jPlusZViewButtonActionPerformed(evt);
            }
        });
        jModelWindowToolBar.add(jPlusZViewButton);

        jTakeSnapshotButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/stillCamera.png"))); // NOI18N
        jTakeSnapshotButton.setToolTipText("Save view as image");
        jTakeSnapshotButton.setAlignmentX(0.5F);
        jTakeSnapshotButton.setBorderPainted(false);
        jTakeSnapshotButton.setContentAreaFilled(false);
        jTakeSnapshotButton.setFocusPainted(false);
        jTakeSnapshotButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        jTakeSnapshotButton.setMaximumSize(new java.awt.Dimension(20, 20));
        jTakeSnapshotButton.setMinimumSize(new java.awt.Dimension(20, 20));
        jTakeSnapshotButton.setPreferredSize(new java.awt.Dimension(20, 20));
        jTakeSnapshotButton.setPressedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/stillCamera_selected.png"))); // NOI18N
        jTakeSnapshotButton.setRolloverIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/stillCamera_rollover.png"))); // NOI18N
        jTakeSnapshotButton.setRolloverSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/stillCamera_rollover_selected.png"))); // NOI18N
        jTakeSnapshotButton.setSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/stillCamera_selected.png"))); // NOI18N
        jTakeSnapshotButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jTakeSnapshotButtonActionPerformed(evt);
            }
        });
        jModelWindowToolBar.add(jTakeSnapshotButton);

        jStartStopMovieToggleButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/movieCamera.png"))); // NOI18N
        jStartStopMovieToggleButton.setToolTipText("Toggle save motion as movie");
        jStartStopMovieToggleButton.setAlignmentX(0.5F);
        jStartStopMovieToggleButton.setBorderPainted(false);
        jStartStopMovieToggleButton.setContentAreaFilled(false);
        jStartStopMovieToggleButton.setFocusPainted(false);
        jStartStopMovieToggleButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        jStartStopMovieToggleButton.setMaximumSize(new java.awt.Dimension(20, 20));
        jStartStopMovieToggleButton.setMinimumSize(new java.awt.Dimension(20, 20));
        jStartStopMovieToggleButton.setPreferredSize(new java.awt.Dimension(20, 20));
        jStartStopMovieToggleButton.setPressedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/movieCamera_selected.png"))); // NOI18N
        jStartStopMovieToggleButton.setRolloverIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/movieCamera_rollover.png"))); // NOI18N
        jStartStopMovieToggleButton.setRolloverSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/movieCamera_rollover_selected.png"))); // NOI18N
        jStartStopMovieToggleButton.setSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/movieCamera_selected.png"))); // NOI18N
        jStartStopMovieToggleButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jStartStopMovieToggleButtonActionPerformed(evt);
                jToggleButton1ActionPerformed(evt);
            }
        });
        jModelWindowToolBar.add(jStartStopMovieToggleButton);

        cameraEditorButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/cameraDolly.png"))); // NOI18N
        cameraEditorButton.setToolTipText("Camera Dolly");
        cameraEditorButton.setAlignmentX(0.5F);
        cameraEditorButton.setBorderPainted(false);
        cameraEditorButton.setContentAreaFilled(false);
        cameraEditorButton.setFocusPainted(false);
        cameraEditorButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        cameraEditorButton.setMaximumSize(new java.awt.Dimension(20, 20));
        cameraEditorButton.setMinimumSize(new java.awt.Dimension(20, 20));
        cameraEditorButton.setPreferredSize(new java.awt.Dimension(20, 20));
        cameraEditorButton.setPressedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/leftView_axes_selected.png"))); // NOI18N
        cameraEditorButton.setRolloverIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/cameraDolly_rollover.png"))); // NOI18N
        cameraEditorButton.setRolloverSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/cameraDolly_rollover_selected.png"))); // NOI18N
        cameraEditorButton.setSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/cameraDolly_selected.png"))); // NOI18N
        cameraEditorButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mousePressed(java.awt.event.MouseEvent evt) {
                cameraEditorButtonMousePressed(evt);
            }
        });
        jModelWindowToolBar.add(cameraEditorButton);

        jAnnotateToggleButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/annotateDisarmed.png"))); // NOI18N
        jAnnotateToggleButton.setToolTipText("Annotate selection");
        jAnnotateToggleButton.setAlignmentX(0.5F);
        jAnnotateToggleButton.setBorderPainted(false);
        jAnnotateToggleButton.setContentAreaFilled(false);
        jAnnotateToggleButton.setFocusPainted(false);
        jAnnotateToggleButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        jAnnotateToggleButton.setMaximumSize(new java.awt.Dimension(20, 20));
        jAnnotateToggleButton.setMinimumSize(new java.awt.Dimension(20, 20));
        jAnnotateToggleButton.setPreferredSize(new java.awt.Dimension(20, 20));
        jAnnotateToggleButton.setPressedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/annotateArmed.png"))); // NOI18N
        jAnnotateToggleButton.setRolloverIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/annotateArmed.png"))); // NOI18N
        jAnnotateToggleButton.setRolloverSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/annotateDisarmed.png"))); // NOI18N
        jAnnotateToggleButton.setSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/annotateArmed.png"))); // NOI18N
        jAnnotateToggleButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jAnnotateToggleButtonActionPerformed(evt);
                jAnnotateButtonActionPerformed(evt);
            }
        });
        jModelWindowToolBar.add(jAnnotateToggleButton);

        org.jdesktop.layout.GroupLayout toolBarPanel1Layout = new org.jdesktop.layout.GroupLayout(toolBarPanel1);
        toolBarPanel1.setLayout(toolBarPanel1Layout);
        toolBarPanel1Layout.setHorizontalGroup(
            toolBarPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jModelWindowToolBar, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
        );
        toolBarPanel1Layout.setVerticalGroup(
            toolBarPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(toolBarPanel1Layout.createSequentialGroup()
                .add(0, 0, 0)
                .add(jModelWindowToolBar, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 244, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
        );

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.fill = java.awt.GridBagConstraints.VERTICAL;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHEAST;
        add(toolBarPanel1, gridBagConstraints);
    }// </editor-fold>//GEN-END:initComponents

    private void jAnnotateButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jAnnotateButtonActionPerformed
// TODO add your handling code here:
        javax.swing.JToggleButton src = (javax.swing.JToggleButton)evt.getSource();
        ViewDB.getInstance().setQuery(src.isSelected());
    }//GEN-LAST:event_jAnnotateButtonActionPerformed

    private void jAnnotateToggleButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jAnnotateToggleButtonActionPerformed
// TODO add your handling code here:
    }//GEN-LAST:event_jAnnotateToggleButtonActionPerformed

    private void openSimCanvas1MousePressed(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_openSimCanvas1MousePressed
// TODO add your handling code here:
        if ((evt.getModifiers() == (InputEvent.BUTTON1_MASK))) {
            deselectViewButtons();
        }
    }//GEN-LAST:event_openSimCanvas1MousePressed

    private void cameraEditorButtonMousePressed(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_cameraEditorButtonMousePressed
      JPopupMenu cameraPopup = new JPopupMenu();
      JRadioButtonMenuItem item = null;

      // null camera
      item = new JRadioButtonMenuItem(new SetCameraAction(null));
      if(getCanvas().getCamera()==null) item.setSelected(true);
      cameraPopup.add(item);

      for(int i=0; i<CameraDB.getInstance().getNumCameras(); i++) {
         Camera camera = CameraDB.getInstance().getCamera(i);
         item = new JRadioButtonMenuItem(new SetCameraAction(camera));
         if(camera.equals(getCanvas().getCamera())) item.setSelected(true);
         cameraPopup.add(item);
      }

      cameraPopup.addSeparator();
      cameraPopup.add(new JMenuItem(new CameraEditorAction()));
      cameraPopup.show(evt.getComponent(), evt.getX(), evt.getY());
    }//GEN-LAST:event_cameraEditorButtonMousePressed

    private void jBackgroundColorButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jBackgroundColorButtonActionPerformed
// TODO add your handling code here:
        JColorChooser backgroundColorChooser = new JColorChooser();
        OpenSimCanvas dCanvas = ViewDB.getInstance().getCurrentModelWindow().getCanvas();
        Color newColor = backgroundColorChooser.showDialog(dCanvas, "Select new background color", dCanvas.getBackground());
        if (newColor != null){
             float[] colorComponents = newColor.getRGBComponents(null);
             dCanvas.GetRenderer().SetBackground(colorComponents[0], colorComponents[1], colorComponents[2]);
             String defaultBackgroundColor=String.valueOf(colorComponents[0])+", "+
                     String.valueOf(colorComponents[1])+", "+
                     String.valueOf(colorComponents[2]);
             Preferences.userNodeForPackage(TheApp.class).put("BackgroundColor", defaultBackgroundColor);
             synchronizeBackgroundColor();
             dCanvas.repaint();
        }
    }//GEN-LAST:event_jBackgroundColorButtonActionPerformed

    private void jAxesToggleButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jAxesToggleButtonActionPerformed
// TODO add your handling code here:
        if (ViewDB.getInstance().isAxesDisplayed()) {
            ViewDB.getInstance().showAxes(false);
            // correct selected mode
            jAxesToggleButton.setSelected(false);
        }
        else {
            ViewDB.getInstance().showAxes(true);
            // correct selected mode
            jAxesToggleButton.setSelected(true);
        }
    }//GEN-LAST:event_jAxesToggleButtonActionPerformed

    private void jPlusXViewButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jPlusXViewButtonActionPerformed
// TODO add your handling code here:
        openSimCanvas1.applyCameraPlusX();
        // correct selected modes
        deselectViewButtons();
        jPlusXViewButton.setSelected(true);
    }//GEN-LAST:event_jPlusXViewButtonActionPerformed

    private void jPlusYViewButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jPlusYViewButtonActionPerformed
// TODO add your handling code here:
        openSimCanvas1.applyCameraPlusY();
        // correct selected modes
        deselectViewButtons();
        jPlusYViewButton.setSelected(true);
    }//GEN-LAST:event_jPlusYViewButtonActionPerformed

    private void jMinusZViewButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMinusZViewButtonActionPerformed
// TODO add your handling code here:
        openSimCanvas1.applyCameraMinusZ();
        // correct selected modes
        deselectViewButtons();
        jMinusZViewButton.setSelected(true);       
    }//GEN-LAST:event_jMinusZViewButtonActionPerformed

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
               // correct selected mode
               jStartStopMovieToggleButton.setSelected(true);
            }
            else {
                btn.getModel().setSelected(false);
                btn.getModel().setArmed(false);
            }
        }
        else {
            getCanvas().finishMovie();
            //System.out.println("Finish movie");
            // correct selected mode
            jStartStopMovieToggleButton.setSelected(false);
        }
    }//GEN-LAST:event_jStartStopMovieToggleButtonActionPerformed

    private void jPlusZViewButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jPlusZViewButtonActionPerformed
// TODO add your handling code here:
        openSimCanvas1.applyCameraPlusZ();
        // correct selected modes
        deselectViewButtons();
        jPlusZViewButton.setSelected(true);
    }//GEN-LAST:event_jPlusZViewButtonActionPerformed

    private void jMinusXViewButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMinusXViewButtonActionPerformed
// TODO add your handling code here:
        openSimCanvas1.applyCameraMinusX();
        // correct selected modes
        deselectViewButtons();
        jMinusXViewButton.setSelected(true);      
    }//GEN-LAST:event_jMinusXViewButtonActionPerformed

   private void jMinusYViewButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMinusYViewButtonActionPerformed
// TODO add your handling code here:
        openSimCanvas1.applyCameraMinusY();
        // correct selected modes
        deselectViewButtons();
        jMinusYViewButton.setSelected(true);    
   }//GEN-LAST:event_jMinusYViewButtonActionPerformed

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
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton cameraEditorButton;
    private javax.swing.JToggleButton jAnnotateToggleButton;
    private javax.swing.JToggleButton jAxesToggleButton;
    private javax.swing.JButton jBackgroundColorButton;
    private javax.swing.JButton jMinusXViewButton;
    private javax.swing.JButton jMinusYViewButton;
    private javax.swing.JButton jMinusZViewButton;
    private javax.swing.JToolBar jModelWindowToolBar;
    private javax.swing.JButton jPlusXViewButton;
    private javax.swing.JButton jPlusYViewButton;
    private javax.swing.JButton jPlusZViewButton;
    private javax.swing.JButton jRefitModelButton;
    private javax.swing.JToggleButton jStartStopMovieToggleButton;
    private javax.swing.JButton jTakeSnapshotButton;
    private org.opensim.view.OpenSimCanvas openSimCanvas1;
    private java.awt.Panel toolBarPanel1;
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
        // Note: seem to need to do it this way rather than just new ViewReplicateAction(), etc. because java complains otherwise
        // about creating multiple instances of a shared object.
        ViewReplicateAction act1 = (ViewReplicateAction) SharedClassObject.findObject(ViewReplicateAction.class, true);   // New...
        ViewEditAction act2 = (ViewEditAction) SharedClassObject.findObject(ViewEditAction.class, true); //Edit...
        Action[] superActs = super.getActions();
                         
        return (new Action[]{superActs[8],act1,act2});
    };

    protected void componentActivated() {
        super.componentActivated();
        ViewDB.getInstance().setCurrentModelWindow(this);
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
    
    public void deselectViewButtons() 
    {
        jMinusZViewButton.setSelected(false);
        jPlusZViewButton.setSelected(false);
        jPlusYViewButton.setSelected(false);
        jMinusYViewButton.setSelected(false);
        jPlusXViewButton.setSelected(false);
        jMinusXViewButton.setSelected(false);
    }

    public void synchronizeBackgroundColor()
    {
        // Get userBackgroundColor
        String userBackgroundColor="0.0, 0.0, 0.0";
        userBackgroundColor = prefs.get("BackgroundColor", userBackgroundColor);
        double[] background = Prefs.parseColor(userBackgroundColor);
        
        // Set toolBarPanel1 background color
        toolBarPanel1.setBackground(new java.awt.Color((int) (background[0]*255), (int) (background[1]*255), (int) (background[2]*255)));
        
    }
    
    public void recenterSphere()
    {
     }

    public void stateChanged(ChangeEvent e) 
    {
        if (e.getSource().equals(openSimCanvas1) && !internalTrigger){
             internalTrigger=true;
             vtkCamera cam = ViewDB.getInstance().getCurrentModelWindow().getCanvas().GetRenderer().GetActiveCamera();
             double rollAngle = cam.GetRoll();
//             jHorizontalSlider1.setValue((int) rollAngle);
//             jJoystickSlider.setValue((int) rollAngle);
             jAnnotateToggleButton.setSelected(ViewDB.getInstance().isQuery());
             internalTrigger=false;
        } 
    }
    public double[] getCameraAttributes() {
        double[] attributes = new double[13];
        vtkCamera dCamera=getCanvas().GetRenderer().GetActiveCamera();
        double[] temp = dCamera.GetPosition();
        for(int i=0; i<3; i++)
            attributes[i]=temp[i];
        temp = dCamera.GetFocalPoint();
        for(int i=0; i<3; i++)
            attributes[3+i]=temp[i];
        temp = dCamera.GetViewUp();
        for(int i=0; i<3; i++)
            attributes[6+i]=temp[i];
        temp = dCamera.GetViewPlaneNormal();
        for(int i=0; i<3; i++)
            attributes[9+i]=temp[i];
        attributes[12]=dCamera.GetViewAngle();
        vtkMatrix4x4 orientation = dCamera.GetViewTransformMatrix();
        return attributes;
    }
    
    public void applyCameraAttributes(double[] cameraAttributes) {
        vtkCamera dCamera=getCanvas().GetRenderer().GetActiveCamera();
        dCamera.SetPosition(cameraAttributes[0], cameraAttributes[1], cameraAttributes[2]);
        dCamera.SetFocalPoint(cameraAttributes[3], cameraAttributes[4], cameraAttributes[5]);
        dCamera.SetViewUp(cameraAttributes[6], cameraAttributes[7], cameraAttributes[8]);
        dCamera.SetViewPlaneNormal(cameraAttributes[9], cameraAttributes[10], cameraAttributes[11]);
        dCamera.SetViewAngle(cameraAttributes[12]);
        dCamera.Modified();
        getCanvas().GetRenderer().ResetCameraClippingRange();
        //vtkLightCollection lights = getCanvas().GetRenderer().GetLights();
        //lights.RemoveAllItems();
        //getCanvas().GetRenderer().CreateLight();
    }

    public UndoRedo getUndoRedo() {
        return ExplorerTopComponent.getDefault().getUndoRedo();
    }
}
