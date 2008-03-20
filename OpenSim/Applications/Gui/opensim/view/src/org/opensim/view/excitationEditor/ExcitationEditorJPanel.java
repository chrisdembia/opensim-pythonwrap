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
/*
 * ExcitationEditorJPanel.java
 *
 * Created on January 29, 2008, 1:43 PM
 */

package org.opensim.view.excitationEditor;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.Shape;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;
import java.awt.geom.Ellipse2D;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Vector;
import javax.swing.AbstractAction;
import javax.swing.JFrame;
import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;
import javax.swing.KeyStroke;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.MutableTreeNode;
import javax.swing.tree.TreeNode;
import javax.swing.tree.TreePath;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.NumberAxis;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.plot.XYPlot;
import org.jfree.data.xy.XYDataItem;
import org.jfree.data.xy.XYDataset;
import org.jfree.data.xy.XYSeriesCollection;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.opensim.modeling.ArrayStr;
import org.opensim.modeling.Control;
import org.opensim.modeling.ControlLinear;
import org.opensim.modeling.ControlLinearNode;
import org.opensim.modeling.ControlSet;
import org.opensim.modeling.Function;
import org.opensim.modeling.LinearFunction;
import org.opensim.modeling.SetControlNodes;
import org.opensim.modeling.StepFunction;
import org.opensim.modeling.Units;
import org.opensim.utils.DialogUtils;
import org.opensim.utils.OpenSimDialog;
import org.opensim.view.functionEditor.FunctionXYSeries;

/**
 *
 * @author  Ayman
 */
public class ExcitationEditorJPanel extends javax.swing.JPanel implements TreeSelectionListener {
    
    private ControlSet controlSet;
    ControlSet backupControlSet;
    JFrame frame;
    ExcitationTreeModel treeModel;
    Vector<TreePath> selectedPathsVector = new Vector<TreePath>(4);   // Cache used to accumulate user selection of the tree
    boolean somethingSelected=false;
    ExcitationsGridJPanel excitationGridPanel = new ExcitationsGridJPanel();
    static int MAX_EXCITATIONS_PER_COLUMN=10;
    static Color[] defaultColors = new Color[]{Color.BLUE, Color.RED, Color.BLACK};
    /** Creates new form ExcitationEditorJPanel */
    
