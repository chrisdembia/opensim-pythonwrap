package simtkcgmalWalking01Pkg;

import simtkModel.*;
public class cgmalWalking01Loader extends cgmalWalking01 {

    static {
		System.loadLibrary("rdModelDll");
		System.loadLibrary("cgmalWalking01_D");
		RegisterTypes();
    }
    /**
	* Default no-param constructor
	*/
    public cgmalWalking01Loader(){
		super(null, null);
	};
	
	/**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
    }
}
