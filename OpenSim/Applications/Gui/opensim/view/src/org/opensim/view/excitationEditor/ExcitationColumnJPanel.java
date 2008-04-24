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
 * ExcitationColumnJPanel.java
 *
 * Created on February 13, 2008, 11:56 AM
 */

package org.opensim.view.excitationEditor;

import java.awt.Component;
import java.awt.Dimension;
import java.io.BufferedWriter;
import java.io.IOException;
import java.util.Vector;
import org.opensim.modeling.ControlLinear;
import org.opensim.modeling.Function;

/**
 *
 * @author  Ayman
 */
public class ExcitationColumnJPanel extends javax.swing.JPanel {
    
    Vector<ExcitationPanel> cache= new Vector<ExcitationPanel>(4);
    // When adding panels, the only way to specify location is adding them as JComponents at index. 
    // this number accounts for components other than ExcitationPanels in 
    int componentOffset=1;  
    int ratioUncollapsedToCollapsedSize=16;
    //Vector<ExcitationPanelListener> listeners = new Vector<ExcitationPanelListener>(4);
    /** Creates new form ExcitationColumnJPanel */
    public ExcitationColumnJPanel() {
        initComponents();
        //setPreferredSize(new Dimension(100, 300));
    }
        
    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
    private void initComponents() {
        jColumnNameLabel = new javax.swing.JLabel();

        setLayout(new javax.swing.BoxLayout(this, javax.swing.BoxLayout.Y_AXIS));

        setToolTipText("\"Column of Excitations\"");
        setAutoscrolls(true);
        setName("name");
        jColumnNameLabel.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jColumnNameLabel.setText("jColumnLabel");
        jColumnNameLabel.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        add(jColumnNameLabel);

    }// </editor-fold>//GEN-END:initComponents
    
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel jColumnNameLabel;
    // End of variables declaration//GEN-END:variables
    
    void exchange(int position1, int position2)
    {
        // Need to remove and insert
        int lower, upper;
        if(position1<position2){
            upper = position1;
            lower = position2;
        }
        else {
            upper = position2;
            lower = position1;            
        }
            
        ExcitationPanel p1 = getPanel(lower);
        ExcitationPanel p2 = getPanel(upper);
        this.remove(p1);
        this.remove(p2);
        this.add(p1, upper+1);
        this.add(p2, lower+1);
        validate();
    }

    void removePanel(int row) {
        ExcitationPanel fp = cache.get(row);
        int index = cache.indexOf(fp);
        remove(fp);
        validate();
    }
    
    void removePanel(ExcitationPanel aPanel) {
        //System.out.println("Removing panel "+aPanel.toString()+" from column "+jColumnNameLabel.getText());
        remove(aPanel);
        int idx=cache.indexOf(aPanel);
        cache.remove(aPanel);
        Component component[] = getComponents();
        for (int i=0; i<component.length; i++){
            Component c=component[i];
            int unused = 1;
        }
        validate();
    }
    
    void appendPanel(ExcitationPanel excitationPanel) {
        //System.out.println("Appending panel "+excitationPanel.toString()+" to column "+jColumnNameLabel.getText());
        add(excitationPanel);
        cache.add(excitationPanel);
        validate();
    }
    
    void addPanel(ExcitationPanel excitationPanel, int i) {
        add(excitationPanel, i+1);
        cache.insertElementAt(excitationPanel, i);
        validate();
    }

    public ExcitationPanel getPanel(int row)
    {
        return (ExcitationPanel) getComponents()[row+1];
    }
    
    void set(int row, ExcitationPanel panel)
    {
        add(panel);
        if (cache.size()<row+1){  // We should make sure cache.size()
            cache.add(panel);
        }
        cache.set(row, panel);
    }
    
