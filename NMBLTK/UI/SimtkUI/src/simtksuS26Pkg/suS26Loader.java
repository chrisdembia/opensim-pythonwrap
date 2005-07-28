package simtksuS26Pkg;

import simtkModel.*;
import simtkCommands.*;
import simtkCore.*;
public class suS26Loader extends suS26 {

    static {
		System.loadLibrary("rdModelDll");
		System.loadLibrary("suS26Gui_D");
		RegisterTypes();
    }
    /**
	* Default no-param constructor
	*/
    public suS26Loader(){
      super("C:\\Work\\DemoFiles\\params.txt", null);
      rdVisibleObject obj = this.getVisibleObjectByName("calcn_rp");
      obj.getVisibleProperties().setDisplayPreference(0);
      obj = this.getVisibleObjectByName("calcn_lp");
      obj.getVisibleProperties().setDisplayPreference(0);

	};

	/**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
    }
}
