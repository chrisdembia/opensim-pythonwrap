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
 * ViewEditJDialog.java
 *
 * Created on November 18, 2006, 9:32 PM
 */

package org.opensim.view;

import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.opensim.view.pub.ViewDB;

/**
 *
 * @author  Ayman.
 * A Class to display and Edit the name of a view window.
 */
public class ViewEditJDialog extends javax.swing.JDialog {
    
    private ModelWindowVTKTopComponent view;
    /** Creates new form ViewEditJDialog */
    public ViewEditJDialog(java.awt.Frame parent, boolean modal, ModelWindowVTKTopComponent window) {
        super(parent, modal);
        view = window;
        initComponents();
        jViewnameTextField1.setText(view.getDisplayName());
    }

    
    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
   // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
   private void initComponents() {
      jCancelButton = new javax.swing.JButton();
      jOKButton = new javax.swing.JButton();
      jViewRenamePanel = new javax.swing.JPanel();
      jLabel1 = new javax.swing.JLabel();
      jViewnameTextField1 = new javax.swing.JTextField();

      setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
      setTitle("Rename View");
      setAlwaysOnTop(true);
      setModal(true);
      setResizable(false);
      jCancelButton.setText("Cancel");
      jCancelButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            ViewEditNameCancel(evt);
         }
      });

      jOKButton.setText("OK");
      jOKButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            ViewEditJDialogRename(evt);
         }
      });

      jLabel1.setText("New view name");

      jViewnameTextField1.setToolTipText("New view name");

      org.jdesktop.layout.GroupLayout jViewRenamePanelLayout = new org.jdesktop.layout.GroupLayout(jViewRenamePanel);
      jViewRenamePanel.setLayout(jViewRenamePanelLayout);
      jViewRenamePanelLayout.setHorizontalGroup(
         jViewRenamePanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(jViewRenamePanelLayout.createSequentialGroup()
            .addContainerGap()
            .add(jLabel1)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED, 11, Short.MAX_VALUE)
            .add(jViewnameTextField1, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 132, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addContainerGap())
      );
      jViewRenamePanelLayout.setVerticalGroup(
         jViewRenamePanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(jViewRenamePanelLayout.createSequentialGroup()
            .add(34, 34, 34)
            .add(jViewRenamePanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(jLabel1)
               .add(jViewnameTextField1, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
      );

      org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(getContentPane());
      getContentPane().setLayout(layout);
      layout.setHorizontalGroup(
         layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(layout.createSequentialGroup()
            .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .add(jViewRenamePanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addContainerGap())
         .add(layout.createSequentialGroup()
            .add(50, 50, 50)
            .add(jOKButton)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED, 67, Short.MAX_VALUE)
            .add(jCancelButton)
            .add(29, 29, 29))
      );
      layout.setVerticalGroup(
         layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(layout.createSequentialGroup()
            .add(jViewRenamePanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(jOKButton)
               .add(jCancelButton))
            .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
      );
      pack();
   }// </editor-fold>//GEN-END:initComponents

    private void ViewEditNameCancel(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ViewEditNameCancel
// TODO add your handling code here:
        dispose();
    }//GEN-LAST:event_ViewEditNameCancel

    private void ViewEditJDialogRename(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ViewEditJDialogRename
// TODO add your handling code here:
        if (evt.getSource()==(javax.swing.JButton) jOKButton){
            //System.out.println("New name is"+jViewnameTextField1.getText());
            String newName = jViewnameTextField1.getText();
            // Validate name is not duplicate 
            boolean valid = ViewDB.getInstance().checkValidViewName(newName, view);
            if (valid){
                view.setTabDisplayName(newName); 
                view.setDisplayName(newName);  
            }
            else
                DialogDisplayer.getDefault().notify(
                    new NotifyDescriptor.Message("The name "+newName+" is already in use. Window will not be renamed."));
        }
        dispose();
    }//GEN-LAST:event_ViewEditJDialogRename
    
    
   // Variables declaration - do not modify//GEN-BEGIN:variables
   private javax.swing.JButton jCancelButton;
   private javax.swing.JLabel jLabel1;
   private javax.swing.JButton jOKButton;
   private javax.swing.JPanel jViewRenamePanel;
   private javax.swing.JTextField jViewnameTextField1;
   // End of variables declaration//GEN-END:variables
    
}