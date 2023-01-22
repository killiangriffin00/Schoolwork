
public class Program
{
    static void Main()
    {
        List<int> input = new List<int>();
        AdvMessageClass print = new AdvMessageClass("HW1 C# BST");
        //request input from user
        print.printMessage("Enter a list of integers (0 - 100): "); 
        //record user input
        input = print.getInput();

        //load user input into BST using list constructor
        BinarySearchTree bst = new BinarySearchTree(input);
        
        //print statistics:
        //numbers in order
        bst.printBST(print);
        //number of nodes
        print.printMessage("NUMBER OF NODES: " + bst.countBST().ToString() + "\n");
        //number of levels
        print.printMessage("NUMBER OF LEVELS: " + bst.levelBST().ToString() + "\n");
        //minimum levels for optimal tree
        print.printMessage("MINIMUM NUMBER OF LEVELS: " + bst.minLevel().ToString() + "\n\n");
    }
}

//message class allows for persistent header and clear/pause function with cleaner output
public class AdvMessageClass 
{
    private string header = "(default message)";
    public void printMessage(string message) { Console.Write(message); }
    public List<int> getInput()
    {
        String input = Console.ReadLine(), debug;
        String[] strArray = input.Split(' ');
        List<int> nums = new List<int>();

        for (int i = 0; i < strArray.Length; i++)
        {
            nums.Add(int.Parse(strArray[i]));
        }
        this.clear();
        return nums;
    }

    public void clear()
    {
        Console.Clear();
        Console.WriteLine(header);
    }
    public void pause()
    {
        Console.WriteLine("Press enter to continue . . .\n");
        Console.ReadLine();
        clear();
    }
    public string Header
    {
        get { return header; }
        set { header = value; }
    }
    public AdvMessageClass() { }

    public AdvMessageClass(string projectTitle)
    {
        this.header = "|---------------*" + projectTitle + "*---------------|";
        this.clear();
    }
}

//actual logic of recursive functions is located in node class
public class BSTNode 
{
    private int item;
    private BSTNode? left;
    private BSTNode? right;
    public BSTNode? Left
    {
        get { return left; }
        set { left = value; }
    }
    public BSTNode? Right
    {
        get { return right; }
        set { left = value; }
    }
    public int Item 
    {
        get { return item; } 
        set { item = value; }
    }
    public BSTNode(int item)
    {
        this.item = item;
        this.left = null;
        this.right = null;
    }
    public void push(BSTNode node)
    {
        if(node.Item > item)
        {
            if(right == null)
            {
                right = node;
                return;
            }
            right.push(node);
            return;
        }
        if (node.Item < item)
        {
            if (left == null)
            {
                left = node;
                return;
            }
            left.push(node);
            return;
        }
    }
    public void printBST(AdvMessageClass output)
    {
        if(left != null)
        {
            left.printBST(output);
        }
        output.printMessage(" " + item.ToString() + " ");
        if(right != null)
        {
            right.printBST(output);
        }
    }
    public int countBST()
    {
        int val = 0;
        if(left != null)
        {
            val += left.countBST();
        }
        if (right != null)
        {
            val += right.countBST();
        }
        return ++val;
    }
    public int levelBST()
    {
        if(left == null && right == null)
        {
            return 1;
        }
        if(left == null)
        {
            return right.levelBST() + 1;
        }
        if(right == null)
        {
            return left.levelBST() + 1;
        }

        int leftLevel = left.levelBST(), rightLevel = right.levelBST();
        if (leftLevel > rightLevel)
        {
            return leftLevel + 1;
        }
        return rightLevel + 1;
        
    }
}
//binary search tree class stores root node and calls recursive node functions
public class BinarySearchTree
{
    private BSTNode root;
    //default constructor can be used alongside push function to construct tree
    public BinarySearchTree(int rootItem)
    {
        root = new BSTNode(rootItem);
    }
    //int list constructor also included to make tree creation more simple,
    //uses push(List<int>)
    public BinarySearchTree(List<int> numList)
    {
        root = new BSTNode(numList[0]);
        numList.RemoveAt(0);
        push(numList);
    }
    public BSTNode push(BSTNode node)
    {
        root.push(node);
        return root;
    }
    public BSTNode push(List<int> numList)
    {
        for (int i = 0; i < numList.Count; i++)
        {
            push(new BSTNode(numList[i]));
        }
        return root;
    }
    //putting recursive function logic in the node functions allows for more simple 
    //function calls and better formatting
    public void printBST(AdvMessageClass output)
    {
        output.printMessage("BST IN-ORDER PRINT:\n");
        output.printMessage("[");
        root.printBST(output);
        output.printMessage("]\n");

    }
    public int countBST()
    {
        return root.countBST();
    }
    public int levelBST()
    {
        return root.levelBST();
    }
    public int minLevel() 
    {
        return 1 + (int)Math.Log(countBST(), 2);
    }
}