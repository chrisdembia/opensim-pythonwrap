/*
 *
 * ValidateUserInput
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
package org.opensim.swingui;

import java.io.File;

/**
 *
 * @author Ayman, a final class with static methods to verify the validity of user input (e.g. file exists, 
 * type mismatch (string in int field) etc.
 */
public final class ValidateUserInput {
    
    /**
     * Check if a file exists, has correct permissions 
     */
    public static boolean validateFileExists(final String filename, 
                                            boolean shouldExist, 
                                            boolean directoriesOk,
                                            boolean isRequired)
    {
        boolean valid = true;
        
        if (filename.equals("") && isRequired)
            return false;
        
        try {
            File test = new File(filename);
            if (shouldExist)    // May ned to issue a warning for overwrite
                valid = test.exists();
            if (valid){
                valid = (test.isDirectory()==directoriesOk);
            }
        }
        catch (NullPointerException e){
            valid = false;
        }
        catch (SecurityException e){
            valid = false;
        }
        return valid;
    }
    /**
     * Validate a single double
     */
    public static boolean validateDouble(final String dString, boolean isRequired)
    {
        boolean valid=true;
        
        if (dString=="" && isRequired)
            return false;
        
        try {
            double dval = Double.parseDouble(dString);
        }
        catch(NumberFormatException e){
            valid = false;
        }
        return valid;
    }
    /**
     * Validate a range is made up of two numbers in right order
     **/
    public static boolean validateDoubleRange(final String min, 
                                            final String max, 
                                            boolean isRequired)
    {
        boolean valid = true;
        
        valid = validateDouble(min, isRequired);
        valid = valid && validateDouble(max, isRequired);
        if (valid && isRequired) { // Validate that min < max
            valid = (Double.parseDouble(max) > Double.parseDouble(min));
        }
        return valid;
    }
  
    
}