    public ExcitationEditorJPanel(JFrame owner, ControlSet controls) {
        frame = owner;
        DefaultMutableTreeNode root=new DefaultMutableTreeNode("Excitation columns");
        treeModel = new ExcitationTreeModel(root);
        initComponents();
        root.setUserObject(excitationGridPanel);
        jExcitationsTree.addTreeSelectionListener(this);
        jMoveUpButton.setEnabled(false);
        jMoveDownButton.setEnabled(false);
        jDeleteButton.setEnabled(false);
        jValueToFormattedTextField.getInputMap().put(KeyStroke.getKeyStroke(
              KeyEvent.VK_ENTER, 0),
              "check");
        jValueToFormattedTextField.getActionMap().put("check", new handleReturnAction());   
        // Drag and Drop support
        jExcitationsTree.setDragEnabled(true);
        MoveExcitationHandler th = new MoveExcitationHandler(excitationGridPanel);
        jExcitationsTree.setTransferHandler(th);
        jExcitationsTree.setDropTarget(new TreeDropTarget(th));

        jExcitationsTree.getInputMap().put(KeyStroke.getKeyStroke(KeyEvent.VK_DELETE, 0),
                            "handleDelete");
        jExcitationsTree.getInputMap().put(KeyStroke.getKeyStroke(KeyEvent.VK_BACK_SPACE, 0),
                            "handleDelete");
        jExcitationsTree.getActionMap().put("handleDelete", new handleDelete());
        if (controls!=null){
            populate(controls);
        }
    }
    
    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
    private void initComponents() {
        jButton5 = new javax.swing.JButton();
        jLabel1 = new javax.swing.JLabel();
        jButton8 = new javax.swing.JButton();
        jTextField1 = new javax.swing.JTextField();
        jPanel3 = new javax.swing.JPanel();
        jSeparator1 = new javax.swing.JSeparator();
        jApplyValueToSelectedButton = new javax.swing.JButton();
        jSplitPane1 = new javax.swing.JSplitPane();
        jLeftPanel = new javax.swing.JPanel();
        jScrollPane1 = new javax.swing.JScrollPane();
        jExcitationsTree = new javax.swing.JTree();
        jLayoutControlPanel = new javax.swing.JPanel();
        jMoveUpButton = new javax.swing.JButton();
        jMoveDownButton = new javax.swing.JButton();
        jInsertButton = new javax.swing.JButton();
        jDeleteButton = new javax.swing.JButton();
        jRightPanel = new javax.swing.JPanel();
        jExScrollPane = new javax.swing.JScrollPane();
        jPanel1 = new javax.swing.JPanel();
        jSeparator2 = new javax.swing.JSeparator();
        jBackupAllButton = new javax.swing.JButton();
        jRestoreAllButton = new javax.swing.JButton();
        jPanel2 = new javax.swing.JPanel();
        jLabel2 = new javax.swing.JLabel();
        jRemoveNodesButton = new javax.swing.JButton();
        jValueToFormattedTextField = new javax.swing.JFormattedTextField();
        jPanel4 = new javax.swing.JPanel();
        jButton1 = new javax.swing.JButton();
        jButton2 = new javax.swing.JButton();

        jButton5.setText("Apply");
        jLabel1.setText("Set to");
        jButton8.setText("Advanced...");

        org.jdesktop.layout.GroupLayout jPanel3Layout = new org.jdesktop.layout.GroupLayout(jPanel3);
        jPanel3.setLayout(jPanel3Layout);
        jPanel3Layout.setHorizontalGroup(
            jPanel3Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(org.jdesktop.layout.GroupLayout.TRAILING, jSeparator1, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 636, Short.MAX_VALUE)
        );
        jPanel3Layout.setVerticalGroup(
            jPanel3Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jPanel3Layout.createSequentialGroup()
                .add(200, 200, 200)
                .add(jSeparator1, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 11, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(372, Short.MAX_VALUE))
        );
        jApplyValueToSelectedButton.setText("Apply");
        jApplyValueToSelectedButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jApplyValueToSelectedButtonActionPerformed(evt);
            }
        });

        setName("Excitation Editor");
        jSplitPane1.setDividerSize(7);
        jSplitPane1.setOneTouchExpandable(true);
        jLeftPanel.setLayout(new java.awt.BorderLayout());

        jExcitationsTree.setDragEnabled(true);
        jExcitationsTree.setModel(treeModel);
        jExcitationsTree.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mousePressed(java.awt.event.MouseEvent evt) {
                jExcitationsTreeMousePressed(evt);
            }
            public void mouseReleased(java.awt.event.MouseEvent evt) {
                jExcitationsTreeMouseReleased(evt);
            }
        });

        jScrollPane1.setViewportView(jExcitationsTree);

        jLeftPanel.add(jScrollPane1, java.awt.BorderLayout.CENTER);

        jMoveUpButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/icons/upArrow.png")));
        jMoveUpButton.setBorderPainted(false);
        jMoveUpButton.setContentAreaFilled(false);
        jMoveUpButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMoveUpButtonActionPerformed(evt);
            }
        });

        jMoveDownButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/icons/downArrow.png")));
        jMoveDownButton.setBorderPainted(false);
        jMoveDownButton.setContentAreaFilled(false);
        jMoveDownButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMoveDownButtonActionPerformed(evt);
            }
        });

        jInsertButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/icons/add.png")));
        jInsertButton.setBorderPainted(false);
        jInsertButton.setContentAreaFilled(false);

        jDeleteButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/view/icons/delete.png")));
        jDeleteButton.setBorderPainted(false);
        jDeleteButton.setContentAreaFilled(false);
        jDeleteButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jDeleteButtonActionPerformed(evt);
            }
        });

        org.jdesktop.layout.GroupLayout jLayoutControlPanelLayout = new org.jdesktop.layout.GroupLayout(jLayoutControlPanel);
        jLayoutControlPanel.setLayout(jLayoutControlPanelLayout);
        jLayoutControlPanelLayout.setHorizontalGroup(
            jLayoutControlPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jLayoutControlPanelLayout.createSequentialGroup()
                .add(jMoveUpButton, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 16, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jMoveDownButton, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 17, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jInsertButton, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 21, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jDeleteButton, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 21, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        jLayoutControlPanelLayout.setVerticalGroup(
            jLayoutControlPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jLayoutControlPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                .add(jMoveUpButton)
                .add(jMoveDownButton)
                .add(jInsertButton)
                .add(jDeleteButton))
        );
        jLeftPanel.add(jLayoutControlPanel, java.awt.BorderLayout.SOUTH);

        jSplitPane1.setLeftComponent(jLeftPanel);

        jRightPanel.setLayout(new java.awt.BorderLayout());

        jExScrollPane.setHorizontalScrollBarPolicy(javax.swing.ScrollPaneConstants.HORIZONTAL_SCROLLBAR_ALWAYS);
        jExScrollPane.setVerticalScrollBarPolicy(javax.swing.ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
        jRightPanel.add(jExScrollPane, java.awt.BorderLayout.CENTER);

        jBackupAllButton.setText("Backup");

        jRestoreAllButton.setText("Restore");

        jPanel2.setBorder(javax.swing.BorderFactory.createTitledBorder(javax.swing.BorderFactory.createEtchedBorder(), "With Selected Points"));
        jLabel2.setText("Set to");

        jRemoveNodesButton.setText("Remove");
        jRemoveNodesButton.setActionCommand("Remove Selected Nodes");
        jRemoveNodesButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jRemoveNodesButtonActionPerformed(evt);
            }
        });

        org.jdesktop.layout.GroupLayout jPanel2Layout = new org.jdesktop.layout.GroupLayout(jPanel2);
        jPanel2.setLayout(jPanel2Layout);
        jPanel2Layout.setHorizontalGroup(
            jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jPanel2Layout.createSequentialGroup()
                .add(jLabel2)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jValueToFormattedTextField, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 47, Short.MAX_VALUE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jRemoveNodesButton)
                .addContainerGap())
        );
        jPanel2Layout.setVerticalGroup(
            jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jPanel2Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                .add(jLabel2)
                .add(jValueToFormattedTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .add(jRemoveNodesButton))
        );

        jPanel4.setBorder(javax.swing.BorderFactory.createTitledBorder(javax.swing.BorderFactory.createEtchedBorder(), "With Selected Excitations"));
        jButton1.setText("Simplify");

        jButton2.setText("Export");

        org.jdesktop.layout.GroupLayout jPanel4Layout = new org.jdesktop.layout.GroupLayout(jPanel4);
        jPanel4.setLayout(jPanel4Layout);
        jPanel4Layout.setHorizontalGroup(
            jPanel4Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jPanel4Layout.createSequentialGroup()
                .addContainerGap()
                .add(jButton2)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jButton1)
                .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        jPanel4Layout.setVerticalGroup(
            jPanel4Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jPanel4Layout.createSequentialGroup()
                .add(jPanel4Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jButton2)
                    .add(jButton1))
                .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        org.jdesktop.layout.GroupLayout jPanel1Layout = new org.jdesktop.layout.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jPanel1Layout.createSequentialGroup()
                .addContainerGap()
                .add(jBackupAllButton)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED, 202, Short.MAX_VALUE)
                .add(jRestoreAllButton)
                .addContainerGap())
            .add(org.jdesktop.layout.GroupLayout.TRAILING, jSeparator2, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 360, Short.MAX_VALUE)
            .add(jPanel1Layout.createSequentialGroup()
                .add(jPanel2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jPanel4, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addContainerGap())
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jPanel1Layout.createSequentialGroup()
                .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .add(jPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING, false)
                    .add(jPanel4, 0, 53, Short.MAX_VALUE)
                    .add(jPanel2, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 53, Short.MAX_VALUE))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jSeparator2, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 17, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jPanel1Layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(jBackupAllButton)
                    .add(jRestoreAllButton)))
        );
        jRightPanel.add(jPanel1, java.awt.BorderLayout.SOUTH);

        jSplitPane1.setRightComponent(jRightPanel);

        org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jSplitPane1, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 472, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(jSplitPane1, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 559, Short.MAX_VALUE)
        );
    }// </editor-fold>//GEN-END:initComponents

    private void jRemoveNodesButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jRemoveNodesButtonActionPerformed
