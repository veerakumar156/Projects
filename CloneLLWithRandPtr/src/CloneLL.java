
public class CloneLL {
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		CloneLL CLL = new CloneLL();
		LinkedList LL = CLL.new LinkedList(1);
		LL.AddNode(2);
		LL.AddNode(3);
		LL.AddNode(4);
		LL.AddNode(5);
		LL.AddNode(6);
		LL.printList();
		LL.PopulateRandomPointers();
		LinkedList newLL = LL.Clone();
		
		newLL.printList();
	}
	
	
	// inner class
	   private class LinkedList {
		   private Node Head = null; 
		   
		   private LinkedList(int data)
		   {
			   Head = new Node(data);
		   }
		   
		   
		   private LinkedList(Node n)
		   {
			   Head = n;
		   }
		   
			public LinkedList Clone()
			{
				FirstStep();
				SecondStep();
				return ThirdStep();
			}
		   
		public void FirstStep()
		{
			//This method duplicates every node of the original linked list. 
			//duplicated nodes are weaved after the original node and thus increasing 
			//the size of the linked list twice that of original. 
			Node current = Head;
			while (current != null)
			{
				Node n = new Node(current.data);
				n.Next = current.Next;
				current.Next = n;
				current = n.Next;//To continue the loop
			}
		}
		
		public void SecondStep()
		{
			//This method copies the random pointers in to the new nodes 
			Node current = Head;
			while (current != null)
			{
				if (current.Random != null)
					current.Next.Random = current.Random.Next;
				
				current = current.Next.Next;
			}
		}
		
		public LinkedList ThirdStep()
		{
			//Duplicated linked list is unlinked from the original linked list. The cloned 
			//linked list is returned
			Node tempNode;
			Node current = Head;
			Node cloneHead = null;
			while (current != null)
			{
				if (cloneHead == null)
					cloneHead = current.Next;

				tempNode = current.Next;
				tempNode.Next = current.Next.Next;
				current.Next = tempNode.Next;
				current = current.Next;//To continue the loop
			}
			
			return new LinkedList(cloneHead);
		}
			
		   public void PopulateRandomPointers()
		   {
			   //TODO
		   }
		   
		   public void printList() {
				Node n = Head;
				System.out.println("The elements in the linked list are: ");
				while (n.Next != null)
				{
					System.out.println(n.data);
					n = n.Next;
				}
				System.out.println(n.data); //the last element for which n.next is null is printed here
			}	
		   
		   private class Node{
			   int data;
			   Node Next;
			   Node Random;
			   public Node(int d)
			   {
				   data = d; 
				   Next = null;
				   Random = null;
			   }
			   
		   }
		   
		   public void AddNode(int data)
		   {
			   Node n = new Node(data);
			   if (Head == null)
				   Head = n;
			   else 
			   {
				   Node current = Head;
				   while(current.Next != null) {
					   current = current.Next;
					}
					current.Next = n; 
			   }
		   }
	   }

}