    void append(ExcitationPanel excitationPanel, ControlLinear excitation, Vector<Function> functionsToEdit)
    {
        excitationPanel.setPreferredSize(new Dimension(300, 100));
        add(excitationPanel);
        cache.add(excitationPanel);
        // Create listener and add it too
        ExcitationPanelListener listener= new ExcitationPanelListener(excitationPanel, excitation, functionsToEdit);
        //listeners.add(listener);
        excitationPanel.addFunctionPanelListener(listener);
    }
    public ExcitationColumnJPanel(String[] names) {
        initComponents();
        //setPreferredSize(new Dimension(100, 300));
    }
    
    public void applyValueToSelectedNodes(double valueDouble) {
        for(int i=0; i<cache.size(); i++)
            cache.get(i).setSelectedNodesToValue(0, valueDouble);
    }
    
    public void removeSelectedNodes() {
        
        for(int i=0; i<cache.size(); i++)
            cache.get(i).deleteSelectedNodes();
    }

    public String toString() {
        return jColumnNameLabel.getText();
    }

    void setLabel(String colLabel) {
        jColumnNameLabel.setText(colLabel);
        validate();
    }

    void toggle(ExcitationPanel dPanel) {
        // Compute size of panel. Expanded panels are ratioUncollapsedToCollapsedSize times as big as collapsed ones
        int totalheight = this.getHeight();
        int width = this.getWidth();
        int numCollapsed = 0;
        int numTotal = cache.size();
        for (int i=0; i<cache.size(); i++){
            ExcitationPanel p1 = getPanel(i);
            if (p1.equals(dPanel)){
                p1.setCollapsed(!p1.isCollapsed());
            }
            numCollapsed += (cache.get(i).isCollapsed()?1:0);
        }
        int collapsedHeight = (int)((double) totalheight)/(numCollapsed + (numTotal-numCollapsed)*ratioUncollapsedToCollapsedSize);
        //System.out.println("collapsedHeight="+collapsedHeight);
        for (int i=0; i<cache.size(); i++){
            ExcitationPanel p1 = getPanel(i);
            if (p1.isCollapsed()){
                p1.setSize(new Dimension(width, collapsedHeight));
                p1.setPreferredSize(new Dimension(width, collapsedHeight));
                p1.setMaximumDrawHeight(collapsedHeight);
            }
            else{
                p1.setPreferredSize(new Dimension(width, ratioUncollapsedToCollapsedSize*collapsedHeight));
                p1.setSize(new Dimension(width, ratioUncollapsedToCollapsedSize*collapsedHeight));
                p1.setMaximumDrawHeight(ratioUncollapsedToCollapsedSize*collapsedHeight);
           }
        }
        invalidate();
        doLayout();
    }

    public String getColumnNameLabelText() {
        return jColumnNameLabel.getText();
    }

    public void setColumnNameLabelText(String newColumnNameLabel) {
        this.jColumnNameLabel.setText(newColumnNameLabel);
    }

    void write(BufferedWriter writer) throws IOException {
        writer.write(getColumnNameLabelText()+"\n");
        writer.write(cache.size()+"\n");
         for(int i=0; i<cache.size(); i++) {
            ExcitationPanel p1 = getPanel(i);
            writer.write(p1.getControlName()+"\n");
        }
    }

    void backup() {
         for(int i=0; i<cache.size(); i++) {
            ExcitationPanel p1 = getPanel(i);
            p1.backup();
         }
    }

    void restore() {
         for(int i=0; i<cache.size(); i++) {
            ExcitationPanel p1 = getPanel(i);
            p1.restore();
         }
    }

    void showBaseShape(int series, boolean b) {
         for(int i=0; i<cache.size(); i++) {
            ExcitationPanel p1 = getPanel(i);
            p1.showBaseShape(series, b);
         }        
    }

    void toggleMinMaxShading(boolean b) {
         for(int i=0; i<cache.size(); i++) {
            ExcitationPanel p1 = getPanel(i);
            p1.toggleMinMaxShading(b);
         }        
    }

}