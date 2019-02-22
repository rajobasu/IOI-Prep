import java.math.*;
import java.io.*;
import java.util.*;
import java.nio.*;

public class GOLD_p1_2015_OPEN{
	static BufferedReader br;
	static PrintWriter pw;

	static BigInteger calcSize(BigInteger node,BigInteger smallerVal)throws IOException{
		if(node.equals(BigInteger.ZERO)){
			return BigInteger.ZERO;
		}

		pw.println(node);
		pw.flush();
		String[] s = br.readLine().split(" ");
		BigInteger leftNode = new BigInteger(s[0]);
		BigInteger rightNode = new BigInteger(s[1]);

		BigInteger leftVal,rightVal;

		if(smallerVal.mod(new BigInteger("2")).equals(BigInteger.ONE)){
			rightVal = smallerVal.subtract(BigInteger.ONE).divide(new BigInteger("2"));
			leftVal = calcSize(leftNode,rightVal);
		}else{
			leftVal = smallerVal.divide(new BigInteger("2"));
			rightVal = calcSize(rightNode,leftVal.subtract(BigInteger.ONE));
		}
		return leftVal.add(rightVal).add(BigInteger.ONE);
	}

	static BigInteger calcSize(BigInteger node)throws IOException{
		pw.println(node);
		pw.flush();
		String[] s = br.readLine().split(" ");
		BigInteger leftNode = new BigInteger(s[0]);
		BigInteger rightNode = new BigInteger(s[1]);

		if(rightNode.equals(BigInteger.ZERO)){
			if(leftNode.equals(BigInteger.ZERO)){
				return BigInteger.ONE;
			}else{
				return BigInteger.ONE.add(BigInteger.ONE);
			}
		}else{
			BigInteger rightVal = calcSize(rightNode);
			BigInteger leftVal = calcSize(leftNode,rightVal);
			return rightVal.add(leftVal).add(BigInteger.ONE);
		}
	}

	public static void main(String[] args)throws IOException{
		br = new BufferedReader(new InputStreamReader(System.in));
		pw = new PrintWriter(System.out);
		pw.println("Answer " + calcSize(BigInteger.ONE));
		pw.flush();

	}

}