// TODO add your handling code here:
        excitationGridPanel.removeSelectedNodes();
    }//GEN-LAST:event_jRemoveNodesButtonActionPerformed

    private void jExcitationsTreeMouseReleased(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jExcitationsTreeMouseReleased
// TODO add your handling code here:
       if (evt.isPopupTrigger())
        invokeTreePopupIfNeeded(evt.getX(), evt.getY());
       if (evt.getClickCount()==2 && evt.getModifiers()==InputEvent.BUTTON1_MASK){    // innocent double click on a node. Toggle display
           toggleDisplay(evt.getX(), evt.getY());
       }

    }//GEN-LAST:event_jExcitationsTreeMouseReleased

    private void jExcitationsTreeMousePressed(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jExcitationsTreeMousePressed
       if (evt.isPopupTrigger())
        invokeTreePopupIfNeeded(evt.getX(), evt.getY());
       
// TODO add your handling code here:
    }//GEN-LAST:event_jExcitationsTreeMousePressed

    private void jApplyValueToSelectedButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jApplyValueToSelectedButtonActionPerformed
// TODO add your handling code here:
        // Cycle thru all excitation panels and apply operation
        String valueString=jValueToFormattedTextField.getText();
        double valueDouble = Double.valueOf(valueString);
        excitationGridPanel.applyValueToSelectedNodes(valueDouble);
    }//GEN-LAST:event_jApplyValueToSelectedButtonActionPerformed

    private void jDeleteButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jDeleteButtonActionPerformed
