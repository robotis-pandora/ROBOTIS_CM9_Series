package processing.app;

public class SharedObjectForThreadControl {

	Serial proxy;
	boolean downloadResult = false;
	void setSerialProxy(Serial tmp){
		
		proxy = tmp;
	}
	synchronized void barkingDog(boolean result) { 
	 
		//System.out.println("[ROBOTIS]Now, notify end of download"); 
		downloadResult = result;
		notify(); 
		 
	} 
	synchronized boolean sleepingBaby() { 
		try {
			//System.out.println("[ROBOTIS]Waiting for finishing uploading...");
			wait(); 
		} catch(InterruptedException e) { 
			System.out.println("InterruptedException caught"); 
		} 
		 
		//System.out.println("[ROBOTIS]Wake up!");
		return downloadResult; 
		 
		} 
}
