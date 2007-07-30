package org.opensim.view;

import java.awt.event.ActionEvent;
import java.io.File;
import javax.swing.AbstractAction;
import org.opensim.utils.BrowserLauncher;


/**
 * A Class that displays a passed in url
 */
class BrowserPageDisplayerAction extends AbstractAction
{
    File dFile;
    
    public BrowserPageDisplayerAction(File localFile){
        super(localFile.getName());
        dFile=localFile;
    }
    public void actionPerformed(ActionEvent e) {
        BrowserLauncher.openURL(dFile.getAbsolutePath());            
    }
    
}