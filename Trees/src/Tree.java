
public class Tree {

	public static void main(String[] args) {
	    
		Tree Tr = new Tree(); 
		Tr.PopulateTreeDefault();
        Tr.InorderTraversal(); 
	}
	
	private void InorderTraversal() {
		PostOrderTraversal(root); 
		
	}

	private void PostOrderTraversal(Node currentNode) {
		if (currentNode != null)
		{
			PostOrderTraversal(currentNode.left);	
			PostOrderTraversal(currentNode.right); 
			Visit(currentNode); 
		}
		
	}

	private void Visit(Node currentNode) {
		System.out.println("The value of the current node is: " + Integer.toString(currentNode.data));
		
	}

	public class Node{
		int data;
		Node left; 
		Node right; 

		Node(int data)
		{
			this.data = data; 
			this.left = null; 
			this.right = null; 
		}
		
		Node()
		{
			this.data = 0; 
			this.left = null; 
			this.right = null; 
		}
	}
	
	public Node root; 
	public Tree()
	{
			root = new Node(); 
    }

	public void PopulateTreeDefault() {
		int start = 5; 
		root.data = start;
		for (int i = 1; i < start; i++)
		{
			AddNode(start+i);
			AddNode(start-i); 
		}   
	}
	
	public void AddNode(int data)
	{
		Node newNode = new Node(data);
		if (root == null)
		{
			root = newNode; 
			return; 
		}
		else 
		{
			Node current = root; 
			Node parent =  null;
			while(current != null)
			{
				parent = current; 
				if (data < current.data)
				{
					current = current.left;
				}
				else 
				{
					current = current.right; 
				}
			}
			
			if (parent.data < data)
				parent.right = newNode; 
			else 
				parent.left = newNode; 
			
		}
	}	

}
