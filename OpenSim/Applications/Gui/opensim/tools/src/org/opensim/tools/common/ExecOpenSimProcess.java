/*
 *
 * ExecOpenSimProcess
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
package org.opensim.tools.common;

/**
 *
 * @author Ayman.
 *
 * Utilities to invoke a process, primarily wrapper around runtime.Exec. Main difference 
 * Is controlling how the output from the process is reported in the GUI.
 */
import java.util.*;
import java.io.*;

public class ExecOpenSimProcess
{
    public static boolean execute(String command, String[] env, File dirToExecuteIn)
    {
        try {            
            Runtime rt = Runtime.getRuntime();
            Process proc = rt.exec(command, env, dirToExecuteIn);
            InputStream stderr = proc.getInputStream();
            InputStreamReader isr = new InputStreamReader(stderr);
            BufferedReader br = new BufferedReader(isr);
            String line = null;
            // Append a tab in front of text to distinguish process output.
            // We may need to do this on separate thread. Also this will
            // need to be piped to a plce in the GUI instead of System.out.
            System.out.println("\t");
            while ( (line = br.readLine()) != null)
                System.out.println("\t"+line);
            System.out.println("\t");
            int exitVal = proc.waitFor();
            return (exitVal==0);	// More detailed error message will be needed
        } 
        catch (Throwable t) {
           t.printStackTrace();
           return false;
        }
    }
}

