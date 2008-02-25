package org.opensim.view.functionEditor;

import java.awt.BasicStroke;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Paint;
import java.awt.Shape;
import java.awt.event.ItemEvent;
import java.awt.geom.Ellipse2D;
import java.io.Serializable;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.util.ArrayList;
import java.util.Observable;
import java.util.Observer;
import java.util.Vector;
import javax.swing.event.EventListenerList;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.NumberAxis;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.plot.XYPlot;
import org.jfree.data.Range;
import org.jfree.data.xy.XYDataItem;
import org.jfree.data.xy.XYDataset;
import org.jfree.data.xy.XYSeriesCollection;
import org.openide.ErrorManager;
import org.openide.util.NbBundle;
import org.openide.windows.TopComponent;
import org.openide.windows.WindowManager;
import org.opensim.modeling.Constant;
import org.opensim.modeling.Function;
import org.opensim.modeling.Model;
import org.opensim.modeling.OpenSimObject;
import org.opensim.modeling.Units;
import org.opensim.view.ModelEvent;
import org.opensim.view.NameChangedEvent;
import org.opensim.view.ObjectSetCurrentEvent;
import org.opensim.view.ObjectsChangedEvent;
import org.opensim.view.ObjectsDeletedEvent;
import org.opensim.view.pub.OpenSimDB;
import org.opensim.view.pub.ViewDB;

//TODO:
// 1. Split up the Function Title text so the model and object names
// are separate. That way, when NameChangedEvents come in, you can
// update the model and object names shown in the title.
// 2. Deal with the case of a muscle being restored while one of
// its functions is being edited.
/**
 * Top component which displays something.
 */
final public class FunctionEditorTopComponent extends TopComponent implements Observer, FunctionPanelListener {
   
   public static class FunctionEditorOptions {
      
      public FunctionEditorOptions() {
         title = "";
         XLabel = "";
         YLabel = "";
         XUnits = new Units(Units.UnitType.simmRadians);
         XDisplayUnits = new Units(Units.UnitType.simmDegrees);
         YUnits = new Units(Units.UnitType.simmMeters);
         YDisplayUnits = new Units(Units.UnitType.simmMeters);
      }
      
      public String title;         // title of function
      public String XLabel;        // label of X axis
      public String YLabel;        // label of Y axis
      public Units XUnits;         // units of X array passed into function editor
      public Units XDisplayUnits;  // units of X array to display to user
      public Units YUnits;         // units of Y array passed into function editor
      public Units YDisplayUnits;  // units of Y array to display to user
   }
   
   private static FunctionEditorTopComponent instance;
   /** path to the icon used by the component and its open action */
//   static final String ICON_PATH = "SET/PATH/TO/ICON/HERE";
   
   private static final String PREFERRED_ID = "FunctionEditorTopComponent";
   
   private JFreeChart chart = null;
   private FunctionPanel functionPanel = null;
   private FunctionRenderer renderer = null;
   private Function function = null;
   private FunctionEditorOptions options;
   private Function savedFunction = null;
   private Model model = null; // the model this function is from
   private Vector<OpenSimObject> relatedObjects = null; // usually, parents of 'object'
   private OpenSimObject object = null; // the object (muscle, joint, etc.) this function is from
   private FunctionXYSeries xySeries = null;
   private XYPlot xyPlot = null;
   private XYDataset xyDataset = null;
   private NumberFormat coordinatesFormat = new DecimalFormat("0.00000");
   private Paint highlightPaint = Color.YELLOW;
   private boolean pendingChanges = false;
   private String[] functionTypeNames = {"natCubicSpline", "GCVSpline", "LinearFunction", "StepFunction", "Constant"};
   
   /** Storage for registered change listeners. */
   private transient EventListenerList listenerList = null;
   
   private FunctionEditorTopComponent() {
      initComponents();
      typeComboBox.setModel(new javax.swing.DefaultComboBoxModel(functionTypeNames));
      setName(NbBundle.getMessage(FunctionEditorTopComponent.class, "CTL_FunctionEditorTopComponent"));
      setToolTipText(NbBundle.getMessage(FunctionEditorTopComponent.class, "HINT_FunctionEditorTopComponent"));
//      setIcon(Utilities.loadImage(ICON_PATH, true));
      this.listenerList = new EventListenerList();
      ViewDB.getInstance().addObserver(this);
      OpenSimDB.getInstance().addObserver(this);
      setupComponent();
   }
   
   // TODO: there is currently no way to clear the function editor
   // (remove the current function), so there's no way to tell when
   // to remove FunctionEventListeners. So for now, allow only one,
   // which is replaced every time the editor is set to a new function.
   public void addChangeListener(FunctionEventListener listener) {
      this.listenerList = new EventListenerList();
      this.listenerList.add(FunctionEventListener.class, listener);
   }
   
