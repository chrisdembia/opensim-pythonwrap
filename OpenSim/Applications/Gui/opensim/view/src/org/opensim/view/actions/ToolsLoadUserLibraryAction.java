package org.opensim.view.actions;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileFilter;
import javax.swing.AbstractAction;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import org.openide.DialogDescriptor;
import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.opensim.view.pub.PluginsDB;

public final class ToolsLoadUserLibraryAction extends CallableSystemAction {
    
    public void performAction() {
        // TODO implement action body
        return ;
    }
    
    public String getName() {
        return NbBundle.getMessage(ToolsLoadUserLibraryAction.class, "CTL_LoadUserLibraryAction");
    }
    
    protected void initialize() {
        super.initialize();
        // see org.openide.util.actions.SystemAction.iconResource() javadoc for more details
        putValue("noIconInMenu", Boolean.TRUE);
    }
    
    public HelpCtx getHelpCtx() {
        return HelpCtx.DEFAULT_HELP;
    }
    
    protected boolean asynchronous() {
        return false;
    }
    
    public JMenuItem getMenuPresenter() {
      JMenu displayMenu = new JMenu("User Plugins");
      FileFilter fileFilter = new FileFilter() {
                public boolean accept(File file) {
                    // For now .dll for windows should generalize to other platforms based on OS property
                    return (!file.isDirectory()&& file.getName().endsWith(".dll"));
                }
      };
      File rootExtensionsDirectory= new File("plugins");
      String fullPath = rootExtensionsDirectory.getAbsolutePath();
      System.out.println("Loading plugins from directory "+fullPath);
      File[] files = rootExtensionsDirectory.listFiles(fileFilter);
      if (files == null)  return displayMenu;
      
      for (int i=0; i<files.length; i++){
        final String filename=files[i].getName();
        JMenuItem extItem = new JMenuItem(filename);
        extItem.addActionListener(new ActionListener(){
                public void actionPerformed(ActionEvent e) {
                    LoadPluginJPanel loadPluginJPanel= new LoadPluginJPanel();
                    DialogDescriptor confirmDialog = new DialogDescriptor(loadPluginJPanel, "Load user plugin");
                    String libName = filename.substring(0, filename.indexOf("."));
                    System.loadLibrary(libName);
                    
                    DialogDisplayer.getDefault().createDialog(confirmDialog).setVisible(true);
                    // Check if we need to always preload
                    if(loadPluginJPanel.isPreloadAlways()){
                        System.out.println("Always preload "+filename);
                        PluginsDB.getInstance().addLibrary(libName);
                    }
                }});
        displayMenu.add(extItem);
      }
      return displayMenu;
    }
    
}
