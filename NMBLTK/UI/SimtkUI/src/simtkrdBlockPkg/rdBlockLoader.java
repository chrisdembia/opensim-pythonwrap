package simtkrdBlockPkg;

import simtkModel.*;
public class rdBlockLoader extends rdBlock {

    static {
		System.loadLibrary("rdModelDll");
		System.loadLibrary("rdBlock_D");
		RegisterTypes();
    }
    /**
	* Default no-param constructor
	*/
    public rdBlockLoader(){
		super(null, null);
	};
	
	/**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
    }
}
