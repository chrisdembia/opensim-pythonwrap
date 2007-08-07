/*
 * MotionControlJPanel.java
 *
 * Created on January 12, 2007, 11:28 AM
 */

package org.opensim.motionviewer;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.DecimalFormat;
import java.util.Hashtable;
import java.util.Observable;
import java.util.Observer;
import javax.swing.JLabel;
import javax.swing.Timer;
import javax.swing.SpinnerModel;
import javax.swing.SpinnerNumberModel;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import org.opensim.motionviewer.MotionEvent.Operation;

/**
 *
 * @author  Ayman
 * The panel for motion playback in main toolbar.
 * The panel will observer MotionsDB so that it can respond to changes in current model, events ...
 */
public class MotionControlJPanel extends javax.swing.JPanel 
        implements ChangeListener,  // For motion slider
                   Observer {       // For MotionsDB
   
   Timer               animationTimer=null;
   SpinnerModel        smodel = new SpinnerNumberModel(1.0, 0.0, 10.0, 0.05);
   boolean             motionLoaded=false;
   MasterMotionModel   masterMotion;
   private int         rangeResolution;
   private int         timerRate = 30;

   private boolean internalTrigger=false;

   /* Old timer callbacks used for advancing each frame... replaced with real time playback
   private class PlayActionListener implements ActionListener {
      public void actionPerformed(ActionEvent evt) {
         masterMotion.advance();
         // Kill self if done and wrapMotion is off
         if (masterMotion.finished(1)){
            animationTimer.stop();
            animationTimer=null;
         }
      }
   }
   private class PlayReverseActionListener implements ActionListener {
      public void actionPerformed(ActionEvent evt) {
          masterMotion.back();
          // Kill self if done and wrapMotion is off
          if (masterMotion.finished(-1)){
             animationTimer.stop();
             animationTimer=null;
          }
      }
   }
   */

   // ActionListener for the timer which is used to play motion forwards/backwards in such a way that
   // advances the model's time based on the real elapsed time (times the factor specified by the smodel spinner)
   private class RealTimePlayActionListener implements ActionListener {
      private boolean firstAction=true;
      private long lastActionTimeNano;
      private int direction;

      private double avgCost = 0;
      private int avgCostCount = 0;

      public RealTimePlayActionListener(int direction) { this.direction = direction; }

      public void actionPerformed(ActionEvent evt) {
         long currentTimeNano = System.nanoTime();
         if(firstAction) {
            firstAction = false;
            lastActionTimeNano = currentTimeNano;
            masterMotion.advanceTime(0);
         } else {
            double speed = (double)(((Double)smodel.getValue()).doubleValue());
            double factor = (double)direction*1e-9*speed;
            if (org.opensim.view.OpenSimCanvas.movieWriterReady) { // check if movie is being written in any view
                masterMotion.advanceTime(speed/15.0); // vtkAVIWriter writes at 15 fps, so advance time by (speed/15) seconds
                //System.out.println("writingMovie masterMotion current time = "+(masterMotion.getCurrentTime()));
            }
            else {
                //System.out.println("Time since last call "+(currentTimeNano-lastActionTimeNano)+" ns");
                masterMotion.advanceTime(factor*(currentTimeNano-lastActionTimeNano));
                //System.out.println("             masterMotion current time = "+(masterMotion.getCurrentTime()));
            }
            lastActionTimeNano = currentTimeNano;
         }

         // Kill self if done and wrapMotion is off
         if (masterMotion.finished(direction)){
            //animationTimer.stop();
            //animationTimer=null;
            jStopButtonActionPerformed(evt);
         } else {
            /*
            double ms=1e-6*(System.nanoTime()-currentTimeNano);
            avgCost += ms; avgCostCount++;
            int elapsedTimeMS = (int)ms;
            //int nextDelay = (timerRate>elapsedTimeMS) ? timerRate - elapsedTimeMS : 0;
            //int nextDelay = 0;
            System.out.println("Current: "+ms+" Avg: "+avgCost/avgCostCount);
            //animationTimer.setDelay(nextDelay);
            */
         }
      }
   }
   
   /**
    * Creates new form MotionControlJPanel
    */
   public MotionControlJPanel() {
      masterMotion = new MasterMotionModel();   // initialize the object backing the GUI.

      initComponents();
      rangeResolution = jMotionSlider.getMaximum(); // assume resolution was set up as max value of slider in form designer

      masterMotion.addChangeListener(this);
      jMotionSlider.addChangeListener(this);             // listen to changes in the slider itself.
      MotionsDB.getInstance().addObserver(this);

      updatePanelDisplay();
   }
   
   /** This method is called from within the constructor to
    * initialize the form.
    * WARNING: Do NOT modify this code. The content of this method is
    * always regenerated by the Form Editor.
    */
    // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
    private void initComponents() {
        jPlaybackButtonsPanel = new javax.swing.JPanel();
        jRestartButton = new javax.swing.JButton();
        jBackButton = new javax.swing.JButton();
        jReverseButton = new javax.swing.JButton();
        jStopButton = new javax.swing.JButton();
        jPlayButton = new javax.swing.JButton();
        jAdvanceButton = new javax.swing.JButton();
        jFinishButton = new javax.swing.JButton();
        jMotionSlider = new javax.swing.JSlider();
        jLabelForMotionNameLabel = new javax.swing.JLabel();
        jMotionNameLabel = new javax.swing.JLabel();
        jTimeTextField = new javax.swing.JTextField();
        jSpeedSpinner = new javax.swing.JSpinner();
        jLabelForSpeedSpinner = new javax.swing.JLabel();
        jLabelForTimeTextField = new javax.swing.JLabel();
        jWrapToggleButton = new javax.swing.JToggleButton();
        jStartTimeTextField = new javax.swing.JTextField();
        jEndTimeTextField = new javax.swing.JTextField();

        setMaximumSize(new java.awt.Dimension(32767, 42));
        setMinimumSize(new java.awt.Dimension(0, 42));
        jPlaybackButtonsPanel.setLayout(new java.awt.FlowLayout(java.awt.FlowLayout.CENTER, 0, 0));

        jPlaybackButtonsPanel.setToolTipText("Motion Controls");
        jPlaybackButtonsPanel.setMaximumSize(new java.awt.Dimension(32767, 16));
        jPlaybackButtonsPanel.setMinimumSize(new java.awt.Dimension(168, 16));
        jPlaybackButtonsPanel.setPreferredSize(new java.awt.Dimension(168, 16));
        jRestartButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/rewindToStart_beveled.png")));
        jRestartButton.setToolTipText("Go to start");
        jRestartButton.setBorder(null);
        jRestartButton.setBorderPainted(false);
        jRestartButton.setContentAreaFilled(false);
        jRestartButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        jRestartButton.setMaximumSize(new java.awt.Dimension(24, 16));
        jRestartButton.setMinimumSize(new java.awt.Dimension(24, 16));
        jRestartButton.setPreferredSize(new java.awt.Dimension(24, 16));
        jRestartButton.setPressedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/rewindToStart_beveled_selected.png")));
        jRestartButton.setRolloverIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/rewindToStart_beveled_rollover.png")));
        jRestartButton.setRolloverSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/rewindToStart_beveled_rollover_selected.png")));
        jRestartButton.setSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/rewindToStart_beveled_selected.png")));
        jRestartButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jRestartButtonActionPerformed(evt);
            }
        });

        jPlaybackButtonsPanel.add(jRestartButton);

        jBackButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/reverseStep_beveled.png")));
        jBackButton.setToolTipText("Previous frame");
        jBackButton.setBorder(null);
        jBackButton.setBorderPainted(false);
        jBackButton.setContentAreaFilled(false);
        jBackButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        jBackButton.setMaximumSize(new java.awt.Dimension(24, 16));
        jBackButton.setMinimumSize(new java.awt.Dimension(24, 16));
        jBackButton.setPreferredSize(new java.awt.Dimension(24, 16));
        jBackButton.setPressedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/reverseStep_beveled_selected.png")));
        jBackButton.setRolloverIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/reverseStep_beveled_rollover.png")));
        jBackButton.setRolloverSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/reverseStep_beveled_rollover_selected.png")));
        jBackButton.setSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/reverseStep_beveled_selected.png")));
        jBackButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jBackButtonActionPerformed(evt);
            }
        });

        jPlaybackButtonsPanel.add(jBackButton);

        jReverseButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/reverse_beveled.png")));
        jReverseButton.setToolTipText("Play backward");
        jReverseButton.setBorder(null);
        jReverseButton.setBorderPainted(false);
        jReverseButton.setContentAreaFilled(false);
        jReverseButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        jReverseButton.setMaximumSize(new java.awt.Dimension(24, 16));
        jReverseButton.setMinimumSize(new java.awt.Dimension(24, 16));
        jReverseButton.setPreferredSize(new java.awt.Dimension(24, 16));
        jReverseButton.setPressedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/reverse_beveled_selected.png")));
        jReverseButton.setRolloverIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/reverse_beveled_rollover.png")));
        jReverseButton.setRolloverSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/reverse_beveled_rollover_selected.png")));
        jReverseButton.setSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/reverse_beveled_selected.png")));
        jReverseButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jPlayReverseButtonActionPerformed(evt);
            }
        });

        jPlaybackButtonsPanel.add(jReverseButton);

        jStopButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/pause_beveled.png")));
        jStopButton.setToolTipText("Pause");
        jStopButton.setBorder(null);
        jStopButton.setBorderPainted(false);
        jStopButton.setContentAreaFilled(false);
        jStopButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        jStopButton.setMaximumSize(new java.awt.Dimension(24, 16));
        jStopButton.setMinimumSize(new java.awt.Dimension(24, 16));
        jStopButton.setPreferredSize(new java.awt.Dimension(24, 16));
        jStopButton.setPressedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/pause_beveled_selected.png")));
        jStopButton.setRolloverIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/pause_beveled_rollover.png")));
        jStopButton.setRolloverSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/pause_beveled_rollover_selected.png")));
        jStopButton.setSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/pause_beveled_selected.png")));
        jStopButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jStopButtonActionPerformed(evt);
            }
        });

        jPlaybackButtonsPanel.add(jStopButton);

        jPlayButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/play_beveled.png")));
        jPlayButton.setToolTipText("Play forward");
        jPlayButton.setBorder(null);
        jPlayButton.setBorderPainted(false);
        jPlayButton.setContentAreaFilled(false);
        jPlayButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        jPlayButton.setMaximumSize(new java.awt.Dimension(24, 16));
        jPlayButton.setMinimumSize(new java.awt.Dimension(24, 16));
        jPlayButton.setPreferredSize(new java.awt.Dimension(24, 16));
        jPlayButton.setPressedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/play_beveled_selected.png")));
        jPlayButton.setRolloverIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/play_beveled_rollover.png")));
        jPlayButton.setRolloverSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/play_beveled_rollover_selected.png")));
        jPlayButton.setSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/play_beveled_selected.png")));
        jPlayButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jPlayButtonActionPerformed(evt);
            }
        });

        jPlaybackButtonsPanel.add(jPlayButton);

        jAdvanceButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/step_beveled.png")));
        jAdvanceButton.setToolTipText("Next frame");
        jAdvanceButton.setBorder(null);
        jAdvanceButton.setBorderPainted(false);
        jAdvanceButton.setContentAreaFilled(false);
        jAdvanceButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        jAdvanceButton.setMaximumSize(new java.awt.Dimension(24, 16));
        jAdvanceButton.setMinimumSize(new java.awt.Dimension(24, 16));
        jAdvanceButton.setPreferredSize(new java.awt.Dimension(24, 16));
        jAdvanceButton.setPressedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/step_beveled_selected.png")));
        jAdvanceButton.setRolloverIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/step_beveled_rollover.png")));
        jAdvanceButton.setRolloverSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/step_beveled_rollover_selected.png")));
        jAdvanceButton.setSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/step_beveled_selected.png")));
        jAdvanceButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jAdvanceButtonActionPerformed(evt);
            }
        });

        jPlaybackButtonsPanel.add(jAdvanceButton);

        jFinishButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/fastforwardToEnd_beveled.png")));
        jFinishButton.setToolTipText("Go to end");
        jFinishButton.setBorder(null);
        jFinishButton.setBorderPainted(false);
        jFinishButton.setContentAreaFilled(false);
        jFinishButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        jFinishButton.setMaximumSize(new java.awt.Dimension(24, 16));
        jFinishButton.setMinimumSize(new java.awt.Dimension(24, 16));
        jFinishButton.setPreferredSize(new java.awt.Dimension(24, 16));
        jFinishButton.setPressedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/fastforwardToEnd_beveled_selected.png")));
        jFinishButton.setRolloverIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/fastforwardToEnd_beveled_rollover.png")));
        jFinishButton.setRolloverSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/fastforwardToEnd_beveled_rollover_selected.png")));
        jFinishButton.setSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/fastforwardToEnd_beveled_selected.png")));
        jFinishButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jFinishButtonActionPerformed(evt);
            }
        });

        jPlaybackButtonsPanel.add(jFinishButton);

        jMotionSlider.setMajorTickSpacing(1000);
        jMotionSlider.setMaximum(10000);
        jMotionSlider.setMinorTickSpacing(200);
        jMotionSlider.setToolTipText("Seek");
        jMotionSlider.setValue(0);
        jMotionSlider.setFocusable(false);
        jMotionSlider.setMaximumSize(new java.awt.Dimension(32767, 22));
        jMotionSlider.setMinimumSize(new java.awt.Dimension(168, 22));
        jMotionSlider.setPreferredSize(new java.awt.Dimension(168, 22));

        jLabelForMotionNameLabel.setFont(new java.awt.Font("Tahoma", 1, 11));
        jLabelForMotionNameLabel.setLabelFor(jMotionNameLabel);
        jLabelForMotionNameLabel.setText("Motion");
        jLabelForMotionNameLabel.setMaximumSize(new java.awt.Dimension(42, 42));
        jLabelForMotionNameLabel.setMinimumSize(new java.awt.Dimension(42, 42));
        jLabelForMotionNameLabel.setPreferredSize(new java.awt.Dimension(42, 42));

        jMotionNameLabel.setToolTipText("Current motion");
        jMotionNameLabel.setBorder(javax.swing.BorderFactory.createEtchedBorder());
        jMotionNameLabel.setMaximumSize(new java.awt.Dimension(200, 20));
        jMotionNameLabel.setMinimumSize(new java.awt.Dimension(200, 20));
        jMotionNameLabel.setOpaque(true);
        jMotionNameLabel.setPreferredSize(new java.awt.Dimension(200, 20));

        jTimeTextField.setToolTipText("Current time");
        jTimeTextField.setMaximumSize(new java.awt.Dimension(50, 19));
        jTimeTextField.setMinimumSize(new java.awt.Dimension(50, 19));
        jTimeTextField.setPreferredSize(new java.awt.Dimension(50, 19));
        jTimeTextField.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jTimeTextFieldActionPerformed(evt);
            }
        });
        jTimeTextField.addPropertyChangeListener(new java.beans.PropertyChangeListener() {
            public void propertyChange(java.beans.PropertyChangeEvent evt) {
                jTimeTextFieldPropertyChange(evt);
            }
        });
        jTimeTextField.addFocusListener(new java.awt.event.FocusAdapter() {
            public void focusLost(java.awt.event.FocusEvent evt) {
                jTimeTextFieldFocusLost(evt);
            }
        });

        jSpeedSpinner.setBackground(new java.awt.Color(255, 255, 255));
        jSpeedSpinner.setFont(new java.awt.Font("Tahoma", 0, 11));
        jSpeedSpinner.setForeground(new java.awt.Color(0, 0, 0));
        jSpeedSpinner.setModel(smodel);
        jSpeedSpinner.setToolTipText("Play speed");
        jSpeedSpinner.setMaximumSize(new java.awt.Dimension(50, 19));
        jSpeedSpinner.setMinimumSize(new java.awt.Dimension(50, 19));
        jSpeedSpinner.setPreferredSize(new java.awt.Dimension(50, 19));

        jLabelForSpeedSpinner.setFont(new java.awt.Font("Tahoma", 1, 11));
        jLabelForSpeedSpinner.setLabelFor(jSpeedSpinner);
        jLabelForSpeedSpinner.setText("Speed");
        jLabelForSpeedSpinner.setMaximumSize(new java.awt.Dimension(37, 19));
        jLabelForSpeedSpinner.setMinimumSize(new java.awt.Dimension(37, 19));
        jLabelForSpeedSpinner.setPreferredSize(new java.awt.Dimension(37, 19));

        jLabelForTimeTextField.setFont(new java.awt.Font("Tahoma", 1, 11));
        jLabelForTimeTextField.setLabelFor(jTimeTextField);
        jLabelForTimeTextField.setText("Time");
        jLabelForTimeTextField.setMaximumSize(new java.awt.Dimension(31, 19));
        jLabelForTimeTextField.setMinimumSize(new java.awt.Dimension(31, 19));
        jLabelForTimeTextField.setPreferredSize(new java.awt.Dimension(31, 19));

        jWrapToggleButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/wrap_beveled.png")));
        jWrapToggleButton.setToolTipText("Loop motion");
        jWrapToggleButton.setBorder(null);
        jWrapToggleButton.setBorderPainted(false);
        jWrapToggleButton.setContentAreaFilled(false);
        jWrapToggleButton.setFocusable(false);
        jWrapToggleButton.setIconTextGap(0);
        jWrapToggleButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        jWrapToggleButton.setMaximumSize(new java.awt.Dimension(24, 42));
        jWrapToggleButton.setMinimumSize(new java.awt.Dimension(24, 42));
        jWrapToggleButton.setOpaque(true);
        jWrapToggleButton.setPreferredSize(new java.awt.Dimension(24, 42));
        jWrapToggleButton.setPressedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/wrap_beveled_selected.png")));
        jWrapToggleButton.setRolloverIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/wrap_beveled_rollover.png")));
        jWrapToggleButton.setRolloverSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/wrap_beveled_rollover_selected.png")));
        jWrapToggleButton.setSelectedIcon(new javax.swing.ImageIcon(getClass().getResource("/org/opensim/motionviewer/images/wrap_beveled_selected.png")));
        jWrapToggleButton.setVerticalAlignment(javax.swing.SwingConstants.TOP);
        jWrapToggleButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jWrapToggleButtonActionPerformed(evt);
            }
        });

        jStartTimeTextField.setBackground(new java.awt.Color(224, 223, 227));
        jStartTimeTextField.setEditable(false);
        jStartTimeTextField.setText("0");
        jStartTimeTextField.setToolTipText("Initial time");
        jStartTimeTextField.setAutoscrolls(false);
        jStartTimeTextField.setBorder(null);
        jStartTimeTextField.setFocusable(false);
        jStartTimeTextField.setMaximumSize(new java.awt.Dimension(50, 16));
        jStartTimeTextField.setMinimumSize(new java.awt.Dimension(50, 16));
        jStartTimeTextField.setOpaque(false);
        jStartTimeTextField.setPreferredSize(new java.awt.Dimension(50, 16));

        jEndTimeTextField.setBackground(new java.awt.Color(224, 223, 227));
        jEndTimeTextField.setEditable(false);
        jEndTimeTextField.setHorizontalAlignment(javax.swing.JTextField.TRAILING);
        jEndTimeTextField.setText("100");
        jEndTimeTextField.setToolTipText("Final time");
        jEndTimeTextField.setAutoscrolls(false);
        jEndTimeTextField.setBorder(null);
        jEndTimeTextField.setFocusable(false);
        jEndTimeTextField.setMaximumSize(new java.awt.Dimension(50, 16));
        jEndTimeTextField.setMinimumSize(new java.awt.Dimension(50, 16));
        jEndTimeTextField.setOpaque(false);
        jEndTimeTextField.setPreferredSize(new java.awt.Dimension(50, 16));

        org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(layout.createSequentialGroup()
                .addContainerGap()
                .add(jLabelForMotionNameLabel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jMotionNameLabel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(jLabelForSpeedSpinner, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jLabelForTimeTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(jTimeTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                    .add(jSpeedSpinner, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(layout.createSequentialGroup()
                        .add(jStartTimeTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 50, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jPlaybackButtonsPanel, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 293, Short.MAX_VALUE)
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                        .add(jEndTimeTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 50, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                    .add(jMotionSlider, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 405, Short.MAX_VALUE))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(jWrapToggleButton, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 24, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(layout.createSequentialGroup()
                .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                        .add(jLabelForMotionNameLabel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                        .add(jMotionNameLabel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                    .add(layout.createSequentialGroup()
                        .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                            .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                                .add(jTimeTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                                .add(jLabelForTimeTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                            .add(jMotionSlider, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 22, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                        .add(0, 0, 0)
                        .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                            .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.BASELINE)
                                .add(jLabelForSpeedSpinner, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                                .add(jSpeedSpinner, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                                .add(jStartTimeTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                            .add(layout.createSequentialGroup()
                                .add(0, 0, 0)
                                .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                                    .add(jEndTimeTextField, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                                    .add(jPlaybackButtonsPanel, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 16, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)))))
                    .add(jWrapToggleButton, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 32, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                .add(1, 1, 1))
        );
    }// </editor-fold>//GEN-END:initComponents

    private void jFinishButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jFinishButtonActionPerformed
// TODO add your handling code here:
      if (isMotionLoaded()) { 
          masterMotion.setTime(masterMotion.getEndTime());
          // correct selected modes
          if (jPlayButton.isSelected() && !jWrapToggleButton.isSelected()) {
              jStopButton.setSelected(true);
              jPlayButton.setSelected(false);
          }
      }
      else { jMotionSlider.setValue(0); }
    }//GEN-LAST:event_jFinishButtonActionPerformed

   private void jRestartButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jRestartButtonActionPerformed
// TODO add your handling code here:
      if (isMotionLoaded()) { 
          masterMotion.setTime(masterMotion.getStartTime());
          // correct selected modes
          if (jReverseButton.isSelected() && !jWrapToggleButton.isSelected()) {
              jStopButton.setSelected(true);
              jReverseButton.setSelected(false);
          }
      }
      else { jMotionSlider.setValue(0); }
   }//GEN-LAST:event_jRestartButtonActionPerformed

   private void jTimeTextFieldPropertyChange(java.beans.PropertyChangeEvent evt) {//GEN-FIRST:event_jTimeTextFieldPropertyChange
   // Listen to "value" changes
      handleUserTimeChange();
// TODO add your handling code here:
   }//GEN-LAST:event_jTimeTextFieldPropertyChange
   
   private void jTimeTextFieldFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_jTimeTextFieldFocusLost
// TODO add your handling code here:
      handleUserTimeChange();
   }//GEN-LAST:event_jTimeTextFieldFocusLost
   
   private void jTimeTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jTimeTextFieldActionPerformed
      handleUserTimeChange();
// TODO add your handling code here:
   }//GEN-LAST:event_jTimeTextFieldActionPerformed
   
   private void jBackButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jBackButtonActionPerformed
      if (isMotionLoaded()){
          masterMotion.back();
          // correct selected modes
          jStopButtonActionPerformed(evt);
      }
   }//GEN-LAST:event_jBackButtonActionPerformed
   
   private void jPlayReverseButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jPlayReverseButtonActionPerformed
      if (animationTimer!=null){
         animationTimer.stop();
         animationTimer=null;
      }
      if (isMotionLoaded() && animationTimer==null){
          if (masterMotion.finished(-1)){
              // reset motion if at end already
              masterMotion.setTime(masterMotion.getEndTime());
          }
          animationTimer = new Timer(timerRate, new RealTimePlayActionListener(-1));
          animationTimer.start();
          // correct selected modes
          deselectPlaybackButtons();
          jReverseButton.setSelected(true);
      }
   }//GEN-LAST:event_jPlayReverseButtonActionPerformed
   
    private void jStopButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jStopButtonActionPerformed
       if (isMotionLoaded() && animationTimer != null){
          animationTimer.stop();
          animationTimer = null;
          // correct selected modes
          deselectPlaybackButtons();
          jStopButton.setSelected(true);
       }
    }//GEN-LAST:event_jStopButtonActionPerformed
    
    private void jWrapToggleButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jWrapToggleButtonActionPerformed
       
       masterMotion.setWrapMotion(!masterMotion.isWrapMotion());
    }//GEN-LAST:event_jWrapToggleButtonActionPerformed
    
    private void jAdvanceButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jAdvanceButtonActionPerformed
       if (isMotionLoaded()){
          masterMotion.advance();
          // correct selected modes
          jStopButtonActionPerformed(evt);
       }
    }//GEN-LAST:event_jAdvanceButtonActionPerformed
    
    private void jPlayButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jPlayButtonActionPerformed
      if (animationTimer!=null){
         animationTimer.stop();
         animationTimer=null;
      }
      if (isMotionLoaded() && animationTimer==null){
          if (masterMotion.finished(1)){
              // reset motion if at end already
              masterMotion.setTime(masterMotion.getStartTime());
          }
          animationTimer = new Timer(timerRate, new RealTimePlayActionListener(1));
          animationTimer.start();
          // correct selected modes
          deselectPlaybackButtons();
          jPlayButton.setSelected(true);
      }
    }//GEN-LAST:event_jPlayButtonActionPerformed
    
    
    public void stateChanged(ChangeEvent e) 
    {
       if (isMotionLoaded()){
          if (e.getSource().equals(masterMotion) && !internalTrigger){
             internalTrigger=true;
             jMotionSlider.setValue(getSliderValueForTime(masterMotion.getCurrentTime()));
             internalTrigger=false;
             setTimeTextField(masterMotion.getCurrentTime());
          } else if (e.getSource().equals(jMotionSlider) && !internalTrigger){
             internalTrigger=true;
             masterMotion.setTime(getTimeForSliderValue(jMotionSlider.getValue()));
             internalTrigger=false;
             setTimeTextField(masterMotion.getCurrentTime());
          }
       }
    }
    
    public boolean isMotionLoaded() {
       return motionLoaded;
    }
    
    private void handleUserTimeChange() {
       if (isMotionLoaded()){
          //get frame corresponding to enetered time
          double userTime = 0.0;
          try {
             userTime = Double.valueOf(jTimeTextField.getText());
          }catch (NumberFormatException e){
             userTime = 0.0;
          }
          masterMotion.setTime(userTime);
       }
    }

   Hashtable makeLabels(int n, double startTime, double endTime) {
      Hashtable<Integer, JLabel> labels = new Hashtable<Integer, JLabel>(5);
      for(int i=0; i<n; i++){
         double alpha=(double)i/(n-1);
         String label = Double.toString(startTime+alpha*(endTime-startTime));
         if (label.length()>5) label=label.substring(0, 5);
         labels.put((int)(alpha*rangeResolution), new JLabel(label));
      }
      return labels;
   }

   /**
    * update the panel to reflect current motion's name, range, ...etc.
    */
   private void updatePanelDisplay() {
      if (masterMotion==null || masterMotion.getNumMotions()==0){
         jMotionNameLabel.setText("No Motions");
         setTimeTextField(0);
         jStartTimeTextField.setText("");
         jEndTimeTextField.setText("");
         Hashtable labels = makeLabels(5, 0, 1);
         jMotionSlider.setLabelTable(labels);
         // disable components
         disableComponents();
      }
      else {
         if (masterMotion.getNumMotions()>=1){
            jMotionNameLabel.setText(masterMotion.getDisplayName());
            setTimeTextField(masterMotion.getCurrentTime());
            setStartTimeTextField(masterMotion.getStartTime());
            setEndTimeTextField(masterMotion.getEndTime());
            Hashtable labels = makeLabels(5, masterMotion.getStartTime(), masterMotion.getEndTime());
            jMotionSlider.setLabelTable(labels);
            // enable components
            enableComponents();
            // correct selected mode
            if (!jPlayButton.isSelected() && !jReverseButton.isSelected()){
                jStopButton.setSelected(true);
            }
         }
      }
   }
   
   // Observable is MotionsDB
   public void update(Observable o, Object arg) {
      // Recover motion info, update toolbar accordingly
      if (o instanceof MotionsDB){
         MotionsDB mdb = (MotionsDB)o;
         if (!(arg instanceof MotionEvent)) // time should be ignored here
             return;
         MotionEvent evt = (MotionEvent)arg;
         if (evt.getOperation() == Operation.CurrentMotionsChanged){
            // Current motion changed.  Update master motion
            double currentTime = masterMotion.getCurrentTime();
            masterMotion.clear();
            for(int i=0; i<mdb.getNumCurrentMotions(); i++)
               masterMotion.add(mdb.getCurrentMotion(i));
            masterMotion.setTime(currentTime);
         }
         motionLoaded = (masterMotion.getNumMotions() > 0);
         updatePanelDisplay();
      }
   }
   
   private void setTimeTextField(double time)
   {
      DecimalFormat df = new DecimalFormat("0.000");
      jTimeTextField.setText(df.format(time));
   }
   
   private void setStartTimeTextField(double time)
   {
      DecimalFormat df = new DecimalFormat(" 0.000");
      jStartTimeTextField.setText(df.format(time));
   }

   private void setEndTimeTextField(double time)
   {
      DecimalFormat df = new DecimalFormat("0.000");
      jEndTimeTextField.setText(df.format(time));
   }
      
   private int getSliderValueForTime(double time)
   {
      if(masterMotion==null || masterMotion.getStartTime() == masterMotion.getEndTime()) 
         return 0;
      else {
         double alpha = (time-masterMotion.getStartTime())/(masterMotion.getEndTime()-masterMotion.getStartTime());
         return (int)(alpha*rangeResolution);
      }
   }

   private double getTimeForSliderValue(int sliderValue)
   {
      if(masterMotion==null) return 0;
      double alpha = (double)sliderValue/rangeResolution;
      return masterMotion.getStartTime() + alpha * (masterMotion.getEndTime()-masterMotion.getStartTime());
   }

   public void enableComponents() 
   {
        jAdvanceButton.setEnabled(true);
        jBackButton.setEnabled(true);
        jFinishButton.setEnabled(true);
        jLabelForMotionNameLabel.setEnabled(true);
        jLabelForSpeedSpinner.setEnabled(true);
        jLabelForTimeTextField.setEnabled(true);
        jMotionNameLabel.setEnabled(true);
        jMotionSlider.setEnabled(true);
        jPlayButton.setEnabled(true);
        jPlaybackButtonsPanel.setEnabled(true);
        jRestartButton.setEnabled(true);
        jReverseButton.setEnabled(true);
        jSpeedSpinner.setEnabled(true);
        jStopButton.setEnabled(true);
        jTimeTextField.setEnabled(true);
        jWrapToggleButton.setEnabled(true);
   }
   
   public void disableComponents() 
   {
        jAdvanceButton.setEnabled(false);
        jBackButton.setEnabled(false);
        jFinishButton.setEnabled(false);
        jLabelForMotionNameLabel.setEnabled(false);
        jLabelForSpeedSpinner.setEnabled(false);
        jLabelForTimeTextField.setEnabled(false);
        jMotionNameLabel.setEnabled(false);
        jMotionSlider.setEnabled(false);
        jPlayButton.setEnabled(false);
        jPlaybackButtonsPanel.setEnabled(false);
        jRestartButton.setEnabled(false);
        jReverseButton.setEnabled(false);
        jSpeedSpinner.setEnabled(false);
        jStopButton.setEnabled(false);
        jTimeTextField.setEnabled(false);
        jWrapToggleButton.setEnabled(false);
   }
   
   public void deselectPlaybackButtons() 
   {
       jAdvanceButton.setSelected(false);
       jBackButton.setSelected(false);
       jFinishButton.setSelected(false);
       jPlayButton.setSelected(false);
       jRestartButton.setSelected(false);
       jReverseButton.setSelected(false);
       jStopButton.setSelected(false);
   }
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton jAdvanceButton;
    private javax.swing.JButton jBackButton;
    private javax.swing.JTextField jEndTimeTextField;
    private javax.swing.JButton jFinishButton;
    private javax.swing.JLabel jLabelForMotionNameLabel;
    private javax.swing.JLabel jLabelForSpeedSpinner;
    private javax.swing.JLabel jLabelForTimeTextField;
    private javax.swing.JLabel jMotionNameLabel;
    private javax.swing.JSlider jMotionSlider;
    private javax.swing.JButton jPlayButton;
    private javax.swing.JPanel jPlaybackButtonsPanel;
    private javax.swing.JButton jRestartButton;
    private javax.swing.JButton jReverseButton;
    private javax.swing.JSpinner jSpeedSpinner;
    private javax.swing.JTextField jStartTimeTextField;
    private javax.swing.JButton jStopButton;
    private javax.swing.JTextField jTimeTextField;
    private javax.swing.JToggleButton jWrapToggleButton;
    // End of variables declaration//GEN-END:variables

}
