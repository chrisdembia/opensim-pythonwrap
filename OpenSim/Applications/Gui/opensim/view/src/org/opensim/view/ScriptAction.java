package org.opensim.view;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.StringTokenizer;
import javax.swing.JFileChooser;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CallableSystemAction;
import org.openide.util.actions.SystemAction;

public final class ScriptAction extends CallableSystemAction {
    
    public void performAction() {
        // TODO implement action body
        final JFileChooser dlog = new JFileChooser();
        
        if (dlog.showOpenDialog(null) == JFileChooser.APPROVE_OPTION && dlog.getSelectedFile() != null) {
            String fileName = dlog.getSelectedFile().getAbsolutePath();

            // We'll have to handle the read commands in a different thread
            try {
             BufferedReader in = new BufferedReader(new FileReader(fileName));
             String str;

             while ((str = in.readLine()) != null) {
                 if (str.length()==0)
                   continue;
                 process(str);
              }
             in.close();
           } catch (IOException e) {
           }
            
        }
    }
    
    public String getName() {
        return NbBundle.getMessage(ScriptAction.class, "CTL_ScriptAction");
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

    private void process(String str) {
        // Read and process one line of the commands file
        StringTokenizer st = new StringTokenizer(str, "'");
        while(st.hasMoreTokens()){
            String nextTok = st.nextToken();
            if (nextTok.equals("!"))
                continue;
            String commandName = nextTok;

            String[] args;
            while(st.hasMoreTokens()){
                System.out.print(st.nextToken());
            }
        }
    }
    
}
