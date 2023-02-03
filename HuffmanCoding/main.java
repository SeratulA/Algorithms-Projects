import java.util.*;
import java.io.*;

public class main{

	public static class treeNode{
		String chStr;
		int frequency;
		String code;
		treeNode left;
		treeNode right;
		treeNode next;

		public treeNode(){
			chStr = "dummy";
			frequency = -999;
			code = "";
			left = null;
			right = null;
			next = null;
		}

		public treeNode(String chStr, int prob, String code, treeNode left, treeNode right, treeNode next){
			this.chStr = chStr;
			this.frequency = prob;
			this.code = code;
			this.left = left;
			this.right = right;
			this.next = next;
		}

		public void printNode(treeNode T, BufferedWriter outFile)throws IOException{
			if(T.right == null || T.left == null) {
				if (T.chStr == "dummy") outFile.write("chStr = "+ T.chStr + " " + ", Frequency = " + T.frequency + ", Code = " + T.code + ", Next chStr = " + T.next.chStr + ", Left chStr = null " + ", Right chStr = null " + ".\n");
				else if (T.next == null) outFile.write("chStr = "+ T.chStr + " " + ", Frequency = " + T.frequency + ", Code = " + T.code + ", Next chStr = null"+ ", Left chStr = null" + ", Right chStr = null" + ".\n");
				else outFile.write("chStr = "+ T.chStr + " " + ", Frequency = " + T.frequency + ", Code = " + T.code + ", Next chStr = " + T.next.chStr + ", Left chStr = null" + ", Right chStr = null" + ".\n");
			}
			else {
				if (T.chStr == "dummy") outFile.write("chStr = "+ T.chStr + " " + ", Frequency = " + T.frequency + ", Code = " + T.code + ", Next chStr = " + T.next.chStr + ", Left chStr = null " + ", Right chStr = null " + ".\n");
				else if (T.next == null) outFile.write("chStr = "+ T.chStr + " " + ", Frequency = " + T.frequency + ", Code = " + T.code + ", Next chStr = null"+ ", Left chStr = " + T.left.chStr + ", Right chStr = null" + ".\n");
				else outFile.write("chStr = "+ T.chStr + " " + ", Frequency = " + T.frequency + ", Code = " + T.code + ", Next chStr = " + T.next.chStr + ", Left chStr = " + T.left.chStr + ", Right chStr = " + T.right.chStr + ".\n");
			}
		}
	}

	public static class linkedList{
		static treeNode listHead;

		public linkedList(){
			listHead = new treeNode();
			treeNode dummy = new treeNode("dummy", -999, "",null,null,null );
			listHead = dummy;
			dummy.frequency = -999;
			dummy.left = null;
		}

		public static treeNode findSpot(treeNode newNode){
			treeNode spot = listHead;
			while(spot.next != null){
				if(spot.next != null && spot.next.frequency < newNode.frequency)
					spot = spot.next;
				else
					return spot;
			}
			return spot;
		}

		public static void insert(treeNode spot,treeNode newNode){
			newNode.next = spot.next;
			spot.next = newNode;
		}

		public static void insertNewNode(treeNode listHead,treeNode newNode){
			treeNode spot = findSpot(newNode);
			insert(spot,newNode);
		}

		public static void printList(treeNode listHead, BufferedWriter outFile)throws IOException {

			treeNode temp = listHead;
			outFile.write("ListHead --> ");
			while(temp.next != null) {
				temp.printNode(temp, outFile);
				temp = temp.next;
			}
			temp.printNode(temp, outFile);
			outFile.write("\r");
		}
	}

	public static class BinaryTree {
		static treeNode Root = new treeNode();
		static int[] charCountAry = new int[256]; 
		static String[] charCode = new String[256]; 

		public BinaryTree(){
			Root = new treeNode();
		}

		public BinaryTree(treeNode listHead){
			Root = listHead;
		}