// TODO add your handling code here:
         if (somethingSelected){
            // Cache nodes to delete separately since deletion of nodes causes the current array of selection to change on us
            Vector<TreeNode> pendingNodesVector=new Vector<TreeNode>(4);
            for(int i=0; i< selectedPathsVector.size(); i++){
                TreePath nextPath=selectedPathsVector.get(i);
                TreeNode lastNode=(TreeNode)nextPath.getLastPathComponent();
                ExcitationObject eo = (ExcitationObject) ((DefaultMutableTreeNode)lastNode).getUserObject();
                if (eo != null){
                    pendingNodesVector.add(lastNode);
                }
            }
             for(int i=0; i< pendingNodesVector.size(); i++){
                TreeNode lastNode=(TreeNode)pendingNodesVector.get(i);  
                int idx = treeModel.getIndexOfChild(lastNode.getParent(),lastNode);
                assert(idx!=-1);
                TreeNode parentNode = lastNode.getParent();
                int parentIndex=treeModel.getIndexOfChild(parentNode.getParent(),parentNode);
                assert(parentIndex!=-1);
                ExcitationObject eo = (ExcitationObject) ((DefaultMutableTreeNode)lastNode).getUserObject();
                if (eo != null){
                   excitationGridPanel.removePanel(parentIndex, eo.getPlotPanel());
                }
                treeModel.removeNodeFromParent((MutableTreeNode) lastNode);
            }
            excitationGridPanel.validate();
         }       
    }//GEN-LAST:event_jDeleteButtonActionPerformed

    private void jMoveDownButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMoveDownButtonActionPerformed
        if (somethingSelected){
            // 
            Vector<TreeNode> pendingNodesVector=new Vector<TreeNode>(4);
            for(int i=0; i< selectedPathsVector.size(); i++){
                TreePath nextPath=selectedPathsVector.get(i);
                TreeNode lastNode=(TreeNode)nextPath.getLastPathComponent();
                ExcitationObject eo = (ExcitationObject) ((DefaultMutableTreeNode)lastNode).getUserObject();
                if (eo != null){
                    pendingNodesVector.add(lastNode);
                }
            }
            // For each column, find selected entries, sort top to bottom and move one step up
            DefaultMutableTreeNode root  = (DefaultMutableTreeNode) treeModel.getRoot();
            for(int i=0; i<root.getChildCount(); i++){
                // get Column's node
                DefaultMutableTreeNode columnNode = (DefaultMutableTreeNode) treeModel.getChild(root, i);
                ArrayList<Integer> selectedIdices = new ArrayList<Integer>();
                for(int j=0; j<columnNode.getChildCount(); j++){
                    DefaultMutableTreeNode exciationNode = (DefaultMutableTreeNode) treeModel.getChild(columnNode, j);
                    if (pendingNodesVector.contains(exciationNode)) 
                        selectedIdices.add(new Integer(j));
                }
                if (selectedIdices.size()==0)   // Nothing to move up
                    continue;
                Collections.sort(selectedIdices);
                // Skip contiguous list starting at last child;
                int lastAllowedNode = columnNode.getChildCount()-1;
                for(int k=selectedIdices.size()-1; k>=0; k--){
                    if (selectedIdices.get(k).intValue()==lastAllowedNode){
                        lastAllowedNode--;
                        continue;
                    }
                    // An index that can be moved up
                    int currentPosition = selectedIdices.get(k).intValue();
                    if (currentPosition==columnNode.getChildCount()-1) continue;
                    TreeNode nodeToMove =  columnNode.getChildAt(currentPosition+1);
                    treeModel.removeNodeFromParent((MutableTreeNode)nodeToMove);
                    treeModel.insertNodeInto((MutableTreeNode) nodeToMove, (MutableTreeNode) columnNode, currentPosition);
                    int idx = treeModel.getIndexOfChild(columnNode.getParent(),columnNode);
                    excitationGridPanel.exchangePlots(currentPosition, currentPosition+1, idx);
               }
            }
             for(int i=0; i<selectedPathsVector.size(); i++){
                TreePath nextPath=selectedPathsVector.get(i);
               // Keep selected in sync.
                jExcitationsTree.addSelectionPath(nextPath);
            }
            //frame.pack();
        }
// TODO add your handling code here:
    }//GEN-LAST:event_jMoveDownButtonActionPerformed

    private void jMoveUpButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMoveUpButtonActionPerformed
