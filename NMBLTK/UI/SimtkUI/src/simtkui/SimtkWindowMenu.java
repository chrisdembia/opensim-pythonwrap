package simtkui;


import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyVetoException;

import javax.swing.JCheckBoxMenuItem;
import javax.swing.JInternalFrame;
import javax.swing.JMenuItem;
import javax.swing.event.MenuEvent;
import javax.swing.event.MenuListener;

import simtkui.guiUtilities.SimtkJMenu;

/**
 * Menu component that handles the functionality expected of a standard
 * "Windows" menu for MDI applications.
 */
public class SimtkWindowMenu extends SimtkJMenu {
    private MDIDesktopPane desktop;
    private JMenuItem tileH=new JMenuItem("Tile Horizontal");
    private JMenuItem tileV=new JMenuItem("Tile Vertical");

    public SimtkWindowMenu(MDIDesktopPane desktop) {
        this.desktop=desktop;
        setText("Window");
        setName("Window");

        tileH.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent ae) {
                SimtkWindowMenu.this.desktop.tileFramesH();
            }
        });
        tileV.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent ae) {
                SimtkWindowMenu.this.desktop.tileFramesV();
            }
        });

        addMenuListener(new MenuListener() {
            public void menuCanceled (MenuEvent e) {}

            public void menuDeselected (MenuEvent e) {
                removeAll();
            }

            public void menuSelected (MenuEvent e) {
                buildChildMenus();
            }
        });
    }

    /* Sets up the children menus depending on the current desktop state */
    private void buildChildMenus() {
        int i;
        ChildMenuItem menu;
        JInternalFrame[] array = desktop.getAllFrames();

        add(tileH);
        add(tileV);
        if (array.length > 0) addSeparator();
        tileH.setEnabled(array.length > 0);
        tileV.setEnabled(array.length > 0);

        for (i = 0; i < array.length; i++) {
            menu = new ChildMenuItem(array[i]);
            menu.setState(i == 0);
            menu.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent ae) {
                    JInternalFrame frame = ((ChildMenuItem)ae.getSource()).getFrame();
                    frame.moveToFront();
                    try {
                        frame.setSelected(true);
                    } catch (PropertyVetoException e) {
                        e.printStackTrace();
                    }
                }
            });
            menu.setIcon(array[i].getFrameIcon());
            add(menu);
        }
    }

    /* This JCheckBoxMenuItem descendant is used to track the child frame that corresponds
       to a give menu. */
    class ChildMenuItem extends JCheckBoxMenuItem {
        private JInternalFrame frame;

        public ChildMenuItem(JInternalFrame frame) {
            super(frame.getTitle());
            this.frame=frame;
        }

        public JInternalFrame getFrame() {
            return frame;
        }
    }
}