   public void removeChangeListener(FunctionEventListener listener) {
      if (this.listenerList != null)
         this.listenerList.remove(FunctionEventListener.class, listener);
   }
   
   public void clearChangeListenerList() {
      this.listenerList = null;
   }
   
   public void notifyListeners(FunctionEvent event) {
      Object[] listeners = this.listenerList.getListenerList();
      for (int i = listeners.length - 2; i >= 0; i -= 2) {
         if (listeners[i] == FunctionEventListener.class) {
            ((FunctionEventListener) listeners[i + 1]).handleFunctionEvent(event);
         }
      }
   }
   
   /** This method is called from within the constructor to
    * initialize the form.
    * WARNING: Do NOT modify this code. The content of this method is
    * always regenerated by the Form Editor.
    */
   // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
   private void initComponents() {
      FunctionEditorScrollPane = new javax.swing.JScrollPane();
      FunctionEditorPanel = new javax.swing.JPanel();
      xValueTextField = new javax.swing.JTextField();
      functionDescriptionLabel = new javax.swing.JLabel();
      functionJPanel = new javax.swing.JPanel();
      xValueLabel = new javax.swing.JLabel();
      yValueLabel = new javax.swing.JLabel();
      yValueTextField = new javax.swing.JTextField();
      typeLabel = new javax.swing.JLabel();
      typeComboBox = new javax.swing.JComboBox();
      backupFunctionButton = new javax.swing.JButton();
      restoreFunctionButton = new javax.swing.JButton();
      crosshairsCheckBox = new javax.swing.JCheckBox();

      xValueTextField.setMaximumSize(new java.awt.Dimension(100, 21));
      xValueTextField.setMinimumSize(new java.awt.Dimension(100, 21));
      xValueTextField.setPreferredSize(new java.awt.Dimension(100, 21));
      xValueTextField.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            xValueActionPerformed(evt);
         }
      });
      xValueTextField.addFocusListener(new java.awt.event.FocusAdapter() {
         public void focusLost(java.awt.event.FocusEvent evt) {
            xValueFocusLost(evt);
         }
      });

      functionDescriptionLabel.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
      org.openide.awt.Mnemonics.setLocalizedText(functionDescriptionLabel, "function name");

      functionJPanel.setMinimumSize(new java.awt.Dimension(25, 25));
      org.jdesktop.layout.GroupLayout functionJPanelLayout = new org.jdesktop.layout.GroupLayout(functionJPanel);
      functionJPanel.setLayout(functionJPanelLayout);
      functionJPanelLayout.setHorizontalGroup(
         functionJPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(0, 493, Short.MAX_VALUE)
      );
      functionJPanelLayout.setVerticalGroup(
         functionJPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(0, 234, Short.MAX_VALUE)
      );

      org.openide.awt.Mnemonics.setLocalizedText(xValueLabel, "X");

      org.openide.awt.Mnemonics.setLocalizedText(yValueLabel, "Y");

      yValueTextField.setMaximumSize(new java.awt.Dimension(100, 21));
      yValueTextField.setMinimumSize(new java.awt.Dimension(100, 21));
      yValueTextField.setPreferredSize(new java.awt.Dimension(100, 21));
      yValueTextField.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            yValueActionPerformed(evt);
         }
      });
      yValueTextField.addFocusListener(new java.awt.event.FocusAdapter() {
         public void focusLost(java.awt.event.FocusEvent evt) {
            yValueFocusLost(evt);
         }
      });

      org.openide.awt.Mnemonics.setLocalizedText(typeLabel, "Type:");

      typeComboBox.setMaximumSize(new java.awt.Dimension(125, 24));
      typeComboBox.setMinimumSize(new java.awt.Dimension(125, 24));
      typeComboBox.setPreferredSize(new java.awt.Dimension(125, 24));
      typeComboBox.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            typeComboBoxActionPerformed(evt);
         }
      });

      org.openide.awt.Mnemonics.setLocalizedText(backupFunctionButton, "Backup function");
      backupFunctionButton.setMaximumSize(new java.awt.Dimension(125, 25));
      backupFunctionButton.setMinimumSize(new java.awt.Dimension(125, 25));
      backupFunctionButton.setPreferredSize(new java.awt.Dimension(125, 25));
      backupFunctionButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            backupFunctionActionPerformed(evt);
         }
      });

      org.openide.awt.Mnemonics.setLocalizedText(restoreFunctionButton, "Restore function");
      restoreFunctionButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            restoreFunctionActionPerformed(evt);
         }
      });

      org.openide.awt.Mnemonics.setLocalizedText(crosshairsCheckBox, "Crosshairs");
      crosshairsCheckBox.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
      crosshairsCheckBox.setMargin(new java.awt.Insets(0, 0, 0, 0));
      crosshairsCheckBox.addItemListener(new java.awt.event.ItemListener() {
         public void itemStateChanged(java.awt.event.ItemEvent evt) {
            crosshairsCheckBoxStateChanged(evt);
         }
      });

      org.jdesktop.layout.GroupLayout FunctionEditorPanelLayout = new org.jdesktop.layout.GroupLayout(FunctionEditorPanel);
      FunctionEditorPanel.setLayout(FunctionEditorPanelLayout);
      FunctionEditorPanelLayout.setHorizontalGroup(
         FunctionEditorPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(FunctionEditorPanelLayout.createSequentialGroup()
            .add(FunctionEditorPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
               .add(FunctionEditorPanelLayout.createSequentialGroup()
                  .addContainerGap()
                  .add(typeLabel)
                  .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                  .add(typeComboBox, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                  .add(41, 41, 41)
                  .add(backupFunctionButton, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                  .add(34, 34, 34)
                  .add(restoreFunctionButton))
               .add(FunctionEditorPanelLayout.createSequentialGroup()
                  .add(90, 90, 90)
                  .add(functionDescriptionLabel))
               .add(FunctionEditorPanelLayout.createSequentialGroup()
                  .addContainerGap()
                  .add(FunctionEditorPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                     .add(FunctionEditorPanelLayout.createSequentialGroup()
                        .add(10, 10, 10)
                        .add(xValueLabel)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(xValueTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .add(21, 21, 21)
                        .add(yValueLabel)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(yValueTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .add(28, 28, 28)
                        .add(crosshairsCheckBox))
                     .add(functionJPanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))))
            .addContainerGap())
      );
      FunctionEditorPanelLayout.setVerticalGroup(
         FunctionEditorPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(FunctionEditorPanelLayout.createSequentialGroup()
            .addContainerGap()
            .add(functionDescriptionLabel)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(functionJPanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
            .add(FunctionEditorPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(xValueLabel)
               .add(xValueTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
               .add(yValueLabel)
               .add(yValueTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
               .add(crosshairsCheckBox))
            .add(36, 36, 36)
            .add(FunctionEditorPanelLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
               .add(restoreFunctionButton)
               .add(typeComboBox, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
               .add(typeLabel)
               .add(backupFunctionButton, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
            .addContainerGap())
      );
      FunctionEditorScrollPane.setViewportView(FunctionEditorPanel);

      org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(this);
      this.setLayout(layout);
      layout.setHorizontalGroup(
         layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(FunctionEditorScrollPane, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 519, Short.MAX_VALUE)
      );
      layout.setVerticalGroup(
         layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
         .add(FunctionEditorScrollPane, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 374, Short.MAX_VALUE)
      );
   }// </editor-fold>//GEN-END:initComponents
   
   private void crosshairsCheckBoxStateChanged(java.awt.event.ItemEvent evt) {//GEN-FIRST:event_crosshairsCheckBoxStateChanged
      if (function != null && functionPanel != null) {
         if (evt.getStateChange() == ItemEvent.SELECTED)
            functionPanel.setMandatoryCrosshairs(true);
         else
            functionPanel.setMandatoryCrosshairs(false);
      }
   }//GEN-LAST:event_crosshairsCheckBoxStateChanged
   
   private void restoreFunctionActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_restoreFunctionActionPerformed
      Function func = function;
      // function must be set to null before calling replaceFunction, but I'm not sure why.
      function = null;
      notifyListeners(new FunctionReplacedEvent(model, object, func, savedFunction));
      restoreFunction();
      setupComponent();
      setPendingChanges(false, true);
      functionJPanel.validate();
      this.repaint();
   }//GEN-LAST:event_restoreFunctionActionPerformed
   
   private void backupFunctionActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_backupFunctionActionPerformed
      backupFunction();
      setPendingChanges(false, true);
   }//GEN-LAST:event_backupFunctionActionPerformed
   
    private void typeComboBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_typeComboBoxActionPerformed
       if (function == null)
          return;
       String nameOfNewType = typeComboBox.getSelectedItem().toString();
       String nameOfOldType = function.getType();
       if (nameOfNewType.equals(nameOfOldType)) {
          return;
       }
       Function newFunction = Function.makeFunctionOfType(function, nameOfNewType);
       if (newFunction == null) {
          return;
       }
       Range domainRange = null;
       boolean domainAuto = false;
       Range rangeRange = null;
       boolean rangeAuto = false;
       if (functionPanel != null) {
          domainRange = functionPanel.getChart().getXYPlot().getDomainAxis().getRange();
          domainAuto = functionPanel.getChart().getXYPlot().getDomainAxis().isAutoRange();
          rangeRange = functionPanel.getChart().getXYPlot().getRangeAxis().getRange();
          rangeAuto = functionPanel.getChart().getXYPlot().getRangeAxis().isAutoRange();
       }
       Function func = function;
       function = newFunction;
       notifyListeners(new FunctionReplacedEvent(model, object, func, newFunction));
       setupComponent();
       setPendingChanges(true, true);
       if (functionPanel != null && domainRange != null && rangeRange != null) {
          functionPanel.getChart().getXYPlot().getDomainAxis().setRange(domainRange);
          functionPanel.getChart().getXYPlot().getDomainAxis().setAutoRange(domainAuto);
          functionPanel.getChart().getXYPlot().getRangeAxis().setRange(rangeRange);
          functionPanel.getChart().getXYPlot().getRangeAxis().setAutoRange(rangeAuto);
       }
       functionJPanel.validate();
       this.repaint();
       
    }//GEN-LAST:event_typeComboBoxActionPerformed
    
    private void yValueFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_yValueFocusLost
       if (!evt.isTemporary())
          yValueEntered((javax.swing.JTextField)evt.getSource());
    }//GEN-LAST:event_yValueFocusLost
    
    private void yValueActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_yValueActionPerformed
       yValueEntered((javax.swing.JTextField)evt.getSource());
    }//GEN-LAST:event_yValueActionPerformed
    
    private void yValueEntered(javax.swing.JTextField field) {
       // TODO: check old value of each selected point to see if anything really changes
       if (field.getText().length() > 0) {
          double newValue = Double.parseDouble(field.getText());
          field.setText(coordinatesFormat.format(newValue));
          ArrayList<FunctionNode> selectedNodes = functionPanel.getSelectedNodes();
          for (int i=0; i<selectedNodes.size(); i++) {
             int index = selectedNodes.get(i).node;
             xySeries.updateByIndex(index, newValue);
             newValue *= options.YDisplayUnits.convertTo(options.YUnits);
             function.setY(index, newValue);
          }
          setPendingChanges(true, true);
          notifyListeners(new FunctionModifiedEvent(model, object, function));
       }
    }
    
    private void xValueFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_xValueFocusLost
       if (!evt.isTemporary())
          xValueEntered((javax.swing.JTextField)evt.getSource());
    }//GEN-LAST:event_xValueFocusLost
    
    private void xValueActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_xValueActionPerformed
       xValueEntered((javax.swing.JTextField)evt.getSource());
    }//GEN-LAST:event_xValueActionPerformed
    
    private void xValueEntered(javax.swing.JTextField field) {
       // TODO: check old value of each selected point to see if anything really changes
       if (field.getText().length() > 0) {
          double newValue = Double.parseDouble(field.getText());
          field.setText(coordinatesFormat.format(newValue));
          ArrayList<FunctionNode> selectedNodes = functionPanel.getSelectedNodes();
          for (int i=0; i<selectedNodes.size(); i++) {
             int index = selectedNodes.get(i).node;
             xySeries.updateByIndex(index, newValue, function.getY(index));
             newValue *= options.XDisplayUnits.convertTo(options.XUnits);
             function.setX(index, newValue);
          }
          setPendingChanges(true, true);
          notifyListeners(new FunctionModifiedEvent(model, object, function));
       }
    }
    
    private void constantValueFocusLost(java.awt.event.FocusEvent evt) {
       if (!evt.isTemporary())
          constantValueEntered((javax.swing.JTextField)evt.getSource());
    }
    
    private void constantValueActionPerformed(java.awt.event.ActionEvent evt) {
       constantValueEntered((javax.swing.JTextField)evt.getSource());
    }
    
    private void constantValueEntered(javax.swing.JTextField field) {
       Constant constant = Constant.safeDownCast(function);
       if (constant != null) {
          if (field.getText().length() > 0) {
             double newValue = Double.parseDouble(field.getText());
             field.setText(coordinatesFormat.format(newValue));
             newValue *= options.YDisplayUnits.convertTo(options.YUnits);
             constant.setValue(newValue);
             setPendingChanges(true, true);
             notifyListeners(new FunctionModifiedEvent(model, object, function));
          }
       }
    }
    
    private void setPendingChanges(boolean state, boolean update) {
       pendingChanges = state;
       
       if (update)
          updateBackupRestoreButtons();
       
       // Call a callback so the model knows about the change, e.g.
       // 1. mark the model dirty
       // 2. mark joint transforms dirty
       // The FunctionEventListener is called before setPendingChanges; should
       // that function mark the model as dirty? Is the listener called for
       // every function change event? TODO
       // Mark the model as dirty as well.
       if (state == true && model != null) {
          //SingleModelGuiElements guiElem = ViewDB.getInstance().getModelGuiElements(model);
          //guiElem.setUnsavedChangesFlag(true);
       }
    }
    
    private void updateBackupRestoreButtons() {
       if (restoreFunctionButton.isEnabled() != pendingChanges)
          restoreFunctionButton.setEnabled(pendingChanges);
       if (backupFunctionButton.isEnabled() != pendingChanges)
          backupFunctionButton.setEnabled(pendingChanges);
    }
    
   // Variables declaration - do not modify//GEN-BEGIN:variables
   private javax.swing.JPanel FunctionEditorPanel;
   private javax.swing.JScrollPane FunctionEditorScrollPane;
   private javax.swing.JButton backupFunctionButton;
   private javax.swing.JCheckBox crosshairsCheckBox;
   private javax.swing.JLabel functionDescriptionLabel;
   private javax.swing.JPanel functionJPanel;
   private javax.swing.JButton restoreFunctionButton;
   private javax.swing.JComboBox typeComboBox;
   private javax.swing.JLabel typeLabel;
   private javax.swing.JLabel xValueLabel;
   private javax.swing.JTextField xValueTextField;
   private javax.swing.JLabel yValueLabel;
   private javax.swing.JTextField yValueTextField;
   // End of variables declaration//GEN-END:variables
   
   /**
    * Gets default instance. Do not use directly: reserved for *.settings files only,
    * i.e. deserialization routines; otherwise you could get a non-deserialized instance.
    * To obtain the singleton instance, use {@link findInstance}.
    */
   public static synchronized FunctionEditorTopComponent getDefault() {
      if (instance == null) {
         instance = new FunctionEditorTopComponent();
      }
      return instance;
   }
   
   /**
    * Obtain the FunctionEditorTopComponent instance. Never call {@link #getDefault} directly!
    */
   public static synchronized FunctionEditorTopComponent findInstance() {
      TopComponent win = WindowManager.getDefault().findTopComponent(PREFERRED_ID);
      if (win == null) {
         ErrorManager.getDefault().log(ErrorManager.WARNING, "Cannot find FunctionEditor component. It will not be located properly in the window system.");
         return getDefault();
      }
      if (win instanceof FunctionEditorTopComponent) {
         return (FunctionEditorTopComponent)win;
      }
      ErrorManager.getDefault().log(ErrorManager.WARNING, "There seem to be multiple components with the '" + PREFERRED_ID + "' ID. That is a potential source of errors and unexpected behavior.");
      return getDefault();
   }
   
   public int getPersistenceType() {
      return TopComponent.PERSISTENCE_ALWAYS;
   }
   
   public void componentOpened() {
      // TODO add custom code on component opening
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
   
   final static class ResolvableHelper implements Serializable {
      private static final long serialVersionUID = 1L;
      public Object readResolve() {
         return FunctionEditorTopComponent.getDefault();
      }
   }
   public void update(Observable o, Object arg) {
      if (o instanceof OpenSimDB) {
         // if current model is being switched due to open/close or change current then
         // update tool window
         if (arg instanceof ModelEvent) {
            final ModelEvent evt = (ModelEvent)arg;
            Model closedModel = evt.getModel();
            if (evt.getOperation() == ModelEvent.Operation.Close && Model.getCPtr(closedModel) == Model.getCPtr(this.model)) {
               this.function = null;
               this.object = null;
               this.relatedObjects = null;
               this.model = null;
               backupFunction();
               setPendingChanges(false, false);
               setupComponent();
            }
         } else if (arg instanceof ObjectSetCurrentEvent) {
            ObjectSetCurrentEvent evt = (ObjectSetCurrentEvent)arg;
            Vector<OpenSimObject> objs = evt.getObjects();
            // If any of the event objects is a model, this means there is a new
            // current model. So update the panel.
            // Kluge: Handle model name change separately!
            if ((objs.size()==1) && (objs.get(0) instanceof Model)){
               if (model != null && model.equals(objs.get(0))){
                  // model was already current; don't do anything.
                  return;
               }
            }
            for (int i=0; i<objs.size(); i++) {
               if (objs.get(i) instanceof Model) {
                  this.function = null;
                  this.object = null;
                  this.relatedObjects = null;
                  this.model = null;
                  backupFunction();
                  setPendingChanges(false, false);
                  setupComponent();
                  break;
               }
            }
         } else if (arg instanceof ObjectsChangedEvent) {
            /** Probably don't need to do anything here.
             * If an object changed such that the function
             * in the Function Editor should be closed,
             * then closeObject() or closeModel() should
             * be called.
             */
         } else if (arg instanceof NameChangedEvent) {
            /* Model and object are used to create the title,
             * so you don't care about relatedObjects here.
             */
            NameChangedEvent evt = (NameChangedEvent)arg;
            if (model != null && object != null) {
               if (model.equals(evt.getObject()) || object.equals(evt.getObject()))
                  updateFunctionTitle();
            }
         } else if (arg instanceof ObjectsDeletedEvent) {
            /* If object or any of the relatedObjects is deleted,
             * clear the Function Editor.
             */
            ObjectsDeletedEvent evt = (ObjectsDeletedEvent)arg;
            Vector<OpenSimObject> objs = evt.getObjects();
            if (anyObjectIsRelevant(evt.getObjects())) {
               this.function = null;
               this.object = null;
               this.relatedObjects = null;
               this.model = null;
               backupFunction();
               setPendingChanges(false, false);
               setupComponent();
            }
         }
      }
   }

   public void setupComponent() {
      // Remove the prior FunctionPanel, if any
      functionJPanel.removeAll();
      
      if (function != null) {
         Constant constant = Constant.safeDownCast(function);
         if (constant != null) {
            backupFunctionButton.setEnabled(true);
            restoreFunctionButton.setEnabled(true);
            typeComboBox.setEnabled(true);
            typeComboBox.setSelectedIndex(findElement(functionTypeNames, constant.getType()));
            javax.swing.JLabel valueLabel = new javax.swing.JLabel();
            valueLabel.setText("value");
            javax.swing.JTextField valueField = new javax.swing.JTextField();
            valueField.setText(coordinatesFormat.format(constant.evaluate()));
            xValueTextField.setEnabled(false);
            yValueTextField.setEnabled(false);
            crosshairsCheckBox.setEnabled(false);
            valueField.addActionListener(new java.awt.event.ActionListener() {
               public void actionPerformed(java.awt.event.ActionEvent evt) {
                  constantValueActionPerformed(evt);
               }
            });
            valueField.addFocusListener(new java.awt.event.FocusAdapter() {
               public void focusLost(java.awt.event.FocusEvent evt) {
                  constantValueFocusLost(evt);
               }
            });
            org.jdesktop.layout.GroupLayout constantLayout = new org.jdesktop.layout.GroupLayout(functionJPanel);
            functionJPanel.setLayout(constantLayout);
            constantLayout.setHorizontalGroup(
                    constantLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(constantLayout.createSequentialGroup()
                    .add(121, 121, 121)
                    .add(valueLabel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 35, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                    .add(valueField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 100, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .addContainerGap(317, Short.MAX_VALUE))
                    );
            constantLayout.setVerticalGroup(
                    constantLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(org.jdesktop.layout.GroupLayout.TRAILING, constantLayout.createSequentialGroup()
                    .addContainerGap(118, Short.MAX_VALUE)
                    .add(constantLayout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                    .add(valueLabel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 16, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(valueField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 21, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                    .add(118, 118, 118))
                    );
         } else {
            XYSeriesCollection seriesCollection = new XYSeriesCollection();
            xySeries = new FunctionXYSeries("function");
            for (int i=0; i<function.getNumberOfPoints(); i++) {
               xySeries.add(new XYDataItem(function.getX(i) * (options.XUnits.convertTo(options.XDisplayUnits)),
                       function.getY(i) * (options.YUnits.convertTo(options.YDisplayUnits))));
            }
            seriesCollection.addSeries(xySeries);
            chart = ChartFactory.createXYLineChart(
                    "", options.XLabel, options.YLabel, seriesCollection,
                    org.jfree.chart.plot.PlotOrientation.VERTICAL,
                    true, true, false);
            xyPlot = chart.getXYPlot();
            xyDataset = xyPlot.getDataset();
            renderer = new FunctionRenderer(function);
            Shape circle = new Ellipse2D.Float(-3, -3, 6, 6);
            renderer.setBaseShapesVisible(true);
            renderer.setBaseShapesFilled(true);
            renderer.setSeriesShape(0, circle);
            renderer.setBaseSeriesVisibleInLegend(false);
            renderer.setDrawOutlines(true);
            renderer.setUseFillPaint(true);
            renderer.setSeriesStroke(0, new BasicStroke(1.5f));
            renderer.setSeriesOutlineStroke(0, new BasicStroke(1.0f));
            renderer.setFunctionPaint(0, Color.BLUE);
            renderer.setFunctionDefaultFillPaint(0, Color.WHITE);
            renderer.setFunctionHighlightFillPaint(0, Color.YELLOW);
            renderer.setXUnits(options.XUnits);
            renderer.setXDisplayUnits(options.XDisplayUnits);
            renderer.setYUnits(options.YUnits);
            renderer.setYDisplayUnits(options.YDisplayUnits);
            ValueAxis va = xyPlot.getRangeAxis();
            if (va instanceof NumberAxis) {
               NumberAxis na = (NumberAxis) va;
               na.setAutoRangeIncludesZero(false);
               na.setAutoRangeStickyZero(false);
               xyPlot.setRangeAxis(na);
            }
            xyPlot.setRenderer(renderer);
            functionPanel = new FunctionPanel(chart);
            functionJPanel.setLayout(new BorderLayout());
            functionJPanel.add(functionPanel);
            functionPanel.addFunctionPanelListener(this);
            backupFunctionButton.setEnabled(true);
            restoreFunctionButton.setEnabled(true);
            typeComboBox.setEnabled(true);
            typeComboBox.setSelectedIndex(findElement(functionTypeNames, function.getType()));
            xValueTextField.setEnabled(true);
            yValueTextField.setEnabled(true);
            crosshairsCheckBox.setEnabled(true);
         }
         updateFunctionTitle();
      } else {
         backupFunctionButton.setEnabled(false);
         restoreFunctionButton.setEnabled(false);
         typeComboBox.setEnabled(false);
         xValueTextField.setEnabled(false);
         yValueTextField.setEnabled(false);
         crosshairsCheckBox.setEnabled(false);
         functionDescriptionLabel.setText("");
         clearChangeListenerList();
      }
      
      Dimension d = new Dimension(500, 430);
      FunctionEditorPanel.setPreferredSize(d);
   }
   
   private void updateFunctionTitle() {
      String modelName, objectName;
      if (model == null)
         modelName = "";
      else
         modelName = model.getName();
      if (object == null)
         objectName = "";
      else
         objectName = object.getName();
      functionDescriptionLabel.setText(modelName + ": " + objectName + ": " + options.title);
   }
   
   public void open(Model model, OpenSimObject object, Vector<OpenSimObject> relatedObjects,
                    Function function, FunctionEditorOptions options) {
      this.model = model;
      this.object = object;
      this.relatedObjects = relatedObjects;
      this.function = function;
      this.options = options;
      setupComponent();
      setPendingChanges(false, true);
      backupFunction();
      super.open();
      this.requestActive();
   }
   
   public Function getFunction() {
      // Return the function currently being edited.
      return function;
   }
   
   private void updateXYTextFields() {
      ArrayList<FunctionNode> selectedNodes = functionPanel.getSelectedNodes();
      
      if (selectedNodes.size() == 1) {
         double x = xyDataset.getXValue(selectedNodes.get(0).series, selectedNodes.get(0).node);
         double y = xyDataset.getYValue(selectedNodes.get(0).series, selectedNodes.get(0).node);
         xValueTextField.setText(coordinatesFormat.format(x));
         xValueTextField.setEnabled(true);
         yValueTextField.setText(coordinatesFormat.format(y));
      } else {
         xValueTextField.setText("");
         xValueTextField.setEnabled(false);
         yValueTextField.setText("");
      }
   }
   
   public void toggleSelectedNode(int series, int node) {
      updateXYTextFields();
   }
   
   public void clearSelectedNodes() {
      updateXYTextFields();
   }
   
   public void replaceSelectedNode(int series, int node) {
      updateXYTextFields();
   }
   
   private void cropDragVector(double dragVector[]) {
      // Don't allow any dragged node to go past either of its neighbors in the X dimension.
      double minGap = 99999999.9;
      ArrayList<FunctionNode> selectedNodes = functionPanel.getSelectedNodes();
      if (dragVector[0] < 0.0) {
         for (int i=0; i<selectedNodes.size(); i++) {
            int index = selectedNodes.get(i).node;
            if (index == 0 || functionPanel.isNodeSelected(0, index-1))
               continue;
            double gap = function.getX(index) - function.getX(index-1);
            if (gap < minGap)
               minGap = gap;
         }
         // minGap is the smallest [positive] distance between a dragged node and its
         // left neighbor (if unselected). dragVector[0] can't be a larger negative
         // number than this value.
         if (dragVector[0] < -minGap)
            dragVector[0] = -minGap;
      } else if (dragVector[0] > 0.0) {
         for (int i=0; i<selectedNodes.size(); i++) {
            int index = selectedNodes.get(i).node;
            if (index == function.getNumberOfPoints()-1 || functionPanel.isNodeSelected(0, index+1))
               continue;
            double gap = function.getX(index+1) - function.getX(index);
            if (gap < minGap)
               minGap = gap;
         }
         // minGap is the smallest [positive] distance between a dragged node and its
         // right neighbor (if unselected). dragVector[0] can't be a larger positive
         // number than this value.
         if (dragVector[0] > minGap)
            dragVector[0] = minGap;
      }
   }
   
   public void dragSelectedNodes(int series, int node, double dragVector[]) {
      dragVector[0] *= options.XDisplayUnits.convertTo(options.XUnits);
      dragVector[1] *= options.YDisplayUnits.convertTo(options.YUnits);
      cropDragVector(dragVector);
      // Now move all the function points by dragVector.
      ArrayList<FunctionNode> selectedNodes = functionPanel.getSelectedNodes();
      for (int i=0; i<selectedNodes.size(); i++) {
         int index = selectedNodes.get(i).node;
         double newX = function.getX(index) + dragVector[0];
         double newY = function.getY(index) + dragVector[1];
         function.setX(index, newX);
         function.setY(index, newY);
         newX *= options.XUnits.convertTo(options.XDisplayUnits);
         newY *= options.YUnits.convertTo(options.YDisplayUnits);
         xySeries.updateByIndex(index, newX, newY);
      }
      updateXYTextFields();
      setPendingChanges(true, true);
      notifyListeners(new FunctionModifiedEvent(model, object, function));
   }
   
   private void backupFunction() {
      if (function != null)
         savedFunction = Function.safeDownCast(function.copy());
      else
         savedFunction = null;
   }
   
   private void restoreFunction() {
      if (savedFunction != null) {
         function = savedFunction;
         // make a new backup copy
         backupFunction();
      }
   }
   
   public void duplicateNode(int series, int node) {
      if (function != null && node >= 0 && node < function.getNumberOfPoints()) {
         // Make a new point that is offset slightly in the X direction from
         // the point to be duplicated.
         double newX = function.getX(node) + 0.00001;
         double newY = function.getY(node);
         addNode(0, newX, newY);
      }
   }
   
   public void deleteNode(int series, int node) {
      if (function != null && node >= 0 && node < function.getNumberOfPoints()) {
         if (function.deletePoint(node)) {
            xySeries.delete(node, node);
            setPendingChanges(true, true);
            notifyListeners(new FunctionModifiedEvent(model, object, function));
         }
      }
   }
   
   public void addNode(int series, double x, double y) {
      if (function != null) {
         xySeries.add(x, y);
         x *= options.XDisplayUnits.convertTo(options.XUnits);
         y *= options.YDisplayUnits.convertTo(options.YUnits);
         function.addPoint(x, y);
         setPendingChanges(true, true);
         notifyListeners(new FunctionModifiedEvent(model, object, function));
      }
   }

   /* Close the current function if it belongs to 'object' or
    * any member of relatedObjects. This function should be called
    * when the object containing the current function (or one of
    * the parents of this object) is modified such that the current
    * function no longer exists. It does not need to be called
    * when the object is deleted, because that will be handled
    * by update().
    */
   public void closeObject(OpenSimObject object) {
      Vector<OpenSimObject> objects = new Vector<OpenSimObject>(1);
      objects.add(object);
      if (anyObjectIsRelevant(objects))
         open(null, null, null, null, null);
   }

   /* Close the current function if it belongs to 'model'.
    * This function should be called when the model containing
    * the current function is modified such that the current
    * function no longer exists. It does not need to be called
    * when the model is deleted, because that will be handled
    * by update().
    */
   public void closeModel(Model model) {
      if (Model.getCPtr(this.model) == Model.getCPtr(model)) {
         open(null, null, null, null, null);
      }
   }

   /* Check to see if any of the objects in the passed-in list are
    * relevant to the Function Editor. An object is relevant if it's
    * the function's model (this.model), owner (this.object) or an
    * object related to its owner (this.relatedObjects).
    */
   private boolean anyObjectIsRelevant(Vector<OpenSimObject> objects) {
      for (int i=0; i<objects.size(); i++) {
         if (model != null && model.equals(objects.get(i)))
            return true;
         if (object != null && object.equals(objects.get(i)))
            return true;
         if (relatedObjects != null) {
            for (int j=0; j<relatedObjects.size(); j++) {
               if (objects.get(i).equals(relatedObjects.get(j)))
                  return true;
            }
         }
      }
      return false;
   }

   private int findElement(String[] nameList, String name) {
      int i;
      for (i = 0; i < nameList.length; i++)
         if (nameList[i].equals(name))
            return i;
      return -1;
   }
}
