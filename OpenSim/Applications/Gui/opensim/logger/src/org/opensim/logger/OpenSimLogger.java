/*
 *
 * OpenSimLogger
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
package org.opensim.logger;

/**
 *
 * @author Ayman. A wrapper to expose the logger window/topComponent
 *
 */
public final class OpenSimLogger {
   
   static LoggerTopComponent loggerWindowInstance;
   
   
   public static int OFF=-2;   // Could use enum too
   public static int DEBUG=-1;      
   public static int INFO=0;      
   public static int WARNING=1;      
   public static int ERROR=2;
   
   private static int errorLevel=INFO;
   
   /**
    * Creates a new loggerWindowInstance of OpenSimLogger
    */
   public OpenSimLogger() {      
   }
   
   public static void logMessage(String message, int messageErrorLevel)
   {
      if (loggerWindowInstance==null)
         loggerWindowInstance=LoggerTopComponent.getDefault();
      
      if (messageErrorLevel>=errorLevel)
         loggerWindowInstance.log(message);
   }

   public static void setErrorLevel(int aErrorLevel) {
      errorLevel = aErrorLevel;
   }
   
}
