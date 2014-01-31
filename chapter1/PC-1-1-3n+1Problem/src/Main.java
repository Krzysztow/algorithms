import com.krzysztow.algorithms.ThreeNPlus1Problem;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.ArrayList;

public class Main {
	public static void main(String [] args) {
		if (1 != args.length) {
			System.out.println("Usage: <file-name> (provided " + args.length + " arguments).");
			return;
		}
		
		try {
			ThreeNPlus1Problem problemSolver = new ThreeNPlus1Problem();
			
			BufferedReader reader = new BufferedReader(new FileReader(args[0]));
			
			//for each line read
			String input = reader.readLine();
			while (null != input) {
				//parse ranges values
				String values[] = input.split("\\s+");			
				Integer first = Integer.parseInt(values[0]);
				Integer second = Integer.parseInt(values[1]);
				
				Integer maxRunsNo = new Integer(0);
				Integer runsNo = null;
				for (Integer it = first; it <= second; ++it) {
					//get values for a given integer
					runsNo = problemSolver.runProblem(it);		
					if (runsNo > maxRunsNo)
						maxRunsNo = runsNo;
				}
				
				//print the output for a line
				System.out.println(first + " " + second + " " + maxRunsNo);
				//read another line
				input = reader.readLine();
			}
		}
		catch(IOException io){
			io.printStackTrace();
		}
	}
}