		public static boolean isLeaf(treeNode node){

			if(node.left == null && node.right == null)
				return true;
			else
				return false;
		}

		public static void preOrderTraversal(treeNode Root, BufferedWriter outFile)throws IOException{

			if (isLeaf(Root)) Root.printNode(Root, outFile);
			else {
				Root.printNode(Root, outFile);
				preOrderTraversal(Root.left, outFile);
				preOrderTraversal(Root.right, outFile);
			}
		}
		public static void postOrderTraversal(treeNode Root, BufferedWriter outFile)throws IOException{
			if (isLeaf(Root)) Root.printNode(Root, outFile);
			else {
				postOrderTraversal(Root.left, outFile);
				postOrderTraversal(Root.right, outFile);
				Root.printNode(Root, outFile);
			}
		}
		public static void inOrderTraversal(treeNode Root, BufferedWriter outFile)throws IOException{
			if (isLeaf(Root)) Root.printNode(Root, outFile);
			else {
				inOrderTraversal(Root.left, outFile);
				Root.printNode(Root, outFile);
				inOrderTraversal(Root.right, outFile);
			}
		}
		public static void computeCharCounts (Scanner inFile, int [] charCountAry) {
			int index = 0;
			while (inFile.hasNext()){
				String nextline = inFile.nextLine();

				for(int i = 0; i < nextline.length(); i++){
					index = (int) nextline.charAt(i);
					if(index >= 0 && index <= 255)

						charCountAry[index] ++;
				}
			}
		}
		public static void printCountAry (int [] charCountAry, BufferedWriter outFile) throws IOException {
			for(int i = 0; i < charCountAry.length; i++){
				if(charCountAry[i] > 0){
					outFile.write((char)i + "\t" + charCountAry[i] + "\r\n"); 
				}
			}
			outFile.write("\r\n"); 
		}

		public static void constructHuffmanLList (int [] charCountAry, BufferedWriter outFile) throws IOException {

			int index = 0;
			while (index < 256) {
				if (charCountAry[index] > 0) {
					String chr = Character.toString((char)(index));
					int prob = charCountAry[index];
					treeNode newNode = new treeNode(chr,prob, "", null, null, null);
					linkedList.insertNewNode(linkedList.listHead, newNode);
					linkedList.printList(linkedList.listHead, outFile);
				}
				index++;
			}
			Root = linkedList.listHead;
		}

		public static void constructHuffmanBinTree (treeNode listHead, BufferedWriter outFile) throws IOException {

			outFile.write("\r\r\r\r");
			while(listHead.next.next!= null){
				treeNode newNode = new treeNode();
				newNode.frequency = listHead.next.frequency + listHead.next.next.frequency;
				newNode.chStr = listHead.next.chStr + listHead.next.next.chStr;
				newNode.left = listHead.next;
				newNode.right = listHead.next.next;
				newNode.next = null;
				linkedList.insertNewNode(listHead, newNode);
				linkedList.listHead.next = listHead.next.next.next;
				linkedList.printList(listHead, outFile);
			}
			Root = linkedList.listHead.next;
		}
		public static void Encode (Scanner orgFile, File outFile) throws IOException {
			FileWriter outFile2 = new FileWriter(outFile);
			char charIn;
			String lineIn = orgFile.nextLine();
			int index;
			String code;

			while (orgFile.hasNextLine()) {
				for (int i = 0; i < lineIn.length(); i++) {
					charIn = lineIn.charAt(i);
					index = (int)charIn;
					code = charCode[index];
					outFile2.write(code);
				}
				lineIn = orgFile.nextLine();
			}
			for (int i = 0; i < lineIn.length(); i++) {
				charIn = lineIn.charAt(i);
				index = (int)charIn;
				code = charCode[index];
				outFile2.write(code);
			}
			outFile2.close();
		}
		public static void Decode (File inFile, BufferedWriter outFile) throws IOException {

			FileReader fileIn=new FileReader(inFile);
			BufferedReader inFile2=new BufferedReader(fileIn);

			treeNode spot = new treeNode();
			int c = 0;
			char oneBit;
			spot = Root;

			while((c = inFile2.read()) != -1)  {
				if (isLeaf(spot)) {
					outFile.write(spot.chStr);
					spot = Root;
				}
				oneBit = (char) c;
				if (oneBit == '0') spot = spot.left;
				else if (oneBit == '1') spot = spot.right;
				else {
					System.out.println("Error! The compress file contains invaliud character\n");
					System.exit(0);
				}	
			}
			if (!isLeaf(spot)) System.out.println("Error! The compress file is corrupted\n");
			inFile2.close();
		}
		public static void constructCharCode(treeNode T, String code){
			if(isLeaf(T)){
				T.code = code;
				char indexChar = (char)T.chStr.charAt(0);
				charCode[(int)indexChar] = code;
			}
			else{
				constructCharCode(T.left, code + "0");
				constructCharCode(T.right, code + "1");
			}
		}


