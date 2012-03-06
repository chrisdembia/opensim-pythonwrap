//--------------------------------------------------------------------------
// File:     LSTextFieldWithListenersForDoubleNonNegative.java
// Parent:   LSTextFieldWithListenersForDouble
// Purpose:  LSTextFields with listeners for event handling to validate non-negative double precision number.
// Authors:  Paul Mitiguy (2011-2012).
//--------------------------------------------------------------------------
// This work is dedicated to the public domain.
// To the maximum extent possible under law, the author(s) and contributor(s) have
// dedicated all copyright and related and neighboring rights to this software
// to the public domain worldwide. This software is distributed without warranty.
//--------------------------------------------------------------------------
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR   
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,     
// FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR CONTRIBUTORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR 
// IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//--------------------------------------------------------------------------
package LSJava.LSComponents;
import  LSJava.LSUtility.*;
import  java.awt.event.*;
import  java.awt.*;


//--------------------------------------------------------------------------
public class LSTextFieldWithListenersForDoubleNonNegative extends LSTextFieldWithListenersForDouble
{
   // Constructor ---------------------------------------------------------
   public LSTextFieldWithListenersForDoubleNonNegative( Color colorForInvalidTextfieldOrNull, double initialValue,  int textWidth, boolean isEditable, LSContainer container, int gridWidth, int gridHeight, ActionListener actionListenerOrNull, FocusListener focusListenerOrNull, KeyListener keyListenerOrNull )   { super( colorForInvalidTextfieldOrNull, initialValue,  textWidth, isEditable, container, gridWidth, gridHeight, actionListenerOrNull, focusListenerOrNull, keyListenerOrNull ); }
   public LSTextFieldWithListenersForDoubleNonNegative( Color colorForInvalidTextfieldOrNull, String initialString, int textWidth, boolean isEditable, LSContainer container, int gridWidth, int gridHeight, ActionListener actionListenerOrNull, FocusListener focusListenerOrNull, KeyListener keyListenerOrNull )   { super( colorForInvalidTextfieldOrNull, initialString, textWidth, isEditable, container, gridWidth, gridHeight, actionListenerOrNull, focusListenerOrNull, keyListenerOrNull ); }


   //-------------------------------------------------------------------------
   protected String  EventActionOrFocusOrKeyEventReturnErrorStringVirtual( )
   {
      return super.IsTextFieldValidDouble() ? null : "Error -- Bad non-negative number: ";
   }

}
