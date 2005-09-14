package simtksuS26Pkg;

import simtkModel.*;
public class suS26Loader extends suS26 {

    static {
		System.loadLibrary("rdModelDll");
		System.loadLibrary("suS26Gui");
		RegisterTypes();
    }
    /**
	* Default no-param constructor
	*/
    public suS26Loader(){
      super("params.txt", null);
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
