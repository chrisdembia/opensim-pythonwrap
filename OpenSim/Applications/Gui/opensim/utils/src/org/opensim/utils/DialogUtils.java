/*
 *
 * DialogUtils.java
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

package org.opensim.utils;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.WindowConstants;

/**
 *
 * @author Ayman
 * Utilities to support Dialog creattion. Normally this is not needed since Netbeans provides
 * a nice Dialog constructionmechanism. Problem is that we have "modeless" frames to fix bug 485
 * and so we need to explicitly specify owners/parents of dialogs.
 */
public final class DialogUtils {
    
    /** Creates a new instance of DialogUtils */
    
    public static JFrame createFrameForPanel(final JPanel panel, String title) {
        JFrame f = new JFrame(title);
        f.getContentPane().setLayout(new BorderLayout());
        f.getContentPane().add(panel, BorderLayout.CENTER);
        // potentially add a "Close" button "
        f.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        f.pack();
        f.setLocationRelativeTo(null);
        f.setIconImage(TheApp.getAppImage());
        return f;
    }
    
    public static OpenSimDialog createDialogForPanelWithParent(Frame parent, final JPanel panel, String title) {
        OpenSimDialog d = new OpenSimDialog(parent);
        d.setTitle(title);
        d.getContentPane().setLayout(new BorderLayout());
        d.getContentPane().add(panel, BorderLayout.CENTER);
        // potentially add a "Close" button "
        d.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        
        d.pack();
        d.setLocationRelativeTo(parent);
        return d;
    }
    
    public static void addStandardButtons(final OpenSimDialog dlg) {
        JPanel buttonPanel = new JPanel();
        buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.X_AXIS));
        buttonPanel.add(Box.createRigidArea(new Dimension(50, 50)));
        buttonPanel.add(Box.createVerticalStrut(50));
        buttonPanel.add(Box.createGlue());
        dlg.getContentPane().add(buttonPanel, BorderLayout.SOUTH);
        
        JButton okButton = new JButton("OK");
        buttonPanel.add(okButton);
        okButton.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) {
                dlg.setDialogReturnValue(OpenSimDialog.OK_OPTION);
                dlg.dispose();
            }});
            JButton cancelButton = new JButton("Cancel");
            cancelButton.addActionListener(new ActionListener(){
                public void actionPerformed(ActionEvent e) {
                    dlg.setDialogReturnValue(OpenSimDialog.CANCEL_OPTION);
                    dlg.dispose();
                }});
                buttonPanel.add(cancelButton);
                // Window listener is added here since closing the dialog with [x] should
                // behave the same as close/cancel
        dlg.addWindowListener(new WindowAdapter(){
            public void windowClosed(WindowEvent e) {
                super.windowClosed(e);
                dlg.setDialogReturnValue(OpenSimDialog.CANCEL_OPTION);
            }

            public void windowClosing(WindowEvent e) {
                super.windowClosing(e);
                dlg.setDialogReturnValue(OpenSimDialog.CANCEL_OPTION);
            }
        });
        //dlg.doLayout();
        dlg.pack();

    }

    public static void addButtons(JFrame frame, JButton[] buttonsList, ActionListener listener) {
        // Create a control panel at the bottom of the passed in window for control buttons
        JPanel buttonPanel = new JPanel();
        buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.X_AXIS));
        buttonPanel.add(Box.createRigidArea(new Dimension(50, 50)));
        buttonPanel.add(Box.createVerticalStrut(50));
        buttonPanel.add(Box.createGlue());
        frame.getContentPane().add(buttonPanel, BorderLayout.SOUTH);
        for (int i=0; i<buttonsList.length; i++){
            buttonPanel.add(buttonsList[i]);
            buttonsList[i].addActionListener(listener);
            // Should also set return value for ok, cancel
        }
       //frame.doLayout();
       frame.pack();
    }
}
