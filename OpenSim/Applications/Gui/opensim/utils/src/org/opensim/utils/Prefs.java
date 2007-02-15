/*
 *
 * Prefs
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
import java.util.StringTokenizer;
import java.util.prefs.Preferences;
import org.openide.util.NbBundle;

/**
 *
 * @author Ayman. Utilities to support/back preferences.
 */
public final class Prefs {
   
   private static Prefs instance;
    /**
     * Creates a new instance of Prefs
     */
    public static Prefs getInstance()
    {
       if (instance==null)
          instance = new Prefs();
       return instance;
       
    }
    public void putPref(String key, String value)
    {
        Preferences.userNodeForPackage(this.getClass()).put(key, value);
    }

    public String getPref(String key, String defaultValue)
    {
        return Preferences.userNodeForPackage(this.getClass()).get(key, defaultValue);
    }
    public String getPreferredDirectory()
    {
        String defaultDir="";
        defaultDir = Preferences.userNodeForPackage(this.getClass()).get("WorkDirectory", defaultDir);
 
        return defaultDir;
    }
    /**
     * Parse a string of color attributes and return it in an array of doubles
     */
    public double[] parseColor(String aColor) {
        double[] color = new double[3];
        int i=0;
        StringTokenizer tokenizer = new StringTokenizer(aColor, " \t\n\r\f,");
        while (tokenizer.hasMoreTokens() && i<3){
            String nextToken = tokenizer.nextToken();
            color[i] = Double.parseDouble(nextToken);
            i++;
        }
        return color;
    }

}