		public static void userInterface() throws IOException {
			Scanner input = new Scanner(System.in);
			String nameOrg = null;
			String nameCompress;
			String nameDeCompress;
			char yesNo = 0;

			while (yesNo != 'n' || yesNo != 'N') {
				System.out.println("If you do not want to compress a file, type N. If not, type anything else.");
				yesNo = input.next().charAt(0);

				if(yesNo == 'N' || yesNo == 'n')
					System.exit(0); 
				else{
					System.out.println("Enter the name of the input file to be compressed");
					nameOrg = input.next();
				}

				nameCompress = nameOrg + "_Compressed.txt";
				nameDeCompress = nameOrg + "_DeCompress.txt";
				nameOrg = nameOrg + ".txt";
				Scanner orgFile = new Scanner(new FileReader(nameOrg));
				File compFile = new File(nameCompress);

				BufferedWriter deCompFile = new BufferedWriter(new FileWriter(nameDeCompress));

				Encode(orgFile,compFile);

				File compfile = new File(nameCompress);
				Scanner newcompFile = new Scanner(compfile);
				Decode(compfile, deCompFile);

				orgFile.close();
				newcompFile.close();
				deCompFile.close();
			}
		}
	}


	public static void main(String[] args) throws IOException{

		String nameInFile = args[0];
		File file = new File("data.txt");
		Scanner InFile = new Scanner(file);
		String nameDebugFile = nameInFile + "_DeBug";
		BufferedWriter DebugFile = new BufferedWriter(new FileWriter(nameDebugFile));
		String emptyString = "";
		linkedList LinkedList = new linkedList();
		treeNode listHead = LinkedList.listHead;
		BinaryTree BinaryTree = new BinaryTree();


		BinaryTree.computeCharCounts(InFile,BinaryTree.charCountAry);
		BinaryTree.printCountAry(BinaryTree.charCountAry, DebugFile);
		BinaryTree.constructHuffmanLList(BinaryTree.charCountAry, DebugFile);
		BinaryTree.constructHuffmanBinTree(LinkedList.listHead, DebugFile);
		BinaryTree.constructCharCode(BinaryTree.Root, emptyString);

		main.linkedList.printList(LinkedList.listHead,DebugFile);
		DebugFile.write("Preforming preorder Traversal\n");
		main.BinaryTree.preOrderTraversal(BinaryTree.Root, DebugFile);

		DebugFile.write("\nPreforming inOrder Traversal\n");
		main.BinaryTree.inOrderTraversal(BinaryTree.Root, DebugFile);

		DebugFile.write("\nPreforming postOrder Traversal\n");
		main.BinaryTree.postOrderTraversal(BinaryTree.Root, DebugFile);

		BinaryTree.userInterface();

		InFile.close();
		DebugFile.close();
	}


}





