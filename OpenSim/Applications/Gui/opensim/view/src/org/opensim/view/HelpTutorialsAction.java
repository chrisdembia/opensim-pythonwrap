package org.opensim.view;

import java.io.File;
import java.io.FileFilter;
import java.net.MalformedURLException;
import java.net.URL;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;

public final class HelpTutorialsAction extends CallableSystemAction {
    
    public void performAction() {
        // TODO implement action body
    }
    
    public String getName() {
        return NbBundle.getMessage(HelpTutorialsAction.class, "CTL_TutorialsAction");
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
      JMenu displayMenu = new JMenu("Tutorials");
      FileFilter fileFilter = new FileFilter() {
                public boolean accept(File file) {
                    return (!file.isDirectory()&& file.getName().endsWith(".html"));
                }
      };
      File rootHelpDirectory= new File("Help/Tutorials");
      String fullPath = rootHelpDirectory.getAbsolutePath();
      File[] files = rootHelpDirectory.listFiles(fileFilter);
      if (files == null)  return displayMenu;
      
      for (int i=0; i<files.length; i++){
        // List html files in tutorials directory 
                // List html files in tutorials directory 
        displayMenu.add(new BrowserPageDisplayerAction(files[i]));
      }
      return displayMenu;
    }
    
}
