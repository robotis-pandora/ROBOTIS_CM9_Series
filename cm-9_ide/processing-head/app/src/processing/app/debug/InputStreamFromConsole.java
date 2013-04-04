package processing.app.debug;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class InputStreamFromConsole extends Thread {
	
	BufferedReader br =null;
	public InputStreamFromConsole( InputStream is ) {
		this.br = new BufferedReader( new InputStreamReader(is)) ;
	}
	
	public void run() {
		String line = "";
		
		try {
			while( (line=br.readLine()) != null ){
				System.out.println(">" + line );
			}			
		}catch ( IOException e) {
			
		}
	}
}