// TODO add your handling code here:
        if (somethingSelected){
            // move node dn in parent unless last node.
            //System.out.println("Size="+selectedPathsVector.size());
            // package it as a Move down
            Vector<TreeNode> pendingNodesVector=new Vector<TreeNode>(4);
            for(int i=0; i< selectedPathsVector.size(); i++){
                TreePath nextPath=selectedPathsVector.get(i);
                TreeNode lastNode=(TreeNode)nextPath.getLastPathComponent();
                ExcitationObject eo = (ExcitationObject) ((DefaultMutableTreeNode)lastNode).getUserObject();
                if (eo != null){
                    pendingNodesVector.add(lastNode);
                }
            }
            // For each column, find selected entries, sort top to bottom and move one step up
            DefaultMutableTreeNode root  = (DefaultMutableTreeNode) treeModel.getRoot();
            for(int i=0; i<root.getChildCount(); i++){
                // get Column's node
                DefaultMutableTreeNode columnNode = (DefaultMutableTreeNode) treeModel.getChild(root, i);
                ArrayList<Integer> selectedIdices = new ArrayList<Integer>();
                for(int j=0; j<columnNode.getChildCount(); j++){
                    DefaultMutableTreeNode exciationNode = (DefaultMutableTreeNode) treeModel.getChild(columnNode, j);
                    if (pendingNodesVector.contains(exciationNode)) 
                        selectedIdices.add(new Integer(j));
                }
                if (selectedIdices.size()==0)   // Nothing to move up
                    continue;
                Collections.sort(selectedIdices);
                // Skip contiguous list starting at 0;
                for(int k=0; k<selectedIdices.size(); k++){
                    if (selectedIdices.get(k).intValue()==k)
                        continue;
                    // An index that can be moved up
                    int currentPosition = selectedIdices.get(k).intValue();
                    TreeNode nodeToMove =  columnNode.getChildAt(currentPosition-1);
                    treeModel.removeNodeFromParent((MutableTreeNode)nodeToMove);
                    treeModel.insertNodeInto((MutableTreeNode) nodeToMove, (MutableTreeNode) columnNode, currentPosition);
                    excitationGridPanel.exchangePlots(currentPosition, currentPosition-1, root.getIndex(columnNode));
               }
            }

             for(int i=0; i<selectedPathsVector.size(); i++){
                TreePath nextPath=selectedPathsVector.get(i);
               // Keep selected in sync.
                jExcitationsTree.addSelectionPath(nextPath);
            }
            //frame.pack();
        }
    }//GEN-LAST:event_jMoveUpButtonActionPerformed
    
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton jApplyValueToSelectedButton;
    private javax.swing.JButton jBackupAllButton;
    private javax.swing.JButton jButton1;
    private javax.swing.JButton jButton2;
    private javax.swing.JButton jButton5;
    private javax.swing.JButton jButton8;
    private javax.swing.JButton jDeleteButton;
    private javax.swing.JScrollPane jExScrollPane;
    private javax.swing.JTree jExcitationsTree;
    private javax.swing.JButton jInsertButton;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JPanel jLayoutControlPanel;
    private javax.swing.JPanel jLeftPanel;
    private javax.swing.JButton jMoveDownButton;
    private javax.swing.JButton jMoveUpButton;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JPanel jPanel3;
    private javax.swing.JPanel jPanel4;
    private javax.swing.JButton jRemoveNodesButton;
    private javax.swing.JButton jRestoreAllButton;
    private javax.swing.JPanel jRightPanel;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JSeparator jSeparator1;
    private javax.swing.JSeparator jSeparator2;
    private javax.swing.JSplitPane jSplitPane1;
    private javax.swing.JTextField jTextField1;
    private javax.swing.JFormattedTextField jValueToFormattedTextField;
    // End of variables declaration//GEN-END:variables

   /** 
     * Creates an overlaid chart.
     *
     * @return The chart.
     */
    private void createExcitationColumnPanel(int colIndex, String[] names) {

        // create plot ...
        DefaultMutableTreeNode columnNode = new DefaultMutableTreeNode("Column "+String.valueOf(colIndex));
        treeModel.insertNodeInto(columnNode, (DefaultMutableTreeNode) treeModel.getRoot(), colIndex);
        excitationGridPanel.addColumn("Column "+String.valueOf(colIndex));
        columnNode.setUserObject(excitationGridPanel.getExcitationColumn(colIndex));
        for(int i=0; i<names.length; i++){
            Control nextControl = getControlSet().get(names[i]);
            if (nextControl==null)
                nextControl = getControlSet().get(getLongName(names[i]));
            addExcitation(columnNode, nextControl, colIndex);
        } 
        validate();
    }

    public void addExcitation(final DefaultMutableTreeNode columnNode, final Control nextControl, final int colIndex) {
        // Build an array of OpenSim::Functions for value, min, max
        Vector<Function> functions = new Vector<Function>(3);
        ControlLinear control = ControlLinear.safeDownCast(nextControl);
        // Create a panel to hold the control/min/max and return the array of underlying OpenSim::Functions
        ExcitationPanel nextExcitationPanel = createPanel(control, functions); 
        // Handle addition to the tree
        ExcitationObject excitationNode= new ExcitationObject(nextExcitationPanel, nextControl.getName());
        excitationNode.setUserObject(excitationNode);
        treeModel.appendChild(excitationNode, columnNode);
        // Handle addition to the panel of excitations
        excitationGridPanel.addExcitationPanel(colIndex, nextExcitationPanel, control, functions);
    }



    void populate(ControlSet obj) {
       backupControlSet = new ControlSet(obj);
       setControlSet(obj);
      
       excitationGridPanel.setControlSet(obj);
       jExScrollPane.setViewportView(excitationGridPanel);
       
       int numColumns= ((DefaultMutableTreeNode)treeModel.getRoot()).getChildCount();
        ArrayStr names = new ArrayStr();
        obj.getNames(names);
        for(int i=0; i< names.getSize(); i++){
            names.setitem(i, getShortName(names.getitem(i)));
        }
       removeDisplayedItems((DefaultMutableTreeNode)treeModel.getRoot(), names);
       FilterableStringArray namesSource = new FilterableStringArray(names);
       NameFilterJPanel filterPanel = new NameFilterJPanel(namesSource, false);
       OpenSimDialog selectionDlg=DialogUtils.createDialogForPanelWithParent(frame, filterPanel, "Select Excitations");
       DialogUtils.addStandardButtons(selectionDlg);
       selectionDlg.setModal(true);
       selectionDlg.setVisible(true);

       if (selectionDlg.getDialogReturnValue()==selectionDlg.OK_OPTION) {
           String[] selNames = new String[filterPanel.getNumSelected()];
           System.arraycopy(filterPanel.getSelected(), 0, selNames, 0, filterPanel.getNumSelected());
           int numExcitationColumns = selNames.length/MAX_EXCITATIONS_PER_COLUMN;
           String[] currentColNames = new String[MAX_EXCITATIONS_PER_COLUMN];
           for(int col=0; col<numExcitationColumns; col++){
               System.arraycopy(filterPanel.getSelected(), col*MAX_EXCITATIONS_PER_COLUMN, currentColNames, 0, MAX_EXCITATIONS_PER_COLUMN);
               numColumns= ((DefaultMutableTreeNode)treeModel.getRoot()).getChildCount();
               createExcitationColumnPanel(numColumns, currentColNames);
           }
           numColumns= ((DefaultMutableTreeNode)treeModel.getRoot()).getChildCount();
           int remainingItemsCount = filterPanel.getSelected().length-numExcitationColumns*MAX_EXCITATIONS_PER_COLUMN;
           currentColNames = new String[remainingItemsCount];
           System.arraycopy(filterPanel.getSelected(), numExcitationColumns*MAX_EXCITATIONS_PER_COLUMN, 
                            currentColNames, 0, remainingItemsCount);
           createExcitationColumnPanel(numColumns, currentColNames);
       }
       else
           return;
       //Rectangle r=panel.getBounds();
       //jRightPanel.add(excitationGridPanel,java.awt.BorderLayout.CENTER);
       //Dimension d = new Dimension(300,600);
       //excitationGridPanel.setPreferredSize(d);
       //jRightPanel.invalidate();

       frame.setExtendedState(Frame.MAXIMIZED_VERT);
       //frame.doLayout();
       frame.validate();
    }

    public void valueChanged(TreeSelectionEvent e) {
       TreePath[] selectedPaths = e.getPaths();
      somethingSelected=false;
      for(int i=0;i<selectedPaths.length;i++){
         ExcitationObject eo = null;
         TreeNode lastNode=(TreeNode)selectedPaths[i].getLastPathComponent();
         if (((DefaultMutableTreeNode)lastNode).getUserObject() instanceof ExcitationObject){
            eo = (ExcitationObject) ((DefaultMutableTreeNode)lastNode).getUserObject();
         }
         if (e.isAddedPath(i)){
             if (eo != null){
                selectedPathsVector.add(selectedPaths[i]);
                eo.markSelected(true);
                somethingSelected=true;
             }
         } else {   //Removed
             if (eo != null){
                selectedPathsVector.remove(selectedPaths[i]);
                eo.markSelected(false);
             }
         }
      }
     // Enable buttons to move only if  (somethingSelected)
      jMoveUpButton.setEnabled(somethingSelected);
      jMoveDownButton.setEnabled(somethingSelected);
      jDeleteButton.setEnabled(somethingSelected);
      
   }
   
   static String filterExcitationName(String fullName)
   {
       String filtered = fullName;
       if (fullName.contains(".")){
           filtered = filtered.substring(0, fullName.indexOf('.')); 
       }
       return filtered;
   }
   
   static ExcitationPanel createPanel(ControlLinear excitation, Vector<Function> functions)
   {
         XYSeriesCollection seriesCollection = new XYSeriesCollection();
         ControlLinear cl = ControlLinear.safeDownCast(excitation);
         
         FunctionXYSeries xySeries = new FunctionXYSeries("excitation");
         SetControlNodes cnodes = cl.getControlValues();
         Function ctrlFunction = createFunctionFromControlLinear(xySeries, cnodes, cl, !cl.getUseSteps());
         functions.add(ctrlFunction);
         seriesCollection.addSeries(xySeries);
         
         FunctionXYSeries xySeriesMin = new FunctionXYSeries("min");
         SetControlNodes minNodes = cl.getControlMinValues();
         Function minFunction = createFunctionFromControlLinear(xySeriesMin, minNodes, cl, true);
         functions.add(minFunction);
         seriesCollection.addSeries(xySeriesMin);
        
         FunctionXYSeries xySeriesMax = new FunctionXYSeries("max");
         SetControlNodes maxNodes = cl.getControlMaxValues();
         Function maxFunction = createFunctionFromControlLinear(xySeriesMax, maxNodes, cl, true);
         functions.add(maxFunction);
         seriesCollection.addSeries(xySeriesMax);
         
         JFreeChart chart = ChartFactory.createXYLineChart(
            "",
            "",
            "",
            seriesCollection,
            org.jfree.chart.plot.PlotOrientation.VERTICAL,
            true,
            true,
            false);
         XYPlot xyPlot = chart.getXYPlot();
         XYDataset xyDataset = xyPlot.getDataset();
         ExcitationRenderer renderer = new ExcitationRenderer(excitation, ctrlFunction);
         renderer.addFunction(minFunction);
         renderer.addFunction(maxFunction);
         renderer.setXUnits(new Units(Units.UnitType.simmSeconds));
         renderer.setXDisplayUnits(new Units(Units.UnitType.simmSeconds));
         renderer.setYUnits(new Units(Units.UnitType.simmSeconds));
         renderer.setYDisplayUnits(new Units(Units.UnitType.simmSeconds));

         Shape circle = new Ellipse2D.Float(-3, -3, 6, 6);
         renderer.setBaseShapesVisible(true);
         renderer.setBaseShapesFilled(true);
         for(int i=0; i<3; i++){
             renderer.setSeriesShape(i, circle);// all series
             renderer.setSeriesStroke(i, new BasicStroke(1.5f));
             renderer.setSeriesOutlineStroke(i, new BasicStroke(1.0f));
             renderer.setFunctionPaint(i, defaultColors[i]);
             renderer.setFunctionDefaultFillPaint(i, Color.WHITE);
             renderer.setFunctionHighlightFillPaint(i, Color.YELLOW);
         }
         renderer.setBaseSeriesVisibleInLegend(false);
         renderer.setDrawOutlines(true);
         renderer.setUseFillPaint(true);
         renderer.setInteriorTitle(excitation.getName().replace(".excitation",""));
         ValueAxis va = xyPlot.getRangeAxis();
         if (va instanceof NumberAxis) {
            NumberAxis na = (NumberAxis) va;
            na.setAutoRangeIncludesZero(false);
            na.setAutoRangeStickyZero(false);
            xyPlot.setRangeAxis(na);
            na.setNumberFormatOverride(new DecimalFormat("0.0000"));
         }
         xyPlot.setRenderer(renderer);
         ExcitationPanel dPanel =  new ExcitationPanel(chart);
         
         return dPanel;
   }


    public static Function createFunctionFromControlLinear(final FunctionXYSeries xySeries, final SetControlNodes cnodes, final ControlLinear cl, boolean useLinear) {
        Function ctrlFunction;
        if (!useLinear){ // Step function
            ctrlFunction = new StepFunction();
            for (int i=0; i<cnodes.getSize(); i++) {
               ControlLinearNode clnode = cnodes.get(i);
               ctrlFunction.addPoint(clnode.getTime(), clnode.getValue());
               xySeries.add(new XYDataItem(clnode.getTime(), clnode.getValue()));
            }
        }
        else { // Linear function
            ctrlFunction = new LinearFunction();
            for (int i=0; i<cnodes.getSize(); i++) {
               ControlLinearNode clnode = cnodes.get(i);
               ctrlFunction.addPoint(clnode.getTime(), clnode.getValue());
               xySeries.add(new XYDataItem(clnode.getTime(), clnode.getValue()));
            }
            
        }
        return ctrlFunction;
    }
   
   private void invokeTreePopupIfNeeded(int evtX, int evtY) {
      final TreePath clickedElement = jExcitationsTree.getPathForLocation(evtX, evtY);
      JPopupMenu contextMenu = new JPopupMenu();
      DefaultMutableTreeNode clickedNode=null;
      Object  clickedObject = null;
      if (clickedElement.getLastPathComponent() instanceof DefaultMutableTreeNode){
          clickedNode = (DefaultMutableTreeNode)clickedElement.getLastPathComponent();
          clickedObject = clickedNode.getUserObject();
      }
      
      if (clickedNode.equals(treeModel.getRoot()) && getControlSet()!=null){
          // allow addition of a new column
            JMenuItem addColMenuItem = new JMenuItem("Add Column...");
            addColMenuItem.addActionListener(new ActionListener(){
                public void actionPerformed(ActionEvent e) {
                    ArrayStr names = getUndisplayedExcitations();
                    FilterableStringArray namesSource = new FilterableStringArray(names);
                    NameFilterJPanel filterPanel = new NameFilterJPanel(namesSource, false);
                    OpenSimDialog selectionDlg=DialogUtils.createDialogForPanelWithParent(frame, filterPanel, "Select Excitations");
                    DialogUtils.addStandardButtons(selectionDlg);
                    selectionDlg.setModal(true);
                    selectionDlg.setVisible(true);
                    
                    int numColumns= ((DefaultMutableTreeNode)treeModel.getRoot()).getChildCount();
                    if (selectionDlg.getDialogReturnValue()==selectionDlg.OK_OPTION) {
                        String[] selNames = new String[filterPanel.getNumSelected()];
                        System.arraycopy(filterPanel.getSelected(), 0, selNames, 0, filterPanel.getNumSelected());
                        for (int i=0; i<filterPanel.getNumSelected(); i++)
                            selNames[i] = getShortName(selNames[i]);
                        createExcitationColumnPanel(numColumns, selNames);
                     }

                }

});
          contextMenu.add(addColMenuItem );
      }
      if (clickedObject instanceof ExcitationColumnJPanel){
          // Add item to change display name
          final ExcitationColumnJPanel columnPanel = (ExcitationColumnJPanel) clickedObject;
          JMenuItem renameMenuItem = new JMenuItem("Rename...");
            renameMenuItem.addActionListener(new ActionListener(){
                public void actionPerformed(ActionEvent e) {
                     NotifyDescriptor.InputLine dlg =
                            new NotifyDescriptor.InputLine("Current Name: "+columnPanel.toString(), "Rename Object");
                     if(DialogDisplayer.getDefault().notify(dlg)==NotifyDescriptor.OK_OPTION){
                        columnPanel.setLabel( dlg.getInputText());
                     }
                }
            });
          JMenuItem appendMenuItem = new JMenuItem("Append...");
            appendMenuItem.addActionListener(new ActionListener(){
                public void actionPerformed(ActionEvent e) {
                    ArrayStr names = getUndisplayedExcitations();
                    FilterableStringArray namesSource = new FilterableStringArray(names);
                    NameFilterJPanel filterPanel = new NameFilterJPanel(namesSource, false);
                    OpenSimDialog selectionDlg=DialogUtils.createDialogForPanelWithParent(frame, filterPanel, "Select Excitations");
                    DialogUtils.addStandardButtons(selectionDlg);
                    selectionDlg.setModal(true);
                    selectionDlg.setVisible(true);
                    
                    int numColumns= ((DefaultMutableTreeNode)treeModel.getRoot()).getChildCount();
                    if (selectionDlg.getDialogReturnValue()==selectionDlg.OK_OPTION) {
                        String[] selNames = new String[filterPanel.getNumSelected()];
                        System.arraycopy(filterPanel.getSelected(), 0, selNames, 0, filterPanel.getNumSelected());
                        for (int i=0; i<filterPanel.getNumSelected(); i++)
                            selNames[i] = getShortName(selNames[i]);
                        // Add selected names to proper column Panel
                        DefaultMutableTreeNode clickedNode = (DefaultMutableTreeNode)clickedElement.getLastPathComponent();
                        int colIndex = treeModel.getIndexOfChild(clickedNode.getParent(),clickedNode);
                        treeModel.insertNodeInto(clickedNode, (DefaultMutableTreeNode) treeModel.getRoot(), colIndex);
                        for(int i=0; i<selNames.length; i++){
                            Control nextControl = getControlSet().get(selNames[i]);
                            if (nextControl==null)
                                nextControl = getControlSet().get(getLongName(selNames[i]));
                            addExcitation(clickedNode, nextControl, colIndex);
                        } 
                        frame.validate();
                     }
                }
            });
           contextMenu.add(renameMenuItem);
           contextMenu.add(appendMenuItem);
      }
      contextMenu.show(jExcitationsTree, evtX, evtY);
   }

    public static String getShortName(String string) {
        int idx= string.indexOf(".excitation");
        if (idx!=-1)
            return string.substring(0, idx);
        else
            return string;
    }

    public static String getLongName(String string) {
        return string+".excitation";
    }
    
   class handleDelete extends AbstractAction {
        public void actionPerformed(ActionEvent e) {
             jDeleteButtonActionPerformed(null);
        }           
   }
   /**
    * Handler of return button in Value
    */
   class handleReturnAction extends AbstractAction {
       public void actionPerformed(ActionEvent e) {
        // Cycle thru all excitation panels and apply operation
        String valueString=jValueToFormattedTextField.getText();
        double valueDouble = Double.valueOf(valueString);
        excitationGridPanel.applyValueToSelectedNodes(valueDouble);

       }
   }

    public ControlSet getControlSet() {
        return controlSet;
    }

    public void setControlSet(ControlSet controlSet) {
        this.controlSet = controlSet;
    }

    private void removeDisplayedItems(DefaultMutableTreeNode treeNode, ArrayStr names) {
        int count = treeNode.getChildCount();
        for( int i=0;  i < count;  i++ ) {
            DefaultMutableTreeNode child = (DefaultMutableTreeNode) treeNode.getChildAt(i);
            if ( child.isLeaf())
                names.remove(names.findIndex(child.toString()));
            else
                removeDisplayedItems( child, names );
        }
    }

    private ArrayStr getUndisplayedExcitations() {
        // Bring up the filter dialog populated by list of names from current control set
        ArrayStr names = new ArrayStr();
        getControlSet().getNames(names);
        for(int i=0; i< names.getSize(); i++){
            names.setitem(i, getShortName(names.getitem(i)));
        }
        removeDisplayedItems((DefaultMutableTreeNode)treeModel.getRoot(), names);
        return names;
    }

    private void toggleDisplay(int evtX, int evtY) {
      final TreePath clickedElement = jExcitationsTree.getPathForLocation(evtX, evtY);
      JPopupMenu contextMenu = new JPopupMenu();
      DefaultMutableTreeNode clickedNode=null;
      Object  clickedObject = null;
      if (clickedElement.getLastPathComponent() instanceof DefaultMutableTreeNode){
          clickedNode = (DefaultMutableTreeNode)clickedElement.getLastPathComponent();
          clickedObject = clickedNode.getUserObject();
      }
      
      if (clickedObject instanceof ExcitationObject){
          ExcitationColumnJPanel parentPanel = (ExcitationColumnJPanel)(((DefaultMutableTreeNode)clickedNode.getParent()).getUserObject());
          ExcitationPanel dPanel = ((ExcitationObject) clickedObject).getPlotPanel();
          parentPanel.toggle(dPanel);
      }
    }

}
